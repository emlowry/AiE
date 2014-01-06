/******************************************************************************
 * File:               Matrix_Constructors.inl
 * Author:             Elizabeth Lowry
 * Date Created:       December 3, 2013
 * Description:        Constructor implementations for Matrix template class.
 * Last Modified:      December 10, 2013
 * Last Modification:  Debugging.
 ******************************************************************************/

#ifndef MATRIX__CONSTRUCTORS__INL
#define MATRIX__CONSTRUCTORS__INL

// #include <type_traits>  // for is_whateverable checks
#include <utility>  // for forward

namespace Math
{

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
inline Matrix< T, M, N >::Matrix( const BaseType& ac_roMatrix )
    : BaseType( ac_roMatrix ) {}
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >::Matrix( Matrix&& a_rroMatrix )
    : BaseType( std::forward< Matrix >( a_rroMatrix ) ) {}
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >::Matrix( BaseType&& a_rroMatrix )
    : BaseType( std::forward< BaseType >( a_rroMatrix ) ) {}
template< typename T, unsigned int M, unsigned int N >
template< typename U, unsigned int P, unsigned int Q >
inline Matrix< T, M, N >::Matrix( const MatrixBase< U, P, Q >& ac_roMatrix,
                                  const T& ac_rFill )
    : BaseType( ac_roMatrix, ac_rFill ) {}
template< typename T, unsigned int M, unsigned int N >
template< unsigned int P, unsigned int Q >
inline Matrix< T, M, N >::Matrix( MatrixBase< T, P, Q >&& a_rroMatrix,
                                  const T& ac_rFill )
    : BaseType( std::forward< MatrixBase< T, P, Q > >( a_rroMatrix ), ac_rFill ) {}
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >::Matrix( const T& ac_rFill ) : BaseType( ac_rFill ) {}
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >::Matrix( const T (&ac_raData)[ M*N ] )
    : BaseType( ac_raData ) {}
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >::Matrix( const T* const ac_cpData,
                                  const unsigned int ac_uiSize,
                                  const T& ac_rFill )
    : BaseType( ac_cpData, ac_uiSize, ac_rFill ) {}
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >::
    Matrix( const T (&ac_raaData)[ M ][ N ] )
    : BaseType( ac_raaData ) {}
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >::Matrix( const T* const* const ac_cpcpData,
                                  const unsigned int ac_uiRows,
                                  const unsigned int ac_uiColumns,
                                  const T& ac_rFill)
    : BaseType( ac_cpcpData, ac_uiRows, ac_uiColumns, ac_rFill ) {}
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >::Matrix( const ColumnVectorType (&ac_raoColumns)[ N ] )
    : BaseType( ac_raoColumns ) {}
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >::
    Matrix( const ColumnVectorType* const (&ac_racpoColumns)[ N ] )
    : BaseType( ac_racpoColumns ) {}
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >::Matrix( const RowVectorType (&ac_raoRows)[ M ] )
    : BaseType( ac_raoRows ) {}
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >::
    Matrix( const RowVectorType* const (&ac_racpoRows)[ M ] )
    : BaseType( ac_racpoRows ) {}

// Construct with diagonal elements set to the second given value and all others
// set to the first
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >::Matrix( const T& ac_rFill, const T& ac_rIdentityFill )
{/*
    if( !std::is_copy_assignable< T >::value )
    {
        throw exception("Non-copy-assignable type");
    } /**/
    for( unsigned int i = 0; i < M; ++i )
    {
        for( unsigned int j = 0; j < N; ++j )
        {
            m_aaData[i][j] = ( ( i == j ) ? ac_rIdentityFill : ac_rFill );
        }
    }
}

}   // namespace Math

#endif  // MATRIX__CONSTRUCTORS__INL
