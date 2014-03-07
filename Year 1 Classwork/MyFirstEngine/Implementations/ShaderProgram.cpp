/******************************************************************************
 * File:               ShaderProgram.hcpp
 * Author:             Elizabeth Lowry
 * Date Created:       February 24, 2014
 * Description:        Function implementations for the ShaderProgram class.
 * Last Modified:      March 6, 2014
 * Last Modification:  Refactoring.
 ******************************************************************************/

#include "../Declarations/GLFW.h"
#include "../Declarations/Shader.h"
#include "../Declarations/ShaderProgram.h"
#include "MathLibrary.h"
#include <list>
#include <unordered_map>
#include <vector>

namespace MyFirstEngine
{

using namespace Utility;

// declare classes instead of typedefs to avoid compiler warnings
// definition is only in cpp
class ShaderProgram::ProgramList
    : public std::vector< ShaderProgram* >,
      public Singleton< ShaderProgram::ProgramList >
{
    friend class Singleton< ProgramList >;
public:
    virtual ~ProgramList() {}
private:
    ProgramList() {}
};
class ShaderProgram::ProgramLookup
    : public std::unordered_map< GLuint, ShaderProgram* >,
      public Singleton< ShaderProgram::ProgramLookup >
{
    friend class Singleton< ProgramLookup >;
public:
    typedef std::unordered_map< GLuint, ShaderProgram* > BaseType;
    typedef BaseType::value_type ValueType;
    virtual ~ProgramLookup() {}
private:
    ProgramLookup();
};
class ShaderProgram::ShaderList : public std::list< Shader >
{
public:
    virtual ~ShaderList() {}
};

// store all the programs
ShaderProgram::ProgramList&
    ShaderProgram::sm_roList = ShaderProgram::ProgramList::Instance();
ShaderProgram::ProgramLookup&
    ShaderProgram::sm_roLookup = ShaderProgram::ProgramLookup::Instance();

// Default constructor used only by Null()
ShaderProgram::ShaderProgram()
    : m_uiID( 0 ), m_uiIndex( sm_roList.size() ), m_poShaders( new ShaderList() )
{
    sm_roList.push_back( this );
}

// Constructor - you should call Setup() after calling these
ShaderProgram::ShaderProgram( const Shader& ac_roVertexShader,
                              const Shader& ac_roFragmentShader,
                              const Shader& ac_roGeometryShader )
    : m_uiID( 0 ), m_uiIndex( sm_roList.size() ), m_poShaders( new ShaderList() )
{
    sm_roList.push_back( this );
    if( Shader::Null() != ac_roVertexShader )
    {
        Shaders().push_back( ac_roVertexShader );
    }
    if( Shader::Null() != ac_roFragmentShader )
    {
        Shaders().push_back( ac_roFragmentShader );
    }
    if( Shader::Null() != ac_roGeometryShader )
    {
        Shaders().push_back( ac_roGeometryShader );
    }
}
ShaderProgram::ShaderProgram( const Shader* ac_paoShaders,
                              unsigned int a_uiCount )
    : m_uiID( 0 ), m_uiIndex( sm_roList.size() ), m_poShaders( new ShaderList() )
{
    sm_roList.push_back( this );
    if( nullptr != ac_paoShaders )
    {
        for( unsigned int ui = 0; ui < a_uiCount; ++ui )
        {
            if( Shader::Null() != ac_paoShaders[ui] )
            {
                Shaders().push_back( ac_paoShaders[ui] );
            }
        }
    }
}

// Destructor - you should call Destroy() before calling this.
ShaderProgram::~ShaderProgram()
{
    sm_roList[ m_uiIndex ] = nullptr;
    delete m_poShaders;
}

// Delete this shader program
void ShaderProgram::Destroy()
{
    if( 0 != m_uiID )
    {
        DestroyData();
        glDeleteProgram( m_uiID );
        sm_roLookup.erase( m_uiID );
        m_uiID = 0;
    }
}

// Set up this shader program
void ShaderProgram::Setup()
{
    if( 0 == m_uiID )
    {
        m_uiID = glCreateProgram();
        for each( Shader oShader in Shaders() )
        {
            if( Shader::Null() != oShader )
            {
                glAttachShader( m_uiID, oShader.ID() );
            }
        }
        glLinkProgram( m_uiID );
        if( IsValid() )
        {
            sm_roLookup[ m_uiID ] = this;
            SetupData();
        }
        else
        {
            glDeleteProgram( m_uiID );
            m_uiID = 0;
        }
    }
}

// Start using this shader program
void ShaderProgram::Use() const
{
    glUseProgram( m_uiID );
    UseData();
}

// Get the first shader of the given type used by this program
Shader ShaderProgram::GetShader( GLenum a_eType ) const
{
    for each( Shader oShader in Shaders() )
    {
        if( oShader.Type() == a_eType )
        {
            return oShader;
        }
    }
    return Shader::Null();
}

// Get the info log
DumbString ShaderProgram::GetLog() const
{
    // get the size of the log
    GLint uiSize = 0;
    glGetProgramiv( m_uiID, GL_INFO_LOG_LENGTH, &uiSize );

    // get the log data
    char* pcData = new char[ uiSize + 1 ];
    glGetProgramInfoLog( m_uiID, uiSize + 1, nullptr, pcData );

    // return the log data
    DumbString oString( pcData );
    delete[] pcData;
    return oString;
}

// Is the program linked and not flagged for deletion?
bool ShaderProgram::IsValid() const
{
    if( 0 == m_uiID || GL_FALSE == glIsProgram( m_uiID ) )
    {
        return false;
    }
    GLint iLinked, iDeleted;
    glGetProgramiv( m_uiID, GL_LINK_STATUS, &iLinked );
    glGetProgramiv( m_uiID, GL_DELETE_STATUS, &iDeleted );
    return ( GL_TRUE == iLinked && GL_FALSE == iDeleted );
}
    
//
// Static functions
//

// get the shader program currently in use
const ShaderProgram& ShaderProgram::Current()
{
    GLint iID;
    glGetIntegerv( GL_CURRENT_PROGRAM, &iID );
    return 0 < sm_roLookup.count( (GLuint)iID ) ? *( sm_roLookup[ (GLuint)iID ] )
                                             : Null();
}

// destroy all shader programs
void ShaderProgram::DestroyAll()
{
    for each( ShaderProgram* poProgram in sm_roList )
    {
        if( nullptr != poProgram )
        {
            poProgram->Destroy();
        }
    }
}

// get a shader program representing no shader program
const ShaderProgram& ShaderProgram::Null()
{
    static ShaderProgram soNull;
    return soNull;
}

}   // namespace MyFirstEngine
