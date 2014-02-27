/******************************************************************************
 * File:               Matrix_AssignOperators.inl
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        Operator implementations for Matrix template class.
 * Last Modified:      February 4, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

#ifndef MATRIX__ASSIGN_OPERATORS__INL
#define MATRIX__ASSIGN_OPERATORS__INL

#include "../Declarations/Matrix.h"
#include "../Declarations/Functions.h"

// #include <type_traits>  // for is_whateverable checks
#include <utility>  // for forward

namespace Math
{

// Copy assign from a different type of matrix
template< typename T, unsigned int M, unsigned int N >
template< typename U, unsigned int P, unsigned int Q >
inline Matrix< T, M, N >& Matrix< T, M, N >::
    operator=( const Matrix< U, P, Q >& ac_roMatrix )
{/*
    if( !std::is_copy_assignable< T >::value )
    {
        throw exception("Non-copy-assignable type");
    }
    if( !std::is_convertible< U, T >:: value )
    {
        throw exception("Non-convertable input type");
    }  /**/
    if( ThisIsNot( ac_roMatrix ) )
    {
        for( unsigned int i = 0; i < M && i < P; ++i )
        {
            for( unsigned int j = 0; j < N && j < Q; ++j )
            {
                m_aaData[i][j] =  (T)(ac_roMatrix[i][j]);
            }
        }
    }
    return *this;
}

// Assign all elements to the given value
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >& Matrix< T, M, N >::operator=( const T& ac_rFill )
{/*
    if( !std::is_copy_assignable< T >::value )
    {
        throw exception("Non-copy-assignable type");
    } /**/
    for( unsigned int i = 0; i < M*N; ++i )
    {
        m_aaData[i/N][i%N] = ac_rFill;
    }
    return *this;
}

// Assign parameter data one row at a time until end of parameter data
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >& Matrix< T, M, N >::
    operator=( const T (&ac_raData)[ M*N ] )
{/*
    if( !std::is_copy_assignable< T >::value )
    {
        throw exception("Non-copy-assignable type");
    } /**/
    for( unsigned int i = 0; i < M*N; ++i )
    {
        m_aaData[i/N][i%N] = ac_raData[i];
    }
    return *this;
}

// Assign parameter data where given
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >& Matrix< T, M, N >::
    operator=( const T (&ac_raaData)[ M ][ N ] )
{/*
    if( !std::is_copy_assignable< T >::value )
    {
        throw exception("Non-copy-assignable type");
    } /**/
    for( unsigned int i = 0; i < M; ++i )
    {
        for( unsigned int j = 0; j < N; ++j )
        {
            m_aaData[i][j] = ac_raaData[i][j];
        }
    }
    return *this;
}

// Assign from a set of columns
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >& Matrix< T, M, N >::
    operator=( const ColumnVectorType (&ac_raoColumns)[ N ] )
{/*
    if( !std::is_copy_assignable< T >::value )
    {
        throw exception("Non-copy-assignable type");
    } /**/
    for( unsigned int i = 0; i < M; ++i )
    {
        for( unsigned int j = 0; j < N; ++j )
        {
            m_aaData[i][j] = ac_raoColumns[j][i];
        }
    }
    return *this;
}
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >& Matrix< T, M, N >::
    operator=( const ColumnVectorType* const (&ac_racpoColumns)[ N ] )
{/*
    if( !std::is_copy_assignable< T >::value )
    {
        throw exception("Non-copy-assignable type");
    } /**/
    for( unsigned int i = 0; i < M; ++i )
    {
        for( unsigned int j = 0; j < N; ++j )
        {
            const ColumnVectorType* const cpcoColumn = ac_racpoColumns[j];
            if( nullptr != cpcoColumn )
            {
                m_aaData[i][j] = (*cpcoColumn)[i] ;
            }
        }
    }
    return *this;
}

// Assign from a set of rows
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >& Matrix< T, M, N >::
    operator=( const RowVectorType (&ac_raoRows)[ M ] )
{/*
    if( !std::is_copy_assignable< T >::value )
    {
        throw exception("Non-copy-assignable type");
    } /**/
    for( unsigned int i = 0; i < M; ++i )
    {
        for( unsigned int j = 0; j < N; ++j )
        {
            m_aaData[i][j] = ac_raoRows[i][j];
        }
    }
    return *this;
}
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >& Matrix< T, M, N >::
    operator=( const RowVectorType* const (&ac_racpoRows)[ M ] )
{/*
    if( !std::is_copy_assignable< T >::value )
    {
        throw exception("Non-copy-assignable type");
    } /**/
    for( unsigned int i = 0; i < M; ++i )
    {
        for( unsigned int j = 0; j < N; ++j )
        {
            const RowVectorType* const cpcoRow = ac_racpoRows[i];
            if( nullptr != cpcoRow )
            {
                m_aaData[i][j] = (*cpcoRow)[j] ;
            }
        }
    }
    return *this;
}

}   // namespace Math

#endif  // MATRIX__ASSIGN_OPERATORS__INL
