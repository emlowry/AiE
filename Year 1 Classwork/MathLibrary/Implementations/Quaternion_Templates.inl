/******************************************************************************
 * File:               Quaternion_Templates.inl
 * Author:             Elizabeth Lowry
 * Date Created:       March 3, 2014
 * Description:        Implementations for templated Quaternion functions.
 * Last Modified:      March 5, 2014
 * Last Modification:  Debugging.
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
    return oCopy.operator^=( ac_rScalar );
}
template< typename T >
inline typename std::enable_if< std::is_scalar< T >::value, Quaternion& >::type
    Quaternion::operator^=( const T& ac_rScalar )
{
    // save time on simple cases
    if( (T)1 == ac_rScalar )
    {
        return *this;
    }
    if( (T)0 == ac_rScalar )
    {
        return operator=( Quaternion::None() );
    }
    
    // "Inverse" means rotate in the opposite direction, so just flip the axis
    if( (T)(-1) == ac_rScalar )
    {
        x = -x;
        y = -y;
        z = -z;
        return *this;
    }
    
    // Otherwise, set the angle
    SetAngle( GetAngle() * ac_rScalar );
    return *this;
}

}   // namespace Space

#endif  // QUATERNION__TEMPLATES__INL
