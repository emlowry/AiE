/******************************************************************************
 * File:               NumericVectorBase.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 25, 2013
 * Description:        Intermediate base class for vectors of numeric type.
 *                      The actual Vector class has to specialize the
 *                      multiplication and division operators based on its
 *                      dimensions.  This class holds all the functions that
 *                      remain the same for all dimensions.
 * Last Modified:      November 25, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef _NUMERIC_VECTOR_BASE_H_
#define _NUMERIC_VECTOR_BASE_H_

#include "Matrix.h"
#include "VectorBase.h"
// #include <type_traits>   // for common_type

namespace Math
{
    
// Forward declare the actual Vector class
template< typename T, unsigned int N, bool t_bIsRow = true >
class Vector;

// A vector handles some things a bit differently than a matrix of the same size
// Most functionality is defined in this intermediate base class, but
//  multiplication with matrices is handled by specializing the Vector class
// descended from this one.
template< typename T, unsigned int N, bool t_bIsRow = true >
class NumericVectorBase
    : public virtual VectorBase< T, N, t_bIsRow >,
      public virtual Matrix< T, ( t_bIsRow ? 1 : N ), ( t_b_IsRow ? N : 1 ) >
{
    // Only the actual Vector class can call this class's constructors
    friend class Vector< T, N, t_bIsRow >;

public:

    // simplify typing
    typedef VectorBase< T, N, t_bIsRow > BaseType;
    typedef Vector< T, M, false > ColumnVectorType;
    typedef Vector< T, N > RowVectorType;
    typedef Matrix< T, ( t_bIsRow ? 1 : N ), ( t_b_IsRow ? N : 1 ) > MatrixType;
    typedef Vector< T, 1 > IdentityType;
    typedef Vector< MatrixInverse< T >::Type, N, !t_bIsRow > InverseType;
    typedef Vector< T, N, !t_bIsRow > TransposeType;
    typedef Vector< T, N, t_bIsRow > ChildType;

    // virtual destructor needed due to virtual methods
    virtual ~NumericVectorBase();

    // Assign from a different type of vector
    template< typename U, unsigned int Q, bool t_bOtherIsRow >
    Vector& operator=( const NumericVectorBase< U, Q, t_bOtherIsRow >& ac_roVector );

    // Element access - hides matrix class row-returning implementation
    T& operator[]( unsigned int a_uiIndex );
    const T& operator[]( unsigned int a_uiIndex ) const;

    // non-virtual override for addition and subtraction - vector implementation
    // doesn't care whether the other vector is a row vector or a column vector,
    // but matrix addition and subtraction does.
    template< typename U, t_bOtherIsRow >
    ChildType& operator+=( const Vector< U, N, t_bOtherIsRow >& ac_roVector );
    template< typename U, t_bOtherIsRow >
    Vector< CommonType< T, U >::Type, N, t_bIsRow >
        operator+( const Vector< U, N, t_bOtherIsRow >& ac_roVector ) const;
    template< typename U, t_bOtherIsRow >
    ChildType& operator-=( const Vector< U, N, t_bOtherIsRow >& ac_roVector );
    template< typename U, t_bOtherIsRow >
    Vector< CommonType< T, U >::Type, N, t_bIsRow >
        operator-( const Vector< U, N, t_bOtherIsRow >& ac_roVector ) const;

    // TODO bitwise operators taking other vectors

    // Get this vector in row/column form
    virtual ColumnVectorType Column() const;
    virtual RowVectorType Row() const;

    // Transpose
    virtual TransposeType Transpose() const override;

private:

    // Constructors that forward to base class constructors
    // Private so they can only be called by the friend child class
    NumericVectorBase();
    NumericVectorBase( const NumericVectorBase& ac_roVector );
    NumericVectorBase( const BaseType& ac_roVector );
    NumericVectorBase( const MatrixType& ac_roMatrix );
    NumericVectorBase( NumericVectorBase&& a_rroVector );
    NumericVectorBase( BaseType&& a_rroVector );
    NumericVectorBase( MatrixType&& a_rroMatrix );
    template< typename U, unsigned int Q, bool t_bOtherIsRow >
    NumericVectorBase( const Vector< U, Q, t_bOtherIsRow >& ac_roVector );
    template< typename U, unsigned int Q, bool t_bOtherIsRow >
    NumericVectorBase( const VectorBase< U, Q, t_bOtherIsRow >& ac_roVector );
    template< typename U, unsigned int P, unsigned int Q >
    NumericVectorBase( const MatrixBase< U, P, Q >& ac_roMatrix,
                       const T& ac_rFill = DEFAULT_FILL );
    template< typename U >
    NumericVectorBase( const U& ac_rFill );
    template< typename U, unsigned int t_uiSize >
    NumericVectorBase( const U (&ac_raData)[ t_uiSize ],
                       const T& ac_rFill = DEFAULT_FILL );
    template< typename U >
    NumericVectorBase( const U* const ac_cpData,
                       const unsigned int ac_uiSize,
                       const T& ac_rFill = DEFAULT_FILL );

    // Hide parent class functions that you shouldn't be using unless you are
    // explicitly treating this object as a matrix, either via casting or via
    // a pointer or reference of the parent type
    template< typename U, unsigned int t_uiRows, unsigned int t_uiColumns >
    MatrixType& operator=( const U (&ac_raaData)[ t_uiRows ][ t_uiColumns ] );
    T& operator[]( unsigned int a_uiRow, unsigned int a_uiColumn );
    const T& operator[]( unsigned int a_uiRow, unsigned int a_uiColumn ) const;

    // Non-virtual override - if explicitly treated as a matrix, then matrix
    // implementation should be available, otherwise no implementation should be
    // available
    ColumnVectorType Column( unsigned int ac_uiIndex ) const;
    RowVectorType Row( unsigned int ac_uiIndex ) const;

};

}   // namespace Math

// The NumericVectorBase type *must* be defined before the Vector type, but
// the Vector type definition must be defined before the NumericVectorBase
// implementations.
#include "Vector.h"

#endif  // _NUMERIC_VECTOR_BASE_H_
