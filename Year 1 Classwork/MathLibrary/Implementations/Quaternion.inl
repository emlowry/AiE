/******************************************************************************
 * File:               Quaternion.inl
 * Author:             Elizabeth Lowry
 * Date Created:       March 3, 2014
 * Description:        Inline implementations for Quaternion functions.
 * Last Modified:      March 5, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

#ifndef QUATERNION__INL
#define QUATERNION__INL

#include "../Declarations/Functions.h"
#include "../Declarations/PointVector.h"
#include "../Declarations/Quaternion.h"
#include "../Declarations/Transform.h"
#include <cmath>
#include "../Declarations/ImExportMacro.h"

namespace Space
{

// Constructors
INLINE Quaternion::Quaternion( const Quaternion& ac_roQuaternion )
    : BaseType( ac_roQuaternion ),
      w( m_aaData[0][0] ),
      x( m_aaData[0][1] ),
      y( m_aaData[0][2] ),
      z( m_aaData[0][3] ) {}
INLINE Quaternion::Quaternion( const BaseType& ac_roVector )
    : BaseType( ac_roVector ),
      w( m_aaData[0][0] ),
      x( m_aaData[0][1] ),
      y( m_aaData[0][2] ),
      z( m_aaData[0][3] ) {}
INLINE Quaternion::Quaternion( double a_dAngle, const Point3D& ac_roAxis )
    : w( m_aaData[0][0] ),
      x( m_aaData[0][1] ),
      y( m_aaData[0][2] ),
      z( m_aaData[0][3] )
{
    Set( a_dAngle, ac_roAxis );
}
INLINE Quaternion::Quaternion( const Point3D& ac_roForward,
                               const Point3D& ac_roUp )
    : w( m_aaData[0][0] ),
      x( m_aaData[0][1] ),
      y( m_aaData[0][2] ),
      z( m_aaData[0][3] )
{
    w = 1;
    Set( ac_roForward, ac_roUp );
}
INLINE Quaternion::Quaternion( double a_dYaw, double a_dPitch, double a_dRoll )
    : w( m_aaData[0][0] ),
      x( m_aaData[0][1] ),
      y( m_aaData[0][2] ),
      z( m_aaData[0][3] )
{
    Set( a_dYaw, a_dPitch, a_dRoll );
}
INLINE Quaternion::Quaternion( double a_dW, double a_dX,
                               double a_dY, double a_dZ )
    : w( m_aaData[0][0] ),
      x( m_aaData[0][1] ),
      y( m_aaData[0][2] ),
      z( m_aaData[0][3] )
{
    w = a_dW;
    x = a_dX;
    y = a_dY;
    z = a_dZ;
}

// Destructor
INLINE Quaternion::~Quaternion() {}

// Assignment
INLINE Quaternion& Quaternion::operator=( const Quaternion& ac_roQuaternion )
{
    BaseType::operator=( ac_roQuaternion );
    return *this;
}
INLINE Quaternion& Quaternion::operator=( const BaseType& ac_roVector )
{
    BaseType::operator=( ac_roVector );
    return *this;
}

// Equality and inequality checks
INLINE bool Quaternion::operator==( const Quaternion& ac_roQuaternion ) const
{
    return BaseType::operator==( ac_roQuaternion );
}
INLINE bool Quaternion::operator!=( const Quaternion& ac_roQuaternion ) const
{
    return BaseType::operator!=( ac_roQuaternion );
}

// Access
INLINE double& Quaternion::operator[]( unsigned int a_uiIndex )
{
    return BaseType::operator[]( a_uiIndex );
}
INLINE double& Quaternion::At( unsigned int a_uiIndex )
{
    return BaseType::At( a_uiIndex );
}
INLINE const double& Quaternion::operator[]( unsigned int a_uiIndex ) const
{
    return BaseType::operator[]( a_uiIndex );
}
INLINE const double& Quaternion::At( unsigned int a_uiIndex ) const
{
    return BaseType::At( a_uiIndex );
}

// Multiplication - multiplying Q1 by Q2 yields a rotation equal to first
// performing rotation Q2, then performing rotation Q1.  Division is just
// multiplication by an inverse
INLINE Quaternion
    Quaternion::operator*( const Quaternion& ac_roQuaternion ) const
{
    Quaternion oCopy( *this );
    return oCopy.operator*=( ac_roQuaternion );
}
INLINE Quaternion& Quaternion::operator*=( const Quaternion& ac_roQuaternion )
{
    w = ( w * ac_roQuaternion.w ) - ( x * ac_roQuaternion.x )
        - ( y * ac_roQuaternion.y ) - ( z * ac_roQuaternion.z );
    x = ( w * ac_roQuaternion.x ) + ( x * ac_roQuaternion.w )
        + ( y * ac_roQuaternion.z ) - ( z * ac_roQuaternion.y );
    y = ( w * ac_roQuaternion.y ) - ( x * ac_roQuaternion.z )
        + ( y * ac_roQuaternion.w ) + ( z * ac_roQuaternion.x );
    w = ( w * ac_roQuaternion.z ) + ( x * ac_roQuaternion.y )
        - ( y * ac_roQuaternion.x ) + ( z * ac_roQuaternion.w );
    return Normalize();
}
INLINE Quaternion
    Quaternion::operator/( const Quaternion& ac_roQuaternion ) const
{
    Quaternion oCopy( *this );
    return oCopy.operator*=( ac_roQuaternion ^ -1 );
}
INLINE Quaternion& Quaternion::operator/=( const Quaternion& ac_roQuaternion )
{
    return operator*=( ac_roQuaternion ^ -1 );
}

// Get properties
INLINE double Quaternion::GetAngle() const
{
    return 2 * std::acos( w );
}
INLINE Point3D Quaternion::GetAxis() const
{
    return Point3D( x, y, z ).Normalize();
}

// Conversions from quaternion to Tait-Bryan angles taken from section 3.4.10 of
// http://www.sedris.org/wg8home/Documents/WG80485.pdf
INLINE double Quaternion::GetYaw() const
{
    // calculate sine of pitch
    double dSinP = -2 * ( x*z - w*y );

    // singularity at pitch = PI/2
    if( 1.0 <= dSinP )
    {
        return -std::atan2( x*y - w*z, x*z + w*y );
    }

    // singularity at pitch = -PI/2
    if( -1.0 >= dSinP )
    {
        return std::atan2( x*y - w*z, x*z + w*y );
    }

    // non-singularity case
    return std::atan2( x*y + w*z, 0.5 - ( y*y + z*z ) );
}

// Conversions from quaternion to Tait-Bryan angles taken from section 3.4.10 of
// http://www.sedris.org/wg8home/Documents/WG80485.pdf
INLINE double Quaternion::GetPitch() const
{
    // calculate sine of pitch
    double dSinP = -2 * ( x*z - w*y );

    // singularity at pitch = PI/2
    if( 1.0 <= dSinP )
    {
        return Math::HALF_PI;
    }

    // singularity at pitch = -PI/2
    if( -1.0 >= dSinP )
    {
        return -Math::HALF_PI;
    }

    // non-singularity case
    return std::asin( dSinP );
}

// Conversions from quaternion to Tait-Bryan angles taken from section 3.4.10 of
// http://www.sedris.org/wg8home/Documents/WG80485.pdf
INLINE double Quaternion::GetRoll() const
{
    // calculate sine of pitch
    Quaternion oUnit = Normal();
    double dSinP = -2 * ( x*z - w*y );

    // singularity at pitch = +/-PI/2
    if( 1.0 <= dSinP || -1.0 >= dSinP )
    {
        return 0.0;
    }

    // non-singularity case
    return std::atan2( y*z + w*x , 0.5 - ( x*x + y*y ) );
}

// Conversions from quaternion to Tait-Bryan angles taken from section 3.4.10 of
// http://www.sedris.org/wg8home/Documents/WG80485.pdf
INLINE void Quaternion::GetTaitBryanAngles( double& a_rdYaw,
                                            double& a_rdPitch,
                                            double& a_rdRoll ) const
{
    // calculate sine of pitch
    long double dSinP = -2 * ( x*z - w*y );

    // singularity at pitch = PI/2
    if( 1.0 <= dSinP )
    {
        a_rdRoll = 0.0;
        a_rdPitch = Math::HALF_PI;
        a_rdYaw = -std::atan2( x*y - w*z, x*z + w*y );
        return;
    }

    // singularity at pitch = -PI/2
    else if( -1.0 >= dSinP )
    {
        a_rdRoll = 0.0;
        a_rdPitch = -Math::HALF_PI;
        a_rdYaw = std::atan2( x*y - w*z, x*z + w*y );
        return;
    }

    // non-singularity case
    a_rdRoll = std::atan2( y*z + w*x, 0.5 - ( x*x + y*y ) );
    a_rdPitch = std::asin( dSinP );
    a_rdYaw = std::atan2( x*y + w*z, 0.5 - ( y*y + z*z ) );
}

// Set properties
INLINE Quaternion& Quaternion::SetAngle( double a_dAngle )
{
    return Set( a_dAngle, GetAxis() );
}
INLINE Quaternion& Quaternion::SetAxis( const Point3D& ac_roAxis )
{
    return Set( GetAngle(), ac_roAxis );
}
INLINE Quaternion& Quaternion::SetYaw( double a_dYaw )
{
    double dYaw, dPitch, dRoll;
    GetTaitBryanAngles( dYaw, dPitch, dRoll );
    return Set( a_dYaw, dPitch, dRoll );
}
INLINE Quaternion& Quaternion::SetPitch( double a_dPitch )
{
    double dYaw, dPitch, dRoll;
    GetTaitBryanAngles( dYaw, dPitch, dRoll );
    return Set( dYaw, a_dPitch, dRoll );
}
INLINE Quaternion& Quaternion::SetRoll( double a_dRoll )
{
    double dYaw, dPitch, dRoll;
    GetTaitBryanAngles( dYaw, dPitch, dRoll );
    return Set( dYaw, dPitch, a_dRoll );
}

// Set entire quaternion
INLINE Quaternion& Quaternion::Set( double a_dAngle, const Point3D& ac_roAxis )
{
    double dSin = std::sin( a_dAngle / 2 );
    Point3D oAxis = ac_roAxis.Normal();
    w = ( 1 == dSin || -1 == dSin ? 0 : std::cos( a_dAngle / 2 ) );
    dSin = ( 1 == w || -1 == w ? 0 : dSin );
    x = dSin * oAxis.x;
    y = dSin * oAxis.y;
    z = dSin * oAxis.z;
    return *this;
}
INLINE Quaternion& Quaternion::Set( const Point3D& ac_roForward,
                                    const Point3D& ac_roUp )
{
    // The new rotation
    Quaternion oRotation;

    // If no forward angle is provided, start with existing rotation
    if( Point3D::Zero() == ac_roForward )
    {
        // If no up vector is provided either, just return
        if( Point3D::Zero() == ac_roUp )
        {
            return *this;
        }
        oRotation = *this;
    }
    // Otherwise, create rotation to face the desired direction
    else
    {
        Point3D oForward = ac_roForward.Normal();
        double dAngle = std::acos( Point3D::Unit(1).Dot( oForward ) );
        Point3D oAxis = Point3D::Unit(1).Cross( oForward ).Normalize();
        oRotation = Quaternion( dAngle, oAxis );

        // if no up vector is provided or if up vector is parallel to forward
        // vector, use existing roll
        if( Point3D::Zero() == ac_roUp || 0.0 == ac_roForward.Dot( ac_roUp ) )
        {
            double dRoll = GetRoll();
            if( 0.0 == dRoll )
            {
                return operator=( oRotation.Normalize() );
            }
            Quaternion oRoll( dRoll, Point3D::Unit( 0 ) );
            return operator=( ( oRotation * oRoll ).Normalize() );
        }
    }

    // Find the axis (in the rotated coordinate system) closest to the up axis
    // on the (rotated) YZ plane
    Point3D oUp = oRotation.Inverse().AppliedTo( ac_roUp );
    oUp.x = 0;

    // if no vector on the rotated YZ plane is closer to the up vector than any
    // other, use existing roll
    if( Point3D::Zero() == oUp )
    {
        return operator=( oRotation.SetRoll( GetRoll() ) ).Normalize();
    }

    // Otherwise, calculate the roll neccessary to rotate the already-rotated
    // x-axis into the previously-calculated position
    double dRoll = std::acos( Point3D::Unit(2).Dot( oUp.Normalize() ) ) *
                   ( oUp.y > 0.0 ? -1 : 1 );
    return operator=( oRotation.SetRoll( dRoll ) ).Normalize();
}
INLINE Quaternion&
    Quaternion::Set( double a_dYaw, double a_dPitch, double a_dRoll )
{
    // calculate sines and cosines
    double dCosY = std::cos( a_dYaw / 2 );
    double dSinY = ( 1 == dCosY || -1 == dCosY ? 0 : std::sin( a_dYaw / 2 ) );
    dCosY = ( 1 == dSinY || -1 == dSinY ? 0 : dCosY );
    double dCosP = std::cos( a_dPitch / 2 );
    double dSinP = ( 1 == dCosP || -1 == dCosP ? 0 : std::sin( a_dPitch / 2 ) );
    dCosP = ( 1 == dSinP || -1 == dSinP ? 0 : dCosP );
    double dCosR = std::cos( a_dRoll / 2 );
    double dSinR = ( 1 == dCosR || -1 == dCosR ? 0 : std::sin( a_dRoll / 2 ) );
    dCosR = ( 1 == dSinR || -1 == dSinR ? 0 : dCosR );

    // set elements
    w = dCosR*dCosP*dCosY - dSinR*dSinP*dSinY;
    x = dSinR*dCosP*dCosY + dCosR*dSinP*dSinY;
    y = dCosR*dSinP*dCosY - dSinR*dCosP*dSinY;
    z = dCosR*dCosP*dSinY + dSinR*dSinP*dCosY;
    return *this;
}

// Apply this rotation to the given point
INLINE Point3D Quaternion::AppliedTo( const Point3D& ac_roPoint ) const
{
    Point3D oCopy( ac_roPoint );
    return ApplyTo( oCopy );
}
INLINE Point3D& Quaternion::ApplyTo( Point3D& a_roPoint ) const
{
    // save time on the simple case
    if( operator==( None() ) )
    {
        return a_roPoint;
    }

    // Calculate rotated point
    Point3D oQVector( x, y, z );
    a_roPoint = 2 * oQVector.Dot(a_roPoint) * oQVector
                + ( w*w - oQVector.MagnitudeSquared() ) * a_roPoint
                + 2 * w * oQVector.Cross( a_roPoint );
    return a_roPoint;
}

// Adjust so that angle of rotation is in the range [0,PI]
// rotating A radians about axis B = rotating ( 2PI - A ) radians about -B
//  cos( PI - A/2 ) = cos( PI )cos( A/2 ) + sin( PI )sin( A/2 ) = -cos( A/2 )
//  sin( PI - A/2 ) = sin( PI )cos( A/2 ) - cos( PI )sin( A/2 ) = sin( A/2 )
//  so going from w = cos( A/2 ), x|y|z = sin( A/2 ) * Bx|By|Bz to
//  w = cos( ( 2PI - A ) / 2 ), x|y|z = sin( ( 2PI - A ) / 2 ) * -Bx|-By|-Bz
//  is the same as going to w = -cos( A/2 ), x|y|z = -sin( A/2 ) * Bx|By|Bz
//  or simply multiplying the quaternion by -1.
INLINE Quaternion Quaternion::Clamped() const
{
    if( w < 0.0 )
    {
        return Quaternion( -w, -x, -y, -z );
    }
    return *this;
}
INLINE Quaternion& Quaternion::Clamp()
{
    if( w < 0.0 )
    {
        BaseType::operator*=( -1 );
    }
    return *this;
}

// Inversion
INLINE Quaternion Quaternion::Inverse() const
{
    return Quaternion( w, -x, -y, -z );
}
INLINE Quaternion& Quaternion::Invert()
{
    x = -x;
    y = -y;
    z = -z;
    return *this;
}

// Magnitude and normalization
INLINE Quaternion& Quaternion::Normalize()
{
    BaseType::Normalize();
    return *this;
}

// Spherical linear interpolation: http://en.wikipedia.org/wiki/Slerp
INLINE Quaternion Quaternion::Slerped( const Quaternion& ac_roQuaternion,
                                       double a_dProgress ) const
{
    Quaternion oCopy( *this );
    return oCopy.Slerp( ac_roQuaternion, a_dProgress );
}
INLINE Quaternion& Quaternion::Slerp( const Quaternion& ac_roQuaternion,
                                      double a_dProgress )
{
    // Save time on endpoint cases
    if( 0.0 == a_dProgress )
    {
        return *this;
    }
    if( 1.0 == a_dProgress )
    {
        return operator=( ac_roQuaternion );
    }

    // Slerp
    Quaternion oDifference = ( ac_roQuaternion / (*this) ).Clamp();
    operator=( ( oDifference ^ a_dProgress ) * (*this) );
    return Normalize();
}
INLINE Quaternion Quaternion::Slerped( const Quaternion& ac_roQuaternion,
                                       double a_dRadiansPerSecond,
                                       double a_dSeconds,
                                       bool a_bClamp ) const
{
    Quaternion oCopy( *this );
    return oCopy.Slerp( ac_roQuaternion,
                        a_dRadiansPerSecond, a_dSeconds,
                        a_bClamp );
}
INLINE Quaternion& Quaternion::Slerp( const Quaternion& ac_roQuaternion,
                                      double a_dRadiansPerSecond,
                                      double a_dSeconds,
                                      bool a_bClamp )
{
    // Save time 
    if( 0.0 == a_dSeconds || 0.0 == a_dRadiansPerSecond ||
        operator==( ac_roQuaternion ) )
    {
        return *this;
    }

    // Get the rotation to apply to this one
    Quaternion oDifference = ( ac_roQuaternion / (*this) ).Clamp();
    double dRadians = oDifference.GetAngle();
    double dDistance = a_dRadiansPerSecond * a_dSeconds;

    // If clamped (stopping at the target instead of spinning past), check for
    // arrival.
    if( a_bClamp &&
        ( dRadians <= dDistance ||
          dRadians - Math::RADIANS_IN_A_CIRCLE >= dDistance ) )
    {
        return operator=( ac_roQuaternion );
    }

    // If not clamped and distance is a multiple of 2PI, save time
    dDistance = Math::ScrollRadians( dDistance );
    if( 0.0 == dDistance || 0.0 == dRadians )
    {
        return *this;
    }

    // Slerp
    operator=( ( oDifference ^ ( dDistance / dRadians ) ) * (*this) );
    return Normalize();
}

// Turn into transform
INLINE Transform Quaternion::MakeTransform() const
{
    Transform oTransform;
    MakeTransform( oTransform );
    return oTransform;
}
INLINE void Quaternion::MakeTransform( Transform& a_roTransform ) const
{
    double adData[4][4] =
    { { 1 - 2*( y*y + z*z ), 2*x*y + 2*w*z,       2*x*z - 2*w*y,       0.0 },
      { 2*x*y - 2*w*z,       1 - 2*( x*x + z*z ), 2*y*z + 2*w*x,       0.0 },
      { 2*x*z + 2*w*y,       2*y*z - 2*w*x,       1 - 2*( x*x + y*y ), 0.0 },
      { 0.0,                 0.0,                 0.0,                 1.0 } };
    a_roTransform = adData;
}
INLINE PointTransform Quaternion::MakePointTransform() const
{
    PointTransform oTransform;
    MakePointTransform( oTransform );
    return oTransform;
}
INLINE void Quaternion::MakePointTransform( PointTransform& a_roTransform ) const
{
    double adData[3][3] =
    { { 1 - 2*( y*y + z*z ), 2*x*y + 2*w*z,       2*x*z - 2*w*y },
      { 2*x*y - 2*w*z,       1 - 2*( x*x + z*z ), 2*y*z + 2*w*x },
      { 2*x*z + 2*w*y,       2*y*z - 2*w*x,       1 - 2*( x*x + y*y ) } };
    a_roTransform = adData;
}

//
// Static functions
//

// Rotation by PI radians about the given axis (default is z-axis)
INLINE const Quaternion& Quaternion::Half( unsigned int a_uiAxis )
{
    static Quaternion aoStorage[3] = { Quaternion( 0.0, 1.0, 0.0, 0.0 ),
                                       Quaternion( 0.0, 0.0, 1.0, 0.0 ),
                                       Quaternion( 0.0, 0.0, 0.0, 1.0 ) };
    return aoStorage[ a_uiAxis ];
}

// Quaternion representing no rotation
INLINE const Quaternion& Quaternion::None()
{
    static Quaternion oNoRotation( 1.0, 0.0, 0.0, 0.0 );
    return oNoRotation;
}

}   // namespace Space

#endif  // QUATERNION__INL
