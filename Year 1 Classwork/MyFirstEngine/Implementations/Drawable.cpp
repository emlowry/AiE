/******************************************************************************
 * File:               Drawable.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       February 24, 2014
 * Description:        Implementations for Drawable member functions.
 * Last Modified:      February 27, 2014
 * Last Modification:  Refactoring and debugging.
 ******************************************************************************/

#include "../Declarations/Drawable.h"
#include <cmath>

namespace MyFirstEngine
{

// Constructor
Drawable::Drawable( ShaderProgram* a_poProgram,
                    const Color::ColorVector& ac_roColor,
                    const Point3D& ac_roScale,
                    const Point3D& ac_roPosition,
                    double a_dYaw, double a_dPitch, double a_dRoll )
    : m_oColor( ac_roColor ), m_oScale( ac_roScale ), m_oPosition( ac_roPosition ),
      m_dYaw( a_dYaw ), m_dPitch( a_dPitch ), m_dRoll( a_dRoll ),
      m_poProgram( a_poProgram ), m_oAfterTransform( Transform3D::Identity() ),
      m_oBeforeTransform( Transform3D::Identity() ), m_bVisible( true ),
      m_pbUpdateModelMatrix( new bool ), m_poModelMatrix( new Transform3D )
{
    UpdateModelMatrix();  // cached modelview transform hasn't been generated
}
Drawable::Drawable( const Drawable& ac_roObject )
    : m_oColor( ac_roObject.m_oColor ), m_oScale( ac_roObject.m_oScale ),
      m_oPosition( ac_roObject.m_oPosition ), m_dYaw( ac_roObject.m_dYaw ),
      m_dPitch( ac_roObject.m_dPitch ), m_dRoll( ac_roObject.m_dRoll ),
      m_poProgram( ac_roObject.m_poProgram ), m_bVisible( ac_roObject.m_bVisible ),
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
    m_dYaw = ac_roObject.m_dYaw;
    m_dPitch = ac_roObject.m_dPitch;
    m_dRoll = ac_roObject.m_dRoll;
    m_poProgram = ac_roObject.m_poProgram;
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

    // In case there is already an active shader program
    const ShaderProgram& roPreviousProgram = ShaderProgram::Current();

    // start using the shader program
    if( nullptr != m_poProgram )
    {
        m_poProgram->Use();
    }

    // Set modelview matrix
    // OpenGL uses column vectors, while the MathLibrary transforms are made for
    // use with row vectors.  However, OpenGL stores matrix data in column-major
    // order, while the MathLibrary matrices store data in row-major order, so
    // feeding data from the latter to the former is an automatic transposition.
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
    glMultMatrixd( &( GetModelMatrix()[0][0] ) );

    // Draw the components of this drawable object - points, lines, other
    // drawable objects, etc.
    DrawComponents();

    // reset modelview matrix
    glMatrixMode( GL_MODELVIEW );
    glPopMatrix();

    // Restore previous shader program
    roPreviousProgram.Use();
}

// Apply transformations to the current matrix
const Transform3D& Drawable::GetModelMatrix() const
{
    // If One of the transformation properties has been updated,
    if( *m_pbUpdateModelMatrix )
    {
        // Recompute the modelview matrix
        *m_poModelMatrix = m_oBeforeTransform * Space::Scaling( m_oScale ) *
                         Space::Rotation( m_dYaw, m_dPitch, m_dRoll ) *
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

// Add rotation properties
Drawable& Drawable::AddPitch( double a_dPitch )
{
    if( a_dPitch != 0.0 )
    {
        m_dPitch = Math::ScrollRadians( m_dPitch + a_dPitch );
        if( -Math::HALF_PI > m_dPitch || Math::HALF_PI < m_dPitch )
        {
            m_dYaw = Math::ScrollRadians( m_dYaw + Math::PI );
            m_dPitch = ( 0 < m_dPitch
                         ? Math::HALF_PI - ( m_dPitch - Math::HALF_PI )
                         : -Math::HALF_PI - ( m_dPitch + Math::HALF_PI ) );
        }
        UpdateModelMatrix();
    }
    return *this;
}
Drawable& Drawable::AddRoll( double a_dRoll )
{
    if( a_dRoll != 0.0 )
    {
        m_dRoll += a_dRoll;
        UpdateModelMatrix();
    }
    return *this;
}
Drawable& Drawable::AddYaw( double a_dYaw )
{
    if( a_dYaw != 0.0 )
    {
        m_dYaw += a_dYaw;
        UpdateModelMatrix();
    }
    return *this;
}
Drawable& Drawable::AddRotation( double a_dYaw, double a_dPitch, double a_dRoll )
{
    if( a_dYaw != 0.0 || a_dPitch != 0.0 || a_dRoll != 0.0 )
    {
        m_dYaw += a_dYaw;
        m_dPitch += a_dPitch;
        m_dRoll += a_dRoll;
        UpdateModelMatrix();
    }
    return *this;
}

// Set rotation properties
Drawable& Drawable::SetPitch( double a_dPitch )
{
    if( a_dPitch != m_dPitch )
    {
        m_dPitch = a_dPitch;
        UpdateModelMatrix();
    }
    return *this;
}
Drawable& Drawable::SetRoll( double a_dRoll )
{
    if( a_dRoll != m_dRoll )
    {
        m_dRoll = a_dRoll;
        UpdateModelMatrix();
    }
    return *this;
}
Drawable& Drawable::SetYaw( double a_dYaw )
{
    if( a_dYaw != m_dYaw )
    {
        m_dYaw = a_dYaw;
        UpdateModelMatrix();
    }
    return *this;
}
Drawable& Drawable::SetRotation( double a_dYaw, double a_dPitch, double a_dRoll )
{
    if( a_dYaw != m_dYaw || a_dPitch != m_dPitch || a_dRoll != m_dRoll )
    {
        m_dYaw = a_dYaw;
        m_dPitch = a_dPitch;
        m_dRoll = a_dRoll;
        UpdateModelMatrix();
    }
    return *this;
}

// Given vectors for a desired forward (x-axis) and up (z-axis) direction,
// calculate yaw, pitch, and roll.  If a zero vector is given as up, use the
// z-axis rotated by this object's current rotation.  If the forward vector
// and the up vector are the same, then the calculated roll will be the
// current roll.  If the given forward vector is zero, then return false.
bool Drawable::
    CalculateTaitBryanAngles( double& a_rdYaw, double& a_rdPitch,
                              double a_rdRoll, const Point3D& ac_roForward,
                              const Point3D& ac_roUp ) const
{
    // If no forward direction is given, return false
    if( Point3D::Zero() == ac_roForward )
    {
        return false;
    }

    // Calculate desired Yaw and pitch
    Point3D oForward = ac_roForward.Normal();
    Point2D oForwardXY( ac_roForward );
    a_rdYaw = ( oForwardXY.y < 0 ? -1 : 1 ) *
        std::acos( Point2D::Unit(0).Dot( oForwardXY.Normalize() ) );
    a_rdPitch = std::asin( oForward.z );

    // If an up vector was provided, use its normalized value as the desired
    // post-rotation z-axis.  Otherwise, use the z-axis transformed by the
    // current yaw, pitch, and roll
    Point3D oUp = ( Point3D::Zero() != ac_roUp ? ac_roUp.Normal()
                    : Point3D::Unit(2) *
                        Space::PointRotation( m_dYaw, m_dPitch, m_dRoll ) );

    // Calculate target roll
    a_rdRoll = m_dRoll;
    if( oUp != oForward )
    {
        oUp *= Space::Rotation( -dYaw, -dPitch, 0.0 );
        oUp.x = 0;
        a_rdRoll = ( oUp.y > 0 ? -1 : 1 ) *
            std::acos( Point3D::Unit(2).Dot( oUp.Normalize() ) );
    }

    return true;
}

// Rotate toward something (for unrotated objects, the x-axis is "forward"
// and the z-axis is "up")
Drawable& Drawable::RotateTowardDirection( const Point3D& ac_roForward,
                                           const Point3D& ac_roUp,
                                           double a_dAmount )
{
    if( 0.0 != a_dAmount && Point3D::Zero() != ac_roForward )
    {
        // Calculate desired Yaw, pitch, and roll
        double dYaw, dPitch, dRoll;
        CalculateTaitBryanAngles( dYaw, dPitch, dRoll, ac_roForward, ac_roUp );

        // Set new rotation values
        m_dYaw = Math::Scroll( m_dYaw,
                               dYaw + (double)Math::PI,
                               dYaw - (double)Math::PI );
        m_dYaw = Math::Interpolate( dYaw, m_dYaw, a_dAmount );
        m_dPitch = Math::Scroll( m_dPitch,
                                 dPitch + (double)Math::PI,
                                 dPitch - (double)Math::PI );
        m_dPitch = Math::Interpolate( dPitch, m_dPitch, a_dAmount );
        m_dRoll = Math::Scroll( m_dRoll,
                                dRoll + (double)Math::PI,
                                dRoll - (double)Math::PI );
        m_dRoll = Math::Interpolate( dRoll, m_dRoll, a_dAmount );
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
                                           double a_dRollSpeed )
{
    if( 0.0 != a_dRadiansPerSecond && 0.0 != a_dSeconds &&
        Point3D::Zero() != ac_roForward )
    {
        Point3D oUp = ( Point3D::Zero() != ac_roUp ? ac_roUp
                        : Point3D::Unit(2) *
                          Space::PointRotation( m_dYaw, m_dPitch, m_dRoll ) );
        // TODO
    }
    return *this;
}
Drawable& Drawable::RotateTowardDirection( const Point3D& ac_roForward,
                                           double a_dRadiansPerSecond,
                                           double a_dSeconds,
                                           double a_dRollSpeed )
{
    return RotateTowardDirection( ac_roForward, Point3D::Zero(),
                                  a_dRadiansPerSecond, a_dSeconds );
}
Drawable& Drawable::RotateTowardPoint( const Point3D& ac_roTarget,
                                       const Point3D& ac_roUp,
                                       double a_dRadiansPerSecond,
                                       double a_dSeconds,
                                       double a_dRollSpeed )
{
    return RotateTowardDirection( ac_roTarget - m_oPosition, ac_roUp,
                                  a_dRadiansPerSecond, a_dSeconds );
}
Drawable& Drawable::RotateTowardPoint( const Point3D& ac_roTarget,
                                       double a_dRadiansPerSecond,
                                       double a_dSeconds,
                                       double a_dRollSpeed )
{
    return RotateTowardDirection( ac_roTarget - m_oPosition, Point3D::Zero(),
                                  a_dRadiansPerSecond, a_dSeconds );
}
Drawable& Drawable::RotateToward( const HVector3D& ac_roHVector,
                                  const Point3D& ac_roUp,
                                  double a_dRadiansPerSecond,
                                  double a_dSeconds,
                                  double a_dRollSpeed )
{
    return ac_roHVector.h == 0
        ? RotateTowardDirection( ac_roHVector, ac_roUp,
                                 a_dRadiansPerSecond, a_dSeconds )
        : RotateTowardPoint( ac_roHVector, ac_roUp,
                             a_dRadiansPerSecond, a_dSeconds );
}
Drawable& Drawable::RotateToward( const HVector3D& ac_roHVector,
                                  double a_dRadiansPerSecond,
                                  double a_dSeconds,
                                  double a_dRollSpeed )
{
    return ac_roHVector.h == 0
        ? RotateTowardDirection( ac_roHVector, Point3D::Zero(),
                                 a_dRadiansPerSecond, a_dSeconds )
        : RotateTowardPoint( ac_roHVector, ac_roUp,
                             a_dRadiansPerSecond, a_dSeconds );
}

// Add position and scale
Drawable& Drawable::AddPosition( const Point3D& ac_roPosition )
{
    if( ac_roPosition != m_oPosition )
    {
        m_oPosition += ac_roPosition;
        UpdateModelMatrix();
    }
    return *this;
}
Drawable& Drawable::AddPosition( double a_dX, double a_dY, double a_dZ )
{
    if( a_dX != m_oPosition.x || a_dY != m_oPosition.y || a_dZ != m_oPosition.z )
    {
        m_oPosition.x += a_dX;
        m_oPosition.y += a_dY;
        m_oPosition.z += a_dZ;
        UpdateModelMatrix();
    }
    return *this;
}
Drawable& Drawable::AddScale( const Point3D& ac_roScale )
{
    if( ac_roScale != m_oScale )
    {
        m_oScale += ac_roScale;
        UpdateModelMatrix();
    }
    return *this;
}
Drawable& Drawable::AddScale( double a_dX, double a_dY, double a_dZ )
{
    if( a_dX != m_oScale.x || a_dY != m_oScale.y || a_dZ != m_oScale.z )
    {
        m_oScale.x += a_dX;
        m_oScale.y += a_dY;
        m_oScale.z += a_dZ;
        UpdateModelMatrix();
    }
    return *this;
}
Drawable& Drawable::AddScale( double a_dFactor )
{
    if( a_dFactor != m_oScale.x ||
        a_dFactor != m_oScale.y ||
        a_dFactor != m_oScale.z )
    {
        m_oScale.x += a_dFactor;
        m_oScale.y += a_dFactor;
        m_oScale.z += a_dFactor;
        UpdateModelMatrix();
    }
    return *this;
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
Drawable& Drawable::ApplyAfterTransform( const Transform3D& ac_roTransform )
{
    if( ac_roTransform != Transform3D::Identity() )
    {
        m_oAfterTransform *= ac_roTransform;
        UpdateModelMatrix();
    }
    return *this;
}
Drawable& Drawable::SetAfterTransform( const Transform3D& ac_roTransform )
{
    if( ac_roTransform != m_oAfterTransform )
    {
        m_oAfterTransform = ac_roTransform;
        UpdateModelMatrix();
    }
    return *this;
}
Drawable& Drawable::ApplyBeforeTransform( const Transform3D& ac_roTransform )
{
    if( ac_roTransform != Transform3D::Identity() )
    {
        m_oBeforeTransform *= ac_roTransform;
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
