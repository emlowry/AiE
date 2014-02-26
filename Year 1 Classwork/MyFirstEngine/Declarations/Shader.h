/******************************************************************************
 * File:               Shader.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 13, 2014
 * Description:        Represents a GLSL shader.
 * Last Modified:      February 25, 2014
 * Last Modification:  Added deletion and reverse lookup.
 ******************************************************************************/

#ifndef SHADER__H
#define SHADER__H

#include "GLFW.h"
#include "MathLibrary.h"
#include <functional>   // for hash
#include <unordered_map>
#include "MyFirstEngineMacros.h"

namespace MyFirstEngine
{

using namespace Utility;

// Loads, compiles, and links a GLSL shader program and provides functions for
// calling upon the resulting shader program
class IMEXPORT_CLASS Shader : public Hashable, public Comparable< Shader >
{
public:

    // Default constructor
    Shader() : m_uiID( 0 ) {}
    
    // Copy constructor
    Shader( const Shader& ac_roShader ) : m_uiID( ac_roShader.m_uiID ) {}

    // Just use the ID of an existing shader
    Shader( GLuint a_uiID ) : m_uiID( a_uiID ) {}

    // If source name is null or empty, use default shader
    // If source name hasn't been loaded yet, do so and compile a new shader
    Shader( GLenum a_eType, const char* ac_pcSourceName,
            bool a_bRecompile = false );

    // If source text is null or empty, behave like the previous constructor
    // Otherwise, if source hasn't already been loaded, do so and compile
    // Otherotherwise, if recompile flag is false, just use already-compiled
    // shader, while if flag is true, replace stored source and recompile shader
    Shader( GLenum a_eType, const char* ac_pcSourceName,
            const char* ac_pcSourceText, bool a_bRecompile = false );

    // Delete the shader
    void Delete();

    // Is this shader compiled and not marked for deletion?
    static bool IsValid( GLuint a_uiID );
    bool IsValid() const { return IsValid( m_uiID ); }

    // Get shader properties
    int Compare( const Shader& ac_roShader ) const
    { return SimpleCompare( m_uiID, ac_roShader.m_uiID ); }
    std::size_t Hash() const { return std::hash< GLuint >()( m_uiID ); }
    GLuint ID() const { return m_uiID; }
    GLenum Type() const;

    // Get the info log
    DumbString GetLog() const;

    // check to see if shaders are the same
    bool operator==( const Shader& ac_roShader ) const
    { return m_uiID == ac_roShader.m_uiID; }
    bool operator==( GLuint a_uiID ) const { return m_uiID == a_uiID; }
    bool operator!=( const Shader& ac_roShader ) const
    { return m_uiID != ac_roShader.m_uiID; }
    bool operator!=( GLuint a_uiID ) const { return m_uiID != a_uiID; }

    // Get the default shader of the given type
    static Shader Default( GLenum a_eType );

    // Destroy all shaders
    static void DestroyAll();

    // Shader meaning no shader
    static const Shader& Null();

    // Source code for default shaders
    static const char* const DEFAULT_FRAGMENT_SHADER_SOURCE_CODE;
    static const char* const DEFAULT_VERTEX_SHADER_SOURCE_CODE;

private:

    // PIMPLE idiom - this class is only defined in the cpp, so inheritance from
    // an stl container won't result in warnings.
    class ShaderLookup;
    class SourceNameLookup;

    // Compile a shader from the given source code
    static GLuint CompileShader( GLenum a_eType, const char* ac_pcSourceText );
    static GLuint CompileShader( const char* ac_pcSourceText, GLuint a_uiID );

    // Get a reference to the lookup map
    static ShaderLookup& Lookup() { return *sm_poLookup; }
    static SourceNameLookup& SourceLookup() { return *sm_poSourceLookup; }

    // ID associated with the GLSL shader object
    GLuint m_uiID;
    
    // store all the compiled shaders
    static ShaderLookup* sm_poLookup;
    static SourceNameLookup* sm_poSourceLookup;

};  // class Shader

}   // namespace MyFirstEngine

#ifdef INLINE_IMPLEMENTATION
#include "../Implementations/Shader.inl"
#endif

#endif  // SHADER__H
