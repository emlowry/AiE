/******************************************************************************
 * File:               Vector.inl
 * Author:             Elizabeth Lowry
 * Date Created:       November 25, 2013
 * Description:        Inline and other function implementations for Vector.h.
 * Last Modified:      December 10, 2013
 * Last Modification:  Debugging.
 ******************************************************************************/

#ifndef VECTOR__INL
#define VECTOR__INL

#include "Declarations/Vector.h"
#include <cmath>    // for std::sqrt

// separate files to keep file size down
#include "Vector_Constructors.inl"
#include "Vector_Operators.inl"

namespace Math
{

// Zero vector
template< typename T, unsigned int N, bool t_IsRow >
const Vector< T, N, t_IsRow >& Vector< T, N, t_IsRow >::Zero()
{
    static Vector oZero(0);
    return oZero;
}

// Unit vector
template< typename T, unsigned int N, bool t_IsRow >
const Vector< T, N, t_IsRow >&
    Vector< T, N, t_IsRow >::Unit( unsigned int a_uiAxis )
{
    static Vector aoUnits[N];
    static bool abInitialized = false;
    if( !abInitialized )
    {
        for( unsigned int i = 0; i < N; ++i )
        {
            aoUnits[i] = Matrix< T, N >::Identity()[i];
        }
        abInitialized = true;
    }
    return ( a_uiAxis < N ? aoUnits[a_uiAxis] : Zero() );
}

// Get this vector in row/column form
template< typename T, unsigned int N, bool t_bIsRow >
inline typename Vector< T, N, t_bIsRow >::ColumnVectorType
    Vector< T, N, t_bIsRow >::Column() const
{
    return t_bIsRow ? ColumnVectorType( *this ) : *this;
}
template< typename T, unsigned int N, bool t_bIsRow >
inline typename Vector< T, N, t_bIsRow >::RowVectorType
    Vector< T, N, t_bIsRow >::Row() const
{
    return t_bIsRow ? *this : RowVectorType( *this );
}

// Inverse
template< typename T, unsigned int N, bool t_bIsRow >
inline typename Vector< T, N, t_bIsRow >::InverseType
    Vector< T, N, t_bIsRow >::Inverse() const
{
    return InverseType( MatrixType::Inverse() );
}
template< typename T, unsigned int N, bool t_bIsRow >
inline typename Vector< T, N, t_bIsRow >::InverseType
    Vector< T, N, t_bIsRow >::Inverse( bool& a_rbInvertable ) const
{
    return InverseType( MatrixType::Inverse( a_rbInvertable ) );
}

// Get a smaller vector by removing an element
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, ( N > 1 ? N-1 : 1 ), t_bIsRow >
    Vector< T, N, t_bIsRow >::MinusElement( unsigned int a_uiIndex ) const
{
    return Vector< T, ( N > 1 ? N-1 : 1 ), t_bIsRow >(
                                          BaseType::MinusElement( a_uiIndex ) );
}

// Transpose
template< typename T, unsigned int N, bool t_bIsRow >
inline typename Vector< T, N, t_bIsRow >::TransposeType
    Vector< T, N, t_bIsRow >::Transpose() const
{
    return TransposeType( *this );
}

// Dot product
template< typename T, unsigned int N, bool t_bIsRow >
inline T Vector< T, N, t_bIsRow >::Dot( const Vector& ac_roVector ) const
{
    T tResult = 0;
    for( unsigned int i = 0; i < N; ++i )
    {
        tResult += At(i) * ac_roVector[i];
    }
    return tResult;
}
template< typename T, unsigned int N, bool t_bIsRow >
inline T Vector< T, N, t_bIsRow >::Dot( const TransposeType& ac_roVector ) const
{
    return Dot( ac_roVector.Transpose() );
}

// Cross product
// This really ought to be a variadic template, but Visual Studio 2010 doesn't
//  support that feature of C++11, so just implement the one-parameter version.
// For N < 2, "perpendicular" has no meaning, so return Zero
// For N == 2, ignore the parameter and just return a perpendicular vector
// For N == 3, use the formal determinant method
// For N > 3, use the formal determinant method with rows 3 through N-1 filled
//  with unit vectors.
// If this is redone for a compiler that supports variadic templates, then
//  ignore parameters past the (N-2)th and use unit vectors for any missing ones
template< typename T, unsigned int N, bool t_bIsRow >
Vector< T, N, t_bIsRow >
    Vector< T, N, t_bIsRow >::Cross( const Vector& ac_roVector ) const
{
    if( N < 2 )
    {
        return Zero();
    }
    if( N == 2 )
    {
        T aValues[2] = { At(1), -1 * At(0) };
        return Vector( aValues );
    }
    RowVectorType aoVectors[ N > 0 ? N - 1 : 0 ];
    aoVectors[0] = Row();   // exception if N < 2
    aoVectors[1] = ac_roVector.Row();
    for( unsigned int i = 2; i < N - 1; ++i )
    {
        aoVectors[i] = Unit(i).Row();
    }
    Matrix<T, N, ( N > 0 ? N-1 : 0 ) > oMatrix( aoVectors );
    Vector oResult;
    for( unsigned int i = 0; i < N; ++i )
    {
        oResult[i] = oMatrix.MinusColumn(i).Determinant() * ( i%2 == 0 ? 1 : -1 );
    }
    return oResult;
}
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >
    Vector< T, N, t_bIsRow >::Cross( const TransposeType& ac_roVector ) const
{
    return Cross( ac_roVector.Transpose() );
}

// Normalization
template< typename T, unsigned int N, bool t_bIsRow >
inline typename MatrixInverse< T >::Type
    Vector< T, N, t_bIsRow >::Magnitude() const
{
    return std::sqrt( MagnitudeSquared() );
}
template< typename T, unsigned int N, bool t_bIsRow >
inline T Vector< T, N, t_bIsRow >::MagnitudeSquared() const
{
    T result = 0;
    for( unsigned int i = 0; i < N; ++i )
    {
        result += At(i) * At(i);
    }
}
template< typename T, unsigned int N, bool t_bIsRow >
inline void Vector< T, N, t_bIsRow >::Normalize()
{
    typename MatrixInverse< T >::Type magnitude = Magnitude();
    for( unsigned int i = 0; i < N; ++i )
    {
        At(i) /= magnitude;
    }
}
template< typename T, unsigned int N, bool t_bIsRow >
inline typename Vector< T, N, t_bIsRow >::NormalType
    Vector< T, N, t_bIsRow >::Normal() const
{
    NormalType oNormal(*this);
    oNormal.Normalize();
    return oNormal;
}

}   // namespace Math

#endif  // VECTOR__INL
