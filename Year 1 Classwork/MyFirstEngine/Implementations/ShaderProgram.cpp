/******************************************************************************
 * File:               ShaderProgram.hcpp
 * Author:             Elizabeth Lowry
 * Date Created:       February 24, 2014
 * Description:        Function implementations for the ShaderProgram class.
 * Last Modified:      February 24, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#include "../Declarations/GLFW.h"
#include "../Declarations/Shader.h"
#include "../Declarations/ShaderProgram.h"
#include "MathLibrary.h"
#include <unordered_map>
#include <list>

namespace MyFirstEngine
{

using namespace Utility;

// declare classes instead of typedefs to avoid compiler warnings
// definition is only in cpp
class ShaderProgram::ProgramList
    : public std::unordered_map< DumbString, GLuint >
{
public:
    typedef std::unordered_map< DumbString, GLuint > BaseType;
    typedef BaseType::value_type ValueType;
};

// store all the programs that have been linked already
ShaderProgram::ProgramList*
    ShaderProgram::sm_poList = new ShaderProgram::ProgramList();

// Constructor
ShaderProgram::ShaderProgram( const char* ac_pcProgramName,
                              const Shader& ac_roVertexShader,
                              const Shader& ac_roFragmentShader,
                              bool a_bRelink )
{
    DumbString oProgramName( ac_pcProgramName );

    // If the program already exists, use the existing ID.
    if( "" == oProgramName || 0 < List().count( ac_pcProgramName ) )
    {
        m_uiID = ( "" == oProgramName ? Default().m_uiID : List()[ oProgramName ] );

        // If relink flag is true, link to new shaders
        if( a_bRelink )
        {
            Link( m_uiID, ac_roVertexShader, ac_roFragmentShader );
        }
    }

    // If the program hasn't been linked before, do so
    else
    {
        m_uiID = Link( ac_roVertexShader, ac_roFragmentShader );
        List()[ oProgramName ] = m_uiID;
    }
}

// Start using this shader program
void ShaderProgram::Use()
{
    Setup();
    glUseProgram( m_uiID );
}

// Get the shaders used by this program
std::list< GLuint > ShaderProgram::ShaderIDs( GLuint a_uiID )
{
    // Get the number of attached shaders
    GLint iMaxCount;
    glGetProgramiv( a_uiID, GL_ATTACHED_SHADERS, &iMaxCount );

    // Get the IDs of the attached shaders
    GLsizei iCount;
    GLuint* auiShaderIDs = new GLuint[ iMaxCount ];
    glGetAttachedShaders( a_uiID, iMaxCount, &iCount, auiShaderIDs );

    // Add the IDs to a list
    std::list< GLuint > oResult;
    for( int i = 0; i < iCount; ++i )
    {
        oResult.push_back( auiShaderIDs[ i ] );
    }
    delete[] auiShaderIDs;
    return oResult;
}
Shader ShaderProgram::GetShader( GLenum a_eType ) const
{
    for each( GLuint uiID in ShaderIDs() )
    {
        Shader oShader( uiID );
        if( oShader.Type() == a_eType )
        {
            return oShader;
        }
    }
    return Shader::Null();
}

//
// Static functions
//

// get the shader program currently in use
ShaderProgram ShaderProgram::Current()
{
    GLint iID;
    glGetIntegerv( GL_CURRENT_PROGRAM, &iID );
    return ShaderProgram( (GLuint)iID );
}

// get the default shader program
ShaderProgram ShaderProgram::Default()
{
    // if the default program has already been compiled, return it
    if( List().count( "" ) > 0 )
    {
        return ShaderProgram( List()[ "" ] );
    }

    // otherwise, link a program with no attached shaders
    List()[ "" ] = Link( Shader::Null(), Shader::Null() );
    return List()[ "" ];
}

// destroy all shader programs
void ShaderProgram::DestroyAll()
{
    for each( ProgramList::ValueType oPair in List() )
    {
        glDeleteProgram( oPair.second );
    }
    List().clear();
}
    
// Link the fragment shader and vertex shader into a program
GLuint ShaderProgram::Link( const Shader& ac_roVertexShader,
                            const Shader& ac_roFragmentShader )
{
    GLuint uiID = glCreateProgram();
    Link( uiID, ac_roVertexShader, ac_roFragmentShader );
    return uiID;
}
GLuint ShaderProgram::Link( GLuint a_uiID,
                            const Shader& ac_roVertexShader,
                            const Shader& ac_roFragmentShader )
{
    // Clear previously-attached shaders
    for each( GLuint uiID in ShaderIDs( a_uiID ) )
    {
        glDetachShader( a_uiID, uiID );
    }

    // Attach shaders
    if( Shader::Null() != ac_roVertexShader )
    {
        glAttachShader( a_uiID, ac_roVertexShader.ID() );
    }
    if( Shader::Null() != ac_roFragmentShader )
    {
        glAttachShader( a_uiID, ac_roFragmentShader.ID() );
    }

    // link
    glLinkProgram( a_uiID );
    return a_uiID;
}

// get a shader program representing no shader program
const ShaderProgram& ShaderProgram::Null()
{
    static ShaderProgram soNull( (GLuint)0 );
    return soNull;
}

}   // namespace MyFirstEngine
