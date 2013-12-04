/******************************************************************************
 * File:               MatrixOperators.inl
 * Author:             Elizabeth Lowry
 * Date Created:       December 3, 2013
 * Description:        Operator implementations for Matrix template class.
 * Last Modified:      December 3, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef _MATRIX_OPERATORS_INL_
#define _MATRIX_OPERATORS_INL_

#include "Functions.h"

namespace Math
{

// Matrix multiplication
template< typename T, unsigned int M, unsigned int N >
template< unsigned int P >
inline Matrix< T, M, P > Matrix< T, M, N >::
    Product( const Matrix< T, N, P >& ac_roMatrix ) const
{
    Matrix< T, M, P > oResult;
    for( unsigned int i = 0; i < M*P; i++ )
    {
        oResult[i/P][i%P] = Row( i/P ).Dot( ac_roMatrix.Column( i%P ) );
    }
    return oResult;
}
template< typename T, unsigned int M, unsigned int N >
template< unsigned int P >
inline Matrix< T, M, P > Matrix< T, M, N >::
    operator*( const Matrix< T, N, P >& ac_roMatrix ) const
{
    return Product( ac_roMatrix );
}

// Matrix "division" = multiplication by inverse
// Returns error if parameter is not invertable
// Order is (*this) * ( ac_roMatrix.Inverse() ) even if P > N
// (P > N means the matrix can only be left-invertable, where
//  ac_roMatrix.Inverse() * ac_roMatrix = IDENTITY but
//  ac_roMatrix * ac_roMatrix.Inverse() != IDENTITY_MATRIX< T, P >
template< typename T, unsigned int M, unsigned int N >
template< unsigned int P >
inline Matrix< typename MatrixInverse< T >::Type, M, P >
    Matrix< T, M, N >::operator/( const Matrix< T, P, N >& ac_roMatrix ) const
{
    assert( ac_roMatrix.IsInvertable() );
    return Product( ac_roMatrix.Inverse() );
}

// multiplication by a column vector produces another column vector
template< typename T, unsigned int M, unsigned int N >
inline Vector< T, M, false >
    Matrix< T, M, N >::operator*( const Matrix< T, N, 1 >& ac_roVector ) const
{
    return Vector< T, M, false >( Product( ac_roVector ) );
}

// "division" by a row vector = multiplication by its inverse, if it has one
template< typename T, unsigned int M, unsigned int N >
inline Vector< typename MatrixInverse< T >::Type, M, false >
    Matrix< T, M, N >::operator/( const Matrix< T, 1, N >& ac_roVector ) const
{
    assert( ac_roMatrix.IsInvertable() );
    typedef Vector< typename MatrixInverse< T >::Type, M, false > ResultType;
    return ResultType( Product( ac_roMatrix.Inverse() ) );
}

// Matrix addition and subtraction
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >& Matrix< T, M, N >::
    operator+=( const Matrix& ac_roMatrix )
{
    for( unsigned int i = 0; i < M*N; ++i )
    {
        m_aaData[i/N][i%N] += ac_roMatrix[i/N][i%N];
    }
    return *this;
}
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N > Matrix< T, M, N >::
    operator+( const Matrix& ac_roMatrix ) const
{
    Matrix oCopy(*this);
    oCopy += ac_roMatrix;
    return oCopy;
}
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >& Matrix< T, M, N >::
    operator-=( const Matrix& ac_roMatrix )
{
    for( unsigned int i = 0; i < M*N; ++i )
    {
        m_aaData[i/N][i%N] -= ac_roMatrix[i/N][i%N];
    }
    return *this;
}
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N > Matrix< T, M, N >::
    operator-( const Matrix& ac_roMatrix ) const
{
    Matrix oCopy(*this);
    oCopy -= ac_roMatrix;
    return oCopy;
}

    // Scalar math - multiplication, division, and modulo
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >& Matrix< T, M, N >::
    operator*=( const T& ac_rScalar )
{
    for( unsigned int i = 0; i < M*N; ++i )
    {
        m_aaData[i/N][i%N] *= ac_rScalar;
    }
    return *this;
}
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N > Matrix< T, M, N >::
    operator*( const T& ac_rScalar ) const
{
    Matrix oCopy(*this);
    oCopy *= ac_rScalar;
    return oCopy;
}
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >& Matrix< T, M, N >::
    operator/=( const T& ac_rScalar )
{
    assert( ac_roScalar != 0 );
    for( unsigned int i = 0; i < M*N; ++i )
    {
        m_aaData[i/N][i%N] /= ac_rScalar;
    }
    return *this;
}
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N > Matrix< T, M, N >::
    operator/( const T& ac_rScalar ) const
{
    Matrix oCopy(*this);
    oCopy /= ac_rScalar;
    return oCopy;
}
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N >& Matrix< T, M, N >::
    operator%=( const T& ac_rScalar )
{
    assert( ac_roScalar != 0 );
    for( unsigned int i = 0; i < M*N; ++i )
    {
        ModuloAssign( m_aaData[i/N][i%N], ac_rScalar );
    }
    return *this;
}
template< typename T, unsigned int M, unsigned int N >
inline Matrix< T, M, N > Matrix< T, M, N >::
    operator%( const T& ac_rScalar ) const
{
    Matrix oCopy(*this);
    oCopy %= ac_rScalar;
    return oCopy;
}

}   // namespace Math

#endif  // _MATRIX_OPERATORS_INL_
