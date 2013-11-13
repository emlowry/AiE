/******************************************************************************
 * File:               DoubleLookup.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 12, 2013
 * Description:        Allows you to store associations between objects of two
 *                      different types and to look up associations for an
 *                      object of either type.  Does not own the objects it
 *                      stores and is not responsible for deallocating them.
 * Last Modified:      November 12, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef _DOUBLE_LOOKUP_H_
#define _DOUBLE_LOOKUP_H_

#include "ReferenceSet.h"
#include <unordered_map>

// save typing long template parameter lists over and over...
#define GENERAL_TYPENAMES typename T, typename U, \
                          typename LessT, typename LessU, \
                          typename HashT, typename HashU, \
                          typename EqualToT, typename EqualToU
#define SPECIALIZED_TYPENAMES typename T, typename LessT, \
                              typename HashT, typename EqualToT
#define GENERAL_PARAMS T, U, LessT, LessU, HashT, HashU, EqualToT, EqualToU
#define SPECIALIZED_PARAMS T, T, LessT, LessT, HashT, HashT, EqualToT, EqualToT

// Stores associations
template< typename T, typename U,
          typename LessT = std::less< T* >, typename LessU = std::less< U* >,
          typename HashT = std::hash< T* >, typename HashU = std::hash< U* >,
          typename EqualToT = std::equal_to< T* >,
          typename EqualToU = std::equal_to< U* > >
class DoubleLookup
{
public:

    // simplify typing
    typedef ReferenceSet< U, LessU > ForwardSet;
    typedef typename ForwardSet::Index ForwardIndex;
    typedef ReferenceSet< T, LessT > ReverseSet;
    typedef typename ReverseSet::Index ReverseIndex;
    
    // get sets of associated objects
    ForwardSet& At( const T& ac_roKey );
    const ForwardSet& At( const T& ac_roKey ) const;
    ReverseSet& At( const U& ac_roKey );
    const ReverseSet& At( const U& ac_roKey ) const;
    ForwardSet& operator[]( const T& ac_roKey );
    const ForwardSet& operator[]( const T& ac_roKey ) const;
    ReverseSet& operator[]( const U& ac_roKey );
    const ReverseSet& operator[]( const U& ac_roKey ) const;

    // checks
    bool AreLinked( const T& ac_roX, const U& ac_roY ) const;
    std::size_t Count( const T& ac_roKey ) const;
    std::size_t Count( const U& ac_roKey ) const;
    bool IsEmpty() const;

    // update associations
    void Clear();
    void Erase( const T& ac_roKey );
    void Erase( const U& ac_roKey );
    void Erase( const T& ac_roX, const U& ac_roY );
    void Insert( const T& ac_roX, const U& ac_roY );

protected:

    typedef std::unordered_map< T*, ForwardSet, HashT, EqualToT > ForwardMap;
    typedef std::unordered_map< U*, ReverseSet, HashU, EqualToU > ReverseMap;

    ForwardMap m_oForwardLookup;
    ReverseMap m_oReverseLookup;

};

// Specialized implementation for objects of the same type
template< SPECIALIZED_TYPENAMES >
class DoubleLookup< SPECIALIZED_PARAMS >
{
public:

    // simplify typing
    typedef ReferenceSet< T, LessT > Set;
    typedef typename Set::Index Index;
    
    // get sets of associated objects
    Set& At( const T& ac_roKey );
    const Set& At( const T& ac_roKey ) const;
    Set& operator[]( const T& ac_roKey );
    const Set& operator[]( const T& ac_roKey ) const;

    // checks
    bool AreLinked( const T& ac_roX, const T& ac_roY ) const;
    std::size_t Count( const T& ac_roKey ) const;
    bool IsEmpty() const;

    // update associations
    void Clear();
    void Erase( const T& ac_roKey );
    void Erase( const T& ac_roX, const T& ac_roY );
    void Insert( const T& ac_roX, const T& ac_roY );

protected:

    typedef std::unordered_map< T*, Set, HashT, EqualToT > Map;

    Map m_oLookup;

};

#include "inline/DoubleLookup.inl"

// clean up macros
#undef GENERAL_TYPENAMES
#undef SPECIALIZED_TYPENAMES
#undef GENERAL_PARAMS
#undef SPECIALIZED_PARAMS

#endif  // _DOUBLE_LOOKUP_H_
