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

#include "../Declarations/GameEngine.h"
#include "../Declarations/GLFW.h"
#include "../Declarations/Shader.h"
#include "../Declarations/Singleton.h"
#include <unordered_map>
#include "../Declarations/MyFirstEngineMacros.h"

namespace MyFirstEngine
{

// store the loaded shaders
struct ShaderStorage : public Singleton< ShaderStorage >
{
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

// Get the default shader of the given type
INLINE Shader Shader::Default( GLenum a_eType )
{
    // TODO
}

// Destroy all shaders
INLINE void Shader::DestroyAll()
{
    //TODO
}

}   // namespace MyFirstEngine

#endif  // SHADER__INL
