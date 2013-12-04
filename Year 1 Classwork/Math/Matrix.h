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

// Used to determine type of matrix inversion operations
template< typename T >
struct MatrixInverse
{
    typedef double Type;
};
template<>
struct MatrixInverse< long double >
{
    typedef long double Type;
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
    typedef Matrix< typename MatrixInverse< T >::Type, N, M > InverseType;
    typedef Matrix< T, N, M > TransposeType;

    // inherit assignment operators
    using BaseType::operator=;

    // virtual destructor needed due to virtual methods
    virtual ~Matrix();
    
    // Constructors that forward to base class constructors
    Matrix();
    Matrix( const Matrix& ac_roMatrix );
    Matrix& operator=( const Matrix& ac_roMatrix );
    Matrix( const BaseType& ac_roMatrix );
    Matrix( Matrix&& a_rroMatrix );
    Matrix& operator=( Matrix&& a_rroMatrix );
    Matrix( BaseType&& a_rroMatrix );
    template< typename U >
    Matrix( const MatrixBase< U, M, N >& ac_roMatrix )
    template< unsigned int P, unsigned int Q >
    Matrix( const MatrixBase< T, P, Q >& ac_roMatrix,
            const T& ac_rFill = DEFAULT_FILL );
    Matrix( const T& ac_rFill );
    Matrix( const T (&ac_raData)[ M*N ] );
    Matrix( const T* const ac_cpData,
            const unsigned int ac_uiSize,
            const T& ac_rFill = DEFAULT_FILL );
    Matrix( const T (&ac_raaData)[ M ][ N ] );
    Matrix( const T* const* const ac_cpcpData,
            const unsigned int ac_uiRows,
            const unsigned int ac_uiColumns,
            const T& ac_rFill = DEFAULT_FILL );
    Matrix( const ColumnVectorType (&ac_raoColumns)[ N ] );
    Matrix( const ColumnVectorType* const (&ac_rpoaColumns)[ N ] );
    Matrix( const RowVectorType (&ac_raoRows)[ M ] );
    Matrix( const RowVectorType* const (&ac_rpoaRows)[ M ] );

    // Fill with one value along the identity diagonal and another elsewhere
    Matrix( const T& ac_rIdentityFill, const T& ac_rFill );

    // Determinant - return 0 if non-square matrix
    T Determinant() const;
    // Determinant of submatrix formed by removing given row and column
    T Minor( unsigned int a_uiRow, unsigned int a_uiColumn ) const;

    // Inverse
    // The second two functions are invertable so that derived classes can
    // redefine them to return the correct type
    bool IsInvertable() const;
    bool Invert();  // If !TrueInvertable, !change; also, beware int truncation
    bool Inverse( InverseType& a_roMatrix ) const;  // !invertable = !change
    virtual InverseType Inverse() const;    // if !invertable, return ZERO
    virtual InverseType Inverse( bool& a_rbInvertable ) const;  // as above

    // Get row/column vectors - redefine in child classes to return correct type
    virtual ColumnVectorType Column( unsigned int ac_uiIndex ) const override;
    virtual RowVectorType Row( unsigned int ac_uiIndex ) const override;
    
    // Get smaller matrices by removing a row and/or column - redefine in child
    // classes to return the correct type.
    virtual Matrix< T, M-1, N-1 >
        MinusRowAndColumn( unsigned int a_uiRow,
                           unsigned int a_uiColumn ) const override;
    virtual Matrix< T, M, N-1 >
        MinusColumn( unsigned int a_uiColumn ) const override;
    virtual Matrix< T, M-1, N > MinusRow( unsigned int a_uiRow ) const override;
    
    // Transpose - redefine in child classes to return correct type
    virtual TransposeType Transpose() const override;

    //
    // Matrix math
    //
    // Operations are only defined for the matrix data type.
    // If you have a decimal parameter and you want a decimal result when your
    // matrix is an integral type, you should explicitly convert.
    //

    // Matrix multiplication
    template< unsigned int P >
    virtual Matrix< T, M, P >
        operator*( const Matrix< T, N, P >& ac_roMatrix ) const;
    // Matrix "division" = multiplication by inverse
    // Returns error if parameter is not invertable
    // Order is (*this) * ( ac_roMatrix.Inverse() ) even if P > N
    // (P > N means the matrix can only be left-invertable, where
    //  ac_roMatrix.Inverse() * ac_roMatrix = IDENTITY but
    //  ac_roMatrix * ac_roMatrix.Inverse() != IDENTITY_MATRIX< T, P >
    template< unsigned int P >
    virtual Matrix< typename MatrixInverse< T >::Type, M, P >
        operator/( const Matrix< T, P, N >& ac_roMatrix ) const;

    // multiplication by a column vector produces another column vector
    virtual Vector< T, M, false >
        operator*( const Matrix< T, N, 1 >& ac_roVector ) const;
    // "division" by a row vector = multiplication by its inverse, if it has one
    virtual Vector< typename MatrixInverse< T >::Type, M, false >
        operator/( const Matrix< T, 1, N >& ac_roVector ) const;

    // Matrix addition and subtraction
    Matrix& operator+=( const Matrix& ac_roMatrix );
    Matrix operator+( const Matrix& ac_roMatrix ) const;
    Matrix& operator-=( const Matrix& ac_roMatrix );
    Matrix operator-( const Matrix& ac_roMatrix ) const;

    //
    // Scalar math - multiplication, division, and modulo
    //
    // Operations are only defined for the matrix data type.
    // If you have a decimal parameter and you want a decimal result when your
    // matrix is an integral type, you should explicitly convert your matrix to
    // a decimal matrix.
    //
    // Non-assign operators are virtual so that child classes can override to
    // return the correct type.
    //
    Matrix& operator*=( const T& ac_rScalar );
    virtual Matrix operator*( const T& ac_rScalar ) const;
    Matrix& operator/=( const T& ac_rScalar );
    virtual Matrix operator/( const T& ac_rScalar ) const;
    Matrix& operator%=( const T& ac_rScalar );
    virtual Matrix operator%( const T& ac_rScalar ) const;

    static const Matrix& ZERO;  // reference to ZERO_MATRIX< T, M, N >
    static const IdentityType& IDENTITY;    // IDENTITY_MATRIX< T, min( M, N ) >

protected:

    // if not invertable by given method, change nothing & return false
    bool LeftInverse( InverseType& a_roMatrix );
    bool RightInverse( InverseType& a_roMatrix );
    bool TrueInverse( InverseType& a_roMatrix );

    // Used by multiplication and division operators
    template< unsigned int P >
    virtual Matrix< T, M, P >
        Product( const Matrix< T, N, P >& ac_roMatrix ) const;

};

// Zero matrix
template< typename T, unsigned int M, unsigned int N = M >
const Matrix< T, M, N > ZERO_MATRIX;

// Identity matrix
template< typename T, unsigned int N >
const Matrix< T, N > IDENTITY_MATRIX;

}   // namespace Math



// The Matrix class *must* be defined before the Vector class, since Vector is
// a child class of Matrix.
#include "Vector.h"

#endif  // _MATRIX_H_
