/******************************************************************************
 * File:               MatrixBaseCopyConstructors.inl
 * Author:             Elizabeth Lowry
 * Date Created:       November 25, 2013
 * Description:        MatrixBase (and VectorBase) constructors and assignment
 *                      operators that copy or move data from other MatrixBase
 *                      (or VectorBase) objects.
 * Last Modified:      November 25, 2013
 * Last Modification:  Moving code out of MatrixBase.inl.
 ******************************************************************************/

#ifndef _MATRIX_BASE_COPY_CONSTRUCTORS_INL_
#define _MATRIX_BASE_COPY_CONSTRUCTORS_INL_

// #include <type_traits>  // for std::is_whateverable checks
#include <utility>  // for std::forward and std::move

namespace Math
{
    
// Copy constructor
template< typename T, unsigned int M, unsigned int N >
inline MatrixBase< T, M, N >::MatrixBase( const MatrixBase& ac_roMatrix )
{/*
    if( !std::is_copy_constructable< T >::value )
    {
        throw exception("Non-copy-constructable type");
    } /**/
    for( unsigned int i = 0; i < M*N; ++i )
    {
        m_aaData[i/N][i%N]( ac_roMatrix[i/N][i%N] );
    }
}

// Copy assignment
template< typename T, unsigned int M, unsigned int N >
inline MatrixBase< T, M, N >&
    MatrixBase< T, M, N >::Assign( const MatrixBase& ac_roMatrix )
{/*
    if( !std::is_copy_assignable< T >::value )
    {
        throw exception("Non-copy-assignable type");
    } /**/
    for( unsigned int i = 0; i < M*N; ++i )
    {
        m_aaData[i/N][i%N] = ac_roMatrix[i/N][i%N];
    }
}
template< typename T, unsigned int M, unsigned int N >
inline MatrixBase< T, M, N >&
    MatrixBase< T, M, N >::operator=( const MatrixBase& ac_roMatrix )
{
    Assign( ac_roMatrix );
}

// Move constructor
template< typename T, unsigned int M, unsigned int N >
inline MatrixBase< T, M, N >::MatrixBase( Matrix&& a_rroMatrixBase )
{/*
    if( !std::is_move_constructable< T >::value )
    {
        throw exception("Non-move-constructable type");
    } /**/
    for( unsigned int i = 0; i < M*N; ++i )
    {
        m_aaData[i/N][i%N]( std::move( ac_roMatrix[i/N][i%N] ) );
    }
}

// Move assignment
template< typename T, unsigned int M, unsigned int N >
inline MatrixBase< T, M, N >&
    MatrixBase< T, M, N >::Assign( MatrixBase&& a_rroMatrix )
{/*
    if( !std::is_move_assignable< T >::value )
    {
        throw exception("Non-move-assignable type");
    } /**/
    for( unsigned int i = 0; i < M*N; ++i )
    {
        m_aaData[i/N][i%N] = std::move( ac_roMatrix[i/N][i%N] );
    }
}
template< typename T, unsigned int M, unsigned int N >
inline MatrixBase< T, M, N >&
    MatrixBase< T, M, N >::operator=( MatrixBase&& a_rroMatrix )
{
    Assign( std::forward< MatrixBase< T, M, N >( a_rroMatrix ) );
}

// Copy construct from a different type of matrix
template< typename T, unsigned int M, unsigned int N >
template< typename U, unsigned int P, unsigned int Q >
inline MatrixBase< T, M, N >::
    MatrixBase( const MatrixBase< U, P, Q >& ac_roMatrix, const T& ac_rFill )
{/*
    if( !std::is_copy_constructable< T >::value )
    {
        throw exception("Non-copy-constructable type");
    }
    if( !std::is_convertible< U, T >:: value )
    {
        throw exception("Non-convertable input type");
    } /**/
    for( unsigned int i = 0; i < M; ++i )
    {
        for( unsigned int j = 0; j < N; ++j )
        {
             m_aaData[i][j]( ( i < P && j < Q )
                             ? (T)( ac_roMatrix[i][j] ) : ac_rFill );
        }
    }
}

// Copy assign from a different type of matrix
template< typename T, unsigned int M, unsigned int N >
template< typename U, unsigned int P, unsigned int Q >
inline MatrixBase< T, M, N >& MatrixBase< T, M, N >::
    Assign( const MatrixBase< U, P, Q >& ac_roMatrix )
{/*
    if( !std::is_copy_assignable< T >::value )
    {
        throw exception("Non-copy-assignable type");
    }
    if( !std::is_convertible< U, T >:: value )
    {
        throw exception("Non-convertable input type");
    } /**/
    for( unsigned int i = 0; i < M && i < P; ++i )
    {
        for( unsigned int j = 0; j < N && j < Q; ++j )
        {
            m_aaData[i][j] = (T)( ac_roMatrix[i][j] );
        }
    }
}
template< typename T, unsigned int M, unsigned int N >
template< typename U, unsigned int P, unsigned int Q >
inline MatrixBase< T, M, N >& MatrixBase< T, M, N >::
    operator=( const MatrixBase< U, P, Q >& ac_roMatrix )
{
    Assign( ac_roMatrix );
}

}   // namespace Math

#endif  // _MATRIX_BASE_COPY_CONSTRUCTORS_INL_
