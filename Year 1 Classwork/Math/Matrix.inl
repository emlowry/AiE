/******************************************************************************
 * File:               Matrix.inl
 * Author:             Elizabeth Lowry
 * Date Created:       November 18, 2013
 * Description:        Function implementations for Matrix template class.
 * Last Modified:      November 18, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef _MATRIX_INL_
#define _MATRIX_INL_

// #include <type_traits>  // for is_whateverable checks
#include <utility>  // for move

namespace Math
{

// Zero matrix
template< typename T, unsigned int M, unsigned int N >
ZERO_MATRIX< T, M, N >( 0 );
template< typename T, unsigned int M, unsigned int N >
const Matrix< T, M, N >& Matrix< T, M, N >::ZERO = ZERO_MATRIX< T, M, N >;

// Identity matrix
template< typename T, unsigned int N >
IDENTITY_MATRIX< T, N >( 1, 0 );
template< typename T, unsigned int M, unsigned int N >
const Matrix< T, ( M < N ? M : N ) >&
    Matrix< T, M, N >::IDENTITY = IDENTITY_MATRIX< T, ( M < N ? M : N ) >;

// destructor doesn't need to do anything
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >::~Matrix() {}
    
// Constructors that forward to base class constructors
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >::Matrix() : BaseType() {}
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >::Matrix( const Matrix& ac_roMatrix )
    : BaseType( ac_roMatrix ) {}
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >& Matrix< T, M, N >::
    operator=( const Matrix& ac_roMatrix )
{
    return Assign( ac_roMatrix );
}
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >::Matrix( const BaseType& ac_roMatrix )
    : BaseType( ac_roMatrix ) {}
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >::Matrix( Matrix&& a_rroMatrix )
    : BaseType( std::forward( a_rroMatrix ) ) {}
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >& Matrix< T, M, N >::
    operator=( Matrix&& a_rroMatrix )
{
    return Assign( std::forward( a_rroMatrix ) );
}
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >::Matrix( BaseType&& a_rroMatrix )
    : BaseType( std::forward( a_rroMatrix ) ) {}
template< typename T, unsigned int M, unsigned int N >
template< typename U, unsigned int P, unsigned int Q >
inline Matrix< T, M, N >::Matrix( const MatrixBase< U, P, Q >& ac_roMatrix,
                                  const T& ac_rFill )
    : BaseType( ac_roMatrix, ac_rFill ) {}
template< typename T, unsigned int M, unsigned int N >
template< typename U >
inline Matrix< T, M, N >::Matrix( const U& ac_rFill ) : BaseType( ac_rFill ) {}
template< typename T, unsigned int M, unsigned int N >
template< typename U, unsigned int t_uiDataSize >
inline Matrix< T, M, N >::Matrix( const U (&ac_raData)[ t_uiDataSize ],
                                  const T& ac_rFill )
    : BaseType( ac_raData, ac_rFill ) {}
template< typename T, unsigned int M, unsigned int N >
template< typename U >
inline Matrix< T, M, N >::Matrix( const U* const ac_cpData,
                                  const unsigned int ac_uiSize,
                                  const T& ac_rFill )
    : BaseType( ac_cpData, ac_uiSize, ac_rFill ) {}
template< typename T, unsigned int M, unsigned int N >
template< typename U, unsigned int t_uiRows, unsigned int t_uiColumns >
inline Matrix< T, M, N >::
    Matrix( const U (&ac_raaData)[ t_uiRows ][ t_uiColumns ], const T& ac_rFill)
    : BaseType( ac_raaData, ac_rFill ) {}
template< typename T, unsigned int M, unsigned int N >
template< typename U >
inline Matrix< T, M, N >::Matrix( const U* const* const ac_cpcpData,
                                  const unsigned int ac_uiRows,
                                  const unsigned int ac_uiColumns,
                                  const T& ac_rFill)
    : BaseType( ac_cpcpData, ac_uiRows, ac_uiColumns, ac_rFill ) {}

// Construct with diagonal elements set to the second given value and all others
// set to the first
template< typename T, unsigned int M, unsigned int N >
template< typename U, typename V >
inline Matrix< T, M, N >::Matrix( const U& ac_rFill, const V& ac_rIdentityFill )
{/*
    if( !std::is_copy_constructable< T >::value )
    {
        throw exception("Non-copy-constructable type");
    }
    if( !std::is_convertible< U, T >:: value )
    {
        throw exception("Non-convertable input type");
    }
    if( !std::is_convertible< V, T >:: value )
    {
        throw exception("Non-convertable input type");
    } /**/
    for( unsigned int i = 0; i < M; ++i )
    {
        for( unsigned int j = 0; j < N; ++j )
        {
            m_aaData[i][j]( (T)( ( i == j ) ? ac_rIdentityFill : ac_rFill ) );
        }
    }
}

// TODO

}   // namespace Math

#endif _MATRIX_INL_
