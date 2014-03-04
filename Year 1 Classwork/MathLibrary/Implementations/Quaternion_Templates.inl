/******************************************************************************
 * File:               Quaternion_Templates.inl
 * Author:             Elizabeth Lowry
 * Date Created:       March 3, 2014
 * Description:        Implementations for templated Quaternion functions.
 * Last Modified:      March 3, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef QUATERNION__TEMPLATES__INL
#define QUATERNION__TEMPLATES__INL

#include "../Declarations/Quaternion.h"

namespace Space
{

// Raising to a scalar power = multiplying rotation angle by that scalar
template< typename T >
inline typename std::enable_if< std::is_scalar< T >::value, Quaternion >::type
    Quaternion::operator^( const T& ac_rScalar ) const
{
    Quaternion oCopy( *this );
    return oCopy.operator*=( ac_rScalar );
}
template< typename T >
inline typename std::enable_if< std::is_scalar< T >::value, Quaternion& >::type
    Quaternion::operator^=( const T& ac_rScalar )
{
    SetAngle( GetAngle() * ac_rScalar );
    return *this;
}

// Multiplying by a scalar = multiplying each component by that scalar
template< typename T >
inline typename std::enable_if< std::is_scalar< T >::value, Quaternion >::type
    Quaternion::operator*( const T& ac_rScalar ) const
{
    Quaternion oCopy( *this );
    return oCopy.operator*=( ac_rScalar );
}
template< typename T >
inline typename std::enable_if< std::is_scalar< T >::value, Quaternion& >::type
    Quaternion::operator*=( const T& ac_rScalar )
{
    BaseType::operator*=( ac_rScalar );
    return *this;
}
template< typename T >
inline typename std::enable_if< std::is_scalar< T >::value, Quaternion >::type
    Quaternion::operator/( const T& ac_rScalar ) const
{
    Quaternion oCopy( *this );
    return oCopy.operator/=( ac_rScalar );
}
template< typename T >
inline typename std::enable_if< std::is_scalar< T >::value, Quaternion& >::type
    Quaternion::operator/=( const T& ac_rScalar )
{
    BaseType::operator/=( ac_rScalar );
    return *this;
}

}   // namespace Space

namespace Math
{

// Spherical linear interpolation: http://en.wikipedia.org/wiki/Slerp
template<>
inline Space::Quaternion
    Interpolate< Space::Quaternion >( const Space::Quaternion& ac_roQuaternionA,
                                      const Space::Quaternion& ac_roQuaternionB,
                                      float a_fProgress)
{
    if( 0.0 == a_fProgress )
    {
        return ac_roQuaternionA;
    }
    if( 1.0 == a_fProgress )
    {
        return ac_roQuaternionB;
    }
    Quaternion oDifference = ( ac_roQuaternionA ^ -1 ) * ac_roQuaternionB;
    return ac_roQuaternionA * ( oDifference.Clamp() ^ a_fProgress );
}

// Quaternion scalar multiplication and division in the other direction
template< typename T >
inline typename std::enable_if< std::is_scalar< T >::value, Space::Quaternion >::type
    operator*( const T& ac_rScalar, const Space::Quaternion& ac_roQuaternion )
{
    return ac_roQuaternion * ac_rScalar;
}
template< typename T >
inline typename std::enable_if< std::is_scalar< T >::value, Space::Quaternion >::type
    operator/( const T& ac_rScalar, const Space::Quaternion& ac_roQuaternion )
{
    return ac_roQuaternion.Inverse() * ac_rScalar;
}

}   // namespace Math

#endif  // QUATERNION__TEMPLATES__INL
