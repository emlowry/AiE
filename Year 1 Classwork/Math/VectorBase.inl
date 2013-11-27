/******************************************************************************
 * File:               VectorBase.inl
 * Author:             Elizabeth Lowry
 * Date Created:       November 25, 2013
 * Description:        Inline and other function implementations for VectorBase.
 * Last Modified:      November 25, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef _VECTOR_BASE_INL_
#define _VECTOR_BASE_INL_

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
inline VectorBase< T, N, t_bIsRow >& VectorBase< T, N, t_bIsRow >::
    operator=( const VectorBase& ac_roVector )
{
    return Assign( ac_roVector );
}
template< typename T, unsigned int N, bool t_bIsRow >
inline VectorBase< T, N, t_bIsRow >::VectorBase( BaseType&& a_rroMatrix )
    : BaseType( std::forward( a_rroMatrix ) ) {}
template< typename T, unsigned int N, bool t_bIsRow >
inline VectorBase< T, N, t_bIsRow >::VectorBase( VectorBase&& a_rroVector )
    : BaseType( std::forward( a_rroVector ) ) {}
template< typename T, unsigned int N, bool t_bIsRow >
inline VectorBase< T, N, t_bIsRow >& VectorBase< T, N, t_bIsRow >::
    operator=( VectorBase&& a_rroVector )
{
    return Assign( std::forward( a_rroVector ) );
}
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U, unsigned int P, unsigned int Q >
inline VectorBase< T, N, t_bIsRow >::
    VectorBase( const MatrixBase< U, P, Q >& ac_roMatrix, const T& ac_rFill )
    : BaseType( ac_roMatrix, ac_rFill ) {}
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U >
inline VectorBase< T, N, t_bIsRow >::VectorBase( const U& ac_rFill )
    : BaseType( ac_rFill ) {}
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U >
inline VectorBase< T, N, t_bIsRow >::VectorBase(const U* const ac_cpData,
                                                const unsigned int ac_uiSize,
                                                const T& ac_rFill )
    : BaseType( ac_cpData, ac_uiSize, ac_rFill ) {}
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U, unsigned int t_uiSize >
inline VectorBase< T, N, t_bIsRow >::
    VectorBase(const U (&ac_raData)[ t_uiSize ], const U& ac_rFill )
    : BaseType( ac_raData, ac_rFill ) {}

// Copy construct from a different kind of vector
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U, unsigned int Q, bool t_bOtherIsRow >
inline VectorBase< T, N, t_bIsRow >::
    VectorBase( const VectorBase< U, Q, t_bOtherIsRow >& ac_roVector,
                const T& ac_rFill )
{/*
    if( !std::is_copy_constructable< T >::value )
    {
        throw exception("Non-copy-constructable type");
    }
    if( !std::is_convertible< U, T >:: value )
    {
        throw exception("Non-convertable input type");
    } /**/
    for( unsigned int i = 0; i < N; ++i )
    {
        m_aaData[ t_bIsRow ? 1 : i][ t_bIsRow ? i : 1 ]( ( i < Q )
                                                         ? ac_roVector[i]
                                                         : ac_rFill );
    }
}

// Copy assign from a different type of vector
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U, unsigned int Q, bool t_bOtherIsRow >
inline VectorBase< T, N, t_bIsRow >& VectorBase< T, N, t_bIsRow >::
    Assign( const VectorBase< U, Q, t_bOtherIsRow >& ac_roVector )
{/*
    if( !std::is_copy_assignable< T >::value )
    {
        throw exception("Non-copy-assignable type");
    }
    if( !std::is_convertible< U, T >:: value )
    {
        throw exception("Non-convertable input type");
    } /**/
    for( unsigned int i = 0; i < N && i < Q; ++i )
    {
        m_aaData[ t_bIsRow ? 1 : i][ t_bIsRow ? i : 1 ] = ac_roVector[i];
    }
}
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U, unsigned int Q, bool t_bOtherIsRow >
inline VectorBase< T, N, t_bIsRow >& VectorBase< T, N, t_bIsRow >::
    Assign( VectorBase< U, Q, t_bOtherIsRow >&& a_rroVector )
{/*
    if( !std::is_move_assignable< T >::value )
    {
        throw exception("Non-move-assignable type");
    }
    if( !std::is_convertible< U, T >:: value )
    {
        throw exception("Non-convertable input type");
    } /**/
    for( unsigned int i = 0; i < N && i < Q; ++i )
    {
        m_aaData[ t_bIsRow ? 1 : i][ t_bIsRow ? i : 1 ] =
            std::move( ac_roVector[i] );
    }
}
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U, unsigned int Q, bool t_bOtherIsRow >
inline VectorBase< T, N, t_bIsRow >& VectorBase< T, N, t_bIsRow >::
    operator=( const VectorBase< U, Q, t_bOtherIsRow >& ac_roVector )
{
    Assign( ac_roVector );
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
inline VectorBase< T, N, t_bIsRow >::ColumnVectorType
    VectorBase< T, N, t_bIsRow >::Column( unsigned int a_uiIndex ) const
{
    return ( t_bIsRow ? ColumnVectorType( *this ) : *this );
}
template< typename T, unsigned int N, bool t_bIsRow >
inline VectorBase< T, N, t_bIsRow >::RowVectorType
    VectorBase< T, N, t_bIsRow >::Row( unsigned int a_uiIndex ) const
{
    return ( t_bIsRow ? *this : RowVectorType( *this ) );
}

// Make row vector from column vector and vice-versa
template< typename T, unsigned int N, bool t_bIsRow >
inline VectorBase< T, N, t_bIsRow >::TransposeType
    VectorBase< T, N, t_bIsRow >::Transpose() const
{
    return TransposeType( *this );
}

}   // namespace Math

#endif _VECTOR_BASE_INL_
