/******************************************************************************
 * File:               Matrix_Operators.inl
 * Author:             Elizabeth Lowry
 * Date Created:       December 3, 2013
 * Description:        Operator implementations for Matrix template class.
 * Last Modified:      February 12, 2014
 * Last Modification:  Refactoring.
 ******************************************************************************/

#ifndef MATRIX__OPERATORS__INL
#define MATRIX__OPERATORS__INL

#include "../Declarations/Matrix.h"
#include "../Declarations/Functions.h"
#include <iostream>     // for ostream
#include <stdexcept>    // for invalid_argument and out_of_range
#include <type_traits>  // for enable_if and is_scalar

namespace Math
{

// Equality and inequality checks
template< typename T, unsigned int M, unsigned int N >
inline bool Matrix< T, M, N >::operator==( const Matrix& ac_roMatrix ) const
{
    bool bResult = true;
    for( unsigned int i = 0; bResult && i < M*N; ++i )
    {
        bResult = ( m_aaData[i/N][i%N] == ac_roMatrix[i/N][i%N] );
    }
    return bResult;
}
template< typename T, unsigned int M, unsigned int N >
inline bool Matrix< T, M, N >::operator!=( const Matrix& ac_roMatrix ) const
{
    bool bResult = false;
    for( unsigned int i = 0; !bResult && i < M*N; ++i )
    {
        bResult = ( m_aaData[i/N][i%N] != ac_roMatrix[i/N][i%N] );
    }
    return bResult;
}

// Row access
template< typename T, unsigned int M, unsigned int N >
inline T (&Matrix< T, M, N >::operator[]( unsigned int a_uiRow ))[ N ]
{
    if( a_uiRow >= M )
    {
        throw std::out_of_range( "Cannot access non-existent matrix row" );
    }
    return m_aaData[a_uiRow];
}
template< typename T, unsigned int M, unsigned int N >
inline const
    T (&Matrix< T, M, N >::operator[]( unsigned int a_uiRow ) const)[ N ]
{
    if( a_uiRow >= M )
    {
        throw std::out_of_range( "Cannot access non-existent matrix row" );
    }
    return m_aaData[a_uiRow];
}

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
inline Matrix< typename InverseOf< T >::Type, M, P >
    Matrix< T, M, N >::operator/( const Matrix< T, P, N >& ac_roMatrix ) const
{
    if( !ac_roMatrix.IsInvertable() )
    {
        throw std::invalid_argument( "Cannot divide by a non-invertable matrix" );
    }
    Matrix< InverseT, M, N > oCopy( *this );
    return oCopy * ac_roMatrix.Inverse() ;
}

// Transform assign
template< typename T, unsigned int M, unsigned int N >
Matrix< T, M, N >& Matrix< T, M, N >::
    operator*=( const Math::Matrix< T, N >& ac_roMatrix )
{
    operator=( operator*( ac_roMatrix ) );
    return *this;
}
template< typename T, unsigned int M, unsigned int N >
Matrix< T, M, N >& Matrix< T, M, N >::
    operator/=( const Math::Matrix< T, N >& ac_roMatrix )
{
    operator=( operator/( ac_roMatrix ) );
    return *this;
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
inline Matrix< T, M, N > Matrix< T, M, N >::operator-() const
{
    return operator*( -1 );
}
template< typename T, unsigned int M, unsigned int N >
template< typename U >
inline typename std::enable_if< std::is_scalar< U >::value,
                                Matrix< T, M, N >& >::type
    Matrix< T, M, N >::operator*=( const U& ac_rScalar )
{
    for( unsigned int i = 0; i < M*N; ++i )
    {
        m_aaData[i/N][i%N] *= ac_rScalar;
    }
    return *this;
}
template< typename T, unsigned int M, unsigned int N >
template< typename U >
inline typename std::enable_if< std::is_scalar< U >::value,
                                Matrix< T, M, N > >::type
    Matrix< T, M, N >::operator*( const U& ac_rScalar ) const
{
    Matrix oCopy(*this);
    oCopy *= ac_rScalar;
    return oCopy;
}
template< typename T, unsigned int M, unsigned int N >
template< typename U >
inline typename std::enable_if< std::is_scalar< U >::value,
                                Matrix< T, M, N >& >::type
    Matrix< T, M, N >::operator/=( const U& ac_rScalar )
{
    if( ac_rScalar == 0 )
    {
        throw std::invalid_argument( "Cannot divide by zero" );
    }
    for( unsigned int i = 0; i < M*N; ++i )
    {
        m_aaData[i/N][i%N] /= ac_rScalar;
    }
    return *this;
}
template< typename T, unsigned int M, unsigned int N >
template< typename U >
inline typename std::enable_if< std::is_scalar< U >::value,
                                Matrix< T, M, N > >::type
    Matrix< T, M, N >::operator/( const U& ac_rScalar ) const
{
    Matrix oCopy(*this);
    oCopy /= ac_rScalar;
    return oCopy;
}
template< typename T, unsigned int M, unsigned int N >
template< typename U >
inline typename std::enable_if< std::is_scalar< U >::value,
                                Matrix< T, M, N >& >::type
    Matrix< T, M, N >::operator%=( const U& ac_rScalar )
{
    if( ac_rScalar == 0 )
    {
        throw std::invalid_argument( "Cannot modulo by zero" );
    }
    for( unsigned int i = 0; i < M*N; ++i )
    {
        ModuloAssign( m_aaData[i/N][i%N], ac_rScalar );
    }
    return *this;
}
template< typename T, unsigned int M, unsigned int N >
template< typename U >
inline typename std::enable_if< std::is_scalar< U >::value,
                                Matrix< T, M, N > >::type
    Matrix< T, M, N >::operator%( const U& ac_rScalar ) const
{
    Matrix oCopy(*this);
    oCopy %= ac_rScalar;
    return oCopy;
}

}   // namespace Math

// Matrix scalar multiplication and division in the other direction
template< typename U, typename T, unsigned int M, unsigned int N >
inline typename std::enable_if< std::is_scalar< U >::value,
                                Math::Matrix< T, M, N > >::type
    operator*( const U& ac_rScalar, const Math::Matrix< T, M, N >& ac_roMatrix )
{
    return ac_roMatrix.operator*( ac_rScalar );
}
template< typename U, typename T, unsigned int M, unsigned int N >
inline typename std::enable_if< std::is_scalar< U >::value,
                                typename Math::Matrix< T, M, N >
                                             ::InverseType >::type
    operator/( const U& ac_rScalar,
               const Math::Matrix< T, M, N >& ac_roMatrix )
{
    if( !ac_roMatrix.IsInvertable() )
    {
        throw std::invalid_argument( "Cannot divide by a non-invertable matrix" );
    }
    return ac_roMatrix.Inverse().operator*( ac_rScalar );
}

// stream operator
template< typename T, unsigned int M, unsigned int N >
std::ostream& operator<<( std::ostream& a_roOut,
                          const Math::Matrix< T, M, N >& ac_roMatrix )
{
    a_roOut << "{ ";
    for( unsigned int i = 0; i < M; ++i )
    {
        a_roOut << "{ ";
        for( unsigned int j = 0; j < N; ++j )
        {
            a_roOut << ac_roMatrix[i][j] << ( j + 1 < N ? ", " : " " );
        }
        a_roOut << ( i + 1 < M ? "}, " : "} " );
    }
    a_roOut << "}";
    return a_roOut;
}

#endif  // MATRIX__OPERATORS__INL
