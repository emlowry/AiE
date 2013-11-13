/******************************************************************************
 * File:               ReferenceSet.inl
 * Author:             Elizabeth Lowry
 * Date Created:       November 12, 2013
 * Description:        Inline function definitions for ReferenceSet.h.
 * Last Modified:      November 12, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef _REFERENCE_SET_INL_
#define _REFERENCE_SET_INL_

// TODO: constructors

// these methods just call the methods of the protected base type
template< typename T >
ReferenceSet< T >::Index ReferenceSet< T >::Begin() const
{
    return set_type::begin();
}
template< typename T >
void ReferenceSet< T >::Clear()
{
    set_type::clear();
}
template< typename T >
ReferenceSet< T >::Index ReferenceSet< T >::End() const
{
    return set_type::end();
}
template< typename T >
bool ReferenceSet< T >::IsEmpty() const
{
    return set_type::empty();
}
template< typename T >
std::size_t ReferenceSet< T >::Size() const
{
    return set_type::size();
}

//
// methods with actual implementation
//

// return an iterator pointing to the stored pointer to the cloned object
// equivalent to the parameter.
template< typename T >
Index Find( const T& ac_roValue ) const
{
    return set_type::find( const_cast< T* >( &ac_roValue ) );
}

// find the object at the given position or equivalent to the given object,
// remove it from the set, and deallocate it.
template< typename T >
void Erase( Index a_oIndex )
{
    set_type::erase( a_oIndex );
}
template< typename T >
void Erase( const T& ac_roValue )
{
    Erase( Find( ac_roValue ) );
}

// add a pointer to the given object to the set, if an equivalent element is
// not present, and return a reference to the equivalent element in the set
// after the insertion.
template< typename T >
T& Insert( const T& ac_roValue )
{
    Index oIndex = Find( ac_roValue );
    if( End() == oIndex )
    {
        std::pair< set_type::iterator, bool> oPair =
            set_type::insert( &ac_roValue );
        return *( const_cast< T* >( *( oPair.first ) ) );
    }
    return *( const_cast< T* >( *oIndex ) );
}

// same behavior as Insert
template< typename T >
T& operator[]( const T& ac_roValue )
{
    return Insert( ac_roValue );
}

// return a reference to the element pointed to by the iterator.
// Behavior is undefined for an invalid position - it'll probably throw up.
template< typename T >
T& operator[]( Index a_oIndex )
{
    return *( const_cast< T* >( *a_oIndex ) );
}
template< typename T >
const T& operator[]( Index a_oIndex ) const
{
    return *( const_cast< T* >( *a_oIndex ) );
}

#endif  // _REFERENCE_SET_INL_
