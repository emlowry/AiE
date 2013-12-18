/******************************************************************************
 * File:               Vector_Operators.inl
 * Author:             Elizabeth Lowry
 * Date Created:       December 17, 2013
 * Description:        Arithmatic operator implementations for Vector.h.
 * Last Modified:      December 17, 2013
 * Last Modification:  Moving code out of Vector.inl.
 ******************************************************************************/

#ifndef VECTOR__OPERATORS__INL
#define VECTOR__OPERATORS__INL

namespace Math
{

// Scalar multiplication, division, and modulo overrides to return correct type
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U >
inline Vector< T, N, t_bIsRow >&
    Vector< T, N, t_bIsRow >::operator*=( const U& ac_rScalar )
{
    MatrixType::operator*=( ac_rScalar );
    return *this;
}
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U >
inline Vector< T, N, t_bIsRow >
    Vector< T, N, t_bIsRow >::operator*( const U& ac_rScalar ) const
{
    return Vector( MatrixType::operator*( ac_rScalar ) );
}
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U >
inline Vector< T, N, t_bIsRow >&
    Vector< T, N, t_bIsRow >::operator/=( const U& ac_rScalar )
{
    MatrixType::operator/=( ac_rScalar );
    return *this;
}
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U >
inline Vector< T, N, t_bIsRow >
    Vector< T, N, t_bIsRow >::operator/( const U& ac_rScalar ) const
{
    return Vector( MatrixType::operator/( ac_rScalar ) );
}
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U >
inline Vector< T, N, t_bIsRow >&
    Vector< T, N, t_bIsRow >::operator%=( const U& ac_rScalar )
{
    MatrixType::operator%=( ac_rScalar );
    return *this;
}
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U >
inline Vector< T, N, t_bIsRow >
    Vector< T, N, t_bIsRow >::operator%( const U& ac_rScalar ) const
{
    return Vector( MatrixType::operator%( ac_rScalar ) );
}

// Matrix addition/subtraction overrides to return correct type
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >&
    Vector< T, N, t_bIsRow >::operator+=( const MatrixType& ac_roMatrix )
{
    MatrixType::operator+=( ac_roMatrix );
    return *this;
}
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >
    Vector< T, N, t_bIsRow >::operator+( const MatrixType& ac_roMatrix ) const
{
    return Vector( MatrixType::operator+( ac_roMatrix ) );
}
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >&
    Vector< T, N, t_bIsRow >::operator-=( const MatrixType& ac_roMatrix )
{
    MatrixType::operator-=( ac_roMatrix );
    return *this;
}
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >
    Vector< T, N, t_bIsRow >::operator-( const MatrixType& ac_roMatrix ) const
{
    return Vector( MatrixType::operator-( ac_roMatrix ) );
}

// Vector addition
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >&
    Vector< T, N, t_bIsRow >::operator+=( const Vector& ac_roVector )
{
    for( unsigned int i = 0; i < N; ++i )
    {
        At(i) += ac_roVector[i];
    }
    return *this;
}
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >&
    Vector< T, N, t_bIsRow >::operator+=( const TransposeType& ac_roVector )
{
    for( unsigned int i = 0; i < N; ++i )
    {
        At(i) += ac_roVector[i];
    }
    return *this;
}
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >
    Vector< T, N, t_bIsRow >::operator+( const Vector& ac_roVector ) const
{
    Vector oCopy(*this);
    oCopy += ac_roVector;
    return oCopy;
}
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow > Vector< T, N, t_bIsRow >::
    operator+( const TransposeType& ac_roVector ) const
{
    Vector oCopy(*this);
    oCopy += ac_roVector;
    return oCopy;
}

// Vector subtraction
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >&
    Vector< T, N, t_bIsRow >::operator-=( const Vector& ac_roVector )
{
    for( unsigned int i = 0; i < N; ++i )
    {
        At(i) -= ac_roVector[i];
    }
    return *this;
}
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >&
    Vector< T, N, t_bIsRow >::operator-=( const TransposeType& ac_roVector )
{
    for( unsigned int i = 0; i < N; ++i )
    {
        At(i) -= ac_roVector[i];
    }
    return *this;
}
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >
    Vector< T, N, t_bIsRow >::operator-( const Vector& ac_roVector ) const
{
    Vector oCopy(*this);
    oCopy -= ac_roVector;
    return oCopy;
}
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow > Vector< T, N, t_bIsRow >::
    operator-( const TransposeType& ac_roVector ) const
{
    Vector oCopy(*this);
    oCopy -= ac_roVector;
    return oCopy;
}

}   // namespace Math

// Vector scalar multiplication and division in the other direction
template< typename U, typename T, unsigned int N, bool t_bIsRow >
inline Math::Vector< T, N, t_bIsRow >
    operator*( const U& ac_rScalar,
               const Math::Vector< T, N, t_bIsRow > ac_roVector )
{
    return ac_roVector.operator*( ac_rScalar );
}
template< typename U, typename T, unsigned int N, bool t_bIsRow >
inline typename Math::Vector< T, N, t_bIsRow >::InverseType
    operator/( const U& ac_rScalar,
               const Math::Vector< T, N, t_bIsRow > ac_roVector )
{
    if( !ac_roVectorMatrix.IsInvertable() )
    {
        throw std::invalid_argument( "Cannot divide by a non-invertable matrix" );
    }
    return ac_roVector.Inverse().operator*( ac_rScalar );
}

#endif  // VECTOR__OPERATORS__INL
