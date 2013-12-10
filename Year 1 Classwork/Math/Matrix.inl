/******************************************************************************
 * File:               Matrix.inl
 * Author:             Elizabeth Lowry
 * Date Created:       November 18, 2013
 * Description:        Function implementations for Matrix template class.
 * Last Modified:      December 3, 2013
 * Last Modification:  Moving code into separate files.
 ******************************************************************************/

#ifndef _MATRIX_INL_
#define _MATRIX_INL_

// Code separated out into separate files to cut down the size of this one
#include "MatrixConstructors.inl"
#include "MatrixOperators.inl"

#include "Functions.h"

namespace Math
{

// Zero matrix
template< typename T, unsigned int M, unsigned int N >
const Matrix< T, M, N >& Matrix< T, M, N >::ZERO()
{
    static Matrix oZero(0);
    return oZero;
}

// Identity matrix
template< typename T, unsigned int M, unsigned int N >
const Matrix< T, M, N >::IdentityType& Matrix< T, M, N >::IDENTITY()
{
    static IdentityType oIdentity( 1, 0 );
    return oIdentity;
}

// Determinant - return 0 if non-square matrix
template< typename T, unsigned int M, unsigned int N >
T Matrix< T, M, N >::Determinant() const
{
    // Trivial cases
    if( N != M || N == 0 )
    {
        return 0;
    }
    if( N == 1 )
    {
        return m_aaData[0][0];
    }
    if( N == 2 )
    {
        return ( m_aaData[0][0] * m_aaData[1][1] )
                - ( m_aaData[0][1] * m_aaData[1][0] );
    }

    // Recursive case - this gets really inefficient for larger matrices
    // (complexity is O(!N)) and should be replaced with a more efficient
    // algorithm if this library is ever used for matrices with larger
    // dimensions.
    T determinant = 0;
    for( unsigned int i = 0; i < N; i++ )
    {
        determinant += Minor( 0, i ) * ( (i%2) == 0 ? 1 : -1 );
    }
    return determinant;
}
template< typename T, unsigned int M, unsigned int N >
inline T Matrix< T, M, N >::Minor( unsigned int a_uiRow,
                                   unsigned int a_uiColumn ) const
{
    return MinusRowAndColumn( a_uiRow, a_uiColumn ).Determinant();
}

// Inverse
template< typename T, unsigned int M, unsigned int N >
inline bool Matrix< T, M, N >::IsInvertable() const
{
    if( M > N ) // is the matrix left-invertable?
    {
        return ( Transpose() * (*this) ).IsInvertable();
    }
    if( M < N ) // is the matrix right-invertable?
    {
        return ( (*this) * Transpose() ).IsInvertable();
    }
    return 0 != Determinant();  // is the matrix truely invertable?
}
template< typename T, unsigned int M, unsigned int N >
inline bool Matrix< T, M, N >::Invert()
{
    InverseType oInverse;
    bool bInvertable = ( M == N && N > 0 && Inverse( oInverse ) );
    if( bInvertable )
    {
        *this = oInverse;
    }
    return bInvertable;
}
template< typename T, unsigned int M, unsigned int N >
inline bool Matrix< T, M, N >::
    Inverse( InverseType& a_roMatrix ) const    // !invertable = !change
{
    if( M > N )
    {
        return LeftInverse( a_roMatrix );
    }
    if( M < N )
    {
        return RightInverse( a_roMatrix );
    }
    return TrueInverse( a_roMatrix );
}
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >::InverseType Matrix< T, M, N >::
    Inverse() const // if !invertable, return ZERO
{
    InverseType oInverse;
    return ( Inverse( oInverse ) ? oInverse : InverseType::ZERO() );
}
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >::InverseType Matrix< T, M, N >::
    Inverse( bool& a_rbInvertable ) const   // as above
{
    InverseType oInverse;
    a_rbInvertable = Inverse( oInverse );
    return a_rbInvertable ? oInverse : InverseType::ZERO();
}

// For MxN matrix A where M > N, ( A^T * A )^(-1) * A^T * A
// So we have a left inverse ( A^T * A )^(-1) * A^T
template< typename T, unsigned int M, unsigned int N >
bool Matrix< T, M, N >::
    LeftInverse( InverseType& a_roMatrix ) const    // !invertable = !change
{
    TransposeType oTranspose = Transpose();
    Matrix< T, N >::InverseType oSquare( oTranspose * (*this) );
    if( !oSquare.Invert() )
    {
        return false;
    }
    a_roMatrix = oSquare * oTranspose;
    return true;
}

// For MxN matrix A where M < N, A * A^T * ( A * A^T )^(-1)
// So we have a right inverse A^T * ( A * A^T )^(-1)
template< typename T, unsigned int M, unsigned int N >
inline bool Matrix< T, M, N >::
    RightInverse( InverseType& a_roMatrix ) const   // !invertable = !change
{
    TransposeType oTranspose = Transpose();
    Matrix< T, M >::InverseType oSquare( (*this) * oTranspose );
    if( !oSquare.Invert() )
    {
        return false;
    }
    a_roMatrix = oTranspose * oSquare;
    return true;
}

// True inverse = transpose of cofactor matrix divided by determinant
// cofactor_i,j = minor_i,j * (-1)^(i+j)
// minor_i,j = determinant of submatrix created by removing row i and column j
template< typename T, unsigned int M, unsigned int N >
bool Matrix< T, M, N >::
    TrueInverse( InverseType& a_roMatrix ) const    // !invertable = !change
{
    T determinant = Determinant();
    if( 0 == determinant )
    {
        return false;
    }
    for( unsigned int i = 0; i < M*N; ++i )
    {
        a_roMatrix[i%N][i/N] = Minor( i/N, i%N );
        a_roMatrix[i%N][i/N] *= ( ( ( (i/N) + (i%N) ) % 2 ) == 1 ) ? -1 : 1;
    }
    a_roMatrix /= determinant;
    return true;
}

// Get row/column vectors - redefine in child classes to return correct type
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >::ColumnVectorType
    Matrix< T, M, N >::Column( unsigned int ac_uiIndex ) const
{
    return ColumnVectorType( BaseType::Column( ac_uiIndex ) );
}
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >::RowVectorType
    Matrix< T, M, N >::Row( unsigned int ac_uiIndex ) const
{
    return RowVectorType( BaseType::Row( ac_uiIndex ) );
}
    
// Get smaller matrices by removing a row and/or column - redefine in child
// classes to return the correct type.
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, ( M > 0 ? M-1 : 0 ), ( N > 0 ? N-1 : 0 ) > Matrix< T, M, N >::
    MinusRowAndColumn( unsigned int a_uiRow, unsigned int a_uiColumn ) const
{
    return Matrix< T, ( M > 0 ? M-1 : 0 ), ( N > 0 ? N-1 : 0 ) >(
                           BaseType::MinusRowAndColumn( a_uiRow, a_uiColumn ) );
}
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, ( N > 0 ? N-1 : 0 ) > Matrix< T, M, N >::
    MinusColumn( unsigned int a_uiColumn ) const
{
    return Matrix< T, M, ( N > 0 ? N-1 : 0 ) >(
                                          BaseType::MinusColumn( a_uiColumn ) );
}
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, ( M > 0 ? M-1 : 0 ), N > Matrix< T, M, N >::
    MinusRow( unsigned int a_uiRow ) const
{
    return Matrix< T, ( M > 0 ? M-1 : 0 ), N >( BaseType::MinusRow( a_uiRow ) );
}
    
// Transpose - redefine in child classes to return correct type
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >::TransposeType Matrix< T, M, N >::Transpose() const
{
    return TransposeType( BaseType::Transpose() );
}

}   // namespace Math

#endif _MATRIX_INL_
