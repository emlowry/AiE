/******************************************************************************
 * File:               VectorBase.inl
 * Author:             Elizabeth Lowry
 * Date Created:       November 25, 2013
 * Description:        Inline and other function implementations for VectorBase.
 * Last Modified:      December 10, 2013
 * Last Modification:  Debugging.
 ******************************************************************************/

#ifndef VECTOR_BASE__INL
#define VECTOR_BASE__INL

#include "Declarations/Functions.h"
// #include <type_traits>  // for std::is_whateverable checks
#include <cassert>  // for assert
#include <utility>  // for std::forward and std::move

namespace Math
{

// Default destructor doesn't need to do anything
template< typename T, unsigned int N, bool t_bIsRow >
inline VectorBase< T, N, t_bIsRow >::~VectorBase() {}

// Constructors mostly call parent class constructors
template< typename T, unsigned int N, bool t_bIsRow >
inline VectorBase< T, N, t_bIsRow >::VectorBase() : BaseType() {}
template< typename T, unsigned int N, bool t_bIsRow >
inline VectorBase< T, N, t_bIsRow >::VectorBase( const BaseType& ac_roMatrix )
    : BaseType( ac_roMatrix ) {}
template< typename T, unsigned int N, bool t_bIsRow >
inline VectorBase< T, N, t_bIsRow >::VectorBase( const VectorBase& ac_roVector )
    : BaseType( ac_roVector ) {}
template< typename T, unsigned int N, bool t_bIsRow >
inline VectorBase< T, N, t_bIsRow >::VectorBase( BaseType&& a_rroMatrix )
    : BaseType( std::forward< BaseType >( a_rroMatrix ) ) {}
template< typename T, unsigned int N, bool t_bIsRow >
inline VectorBase< T, N, t_bIsRow >::VectorBase( VectorBase&& a_rroVector )
    : BaseType( std::forward< VectorBase >( a_rroVector ) ) {}
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U, unsigned int P, unsigned int Q >
inline VectorBase< T, N, t_bIsRow >::
    VectorBase( const MatrixBase< U, P, Q >& ac_roMatrix, const T& ac_rFill )
    : BaseType( ac_roMatrix, ac_rFill ) {}
template< typename T, unsigned int N, bool t_bIsRow >
template< unsigned int P, unsigned int Q >
inline VectorBase< T, N, t_bIsRow >::
    VectorBase( MatrixBase< T, P, Q >&& a_rroMatrix, const T& ac_rFill )
    : BaseType( std::forward< MatrixBase< T, P, Q > >( a_rroMatrix ), ac_rFill ) {}
template< typename T, unsigned int N, bool t_bIsRow >
inline VectorBase< T, N, t_bIsRow >::VectorBase( const T& ac_rFill )
    : BaseType( ac_rFill ) {}
template< typename T, unsigned int N, bool t_bIsRow >
inline VectorBase< T, N, t_bIsRow >::VectorBase(const T* const ac_cpData,
                                                const unsigned int ac_uiSize,
                                                const T& ac_rFill )
    : BaseType( ac_cpData, ac_uiSize, ac_rFill ) {}
template< typename T, unsigned int N, bool t_bIsRow >
inline VectorBase< T, N, t_bIsRow >::
    VectorBase( const T (&ac_raData)[ N ] )
    : BaseType( ac_raData ) {}

// Copy construct from a different kind of vector
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U, unsigned int Q, bool t_bOtherIsRow >
inline VectorBase< T, N, t_bIsRow >::
    VectorBase( const VectorBase< U, Q, t_bOtherIsRow >& ac_roVector,
                const T& ac_rFill )
{/*
    if( !std::is_copy_assignable< T >::value )
    {
        throw exception("Non-copy-assignable type");
    }
    if( !std::is_convertible< U, T >:: value )
    {
        throw exception("Non-convertable input type");
    } /**/
    for( unsigned int i = 0; i < N; ++i )
    {
        At(i) = ( i < Q ) ? (T)( ac_roVector[i] ) : ac_rFill;
    }
}

// Copy assign from a different type of vector
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U, unsigned int Q, bool t_bOtherIsRow >
inline VectorBase< T, N, t_bIsRow >& VectorBase< T, N, t_bIsRow >::
    operator=( const VectorBase< U, Q, t_bOtherIsRow >& ac_roVector )
{/*
    if( !std::is_copy_assignable< T >::value )
    {
        throw exception("Non-copy-assignable type");
    }
    if( !std::is_convertible< U, T >:: value )
    {
        throw exception("Non-convertable input type");
    } /**/
    if( Address() != ac_roVector.Address() )
    {
        for( unsigned int i = 0; i < N && i < Q; ++i )
        {
            At(i) = (T)( ac_roVector[i] );
        }
    }
    return *this;
}

// Move construct from a different kind of vector
template< typename T, unsigned int N, bool t_bIsRow >
template< unsigned int Q, bool t_bOtherIsRow >
inline VectorBase< T, N, t_bIsRow >::
    VectorBase( VectorBase< T, Q, t_bOtherIsRow >&& a_rroVector,
                const T& ac_rFill )
{/*
    if( !std::is_move_assignable< T >::value )
    {
        throw exception("Non-move-assignable type");
    } /**/
    for( unsigned int i = 0; i < N; ++i )
    {
        At(i) = ( i < Q ) ? std::move( a_rroVector[i] ) : ac_rFill;
    }
}

// Move assign from a different type of vector
template< typename T, unsigned int N, bool t_bIsRow >
template< unsigned int Q, bool t_bOtherIsRow >
inline VectorBase< T, N, t_bIsRow >& VectorBase< T, N, t_bIsRow >::
    operator=( VectorBase< T, Q, t_bOtherIsRow >&& a_rroVector )
{/*
    if( !std::is_move_assignable< T >::value )
    {
        throw exception("Non-move-assignable type");
    } /**/
    if( Address() != a_rroVector.Address() )
    {
        for( unsigned int i = 0; i < N && i < Q; ++i )
        {
            At(i) = std::move( a_rroVector[i] );
        }
    }
    return *this;
}

// Vector element access
template< typename T, unsigned int N, bool t_bIsRow >
inline T& VectorBase< T, N, t_bIsRow >::At( unsigned int a_uiIndex )
{
    assert( a_uiIndex < N );
    return ( t_bIsRow ? m_aaData[1][a_uiIndex] : m_aaData[a_uiIndex][1] );
}
template< typename T, unsigned int N, bool t_bIsRow >
inline T& VectorBase< T, N, t_bIsRow >::operator[]( unsigned int a_uiIndex )
{
    return At( a_uiIndex );
}
template< typename T, unsigned int N, bool t_bIsRow >
inline const T& VectorBase< T, N, t_bIsRow >::At( unsigned int a_uiIndex ) const
{
    assert( a_uiIndex < N );
    return ( t_bIsRow ? m_aaData[1][a_uiIndex] : m_aaData[a_uiIndex][1] );
}
template< typename T, unsigned int N, bool t_bIsRow >
inline const T& VectorBase< T, N, t_bIsRow >::
    operator[]( unsigned int a_uiIndex ) const
{
    return At( a_uiIndex );
}

// Get this vector as a row/column vector
template< typename T, unsigned int N, bool t_bIsRow >
inline typename VectorBase< T, N, t_bIsRow >::ColumnVectorType
    VectorBase< T, N, t_bIsRow >::Column() const
{
    return ( t_bIsRow ? ColumnVectorType( *this ) : *this );
}
template< typename T, unsigned int N, bool t_bIsRow >
inline typename VectorBase< T, N, t_bIsRow >::RowVectorType
    VectorBase< T, N, t_bIsRow >::Row() const
{
    return ( t_bIsRow ? *this : RowVectorType( *this ) );
}

// Make row vector from column vector and vice-versa
template< typename T, unsigned int N, bool t_bIsRow >
inline typename VectorBase< T, N, t_bIsRow >::TransposeType
    VectorBase< T, N, t_bIsRow >::Transpose() const
{
    return TransposeType( *this );
}

// Shift elements by the given number of places
template< typename T, unsigned int N, bool t_bIsRow >
inline void VectorBase< T, N, t_bIsRow >::Shift( int a_iPlaces )
{
    VectorBase oCopy(*this);
    for( unsigned int i = 0; i < N; ++i )
    {
        At( Scroll<int>( i + a_iPlaces, N ) ) = oCopy[i];
    }
}

// Get a smaller vector by removing an element
template< typename T, unsigned int N, bool t_bIsRow >
VectorBase< T, ( N > 0 ? N-1 : 0 ), t_bIsRow > VectorBase< T, N, t_bIsRow >::
    MinusElement( unsigned int a_uiIndex ) const
{
    if( N == 0 )
    {
        throw( std::out_of_range( "Cannot remove element if there are none" ) );
    }
    Vector oCopy(*this);
    oCopy.Shift( -1 - a_uiIndex );
    Vector< T, ( N > 0 ? N-1 : 0 ), t_bIsRow > oResult( oCopy );
    oResult.Shift( a_uiIndex );
    return oResult;
}

}   // namespace Math

#endif VECTOR_BASE__INL
