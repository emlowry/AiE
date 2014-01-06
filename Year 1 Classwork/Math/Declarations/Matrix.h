/******************************************************************************
 * File:               Matrix.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 18, 2013
 * Description:        Base class for matrices of numeric type.
 * Last Modified:      December 10, 2013
 * Last Modification:  Debugging.
 ******************************************************************************/

#ifndef MATRIX__H
#define MATRIX__H

#include "MatrixBase.h"

namespace Math
{

// Used to determine type of matrix inversion operations
template< typename T >
struct MatrixInverse
{
    typedef double Type;
};
template<>
struct MatrixInverse< float >
{
    typedef float Type;
};
template<>
struct MatrixInverse< long double >
{
    typedef long double Type;
};

// Forward declare vector type
template< typename T, unsigned int N, bool t_bIsRow/* = true*/ >
class Vector;

// Represents a matrix of values of a set type with set dimensions.
template< typename T, unsigned int M, unsigned int N = M >
class Matrix : public virtual MatrixBase< T, M, N >
{
public:

    // simplify typing
    typedef MatrixBase< T, M, N > BaseType;
    typedef Vector< T, M, false > ColumnVectorType;
    typedef Vector< T, N, true > RowVectorType;
    typedef Matrix< T, ( M < N ? M : N ) > IdentityType;
    typedef Matrix< typename MatrixInverse< T >::Type, N, M > InverseType;
    typedef Matrix< T, N, M > TransposeType;

    // inherit assignment operators
    using BaseType::operator=;

    // destructor
    virtual ~Matrix();
    
    // Constructors that forward to base class constructors
    Matrix();
    Matrix( const Matrix& ac_roMatrix );
    Matrix( const BaseType& ac_roMatrix );
    Matrix( Matrix&& a_rroMatrix );
    Matrix( BaseType&& a_rroMatrix );
    template< typename U, unsigned int P, unsigned int Q >
    Matrix( const MatrixBase< U, P, Q >& ac_roMatrix,
            const T& ac_rFill = DefaultFill< T >() );
    template< unsigned int P, unsigned int Q >
    Matrix( MatrixBase< T, P, Q >&& a_rroMatrix,
            const T& ac_rFill = DefaultFill< T >() );
    Matrix( const T& ac_rFill );
    Matrix( const T (&ac_raData)[ M*N ] );
    Matrix( const T* const ac_cpData,
            const unsigned int ac_uiSize,
            const T& ac_rFill = DefaultFill< T >() );
    Matrix( const T (&ac_raaData)[ M ][ N ] );
    Matrix( const T* const* const ac_cpcpData,
            const unsigned int ac_uiRows,
            const unsigned int ac_uiColumns,
            const T& ac_rFill = DefaultFill< T >() );
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
    bool IsInvertable() const;
    bool Invert();  // If !TrueInvertable, !change; also, beware int truncation
    bool Inverse( InverseType& a_roMatrix ) const;  // !invertable = !change
    InverseType Inverse() const;    // if !invertable, return Zero
    InverseType Inverse( bool& a_rbInvertable ) const;  // as above

    // Return true if this matrix is an orthogonal matrix
    bool IsOrthogonal() const;

    // Non-virtual overrides to return the correct type, since return type is
    // concrete and not a reference or pointer
    ColumnVectorType Column( unsigned int ac_uiIndex ) const;
    RowVectorType Row( unsigned int ac_uiIndex ) const;
    Matrix< T, ( M > 1 ? M-1 : 1 ), ( N > 1 ? N-1 : 1 ) >
        MinusRowAndColumn( unsigned int a_uiRow,
                           unsigned int a_uiColumn ) const;
    Matrix< T, M, ( N > 1 ? N-1 : 1 ) >
        MinusColumn( unsigned int a_uiColumn ) const;
    Matrix< T, ( M > 1 ? M-1 : 1 ), N >
        MinusRow( unsigned int a_uiRow ) const;
    TransposeType Transpose() const;

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
    Matrix< typename MatrixInverse< T >::Type, M, P >
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
    // Operations are only defined for the matrix data type.
    // If you have a decimal parameter and you want a decimal result when your
    // matrix is an integral type, you should explicitly convert your matrix to
    // a decimal matrix.
    //
    template< typename U >
    Matrix& operator*=( const U& ac_rScalar );
    template< typename U >
    Matrix operator*( const U& ac_rScalar ) const;
    template< typename U >
    Matrix& operator/=( const U& ac_rScalar );
    template< typename U >
    Matrix operator/( const U& ac_rScalar ) const;
    template< typename U >
    Matrix& operator%=( const U& ac_rScalar );
    template< typename U >
    Matrix operator%( const U& ac_rScalar ) const;

    // constant references to Zero and Identity matrices
    static const Matrix& Zero();
    static const IdentityType& Identity();

protected:

    // if not invertable by given method, change nothing & return false
    bool LeftInverse( InverseType& a_roMatrix ) const;
    bool RightInverse( InverseType& a_roMatrix ) const;
    bool TrueInverse( InverseType& a_roMatrix ) const;

};

}   // namespace Math

// Matrix scalar multiplication and division in the other direction
template< typename U, typename T, unsigned int M, unsigned int N >
Math::Matrix< T, M, N > operator*( const U& ac_rScalar,
                                   const Math::Matrix< T, M, N >& ac_roMatrix );
template< typename U, typename T, unsigned int M, unsigned int N >
typename Math::Matrix< T, M, N >::InverseType
    operator/( const U& ac_rScalar,
               const Math::Matrix< T, M, N >& ac_roMatrix );

// Always include template function implementations with this header
#include "Implementations/Matrix.inl"

#endif  // MATRIX__H
