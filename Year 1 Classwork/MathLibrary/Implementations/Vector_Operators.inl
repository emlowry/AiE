/******************************************************************************
 * File:               Vector_Operators.inl
 * Author:             Elizabeth Lowry
 * Date Created:       December 17, 2013
 * Description:        Arithmatic operator implementations for Vector.h.
 * Last Modified:      February 12, 2014
 * Last Modification:  Refactoring.
 ******************************************************************************/

#ifndef VECTOR__OPERATORS__INL
#define VECTOR__OPERATORS__INL

#include <stdexcept>    // for out_of_range
#include <type_traits>  // for enable_if and is_scalar

namespace Math
{

// Vector element access
template< typename T, unsigned int N, bool t_bIsRow >
inline T& Vector< T, N, t_bIsRow >::At( unsigned int a_uiIndex )
{
    if( a_uiIndex >= N )
    {
        throw std::out_of_range( "Cannot access non-existent vector element" );
    }
    return ( t_bIsRow ? m_aaData[0][a_uiIndex] : m_aaData[a_uiIndex][0] );
}
template< typename T, unsigned int N, bool t_bIsRow >
inline T& Vector< T, N, t_bIsRow >::operator[]( unsigned int a_uiIndex )
{
    return At( a_uiIndex );
}
template< typename T, unsigned int N, bool t_bIsRow >
inline const T& Vector< T, N, t_bIsRow >::At( unsigned int a_uiIndex ) const
{
    if( a_uiIndex >= N )
    {
        throw std::out_of_range( "Cannot access non-existent vector element" );
    }
    return ( t_bIsRow ? m_aaData[0][a_uiIndex] : m_aaData[a_uiIndex][0] );
}
template< typename T, unsigned int N, bool t_bIsRow >
inline const T& Vector< T, N, t_bIsRow >::
    operator[]( unsigned int a_uiIndex ) const
{
    return At( a_uiIndex );
}

// Matrix multiplication and division overrides so the operators won't be
// hidden by the scalar multiplication and division operator overrides
template< typename T, unsigned int N, bool t_bIsRow >
template< unsigned int P >
inline typename std::conditional< t_bIsRow, Vector< T, P >,
                                            Matrix< T, N, P > >::type
    Vector< T, N, t_bIsRow >::
    operator*( const Matrix< T, ( t_bIsRow ? N : 1 ), P >& ac_roMatrix ) const
{
    typedef typename std::conditional< t_bIsRow, Vector< T, P >,
                                                 Matrix< T, N, P > >::type
            ResultType;
    return ResultType( BaseType::operator*( ac_roMatrix ) );
}
template< typename T, unsigned int N, bool t_bIsRow >
template< unsigned int P >
inline typename std::conditional< t_bIsRow, Vector< typename InverseOf< T >::Type, P >,
                                  Matrix< typename InverseOf< T >::Type, N, P > >::type
    Vector< T, N, t_bIsRow >::
    operator/( const Matrix< T, P, ( t_bIsRow ? N : 1 ) >& ac_roMatrix ) const
{
    typedef typename std::conditional< t_bIsRow, Vector< InverseT, P >,
                                       Matrix< InverseT, N, P > >::type
            ResultType;
    return ResultType( BaseType::operator/( ac_roMatrix ) );
}
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >& Vector< T, N, t_bIsRow >::
    operator*=( const Matrix< T, ( t_bIsRow ? N : 1 ) >& ac_roMatrix )
{
    BaseType::operator*=( ac_roMatrix );
    return *this;
}
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >& Vector< T, N, t_bIsRow >::
    operator/=( const Matrix< T, ( t_bIsRow ? N : 1 ) >& ac_roMatrix )
{
    BaseType::operator/=( ac_roMatrix );
    return *this;
}

// Scalar multiplication, division, and modulo overrides to return correct type
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow > Vector< T, N, t_bIsRow >::operator-() const
{
    return operator*( -1 );
}
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U >
inline typename std::enable_if< std::is_scalar< U >::value,
                                Vector< T, N, t_bIsRow >& >::type
    Vector< T, N, t_bIsRow >::operator*=( const U& ac_rScalar )
{
    BaseType::operator*=( ac_rScalar );
    return *this;
}
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U >
inline typename std::enable_if< std::is_scalar< U >::value,
                                Vector< T, N, t_bIsRow > >::type
    Vector< T, N, t_bIsRow >::operator*( const U& ac_rScalar ) const
{
    return Vector( BaseType::operator*( ac_rScalar ) );
}
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U >
inline typename std::enable_if< std::is_scalar< U >::value,
                                Vector< T, N, t_bIsRow >& >::type
    Vector< T, N, t_bIsRow >::operator/=( const U& ac_rScalar )
{
    BaseType::operator/=( ac_rScalar );
    return *this;
}
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U >
inline typename std::enable_if< std::is_scalar< U >::value,
                                Vector< T, N, t_bIsRow > >::type
    Vector< T, N, t_bIsRow >::operator/( const U& ac_rScalar ) const
{
    return Vector( BaseType::operator/( ac_rScalar ) );
}
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U >
inline typename std::enable_if< std::is_scalar< U >::value,
                                Vector< T, N, t_bIsRow >& >::type
    Vector< T, N, t_bIsRow >::operator%=( const U& ac_rScalar )
{
    BaseType::operator%=( ac_rScalar );
    return *this;
}
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U >
inline typename std::enable_if< std::is_scalar< U >::value,
                                Vector< T, N, t_bIsRow > >::type
    Vector< T, N, t_bIsRow >::operator%( const U& ac_rScalar ) const
{
    return Vector( BaseType::operator%( ac_rScalar ) );
}

// Matrix addition/subtraction overrides to return correct type
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >&
    Vector< T, N, t_bIsRow >::operator+=( const BaseType& ac_roMatrix )
{
    BaseType::operator+=( ac_roMatrix );
    return *this;
}
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >
    Vector< T, N, t_bIsRow >::operator+( const BaseType& ac_roMatrix ) const
{
    return Vector( BaseType::operator+( ac_roMatrix ) );
}
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >&
    Vector< T, N, t_bIsRow >::operator-=( const BaseType& ac_roMatrix )
{
    BaseType::operator-=( ac_roMatrix );
    return *this;
}
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >
    Vector< T, N, t_bIsRow >::operator-( const BaseType& ac_roMatrix ) const
{
    return Vector( BaseType::operator-( ac_roMatrix ) );
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
inline typename std::enable_if< std::is_scalar< U >::value,
                                Math::Vector< T, N, t_bIsRow > >::type
    operator*( const U& ac_rScalar,
               const Math::Vector< T, N, t_bIsRow >& ac_roVector )
{
    return ac_roVector.operator*( ac_rScalar );
}
template< typename U, typename T, unsigned int N, bool t_bIsRow >
inline typename std::enable_if< std::is_scalar< U >::value,
                                typename Math::Vector< T, N, t_bIsRow >
                                             ::InverseType >::type
    operator/( const U& ac_rScalar,
               const Math::Vector< T, N, t_bIsRow >& ac_roVector )
{
    if( !ac_roVector.IsInvertable() )
    {
        throw std::invalid_argument( "Cannot divide by a non-invertable matrix" );
    }
    return ac_roVector.Inverse().operator*( ac_rScalar );
}

#endif  // VECTOR__OPERATORS__INL
