/******************************************************************************
 * File:               Vector.inl
 * Author:             Elizabeth Lowry
 * Date Created:       November 25, 2013
 * Description:        Inline and other function implementations for Vector.h.
 * Last Modified:      February 12, 2014
 * Last Modification:  Refactoring.
 ******************************************************************************/

#ifndef VECTOR__INL
#define VECTOR__INL

#include "../Declarations/Vector.h"
#include "../Declarations/Functions.h"
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

// Assign to arrays
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U, unsigned int P >
typename ArrayReference< U, P >::type Vector< T, N, t_bIsRow >::
    AssignToRow( typename ArrayReference< U, P >::type a_raData ) const
{/*
    if( !std::is_copy_assignable< U >::value )
    {
        throw exception("Non-copy-assignable type");
    }
    if( !std::is_convertible< T, U >:: value )
    {
        throw exception("Non-convertable input type");
    }  /**/
    for( unsigned int i = 0; i < N && i < P; ++i )
    {
        a_raData[i] = At(i);
    }
    return a_raData;
}
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U, unsigned int P >
typename ArrayReference< U, P >::type Vector< T, N, t_bIsRow >::
    AssignToColumn( typename ArrayReference< U, P >::type a_raData,
                    unsigned int a_uiColumns,
                    unsigned int a_uiAssignToColumn ) const
{/*
    if( !std::is_copy_assignable< U >::value )
    {
        throw exception("Non-copy-assignable type");
    }
    if( !std::is_convertible< T, U >:: value )
    {
        throw exception("Non-convertable input type");
    }  /**/
    for( unsigned int i = 0; i < N && i < P; ++i )
    {
        a_raData[ ( i * a_uiColumns ) + a_uiAssignToColumn ] = At(i);
    }
    return a_raData;
}
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U, unsigned int P, unsigned int Q >
typename Array2DReference< U, P, Q >::type Vector< T, N, t_bIsRow >::
    AssignToColumn( typename Array2DReference< U, P, Q>::type a_raaData,
                    unsigned int a_uiAssignToColumn ) const
{/*
    if( !std::is_copy_assignable< U >::value )
    {
        throw exception("Non-copy-assignable type");
    }
    if( !std::is_convertible< T, U >:: value )
    {
        throw exception("Non-convertable input type");
    }  /**/
    for( unsigned int i = 0; i < N && i < P; ++i )
    {
        a_raaData[i][a_uiAssignToColumn] = At(i);
    }
    return a_raaData;
}
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U >
U* Vector< T, N, t_bIsRow >::AssignToRow( U* const a_cpData,
                                          unsigned int a_uiSize ) const
{/*
    if( !std::is_copy_assignable< U >::value )
    {
        throw exception("Non-copy-assignable type");
    }
    if( !std::is_convertible< T, U >:: value )
    {
        throw exception("Non-convertable input type");
    }  /**/
    for( unsigned int i = 0; i < N && i < a_uiSize; ++i )
    {
        a_cpData[i] = At(i);
    }
    return a_cpData;
}
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U >
U* Vector< T, N, t_bIsRow >::AssignToColumn( U* const a_cpData,
                                             unsigned int a_uiColumns,
                                             unsigned int a_uiAssignToColumn,
                                             unsigned int a_uiRows ) const
{/*
    if( !std::is_copy_assignable< U >::value )
    {
        throw exception("Non-copy-assignable type");
    }
    if( !std::is_convertible< T, U >:: value )
    {
        throw exception("Non-convertable input type");
    }  /**/
    for( unsigned int i = 0; i < N && i < a_uiRows; ++i )
    {
        a_cpData[ ( i * a_uiColumns ) + a_uiAssignToColumn ] = At(i);
    }
    return a_cpData;
}
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U >
U** Vector< T, N, t_bIsRow >::AssignToColumn( U* const* const a_cpcpData,
                                              unsigned int a_uiAssignToColumn,
                                              unsigned int a_uiRows ) const
{/*
    if( !std::is_copy_assignable< U >::value )
    {
        throw exception("Non-copy-assignable type");
    }
    if( !std::is_convertible< T, U >:: value )
    {
        throw exception("Non-convertable input type");
    }  /**/
    for( unsigned int i = 0; i < N && i < a_uiRows; ++i )
    {
        a_cpcpData[i][a_uiAssignToColumn] = At(i);
    }
    return a_cpcpData;
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
    return InverseType( BaseType::Inverse() );
}
template< typename T, unsigned int N, bool t_bIsRow >
inline typename Vector< T, N, t_bIsRow >::InverseType
    Vector< T, N, t_bIsRow >::Inverse( bool& a_rbInvertable ) const
{
    return InverseType( BaseType::Inverse( a_rbInvertable ) );
}

// Get a smaller vector by removing an element
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, ( N > 1 ? N-1 : 1 ), t_bIsRow > Vector< T, N, t_bIsRow >::
    MinusElement( unsigned int a_uiIndex ) const
{
    if( N == 1 )
    {
        throw( std::out_of_range( "Cannot remove element if there are none" ) );
    }
    Vector< T, ( N > 1 ? N-1 : 1 ), t_bIsRow >
        oResult( Vector(*this).Shift( -1 - a_uiIndex ) );
    return oResult.Shift( a_uiIndex );
}

// Shift elements by the given number of places
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >& Vector< T, N, t_bIsRow >::Shift( int a_iPlaces )
{
    Vector oCopy(*this);
    for( unsigned int i = 0; i < N; ++i )
    {
        At( Scroll<int>( i + a_iPlaces, N ) ) = oCopy[i];
    }
    return *this;
}

// Transpose
template< typename T, unsigned int N, bool t_bIsRow >
inline typename Vector< T, N, t_bIsRow >::TransposeType
    Vector< T, N, t_bIsRow >::Transpose() const
{
    return TransposeType( *this );
}
template< typename T, unsigned int N, bool t_bIsRow >
inline typename Vector< T, N, t_bIsRow >::TransposeType
    Vector< T, N, t_bIsRow >::ConjugateTranspose() const
{
    return TransposeType( BaseType::ConjugateTranspose() );
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
        // return this vector rotated 90 degrees clockwise, which is what you'd
        // get by crossing a 3D version of this vector with the Z-axis.
        T aValues[N];
        aValues[0] = At(1);
        aValues[1] = -1 * At(0);
        return Vector( aValues );
    }
    RowVectorType aoVectors[ N - 1 ];
    aoVectors[0] = Row();   // exception if N < 2
    aoVectors[1] = ac_roVector.Row();   // exception if N < 3
    for( unsigned int i = 2; i < N - 1; ++i )
    {
        aoVectors[i] = Unit(i).Row();
    }
    Matrix<T, ( N > 0 ? N-1 : 0 ), N > oMatrix( aoVectors );
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
inline typename InverseOf< T >::Type Vector< T, N, t_bIsRow >::Magnitude() const
{
    InverseT magnitudeSquared = MagnitudeSquared();
    return ( (InverseT)1.0 == magnitudeSquared
                ? (InverseT)1.0 : std::sqrt( magnitudeSquared ) );
}
template< typename T, unsigned int N, bool t_bIsRow >
inline T Vector< T, N, t_bIsRow >::MagnitudeSquared() const
{
    T result = 0;
    for( unsigned int i = 0; i < N; ++i )
    {
        result += At(i) * At(i);
    }
    return result;
}
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >& Vector< T, N, t_bIsRow >::Normalize()
{
    InverseT magnitude = Magnitude();
    for( unsigned int i = 0; i < N; ++i )
    {
        At(i) = (T)( At(i) / magnitude );
    }
    return *this;
}
template< typename T, unsigned int N, bool t_bIsRow >
inline typename Vector< T, N, t_bIsRow >::NormalType
    Vector< T, N, t_bIsRow >::Normal() const
{
    NormalType oNormal(*this);
    oNormal.Normalize();
    return oNormal;
}

// Hidden parent functionality is defined anyway so the compiler won't complain
template< typename T, unsigned int N, bool t_bIsRow >
inline T Vector< T, N, t_bIsRow >::Determinant()
{
    return BaseType::Determinant();
}
template< typename T, unsigned int N, bool t_bIsRow >
inline T Vector< T, N, t_bIsRow >::
    Minor( unsigned int a_uiRow, unsigned int a_uiColumn )
{
    return BaseType::Minor( a_uiRow, a_uiColumn );
}
template< typename T, unsigned int N, bool t_bIsRow >
inline typename Vector< T, N, t_bIsRow >::BaseType::ColumnVectorType
    Vector< T, N, t_bIsRow >::Column( unsigned int ac_uiIndex ) const
{
    return BaseType::Column( ac_uiIndex );
}
template< typename T, unsigned int N, bool t_bIsRow >
inline typename Vector< T, N, t_bIsRow >::BaseType::RowVectorType
    Vector< T, N, t_bIsRow >::Row( unsigned int ac_uiIndex ) const
{
    return BaseType::Row( ac_uiIndex );
}
template< typename T, unsigned int N, bool t_bIsRow >
inline Matrix< T, ( !t_bIsRow && N > 1 ? N-1 : 1 ), ( t_bIsRow && N > 1 ? N-1 : 1 ) >
    Vector< T, N, t_bIsRow >::
    MinusRowAndColumn( unsigned int a_uiRow, unsigned int a_uiColumn ) const
{
    return BaseType::MinusRowAndColumn( a_uiRow, a_uiColumn );
}
template< typename T, unsigned int N, bool t_bIsRow >
inline Matrix< T, ( !t_bIsRow ? N : 1 ), ( t_bIsRow && N > 1 ? N-1 : 1 ) >
    Vector< T, N, t_bIsRow >::MinusColumn( unsigned int a_uiColumn ) const
{
    return BaseType::MinusColumn( a_uiColumn );
}
template< typename T, unsigned int N, bool t_bIsRow >
inline Matrix< T, ( !t_bIsRow && N > 1 ? N-1 : 1 ), ( t_bIsRow ? N : 1 ) >
    Vector< T, N, t_bIsRow >::MinusRow( unsigned int a_uiRow ) const
{
    return BaseType::MinusRow( a_uiRow );
}
template< typename T, unsigned int N, bool t_bIsRow >
inline typename Vector< T, N, t_bIsRow >::BaseType&
    Vector< T, N, t_bIsRow >::Shift( int a_iRight, int a_iDown )
{
    return BaseType::Shift( a_iRight, a_iDown );
}

}   // namespace Math

#endif  // VECTOR__INL
