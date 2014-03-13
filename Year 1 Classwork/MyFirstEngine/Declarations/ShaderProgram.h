/******************************************************************************
 * File:               ShaderProgram.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 13, 2014
 * Description:        Represents a GLSL shader program.
 * Last Modified:      March 12, 2014
 * Last Modification:  Refactoring.
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
class IMEXPORT_CLASS ShaderProgram
    : public NotCopyable, public MostDerivedAddress
{
public:

    // Constructor
    ShaderProgram( const Shader& ac_roVertexShader,
                   const Shader& ac_roFragmentShader = Shader::Null(),
                   const Shader& ac_roGeometryShader = Shader::Null() );
    ShaderProgram( const Shader* ac_paoShaders, unsigned int a_uiCount );

    // Destructor actually does something
    virtual ~ShaderProgram();

    // (In)Equality operators
    bool operator==( const ShaderProgram& ac_roProgram ) const
    { return ThisIs( ac_roProgram ); }
    bool operator!=( const ShaderProgram& ac_roProgram ) const
    { return ThisIsNot( ac_roProgram ); }

    // Start or stop using a given (or the current) shader program
    virtual void Use() const;
    static void Use( ShaderProgram& a_roProgram ) { a_roProgram.Use(); }
    static void Stop() { Null().Use(); }

    // Get shader program properties
    GLuint ID() const { return m_uiID; }

    // Get the first attached shader of a given type
    Shader GetShader( GLenum a_eType ) const;
    Shader VertexShader() const { return GetShader( GL_VERTEX_SHADER ); }
    Shader GeometryShader() const { return GetShader( GL_GEOMETRY_SHADER ); }
    Shader FragmentShader() const { return GetShader( GL_FRAGMENT_SHADER ); }

    // Get the info log
    DumbString GetLog() const;

    // Is the program linked and not flagged for deletion?
    static bool IsValid( const ShaderProgram& ac_roProgram )
    { return ac_roProgram.IsValid(); }
    bool IsValid() const;

    // get the shader program currently in use
    static const ShaderProgram& Current();

    // destroy all shader programs
    static void DestroyAll();

    // get a shader program representing no shader program
    static const ShaderProgram& Null();

protected:

    // Delete this shader program
    void Destroy();

    // Destroy vertex arrays, zero out IDs, etc.
    virtual void DestroyData() {}

    // Link, set up vertex arrays, etc.
    void Setup();

    // Set up vertex arrays, get uniform variable locations, etc.
    virtual void SetupData() {}

    // Bind vertex arrays, etc.
    virtual void UseData() const {}

    // ID of the GL shader program
    GLuint m_uiID;

private:

    // PIMPLE idiom - this class is only defined in the cpp, so inheritance
    // from an stl container won't result in warnings.
    class ShaderList;

    // Default constructor used only by Null()
    ShaderProgram();

    // Get a reference to the list of shaders
    ShaderList& Shaders() { return *m_poShaders; }
    const ShaderList& Shaders() const { return *m_poShaders; }

    unsigned int m_uiIndex; // location of shader program in list
    ShaderList* m_poShaders; // owned by this object

};  // class ShaderProgram

}   // namespace MyFirstEngine

#endif  // SHADER_PROGRAM__H
