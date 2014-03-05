/******************************************************************************
 * File:               Vector.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 25, 2013
 * Description:        Base class for vectors of numeric type.
 * Last Modified:      February 12, 2014
 * Last Modification:  Refactoring.
 ******************************************************************************/

#ifndef VECTOR__H
#define VECTOR__H

#include "Functions.h"
#include "Matrix.h"
#include <type_traits>  // for enable_if and is_scalar

namespace Math
{
    
// A vector handles some things a bit differently than a matrix of the same size
template< typename T, unsigned int N, bool t_bIsRow = true >
class Vector
    : public Matrix< T, ( t_bIsRow ? 1 : N ), ( t_bIsRow ? N : 1 ) >
{
public:

    // simplify typing
    typedef Matrix< T, ROWS, COLUMNS > BaseType;
    typedef Vector< T, N, false > ColumnVectorType;
    typedef Vector< T, N > RowVectorType;
    typedef Vector< T, 1 > IdentityType;
    typedef typename InverseOf< T >::Type InverseT;
    typedef Vector< InverseT, N, !t_bIsRow > InverseType;
    typedef Vector< T, N, !t_bIsRow > TransposeType;
    typedef Vector< InverseT, N, t_bIsRow > NormalType;

    // destructor
    virtual ~Vector();

    // Constructors that forward to base class constructors
    Vector();
    template< typename U, unsigned int P, unsigned int Q >
    Vector( const Matrix< U, P, Q >& ac_roMatrix,
            const T& ac_rFill = DefaultValue< T >() );
    Vector( const T& ac_rFill );
    Vector( const T (&ac_raData)[ N ] );

    // Assignment operators that pass to base class
    template< typename U, unsigned int P, unsigned int Q >
    Vector& operator=( const Matrix< U, P, Q >& ac_roMatrix );
    Vector& operator=( const T& ac_rFill );
    Vector& operator=( const T (&ac_raData)[ N ] );
    
    // Construct from another type of vector
    template< typename U, unsigned int Q, bool t_bOtherIsRow >
    Vector( const Vector< U, Q, t_bOtherIsRow >& ac_roVector,
            const T& ac_rFill = DefaultValue< T >() );
    template< typename U, unsigned int Q, bool t_bOtherIsRow >
    Vector& operator=( const Vector< U, Q, t_bOtherIsRow >& ac_roVector );
    Vector& operator=( const Vector& ac_roMatrix )
    { return operator=< T, N, t_bIsRow >( ac_roMatrix ); }

    // Assign to arrays
    template< typename U, unsigned int P >
    typename ArrayReference< U, P >::type
        AssignToRow( typename ArrayReference< U, P >::type a_raData ) const;
    template< typename U, unsigned int P >
    typename ArrayReference< U, P >::type
        AssignToColumn( typename ArrayReference< U, P >::type a_raData,
                        unsigned int a_uiColumns,
                        unsigned int a_uiAssignToColumn = 0 ) const;
    template< typename U, unsigned int P, unsigned int Q >
    typename Array2DReference< U, P, Q >::type
        AssignToColumn( typename Array2DReference< U, P, Q>::type a_raaData,
                        unsigned int a_uiAssignToColumn = 0 ) const;
    template< typename U >
    U* AssignToRow( U* const a_cpData, unsigned int a_uiSize = N ) const;
    template< typename U >
    U* AssignToColumn( U* const a_cpData,
                       unsigned int a_uiColumns,
                       unsigned int a_uiAssignToColumn = 0,
                       unsigned int a_uiRows = N ) const;
    template< typename U >
    U** AssignToColumn( U* const* const a_cpcpData,
                        unsigned int a_uiAssignToColumn = 0,
                        unsigned int a_uiRows = N ) const;
    
    // Element access - hides parent class row-returning implementation
    T& operator[]( unsigned int a_uiIndex );
    T& At( const unsigned int ac_uiIndex );
    const T& operator[]( unsigned int a_uiIndex ) const;
    const T& At( const unsigned int ac_uiIndex ) const;

    // Instead of getting a row or column of a matrix, return this vector in row
    // or column form.
    ColumnVectorType Column() const;
    RowVectorType Row() const;

    // Get a smaller vector by removing an element
    Vector< T, ( N > 1 ? N-1 : 1 ), t_bIsRow >
        MinusElement( unsigned int a_uiIndex ) const;

    // Shift elements by the given number of places
    Vector& Shift( int a_iPlaces );

    // Non-virtual overrides to return correct type, since return type is
    // concrete and not a pointer or reference.
    InverseType Inverse() const;
    InverseType Inverse( bool& a_rbInvertable ) const;
    TransposeType Transpose() const;
    TransposeType ConjugateTranspose() const;

    // Dot and cross products
    T Dot( const Vector& ac_roVector ) const;
    T Dot( const TransposeType& ac_roVector ) const;
    Vector Cross( const Vector& ac_roVector = Zero() ) const;
    Vector Cross( const TransposeType& ac_roVector ) const;

    // Normalization
    InverseT Magnitude() const;
    T MagnitudeSquared() const; // for efficiency in complex calculations
    Vector& Normalize();
    NormalType Normal() const;

    // Matrix multiplication and division overrides so the operators won't be
    // hidden by the scalar multiplication and division operator overrides
    template< unsigned int P >
    typename std::conditional< t_bIsRow, Vector< T, P >, Matrix< T, N, P > >::type
        operator*( const Matrix< T, ( t_bIsRow ? N : 1 ), P >& ac_roMatrix ) const;
    template< unsigned int P >
    typename std::conditional< t_bIsRow, Vector< InverseT, P >,
                               Matrix< InverseT, N, P > >::type
        operator/( const Matrix< T, P, ( t_bIsRow ? N : 1 ) >& ac_roMatrix ) const;
    Vector& operator*=( const Matrix< T, ( t_bIsRow ? N : 1 ) >& ac_roMatrix );
    Vector& operator/=( const Matrix< T, ( t_bIsRow ? N : 1 ) >& ac_roMatrix );

    // Scalar multiplication/division/modulo overrides to return correct type
    Vector operator-() const;
    template< typename U >
    typename std::enable_if< std::is_scalar< U >::value, Vector& >::type
        operator*=( const U& ac_rScalar );
    template< typename U >
    typename std::enable_if< std::is_scalar< U >::value, Vector >::type
        operator*( const U& ac_rScalar ) const;
    template< typename U >
    typename std::enable_if< std::is_scalar< U >::value, Vector& >::type
        operator/=( const U& ac_rScalar );
    template< typename U >
    typename std::enable_if< std::is_scalar< U >::value, Vector >::type
        operator/( const U& ac_rScalar ) const;
    template< typename U >
    typename std::enable_if< std::is_scalar< U >::value, Vector& >::type
        operator%=( const U& ac_rScalar );
    template< typename U >
    typename std::enable_if< std::is_scalar< U >::value, Vector >::type
        operator%( const U& ac_rScalar ) const;

    // Matrix addition/subtraction overrides to return correct type
    Vector& operator+=( const BaseType& ac_roMatrix );
    Vector operator+( const BaseType& ac_roMatrix ) const;
    Vector& operator-=( const BaseType& ac_roMatrix );
    Vector operator-( const BaseType& ac_roMatrix ) const;

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

    static const unsigned int IS_ROW_VECTOR = t_bIsRow;
    static const unsigned int SIZE = N;

private:

    // Hide parent class functions that you shouldn't be using unless you are
    // explicitly treating this object as a matrix, either via casting or via
    // a pointer or reference of the parent type
    T Determinant();
    T Minor( unsigned int a_uiRow, unsigned int a_uiColumn );
    typedef typename BaseType::ColumnVectorType BaseColumnVectorType;
    BaseColumnVectorType Column( unsigned int ac_uiIndex ) const;
    typedef typename BaseType::RowVectorType BaseRowVectorType;
    BaseRowVectorType Row( unsigned int ac_uiIndex ) const;
    Matrix< T, ( !t_bIsRow && N > 1 ? N-1 : 1 ), ( t_bIsRow && N > 1 ? N-1 : 1 ) >
        MinusRowAndColumn( unsigned int a_uiRow, unsigned int a_uiColumn ) const;
    Matrix< T, ( !t_bIsRow ? N : 1 ), ( t_bIsRow && N > 1 ? N-1 : 1 ) >
        MinusColumn( unsigned int a_uiColumn ) const;
    Matrix< T, ( !t_bIsRow && N > 1 ? N-1 : 1 ), ( t_bIsRow ? N : 1 ) >
        MinusRow( unsigned int a_uiRow ) const;
    BaseType& Shift( int a_iRight, int a_iDown );

};

}   // namespace Math

// Vector scalar multiplication and division in the other direction
template< typename U, typename T, unsigned int N, bool t_bIsRow >
typename std::enable_if< std::is_scalar< U >::value,
                         Math::Vector< T, N, t_bIsRow > >::type
    operator*( const U& ac_rScalar,
               const Math::Vector< T, N, t_bIsRow >& ac_roVector );
template< typename U, typename T, unsigned int N, bool t_bIsRow >
typename std::enable_if< std::is_scalar< U >::value,
                         typename Math::Vector< T, N, t_bIsRow >
                                      ::InverseType >::type
    operator/( const U& ac_rScalar,
               const Math::Vector< T, N, t_bIsRow >& ac_roVector );

// Always include template function implementations with this header
#include "../Implementations/Vector.inl"

#endif  // VECTOR__H
