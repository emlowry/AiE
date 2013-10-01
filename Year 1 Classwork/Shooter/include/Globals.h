/******************************************************************************
 * File:               Globals.h
 * Author:             Elizabeth Lowry
 * Date Created:       September 30, 2013
 * Description:        Structs, enums, constants, and static functions used in
 *                       multiple locations throughout the project.
 * Last Modified:      September 30, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <cmath>

template <typename T>
struct XY
{
    T x;
    T y;

    XY( const T& a_roT ) : x(a_roT), y(a_roT) {}

    template <typename U>
    operator XY<U>() const
    {
        return { (U)x, (U)y };
    }
};

typedef XY<int> IntXY;
typedef XY<float> FloatXY;

template <typename T, typename U>
float DistanceBetween( const XY<T>& a_roPointA,
                       const XY<U>& a_roPointB )
{
    return hypot( fdim( a_roPointA.x, a_roPointB.x ),
                  fdim( a_roPointA.y, a_roPointB.y ) );
}

const IntXY XY_ZERO = { 0, 0 };
const IntXY XY_ONE = { 1, 1 };

#endif  // _GLOBALS_H_