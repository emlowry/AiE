/******************************************************************************
 * File:               XY.inl
 * Author:             Elizabeth Lowry
 * Date Created:       October 29, 2013
 * Description:        Inline function definitions for XY.h.
 * Last Modified:      October 29, 2013
 * Last Modification:  Moved code out of Globals.inl.
 ******************************************************************************/

#ifndef _XY_INL_
#define _XY_INL_

#include <cmath>

// Constructors
template < typename T >
inline XY< T >::XY( const T& a_roT ) : x( a_roT ), y( a_roT ) {}
template < typename T >
inline XY< T >::XY( const T& a_roTx, const T& a_roTy )
    : x( a_roTx ), y( a_roTy ) {}

// Conversion operator
template< typename T >
template < typename U >
inline XY< T >::operator XY< U >() const
{
    return XY< U >( (U)x, (U)y );
}

// Assignment operator
template< typename T >
template< typename U >
XY< T >& XY< T >::operator=( const XY< U >& ac_roNew )
{
    if( (const void*)(&ac_roNew) != (const void*)(this) )
    {
        x = (T)(ac_roNew.x);
        y = (T)(ac_roNew.y);
    }
    return *this;
}

// Distance between two points
template < typename T, typename U >
inline double Hypotenuse( const XY< T >& a_roPointA, const XY< U >& a_roPointB )
{
    return hypot( abs( (double)(a_roPointA.x) - (double)(a_roPointB.x) ),
                  abs( (double)(a_roPointA.y) - (double)(a_roPointB.y) ) );
}

#endif  // _XY_INL_
