/******************************************************************************
 * File:               Drawable.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       February 24, 2014
 * Description:        Implementations for Drawable member functions.
 * Last Modified:      March 17, 2014
 * Last Modification:  Adding replacement for deprecated OpenGL matrix stack.
 ******************************************************************************/

#include "../Declarations/Drawable.h"
#include "../Declarations/GameEngine.h"
#include <cmath>

namespace MyFirstEngine
{

//
// Class functions
//

// Constructor
Drawable::Drawable( const Color::ColorVector& ac_roColor,
                    const Point3D& ac_roScale,
                    const Point3D& ac_roPosition,
                    const Rotation3D& ac_roRotation )
    : m_oColor( ac_roColor ), m_oScale( ac_roScale ),
      m_oPosition( ac_roPosition ), m_oRotation( ac_roRotation ),
      m_oAfterTransform( Transform3D::Identity() ),
      m_oBeforeTransform( Transform3D::Identity() ), m_bVisible( true ),
      m_pbUpdateModelMatrix( new bool ), m_poModelMatrix( new Transform3D )
{
    UpdateModelMatrix();  // cached modelview transform hasn't been generated
}
Drawable::Drawable( const Drawable& ac_roObject )
    : m_oColor( ac_roObject.m_oColor ), m_oScale( ac_roObject.m_oScale ),
      m_oPosition( ac_roObject.m_oPosition ), m_oRotation( ac_roObject.m_oRotation ),
      m_bVisible( ac_roObject.m_bVisible ),
      m_oAfterTransform( ac_roObject.m_oAfterTransform ),
      m_oBeforeTransform( ac_roObject.m_oBeforeTransform ),
      m_pbUpdateModelMatrix( new bool ), m_poModelMatrix( new Transform3D )
{
    UpdateModelMatrix();  // cached modelview transform hasn't been generated
}
Drawable& Drawable::operator=( const Drawable& ac_roObject )
{
    m_oColor = ac_roObject.m_oColor;
    m_oScale = ac_roObject.m_oScale;
    m_oPosition = ac_roObject.m_oPosition;
    m_oRotation = ac_roObject.m_oRotation;
    m_bVisible = ac_roObject.m_bVisible;
    m_oAfterTransform = ac_roObject.m_oAfterTransform;
    m_oBeforeTransform = ac_roObject.m_oBeforeTransform;
    UpdateModelMatrix();
    return *this;
}

// Destructor deallocates the dynamically stored modelview transform cache
// and flag.
Drawable::~Drawable()
{
    delete m_pbUpdateModelMatrix;
    delete m_poModelMatrix;
}

// Draw the object to the screen
void Drawable::Draw() const
{
    // Don't bother if the object isn't visible
    if( !m_bVisible )
    {
        return;
    }

    // Set modelview matrix
    GameEngine::PushModelView();
    GameEngine::ApplyBeforeModelView( GetModelMatrix() );

    // Draw the components of this drawable object - points, lines, other
    // drawable objects, etc.
    DrawComponents();

    // reset modelview matrix
    GameEngine::PopModelView();
}

// Apply transformations to the current matrix
const Transform3D& Drawable::GetModelMatrix() const
{
    // If One of the transformation properties has been updated,
    if( *m_pbUpdateModelMatrix )
    {
        // Recompute the modelview matrix
        *m_poModelMatrix = m_oBeforeTransform * Space::Scaling( m_oScale ) *
                           m_oRotation.MakeTransform() *
                           Space::Translation( m_oPosition ) * m_oAfterTransform;
        *m_pbUpdateModelMatrix = false;
    }
    return *m_poModelMatrix;
}

// Set color
Drawable& Drawable::SetColor( const Color::ColorVector& ac_roColor )
{
    m_oColor = ac_roColor;
    return *this;
}
Drawable& Drawable::SetColor( float a_fRed, float a_fGreen, float a_fBlue,
                              float a_fAlpha )
{
    m_oColor.r = a_fRed;
    m_oColor.g = a_fGreen;
    m_oColor.b = a_fBlue;
    m_oColor.a = a_fAlpha;
    return *this;
}
Drawable& Drawable::SetColor( Color::Channel a_ucRed,
                              Color::Channel a_ucGreen,
                              Color::Channel a_ucBlue,
                              Color::Channel a_ucAlpha )
{
    m_oColor.RedChannel( a_ucRed );
    m_oColor.GreenChannel( a_ucGreen );
    m_oColor.BlueChannel( a_ucBlue );
    m_oColor.AlphaChannel( a_ucAlpha );
    return *this;
}

// Set rotation properties
Drawable& Drawable::SetPitch( double a_dPitch )
{
    m_oRotation.SetPitch( a_dPitch );
    UpdateModelMatrix();
    return *this;
}
Drawable& Drawable::SetRoll( double a_dRoll )
{
    m_oRotation.SetRoll( a_dRoll );
    UpdateModelMatrix();
    return *this;
}
Drawable& Drawable::SetYaw( double a_dYaw )
{
    m_oRotation.SetYaw( a_dYaw );
    UpdateModelMatrix();
    return *this;
}
Drawable& Drawable::SetRotation( const Rotation3D& ac_roRotation )
{
    if( m_oRotation != ac_roRotation )
    {
        m_oRotation = ac_roRotation;
        UpdateModelMatrix();
    }
    return *this;
}
Drawable& Drawable::SetRotation( double a_dAngle, const Point3D& ac_roAxis )
{
    m_oRotation.Set( a_dAngle, ac_roAxis );
    UpdateModelMatrix();
    return *this;
}
Drawable& Drawable::SetRotationAngle( double a_dAngle )
{
    m_oRotation.SetAngle( a_dAngle );
    UpdateModelMatrix();
    return *this;
}
Drawable& Drawable::SetRotationAxis( const Point3D& ac_roAxis )
{
    m_oRotation.SetAxis( ac_roAxis );
    UpdateModelMatrix();
    return *this;
}
Drawable& Drawable::SetTaitBryanAngles( double a_dYaw, double a_dPitch, double a_dRoll )
{
    m_oRotation.Set( a_dYaw, a_dPitch, a_dRoll );
    UpdateModelMatrix();
    return *this;
}

// Rotate toward something (for unrotated objects, the x-axis is "forward"
// and the z-axis is "up")
Drawable& Drawable::RotateTowardDirection( const Point3D& ac_roForward,
                                           const Point3D& ac_roUp,
                                           double a_dAmount )
{
    if( 0.0 != a_dAmount &&
        ( Point3D::Zero() != ac_roForward || Point3D::Zero() != ac_roUp ) )
    {
        Rotation3D oTarget( m_oRotation );
        oTarget.Set( ac_roForward, ac_roUp );
        m_oRotation.Slerp( oTarget, a_dAmount );
        UpdateModelMatrix();
    }
    return *this;
}
Drawable& Drawable::RotateTowardDirection( const Point3D& ac_roForward,
                                           double a_dAmount )
{
    return RotateTowardDirection( ac_roForward, Point3D::Zero(), a_dAmount );
}
Drawable& Drawable::RotateTowardPoint( const Point3D& ac_roTarget,
                                       const Point3D& ac_roUp,
                                       double a_dAmount )
{
    return RotateTowardDirection( ac_roTarget - m_oPosition,
                                  ac_roUp, a_dAmount );
}
Drawable& Drawable::RotateTowardPoint( const Point3D& ac_roTarget,
                                       double a_dAmount )
{
    return RotateTowardDirection( ac_roTarget - m_oPosition,
                                  Point3D::Zero(), a_dAmount );
}
Drawable& Drawable::RotateToward( const HVector3D& ac_roHVector,
                                  const Point3D& ac_roUp,
                                  double a_dAmount )
{
    return ac_roHVector.h == 0
        ? RotateTowardDirection( ac_roHVector, ac_roUp, a_dAmount )
        : RotateTowardPoint( ac_roHVector, ac_roUp, a_dAmount );
}
Drawable& Drawable::RotateToward( const HVector3D& ac_roHVector,
                                  double a_dAmount )
{
    return ac_roHVector.h == 0
        ? RotateTowardDirection( ac_roHVector, Point3D::Zero(), a_dAmount )
        : RotateTowardPoint( ac_roHVector, Point3D::Zero(), a_dAmount );
}
Drawable& Drawable::RotateTowardDirection( const Point3D& ac_roForward,
                                           const Point3D& ac_roUp,
                                           double a_dRadiansPerSecond,
                                           double a_dSeconds,
                                           bool a_bClamp )
{
    if( 0.0 != a_dRadiansPerSecond && 0.0 != a_dSeconds &&
        ( Point3D::Zero() != ac_roForward || Point3D::Zero() != ac_roUp ) )
    {
        Rotation3D oTarget( m_oRotation );
        oTarget.Set( ac_roForward, ac_roUp );
        m_oRotation.Slerp( oTarget, a_dRadiansPerSecond, a_dSeconds, a_bClamp );
        UpdateModelMatrix();
    }
    return *this;
}
Drawable& Drawable::RotateTowardDirection( const Point3D& ac_roForward,
                                           double a_dRadiansPerSecond,
                                           double a_dSeconds,
                                           bool a_bClamp )
{
    return RotateTowardDirection( ac_roForward, Point3D::Zero(),
                                  a_dRadiansPerSecond, a_dSeconds, a_bClamp );
}
Drawable& Drawable::RotateTowardPoint( const Point3D& ac_roTarget,
                                       const Point3D& ac_roUp,
                                       double a_dRadiansPerSecond,
                                       double a_dSeconds,
                                       bool a_bClamp )
{
    return RotateTowardDirection( ac_roTarget - m_oPosition, ac_roUp,
                                  a_dRadiansPerSecond, a_dSeconds, a_bClamp );
}
Drawable& Drawable::RotateTowardPoint( const Point3D& ac_roTarget,
                                       double a_dRadiansPerSecond,
                                       double a_dSeconds,
                                       bool a_bClamp )
{
    return RotateTowardDirection( ac_roTarget - m_oPosition, Point3D::Zero(),
                                  a_dRadiansPerSecond, a_dSeconds, a_bClamp );
}
Drawable& Drawable::RotateToward( const HVector3D& ac_roHVector,
                                  const Point3D& ac_roUp,
                                  double a_dRadiansPerSecond,
                                  double a_dSeconds,
                                  bool a_bClamp )
{
    return ac_roHVector.h == 0
        ? RotateTowardDirection( ac_roHVector, ac_roUp,
                                 a_dRadiansPerSecond, a_dSeconds, a_bClamp )
        : RotateTowardPoint( ac_roHVector, ac_roUp,
                             a_dRadiansPerSecond, a_dSeconds, a_bClamp );
}
Drawable& Drawable::RotateToward( const HVector3D& ac_roHVector,
                                  double a_dRadiansPerSecond,
                                  double a_dSeconds,
                                  bool a_bClamp)
{
    return ac_roHVector.h == 0
        ? RotateTowardDirection( ac_roHVector, Point3D::Zero(),
                                 a_dRadiansPerSecond, a_dSeconds, a_bClamp )
        : RotateTowardPoint( ac_roHVector, Point3D::Zero(),
                             a_dRadiansPerSecond, a_dSeconds, a_bClamp );
}

// Set position and scale
Drawable& Drawable::
    SetPosition( const Point3D& ac_roPosition )
{
    if( ac_roPosition != m_oPosition )
    {
        m_oPosition = ac_roPosition;
        UpdateModelMatrix();
    }
    return *this;
}
Drawable& Drawable::SetPosition( double a_dX, double a_dY, double a_dZ )
{
    if( a_dX != m_oPosition.x || a_dY != m_oPosition.y || a_dZ != m_oPosition.z )
    {
        m_oPosition.x = a_dX;
        m_oPosition.y = a_dY;
        m_oPosition.z = a_dZ;
        UpdateModelMatrix();
    }
    return *this;
}
Drawable& Drawable::SetScale( const Point3D& ac_roScale )
{
    if( ac_roScale != m_oScale )
    {
        m_oScale = ac_roScale;
        UpdateModelMatrix();
    }
    return *this;
}
Drawable& Drawable::SetScale( double a_dX, double a_dY, double a_dZ )
{
    if( a_dX != m_oScale.x || a_dY != m_oScale.y || a_dZ != m_oScale.z )
    {
        m_oScale.x = a_dX;
        m_oScale.y = a_dY;
        m_oScale.z = a_dZ;
        UpdateModelMatrix();
    }
    return *this;
}
Drawable& Drawable::SetScale( double a_dFactor )
{
    if( a_dFactor != m_oScale.x ||
        a_dFactor != m_oScale.y ||
        a_dFactor != m_oScale.z )
    {
        m_oScale.x = a_dFactor;
        m_oScale.y = a_dFactor;
        m_oScale.z = a_dFactor;
        UpdateModelMatrix();
    }
    return *this;
}

// Apply/Set additional transformation
Drawable& Drawable::SetAfterTransform( const Transform3D& ac_roTransform )
{
    if( ac_roTransform != m_oAfterTransform )
    {
        m_oAfterTransform = ac_roTransform;
        UpdateModelMatrix();
    }
    return *this;
}
Drawable& Drawable::SetBeforeTransform( const Transform3D& ac_roTransform )
{
    if( ac_roTransform != m_oBeforeTransform )
    {
        m_oBeforeTransform = ac_roTransform;
        UpdateModelMatrix();
    }
    return *this;
}

// Show/Hide
Drawable& Drawable::Show()
{
    m_bVisible = true;
    return *this;
}
Drawable& Drawable::Hide()
{
    m_bVisible = false;
    return *this;
}
Drawable& Drawable::SetVisible( bool a_bVisible )
{
    m_bVisible = a_bVisible;
    return *this;
}

}   // namespace MyFirstEngine
