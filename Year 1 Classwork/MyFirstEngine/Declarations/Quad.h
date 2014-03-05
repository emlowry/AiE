/******************************************************************************
 * File:               Quad.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 13, 2014
 * Description:        Class representing an untextured rectangle.
 * Last Modified:      March 5, 2014
 * Last Modification:  Adding function for setting dimensions based on corners.
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
        : Drawable( &( QuadShaderProgram::Instance() ),
                    ac_roColor, ac_roSize, ac_roPosition, ac_roRotation ) {}
    Quad( const Quad& ac_roQuad ) : Drawable( ac_roQuad ) {}
    Quad& operator=( const Quad& ac_roQuad )
    {
        Drawable::operator=( ac_roQuad );
        return *this;
    }
    Quad( const Color::ColorVector& ac_roColor,
          const Point3D& ac_roLowerLeftCorner,
          const Point3D& ac_roUpperRightCorner,
          const Point3D& ac_roForward = Point3D::Unit(0) )
        : Drawable( &( QuadShaderProgram::Instance() ), ac_roColor )
    {
        SetDimensions( ac_roLowerLeftCorner, ac_roUpperRightCorner, ac_roForward );
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

    // Protected constructor for child classes that want to use their own shaders
    Quad( ShaderProgram* a_poProgram,
          const Color::ColorVector& ac_roColor = Color::WHITE,
          const Point2D& ac_roSize = Point2D( 1.0 ),
          const Point3D& ac_roPosition = Point3D::Origin(),
          const Rotation3D& ac_roRotation = Rotation3D::None() )
        : Drawable( a_poProgram, ac_roColor, ac_roSize,
                    ac_roPosition, ac_roRotation ) {}
    Quad( ShaderProgram* a_poProgram,
          const Color::ColorVector& ac_roColor,
          const Point3D& ac_roLowerLeftCorner,
          const Point3D& ac_roUpperRightCorner,
          const Point3D& ac_roForward = Point3D::Unit(0) )
        : Drawable( a_poProgram, ac_roColor )
    {
        SetDimensions( ac_roLowerLeftCorner, ac_roUpperRightCorner, ac_roForward );
    }

    // Draw the four corners
    virtual void DrawComponents() const override
    {
        QuadShaderProgram::DrawQuad( m_oColor );
    }

};  // class Quad

}   // namespace MyFirstEngine

#endif
