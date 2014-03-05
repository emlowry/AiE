/******************************************************************************
 * File:               Matrix.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 18, 2013
 * Description:        Base class for matrices of numeric type.
 * Last Modified:      February 24, 2014
 * Last Modification:  MostDerivedAddress moved to Utility namespace.
 ******************************************************************************/

#ifndef MATRIX__H
#define MATRIX__H

#include "Functions.h"
#include "MostDerivedAddress.h"
#include <iostream>
#include <type_traits>  // for enable_if and is_scalar

namespace Math
{

// Forward declare vector type
template< typename T, unsigned int N, bool t_bIsRow/* = true*/ >
class Vector;

// Represents a matrix of values of a set type with set dimensions.
template< typename T, unsigned int M, unsigned int N = M >
class Matrix : public Utility::MostDerivedAddress
{
public:

    // simplify typing
    typedef Vector< T, M, false > ColumnVectorType;
    typedef Vector< T, N, true > RowVectorType;
    typedef Matrix< T, ( M < N ? M : N ) > IdentityType;
    typedef typename InverseOf< T >::Type InverseT;
    typedef Matrix< InverseT, N, M > InverseType;
    typedef Matrix< T, N, M > TransposeType;

    // destructor
    virtual ~Matrix();
    
    // Construct/assign from a differently-sized/typed matrix
    template< typename U, unsigned int P, unsigned int Q >
    Matrix( const Matrix< U, P, Q >& ac_roMatrix,
            const T& ac_rFill = DefaultValue< T >() );
    template< typename U, unsigned int P, unsigned int Q >
    Matrix& operator=( const Matrix< U, P, Q >& ac_roMatrix );
    Matrix& operator=( const Matrix& ac_roMatrix )
    { return operator=< T, M, N >( ac_roMatrix ); }

    // Construct/assign all values equal to parameter
    Matrix( const T& ac_rFill = DefaultValue< T >() );
    Matrix& operator=( const T& ac_rFill );

    // Fill with one value along the identity diagonal and another elsewhere
    Matrix( const T& ac_rIdentityFill, const T& ac_rFill );

    // Construct/assign with parameter data
    Matrix( const T (&ac_raData)[ M*N ] );
    Matrix& operator=( const T (&ac_raData)[ M*N ] );
    Matrix( const T (&ac_raaData)[ M ][ N ] );
    Matrix& operator=( const T (&ac_raaData)[ M ][ N ] );

    // Construct/assign from a set of rows or columns
    Matrix( const ColumnVectorType (&ac_raoColumns)[ N ] );
    Matrix& operator=( const ColumnVectorType (&ac_raoColumns)[ N ] );
    Matrix( const ColumnVectorType* const (&ac_racpoColumns)[ N ] );
    Matrix& operator=( const ColumnVectorType* const (&ac_racpoColumns)[ N ] );
    Matrix( const RowVectorType (&ac_raoRows)[ M ] );
    Matrix& operator=( const RowVectorType (&ac_raoRows)[ M ] );
    Matrix( const RowVectorType* const (&ac_racpoRows)[ M ] );
    Matrix& operator=( const RowVectorType* const (&ac_racpoRows)[ M ] );

    // Assign to arrays
    template< typename U, unsigned int P >
    inline typename ArrayReference< U, P >::type
        AssignTo( U (&a_raData)[ P ], bool a_bTranspose = false ) const;
    template< typename U, unsigned int P, unsigned int Q >
    inline typename Array2DReference< U, P, Q >::type
        AssignTo( U (&a_raaData)[ P ][ Q ], bool a_bTranspose = false ) const;
    template< typename U >
    U* AssignTo( U* const a_cpData,
                 unsigned int a_uiSize = M*N,
                 bool a_bTranspose = false ) const;
    template< typename U >
    U** AssignTo( U* const* const a_cpcpData,
                  unsigned int a_uiRows = M,
                  unsigned int a_uiColumns = N,
                  bool a_bTranspose = false ) const;

    // Equality and inequality checks
    bool operator==( const Matrix& ac_roMatrix ) const;
    bool operator!=( const Matrix& ac_roMatrix ) const;
    
    // Array access
    T (&operator[]( unsigned int a_uiRow ))[ N ];
    const T (&operator[]( unsigned int a_uiRow ) const)[ N ];
    T& At( unsigned int a_uiRow, unsigned int a_uiColumn );
    const T& At( unsigned int a_uiRow, unsigned int a_uiColumn ) const;

    // Get row/column vectors - redefine non-virtually in child classes to
    // return correct type, since return type is concrete and not a pointer or
    // reference.
    ColumnVectorType Column( unsigned int ac_uiIndex ) const;
    RowVectorType Row( unsigned int ac_uiIndex ) const;
    
    // Get smaller matrices by removing a row and/or column - redefine
    // non-virtually in child classes to return the correct type.
    Matrix< T, ( M > 1 ? M-1 : 1 ), ( N > 1 ? N-1 : 1 ) >
        MinusRowAndColumn( unsigned int a_uiRow,
                           unsigned int a_uiColumn ) const;
    Matrix< T, M, ( N > 1 ? N-1 : 1 ) >
        MinusColumn( unsigned int a_uiColumn ) const;
    Matrix< T, ( M > 1 ? M-1 : 1 ), N >
        MinusRow( unsigned int a_uiRow ) const;

    // Shift elements right/down the given number of spaces, wrapping around the
    // ends of columns and rows
    // Example:
    // Matrix m = { { 0, 1, 2 }, { 10, 11, 12 }, { 20, 21, 22 } };
    // m.Shift( 1, 1 );
    // // m == { { 22, 20, 21 }, { 2, 0, 1 }, { 12, 10, 11 } }
    // m.Shift( -1, -1 );
    // // m == { { 0, 1, 2 }, { 10, 11, 12 }, { 20, 21, 22 } }
    Matrix& Shift( int a_iRight, int a_iDown = 0 );

    // Round all elements to nearest whole number
    Matrix& Round();

    // Transpose - redefine non-virtually in child classes to return the correct
    // type
    TransposeType Transpose() const;
    TransposeType ConjugateTranspose() const;

    // Determinant - return 0 if non-square matrix
    T Determinant() const;
    // Determinant of submatrix formed by removing given row and column
    T Minor( unsigned int a_uiRow, unsigned int a_uiColumn ) const;

    // Inverse
    bool IsInvertable() const;
    bool Invert();  // If !TrueInvertable, !change; also, beware int truncation
    bool Inverse( InverseType& a_roMatrix ) const;  // !invertable = !change
    InverseType Inverse() const;    // if !invertable, return Zero
    InverseType Inverse( bool& a_rbInvertable ) const;  // as above

    // Return true if this matrix is an orthogonal matrix
    bool IsOrthogonal() const;

    // Return true if this matrix is an idempotent matrix
    bool IsIdempotent() const;

    // Return true if this matrix if a Hermitian matrix
    bool IsHermitian() const;

    //
    // Matrix math
    //
    // Operations are only defined for the matrix data type.
    // If you have a floating-point parameter and you want a floating-point
    // result when your matrix is an integral type, you should explicitly
    // convert to a floating-point matrix.
    //

    // Matrix multiplication
    template< unsigned int P >
    Matrix< T, M, P >
        operator*( const Matrix< T, N, P >& ac_roMatrix ) const;
    // Matrix "division" = multiplication by inverse
    // Returns error if parameter is not invertable
    // Order is (*this) * ( ac_roMatrix.Inverse() ) even if P > N
    // (P > N means the matrix can only be left-invertable, where
    //  ac_roMatrix.Inverse() * ac_roMatrix = Identity() but
    //  ac_roMatrix * ac_roMatrix.Inverse() != Matrix< T, P >::Identity()
    template< unsigned int P >
    Matrix< InverseT, M, P >
        operator/( const Matrix< T, P, N >& ac_roMatrix ) const;

    // transform assign
    Matrix& operator*=( const Matrix< T, N >& ac_roMatrix );
    Matrix& operator/=( const Matrix< T, N >& ac_roMatrix );

    // Matrix addition and subtraction
    Matrix& operator+=( const Matrix& ac_roMatrix );
    Matrix operator+( const Matrix& ac_roMatrix ) const;
    Matrix& operator-=( const Matrix& ac_roMatrix );
    Matrix operator-( const Matrix& ac_roMatrix ) const;

    //
    // Scalar math - multiplication, division, and modulo
    //
    // Result will be matrix of the same type - multiplying an integer matrix
    // by a floating-point scalar will result in another integer matrix, not a
    // floating-point matrix
    //
    Matrix operator-() const;
    template< typename U >
    typename std::enable_if< std::is_scalar< U >::value, Matrix& >::type
        operator*=( const U& ac_rScalar );
    template< typename U >
    typename std::enable_if< std::is_scalar< U >::value, Matrix >::type
        operator*( const U& ac_rScalar ) const;
    template< typename U >
    typename std::enable_if< std::is_scalar< U >::value, Matrix& >::type
        operator/=( const U& ac_rScalar );
    template< typename U >
    typename std::enable_if< std::is_scalar< U >::value, Matrix >::type
        operator/( const U& ac_rScalar ) const;
    template< typename U >
    typename std::enable_if< std::is_scalar< U >::value, Matrix& >::type
        operator%=( const U& ac_rScalar );
    template< typename U >
    typename std::enable_if< std::is_scalar< U >::value, Matrix >::type
        operator%( const U& ac_rScalar ) const;

    // constant references to Zero and Identity matrices
    static const Matrix& Zero();
    static const IdentityType& Identity();

    static const unsigned int ROWS = M;
    static const unsigned int COLUMNS = N;

protected:

    // if not invertable by given method, change nothing & return false
    bool LeftInverse( InverseType& a_roMatrix ) const;
    bool RightInverse( InverseType& a_roMatrix ) const;
    bool TrueInverse( InverseType& a_roMatrix ) const;

    // elements of the matrix
    T m_aaData[ M ][ N ];

};

}   // namespace Math

// Matrix scalar multiplication and division in the other direction
template< typename U, typename T, unsigned int M, unsigned int N >
typename std::enable_if< std::is_scalar< U >::value,
                         Math::Matrix< T, M, N > >::type
    operator*( const U& ac_rScalar,
               const Math::Matrix< T, M, N >& ac_roMatrix );
template< typename U, typename T, unsigned int M, unsigned int N >
typename std::enable_if< std::is_scalar< U >::value,
                         typename Math::Matrix< T, M, N >::InverseType >::type
    operator/( const U& ac_rScalar,
               const Math::Matrix< T, M, N >& ac_roMatrix );

// stream operator
template< typename T, unsigned int M, unsigned int N >
std::ostream& operator<<( std::ostream& a_roOut,
                          const Math::Matrix< T, M, N >& ac_roMatrix );

// Always include template function implementations with this header
#include "../Implementations/Matrix.inl"

#endif  // MATRIX__H
