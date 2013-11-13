/******************************************************************************
 * File:               CloneSet.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 12, 2013
 * Description:        Set implementation that stores pointers to clones instead
 *                      of storing copies.  Assumes the template parameter type
 *                      has Cloneable as a base class.
 * Last Modified:      November 12, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef _CLONE__CLONE_SET_H_
#define _CLONE__CLONE_SET_H_

#include "DeepOperators.h"
#include <set>

template< typename T >
class CloneSet : private std::set< T*, DeepLess< T > >
{
protected:

    // simplify typing
    typedef std::set< T*, DeepLess< T > > set_type;

public:

    // make available to users so they can iterate
    typedef typename set_type::const_iterator Index;

    // deallocate contents
    ~CloneSet();

    // these methods just call the methods of the protected base type
    Index Begin() const;
    Index End() const;
    bool IsEmpty() const;
    std::size_t Size() const;

    //
    // methods with actual implementation
    //
    
    // return a reference to the element pointed to by the iterator.
    // Behavior is undefined for an invalid position - it'll probably throw up.
    T& At( Index a_oIndex );
    const T& At( Index a_oIndex ) const;

    // remove and deallocate all elements.
    void Clear();

    // find the object at the given position or equivalent to the given object,
    // remove it from the set, and deallocate it.
    void Erase( Index a_oIndex );
    void Erase( const T& ac_roValue );

    // returns true if the set contains a pointer to an object equivalent to the
    // given one
    bool Contains( const T& ac_roValue ) const;

    // return an iterator pointing to the stored pointer to the cloned object
    // equivalent to the parameter.
    Index Find( const T& ac_roValue ) const;

    // find the object at the given position or equivalent to the given object,
    // remove it from the set, and return a pointer to it.
    T* Remove( Index a_oIndex );
    T* Remove( const T& ac_roValue );   // return null if not present

    // add a clone of the given object to the set, if an equivalent element is
    // not present, and return a reference to the equivalent element in the set
    // after the insertion.
    T& Insert( const T& ac_roValue );

    // same behavior as Insert
    T& operator[]( const T& ac_roValue );

    // same behavior as At
    T& operator[]( Index a_oIndex );
    const T& operator[]( Index a_oIndex ) const;
};

#include "inline/clone/CloneSet.inl"

#endif  // _CLONE__CLONE_SET_H_
