/******************************************************************************
 * File:               Quad.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 13, 2014
 * Description:        Class representing an untextured rectangle.
 * Last Modified:      March 12, 2014
 * Last Modification:  Debugging.
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
          const Rotation3D& ac_roRotation = Rotation3D::None() )
        : Drawable( ac_roColor, ac_roSize, ac_roPosition, ac_roRotation ) {}
    Quad( const Color::ColorVector& ac_roColor,
          const Point2D& ac_roSize,
          const Point3D& ac_roPosition,
          const Point3D& ac_roForward,
          const Point3D& ac_roUp = Point3D::Unit(2) )
        : Drawable( ac_roColor, ac_roSize, ac_roPosition,
                    Rotation3D( ac_roForward, ac_roUp ) ) {}
    Quad( const Color::ColorVector& ac_roColor,
          const Point3D& ac_roLowerLeftCorner,
          const Point3D& ac_roUpperRightCorner,
          const Point3D& ac_roForward = Point3D::Unit(0) )
        : Drawable( ac_roColor )
    {
        SetDimensions( ac_roLowerLeftCorner, ac_roUpperRightCorner, ac_roForward );
    }

    // Copy constructor/operator
    Quad( const Quad& ac_roQuad ) : Drawable( ac_roQuad ) {}
    Quad& operator=( const Quad& ac_roQuad )
    {
        Drawable::operator=( ac_roQuad );
        return *this;
    }

    // destructor is virtual, since Sprite inherits from Quad
    virtual ~Quad() {}

    Quad& SetDimensions( const Point3D& ac_roLowerLeftCorner,
                         const Point3D& ac_roUpperRightCorner,
                         const Point3D& ac_roForward = Point3D::Unit(0) )
    {
        // Set position
        Point3D oDiagonal = ac_roUpperRightCorner - ac_roLowerLeftCorner;
        m_oPosition = ( oDiagonal / 2 ) + ac_roLowerLeftCorner;

        // Choose forward vector
        Point3D oForward = ( Point3D::Zero() == ac_roForward
                             ? Point3D::Unit(0) : ac_roForward );

        // if forward vector isn't parallel to diagonal, use cross as up vector
        double dDot = oForward.Dot( oDiagonal );
        if( 0.0 != dDot )
        {
            m_oRotation.Set( oForward, oForward.Cross( oDiagonal ) );
        }
        // Otherwise, leave as default
        else if( Point3D::Unit(0) != oForward.Normalize() )
        {
            m_oRotation.Set( oForward );
        }

        // Calculate scale
        m_oScale = m_oRotation.Inverse().AppliedTo( ac_roUpperRightCorner ) -
                   m_oRotation.Inverse().AppliedTo( ac_roLowerLeftCorner );

        // Make sure model matrix gets calculated
        UpdateModelMatrix();
        return *this;
    }

protected:

    // Draw the four corners
    virtual void DrawComponents() const override
    {
        QuadShaderProgram::DrawQuad( m_oColor );
    }

};  // class Quad

}   // namespace MyFirstEngine

#endif
