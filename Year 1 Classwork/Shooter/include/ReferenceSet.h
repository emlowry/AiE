/******************************************************************************
 * File:               ReferenceSet.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 12, 2013
 * Description:        Set implementation that stores pointers but only accepts
 *                      or returns them in the form of references - in other
 *                      words, it doesn't own the memory it points to and isn't
 *                      responsible for deallocating it.
 * Last Modified:      November 12, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef _REFERENCE_SET_H_
#define _REFERENCE_SET_H_

#include "DeepOperators.h"
#include <set>

template< typename T >
class ReferenceSet : protected set< T*, DeepLess >
{
protected:

    // simplify typing
    typedef std::set< T*, DeepLess< T > > set_type;

public:

    ReferenceSet();
    ReferenceSet( const ReferenceSet& ac_roSet );
    ReferenceSet( ReferenceSet&& a_rroSet );
    ReferenceSet& operator=( const ReferenceSet& ac_roSet );
    ReferenceSet& operator=( ReferenceSet&& ac_roSet );

    // make available to users so they can iterate
    typedef set_type::const_iterator Index;

    // these methods just call the methods of the protected base type
    Index Begin() const;
    void Clear();
    Index End() const;
    bool IsEmpty() const;
    std::size_t Size() const;

    //
    // methods with actual implementation
    //

    // return an iterator pointing to the stored pointer to the cloned object
    // equivalent to the parameter.
    Index Find( const T& ac_roValue ) const;

    // find the object at the given position or equivalent to the given object,
    // remove it from the set, and deallocate it.
    void Erase( Index a_oIndex );
    void Erase( const T& ac_roValue );

    // add a pointer to the given object to the set, if an equivalent element is
    // not present, and return a reference to the equivalent element in the set
    // after the insertion.
    T& Insert( const T& ac_roValue );

    // same behavior as Insert
    T& operator[]( const T& ac_roValue );

    // return a reference to the element pointed to by the iterator.
    // Behavior is undefined for an invalid position - it'll probably throw up.
    T& operator[]( Index a_oIndex );
    const T& operator[]( Index a_oIndex ) const;

}

#include "inline/ReferenceSet.inl"

#endif