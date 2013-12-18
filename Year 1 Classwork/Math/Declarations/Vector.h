/******************************************************************************
 * File:               Vector.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 25, 2013
 * Description:        Base class for vectors of numeric type.
 * Last Modified:      December 10, 2013
 * Last Modification:  Debugging.
 ******************************************************************************/

#ifndef VECTOR__H
#define VECTOR__H

#include "Matrix.h"
#include "VectorBase.h"
// #include <type_traits>   // for common_type

namespace Math
{
    
// A vector handles some things a bit differently than a matrix of the same size
template< typename T, unsigned int N, bool t_bIsRow = true >
class Vector
    : public virtual VectorBase< T, N, t_bIsRow >,
      public virtual Matrix< T, ( t_bIsRow ? 1 : N ), ( t_bIsRow ? N : 1 ) >
{
public:

    // simplify typing
    typedef MatrixBase< T, ROWS, COLUMNS > RootType;
    typedef VectorBase< T, N, t_bIsRow > BaseType;
    typedef Vector< T, N, false > ColumnVectorType;
    typedef Vector< T, N > RowVectorType;
    typedef Matrix< T, ROWS, COLUMNS > MatrixType;
    typedef Vector< T, 1 > IdentityType;
    typedef Vector< typename MatrixInverse< T >::Type, N, !t_bIsRow > InverseType;
    typedef Vector< T, N, !t_bIsRow > TransposeType;
    typedef Vector< typename MatrixInverse< T >::Type, N, t_bIsRow > NormalType;

    // inherit assignment operators
    using BaseType::operator=;

    // destructor
    virtual ~Vector();

    // Constructors that forward to base class constructors
    Vector();
    Vector( const Vector& ac_roVector );
    Vector( const BaseType& ac_roVector );
    Vector( const RootType& ac_roMatrix );
    Vector( Vector&& a_rroVector );
    Vector( BaseType&& a_rroVector );
    Vector( RootType&& a_rroMatrix );
    template< typename U, unsigned int Q, bool t_bOtherIsRow >
    Vector( const Vector< U, Q, t_bOtherIsRow >& ac_roVector,
            const T& ac_rFill = DefaultFill< T >() );
    template< unsigned int Q, bool t_bOtherIsRow >
    Vector( Vector< T, Q, t_bOtherIsRow >&& a_rroVector,
            const T& ac_rFill = DefaultFill< T >() );
    template< typename U, unsigned int Q, bool t_bOtherIsRow >
    Vector( const VectorBase< U, Q, t_bOtherIsRow >& ac_roVector,
            const T& ac_rFill = DefaultFill< T >() );
    template< unsigned int Q, bool t_bOtherIsRow >
    Vector( VectorBase< T, Q, t_bOtherIsRow >&& a_rroVector,
            const T& ac_rFill = DefaultFill< T >() );
    template< typename U, unsigned int P, unsigned int Q >
    Vector( const MatrixBase< U, P, Q >& ac_roMatrix,
            const T& ac_rFill = DefaultFill< T >() );
    template< unsigned int P, unsigned int Q >
    Vector( MatrixBase< T, P, Q >&& a_rroMatrix,
            const T& ac_rFill = DefaultFill< T >() );
    Vector( const T& ac_rFill );
    Vector( const T (&ac_raData)[ N ] );
    Vector( const T* const ac_cpData,
            const unsigned int ac_uiSize,
            const T& ac_rFill = DefaultFill< T >() );
    
    // Copy assign, move assign, and assign from a different type of vector
    // These are specified to remove ambiguity between MatrixBase::operator= and
    // VectorBase::operator=, since both could work - MatrixBase::operator= is
    // available through inheritance from Matrix, VectorBase::operator= through
    // inheritance from VectorBase.
    template< typename U, unsigned int Q, bool t_bOtherIsRow >
    Vector& operator=( const Vector< U, Q, t_bOtherIsRow >& ac_roVector );
    template< unsigned int Q, bool t_bOtherIsRow >
    Vector& operator=( Vector< T, Q, t_bOtherIsRow >&& a_rroVector );
    
    // Element access - hides matrix class row-returning implementation
    //T& operator[]( unsigned int a_uiIndex );
    //const T& operator[]( unsigned int a_uiIndex ) const;
    using BaseType::operator[];

    // Non-virtual overrides to return correct type, since return type is
    // concrete and not a pointer or reference.
    ColumnVectorType Column() const;
    RowVectorType Row() const;
    InverseType Inverse() const;
    InverseType Inverse( bool& a_rbInvertable ) const;
    Vector< T, ( N > 0 ? N-1 : 0 ), t_bIsRow >
        MinusElement( unsigned int a_uiIndex ) const;
    TransposeType Transpose() const;

    // Dot and cross products
    T Dot( const Vector& ac_roVector ) const;
    T Dot( const TransposeType& ac_roVector ) const;
    Vector Cross( const Vector& ac_roVector
                        = ( N > 2 ? Unit(1) : Zero() ) ) const;
    Vector Cross( const TransposeType& ac_roVector
                        = ( N > 2 ? TransposeType::Unit(1)
                                  : TransposeType::Zero() ) ) const;

    // Normalization
    typename MatrixInverse< T >::Type Magnitude() const;
    T MagnitudeSquared() const; // for efficiency in complex calculations
    void Normalize();
    NormalType Normal() const;

    // Inherit matrix multiplication and division
    using MatrixType::operator*;
    using MatrixType::operator/;

    // Scalar multiplication/division/modulo overrides to return correct type
    template< typename U >
    Vector& operator*=( const U& ac_rScalar );
    template< typename U >
    Vector operator*( const U& ac_rScalar ) const;
    template< typename U >
    Vector& operator/=( const U& ac_rScalar );
    template< typename U >
    Vector operator/( const U& ac_rScalar ) const;
    template< typename U >
    Vector& operator%=( const U& ac_rScalar );
    template< typename U >
    Vector operator%( const U& ac_rScalar ) const;

    // Matrix addition/subtraction overrides to return correct type
    Vector& operator+=( const MatrixType& ac_roMatrix );
    Vector operator+( const MatrixType& ac_roMatrix ) const;
    Vector& operator-=( const MatrixType& ac_roMatrix );
    Vector operator-( const MatrixType& ac_roMatrix ) const;

    // Vector addition and subtraction
    // Non-virtual overrides for arithmatic with another vector - vector
    // implementation doesn't care whether the other vector is a row vector or a
    // column vector, as arithmatic with a matrix does.  If either object is
    // being explicitly treated a a matrix, then a user should expect matrix-
    // -style arithmatic.  If this object is instead being explicitly treated as
    // the vector it is, then a user should expect vector-style arithmatic.
    Vector& operator+=( const Vector& ac_roVector );
    Vector& operator+=( const TransposeType& ac_roVector );
    Vector operator+( const Vector& ac_roVector ) const;
    Vector operator+( const TransposeType& ac_roVector ) const;
    Vector& operator-=( const Vector& ac_roVector );
    Vector& operator-=( const TransposeType& ac_roVector );
    Vector operator-( const Vector& ac_roVector ) const;
    Vector operator-( const TransposeType& ac_roVector ) const;

    // constant references to zero and unit vectors
    static const Vector& Zero();
    static const Vector& Unit( unsigned int a_uiAxis );

private:

    // Hide parent class functions that you shouldn't be using unless you are
    // explicitly treating this object as a matrix, either via casting or via
    // a pointer or reference of the parent type
    T Determinant();
    T Minor( unsigned int a_uiRow, unsigned int a_uiColumn );

    // Non-virtual override - if explicitly treated as a matrix, then matrix
    // implementation should be available, otherwise no implementation should be
    // available
    typedef typename MatrixType::ColumnVectorType BaseColumnVectorType;
    BaseColumnVectorType Column( unsigned int ac_uiIndex ) const;
    typedef typename MatrixType::RowVectorType BaseRowVectorType;
    BaseRowVectorType Row( unsigned int ac_uiIndex ) const;
    Matrix< T, ( !t_bIsRow && N > 0 ? N-1 : 0 ), ( t_bIsRow && N > 0 ? N-1 : 0 ) >
        MinusRowAndColumn( unsigned int a_uiRow, unsigned int a_uiColumn ) const;
    Matrix< T, ( !t_bIsRow ? N : 1 ), ( t_bIsRow && N > 0 ? N-1 : 0 ) >
        MinusColumn( unsigned int a_uiColumn ) const;
    Matrix< T, ( !t_bIsRow && N > 0 ? N-1 : 0 ), ( t_bIsRow ? N : 1 ) >
        MinusRow( unsigned int a_uiRow ) const;
    void Shift( int a_iRight, int a_iDown = 0 );

};

}   // namespace Math

// Vector scalar multiplication and division in the other direction
template< typename U, typename T, unsigned int N, bool t_bIsRow >
Math::Vector< T, N, t_bIsRow >
    operator*( const U& ac_rScalar,
               const Math::Vector< T, N, t_bIsRow > ac_roVector );
template< typename U, typename T, unsigned int N, bool t_bIsRow >
typename Math::Vector< T, N, t_bIsRow >::InverseType
    operator/( const U& ac_rScalar,
               const Math::Vector< T, N, t_bIsRow > ac_roVector );

#include "Implementations/Vector.inl"

#endif  // VECTOR__H
