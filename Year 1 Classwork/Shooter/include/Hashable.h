/******************************************************************************
 * File:               Hashable.h
 * Author:             Elizabeth Lowry
 * Date Created:       October 29, 2013
 * Description:        Abstract parent struct for objects easily stored in
 *                      hash-based containers, like unordered_map.
 * Last Modified:      October 29, 2013
 * Last Modification:  Moved code out of Globals.h.
 ******************************************************************************/

#ifndef _HASHABLE_H_
#define _HASHABLE_H_

#include <functional>

// parent for objects to use with hash-reliant containers like unordered_map
struct Hashable
{
    virtual std::size_t Hash() const = 0;
    std::size_t operator<( const Hashable& ac_roHashable ) const;
    std::size_t operator>( const Hashable& ac_roHashable ) const;
    std::size_t operator<=( const Hashable& ac_roHashable ) const;
    std::size_t operator>=( const Hashable& ac_roHashable ) const;
    std::size_t operator==( const Hashable& ac_roHashable ) const;
    std::size_t operator!=( const Hashable& ac_roHashable ) const;
};

// Redefine std::hash functor for hashable objects
template<>
struct std::hash< Hashable >
{
    std::size_t operator()( const Hashable& ac_roHashable ) const;
};
template<>
struct std::hash< const Hashable >
{
    std::size_t operator()( const Hashable& ac_roHashable ) const;
};

#include "inline/Hashable.inl"

#endif  // _HASHABLE_H_