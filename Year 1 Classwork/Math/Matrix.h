/******************************************************************************
 * File:               Matrix.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 18, 2013
 * Description:        Base class for matrices of numeric type.
 *                      The library compiles Matrix classes with dimensions of
 *                      any combination of 1, 2, 3, or 4 for all of the numeric
 *                      primitive types.  If a user needs to instantiate a
 *                      Matrix class with dimensions beyond these, then they
 *                      need to include T_Matrix.h instead.  For a type that
 *                      doesn't have the arithmatic operations defined, include
 *                      T_MatrixBase.h to use the base class.
 * Last Modified:      November 20, 2013
 * Last Modification:  Moving certain functions to MatrixBase.
 ******************************************************************************/

#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "MatrixBase.h"
// #include <type_traits>   // for common_type

namespace Math
{

// Used to determine type of matrix arithmetic operations
template< typename T, typename U = T >
struct CommonType
{
    // typedef std::common_type< T, U >:: type Type
    typedef decltype( T() + U() ) Type;
};
template< typename T >
struct CommonType< T >
{
    typedef T Type;
};

// Used to determine type of matrix inversion operations
template< typename T >
struct MatrixInverse
{
    typedef T Type;
};

// Forward declare vector type, include vector definition *after* matrix
// definition, since matrix is parent of vector
template< typename T, unsigned int N, bool t_bIsRow = true >
class Vector;

// Represents a matrix of values of a set type with set dimensions.
template< typename T, unsigned int M, unsigned int N = M >
class Matrix : public virtual MatrixBase< T, M, N >
{
public:

    // simplify typing
    typedef MatrixBase< T, M, N > BaseType;
    typedef Vector< T, M, false > ColumnVectorType;
    typedef Vector< T, N > RowVectorType;
    typedef Matrix< T, ( M < N ? M : N ) > IdentityType;
    typedef Matrix< MatrixInverse< T >::Type, N, M > InverseType;
    typedef Matrix< T, N, M > TransposeType;

    // virtual destructor needed due to virtual methods
    virtual ~Matrix();
    
    // Constructors that forward to base class constructors
    Matrix();
    Matrix( const Matrix& ac_roMatrix );
    Matrix( const MatrixBase& ac_roMatrix );
    Matrix( Matrix&& a_rroMatrix );
    Matrix( MatrixBase&& a_rroMatrix );
    template< typename U, unsigned int P, unsigned int Q >
    Matrix( const MatrixBase< U, P, Q >& ac_roMatrix,
            const T& ac_rFill = DEFAULT_FILL );
    template< typename U >
    Matrix( const U& ac_rFill );
    template< typename U, unsigned int t_uiDataSize >
    Matrix( const U (&ac_raData)[ t_uiDataSize ],
            const T& ac_rFill = DEFAULT_FILL );
    template< typename U >
    Matrix( const U* const ac_cpData,
            const unsigned int ac_uiSize,
            const T& ac_rFill = DEFAULT_FILL );
    template< typename U, unsigned int t_uiRows, unsigned int t_uiColumns >
    Matrix( const U (&ac_raaData)[ t_uiRows ][ t_uiColumns ],
            const T& ac_rFill = DEFAULT_FILL );
    template< typename U >
    Matrix( const U* const* const ac_cpcpData,
            const unsigned int ac_uiRows,
            const unsigned int ac_uiColumns,
            const T& ac_rFill = DEFAULT_FILL );

    // Fill with one value along the identity diagonal and another elsewhere
    template< typename U, typename V >
    Matrix( const V& ac_rIdentityFill, const U& ac_rFill );

    // Scalar multiplication and division
    template< typename U >
    Matrix& operator*=( const U& a_rScalar );
    template< typename U >
    Matrix< CommonType< T, U >::Type, M, N >
        operator*( const U& a_rScalar ) const;
    template< typename U >
    Matrix& operator/=( const U& a_rScalar );
    template< typename U >
    Matrix< CommonType< T, U >::Type, M, N >
        operator/( const U& a_rScalar ) const;

    // Matrix addition and subtraction
    template< typename U >
    Matrix& operator+=( const Matrix< U, M, N >& ac_roMatrix );
    template< typename U >
    Matrix< CommonType< T, U >::Type, M, N >
        operator+( const Matrix< U, M, N >& ac_roMatrix ) const;
    template< typename U >
    Matrix& operator-=( const Matrix< U, M, N >& ac_roMatrix );
    template< typename U >
    Matrix< CommonType< T, U >::Type, M, N >
        operator-( const Matrix< U, M, N >& ac_roMatrix ) const;

    // Matrix multiplication
    template< typename U, unsigned int P >
    Matrix< CommonType< T, U >::Type, M, P >
        operator*( const Matrix< U, N, P >& ac_roMatrix ) const;
    // Matrix "division" = multiplication by inverse
    // Returns error if parameter is not invertable
    // Order is (*this) * ( ac_roMatrix.Inverse() ) even if P > N
    // (P > N means the matrix can only be left-invertable, where
    //  ac_roMatrix.Inverse() * ac_roMatrix = IDENTITY but
    //  ac_roMatrix * ac_roMatrix.Inverse() != IDENTITY_MATRIX< T, P >
    template< typename U, unsigned int P >
    Matrix< CommonType< T, MatrixInverse< U >::Type >::Type, M, P >
        operator/( const Matrix< U, P, N >& ac_roMatrix ) const;

    // TODO bitwise operations

    // multiplication by a column vector
    template< typename U >
    Vector< CommonType< T, U >, M, false >
        operator*( const Vector< U, N, false >& ac_roVector ) const;
    // "division" by a row vector = multiplication by its inverse, if it has one
    template< typename U >
    Vector< CommonType< T, MatrixInverse< U >::Type >, M, false >
        operator/( const Vector< U, N >& ac_roVector ) const;

    // Determinant - return 0 if non-square matrix
    T Determinant();

    // Inverse
    bool IsInvertable() const;
    bool Inverse( InverseType& a_roMatrix ) const;  // !invertable = !change
    InverseType Inverse() const;    // if not invertable, return zero matrix
    InverseType Inverse( bool& a_rbInvertable ) const;  // as above

    // Get row/column vectors - redefine in child classes to return correct type
    virtual ColumnVectorType Column( unsigned int ac_uiIndex ) const;
    virtual RowVectorType Row( unsigned int ac_uiIndex ) const;
    
    // Transpose - redefine in child classes to return correct type
    virtual TransposeType Transpose() const;

    static const Matrix& ZERO;  // reference to ZERO_MATRIX< T, M, N >
    static const IdentityType& IDENTITY;    // IDENTITY_MATRIX< T, min( M, N ) >
    static const unsigned int ROWS = M;
    static const unsigned int COLUMNS = N;

protected:

    // if not invertable by given method, change nothing & return false
    bool LeftInverse( Matrix< MatrixInverse< T >::Type, N, M >& a_roMatrix );
    bool RightInverse( Matrix< MatrixInverse< T >::Type, N, M >& a_roMatrix );
    bool TrueInverse( Matrix< MatrixInverse< T >::Type, N, M >& a_roMatrix );

};

// Zero matrix
template< typename T, unsigned int M, unsigned int N >
const Matrix< T, M, N > ZERO_MATRIX;

// Identity matrix
template< typename T, unsigned int N >
const Matrix< T, N > IDENTITY_MATRIX;

}   // namespace Math

// The Matrix class *must* be defined before the Vector class, since Vector is
// a child class of Matrix.
#include "Vector.h"

#endif  // _MATRIX_H_
