/******************************************************************************
 * File:               Quad.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 13, 2014
 * Description:        Class representing an untextured rectangle.
 * Last Modified:      February 24, 2014
 * Last Modification:  Actually adding a class definition.
 ******************************************************************************/

#ifndef QUAD__H
#define QUAD__H

#include "Drawable.h"
#include "MathLibrary.h"
#include "ShaderProgram.h"
#include "MyFirstEngineMacros.h"

namespace MyFirstEngine
{

class IMEXPORT_CLASS Quad : public Drawable
{
public:

    Quad( const Point2D& ac_roSize = Point2D( 1.0 ),
          const Point3D& ac_roPosition = Point3D::Origin(),
          Color::Hex a_oColor = Color::WHITE );

    // destructor is virtual, since Sprite inherits from Quad
    virtual ~Quad() {}

    // Initialize the vertices that get reused every time and load the default
    // Quad shader program
    static void Initialize();

    static bool IsInitialized() { return 0 == sm_uiVertexBufferID; }

    // get rid of the vertex data
    static void Terminate();

    // name of the default quad shader program
    static const char* const QUAD_SHADER_PROGRAM_NAME;

    // default quad shader source code
    static const char* const QUAD_VERTEX_SHADER_SOURCE;
    static const char* const QUAD_FRAGMENT_SHADER_SOURCE;

protected:

    // For child classes that want to use their own shaders
    Quad( ShaderProgram* a_poProgram, Color::Hex a_oColor = Color::WHITE )
        : Drawable( a_oColor, a_poProgram ) {}

    // Draw the four corners
    virtual void DrawComponents() const override;

    // Set the uniform value for color
    virtual void Setup() const override;

    // The positions of the four corners of an unscaled, unrotated Quad on the
    // XY plane.
    static const float QUAD_XY_VERTEX_DATA[8];

    // The default Quad shader program
    static ShaderProgram sm_oQuadProgram;

    // Vertex buffer
    static GLuint sm_uiVertexBufferID;

};  // class Quad

}   // namespace MyFirstEngine

#endif
