/******************************************************************************
 * File:               Quaternion.inl
 * Author:             Elizabeth Lowry
 * Date Created:       March 3, 2014
 * Description:        Inline implementations for Quaternion functions.
 * Last Modified:      March 3, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef QUATERNION__INL
#define QUATERNION__INL

#include "../Declarations/Quaternion.h"
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
    : BaseType( ac_roQuaternion ),
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
    Point3D oAxis = ac_roAxis.Normal();
    w = std::cos( a_dAngle / 2 );
    x = std::sin( a_dAngle / 2 ) * oAxis.x;
    y = std::sin( a_dAngle / 2 ) * oAxis.y;
    z = std::sin( a_dAngle / 2 ) * oAxis.z;
}
INLINE Quaternion::Quaternion( const Point3D& ac_roAxisMultipliedByAngle )
    : w( m_aaData[0][0] ),
      x( m_aaData[0][1] ),
      y( m_aaData[0][2] ),
      z( m_aaData[0][3] )
{
    Point3D oAxis = ac_roAxisMultipliedByAngle.Normal();
    double dAngle = ac_roAxisMultipliedByAngle.Magnitude();
    w = std::cos( dAngle / 2 );
    x = std::sin( dAngle / 2 ) * oAxis.x;
    y = std::sin( dAngle / 2 ) * oAxis.y;
    z = std::sin( dAngle / 2 ) * oAxis.z;
}
INLINE Quaternion::Quaternion( double a_dYaw, double a_dPitch, double a_dRoll )
    : w( m_aaData[0][0] ),
      x( m_aaData[0][1] ),
      y( m_aaData[0][2] ),
      z( m_aaData[0][3] )
{
    operator=( ( HalfRotationAboutAxis( 0 ) ^ ( a_dRoll / Math::PI ) ) *
               ( HalfRotationAboutAxis( 1 ) ^ ( a_dPitch / Math::PI ) ) *
               ( HalfRotationAboutAxis( 2 ) ^ ( a_dYaw / Math::PI ) ) );
}

// Destructor
INLINE Quaternion::~Quaternion() {}

// Assignment
INLINE Quaternion& Quaternion::operator=( const Quaternion& ac_roQuaternion )
{
    BaseType::operator=( ac_roQuaternion );
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

// Addition - adding quaternions means adding their elements
INLINE Quaternion
    Quaternion::operator+( const Quaternion& ac_roQuaternion ) const
{
    Quaternion oCopy( *this );
    return oCopy.operator+=( ac_roQuaternion );
}
INLINE Quaternion& Quaternion::operator+=( const Quaternion& ac_roQuaternion )
{
    BaseType::operator+=( ac_roQuaternion );
    return *this;
}
INLINE Quaternion
    Quaternion::operator-( const Quaternion& ac_roQuaternion ) const
{
    Quaternion oCopy( *this );
    return oCopy.operator-=( ac_roQuaternion );
}
INLINE Quaternion& Quaternion::operator-=( const Quaternion& ac_roQuaternion )
{
    BaseType::operator-=( ac_roQuaternion );
    return *this;
}

// Multiplication - multiplying Q1 by Q2 yields a rotation equal to first
// performing rotation Q1, then performing rotation Q2.  Division is just
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
    return *this;
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

// Unary negation
INLINE Quaternion Quaternion::operator-() const
{
    return *this * -1;
}

// Get properties
INLINE double Quaternion::GetAngle() const
{
    return 2 * std::acos( 1.0 == MagnitudeSquared() ? w : w / Magnitude() );
}
INLINE Point3D Quaternion::GetAxis() const
{
    return Point3D( x, y, z ).Normalize();
}
INLINE Point3D Quaternion::GetAxisMultipliedByAngle() const
{
    return GetAxis() * GetAngle();
}
INLINE double Quaternion::GetYaw() const;
INLINE double Quaternion::GetPitch() const;
INLINE double Quaternion::GetRoll() const;
INLINE void Quaternion::GetTaitBryanAngles( double& a_rdYaw,
                                            double& a_rdPitch,
                                            double& a_rdRoll ) const
{
    // calculate sine of pitch
    double dSinP = 2 * ( (w*z) - (x*y) );

    // singularity at pitch = PI/2
    if( 1.0 <= dSinP )
    {
        a_rdRoll = 0.0;
        a_dPitch = Math::HALF_PI;
        a_rdYaw = -std::atan2( (x*y) - (w*z), (x*z) + (w*x) );
        return;
    }

    // singularity at pitch = -PI/2
    else if( -1.0 >= dSinP )
    {
        a_rdRoll = 0.0;
        a_dPitch = -Math::HALF_PI;
        a_rdYaw = std::atan2( (x*y) - (w*z), (x*z) + (w*x) );
        return;
    }

    // non-singularity case
    a_rdRoll = std::atan2( (y*z) + (w*x), 0.5 - ( (x*x) + (y*y) ) );
    a_rdPitch = std::asin( dSinP );
    a_dYaw = std::atan2( (x*y) + (w*z), 0.5 - ( (y*y) + (z*z) ) );
}

}   // namespace Space

#endif  // QUATERNION__INL
