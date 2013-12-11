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

#include <cmath>    // for std::sqrt
// #include <type_traits>  // for std::is_whateverable checks
#include <utility>  // for std::forward and std::move

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

// Destructor doesn't need to do anything
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >::~Vector() {}

// Constructors that forward to base class constructors
// Private so they can only be called by the friend child class
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >::Vector() : BaseType() {}
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >::Vector( const Vector& ac_roVector )
    : BaseType( ac_roVector ) {}
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >::Vector( const BaseType& ac_roVector )
    : BaseType( ac_roVector ) {}
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >::Vector( const RootType& ac_roMatrix )
    : BaseType( ac_roMatrix ) {}
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >::Vector( Vector&& a_rroVector )
    : BaseType( std::forward( a_rroVector ) ) {}
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >::Vector( BaseType&& a_rroVector )
    : BaseType( std::forward( a_rroVector ) ) {}
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >::Vector( RootType&& a_rroMatrix )
    : BaseType( std::forward( a_rroMatrix ) ) {}
template< typename T, unsigned int N, bool t_bIsRow >
template< unsigned int Q, bool t_bOtherIsRow >
inline Vector< T, N, t_bIsRow >::
    Vector( const Vector< T, Q, t_bOtherIsRow >& ac_roVector,
            const T& ac_rFill )
    : BaseType( ac_roVector, ac_rFill ) {}
template< typename T, unsigned int N, bool t_bIsRow >
template< unsigned int Q, bool t_bOtherIsRow >
inline Vector< T, N, t_bIsRow >::
    Vector( const VectorBase< T, Q, t_bOtherIsRow >& ac_roVector,
            const T& ac_rFill )
    : BaseType( ac_roVector, ac_rFill ) {}
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U >
inline Vector< T, N, t_bIsRow >::
    Vector( const MatrixBase< U, ROWS, COLUMNS >& ac_roMatrix )
    : BaseType( ac_roMatrix );
template< typename T, unsigned int N, bool t_bIsRow >
template< unsigned int P, unsigned int Q >
inline Vector< T, N, t_bIsRow >::
    Vector( const MatrixBase< T, P, Q >& ac_roMatrix, const T& ac_rFill )
    : BaseType( ac_roMatrix, ac_rFill ) {}
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >::Vector( const T& ac_rFill )
    : BaseType( ac_rFill ) {}
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >::Vector( const T (&ac_raData)[ N ] )
    : BaseType( ac_raData ) {}
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >::Vector( const T* const ac_cpData,
                                         const unsigned int ac_uiSize,
                                         const T& ac_rFill )
    : BaseType( ac_cpData, ac_uiSize, ac_rFill ) {}

// Copy assign, move assign, and assign from a different type of numeric vector
// These are specified to remove ambiguity between MatrixBase::operator= and
// VectorBase::operator=, since both could work - MatrixBase::operator= is
// available through inheritance from Matrix, VectorBase::operator= through
// inheritance from VectorBase.
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >&
    Vector< T, N, t_bIsRow >::operator=( const Vector& ac_roVector )
{
    return BaseType::operator=( ac_roVector );
}
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >&
    Vector< T, N, t_bIsRow >::operator=( Vector&& a_rroVector )
{
    return BaseType::operator=( ac_roVector );
}
template< typename T, unsigned int N, bool t_bIsRow >
template< unsigned int Q, bool t_bOtherIsRow >
inline Vector< T, N, t_bIsRow >& Vector< T, N, t_bIsRow >::
    operator=( const Vector< T, Q, t_bOtherIsRow >& ac_roVector )
{
    return BaseType::operator=( ac_roVector );
}

// Element access - hides matrix class row-returning implementation
template< typename T, unsigned int N, bool t_bIsRow >
inline T& Vector< T, N, t_bIsRow >::operator[]( unsigned int a_uiIndex )
{
    return At( a_uiIndex );
}
template< typename T, unsigned int N, bool t_bIsRow >
inline const T&
    Vector< T, N, t_bIsRow >::operator[]( unsigned int a_uiIndex ) const
{
    return At( a_uiIndex );
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
inline Vector< T, ( N > 0 ? N-1 : 0 ), t_bIsRow >
    Vector< T, N, t_bIsRow >::MinusElement( unsigned int a_uiIndex ) const
{
    return Vector< T, ( N > 0 ? N-1 : 0 ), t_bIsRow >(
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
    return T;
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
        aoVectors[i] = RowVectorType( Unit(i) );
    }
    Matrix<T, N, ( N > 0 ? N-1 : 0 ) > oMatrix( aoVectors );
    Vector oResult;
    for( unsigned int i = 0; i < N; ++i )
    {
        oResult[i] = ( i%2 == 0 ? 1 : -1 ) * oMatrix.MinusColumn(i).Determinant();
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

// Addition
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

// Subtraction
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

#endif  // VECTOR__INL
