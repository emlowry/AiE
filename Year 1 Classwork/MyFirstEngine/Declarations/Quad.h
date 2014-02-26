/******************************************************************************
 * File:               Quad.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 13, 2014
 * Description:        Class representing an untextured rectangle.
 * Last Modified:      February 25, 2014
 * Last Modification:  Implementation.
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

    // Public constructor
    Quad( const Point2D& ac_roSize = Point2D( 1.0 ),
          const Point3D& ac_roPosition = Point3D::Origin(),
          Color::Hex a_oColor = Color::WHITE );

    // destructor is virtual, since Sprite inherits from Quad
    virtual ~Quad() {}

    // Initialize the vertices that get reused every time and load the default
    // Quad shader program
    static void Initialize();

    static bool IsInitialized() { return 0 != sm_uiQuadVertexArrayID; }

    // get rid of the vertex data
    static void Terminate();

    // name of the default quad shader program
    static const char* const QUAD_SHADER_PROGRAM_NAME;

    // default quad shader source code files
    static const char* const QUAD_VERTEX_SHADER_FILE;
    static const char* const QUAD_FRAGMENT_SHADER_FILE;

protected:

    // Protected constructor for child classes that want to use their own shaders
    Quad( ShaderProgram* a_poProgram, Color::Hex a_oColor = Color::WHITE )
        : Drawable( a_oColor, a_poProgram ) {}

    // Draw the four corners
    virtual void DrawComponents() const override;

    // The positions of the four corners of an unscaled, unrotated Quad on the
    // XY plane.
    static const float QUAD_XY_VERTEX_DATA[8];
    static const unsigned int QUAD_ELEMENT_DATA[6];

    // The default Quad shader program
    static ShaderProgram sm_oQuadProgram;

    // Element buffer
    static GLuint sm_uiQuadElementBufferID;

    // Vertex buffer
    static GLuint sm_uiQuadVertexBufferID;

    // Vertex array
    static GLuint sm_uiQuadVertexArrayID;

    // Color uniform variable
    static GLint sm_iQuadColorID;

};  // class Quad

}   // namespace MyFirstEngine

#endif
