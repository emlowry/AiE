/******************************************************************************
 * File:               ShaderProgram.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 13, 2014
 * Description:        Represents a GLSL shader program.
 * Last Modified:      February 13, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef SHADER_PROGRAM__H
#define SHADER_PROGRAM__H

#include "GLFW.h"
#include "Shader.h"

namespace MyFirstEngine
{

// Loads, compiles, and links a GLSL shader program and provides functions for
// calling upon the resulting shader program
class ShaderProgram
{
public:

    // Constructor
    ShaderProgram( const char* ac_pcProgramName = nullptr,
                   const Shader& ac_roVertexShader
                                          = Shader::Default( GL_VERTEX_SHADER ),
                   const Shader& ac_roFragmentShader
                                      = Shader::Default( GL_FRAGMENT_SHADER ) );

    // Destructor is virtual - this should be used as a base class, with derived
    // classes passing specific shaders back to the base constructor and
    // providing their own functions for setting uniform variables
    virtual ~ShaderProgram() {}

    // Start or stop using a given (or the current) shader program
    virtual void Use();
    static void Use( ShaderProgram& a_roProgram ) { a_roProgram.Use(); }
    static void StopUsing();

    // destroy all shader programs
    static void DestroyAll();

private:

    // PIMPLE idiom - this class is only defined in the cpp, so inheritance from
    // an stl container won't result in warnings.
    class ProgramList;

    // Link the fragment shader and vertex shader into a program
    static GLuint Link( const Shader& ac_roVertexShader,
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
