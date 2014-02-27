/******************************************************************************
 * File:               Quad.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 13, 2014
 * Description:        Class representing an untextured rectangle.
 * Last Modified:      February 26, 2014
 * Last Modification:  Separating out shader code.
 ******************************************************************************/

#ifndef QUAD__H
#define QUAD__H

#include "Drawable.h"
#include "MathLibrary.h"
#include "QuadShaderProgram.h"
#include "ShaderProgram.h"
#include "MyFirstEngineMacros.h"

namespace MyFirstEngine
{

class IMEXPORT_CLASS Quad : public Drawable
{
public:

    // Public constructor
    Quad( const Color::ColorVector& ac_roColor = Color::WHITE,
          const Point2D& ac_roSize = Point2D( 1.0 ),
          const Point3D& ac_roPosition = Point3D::Origin(),
          double a_dYaw = 0.0, double a_dPitch = 0.0, double a_dRoll = 0.0 )
        : Drawable( &( QuadShaderProgram::Instance() ),
                    ac_roColor, ac_roSize, ac_roPosition,
                    a_dYaw, a_dPitch, a_dRoll ) {}

    // destructor is virtual, since Sprite inherits from Quad
    virtual ~Quad() {}

protected:

    // Protected constructor for child classes that want to use their own shaders
    Quad( ShaderProgram* a_poProgram,
          const Color::ColorVector& ac_roColor = Color::WHITE,
          const Point2D& ac_roSize = Point2D( 1.0 ),
          const Point3D& ac_roPosition = Point3D::Origin(),
          double a_dYaw = 0.0, double a_dPitch = 0.0, double a_dRoll = 0.0 )
        : Drawable( a_poProgram, ac_roColor, ac_roSize, ac_roPosition,
                    a_dYaw, a_dPitch, a_dRoll ) {}

    // Draw the four corners
    virtual void DrawComponents() const override
    {
        QuadShaderProgram::DrawQuad( m_oColor );
    }

};  // class Quad

}   // namespace MyFirstEngine

#endif
