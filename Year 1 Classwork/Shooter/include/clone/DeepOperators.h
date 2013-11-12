/******************************************************************************
 * File:               DeepOperations.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 7, 2013
 * Description:        Derived classes of various std structs for performing
 *                      operations on pointers based on their targets instead of
 *                      on their own values.
 * Last Modified:      November 7, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef _DEEP_OPERATIONS_H_
#define _DEEP_OPERATIONS_H_

#include <functional>

// Equality
template< typename T >
struct DeepEqualTo : public virtual std::equal_to< T* >
{
    bool operator()( const T* const ac_cpoLeft,
                     const T* const ac_cpoRight ) const;
};
template< typename T >
struct DeepEqualTo< const T > : public virtual std::equal_to< const T* >
{
    bool operator()( const T* const ac_cpoLeft,
                     const T* const ac_cpoRight ) const;
};

// Hash
template< typename T >
struct DeepHash : public virtual std::hash< T* >
{
    bool operator()( const T* const ac_cpoT ) const;
};
template< typename T >
struct DeepHash< const T > : public virtual std::hash< const T* >
{
    bool operator()( const T* const ac_cpoT ) const;
};

// Less-than comparison
template< typename T >
struct DeepLess : public virtual std::less< T* >
{
    bool operator()( const T* const ac_cpoLeft,
                     const T* const ac_cpoRight ) const;
};
template< typename T >
struct DeepLess< const T > : public virtual std::less< const T* >
{
    bool operator()( const T* const ac_cpoLeft,
                     const T* const ac_cpoRight ) const;
};

#endif  // _DEEP_OPERATIONS_H_