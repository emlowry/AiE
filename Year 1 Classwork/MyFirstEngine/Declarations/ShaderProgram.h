/******************************************************************************
 * File:               ShaderProgram.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 13, 2014
 * Description:        Represents a GLSL shader program.
 * Last Modified:      February 24, 2014
 * Last Modification:  Moved base classes to Utility namespace in MathLibrary.
 ******************************************************************************/

#ifndef SHADER_PROGRAM__H
#define SHADER_PROGRAM__H

#include "GLFW.h"
#include "MathLibrary.h"
#include "Shader.h"
#include <list>

#include "MyFirstEngineMacros.h"

namespace MyFirstEngine
{

using namespace Utility;

// Loads, compiles, and links a GLSL shader program and provides functions for
// calling upon the resulting shader program
class IMEXPORT_CLASS ShaderProgram : public Hashable, public Comparable< ShaderProgram >
{
public:

    // Default constructor
    ShaderProgram() : m_uiID( 0 ) {}

    // Copy constructor
    ShaderProgram( const ShaderProgram& ac_roProgram )
         : m_uiID( ac_roProgram.m_uiID ) {}

    // Just use the ID of an existing program
    ShaderProgram( GLuint a_uiID ) : m_uiID( a_uiID ) {}

    // Constructor
    ShaderProgram( const char* ac_pcProgramName,
                   const Shader& ac_roVertexShader = Shader::Null(),
                   const Shader& ac_roFragmentShader = Shader::Null(),
                   bool a_bRelink = false );

    // Destructor is virtual - this should be used as a base class, with derived
    // classes passing specific shaders back to the base constructor and
    // providing their own functions for setting uniform variables
    virtual ~ShaderProgram() {}

    // Start or stop using a given (or the current) shader program
    void Use();
    static void Use( ShaderProgram& a_roProgram ) { a_roProgram.Use(); }
    static void StopUsing() { ShaderProgram( Null() ).Use(); }

    // Perform sany neccesary setup tasks before starting to use this program.
    // Default behavior is to do nothing - redefine in child classes to set
    // uniform variables and such.
    virtual void Setup() {}

    // Get shader program properties
    int Compare( const ShaderProgram& ac_roProgram ) const
    { return SimpleCompare( m_uiID, ac_roProgram.m_uiID ); }
    std::size_t Hash() const { return std::hash< GLuint >()( m_uiID ); }
    GLuint ID() const { return m_uiID; }
    Shader VertexShader() const { return GetShader( GL_VERTEX_SHADER ); }
    Shader FragmentShader() const { return GetShader( GL_FRAGMENT_SHADER ); }

    // get the shader program currently in use
    static ShaderProgram Current();

    // get the default shader program
    static ShaderProgram Default();

    // destroy all shader programs
    static void DestroyAll();

    // get a shader program representing no shader program
    static const ShaderProgram& Null();

private:

    // PIMPLE idiom - this class is only defined in the cpp, so inheritance from
    // an stl container won't result in warnings.
    class ProgramList;

    // Get a list of all attached shaders
    std::list< GLuint > ShaderIDs() const { return ShaderIDs( m_uiID ); }
    static std::list< GLuint > ShaderIDs( GLuint a_uiID );

    // Get the first attached shader of a given type
    Shader GetShader( GLenum a_eType ) const;

    // Link the fragment shader and vertex shader into a program
    static GLuint Link( const Shader& ac_roVertexShader,
                        const Shader& ac_roFragmentShader );
    static GLuint Link( GLuint a_uiID,
                        const Shader& ac_roVertexShader,
                        const Shader& ac_roFragmentShader );

    // Get a reference to the map of already-linked programs
    static ProgramList& List() { return *sm_poList; }

    GLuint m_uiID;  // ID of the GL shader program
    Shader m_oFragmentShader;
    Shader m_oVertexShader;

    // store all the programs that have been linked already
    static ProgramList* sm_poList;

};  // class ShaderProgram

}   // namespace MyFirstEngine

#endif  // SHADER_PROGRAM__H
