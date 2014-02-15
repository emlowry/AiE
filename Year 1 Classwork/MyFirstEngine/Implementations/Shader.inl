/******************************************************************************
 * File:               Shader.inl
 * Author:             Elizabeth Lowry
 * Date Created:       February 13, 2014
 * Description:        Inline function implementations for the Shader class.
 * Last Modified:      February 13, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef SHADER__INL
#define SHADER__INL

#include "../Declarations/DumbString.h"
#include "../Declarations/GameEngine.h"
#include "../Declarations/GLFW.h"
#include "../Declarations/Shader.h"
#include "../Declarations/Singleton.h"
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include "../Declarations/MyFirstEngineMacros.h"

namespace MyFirstEngine
{

// store the loaded shaders
struct ShaderStorage : public Singleton< ShaderStorage >
{
    typedef std::unordered_map< DumbString, Shader > SourceLookup;
    std::unordered_map< GLenum, SourceLookup > lookup;
}

// Copy constructor
INLINE Shader::Shader( const Shader& ac_roShader )
    : m_uiID( ac_roShader.m_uiID ), m_eType( ac_roShader.m_eType ) {}

// If source name is null or empty, use default shader
// If source name hasn't been loaded yet, do so and compile a new shader
INLINE Shader::Shader( GLenum a_eType, const char* ac_pcSourceName )
    : m_eType( ac_roShader.m_eType )
{
    // TODO
}

// If source text is null or empty, behave like the previous constructor
// Otherwise, if source hasn't already been loaded, do so and compile
// Otherotherwise, if recompile flag is false, just use already-compiled
// shader, while if flag is true, replace stored source and recompile shader
INLINE Shader::Shader( GLenum a_eType, const char* ac_pcSourceName,
                       const char* ac_pcSourceText, bool a_bRecompile )
    : m_eType( ac_roShader.m_eType )
{
    // TODO
}

// just use the ID of an existing shader
INLINE Shader::Shader( GLuint a_uiID ) : m_uiID( a_uiID )
{
    GLint iType;
    glGetShaderiv( a_uiID, GL_SHADER_TYPE, &iType );
    m_eType = iType;
}

// Is this shader compiled and not marked for deletion?
INLINE bool Shader::IsValid( GLuint a_uiID )
{
    if( GL_FALSE == glIsShader( a_uiID ) )
    {
        return false;
    }
    GLint iCompiled, iDelete;
    glGetShaderiv( a_uiID, GL_COMPILE_STATUS, &iCompiled );
    glGetShaderiv( a_uiID, GL_DELETE_STATUS, &iDelete );
    return ( GL_TRUE == iCompiled && GL_FALSE == iDeleted );
}
INLINE bool Shader::IsValid() const
{
    return IsValid( m_uiID );
}

// Get shader properties
INLINE GLenum Shader::Type() const
{
    return m_eType;
}
INLINE GLuint Shader::ID() const
{
    return m_uiID;
}

//
// Static functions
//

// Get the default shader of the given type
INLINE Shader Shader::Default( GLenum a_eType )
{
    if( 0 == ShaderStorage::Instance().lookup[ a_eType ].count( "" ) )
    {
        switch( a_eType )
        {
        case GL_FRAGMENT_SHADER:
            return Shader( a_eType, "", DefaultFragmentShaderSource() );
            break;
        case GL_VERTEX_SHADER:
            return Shader( a_eType, "", DefaultVertexShaderSource() );
            break;
        default:
            throw std::invalid_argument( "No default shader for this shader type" );
            break;
        }
    }
    return ShaderStorage::Instance().lookup[ a_eType ][ "" ];
}

// source code for default shaders
INLINE const DumbString& Shader::DefaultFragmentShaderSource()
{
    static DumbString s_oSource = "varying vec4 v_v4Color; "
                                  "void main(void) { "
                                  "    gl_FragColor = v_v4Color; "
                                  "}";
    return s_oSource;
}
INLINE const DumbString& Shader::DefaultVertexShaderSource()
{
    static DumbString s_oSource =
        "varying vec4 v_v4Color; "
        "void main(void) { "
        "    v_v4Color = gl_Color; "
        "    gl_Position = gl_ModelViewProjectionMatrix * glVertex; "
        "}";
    return s_oSource;
}

// Destroy all shaders
INLINE void Shader::DestroyAll()
{
    typedef std::pair< Glenum, ShaderStorage::SourceLookup > LookupPair
    for each( LookupPair oPair in ShaderStorage::Instance().lookup )
    {
        for each( std::pair< DumbString, Shader > oLookup in oPair.second )
        {
            glDeleteShader( Shader.ID() );
        }
    }
    ShaderStorage::Instance().lookup.clear();
}

// load source code
INLINE DumbString Shader::LoadSource( const char* ac_pcFileName )
{
    //TODO
}

}   // namespace MyFirstEngine

#endif  // SHADER__INL
