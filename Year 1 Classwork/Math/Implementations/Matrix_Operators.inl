/******************************************************************************
 * File:               Matrix_Operators.inl
 * Author:             Elizabeth Lowry
 * Date Created:       December 3, 2013
 * Description:        Operator implementations for Matrix template class.
 * Last Modified:      December 10, 2013
 * Last Modification:  Debugging.
 ******************************************************************************/

#ifndef MATRIX__OPERATORS__INL
#define MATRIX__OPERATORS__INL

#include "Declarations/Functions.h"

namespace Math
{

// Matrix multiplication
template< typename T, unsigned int M, unsigned int N >
template< unsigned int P >
inline Matrix< T, M, P > Matrix< T, M, N >::
    operator*( const Matrix< T, N, P >& ac_roMatrix ) const
{
    Matrix< T, M, P > oResult;
    for( unsigned int i = 0; i < M*P; i++ )
    {
        oResult[i/P][i%P] = Row( i/P ).Dot( ac_roMatrix.Column( i%P ) );
    }
    return oResult;
}

// Matrix "division" = multiplication by inverse
// Returns error if parameter is not invertable
// Order is (*this) * ( ac_roMatrix.Inverse() ) even if P > N
// (P > N means the matrix can only be left-invertable, where
//  ac_roMatrix.Inverse() * ac_roMatrix = Identity() but
//  ac_roMatrix * ac_roMatrix.Inverse() != Matrix< T, P >::Identity()
template< typename T, unsigned int M, unsigned int N >
template< unsigned int P >
inline Matrix< typename MatrixInverse< T >::Type, M, P >
    Matrix< T, M, N >::operator/( const Matrix< T, P, N >& ac_roMatrix ) const
{
    if( !ac_roMatrix.IsInvertable() )
    {
        throw std::invalid_argument( "Cannot divide by a non-invertable matrix" );
    }
    return operator*( ac_roMatrix.Inverse() );
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
template< typename U >
inline Matrix< T, M, N >& Matrix< T, M, N >::
    operator*=( const U& ac_rScalar )
{
    for( unsigned int i = 0; i < M*N; ++i )
    {
        m_aaData[i/N][i%N] *= ac_rScalar;
    }
    return *this;
}
template< typename T, unsigned int M, unsigned int N >
template< typename U >
inline Matrix< T, M, N > Matrix< T, M, N >::
    operator*( const U& ac_rScalar ) const
{
    Matrix oCopy(*this);
    oCopy *= ac_rScalar;
    return oCopy;
}
template< typename T, unsigned int M, unsigned int N >
template< typename U >
inline Matrix< T, M, N >& Matrix< T, M, N >::
    operator/=( const U& ac_rScalar )
{
    assert( ac_roScalar != 0 );
    for( unsigned int i = 0; i < M*N; ++i )
    {
        m_aaData[i/N][i%N] /= ac_rScalar;
    }
    return *this;
}
template< typename T, unsigned int M, unsigned int N >
template< typename U >
inline Matrix< T, M, N > Matrix< T, M, N >::
    operator/( const U& ac_rScalar ) const
{
    Matrix oCopy(*this);
    oCopy /= ac_rScalar;
    return oCopy;
}
template< typename T, unsigned int M, unsigned int N >
template< typename U >
inline Matrix< T, M, N >& Matrix< T, M, N >::
    operator%=( const U& ac_rScalar )
{
    assert( ac_roScalar != 0 );
    for( unsigned int i = 0; i < M*N; ++i )
    {
        ModuloAssign( m_aaData[i/N][i%N], ac_rScalar );
    }
    return *this;
}
template< typename T, unsigned int M, unsigned int N >
template< typename U >
inline Matrix< T, M, N > Matrix< T, M, N >::
    operator%( const U& ac_rScalar ) const
{
    Matrix oCopy(*this);
    oCopy %= ac_rScalar;
    return oCopy;
}

}   // namespace Math

// Matrix scalar multiplication and division in the other direction
template< typename U, typename T, unsigned int M, unsigned int N >
inline Math::Matrix< T, M, N >
    operator*( const U& ac_roScalar, const Math::Matrix< T, M, N > ac_roMatrix )
{
    return ac_roMatrix.operator*( ac_roScalar );
}
template< typename U, typename T, unsigned int M, unsigned int N >
inline typename Math::Matrix< T, M, N >::InverseType
    operator/( const U& ac_roScalar,
               const Math::Matrix< T, M, N > ac_roMatrix )
{
    if( !ac_roMatrix.IsInvertable() )
    {
        throw std::invalid_argument( "Cannot divide by a non-invertable matrix" );
    }
    return ac_roMatrix.Inverse().operator*( ac_roScalar );
}

#endif  // MATRIX__OPERATORS__INL
