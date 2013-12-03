/******************************************************************************
 * File:               MatrixBase.inl
 * Author:             Elizabeth Lowry
 * Date Created:       November 20, 2013
 * Description:        Inline and other function implementations for MatrixBase.
 * Last Modified:      November 25, 2013
 * Last Modification:  Separating out non-default constructor code.
 ******************************************************************************/

#ifndef _MATRIX_BASE_INL_
#define _MATRIX_BASE_INL_

// Separated out to keep individual file size down
#include "MatrixBaseCopyConstructors.inl"
#include "MatrixBaseFillConstructors.inl"

#include "Functions.h"
#include <cassert>  // for assert

namespace Math
{

// Default matrix fill
template< typename T >
const T* MatrixFill< T* >::DEFAULT = nullptr;
template< typename T, unsigned int M, unsigned int N >
const T& MatrixBase< T, M, N >::DEFAULT_FILL = MatrixFill< T >::DEFAULT;

// Default destructor doesn't need to do anything
template< typename T, unsigned int M, unsigned int N >
inline MatrixBase< T, M, N >::~MatrixBase() {}

// Default constructor passes to fill constructor
template< typename T, unsigned int M, unsigned int N >
inline MatrixBase< T, M, N >::MatrixBase() : MatrixBase( DEFAULT_FILL ) {}

// Equality and inequality checks
template< typename T, unsigned int M, unsigned int N >
inline bool MatrixBase< T, M, N >::
    operator==( const Matrix& ac_roMatrix ) const
{
    bool bResult = true;
    for( unsigned int i = 0; bResult && i < M*N; ++i )
    {
        bResult = ( m_aaData[i/N][i%N] == ac_roMatrix[i/N][i%N] ) );
    }
    return bResult;
}
template< typename T, unsigned int M, unsigned int N >
inline bool MatrixBase< T, M, N >::
    operator!=( const Matrix& ac_roMatrix ) const
{
    bool bResult = false;
    for( unsigned int i = 0; bResult && i < M*N; ++i )
    {
        bResult = !( m_aaData[i/N][i%N] != ac_roMatrix[i/N][i%N] ) );
    }
    return bResult;
}

// Row access
template< typename T, unsigned int M, unsigned int N >
inline T (&MatrixBase< T, M, N >::operator[])( unsigned int a_uiRow )[ N ]
{
    assert( a_uiRow < M );
    return m_aaData[a_uiRow];
}
template< typename T, unsigned int M, unsigned int N >
inline const
    T (&MatrixBase< T, M, N >::operator[])( unsigned int a_uiRow )[ N ] const
{
    assert( a_uiRow < M )
    return m_aaData[a_uiRow];
}

// Element access
template< typename T, unsigned int M, unsigned int N >
inline T& MatrixBase< T, M, N >::
    operator[]( unsigned int a_uiRow, unsigned int a_uiColumn )
{
    assert( a_uiRow < M && a_uiColumn < N );
    return m_aaData[a_uiRow][a_uiColumn];
}
template< typename T, unsigned int M, unsigned int N >
inline const T& MatrixBase< T, M, N >::
    operator[]( unsigned int a_uiRow, unsigned int a_uiColumn ) const
{
    assert( a_uiRow < M && a_uiColumn < N );
    return m_aaData[a_uiRow][a_uiColumn];
}

// Get row/column vectors
template< typename T, unsigned int M, unsigned int N >
inline MatrixBase< T, M, N >::ColumnVectorType
    MatrixBase< T, M, N >::Column( unsigned int ac_uiIndex ) const
{
    ColumnVectorType oColumn;
    for( unsigned int i = 0; i < M; ++i )
    {
        oColumn[i] = m_aaData[i][ac_uiIndex];
    }
    return oColumn;
}
template< typename T, unsigned int M, unsigned int N >
inline MatrixBase< T, M, N >::RowVectorType
    MatrixBase< T, M, N >::Row( unsigned int ac_uiIndex ) const
{
    return RowVectorType( m_aaData[ ac_uiIndex ] );
}

// Return transpose of a matrix
template< typename T, unsigned int M, unsigned int N >
inline MatrixBase< T, M, N >::TransposeType
    MatrixBase< T, M, N >::Transpose() const
{
    TransposeType oTranspose;
    for(unsigned int i = 0; i < M*N; ++i )
    {
        oTranspose[i%N][i/N] = m_aaData[i/N][i%N];
    }
    return oTranspose;
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
inline void MatrixBase< T, M, N >::Shift( int a_iRight, int a_iDown )
{
    MatrixBase oCopy(*this);
    for( unsigned int i = 0; i < M*N; ++i )
    {
        m_aaData[ Scroll<int>( a_iDown + i/N, M ) ]
                [ Scroll<int>( a_iRight + i, N ) ] = oCopy[i/N][i%N];
    }
}

}   // namespace Math

#endif  // _MATRIX_BASE_INL_
