/******************************************************************************
 * File:               NumericVectorBase.inl
 * Author:             Elizabeth Lowry
 * Date Created:       November 25, 2013
 * Description:        Inline and other function implementations for
 *                      NumericVectorBase.
 * Last Modified:      November 25, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef _NUMERIC_VECTOR_BASE_INL_
#define _NUMERIC_VECTOR_BASE_INL_

#include <cmath>    // for std::sqrt
// #include <type_traits>  // for std::is_whateverable checks
#include <utility>  // for std::forward and std::move

namespace Math
{

// Zero vector
template< typename T, unsigned int N, bool t_IsRow >
ZERO_VECTOR< T, N, t_IsRow >( 0 );
template< typename T, unsigned int N, bool t_IsRow >
NumericVectorBase< T, N, t_IsRow >::ZERO = ZERO_VECTOR< T, N, t_IsRow >;

// Unit vector
template< typename T, unsigned int N, unsigned int I, bool t_IsRow >
UNIT_VECTOR< T, N, I, t_IsRow >( IDENTITY_MATRIX< T, N >[ I ] );
template< typename T, unsigned int N, bool t_IsRow >
template< unsigned int I >
NumericVectorBase< T, N, t_IsRow >::UNIT< I > = UNIT_VECTOR< T, N, I, t_IsRow >;

// Destructor doesn't need to do anything
template< typename T, unsigned int N, bool t_bIsRow >
inline NumericVectorBase< T, N, t_bIsRow >::~NumericVectorBase() {}

// Constructors that forward to base class constructors
// Private so they can only be called by the friend child class
template< typename T, unsigned int N, bool t_bIsRow >
inline NumericVectorBase< T, N, t_bIsRow >::NumericVectorBase() : BaseType() {}
template< typename T, unsigned int N, bool t_bIsRow >
inline NumericVectorBase< T, N, t_bIsRow >::
    NumericVectorBase( const NumericVectorBase& ac_roVector )
    : BaseType( ac_roVector ) {}
template< typename T, unsigned int N, bool t_bIsRow >
inline NumericVectorBase< T, N, t_bIsRow >::
    NumericVectorBase( const BaseType& ac_roVector )
    : BaseType( ac_roVector ) {}
template< typename T, unsigned int N, bool t_bIsRow >
inline NumericVectorBase< T, N, t_bIsRow >::
    NumericVectorBase( const RootType& ac_roMatrix )
    : BaseType( ac_roMatrix ) {}
template< typename T, unsigned int N, bool t_bIsRow >
inline NumericVectorBase< T, N, t_bIsRow >::
    NumericVectorBase( NumericVectorBase&& a_rroVector )
    : BaseType( std::forward( a_rroVector ) ) {}
template< typename T, unsigned int N, bool t_bIsRow >
inline NumericVectorBase< T, N, t_bIsRow >::
    NumericVectorBase( BaseType&& a_rroVector )
    : BaseType( std::forward( a_rroVector ) ) {}
template< typename T, unsigned int N, bool t_bIsRow >
inline NumericVectorBase< T, N, t_bIsRow >::
    NumericVectorBase( RootType&& a_rroMatrix )
    : BaseType( std::forward( a_rroMatrix ) ) {}
template< typename T, unsigned int N, bool t_bIsRow >
template< unsigned int Q, bool t_bOtherIsRow >
inline NumericVectorBase< T, N, t_bIsRow >::
    NumericVectorBase( const NumericVectorBase< T, Q, t_bOtherIsRow >& ac_roVector,
                       const T& ac_rFill )
    : BaseType( ac_roVector, ac_rFill ) {}
template< typename T, unsigned int N, bool t_bIsRow >
template< unsigned int Q, bool t_bOtherIsRow >
inline NumericVectorBase< T, N, t_bIsRow >::
    NumericVectorBase( const VectorBase< T, Q, t_bOtherIsRow >& ac_roVector,
                       const T& ac_rFill )
    : BaseType( ac_roVector, ac_rFill ) {}
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U >
inline NumericVectorBase< T, N, t_bIsRow >::
    NumericVectorBase( const MatrixBase< U, ROWS, COLUMNS >& ac_roMatrix )
    : BaseType( ac_roMatrix );
template< typename T, unsigned int N, bool t_bIsRow >
template< unsigned int P, unsigned int Q >
inline NumericVectorBase< T, N, t_bIsRow >::
    NumericVectorBase( const MatrixBase< T, P, Q >& ac_roMatrix,
                       const T& ac_rFill = DEFAULT_FILL )
    : BaseType( ac_roMatrix, ac_rFill ) {}
template< typename T, unsigned int N, bool t_bIsRow >
inline NumericVectorBase< T, N, t_bIsRow >::
    NumericVectorBase( const T& ac_rFill ) : BaseType( ac_rFill ) {}
template< typename T, unsigned int N, bool t_bIsRow >
inline NumericVectorBase< T, N, t_bIsRow >::
    NumericVectorBase( const T (&ac_raData)[ N ] )
    : BaseType( ac_raData ) {}
template< typename T, unsigned int N, bool t_bIsRow >
inline NumericVectorBase< T, N, t_bIsRow >::
    NumericVectorBase( const T* const ac_cpData,
                       const unsigned int ac_uiSize,
                       const T& ac_rFill = DEFAULT_FILL )
    : BaseType( ac_cpData, ac_uiSize, ac_rFill ) {}

// Copy assign, move assign, and assign from a different type of numeric vector
// These are specified to remove ambiguity between MatrixBase::operator= and
// VectorBase::operator=, since both could work - MatrixBase::operator= is
// available through inheritance from Matrix, VectorBase::operator= through
// inheritance from VectorBase.
template< typename T, unsigned int N, bool t_bIsRow >
inline NumericVectorBase< T, N, t_bIsRow >&
    NumericVectorBase< T, N, t_bIsRow >::
    operator=( const NumericVectorBase& ac_roVector )
{
    return BaseType::operator=( ac_roVector );
}
template< typename T, unsigned int N, bool t_bIsRow >
inline NumericVectorBase< T, N, t_bIsRow >&
    NumericVectorBase< T, N, t_bIsRow >::
    operator=( NumericVectorBase&& a_rroVector )
{
    return BaseType::operator=( ac_roVector );
}
template< typename T, unsigned int N, bool t_bIsRow >
template< unsigned int Q, bool t_bOtherIsRow >
inline NumericVectorBase< T, N, t_bIsRow >&
    NumericVectorBase< T, N, t_bIsRow >::
    operator=( const NumericVectorBase< T, Q, t_bOtherIsRow >& ac_roVector )
{
    return BaseType::operator=( ac_roVector );
}

// Element access - hides matrix class row-returning implementation
template< typename T, unsigned int N, bool t_bIsRow >
inline T& NumericVectorBase< T, N, t_bIsRow >::
    operator[]( unsigned int a_uiIndex )
{
    return At( a_uiIndex );
}
template< typename T, unsigned int N, bool t_bIsRow >
inline const T& NumericVectorBase< T, N, t_bIsRow >::
    operator[]( unsigned int a_uiIndex ) const
{
    return At( a_uiIndex );
}

// Get this vector in row/column form
template< typename T, unsigned int N, bool t_bIsRow >
inline NumericVectorBase< T, N, t_bIsRow >::ColumnVectorType
    NumericVectorBase< T, N, t_bIsRow >::Column() const
{
    return t_bIsRow ? ColumnVectorType( *this ) : *this;
}
template< typename T, unsigned int N, bool t_bIsRow >
inline NumericVectorBase< T, N, t_bIsRow >::RowVectorType
    NumericVectorBase< T, N, t_bIsRow >::Row() const
{
    return t_bIsRow ? *this : RowVectorType( *this );
}

// Inverse
template< typename T, unsigned int N, bool t_bIsRow >
inline NumericVectorBase< T, N, t_bIsRow >::InverseType
    NumericVectorBase< T, N, t_bIsRow >::Inverse() const
{
    return InverseType( MatrixType::Inverse() );
}
template< typename T, unsigned int N, bool t_bIsRow >
inline NumericVectorBase< T, N, t_bIsRow >::InverseType
    NumericVectorBase< T, N, t_bIsRow >::Inverse( bool& a_rbInvertable ) const
{
    return InverseType( MatrixType::Inverse( a_rbInvertable ) );
}

// Get a smaller vector by removing an element
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N-1, t_bIsRow > NumericVectorBase< T, N, t_bIsRow >::
    MinusElement( unsigned int a_uiIndex ) const
{
    return Vector< T, N-1, t_bIsRow >( BaseType::MinusElement( a_uiIndex ) );
}

// Transpose
template< typename T, unsigned int N, bool t_bIsRow >
inline NumericVectorBase< T, N, t_bIsRow >::TransposeType
    NumericVectorBase< T, N, t_bIsRow >::Transpose() const
{
    return TransposeType( *this );
}

// Dot product
template< typename T, unsigned int N, bool t_bIsRow >
inline T NumericVectorBase< T, N, t_bIsRow >::
    Dot( const ChildType& ac_roVector ) const
{
    T tResult = 0;
    for( unsigned int i = 0; i < N; ++i )
    {
        tResult += At(i) * ac_roVector[i];
    }
    return T;
}

// Cross product
template< typename T, unsigned int N, bool t_bIsRow >
inline NumericVectorBase< T, N, t_bIsRow >::ChildType
    NumericVectorBase< T, N, t_bIsRow >::
    Cross( const ChildType (&ac_raoVectors)[ N - 2 ] ) const
{
    RowVectorType aoVectors[ N - 1 ];
    acpcoVectors[0] = Row();
    for( unsigned int i = 1; i < N; ++i )
    {
        acpcoVectors[i] = ac_raoVectors[i-1].Row();
    }
    return Cross( aoVectors );
}
template< typename T, unsigned int N, bool t_bIsRow >
inline NumericVectorBase< T, N, t_bIsRow >::ChildType
    NumericVectorBase< T, N, t_bIsRow >::
    Cross( const ChildType* const (&ac_racpoVectors)[ N - 2 ] ) const
{
    const RowVectorType aoVectors[ N - 1 ];
    acpcoVectors[0] = Row();
    for( unsigned int i = 1; i < N; ++i )
    {
        acpcoVectors[i] = ac_raoVectors[i-1]->Row();
    }
    return Cross( aoVectors );
}
template< typename T, unsigned int N, bool t_bIsRow >
inline NumericVectorBase< T, N, t_bIsRow >::ChildType
    NumericVectorBase< T, N, t_bIsRow >::
    Cross( const RowVectorType (&ac_raoVectors)[ N - 1 ] )
{
    Matrix< T, N-1, N > oMatrix( ac_raoVectors );
    ChildType oCross;
    for( unsigned int i = 0; i < N; ++i )
    {
        oCross[i] = ( (2*(i%2)) - 1 ) * oMatrix.MinusColumn(i).Determinant();
    }
    return oCross;
}

// Normalization
template< typename T, unsigned int N, bool t_bIsRow >
inline typename MatrixInverse< T >::Type
    NumericVectorBase< T, N, t_bIsRow >::Magnitude() const
{
    return std::sqrt( MagnitudeSquared() );
}
template< typename T, unsigned int N, bool t_bIsRow >
inline T
    NumericVectorBase< T, N, t_bIsRow >::MagnitudeSquared() const
{
    T result = 0;
    for( unsigned int i = 0; i < N; ++i )
    {
        result += At(i) * At(i);
    }
}
template< typename T, unsigned int N, bool t_bIsRow >
inline void NumericVectorBase< T, N, t_bIsRow >::Normalize()
{
    typename MatrixInverse< T >::Type magnitude = Magnitude();
    for( unsigned int i = 0; i < N; ++i )
    {
        At(i) /= magnitude;
    }
}
template< typename T, unsigned int N, bool t_bIsRow >
inline NumericVectorBase< T, N, t_bIsRow >::NormalType
    NumericVectorBase< T, N, t_bIsRow >::Normal() const
{
    NormalType oNormal(*this);
    oNormal.Normalize();
    return oNormal;
}

// Addition
template< typename T, unsigned int N, bool t_bIsRow >
inline NumericVectorBase< T, N, t_bIsRow >::ChildType&
    NumericVectorBase< T, N, t_bIsRow >::
    operator+=( const ChildType& ac_roVector )
{
    for( unsigned int i = 0; i < N; ++i )
    {
        At(i) += ac_roVector[i];
    }
    return *this;
}
template< typename T, unsigned int N, bool t_bIsRow >
inline NumericVectorBase< T, N, t_bIsRow >::ChildType&
    NumericVectorBase< T, N, t_bIsRow >::
    operator+=( const TransposeType& ac_roVector )
{
    for( unsigned int i = 0; i < N; ++i )
    {
        At(i) += ac_roVector[i];
    }
    return *this;
}
template< typename T, unsigned int N, bool t_bIsRow >
inline NumericVectorBase< T, N, t_bIsRow >::ChildType
    NumericVectorBase< T, N, t_bIsRow >::
    operator+( const ChildType& ac_roVector ) const
{
    ChildType oCopy(*this);
    oCopy += ac_roVector;
    return oCopy;
}
template< typename T, unsigned int N, bool t_bIsRow >
inline NumericVectorBase< T, N, t_bIsRow >::ChildType
    NumericVectorBase< T, N, t_bIsRow >::
    operator+( const TransposeType& ac_roVector ) const
{
    ChildType oCopy(*this);
    oCopy += ac_roVector;
    return oCopy;
}

// Subtraction
template< typename T, unsigned int N, bool t_bIsRow >
inline NumericVectorBase< T, N, t_bIsRow >::ChildType&
    NumericVectorBase< T, N, t_bIsRow >::
    operator-=( const ChildType& ac_roVector )
{
    for( unsigned int i = 0; i < N; ++i )
    {
        At(i) -= ac_roVector[i];
    }
    return *this;
}
template< typename T, unsigned int N, bool t_bIsRow >
inline NumericVectorBase< T, N, t_bIsRow >::ChildType&
    NumericVectorBase< T, N, t_bIsRow >::
    operator-=( const TransposeType& ac_roVector )
{
    for( unsigned int i = 0; i < N; ++i )
    {
        At(i) -= ac_roVector[i];
    }
    return *this;
}
template< typename T, unsigned int N, bool t_bIsRow >
inline NumericVectorBase< T, N, t_bIsRow >::ChildType
    NumericVectorBase< T, N, t_bIsRow >::
    operator-( const ChildType& ac_roVector ) const
{
    ChildType oCopy(*this);
    oCopy -= ac_roVector;
    return oCopy;
}
template< typename T, unsigned int N, bool t_bIsRow >
inline NumericVectorBase< T, N, t_bIsRow >::ChildType
    NumericVectorBase< T, N, t_bIsRow >::
    operator-( const TransposeType& ac_roVector ) const
{
    ChildType oCopy(*this);
    oCopy -= ac_roVector;
    return oCopy;
}

// Override scalar multiplication/division/modulo operators to return the
// correct type
template< typename T, unsigned int N, bool t_bIsRow >
inline NumericVectorBase< T, N, t_bIsRow >::ChildType
    NumericVectorBase< T, N, t_bIsRow >::operator*( const T& ac_rScalar ) const
{
    return ChildType( MatrixType::operator*( ac_rScalar ) );
}
template< typename T, unsigned int N, bool t_bIsRow >
inline NumericVectorBase< T, N, t_bIsRow >::ChildType
    NumericVectorBase< T, N, t_bIsRow >::operator/( const T& ac_rScalar ) const
{
    return ChildType( MatrixType::operator/( ac_rScalar ) );
}
template< typename T, unsigned int N, bool t_bIsRow >
inline NumericVectorBase< T, N, t_bIsRow >::ChildType
    NumericVectorBase< T, N, t_bIsRow >::operator%( const T& ac_rScalar ) const
{
    return ChildType( MatrixType::operator%( ac_rScalar ) );
}

}   // namespace Math

#endif  // _NUMERIC_VECTOR_BASE_INL
