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

// #include <type_traits>  // for std::is_whateverable checks
#include <utility>  // for std::forward and std::move

namespace Math
{

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
    NumericVectorBase( const MatrixType& ac_roMatrix )
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
    NumericVectorBase( MatrixType&& a_rroMatrix )
    : BaseType( std::forward( a_rroMatrix ) ) {}
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U, unsigned int Q, bool t_bOtherIsRow >
inline NumericVectorBase< T, N, t_bIsRow >::
    NumericVectorBase( const NumericVectorBase< U, Q, t_bOtherIsRow >& ac_roVector,
                       const T& ac_rFill )
    : BaseType( ac_roVector, ac_rFill ) {}
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U, unsigned int Q, bool t_bOtherIsRow >
inline NumericVectorBase< T, N, t_bIsRow >::
    NumericVectorBase( const VectorBase< U, Q, t_bOtherIsRow >& ac_roVector,
                       const T& ac_rFill )
    : BaseType( ac_roVector, ac_rFill ) {}
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U, unsigned int P, unsigned int Q >
inline NumericVectorBase< T, N, t_bIsRow >::
    NumericVectorBase( const MatrixBase< U, P, Q >& ac_roMatrix,
                       const T& ac_rFill = DEFAULT_FILL )
    : BaseType( ac_roMatrix, ac_rFill ) {}
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U >
inline NumericVectorBase< T, N, t_bIsRow >::
    NumericVectorBase( const U& ac_rFill ) : BaseType( ac_rFill ) {}
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U, unsigned int t_uiSize >
inline NumericVectorBase< T, N, t_bIsRow >::
    NumericVectorBase( const U (&ac_raData)[ t_uiSize ],
                       const T& ac_rFill = DEFAULT_FILL )
    : BaseType( ac_raData, ac_rFill ) {}
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U >
inline NumericVectorBase< T, N, t_bIsRow >::
    NumericVectorBase( const U* const ac_cpData,
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
    operator=( NumericVectorBase& a_rroVector )
{
    return BaseType::operator=( ac_roVector );
}
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U, unsigned int Q, bool t_bOtherIsRow >
inline NumericVectorBase< T, N, t_bIsRow >&
    NumericVectorBase< T, N, t_bIsRow >::
    operator=( const NumericVectorBase< U, Q, t_bOtherIsRow >& ac_roVector )
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
    InverseType oResult();
    if( !Inverse( oResult ) )
    {
        oResult = ZERO;
    }
    return oResult;
}
template< typename T, unsigned int N, bool t_bIsRow >
inline NumericVectorBase< T, N, t_bIsRow >::InverseType
    NumericVectorBase< T, N, t_bIsRow >::Inverse( bool& a_rbInvertable )
{
    InverseType oResult();
    a_rbInvertable = Inverse( oResult );
    if( !a_rbInvertable )
    {
        oResult = ZERO;
    }
    return oResult;
}

// Transpose
template< typename T, unsigned int N, bool t_bIsRow >
inline NumericVectorBase< T, N, t_bIsRow >::TransposeType
    NumericVectorBase< T, N, t_bIsRow >::Transpose() const
{
    return TransposeType( *this );
}

// Dot and cross products
template< typename T, unsigned int N, bool t_bIsRow >
inline T NumericVectorBase< T, N, t_bIsRow >::
    Dot( const Vector& ac_roVector ) const
{
    T tResult = 0;
    for( unsigned int i = 0; i < N; ++i )
    {
        tResult += At(i) * ac_roVector[i];
    }
    return T;
}
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector NumericVectorBase< T, N, t_bIsRow >::
    Cross( const Vector& ac_roVector ) const
{
}

// Normalization
template< typename T, unsigned int N, bool t_bIsRow >
inline MatrixInverse< T >::Type
    NumericVectorBase< T, N, t_bIsRow >::Magnitude() const
{
}
template< typename T, unsigned int N, bool t_bIsRow >
inline void NumericVectorBase< T, N, t_bIsRow >::Normalize()
{
}
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< MatrixInverse< T >::Type, N, t_bIsRow >
    NumericVectorBase< T, N, t_bIsRow >::Normal() const
{
}

// TODO

}   // namespace Math

#endif  // _NUMERIC_VECTOR_BASE_INL
