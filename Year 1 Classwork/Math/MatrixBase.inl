/******************************************************************************
 * File:               MatrixBase.inl
 * Author:             Elizabeth Lowry
 * Date Created:       November 20, 2013
 * Description:        Inline and other function implementations for MatrixBase.
 * Last Modified:      November 20, 2013
 * Last Modification:  Moving code in from Matrix.inl.
 ******************************************************************************/

#ifndef _MATRIX_BASE_INL_
#define _MATRIX_BASE_INL_

// #include <type_traits>  // for std::is_whateverable checks
#include <utility>  // for std::forward and std::move

namespace Math
{

// Default matrix fill
template< typename T >
const T* MatrixFill< T* >::DEFAULT = nullptr;
template< typename T, unsigned int M, unsigned int N >
const T& MatrixBase< T, M, N >::DEFAULT_FILL = MatrixFill< T >::DEFAULT;

// Default constructor passes to fill constructor
template< typename T, unsigned int M, unsigned int N >
MatrixBase< T, M, N >::MatrixBase() : MatrixBase( DEFAULT_FILL ) {}

// Copy constructor
template< typename T, unsigned int M, unsigned int N >
MatrixBase< T, M, N >::MatrixBase( const MatrixBase& ac_roMatrix )
{/*
    if( !std::is_copy_constructable< T >::value )
    {
        throw exception("Non-copy-constructable type");
    } /**/
    for( unsigned int i = 0; i < M; ++i )
    {
        for( unsigned int j = 0; j < N; ++j )
        {
            m_aaData[i][j]( ac_roMatrix[i][j] );
        }
    }
}

// Copy assignment
template< typename T, unsigned int M, unsigned int N >
MatrixBase< T, M, N >&
    MatrixBase< T, M, N >::Assign( const MatrixBase& ac_roMatrix )
{/*
    if( !std::is_copy_assignable< T >::value )
    {
        throw exception("Non-copy-assignable type");
    } /**/
    for( unsigned int i = 0; i < M; ++i )
    {
        for( unsigned int j = 0; j < N; ++j )
        {
            m_aaData[i][j] = ac_roMatrix[i][j];
        }
    }
}
template< typename T, unsigned int M, unsigned int N >
MatrixBase< T, M, N >&
    MatrixBase< T, M, N >::operator=( const MatrixBase& ac_roMatrix )
{
    Assign( ac_roMatrix );
}

// Move constructor
template< typename T, unsigned int M, unsigned int N >
MatrixBase< T, M, N >::MatrixBase( Matrix&& a_rroMatrixBase )
{/*
    if( !std::is_move_constructable< T >::value )
    {
        throw exception("Non-move-constructable type");
    } /**/
    for( unsigned int i = 0; i < M; ++i )
    {
        for( unsigned int j = 0; j < N; ++j )
        {
            m_aaData[i][j]( std::move( ac_roMatrix[i][j] ) );
        }
    }
}

// Move assignment
template< typename T, unsigned int M, unsigned int N >
MatrixBase< T, M, N >&MatrixBase< T, M, N >::Assign( MatrixBase&& a_rroMatrix )
{/*
    if( !std::is_move_assignable< T >::value )
    {
        throw exception("Non-move-assignable type");
    } /**/
    for( unsigned int i = 0; i < M; ++i )
    {
        for( unsigned int j = 0; j < N; ++j )
        {
            m_aaData[i][j] = std::move( ac_roMatrix[i][j] );
        }
    }
}
template< typename T, unsigned int M, unsigned int N >
MatrixBase< T, M, N >&
    MatrixBase< T, M, N >::operator=( MatrixBase&& a_rroMatrix )
{
    Assign( std::forward< MatrixBase< T, M, N >( a_rroMatrix ) );
}

// Copy construct from a different type of matrix
template< typename T, unsigned int M, unsigned int N >
template< typename U, unsigned int P, unsigned int Q >
MatrixBase< T, M, N >::MatrixBase( const MatrixBase< U, P, Q >& ac_roMatrix,
                                   const T& ac_roFill )
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
            if( i < P && j < Q )
            {
                m_aaData[i][j]( (T)( ac_roMatrix[i][j] ) );
            }
            else
            {
                m_aaData[i][j]( ac_roFill );
            }
        }
    }
}

// Copy assign from a different type of matrix
template< typename T, unsigned int M, unsigned int N >
template< typename U, unsigned int P, unsigned int Q >
MatrixBase< T, M, N >& MatrixBase< T, M, N >::
    Assign( const MatrixBase< U, P, Q >& ac_roMatrix )
{/*
    if( !std::is_copy_assignable< T >::value )
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
            if( i < P && j < Q )
            {
                m_aaData[i][j] = (T)( ac_roMatrix[i][j] );
            }
            else
            {
                m_aaData[i][j] = MatrixFill< T >::DEFAULT;
            }
        }
    }
}
template< typename T, unsigned int M, unsigned int N >
template< typename U, unsigned int P, unsigned int Q >
MatrixBase< T, M, N >& MatrixBase< T, M, N >::
    operator=( const MatrixBase< U, P, Q >& ac_roMatrix )
{
    Assign( ac_roMatrix );
}

// Construct with all elements set to the given value
template< typename T, unsigned int M, unsigned int N >
template< typename U >
MatrixBase< T, M, N >::MatrixBase( const U& ac_rFill )
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
            m_aaData[i][j]( (T)( ac_rFill ) );
        }
    }
}

}   // namespace Math

#endif  // _MATRIX_BASE_INL_
