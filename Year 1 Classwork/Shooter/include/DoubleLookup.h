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

#include "DeepOperators.h"
#include "ReferenceSet.h"
#include <unordered_map>

// Stores associations
template< typename T, typename U >
class DoubleLookup
{
public:
    
    bool AreLinked( const T& ac_roX, const U& ac_roY ) const;
    ReferenceSet< U > At( const T& ac_roKey ) const;
    ReferenceSet< T > At( const U& ac_roKey ) const;
    void Clear();
    bool Count( const T& ac_roKey ) const;
    bool Count( const U& ac_roKey ) const;
    void Erase( const T& ac_roKey ) const;
    void Erase( const U& ac_roKey ) const;
    bool Insert( const T& ac_roX, const U& ac_roY );
    bool IsEmpty() const;

protected:

    typedef std::unordered_map< T*, ReferenceSet< U >,
                                DeepHash< T >, DeepEqualTo< T > > ForwardMap;
    typedef std::unordered_map< U*, ReferenceSet< T >,
                                DeepHash< U >, DeepEqualTo< U > > ReverseMap;

    ForwardMap m_oForwardLookup;
    ReverseMap m_oReverseLookup;

};

// Specialized implementation for objects of the same type
template< typename T >
class DoubleLookup< T, T >
{
public:

    bool AreLinked( const T& ac_roX, const T& ac_roY ) const;
    ReferenceSet< T > At( const T& ac_roKey ) const;
    void Clear();
    bool Count( const T& ac_roKey ) const;
    void Erase( const T& ac_roKey ) const;
    bool Insert( const T& ac_roX, const T& ac_roY );
    bool IsEmpty;

protected:

    typedef std::unordered_map< T*, ReferenceSet< T >,
                                DeepHash< T >, DeepEqualTo< T > > Map;

    Map m_oLookup;
};

#include "inline/DoubleLookup.inl"

#endif  // _DOUBLE_LOOKUP_H_
