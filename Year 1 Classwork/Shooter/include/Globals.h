/******************************************************************************
 * File:               Globals.h
 * Author:             Elizabeth Lowry
 * Date Created:       September 30, 2013
 * Description:        Structs, enums, constants, and static functions used in
 *                       multiple locations throughout the project.
 * Last Modified:      October 28, 2013
 * Last Modification:  Added Hashable class.
 ******************************************************************************/

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <cmath>
#include <functional>

struct Hashable
{
    virtual std::size_t Hash() const = 0;
    inline std::size_t operator<( const Hashable& ac_roHashable ) const
    { return Hash() < ac_roHashable.Hash(); }
    inline std::size_t operator>( const Hashable& ac_roHashable ) const
    { return Hash() > ac_roHashable.Hash(); }
    inline std::size_t operator<=( const Hashable& ac_roHashable ) const
    { return Hash() <= ac_roHashable.Hash(); }
    inline std::size_t operator>=( const Hashable& ac_roHashable ) const
    { return Hash() >= ac_roHashable.Hash(); }
    inline std::size_t operator==( const Hashable& ac_roHashable ) const
    { return Hash() == ac_roHashable.Hash(); }
    inline std::size_t operator!=( const Hashable& ac_roHashable ) const
    { return Hash() != ac_roHashable.Hash(); }
};
template<>
struct std::hash< Hashable >
{
    inline std::size_t operator()( const Hashable& ac_roHashable ) const
    { return ac_roHashable.Hash(); }
};
struct HashablePointerHash : public std::hash< Hashable* >
{
    inline std::size_t operator()( const Hashable* const ac_cpoHashable) const
    { return ( nullptr == ac_cpoHashable ) ? 0 : ac_cpoHashable->Hash(); }
};
struct HashablePointerLess : public std::less< Hashable* >
{
    inline bool operator()( const Hashable* const ac_cpoFirst,
                            const Hashable* const ac_cpoSecond ) const
    {
        return ( nullptr == ac_cpoFirst) ? ( nullptr == ac_cpoSecond )
                : ( nullptr == ac_cpoSecond ) ? false
                : ( *ac_cpoFirst < *ac_cpoSecond );
    }
};

template <typename T>
struct XY
{
    T x;
    T y;

    XY( const T& a_roT ) : x(a_roT), y(a_roT) {}
    XY( const T& a_roTx, const T& a_roTy ) : x(a_roTx), y(a_roTy) {}

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

const IntXY XY_ZERO( 0 );
const IntXY XY_ONE( 1 );

#endif  // _GLOBALS_H_