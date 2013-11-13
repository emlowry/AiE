/******************************************************************************
 * File:               CloneSet.inl
 * Author:             Elizabeth Lowry
 * Date Created:       November 12, 2013
 * Description:        Inline function implementations for CloneSet.h.
 * Last Modified:      November 12, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef _CLONE__CLONE_SET_INL_
#define _CLONE__CLONE_SET_INL_

// Destructor deallocates contents
template< typename T >
inline CloneSet< T >::~CloneSet()
{
    Clear();
}

// these methods just call the methods of the protected base type
template< typename T >
inline typename CloneSet< T >::Index CloneSet< T >::Begin() const
{
    return set_type::begin();
}
template< typename T >
inline typename CloneSet< T >::Index CloneSet< T >::End() const
{
    return set_type::end();
}
template< typename T >
inline bool CloneSet< T >::IsEmpty() const
{
    return set_type::empty();
}
template< typename T >
inline std::size_t CloneSet< T >::Size() const
{
    return set_type::size();
}

// return a reference to the element pointed to by the iterator.
// Behavior is undefined for an invalid position - it'll probably throw up.
template< typename T >
inline T& CloneSet< T >::At( Index a_oIndex )
{
    return *( const_cast< T* >( *a_oIndex ) );
}
template< typename T >
inline const T& CloneSet< T >::At( Index a_oIndex ) const
{
    return *( const_cast< T* >( *a_oIndex ) );
}
template< typename T >
inline T& CloneSet< T >::operator[]( Index a_oIndex )
{
    return At( a_oIndex );
}
template< typename T >
inline const T& CloneSet< T >::operator[]( Index a_oIndex ) const
{
    return At( a_oIndex );
}

// remove and deallocate all elements
template< typename T >
inline void CloneSet< T >::Clear()
{
    while( !IsEmpty() )
    {
        Erase( Begin() );
    }
}

// returns true if the set contains a pointer to an object equivalent to the
// given one.
template< typename T >
inline bool CloneSet< T >::Contains( const T& ac_roValue ) const
{
    return ( End() != Find( ac_roValue ) );
}

// return an iterator pointing to the stored pointer to the cloned object
// equivalent to the parameter
template< typename T >
inline typename CloneSet< T >::Index CloneSet< T >::Find( const T& ac_roValue ) const
{
    return set_type::find( const_cast< T* >( &ac_roValue ) );
}

// find the object at the given position or equivalent to the given object,
// remove it from the set, and deallocate it.
template< typename T >
inline void CloneSet< T >::Erase( Index a_oIndex )
{
    if( End() != a_oIndex )
    {
        T* poValue = &At( a_oIndex );
        set_type::erase( a_oIndex );
        delete poValue;
    }
}
template< typename T >
inline void CloneSet< T >::Erase( const T& ac_roValue )
{
    T* poValue = Remove( ac_roValue );
    if( nullptr != poValue )
    {
        delete poValue;
    }
}

// find the object at the given position or equivalent to the given object,
// remove it from the set, and return a pointer to it.
template< typename T >
inline T* CloneSet< T >::Remove( Index a_oIndex )
{
    if( End() == a_oIndex )
    {
        return nullptr;
    }
    T* poValue = &At( a_oIndex );
    set_type::erase( a_oIndex );
    return poValue;
}
template< typename T >
inline T* CloneSet< T >::Remove( const T& ac_roValue )
{
    Index oIndex = Find( ac_roValue );
    return Remove( oIndex );
}

// add a clone of the given object to the set
template< typename T >
inline T& CloneSet< T >::Insert( const T& ac_roValue )
{
    Index oIndex = Find( ac_roValue );
    if( End() == oIndex )
    {
        std::pair< set_type::iterator, bool> oPair =
            set_type::insert( ac_roValue.Clone() );
        return At( oPair.first );
    }
    return At( oIndex );
}
template< typename T >
inline T& CloneSet< T >::operator[]( const T& ac_roValue )
{
    return Insert( ac_roValue );
}

#endif  // _CLONE__CLONE_SET_INL_
