/******************************************************************************
 * File:               XY.inl
 * Author:             Elizabeth Lowry
 * Date Created:       October 29, 2013
 * Description:        Inline function definitions for XY.h.
 * Last Modified:      October 29, 2013
 * Last Modification:  Moved code out of Globals.inl.
 ******************************************************************************/

#include <cmath>

// Constructors
template < typename T >
inline XY< T >::XY( const T& a_roT ) : x( a_roT ), y( a_roT ) {}
template < typename T >
inline XY< T >::XY( const T& a_roTx, const T& a_roTy )
    : x( a_roTx ), y( a_roTy ) {}

// Distance between two points
template < typename T, typename U >
inline float Hypotenuse( const XY< T >& a_roPointA, const XY< U >& a_roPointB )
{
    return hypot( fdim( a_roPointA.x, a_roPointB.x ),
                  fdim( a_roPointA.y, a_roPointB.y ) );
}
