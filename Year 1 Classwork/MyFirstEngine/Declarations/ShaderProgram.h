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

#include "Shader.h"

namespace MyFirstEngine
{

// Loads, compiles, and links a GLSL shader program and provides functions for
// calling upon the resulting shader program
class ShaderProgram
{
public:

    // null string means use default shader
    ShaderProgram( const char* ac_pcVertexShader = nullptr,
                   const char* ac_pcFragmentShader = nullptr );
    ShaderProgram( const char* ac_pcVertexShader, 
    

    // Start or stop using a given (or the current) shader program
    virtual void Use();
    static void Use( ShaderProgram& a_roProgram ) { a_roProgram.Use(); }
    static void StopUsing();

};  // class ShaderProgram

}   // namespace MyFirstEngine

#endif  // SHADER_PROGRAM__H
