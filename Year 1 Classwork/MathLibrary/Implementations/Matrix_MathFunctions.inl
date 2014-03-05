/******************************************************************************
 * File:               Matrix_MathFunctions.inl
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        Function implementations for Matrix template class.
 * Last Modified:      February 12, 2014
 * Last Modification:  Refactoring.
 ******************************************************************************/

#ifndef MATRIX__MATH_FUNCTIONS__INL
#define MATRIX__MATH_FUNCTIONS__INL

#include "../Declarations/Matrix.h"

namespace Math
{

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
        determinant += m_aaData[0][i] * Minor( 0, i ) * ( (i%2) == 0 ? 1 : -1 );
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
    return ( 0 != Determinant() );  // is the matrix truely invertable?
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
inline typename Matrix< T, M, N >::InverseType Matrix< T, M, N >::
    Inverse() const // if !invertable, return Zero
{
    InverseType oInverse;
    return ( Inverse( oInverse ) ? oInverse : InverseType::Zero() );
}
template< typename T, unsigned int M, unsigned int N >
inline typename Matrix< T, M, N >::InverseType Matrix< T, M, N >::
    Inverse( bool& a_rbInvertable ) const   // as above
{
    InverseType oInverse;
    a_rbInvertable = Inverse( oInverse );
    return ( a_rbInvertable ? oInverse : InverseType::Zero() );
}

// For MxN matrix A where M > N, ( A^T * A )^(-1) * A^T * A
// So we have a left inverse ( A^T * A )^(-1) * A^T
template< typename T, unsigned int M, unsigned int N >
inline bool Matrix< T, M, N >::
    LeftInverse( InverseType& a_roMatrix ) const    // !invertable = !change
{
    InverseType oTranspose = Transpose();
    Matrix< InverseT, M, N > oCopy( *this );
    typename Matrix< T, N >::InverseType oSquare( oTranspose * oCopy );
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
    InverseType oTranspose = Transpose();
    Matrix< InverseT, M, N > oCopy( *this );
    typename Matrix< T, M >::InverseType oSquare( oCopy * oTranspose );
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
    if( 1 == N )
    {
        a_roMatrix[0][0] = 1 / determinant;
        return true;
    }
    for( unsigned int i = 0; i < M*N; ++i )
    {
        a_roMatrix[i%N][i/N] = Minor( i/N, i%N );
        a_roMatrix[i%N][i/N] *= ( ( ( (i/N) + (i%N) ) % 2 ) == 0 ) ? 1 : -1;
    }
    a_roMatrix /= determinant;
    return true;
}

// Return true if this matrix is an orthogonal matrix
template< typename T, unsigned int M, unsigned int N >
inline bool Matrix< T, M, N >::IsOrthogonal() const
{
    if( M != N || N == 0 )
    {
        return false;
    }
    return ( Identity() == (*this) * Transpose() );
}

// Return true if this matrix is an idempotent matrix
template< typename T, unsigned int M, unsigned int N >
inline bool Matrix< T, M, N >::IsIdempotent() const
{
    if( M != N || N == 0 )
    {
        return false;
    }
    return ( (*this) * Transpose() == (*this) );
}

// Return true if this matrix is a Hermitian matrix
template< typename T, unsigned int M, unsigned int N >
inline bool Matrix< T, M, N >::IsHermitian() const
{
    if( M != N || N == 0 )
    {
        return false;
    }
    return ( ConjugateTranspose() == (*this) );
}

}   // namespace math

#endif  // MATRIX__MATH_FUNCTIONS__INL