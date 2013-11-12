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

// Provide an equal_to comparison functor for cases when we want to hash
// pointers to hashable objects by their targets instead of using the standard
// equal_to<T*> implementation.
struct HashablePointerEqualTo : public std::equal_to< Hashable* >
{
    bool operator()( const Hashable* const ac_cpoFirst,
                     const Hashable* const ac_cpoSecond ) const;
};

// Provide a hash functor for cases where we want to hash pointers to hashable
// objects by their targets instead of using the standard hash<T*>
// implementation.
struct HashablePointerHash : public std::hash< Hashable* >
{
    std::size_t operator()( const Hashable* const ac_cpoHashable) const;
};

// Provide a less comparison functor for cases where we want to sort pointers
// to hashable objects by their targets instead of using the standard less<T*>
// implementation.
struct HashablePointerLess : public std::less< Hashable* >
{
    bool operator()( const Hashable* const ac_cpoFirst,
                     const Hashable* const ac_cpoSecond ) const;
};

#include "inline/Hashable.inl"

#endif  // _HASHABLE_H_