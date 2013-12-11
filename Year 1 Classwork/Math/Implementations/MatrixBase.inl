/******************************************************************************
 * File:               MatrixBase.inl
 * Author:             Elizabeth Lowry
 * Date Created:       November 20, 2013
 * Description:        Inline and other function implementations for MatrixBase.
 * Last Modified:      December 10, 2013
 * Last Modification:  Debugging.
 ******************************************************************************/

#ifndef MATRIX_BASE__INL
#define MATRIX_BASE__INL

// Separated out to keep individual file size down
#include "MatrixBase_CopyConstructors.inl"
#include "MatrixBase_FillConstructors.inl"

#include "Declarations/Functions.h"
#include <cassert>  // for assert

namespace Math
{

// Default matrix fill
template< typename T, unsigned int M, unsigned int N >
const T& MatrixBase< T, M, N >::DefaultFill()
{
    return MatrixFill< T >::DEFAULT;
}

// Default destructor doesn't need to do anything
template< typename T, unsigned int M, unsigned int N >
inline MatrixBase< T, M, N >::~MatrixBase() {}

// Default constructor passes to fill constructor
template< typename T, unsigned int M, unsigned int N >
inline MatrixBase< T, M, N >::MatrixBase() : MatrixBase( DefaultFill() ) {}

// Equality and inequality checks
template< typename T, unsigned int M, unsigned int N >
inline bool MatrixBase< T, M, N >::
    operator==( const MatrixBase& ac_roMatrix ) const
{
    bool bResult = true;
    for( unsigned int i = 0; bResult && i < M*N; ++i )
    {
        bResult = ( m_aaData[i/N][i%N] == ac_roMatrix[i/N][i%N] );
    }
    return bResult;
}
template< typename T, unsigned int M, unsigned int N >
inline bool MatrixBase< T, M, N >::
    operator!=( const MatrixBase& ac_roMatrix ) const
{
    bool bResult = false;
    for( unsigned int i = 0; !bResult && i < M*N; ++i )
    {
        bResult = !( m_aaData[i/N][i%N] != ac_roMatrix[i/N][i%N] );
    }
    return bResult;
}

// Row access
template< typename T, unsigned int M, unsigned int N >
inline T (&MatrixBase< T, M, N >::operator[]( unsigned int a_uiRow ))[ N ]
{
    assert( a_uiRow < M );
    return m_aaData[a_uiRow];
}
template< typename T, unsigned int M, unsigned int N >
inline const
    T (&MatrixBase< T, M, N >::operator[]( unsigned int a_uiRow ) const)[ N ]
{
    assert( a_uiRow < M )
    return m_aaData[a_uiRow];
}

// Element access
template< typename T, unsigned int M, unsigned int N >
inline T& MatrixBase< T, M, N >::
    At( unsigned int a_uiRow, unsigned int a_uiColumn )
{
    assert( a_uiRow < M && a_uiColumn < N );
    return m_aaData[a_uiRow][a_uiColumn];
}
template< typename T, unsigned int M, unsigned int N >
inline const T& MatrixBase< T, M, N >::
    At( unsigned int a_uiRow, unsigned int a_uiColumn ) const
{
    assert( a_uiRow < M && a_uiColumn < N );
    return m_aaData[a_uiRow][a_uiColumn];
}

// Get row/column vectors
template< typename T, unsigned int M, unsigned int N >
inline typename MatrixBase< T, M, N >::ColumnVectorType
    MatrixBase< T, M, N >::Column( unsigned int ac_uiIndex ) const
{
    assert( ac_uiIndex < N );
    ColumnVectorType oColumn;
    for( unsigned int i = 0; i < M; ++i )
    {
        oColumn[i] = m_aaData[i][ac_uiIndex];
    }
    return oColumn;
}
template< typename T, unsigned int M, unsigned int N >
inline typename MatrixBase< T, M, N >::RowVectorType
    MatrixBase< T, M, N >::Row( unsigned int ac_uiIndex ) const
{
    assert( ac_uiIndex < M );
    return RowVectorType( m_aaData[ ac_uiIndex ] );
}

// Return transpose of a matrix
template< typename T, unsigned int M, unsigned int N >
inline typename MatrixBase< T, M, N >::TransposeType
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
    
// Get smaller matrices by removing a row and/or column - redefine in child
// classes to return the correct type.
template< typename T, unsigned int M, unsigned int N >
MatrixBase< T, ( M > 0 ? M-1 : 0 ), ( N > 0 ? N-1 : 0 ) > MatrixBase< T, M, N >::
    MinusRowAndColumn( unsigned int a_uiRow, unsigned int a_uiColumn ) const
{
    if( N == 0 || M == 0 )
    {
        throw( std::out_of_range( "Cannot remove row and column if "
                                  "there are none of either" ) );
    }
    assert( a_uiRow < M && a_uiColumn < N );
    MatrixBase oCopy(*this);
    oCopy.Shift( -1 - a_uiColumn, -1 - a_uiRow );
    MatrixBase< T, ( M > 0 ? M-1 : 0 ), ( N > 0 ? N-1 : 0 ) > oResult( oCopy );
    oResult.Shift( a_uiColumn, a_uiRow );
}
template< typename T, unsigned int M, unsigned int N >
MatrixBase< T, M, ( N > 0 ? N-1 : 0 ) > MatrixBase< T, M, N >::
    MinusColumn( unsigned int a_uiColumn ) const
{
    if( N == 0 )
    {
        throw( std::out_of_range( "Cannot remove column if there are none" ) );
    }
    assert( a_uiColumn < N );
    MatrixBase oCopy(*this);
    oCopy.Shift( -1 - a_uiColumn );
    MatrixBase< T, M, ( N > 0 ? N-1 : 0 ) > oResult( oCopy );
    oResult.Shift( a_uiColumn );
}
template< typename T, unsigned int M, unsigned int N >
MatrixBase< T, ( M > 0 ? M-1 : 0 ), N > MatrixBase< T, M, N >::
    MinusRow( unsigned int a_uiRow ) const
{
    if( M == 0 )
    {
        throw( std::out_of_range( "Cannot remove row if there are none" ) );
    }
    assert( a_uiRow < M );
    MatrixBase oCopy(*this);
    oCopy.Shift( 0, -1 - a_uiRow );
    MatrixBase< T, ( M > 0 ? M-1 : 0 ), N > oResult( oCopy );
    oResult.Shift( 0, a_uiRow );
}

}   // namespace Math

#endif  // MATRIX_BASE__INL
