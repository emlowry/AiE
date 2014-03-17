/******************************************************************************
 * File:               QuadShaderProgram.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 26, 2014
 * Description:        Shader program for Quad objects.
 * Last Modified:      February 27, 2014
 * Last Modification:  Overriding virtual functions added to parent class.
 ******************************************************************************/

#ifndef QUAD_SHADER_PROGRAM__H
#define QUAD_SHADER_PROGRAM__H

#include "MathLibrary.h"
#include "ShaderProgram.h"
#include "MyFirstEngineMacros.h"

namespace MyFirstEngine
{

using namespace Utility;

// Default Quad shader program
class IMEXPORT_CLASS QuadShaderProgram
    : public ShaderProgram, public InitializeableSingleton< QuadShaderProgram >
{
    friend class InitializeableSingleton< QuadShaderProgram >;

public:

    // virtual destructor present due to inheritance
    virtual ~QuadShaderProgram() {}

    // For use by other shader programs that want to reuse this one's vertex
    // data
    static void BindVertexBuffer( const ShaderProgram& ac_roProgram,
                                  const char* ac_pcPositionAttributeName );

    // For use by other shader programs that want to reuse this one's element
    // buffer
    static void BindElementBuffer();

    // For use by other shader programs that reuse this one's elements
    static void DrawElements();

    // Draw a solid-color 1x1 quad at the origin of the XY plane (in model space)
    static void DrawQuad( const Color::ColorVector& ac_roColor );

    // default quad shader source code files
    static const char* const QUAD_VERTEX_SHADER_FILE;
    static const char* const QUAD_FRAGMENT_SHADER_FILE;

    // The positions of the four corners of an unscaled, unrotated Quad on the
    // XY plane.
    static const float QUAD_XY_VERTEX_DATA[8];
    static const unsigned int QUAD_ELEMENT_DATA[4];

protected:

    // only the parent class's Initialize function can call this.
    QuadShaderProgram();

    // Instance initialization/termination calls Setup()/Destroy() before
    // constructor/destructor
    virtual void InitializeInstance() override { Setup(); }
    virtual void TerminateInstance() override { Destroy(); }

    // manage the buffers, vertex array, and color uniform variable
    virtual void DestroyData() override;
    virtual void SetupData() override;
    virtual void UseData() const override;

    // Uniform variable locations
    GLint m_iModelViewProjectionID;
    GLint m_iColorID;

    // Element buffer
    GLuint m_uiElementBufferID;

    // Vertex array
    GLuint m_uiVertexArrayID;

    // Vertex buffer
    GLuint m_uiVertexBufferID;

};   // class QuadShaderProgram

}   // namespace MyFirstEngine

#endif  // QUAD_SHADER_PROGRAM__H
