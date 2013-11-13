/******************************************************************************
 * File:               DoubleLookup.inl
 * Author:             Elizabeth Lowry
 * Date Created:       November 12, 2013
 * Description:        Inline and other template function implementations for
 *                      DoubleLookup.h.
 * Last Modified:      November 12, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef _DOUBLE_LOOKUP_INL_
#define _DOUBLE_LOOKUP_INL_

#include <stdexcept>    // for std::out_of_range

//
// Lookup
//
// Returns a copy of the set of objects associated with the given object, if
// there are any, or an empty set if the object isn't there.
//

// generalized case: forward lookup
template< GENERAL_TYPENAMES >
inline typename DoubleLookup< GENERAL_PARAMS >::ForwardSet&
    DoubleLookup< GENERAL_PARAMS >::At( const T& ac_roKey )
{
    if( Count( ac_roKey ) == 0 )
    {
        throw std::out_of_range("Key not present");
    }
    return m_oForwardLookup.at( const_cast< T* >( &ac_roKey ) );
}
template< GENERAL_TYPENAMES >
inline typename DoubleLookup< GENERAL_PARAMS >::ForwardSet&
    DoubleLookup< GENERAL_PARAMS >::operator[]( const T& ac_roKey )
{
    return At( ac_roKey );
}
template< GENERAL_TYPENAMES >
inline const typename DoubleLookup< GENERAL_PARAMS >::ForwardSet&
    DoubleLookup< GENERAL_PARAMS >::At( const T& ac_roKey ) const
{
    if( Count( ac_roKey ) == 0 )
    {
        throw std::out_of_range("Key not present");
    }
    return m_oForwardLookup.at( const_cast< T* >( &ac_roKey ) );
}
template< GENERAL_TYPENAMES >
inline const typename DoubleLookup< GENERAL_PARAMS >::ForwardSet&
    DoubleLookup< GENERAL_PARAMS >::operator[]( const T& ac_roKey ) const
{
    return At( ac_roKey );
}

// generalized case: reverse lookup
template< GENERAL_TYPENAMES >
inline typename DoubleLookup< GENERAL_PARAMS >::ReverseSet&
    DoubleLookup< GENERAL_PARAMS >::At( const U& ac_roKey )
{
    if( Count( ac_roKey ) == 0 )
    {
        throw std::out_of_range("Key not present");
    }
    return m_oReverseLookup.at( const_cast< U* >( &ac_roKey ) );
}
template< GENERAL_TYPENAMES >
inline typename DoubleLookup< GENERAL_PARAMS >::ReverseSet&
    DoubleLookup< GENERAL_PARAMS >::operator[]( const U& ac_roKey )
{
    return At( ac_roKey );
}
template< GENERAL_TYPENAMES >
inline const typename DoubleLookup< GENERAL_PARAMS >::ReverseSet&
    DoubleLookup< GENERAL_PARAMS >::At( const U& ac_roKey ) const
{
    if( Count( ac_roKey ) == 0 )
    {
        throw std::out_of_range("Key not present");
    }
    return m_oReverseLookup.at( const_cast< U* >( &ac_roKey ) );
}
template< GENERAL_TYPENAMES >
inline const typename DoubleLookup< GENERAL_PARAMS >::ReverseSet&
    DoubleLookup< GENERAL_PARAMS >::operator[]( const U& ac_roKey ) const
{
    return At( ac_roKey );
}

// specialized case
template< SPECIALIZED_TYPENAMES >
inline typename DoubleLookup<SPECIALIZED_PARAMS>::Set&
    DoubleLookup< SPECIALIZED_PARAMS >::At( const T& ac_roKey )
{
    if( Count( ac_roKey ) == 0 )
    {
        throw std::out_of_range("Key not present");
    }
    return m_oLookup.at( const_cast< T* >( &ac_roKey ) );
}
template< SPECIALIZED_TYPENAMES >
inline typename DoubleLookup< SPECIALIZED_PARAMS >::Set&
    DoubleLookup< SPECIALIZED_PARAMS >::operator[]( const T& ac_roKey )
{
    return At( ac_roKey );
}
template< SPECIALIZED_TYPENAMES >
inline const typename DoubleLookup<SPECIALIZED_PARAMS>::Set&
    DoubleLookup< SPECIALIZED_PARAMS >::At( const T& ac_roKey ) const
{
    if( Count( ac_roKey ) == 0 )
    {
        throw std::out_of_range("Key not present");
    }
    return m_oLookup.at( const_cast< T* >( &ac_roKey ) );
}
template< SPECIALIZED_TYPENAMES >
inline const typename DoubleLookup< SPECIALIZED_PARAMS >::Set&
    DoubleLookup< SPECIALIZED_PARAMS >::operator[]( const T& ac_roKey ) const
{
    return At( ac_roKey );
}

//
// Checks
//

// Are the two provided objects associated with one another?
// If X links to Y, then Y links to X, so we only need to check one.
template< GENERAL_TYPENAMES >
inline bool DoubleLookup< GENERAL_PARAMS >::AreLinked( const T& ac_roX,
                                                       const U& ac_roY ) const
{
    if( Count( ac_roX ) == 0 )
    {
        return false;
    }
    const ForwardSet& oSet = At( ac_roX );
    return ( oSet.End() != oSet.Find( ac_roY ) );
}
template< SPECIALIZED_TYPENAMES >
inline bool
    DoubleLookup< SPECIALIZED_PARAMS >::AreLinked( const T& ac_roX,
                                                   const T& ac_roY ) const
{
    if( Count( ac_roX ) == 0 )
    {
        return false;
    }
    const Set& oSet = At( ac_roX );
    return ( oSet.End() != oSet.Find( ac_roY ) );
}

// How many objects are associated with the given object?
template< GENERAL_TYPENAMES >
inline std::size_t
    DoubleLookup< GENERAL_PARAMS >::Count( const T& ac_roKey ) const
{
    if( 0 == m_oForwardLookup.count( const_cast< T* >( &ac_roKey ) ) )
    {
        return 0;
    }
    return At( ac_roKey ).Size();
}
template< GENERAL_TYPENAMES >
inline std::size_t
    DoubleLookup< GENERAL_PARAMS >::Count( const U& ac_roKey ) const
{
    if( 0 == m_oReverseLookup.count( const_cast< U* >( &ac_roKey ) ) )
    {
        return 0;
    }
    return At( ac_roKey ).Size();
}
template< SPECIALIZED_TYPENAMES >
inline std::size_t
    DoubleLookup< SPECIALIZED_PARAMS >::Count( const T& ac_roKey ) const
{
    if( 0 == m_oLookup.count( const_cast< T* >( &ac_roKey ) ) )
    {
        return 0;
    }
    return At( ac_roKey ).Size();
}

// Are there no associations at all?
template< GENERAL_TYPENAMES >
inline bool DoubleLookup< GENERAL_PARAMS >::IsEmpty() const
{
    return m_oForwardLookup.empty();
}
template< SPECIALIZED_TYPENAMES >
inline bool DoubleLookup< SPECIALIZED_PARAMS >::IsEmpty() const
{
    return m_oLookup.empty();
}

//
// Modify associations
//

// Remove all associations
template< GENERAL_TYPENAMES >
inline void DoubleLookup< GENERAL_PARAMS >::Clear()
{
    m_oForwardLookup.clear();
    m_oReverseLookup.clear();
}
template< SPECIALIZED_TYPENAMES >
inline void DoubleLookup< SPECIALIZED_PARAMS >::Clear()
{
    m_oLookup.clear();
}

// Remove all associations with the given object
template< GENERAL_TYPENAMES >
inline void DoubleLookup< GENERAL_PARAMS >::Erase( const T& ac_roKey )
{
    if( Count( ac_roKey ) != 0 )
    {
        // get a copy of the set of associations so that the set you iterate
        // through won't be affected by your erasures
        ForwardSet oSet = At( ac_roKey );
        for( ForwardIndex oIndex = oSet.Begin(); oIndex != oSet.End(); ++oIndex )
        {
            Erase( ac_roKey, oSet.At( oIndex ) );
        }
    }
}
template< GENERAL_TYPENAMES >
inline void DoubleLookup< GENERAL_PARAMS >::Erase( const U& ac_roKey )
{
    if( Count( ac_roKey ) != 0 )
    {
        // get a copy of the set of associations so that the set you iterate
        // through won't be affected by your erasures
        ReverseSet oSet = At( ac_roKey );
        for( ReverseIndex oIndex = oSet.Begin(); oIndex != oSet.End(); ++oIndex )
        {
            Erase( oSet.At( oIndex ), ac_roKey );
        }
    }
}
template< SPECIALIZED_TYPENAMES >
inline void DoubleLookup< SPECIALIZED_PARAMS >::Erase( const T& ac_roKey )
{
    if( Count( ac_roKey ) != 0 )
    {
        // get a copy of the set of associations so that the set you iterate
        // through won't be affected by your erasures
        Set oSet = At( ac_roKey );
        for( Index oIndex = oSet.Begin(); oIndex != oSet.End(); ++oIndex )
        {
            Erase( oSet.At( oIndex ), ac_roKey );
        }
    }
}

// Remove an association between two objects
template< typename T, typename U, typename LessT, typename LessU,
          typename HashT, typename HashU, typename EqualToT, typename EqualToU >
void DoubleLookup< T, U, LessT, LessU, HashT, HashU, EqualToT, EqualToU >::
    Erase( const T& ac_roX, const U& ac_roY )
{
    // If the given objects aren't linked to begin with, nothing needs doing.
    if( !AreLinked( ac_roX, ac_roY ) )
    {
        return;
    }

    // Remove the second object from the first's list of associated objects.
    At( ac_roX ).Erase( ac_roY );

    // If the first object's list of associated objects is now empty, remove it.
    if( Count( ac_roX ) == 0 )
    {
        m_oForwardLookup.erase( const_cast< T* >( &ac_roX ) );
    }

    // Remove the first object from the second's list of associated objects.
    At( ac_roY ).Erase( ac_roX );

    // If the second object's list of associated objects is now empty, remove it.
    if( Count( ac_roY ) == 0 )
    {
        m_oReverseLookup.erase( const_cast< U* >( &ac_roY ) );
    }
}
template< typename T, typename LessT, typename HashT, typename EqualToT >
void DoubleLookup< T, T, LessT, LessT, HashT, HashT, EqualToT, EqualToT >::
    Erase( const T& ac_roX, const T& ac_roY )
{
    // If the given objects aren't linked to begin with, nothing needs doing.
    if( !AreLinked( ac_roX, ac_roY ) )
    {
        return;
    }

    // Remove the second object from the first's list of associated objects.
    At( ac_roX ).Erase( ac_roY );

    // If the first object's list of associated objects is now empty, remove it.
    if( Count( ac_roX ) == 0 )
    {
        m_oLookup.erase( const_cast< T* >( &ac_roX ) );
    }

    // If the first and second object are the same by the reckoning of the map's
    // comparator, then dissassociation is complete.
    if( EqualToT( const_cast< T* >( &ac_roX ), const_cast< T* >( &ac_roY ) ) )
    {
        return;
    }

    // Remove the first object from the second's list of associated objects.
    At( ac_roY ).Erase( ac_roX );

    // If the second object's list of associated objects is now empty, remove it.
    if( Count( ac_roY ) == 0 )
    {
        m_oLookup.erase( const_cast< T* >( &ac_roY ) );
    }
}

// Add an association
template< GENERAL_TYPENAMES >
inline void DoubleLookup< GENERAL_PARAMS >::Insert( const T& ac_roX,
                                                    const U& ac_roY )
{
    m_oForwardLookup[ const_cast< T* >( &ac_roX ) ].Insert( ac_roY );
    m_oReverseLookup[ const_cast< U* >( &ac_roY ) ].Insert( ac_roX );
}
template< SPECIALIZED_TYPENAMES >
inline void DoubleLookup< SPECIALIZED_PARAMS >::Insert( const T& ac_roX,
                                                        const T& ac_roY )
{
    m_oLookup[ const_cast< T* >( &ac_roX ) ].Insert( ac_roY );
    if( !( EqualToT( const_cast< T* >( &ac_roX ),
                     const_cast< T* >( &ac_roY ) ) ) )
    {
        m_oLookup[ const_cast< T* >( &ac_roY ) ].Insert( ac_roX );
    }
}

// TODO

#endif  // _DOUBLE_LOOKUP_INL_
