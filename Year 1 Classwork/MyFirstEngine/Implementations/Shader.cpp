/******************************************************************************
 * File:               Shader.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       February 13, 2014
 * Description:        Function implementations for the Shader class.
 * Last Modified:      March 25, 2014
 * Last Modification:  Removing PIMPL static pointers from header.
 ******************************************************************************/

#include "../Declarations/GameEngine.h"
#include "../Declarations/GLFW.h"
#include "../Declarations/Shader.h"
#include "MathLibrary.h"
#include <fstream>
#include <stdexcept>
#include <unordered_map>
#include <utility>

//
// File-only helper functions and classes
//
namespace
{
    
// looking up existing shaders and source text
class ShaderLookup
    : public std::unordered_map< GLenum, std::unordered_map< Utility::DumbString, GLuint > >,
      public Utility::Singleton< ShaderLookup >
{
    friend class Utility::Singleton< ShaderLookup >;
public:
    typedef std::unordered_map< Utility::DumbString, GLuint > InnerType;
    typedef InnerType::value_type InnerValueType;
    typedef std::unordered_map< GLenum, InnerType > BaseType;
    typedef BaseType::value_type ValueType;
    virtual ~ShaderLookup() {}
private:
    ShaderLookup() {}
};
class SourceNameLookup
    : public std::unordered_map< GLuint, Utility::DumbString >,
      public Utility::Singleton< SourceNameLookup >
{
    friend class Utility::Singleton< SourceNameLookup >;
public:
    typedef std::unordered_map< GLuint, Utility::DumbString > BaseType;
    typedef BaseType::value_type ValueType;
    virtual ~SourceNameLookup() {}
private:
    SourceNameLookup() {}
};
ShaderLookup& Lookup()
{
    return ShaderLookup::Instance();
}
SourceNameLookup& SourceLookup()
{
    return SourceNameLookup::Instance();
}

// Compile a shader from the given source code
GLuint CompileShader( const char* ac_pcSourceText, GLuint a_uiID )
{
    glShaderSource( a_uiID, 1, &ac_pcSourceText, nullptr );
    glCompileShader( a_uiID );
    return a_uiID;
}
GLuint CompileShader( GLenum a_eType, const char* ac_pcSourceText )
{
    GLuint uiID = glCreateShader( a_eType );
    CompileShader( ac_pcSourceText, uiID );
    return uiID;
}

}   // namespace

//
// Class functions
//
namespace MyFirstEngine
{

using namespace Utility;

// If source name is null or empty, use default shader
// If source name hasn't been loaded yet, do so and compile a new shader
Shader::Shader( GLenum a_eType, const char* ac_pcSourceName, bool a_bRecompile )
{
    DumbString oSourceName( ac_pcSourceName );
    
    // If requesting the default shader of this type, use the specialized
    // Default function to make sure the default shader is loaded and compiled.
    if( "" == oSourceName )
    {
        m_uiID = Null().m_uiID;
    }

    // If a shader has already been compiled from source code with the given
    // name, reuse its ID.
    else if( 0 < Lookup()[ a_eType ].count( oSourceName ) )
    {
        m_uiID = Lookup()[ a_eType ][ oSourceName ];

        // If the recompile flag is set to true, reload and recompile the shader
        if( a_bRecompile )
        {
            CompileShader( DumbString::LoadFrom( oSourceName ), m_uiID );
        }
    }

    // Otherwise, compile the new shader and make sure to store it in the lookup
    // map.
    else
    {
        m_uiID = CompileShader( a_eType, DumbString::LoadFrom( oSourceName ) );
        Lookup()[ a_eType ][ oSourceName ] = m_uiID;
        SourceLookup()[ m_uiID ] = oSourceName;
    }
}

// If source text is null or empty, behave like the previous constructor
// Otherwise, if source hasn't already been loaded, do so and compile
// Otherotherwise, if recompile flag is false, just use already-compiled
// shader, while if flag is true, replace stored source and recompile shader
Shader::Shader( GLenum a_eType, const char* ac_pcSourceName,
                const char* ac_pcSourceText, bool a_bRecompile )
{
    DumbString oSourceName( ac_pcSourceName );
    DumbString oSourceText( ac_pcSourceText );

    // If requesting the default shader or an already-compiled shader, reuse the
    // existing ID.
    if( "" == oSourceName || 0 < Lookup()[ a_eType ].count( oSourceName ) )
    {
        m_uiID = ( "" == oSourceName
                    ? Null().m_uiID : Lookup()[ a_eType ][ oSourceName ] );

        // If the recompile flag is set to true and either a file name or source
        // code is passed in, reload and recompile.
        if( a_bRecompile && ( "" != oSourceName || "" != oSourceText ) )
        {
            CompileShader( "" == oSourceText
                            ? DumbString::LoadFrom( oSourceName ) : oSourceText,
                           m_uiID );
        }
    }

    // If there is no already-compiled shader, load and compile.
    else
    {
        m_uiID = CompileShader( a_eType, "" == oSourceText
                                         ? DumbString::LoadFrom( oSourceName )
                                         : oSourceText );
        Lookup()[ a_eType ][ oSourceName ] = m_uiID;
        SourceLookup()[ m_uiID ] = oSourceName;
    }
}

// Delete the shader
void Shader::Delete()
{
    if( 0 != m_uiID )
    {
        glDeleteShader( m_uiID );
        Lookup()[ Type() ].erase( SourceLookup()[ m_uiID ] );
        SourceLookup().erase( m_uiID );
    }
}

// Get the info log
DumbString Shader::GetLog() const
{
    // get the size of the log
    GLint uiSize = 0;
    glGetShaderiv( m_uiID, GL_INFO_LOG_LENGTH, &uiSize );

    // get the log data
    char* pcData = new char[ uiSize + 1 ];
    glGetShaderInfoLog( m_uiID, uiSize + 1, nullptr, pcData );

    // return the log data
    DumbString oString( pcData );
    delete[] pcData;
    return oString;
}

// Get the type of the shader
GLenum Shader::Type() const
{
    GLint iType;
    glGetShaderiv( m_uiID, GL_SHADER_TYPE, &iType );
    return (GLenum)iType;
}

//
// Static class functions
//

// Destroy all shaders
void Shader::DestroyAll()
{
    for each( ShaderLookup::ValueType oPair in Lookup() )
    {
        for each( ShaderLookup::InnerValueType oInnerPair in oPair.second )
        {
            glDeleteShader( oInnerPair.second );
        }
    }
    Lookup().clear();
    SourceLookup().clear();
}

// Is this shader compiled and not marked for deletion?
bool Shader::IsValid( GLuint a_uiID )
{
    if( GL_FALSE == glIsShader( a_uiID ) )
    {
        return false;
    }
    GLint iCompiled, iDeleted;
    glGetShaderiv( a_uiID, GL_COMPILE_STATUS, &iCompiled );
    glGetShaderiv( a_uiID, GL_DELETE_STATUS, &iDeleted );
    return ( GL_TRUE == iCompiled && GL_FALSE == iDeleted );
}

// Shader meaning no shader
const Shader& Shader::Null()
{
    static Shader soNull( 0 );
    return soNull;
}

}   // namespace MyFirstEngine

