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

#include <utility>  // for std::forward

// constructors
template< typename T, typename Less >
inline ReferenceSet< T, Less >::ReferenceSet( const ReferenceSet& ac_roSet )
    : set_type( ac_roSet ) {}
template< typename T, typename Less >
inline ReferenceSet< T, Less >::ReferenceSet( ReferenceSet&& a_rroSet )
    : set_type( std::forward< ReferenceSet >( a_rroSet ) ) {}

// assignment operators
template< typename T, typename Less >
inline ReferenceSet< T, Less >&
    ReferenceSet< T, Less >::operator=( const ReferenceSet& ac_roSet )
{
    set_type::operator=( ac_roSet );
    return *this;
}
template< typename T, typename Less >
inline ReferenceSet< T, Less >&
    ReferenceSet< T, Less >::operator=( ReferenceSet&& a_rroSet )
{
    set_type::operator=( std::forward< ReferenceSet >( a_rroSet ) );
    return *this;
}

// these methods just call the methods of the protected base type
template< typename T, typename Less >
inline typename ReferenceSet< T, Less >::Index
    ReferenceSet< T, Less >::Begin() const
{
    return set_type::begin();
}
template< typename T, typename Less >
inline void ReferenceSet< T, Less >::Clear()
{
    set_type::clear();
}
template< typename T, typename Less >
inline typename ReferenceSet< T, Less >::Index
    ReferenceSet< T, Less >::End() const
{
    return set_type::end();
}
template< typename T, typename Less >
inline bool ReferenceSet< T, Less >::IsEmpty() const
{
    return set_type::empty();
}
template< typename T, typename Less >
inline std::size_t ReferenceSet< T, Less >::Size() const
{
    return set_type::size();
}

//
// methods with actual implementation
//

// return a reference to the element pointed to by the iterator.
// Behavior is undefined for an invalid position - it'll probably throw up.
template< typename T, typename Less >
inline T& ReferenceSet< T, Less >::At( Index a_oIndex )
{
    return *( const_cast< T* >( *a_oIndex ) );
}
template< typename T, typename Less >
inline const T& ReferenceSet< T, Less >::At( Index a_oIndex ) const
{
    return *( const_cast< T* >( *a_oIndex ) );
}
template< typename T, typename Less >
inline T& ReferenceSet< T, Less >::operator[]( Index a_oIndex )
{
    return At( a_oIndex );
}
template< typename T, typename Less >
inline const T& ReferenceSet< T, Less >::operator[]( Index a_oIndex ) const
{
    return At( a_oIndex );
}

// find the object at the given position or equivalent to the given object,
// remove it from the set, and deallocate it.
template< typename T, typename Less >
inline void ReferenceSet< T, Less >::Erase( Index a_oIndex )
{
    set_type::erase( a_oIndex );
}
template< typename T, typename Less >
inline void ReferenceSet< T, Less >::Erase( const T& ac_roValue )
{
    Erase( Find( ac_roValue ) );
}

// return an iterator pointing to the stored pointer to the cloned object
// equivalent to the parameter.
template< typename T, typename Less >
inline typename ReferenceSet< T, Less >::Index
    ReferenceSet< T, Less >::Find( const T& ac_roValue ) const
{
    return set_type::find( const_cast< T* >( &ac_roValue ) );
}

// add a pointer to the given object to the set, if an equivalent element is
// not present, and return a reference to the equivalent element in the set
// after the insertion.
template< typename T, typename Less >
inline T& ReferenceSet< T, Less >::Insert( const T& ac_roValue )
{
    Index oIndex = Find( ac_roValue );
    if( End() == oIndex )
    {
        std::pair< set_type::iterator, bool> oPair =
            set_type::insert( const_cast< T* >( &ac_roValue ) );
        return At( oPair.first );
    }
    return At( oIndex );
}
template< typename T, typename Less >
inline T& ReferenceSet< T, Less >::operator[]( const T& ac_roValue )
{
    return Insert( ac_roValue );
}

#endif  // _REFERENCE_SET_INL_
