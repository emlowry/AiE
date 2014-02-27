/******************************************************************************
 * File:               Drawable.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 24, 2014
 * Description:        Base class for drawable objects.
 * Last Modified:      February 26, 2014
 * Last Modification:  Changed how transforms are assembled.
 ******************************************************************************/

#ifndef DRAWABLE__H
#define DRAWABLE__H

#include "MathLibrary.h"
#include "ShaderProgram.h"
#include "MyFirstEngineMacros.h"

namespace MyFirstEngine
{

// represents an object that can be drawn on the screen
class IMEXPORT_CLASS Drawable
{
public:

    // The drawable object DOES NOT own the shader object passed in.  A pointer
    // is passed in to distinguish between using whatever shader program is
    // current (indicated by a null pointer) or using no shader program
    // (indicated by a pointer to a program equal to ShaderProgram::Null() )
    Drawable( ShaderProgram* a_poProgram = nullptr,
              const Color::ColorVector& ac_roColor = Color::WHITE,
              const Point2D& ac_roSize = Point2D( 1.0 ),
              const Point3D& ac_roPosition = Point3D::Origin(),
              double a_dYaw = 0.0, double a_dPitch = 0.0, double a_dRoll = 0.0 );
    virtual ~Drawable() {}

    // Draw the object to the screen
    void Draw() const;

    // Add/Get/Set color
    const Color::ColorVector& GetColor() const { return m_oColor; }
    Drawable& SetColor( const Color::ColorVector& ac_roColor )
    { m_oColor = ac_roColor; return *this; }

    // Add/Get/Set rotation properties
    Drawable& AddPitch( double a_dPitch )
    { m_dPitch += a_dPitch; return *this; }
    double GetPitch() const { return m_dPitch; }
    Drawable& SetPitch( double a_dPitch = 0.0 )
    { m_dPitch = a_dPitch; return *this; }
    Drawable& AddRoll( double a_dRoll ) { m_dRoll += a_dRoll; return *this; }
    double GetRoll() const { return m_dRoll; }
    Drawable& SetRoll( double a_dRoll = 0.0 )
    { m_dRoll = a_dRoll; return *this; }
    Drawable& AddYaw( double a_dYaw ) { m_dYaw += a_dYaw; return *this; }
    double GetYaw() const { return m_dYaw; }
    Drawable& SetYaw( double a_dYaw = 0.0 ) { m_dYaw = a_dYaw; return *this; }

    // Add/Get/Set Position and Scale
    Drawable& AddPosition( const Point3D& ac_roPosition )
    { m_oPosition += ac_roPosition; return *this; }
    const Point3D& GetPosition() const { return m_oPosition; }
    Drawable& SetPosition( const Point3D& ac_roPosition = Point3D::Origin() )
    { m_oPosition = ac_roPosition; return *this; }
    Drawable& AddScale( const Point3D& ac_roScale )
    { m_oScale += ac_roScale; return *this; }
    const Point3D& GetScale() const { return m_oScale; }
    Drawable& SetScale( const Point3D& ac_roScale = Point3D( 1.0 ) )
    { m_oScale = ac_roScale; return *this; }

    // Apply/Get/Set additional transformation
    Drawable& ApplyAfterTransformation( const Transform3D& ac_roTransform )
    { m_oAfterTransform *= ac_roTransform; return *this; }
    const Transform3D& GetAfterTransformation() const
    { return m_oAfterTransform; }
    Drawable& SetAfterTransformation(
        const Transform3D& ac_roTransform = Transform3D::Identity() )
    { m_oAfterTransform = ac_roTransform; return *this; }
    Drawable& ApplyBeforeTransformation( const Transform3D& ac_roTransform )
    { m_oBeforeTransform *= ac_roTransform; return *this; }
    const Transform3D& GetBeforeTransformation() const
    { return m_oBeforeTransform; }
    Drawable& SetBeforeTransformation(
        const Transform3D& ac_roTransform = Transform3D::Identity() )
    { m_oBeforeTransform = ac_roTransform; return *this; }

    // Show/Hide
    bool IsVisible() const { return m_bVisible; }
    Drawable& Show() { m_bVisible = true; return *this; }
    Drawable& Hide() { m_bVisible = false; return *this; }
    Drawable& SetVisible( bool a_bVisible ) { m_bVisible = a_bVisible; return *this; }

protected:

    // Apply transformations for this object to the current matrix.  Assumes
    // points are row vectors, so make sure to transpose if the points to
    // transform are column vectors.
    void ApplyTransforms() const;

    // This is where the actual work of drawing the object, whatever it is,
    // takes place.
    virtual void DrawComponents() const = 0;

    // Default color for everything
    Color::ColorVector m_oColor;

    // Basic scale/position/rotation
    double m_dYaw;  // first rotation, about world z-axis
    double m_dPitch;    // second rotation, about model y-axis
    double m_dRoll; // third rotation, about model x-axis
    Point3D m_oPosition;    // applied after rotation
    Point3D m_oScale;   // applied before rotation

    // Additional transformations applied to vertices after the transformations
    // due to the above properties
    Transform3D m_oAfterTransform;

    // Additional transformations applied to vertices before the transformations
    // due to the above properties
    Transform3D m_oBeforeTransform;

    // Shader program to use - if null, use whatever program is current
    ShaderProgram* m_poProgram;

    // Is this object even visible?
    bool m_bVisible;

};  // class Drawable

}   // namespace MyFirstEngine

#endif  // DRAWABLE__H
