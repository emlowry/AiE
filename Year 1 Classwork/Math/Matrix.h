/******************************************************************************
 * File:               Matrix.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 18, 2013
 * Description:        Main class for matrices and vectors.
 *                      The library compiles Matrix classes with dimensions of
 *                      any combination of 1, 2, 3, or 4 for all of the numeric
 *                      primitive types.  If a user needs to instantiate a
 *                      Matrix class with type/dimensions beyond these, then
 *                      they need to include T_Matrix.h instead.
 * Last Modified:      November 18, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef _MATRIX_H_
#define _MATRIX_H_

// #include <type_traits>   // for common_type

namespace Math
{

// Used whenever values at a given coordinate aren't specified, as in
// constructing a matrix from another matrix with smaller dimensions.
template< typename T >
struct MatrixFill
{
    static const T DEFAULT = 0; // redefine for non-numeric types
};

// Used to determine type of matrix arithmetic operations
template< typename T, typename U = T >
struct MatrixOperationResult
{
    // typedef std::common_type< T, U >:: type Type
    typedef decltype( T() + U() ) Type;
};
template< typename T >
struct MatrixOperationResult< T >
{
    typedef T Type;
};
template< typename T >
struct MatrixInverse
{
    typedef MatrixOperationResult< T >::Type Type;
};
template<>
struct MatrixInverse< char >
{
    typedef float Type;
};
template<>
struct MatrixInverse< short >
{
    typedef double Type;
};
template<>
struct MatrixInverse< int >
{
    typedef double Type;
};
template<>
struct MatrixInverse< long >
{
    typedef long double Type;
};
template<>
struct MatrixInverse< long long >
{
    typedef long double Type;
};

// Represents a matrix of values of a set type with set dimensions.
template< typename T, unsigned int M, unsigned int N = M >
class Matrix
{
public:

    // Copy/move constructor/operator
    Matrix( const Matrix& ac_roMatrix );
    Matrix& operator=( const Matrix& ac_roMatrix );
    Matrix( Matrix&& a_rroMatrix );
    Matrix& operator=( Matrix&& a_rroMatrix );

    // Construct/assign from a differently-sized matrix
    template< typename U, unsigned int P, unsigned int Q >
    Matrix( const Matrix< U, P, Q >& ac_roMatrix,
            const T& ac_roFill = MatrixFill< T >::DEFAULT );
    template< typename U, unsigned int P, unsigned int Q >
    Matrix& operator=( const Matrix< U, P, Q >& ac_roMatrix,
                       const T& ac_roFill = MatrixFill< T >::DEFAULT );

    // Construct with all values equal to parameter
    template< typename U >
    Matrix( const U& ac_rFill = MatrixFill< U >::DEFAULT );
    template< typename U, typename V >
    Matrix( const U& ac_rFill, const V& ac_rIdentityFill );

    // Construct with data filled in with parameter data one row at a time, one
    // column at a time, until end of parameter data, then filled with either
    // default/previous data
    template< typename U >
    Matrix( const U* const ac_cpData, const unsigned int ac_uiSize = M * N );
    template< typename U >
    Matrix( const U (&ac_raData)[ M * N ] );
    template< typename U, unsigned int t_uiDataSize >
    Matrix( const U (&ac_raData)[ t_uiDataSize ] );

    // Construct with data filled in with parameter data where given and either
    // default/previous data elsewhere
    template< typename U >
    Matrix( const U* const* const ac_cpcpData,
            const unsigned int ac_uiRows = M,
            const unsigned int ac_uiColumns = N );
    template< typename U >
    Matrix( const U (&ac_raaData)[ M ][ N ] );
    template< typename U, unsigned int t_uiRows, unsigned int t_uiColumns >
    Matrix( const U (&ac_raaData)[ t_uiRows ][ t_uiColumns ] );

    // Array access - *non-virtual* override in Vector child class
    T (&operator[])( unsigned int a_uiRow )[ N ];
    const T (&operator[])( unsigned int a_uiRow )[ N ];
    T& operator[]( unsigned int a_uiRow, unsigned int a_uiColumn );
    const T& operator[]( unsigned int a_uiRow, unsigned int a_uiColumn ) const;

    // Scalar multiplication and division
    template< typename U >
    Matrix& operator*=( const U& a_rScalar );
    template< typename U >
    Matrix< MatrixOperationResult< T, U >::Type, M, N >
        operator*( const U& a_rScalar ) const;
    template< typename U >
    Matrix& operator/=( const U& a_rScalar );
    template< typename U >
    Matrix< MatrixOperationResult< T, U >::Type, M, N >
        operator/( const U& a_rScalar ) const;

    // Matrix addition and subtraction
    template< typename U >
    Matrix& operator+=( const Matrix< U, M, N >& ac_roMatrix );
    template< typename U >
    Matrix< MatrixOperationResult< T, U >::Type, M, N >
        operator+( const Matrix< U, M, N >& ac_roMatrix ) const;
    template< typename U >
    Matrix& operator-=( const Matrix< U, M, N >& ac_roMatrix );
    template< typename U >
    Matrix< MatrixOperationResult< T, U >::Type, M, N >
        operator-( const Matrix< U, M, N >& ac_roMatrix ) const;

    // Matrix multiplication
    template< typename U, unsigned int P >
    Matrix< MatrixOperationResult< T, U >::Type, M, N >
        operator*( const Matrix< U, N, P >& ac_roMatrix ) const;
    // Matrix "division" = multiplication by inverse
    template< typename U, unsigned int P >
    Matrix< MatrixOperationResult< T, U >::Type, M, N >
        operator/( const Matrix< U, P, N >& ac_roMatrix ) const;

    // Transpose
    Matrix< T, N, M > Transpose() const;

    // Determinant - return 0 if non-square matrix
    T Determinant();

    // Inverse
    bool IsInvertable() const;
    bool Invert();  // if not square & invertable, change nothing & return falses
    Matrix< MatrixInverse< T >::Type, N, M > Inverse() const;

    static const unsigned int ROWS = M;
    static const unsigned int COLUMNS = N;

protected:

    // if not invertable by given method, change nothing & return false
    bool LeftInverse( Matrix< MatrixInverse< T >::Type, N, M >& a_roMatrix );
    bool RightInverse( Matrix< MatrixInverse< T >::Type, N, M >& a_roMatrix );
    bool TrueInverse( Matrix< MatrixInverse< T >::Type, N, M >& a_roMatrix );

    // elements of the matrix
    T m_aaData[ M ][ N ];

};

// Zero matrix
template< typename T, unsigned int M, unsigned int N >
const Matrix< T, M, N > ZERO_MATRIX;
template< typename T, unsigned int M, unsigned int N >
ZERO_MATRIX< T, M, N >( 0 );

// All-ones matrix
template< typename T, unsigned int M, unsigned int N >
const Matrix< T, M, N > ALL_ONES_MATRIX;
template< typename T, unsigned int M, unsigned int N >
ALL_ONES_MATRIX< T, M, N >( 1 );

// Identity matrix
template< typename T, unsigned int N >
const Matrix< T, N > IDENTITY_MATRIX;
template< typename T, unsigned int N >
IDENTITY_MATRIX< T, N >( 0, 1 );

}   // namespace Math

#endif  // _MATRIX_H_
