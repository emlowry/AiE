/******************************************************************************
 * File:               Matrix_Constructors.inl
 * Author:             Elizabeth Lowry
 * Date Created:       December 3, 2013
 * Description:        Constructor implementations for Matrix template class.
 * Last Modified:      February 12, 2014
 * Last Modification:  Refactoring.
 ******************************************************************************/

#ifndef MATRIX__CONSTRUCTORS__INL
#define MATRIX__CONSTRUCTORS__INL

#include "../Declarations/Matrix.h"
// #include <type_traits>  // for is_whateverable checks
#include <utility>  // for forward

namespace Math
{

// destructor doesn't need to do anything
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >::~Matrix() {}
    
// Copy constructor
template< typename T, unsigned int M, unsigned int N >
template< typename U, unsigned int P, unsigned int Q >
inline Matrix< T, M, N >::
    Matrix( const Matrix< U, P, Q >& ac_roMatrix, const T& ac_rFill )
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
             m_aaData[i][j] =
                 ( ( i < P && j < Q ) ? (T)(ac_roMatrix[i][j]) : ac_rFill );
        }
    }
}

// Construct with all elements set to the given value
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >::Matrix( const T& ac_rFill )
{/*
    if( !std::is_copy_assignable< T >::value )
    {
        throw exception("Non-copy-assignable type");
    } /**/
    for( unsigned int i = 0; i < M*N; ++i )
    {
        m_aaData[i/N][i%N] = ac_rFill;
    }
}

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

// Construct with parameter data
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >::Matrix( const T (&ac_raData)[ M*N ] )
{/*
    if( !std::is_copy_assignable< T >::value )
    {
        throw exception("Non-copy-assignable type");
    } /**/
    for( unsigned int i = 0; i < M*N; ++i )
    {
        m_aaData[i/N][i%N] = ac_raData[i];
    }
}
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >::Matrix( const T (&ac_raaData)[ M ][ N ] )
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
}

// Construct from a set of columns
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >::
    Matrix( const ColumnVectorType (&ac_raoColumns)[ N ] )
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
}
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >::
    Matrix( const ColumnVectorType* const (&ac_racpoColumns)[ N ] )
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
            m_aaData[i][j] = ( nullptr == cpcoColumn ? DefaultValue< T >()
                                                  : (*cpcoColumn)[i] );
        }
    }
}

// Construct from a set of rows
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >::Matrix( const RowVectorType (&ac_raoRows)[ M ] )
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
}
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >::
    Matrix( const RowVectorType* const (&ac_racpoRows)[ M ] )
{/*
    if( !std::is_copy_assignable< T >::value )
    {
        throw exception("Non-copy-assignable type");
    } /**/
    for( unsigned int i = 0; i < M; ++i )
    {
        const RowVectorType* const cpcoRow = ac_racpoRows[i];
        for( unsigned int j = 0; j < N; ++j )
        {
            m_aaData[i][j] = ( nullptr == cpcoRow ? DefaultValue< T >()
                                                  : (*cpcoRow)[j] );
        }
    }
}

}   // namespace Math

#endif  // MATRIX__CONSTRUCTORS__INL
