/******************************************************************************
 * File:               Drawable.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 24, 2014
 * Description:        Base class for drawable objects.
 * Last Modified:      March 12, 2014
 * Last Modification:  Debugging.
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
    Drawable( const Color::ColorVector& ac_roColor = Color::WHITE,
              const Point3D& ac_roScale = Point3D( 1.0 ),
              const Point3D& ac_roPosition = Point3D::Origin(),
              const Rotation3D& ac_roRotation = Rotation3D::None() );
    Drawable( const Drawable& ac_roObject );
    Drawable& operator=( const Drawable& ac_roObject );

    // Destructor deallocates the dynamically stored modelview transform cache
    // and flag.
    virtual ~Drawable();

    // Draw the object to the screen
    void Draw() const;

    // Get properties
    const Color::ColorVector& GetColor() const { return m_oColor; }
    const Point3D& GetPosition() const { return m_oPosition; }
    const Point3D& GetScale() const { return m_oScale; }
    const Transform3D& GetAfterTransform() const
    { return m_oAfterTransform; }
    const Transform3D& GetBeforeTransform() const
    { return m_oBeforeTransform; }
    bool IsVisible() const { return m_bVisible; }

    // Get rotation properties
    double GetPitch() const { return m_oRotation.GetPitch(); }
    double GetRoll() const { return m_oRotation.GetRoll(); }
    double GetYaw() const { return m_oRotation.GetYaw(); }
    double GetRotationAngle() const { return m_oRotation.GetAngle(); }
    Point3D GetRotationAxis() const { return m_oRotation.GetAxis(); }
    const Rotation3D& GetRotation() const { return m_oRotation; }
    void GetTaitBryanAngles( double& a_rdYaw, double& a_rdPitch,
                             double& a_rdRoll ) const
    { m_oRotation.GetTaitBryanAngles( a_rdYaw, a_rdPitch, a_rdRoll ); }

    // Get the cached model view transformation resulting from this object's
    // scale/rotation/position/etc.  If any of those properties have changed
    // since the last time said transformation was calculated, recalculate it.
    virtual const Transform3D& GetModelMatrix() const;

    // Set color
    Drawable& SetColor( const Color::ColorVector& ac_roColor );
    Drawable& SetColor( float a_fRed, float a_fGreen, float a_fBlue,
                        float a_fAlpha = 1.0f );
    Drawable& SetColor( Color::Channel a_ucRed,
                        Color::Channel a_ucGreen,
                        Color::Channel a_ucBlue,
                        Color::Channel a_ucAlpha = 0xFF );

    // Rotate toward something (for unrotated objects, the x-axis is "forward"
    // and the z-axis is "up")
    Drawable& RotateTowardDirection( const Point3D& ac_roForward,
                                     const Point3D& ac_roUp,
                                     double a_dAmount = 1.0 );
    Drawable& RotateTowardDirection( const Point3D& ac_roForward,
                                     double a_dAmount = 1.0 );
    Drawable& RotateTowardPoint( const Point3D& ac_roTarget,
                                 const Point3D& ac_roUp,
                                 double a_dAmount = 1.0 );
    Drawable& RotateTowardPoint( const Point3D& ac_roTarget,
                                 double a_dAmount = 1.0 );
    Drawable& RotateToward( const HVector3D& ac_roHVector,
                            const Point3D& ac_roUp,
                            double a_dAmount = 1.0 );
    Drawable& RotateToward( const HVector3D& ac_roHVector,
                            double a_dAmount = 1.0 );
    Drawable& RotateTowardDirection( const Point3D& ac_roForward,
                                     const Point3D& ac_roUp,
                                     double a_dRadiansPerSecond,
                                     double a_dSeconds,
                                     bool a_bClamp = true );
    Drawable& RotateTowardDirection( const Point3D& ac_roForward,
                                     double a_dRadiansPerSecond,
                                     double a_dSeconds,
                                     bool a_bClamp = true );
    Drawable& RotateTowardPoint( const Point3D& ac_roTarget,
                                 const Point3D& ac_roUp,
                                 double a_dRadiansPerSecond,
                                 double a_dSeconds,
                                 bool a_bClamp = true );
    Drawable& RotateTowardPoint( const Point3D& ac_roTarget,
                                 double a_dRadiansPerSecond,
                                 double a_dSeconds,
                                 bool a_bClamp = true );
    Drawable& RotateToward( const HVector3D& ac_roHVector,
                            const Point3D& ac_roUp,
                            double a_dRadiansPerSecond,
                            double a_dSeconds,
                            bool a_bClamp = true );
    Drawable& RotateToward( const HVector3D& ac_roHVector,
                            double a_dRadiansPerSecond,
                            double a_dSeconds,
                            bool a_bClamp = true );


    // Set rotation
    Drawable& SetPitch( double a_dPitch = 0.0 );
    Drawable& SetRoll( double a_dRoll = 0.0 );
    Drawable& SetYaw( double a_dYaw = 0.0 );
    Drawable& SetRotation( const Rotation3D& ac_roRotation = Rotation3D::None() );
    Drawable& SetRotation( double a_dAngle,
                           const Point3D& ac_roAxis = Point3D::Unit(2) );
    Drawable& SetRotationAngle( double a_dAngle = 0.0 );
    Drawable& SetRotationAxis( const Point3D& ac_roAxis = Point3D::Unit(2) );
    Drawable& SetTaitBryanAngles( double a_dYaw = 0.0, double a_dPitch = 0.0,
                                  double a_dRoll = 0.0 );

    // Set position and scale
    Drawable& SetPosition( const Point3D& ac_roPosition = Point3D::Origin() );
    Drawable& SetPosition( double a_dX, double a_dY = 0.0, double a_dZ = 0.0 );
    Drawable& SetScale( const Point3D& ac_roScale = Point3D( 1.0 ) );
    Drawable& SetScale( double a_dFactor );
    Drawable& SetScale( double a_dX, double a_dY, double a_dZ = 0.0 );

    // Apply/Set additional transformation
    Drawable& SetAfterTransform(
        const Transform3D& ac_roTransform = Transform3D::Identity() );
    Drawable& SetBeforeTransform(
        const Transform3D& ac_roTransform = Transform3D::Identity() );

    // Show/Hide
    Drawable& Show();
    Drawable& Hide();
    Drawable& SetVisible( bool a_bVisible );

    // set a flag indicating that the cached modelview matrix for this object
    // should be recalculated
    void UpdateModelMatrix() { *m_pbUpdateModelMatrix = true; }

protected:

    // This is where the actual work of drawing the object, whatever it is,
    // takes place.
    virtual void DrawComponents() const = 0;

    // Default color for everything
    Color::ColorVector m_oColor;

    // Basic scale/position/rotation
    Point3D m_oPosition;    // applied after rotation
    Rotation3D m_oRotation;
    Point3D m_oScale;   // applied before rotation

    // Additional transformations applied to vertices after the transformations
    // due to the above properties
    Transform3D m_oAfterTransform;

    // Additional transformations applied to vertices before the transformations
    // due to the above properties
    Transform3D m_oBeforeTransform;

    // Is this object even visible?
    bool m_bVisible;

    // Cache the complete transformation for cases when it doesn't change.
    // When it does change, set a flag indicating that the cached matrix should
    // be recalculated.  These are pointers to values instead of actual values
    // as a cheat that lets them be updated even in const functions.
    bool* m_pbUpdateModelMatrix;
    Transform3D* m_poModelMatrix;

};  // class Drawable

}   // namespace MyFirstEngine

#endif  // DRAWABLE__H
