/******************************************************************************
 * File:               Drawable.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 24, 2014
 * Description:        Base class for drawable objects.
 * Last Modified:      February 27, 2014
 * Last Modification:  Refactoring and debugging.
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
              const Point3D& ac_roScale = Point3D( 1.0 ),
              const Point3D& ac_roPosition = Point3D::Origin(),
              double a_dYaw = 0.0, double a_dPitch = 0.0, double a_dRoll = 0.0 );
    Drawable( const Drawable& ac_roObject );
    Drawable& operator=( const Drawable& ac_roObject );

    // Destructor deallocates the dynamically stored modelview transform cache
    // and flag.
    virtual ~Drawable();

    // Draw the object to the screen
    void Draw() const;

    // Get properties
    const Color::ColorVector& GetColor() const { return m_oColor; }
    double GetPitch() const { return m_dPitch; }
    double GetRoll() const { return m_dRoll; }
    double GetYaw() const { return m_dYaw; }
    const Point3D& GetPosition() const { return m_oPosition; }
    const Point3D& GetScale() const { return m_oScale; }
    const Transform3D& GetAfterTransform() const
    { return m_oAfterTransform; }
    const Transform3D& GetBeforeTransform() const
    { return m_oBeforeTransform; }
    bool IsVisible() const { return m_bVisible; }

    // Get the cached model view transformation resulting from this object's
    // scale/rotation/position/etc.  If any of those properties have changed
    // since the last time said transformation was calculated, recalculate it.
    virtual const Transform3D& ModelView() const;

    // Set color
    Drawable& SetColor( const Color::ColorVector& ac_roColor );
    Drawable& SetColor( float a_fRed, float a_fGreen, float a_fBlue,
                        float a_fAlpha = 1.0f );
    Drawable& SetColor( Color::Channel a_ucRed,
                        Color::Channel a_ucGreen,
                        Color::Channel a_ucBlue,
                        Color::Channel a_ucAlpha = 0xFF );

    // Add rotation
    Drawable& AddPitch( double a_dPitch );
    Drawable& AddRoll( double a_dRoll );
    Drawable& AddYaw( double a_dYaw );
    Drawable& AddRotation( double a_dYaw,
                           double a_dPitch = 0.0,
                           double a_dRoll = 0.0 );

    // Set rotation
    Drawable& SetPitch( double a_dPitch = 0.0 );
    Drawable& SetRoll( double a_dRoll = 0.0 );
    Drawable& SetYaw( double a_dYaw = 0.0 );
    Drawable& SetRotation( double a_dYaw = 0.0,
                           double a_dPitch = 0.0,
                           double a_dRoll = 0.0 );

    // Add position and scale
    Drawable& AddPosition( const Point3D& ac_roPosition );
    Drawable& AddPosition( double a_dX, double a_dY = 0.0, double a_dZ = 0.0 );
    Drawable& AddScale( const Point3D& ac_roScale );
    Drawable& AddScale( double a_dFactor );
    Drawable& AddScale( double a_dX, double a_dY, double a_dZ = 0.0 );

    // Set position and scale
    Drawable& SetPosition( const Point3D& ac_roPosition = Point3D::Origin() );
    Drawable& SetPosition( double a_dX, double a_dY = 0.0, double a_dZ = 0.0 );
    Drawable& SetScale( const Point3D& ac_roScale = Point3D( 1.0 ) );
    Drawable& SetScale( double a_dFactor );
    Drawable& SetScale( double a_dX, double a_dY, double a_dZ = 0.0 );

    // Apply/Set additional transformation
    Drawable& ApplyAfterTransform( const Transform3D& ac_roTransform );
    Drawable& SetAfterTransform(
        const Transform3D& ac_roTransform = Transform3D::Identity() );
    Drawable& ApplyBeforeTransform( const Transform3D& ac_roTransform );
    Drawable& SetBeforeTransform(
        const Transform3D& ac_roTransform = Transform3D::Identity() );

    // Show/Hide
    Drawable& Show();
    Drawable& Hide();
    Drawable& SetVisible( bool a_bVisible );

    // set a flag indicating that the cached modelview matrix for this object
    // should be recalculated
    void UpdateModelView() { *m_pbUpdateModelView = true; }

protected:

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

    // Cache the complete transformation for cases when it doesn't change.
    // When it does change, set a flag indicating that the cached matrix should
    // be recalculated.  These are pointers to values instead of actual values
    // as a cheat that lets them be updated even in const functions.
    bool* m_pbUpdateModelView;
    Transform3D* m_poModelView;

};  // class Drawable

}   // namespace MyFirstEngine

#endif  // DRAWABLE__H
