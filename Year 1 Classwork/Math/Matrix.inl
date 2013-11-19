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

// Copy constructor
template< typename T, unsigned int M, unsigned int N >
Matrix< T, M, N >::Matrix( const Matrix& ac_roMatrix )
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
Matrix< T, M, N >& Matrix< T, M, N >::operator=( const Matrix& ac_roMatrix )
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

// Move constructor
template< typename T, unsigned int M, unsigned int N >
Matrix< T, M, N >::Matrix( Matrix&& a_rroMatrix )
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
Matrix< T, M, N >& Matrix< T, M, N >::operator=( Matrix&& a_rroMatrix )
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

// Copy construct from a different type of matrix
template< typename T, unsigned int M, unsigned int N >
template< typename U, unsigned int P, unsigned int Q >
Matrix< T, M, N >::Matrix( const Matrix< U, P, Q >& ac_roMatrix,
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
Matrix< T, M, N >& Matrix< T, M, N >::
    operator=( const Matrix< U, P, Q >& ac_roMatrix, const T& ac_roFill )
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
                m_aaData[i][j] = ac_roFill;
            }
        }
    }
}

// Construct with all elements set to the given value
template< typename T, unsigned int M, unsigned int N >
template< typename U >
Matrix< T, M, N >::Matrix( const U& ac_rFill )
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

// Construct with diagonal elements set to the second given value and all others
// set to the first
template< typename T, unsigned int M, unsigned int N >
template< typename U, typename V >
Matrix< T, M, N >:Matrix( const U& ac_rFill, const V& ac_rIdentityFill )
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
            if( i == j )
            {
                m_aaData[i][j]( (T)( ac_rIdentityFill ) );
            }
            else
            {
                m_aaData[i][j]( (T)( ac_rFill ) );
            }
        }
    }
}

}   // namespace Math

#endif _MATRIX_INL_
