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
// Most functionality is defined in this intermediate base class, but
//  multiplication with matrices is handled by specializing the Vector class
// descended from this one.
template< typename T, unsigned int N, bool t_bIsRow = true >
class Vector
    : public virtual VectorBase< T, N, t_bIsRow >,
      public virtual Matrix< T, ( t_bIsRow ? 1 : N ), ( t_bIsRow ? N : 1 ) >
{
    // Only the actual Vector class can call this class's constructors
    friend class Vector< T, N, t_bIsRow >;

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

    // virtual destructor needed due to virtual methods
    virtual ~Vector();

    // Copy assign, move assign, and assign from a different type of vector
    // These are specified to remove ambiguity between MatrixBase::operator= and
    // VectorBase::operator=, since both could work - MatrixBase::operator= is
    // available through inheritance from Matrix, VectorBase::operator= through
    // inheritance from VectorBase.
    Vector& operator=( const Vector& ac_roVector );
    Vector& operator=( Vector&& a_rroVector );
    template< unsigned int Q, bool t_bOtherIsRow >
    Vector& operator=( const Vector< T, Q, t_bOtherIsRow >& ac_roVector );

    // Element access - hides matrix class row-returning implementation
    T& operator[]( unsigned int a_uiIndex );
    const T& operator[]( unsigned int a_uiIndex ) const;

    // Get this vector in row/column form
    virtual ColumnVectorType Column() const;
    virtual RowVectorType Row() const;

    // Inverse - if not invertable, return zero vector
    virtual InverseType Inverse() const override;
    virtual InverseType Inverse( bool& a_rbInvertable ) const override;

    // Get a smaller vector by removing an element
    virtual Vector< T, ( N > 0 ? N-1 : 0 ), t_bIsRow >
        MinusElement( unsigned int a_uiIndex ) const override;

    // Transpose
    virtual TransposeType Transpose() const override;

    // Dot and cross products
    T Dot( const Vector& ac_roVector ) const;
    T Dot( const TransposeType& ac_roVector ) const;
    virtual Vector Cross( const Vector& ac_roVector
                            = ( N > 2 ? Unit(1) : Zero() ) ) const;
    virtual Vector Cross( const TransposeType& ac_roVector
                            = ( N > 2 ? TransposeType::Unit(1)
                                      : TransposeType::Zero() ) ) const;

    // Normalization
    typename MatrixInverse< T >::Type Magnitude() const;
    T MagnitudeSquared() const; // for efficiency in complex calculations
    void Normalize();
    virtual NormalType Normal() const;

    // Inherit matrix addition and subtraction
    using MatrixType::operator+=;
    using MatrixType::operator+;
    using MatrixType::operator-=;
    using MatrixType::operator-;

    // Vector addition and subtraction
    // Non-virtual overrides for arithmatic with another vector - vector
    // implementation doesn't care whether the other vector is a row vector or a
    // column vector, as arithmatic with a matrix does.  If both objects are
    // being explicitly treated as matrices, then a user should expect matrix-
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

    // Constructors that forward to base class constructors
    // Private so they can only be called by the friend child class
    Vector();
    Vector( const Vector& ac_roVector );
    Vector( const BaseType& ac_roVector );
    Vector( const RootType& ac_roMatrix );
    Vector( Vector&& a_rroVector );
    Vector( BaseType&& a_rroVector );
    Vector( RootType&& a_rroMatrix );
    template< unsigned int Q, bool t_bOtherIsRow >
    Vector( const Vector< T, Q, t_bOtherIsRow >& ac_roVector,
            const T& ac_rFill = DefaultFill() );
    template< unsigned int Q, bool t_bOtherIsRow >
    Vector( const VectorBase< T, Q, t_bOtherIsRow >& ac_roVector,
            const T& ac_rFill = DefaultFill() );
    template< typename U >
    Vector( const MatrixBase< U, ROWS, COLUMNS >& ac_roMatrix );
    template< unsigned int P, unsigned int Q >
    Vector( const MatrixBase< T, P, Q >& ac_roMatrix,
            const T& ac_rFill = DefaultFill() );
    Vector( const T& ac_rFill );
    Vector( const T (&ac_raData)[ N ] );
    Vector( const T* const ac_cpData,
            const unsigned int ac_uiSize,
            const T& ac_rFill = DefaultFill() );

    // Hide parent class functions that you shouldn't be using unless you are
    // explicitly treating this object as a matrix, either via casting or via
    // a pointer or reference of the parent type
    RootType& operator=( const T (&ac_raaData)[ ROWS ][ COLUMNS ] );
    typedef typename RootType::ColumnVectorType BaseColumnVectorType;
    RootType& operator=( const BaseColumnVectorType (&ac_raColumns)[ COLUMNS ] );
    RootType& operator=( const BaseColumnVectorType* const (&ac_racpoColumns)[ COLUMNS ] );
    typedef typename RootType::RowVectorType BaseRowVectorType;
    RootType& operator=( const BaseRowVectorType (&ac_raRows)[ ROWS ] );
    RootType& operator=( const BaseRowVectorType* const (&ac_racpoRows)[ ROWS ] );
    T Determinant();
    T Minor( unsigned int a_uiRow, unsigned int a_uiColumn );

    // Non-virtual override - if explicitly treated as a matrix, then matrix
    // implementation should be available, otherwise no implementation should be
    // available
    BaseColumnVectorType Column( unsigned int ac_uiIndex ) const;
    BaseRowVectorType Row( unsigned int ac_uiIndex ) const;
    Matrix< T, ( !t_bIsRow && N > 0 ? N-1 : 0 ), ( t_bIsRow && N > 0 ? N-1 : 0 ) >
        MinusRowAndColumn( unsigned int a_uiRow, unsigned int a_uiColumn ) const;
    Matrix< T, ( !t_bIsRow ? N : 1 ), ( t_bIsRow && N > 0 ? N-1 : 0 ) >
        MinusColumn( unsigned int a_uiColumn ) const;
    Matrix< T, ( !t_bIsRow && N > 0 ? N-1 : 0 ), ( t_bIsRow ? N : 1 ) >
        MinusRow( unsigned int a_uiRow ) const;

};

}   // namespace Math

#include "Implementations/Vector.inl"

#endif  // VECTOR__H
