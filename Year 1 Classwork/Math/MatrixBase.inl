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
    return m_aaData[a_uiRow];
}
template< typename T, unsigned int M, unsigned int N >
inline const
    T (&MatrixBase< T, M, N >::operator[])( unsigned int a_uiRow )[ N ] const
{
    return m_aaData[a_uiRow];
}

// Element access
template< typename T, unsigned int M, unsigned int N >
inline T& MatrixBase< T, M, N >::
    operator[]( unsigned int a_uiRow, unsigned int a_uiColumn )
{
    return m_aaData[a_uiRow][a_uiColumn];
}
template< typename T, unsigned int M, unsigned int N >
inline const T& MatrixBase< T, M, N >::
    operator[]( unsigned int a_uiRow, unsigned int a_uiColumn ) const
{
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

}   // namespace Math

#endif  // _MATRIX_BASE_INL_
