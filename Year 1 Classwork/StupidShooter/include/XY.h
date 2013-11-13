/******************************************************************************
 * File:               XY.h
 * Author:             Elizabeth Lowry
 * Date Created:       October 29, 2013
 * Description:        Struct representing a point or vector on the Cartesian
 *                      plane.
 * Last Modified:      October 29, 2013
 * Last Modification:  Moved code out of Globals.h.
 ******************************************************************************/

#ifndef _XY_H_
#define _XY_H_

// A pair of X and Y coordinates
template < typename T >
struct XY
{
    T x;
    T y;

    XY( const T& a_roT );
    XY( const T& a_roTx, const T& a_roTy );

    template < typename U >
    operator XY< U >() const;

    template< typename U >
    XY& operator=( const XY< U >& ac_roNew );
};

// Return the distance betweed two coordinate pairs
template < typename T, typename U >
double Hypotenuse( const XY< T >& a_roPointA, const XY< U >& a_roPointB );

// typedef the most-used versions of the template
typedef XY<int> IntXY;
typedef XY<float> FloatXY;

// default coordinates
const IntXY XY_ZERO( 0 );
const IntXY XY_ONE( 1 );

#include "inline/XY.inl"

#endif  // _XY_H_