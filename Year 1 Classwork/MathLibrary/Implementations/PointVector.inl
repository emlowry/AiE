/******************************************************************************
 * File:               PointVector.inl
 * Author:             Elizabeth Lowry
 * Date Created:       December 17, 2013
 * Description:        Inline function implementations for PointVector.
 * Last Modified:      February 11, 2014
 * Last Modification:  Redistributing functions from this file and
 *                      PointVector_Templates.inl into this file and
 *                      PointVector_Constructors.inl.
 ******************************************************************************/

#ifndef POINT_VECTOR__INL
#define POINT_VECTOR__INL

#include "../Declarations/HomogeneousVector.h"
#include "../Declarations/PointVector.h"
#include "PointVector_Constructors.inl"
#include "../Declarations/ImExportMacro.h"

namespace Plane
{

// destructor
template< typename T >
INLINE PointVector< T >::~PointVector() {}

// Assignment operators that pass to base class
template< typename T >
INLINE PointVector< T >& PointVector< T >::operator=( const T& ac_rFill )
{
    BaseType::operator=( ac_rFill );
    return *this;
}
template< typename T >
INLINE PointVector< T >& PointVector< T >::operator=( const T (&ac_raData)[ 2 ] )
{
    BaseType::operator=( ac_raData );
    return *this;
}

// Assignment operators that pass to base class
template< typename T >
template< typename U, unsigned int Q, bool t_bOtherIsRow >
INLINE PointVector< T >& PointVector< T >::
    operator=( const Vector< U, Q, t_bOtherIsRow >& ac_roVector )
{
    BaseType::operator=( ac_roVector );
    return *this;
}
template< typename T >
template< typename U, unsigned int P, unsigned int Q >
INLINE PointVector< T >& PointVector< T >::
    operator=( const Matrix< U, P, Q >& ac_roMatrix )
{
    BaseType::operator=( ac_roMatrix );
    return *this;
}

// Origin of the coordinate system
template< typename T >
INLINE const PointVector< T >& PointVector< T >::Origin()
{
    static PointVector oOrigin = Zero();
    return oOrigin;
}

}   // namespace Plane

namespace Space
{

// destructor
template< typename T >
INLINE PointVector< T >::~PointVector() {}

// Assignment operators that pass to base class
template< typename T >
INLINE PointVector< T >& PointVector< T >::operator=( const T& ac_rFill )
{
    BaseType::operator=( ac_rFill );
    return *this;
}
template< typename T >
INLINE PointVector< T >& PointVector< T >::operator=( const T (&ac_raData)[ 3 ] )
{
    BaseType::operator=( ac_raData );
    return *this;
}

// Assignment operators that pass to base class
template< typename T >
template< typename U, unsigned int Q, bool t_bOtherIsRow >
INLINE PointVector< T >& PointVector< T >::
    operator=( const Vector< U, Q, t_bOtherIsRow >& ac_roVector )
{
    BaseType::operator=( ac_roVector );
    return *this;
}
template< typename T >
template< typename U, unsigned int P, unsigned int Q >
INLINE PointVector< T >& PointVector< T >::
    operator=( const Matrix< U, P, Q >& ac_roMatrix )
{
    BaseType::operator=( ac_roMatrix );
    return *this;
}

// Origin of the coordinate system
template< typename T >
INLINE const PointVector< T >& PointVector< T >::Origin()
{
    static PointVector oOrigin = Zero();
    return oOrigin;
}

}   // namespace Space

#endif  // POINT_VECTOR__INL
