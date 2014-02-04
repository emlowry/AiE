/******************************************************************************
 * File:               Matrix.inl
 * Author:             Elizabeth Lowry
 * Date Created:       November 18, 2013
 * Description:        Function implementations for Matrix template class.
 * Last Modified:      January 5, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

#ifndef MATRIX__INL
#define MATRIX__INL

#include "Declarations/Matrix.h"
#include "Declarations/Vector.h"
#include "Declarations/Functions.h"
#include <stdexcept>    // for out_of_range

// Code separated out into separate files to cut down the size of this one
#include "Matrix_AssignOperators.inl"
#include "Matrix_Constructors.inl"
#include "Matrix_MathFunctions.inl"
#include "Matrix_Operators.inl"

namespace Math
{
    
// Used whenever values at a given coordinate aren't specified, as in
// constructing a matrix from another matrix with smaller dimensions.
template< typename T >
const T& DefaultFill()
{
    static T fill = 0;
    return fill;
}

// Zero matrix
template< typename T, unsigned int M, unsigned int N >
const Matrix< T, M, N >& Matrix< T, M, N >::Zero()
{
    static Matrix oZero(0);
    return oZero;
}

// Identity matrix
template< typename T, unsigned int M, unsigned int N >
const typename Matrix< T, M, N >::IdentityType& Matrix< T, M, N >::Identity()
{
    static IdentityType oIdentity( 0, 1 );
    return oIdentity;
}

// Element access
template< typename T, unsigned int M, unsigned int N >
inline T& Matrix< T, M, N >::
    At( unsigned int a_uiRow, unsigned int a_uiColumn )
{
    if( a_uiRow >= M || a_uiColumn >= N )
    {
        throw std::out_of_range( "Cannot access non-existent matrix element" );
    }
    return m_aaData[a_uiRow][a_uiColumn];
}
template< typename T, unsigned int M, unsigned int N >
inline const T& Matrix< T, M, N >::
    At( unsigned int a_uiRow, unsigned int a_uiColumn ) const
{
    if( a_uiRow >= M || a_uiColumn >= N )
    {
        throw std::out_of_range( "Cannot access non-existent matrix element" );
    }
    return m_aaData[a_uiRow][a_uiColumn];
}

// Get row/column vectors
template< typename T, unsigned int M, unsigned int N >
inline typename Matrix< T, M, N >::ColumnVectorType
    Matrix< T, M, N >::Column( unsigned int a_uiIndex ) const
{
    if( a_uiIndex >= N )
    {
        throw std::out_of_range( "Cannot access non-existent matrix column" );
    }
    ColumnVectorType oColumn;
    for( unsigned int i = 0; i < M; ++i )
    {
        oColumn[i] = m_aaData[i][a_uiIndex];
    }
    return oColumn;
}
template< typename T, unsigned int M, unsigned int N >
inline typename Matrix< T, M, N >::RowVectorType
    Matrix< T, M, N >::Row( unsigned int a_uiIndex ) const
{
    if( a_uiIndex >= M )
    {
        throw std::out_of_range( "Cannot access non-existent matrix row" );
    }
    return RowVectorType( m_aaData[ a_uiIndex ] );
}
    
// Get smaller matrices by removing a row and/or column - redefine in child
// classes to return the correct type.
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, ( M > 1 ? M-1 : 1 ), ( N > 1 ? N-1 : 1 ) > Matrix< T, M, N >::
    MinusRowAndColumn( unsigned int a_uiRow, unsigned int a_uiColumn ) const
{
    if( N == 1 || M == 1 )
    {
        throw( std::out_of_range( "Cannot remove row and column if "
                                  "there is only one of either" ) );
    }
    if( a_uiRow >= M )
    {
        throw std::out_of_range( "Cannot remove non-existent matrix row" );
    }
    if( a_uiColumn >= N )
    {
        throw std::out_of_range( "Cannot remove non-existent matrix column" );
    }
    Matrix< T, ( M > 1 ? M-1 : 1 ), ( N > 1 ? N-1 : 1 ) >
        oResult( Matrix(*this).Shift( -1 - a_uiColumn, -1 - a_uiRow ) );
    return oResult.Shift( a_uiColumn, a_uiRow );
}
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, ( N > 1 ? N-1 : 1 ) > Matrix< T, M, N >::
    MinusColumn( unsigned int a_uiColumn ) const
{
    if( N == 1 )
    {
        throw( std::out_of_range( "Cannot remove column if there is only one" ) );
    }
    if( a_uiColumn >= N )
    {
        throw std::out_of_range( "Cannot remove non-existent matrix column" );
    }
    Matrix< T, M, ( N > 1 ? N-1 : 1 ) >
        oResult( Matrix(*this).Shift( -1 - a_uiColumn ) );
    return oResult.Shift( a_uiColumn );
}
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, ( M > 1 ? M-1 : 1 ), N > Matrix< T, M, N >::
    MinusRow( unsigned int a_uiRow ) const
{
    if( M == 1 )
    {
        throw( std::out_of_range( "Cannot remove row if there is only one" ) );
    }
    if( a_uiRow >= M )
    {
        throw std::out_of_range( "Cannot remove non-existent matrix row" );
    }
    Matrix< T, ( M > 1 ? M-1 : 1 ), N >
        oResult( Matrix(*this).Shift( 0, -1 - a_uiRow ) );
    return oResult.Shift( 0, a_uiRow );
}

// Shift elements right/down the given number of spaces, wrapping around the
// ends of columns and rows
// Example:
// Matrix m = { { 0, 1, 2 }, { 10, 11, 12 }, { 20, 21, 22 } };
// m.Shift( 1, 1 );
// // m == { { 22, 20, 21 }, { 2, 0, 1 }, { 12, 10, 11 } }
// m.Shift( -1, -1 );
// // m == { { 0, 1, 2 }, { 10, 11, 12 }, { 20, 21, 22 } }
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >& Matrix< T, M, N >::Shift( int a_iRight, int a_iDown )
{
    Matrix oCopy(*this);
    for( unsigned int i = 0; i < M*N; ++i )
    {
        m_aaData[ Scroll<int>( a_iDown + i/N, M ) ]
                [ Scroll<int>( a_iRight + i, N ) ] = oCopy[i/N][i%N];
    }
    return *this;
}

// Round all elements to nearest whole number
// Optionally, divide by the given number first, then multiply by it after
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >& Matrix< T, M, N >::Round()
{
    for( unsigned int i = 0; i < M*N; ++i )
    {
        m_aaData[i/N][i%N] = Math::Round( m_aaData[i/N][i%N] );
    }
    return *this;
}

// Return transpose of a matrix
template< typename T, unsigned int M, unsigned int N >
inline typename Matrix< T, M, N >::TransposeType
    Matrix< T, M, N >::Transpose() const
{
    TransposeType oTranspose;
    for(unsigned int i = 0; i < M*N; ++i )
    {
        oTranspose[i%N][i/N] = m_aaData[i/N][i%N];
    }
    return oTranspose;
}
template< typename T, unsigned int M, unsigned int N >
inline typename Matrix< T, M, N >::TransposeType
    Matrix< T, M, N >::ConjugateTranspose() const
{
    TransposeType oTranspose;
    for(unsigned int i = 0; i < M*N; ++i )
    {
        oTranspose[i%N][i/N] = ComplexConjugate( m_aaData[i/N][i%N] );
    }
    return oTranspose;
}

}   // namespace Math

#endif MATRIX__INL
