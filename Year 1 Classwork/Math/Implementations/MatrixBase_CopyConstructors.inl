/******************************************************************************
 * File:               MatrixBase_CopyConstructors.inl
 * Author:             Elizabeth Lowry
 * Date Created:       November 25, 2013
 * Description:        MatrixBase constructors and assignment operators that
 *                      copy or move data from other MatrixBase objects.
 * Last Modified:      December 10, 2013
 * Last Modification:  Debugging.
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
    MatrixBase< T, M, N >::operator=( const MatrixBase& ac_roMatrix )
{/*
    if( !std::is_copy_assignable< T >::value )
    {
        throw exception("Non-copy-assignable type");
    } /**/
    if( this != &ac_roMatrix )
    {
        return;
    }
    for( unsigned int i = 0; i < M*N; ++i )
    {
        m_aaData[i/N][i%N] = ac_roMatrix[i/N][i%N];
    }
}

// Move constructor
template< typename T, unsigned int M, unsigned int N >
inline MatrixBase< T, M, N >::MatrixBase( MatrixBase&& a_rroMatrixBase )
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
    MatrixBase< T, M, N >::operator=( MatrixBase&& a_rroMatrix )
{/*
    if( !std::is_move_assignable< T >::value )
    {
        throw exception("Non-move-assignable type");
    } /**/
    if( this != &a_rroMatrix )
    {
        return;
    }
    for( unsigned int i = 0; i < M*N; ++i )
    {
        m_aaData[i/N][i%N] = std::move( ac_roMatrix[i/N][i%N] );
    }
}

// Copy construct from a different type of matrix
template< typename T, unsigned int M, unsigned int N >
template< typename U >
inline MatrixBase< T, M, N >::
    MatrixBase( const MatrixBase< U, M, N >& ac_roMatrix )
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
             m_aaData[i][j]( (T)( ac_roMatrix[i][j] ) );
        }
    }
}
template< typename T, unsigned int M, unsigned int N >
template< unsigned int P, unsigned int Q >
inline MatrixBase< T, M, N >::
    MatrixBase( const MatrixBase< T, P, Q >& ac_roMatrix, const T& ac_rFill )
{/*
    if( !std::is_copy_constructable< T >::value )
    {
        throw exception("Non-copy-constructable type");
    } /**/
    for( unsigned int i = 0; i < M; ++i )
    {
        for( unsigned int j = 0; j < N; ++j )
        {
             m_aaData[i][j]( ( i < P && j < Q ) ? ac_roMatrix[i][j] : ac_rFill );
        }
    }
}

// Copy assign from a different type of matrix
template< typename T, unsigned int M, unsigned int N >
template< typename U >
inline MatrixBase< T, M, N >& MatrixBase< T, M, N >::
    operator=( const MatrixBase< U, M, N >& ac_roMatrix )
{/*
    if( !std::is_copy_assignable< T >::value )
    {
        throw exception("Non-copy-assignable type");
    }
    if( !std::is_convertible< U, T >:: value )
    {
        throw exception("Non-convertable input type");
    } /**/
    for( unsigned int i = 0; i < M; ++i )
    {
        for( unsigned int j = 0; j < N; ++j )
        {
            m_aaData[i][j] = (T)( ac_roMatrix[i][j] );
        }
    }
}
template< typename T, unsigned int M, unsigned int N >
template< unsigned int P, unsigned int Q >
inline MatrixBase< T, M, N >& MatrixBase< T, M, N >::
    operator=( const MatrixBase< T, P, Q >& ac_roMatrix )
{/*
    if( !std::is_copy_assignable< T >::value )
    {
        throw exception("Non-copy-assignable type");
    } /**/
    for( unsigned int i = 0; i < M && i < P; ++i )
    {
        for( unsigned int j = 0; j < N && j < Q; ++j )
        {
            m_aaData[i][j] =  ac_roMatrix[i][j];
        }
    }
}

}   // namespace Math

#endif  // _MATRIX_BASE_COPY_CONSTRUCTORS_INL_
