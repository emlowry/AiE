/******************************************************************************
 * File:               Shader.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 13, 2014
 * Description:        Represents a GLSL shader.
 * Last Modified:      February 13, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef SHADER__H
#define SHADER__H

#include "DumbString.h"
#include "GLFW.h"
#include <unordered_map>
#include "MyFirstEngineMacros.h"

namespace MyFirstEngine
{

// Loads, compiles, and links a GLSL shader program and provides functions for
// calling upon the resulting shader program
class IMEXPORT_CLASS Shader
{
public:

    // Copy constructor
    Shader( const Shader& ac_roShader );
    Shader& operator=( const Shader& ac_roShader );

    // If source name is null or empty, use default shader
    // If source name hasn't been loaded yet, do so and compile a new shader
    Shader( GLenum a_eType, const char* ac_pcSourceName = nullptr );

    // If source text is null or empty, behave like the previous constructor
    // Otherwise, if source hasn't already been loaded, do so and compile
    // Otherotherwise, if recompile flag is false, just use already-compiled
    // shader, while if flag is true, replace stored source and recompile shader
    Shader( GLenum a_eType, const char* ac_pcSourceName = nullptr,
            const char* ac_pcSourceText = nullptr, bool a_bRecompile = false );

    // just use the ID of an existing shader
    Shader( GLuint a_eID );

    // Is this shader compiled and not marked for deletion?
    static bool IsValid( GLuint a_uiID );
    bool IsValid() const;

    // Get shader properties
    GLenum Type() const;
    GLuint ID() const;

    // Get the default shader of the given type
    static Shader Default( GLenum a_eType );

    // Destroy all shaders
    static void DestroyAll();

private:

    // source code for default shaders
    static const DumbString& DefaultFragmentShaderSource();
    static const DumbString& DefaultVertexShaderSource();

    // load source code
    static DumbString LoadSource( const char* ac_pcFileName );

    // Shader type
    GLenum m_eType;

    // ID associated with the GLSL shader object
    GLuint m_uiID;

};  // class Shader

}   // namespace MyFirstEngine

#ifdef INLINE_IMPLEMENTATION
#include "../Implementations/Shader.inl"
#endif

#endif  // SHADER__H
