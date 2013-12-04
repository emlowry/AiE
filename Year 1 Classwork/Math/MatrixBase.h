/******************************************************************************
 * File:               MatrixBase.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 20, 2013
 * Description:        Base class for matrices of any type.
 *                      The library compiles MatrixBase classes with dimensions
 *                      of any combination of 1, 2, 3, or 4 for string, char*,
 *                      and void* types.  If a user needs to instantiate a
 *                      MatrixBase class with type or dimensions beyond these,
 *                      then they need to include T_MatrixBase.h instead.
 * Last Modified:      November 25, 2013
 * Last Modification:  Adding the closely-entwined VectorBase class.
 ******************************************************************************/

#ifndef _MATRIX_BASE_H_
#define _MATRIX_BASE_H_

namespace Math
{

// Forward-declare VectorBase, include definition *after* MatrixBase definition,
// since MatrixBase is the parent of VectorBase.
template< typename T, unsigned int N, bool t_bIsRow = true >
class VectorBase;

// Base class for matrices.  For matrices with mathematical operations beyond
// transposition, use the child Matrix class instead.
template< typename T, unsigned int M, unsigned int N = M >
class MatrixBase
{
public:

    // Simplify typing
    typedef VectorBase< T, M, false > ColumnVectorType;
    typedef VectorBase< T, N > RowVectorType;
    typedef MatrixBase< T, N, M > TransposeType;
    static const T& DEFAULT_FILL;   // referance to MatrixFill< T >::DEFAULT

    // Default constructor fills array with DEFAULT_FILL
    MatrixBase();

    // Virtual destructor needed, since Transpose and assignment functions
    // are virtual.  Assignment operators are implemented in terms of virtual
    // Assign functions in case child classes have more fields to set.
    virtual ~MatrixBase();
    
    // Copy/move constructor/operator
    MatrixBase( const MatrixBase& ac_roMatrix );
    MatrixBase& operator=( const MatrixBase& ac_roMatrix );
    MatrixBase( MatrixBase&& a_rroMatrix );
    MatrixBase& operator=( MatrixBase&& a_rroMatrix );

    // Construct/assign from a differently-sized/typed matrix
    template< typename U >
    MatrixBase( const MatrixBase< U, M, N >& ac_roMatrix );
    template< unsigned int P, unsigned int Q >
    MatrixBase( const MatrixBase< T, P, Q >& ac_roMatrix,
                const T& ac_rFill = DEFAULT_FILL );
    template< typename U >
    MatrixBase& operator=( const MatrixBase< U, M, N >& ac_roMatrix );
    template< unsigned int P, unsigned int Q >
    MatrixBase& operator=( const MatrixBase< T, P, Q >& ac_roMatrix );

    // Construct/assign all values equal to parameter
    MatrixBase( const T& ac_rFill );
    MatrixBase& operator=( const T& ac_rFill );

    // Construct/assign with parameter data one row at a time until end of
    // parameter data, then filled with default/previous data
    MatrixBase( const T* const ac_cpData,
                const unsigned int ac_uiSize,
                const T& ac_rFill = DEFAULT_FILL );
    MatrixBase( const T (&ac_raData)[ M*N ] );
    MatrixBase& operator=( const T (&ac_raData)[ M*N ] );

    // Construct/assign with parameter data where given and default/previous
    // data elsewhere
    MatrixBase( const T* const* const ac_cpcpData,
                const unsigned int ac_uiRows,
                const unsigned int ac_uiColumns,
                const T& ac_rFill = DEFAULT_FILL );
    MatrixBase( const T (&ac_raaData)[ M ][ N ] );
    MatrixBase& operator=( const T (&ac_raaData)[ M ][ N ] );

    // Construct/assign from a set of rows or columns
    MatrixBase( const ColumnVectorType (&ac_raoColumns)[ N ] );
    MatrixBase& operator=( const ColumnVectorType (&ac_raoColumns)[ N ] );
    MatrixBase( const ColumnVectorType* const (&ac_racpoColumns)[ N ] );
    MatrixBase& operator=( const ColumnVectorType* const (&ac_racpoColumns)[ N ] );
    MatrixBase( const RowVectorType (&ac_raoRows)[ M ] );
    MatrixBase& operator=( const RowVectorType (&ac_raoRows)[ M ] );
    MatrixBase( const RowVectorType* const (&ac_racpoRows)[ M ] );
    MatrixBase& operator=( const RowVectorType* const (&ac_racpoRows)[ M ] );

    // Equality and inequality checks
    bool operator==( const Matrix& ac_roMatrix ) const;
    bool operator!=( const Matrix& ac_roMatrix ) const;
    
    // Array access - *non-virtual* override in VectorBase child class
    T (&operator[])( unsigned int a_uiRow )[ N ];
    const T (&operator[])( unsigned int a_uiRow )[ N ] const;
    T& operator[]( unsigned int a_uiRow, unsigned int a_uiColumn );
    const T& operator[]( unsigned int a_uiRow, unsigned int a_uiColumn ) const;

    // Get row/column vectors - redefine in child classes to return correct type
    virtual ColumnVectorType Column( unsigned int ac_uiIndex ) const;
    virtual RowVectorType Row( unsigned int ac_uiIndex ) const;

    // Shift elements right/down the given number of spaces, wrapping around the
    // ends of columns and rows
    // Example:
    // Matrix m = { { 0, 1, 2 }, { 10, 11, 12 }, { 20, 21, 22 } };
    // m.Shift( 1, 1 );
    // // m == { { 22, 20, 21 }, { 2, 0, 1 }, { 12, 10, 11 } }
    // m.Shift( -1, -1 );
    // // m == { { 0, 1, 2 }, { 10, 11, 12 }, { 20, 21, 22 } }
    void Shift( int a_iRight, int a_iDown = 0 );
    
    // Get smaller matrices by removing a row and/or column - redefine in child
    // classes to return the correct type.
    virtual MatrixBase< T, M-1, N-1 >
        MinusRowAndColumn( unsigned int a_uiRow, unsigned int a_uiColumn ) const;
    virtual MatrixBase< T, M, N-1 > MinusColumn( unsigned int a_uiColumn ) const;
    virtual MatrixBase< T, M-1, N > MinusRow( unsigned int a_uiRow ) const;

    // Transpose - redefine in child classes to return correct type
    virtual TransposeType Transpose() const;

    static const unsigned int ROWS = M;
    static const unsigned int COLUMNS = N;

protected:

    // Used by assignment operators so that only child classes with genuinely
    // different behavior need to override.
    virtual MatrixBase& Assign( const MatrixBase& ac_roMatrix );
    virtual MatrixBase& Assign( MatrixBase&& a_rroMatrix );
    template< typename U >
    virtual MatrixBase& Assign( const MatrixBase< U, M, N >& ac_roMatrix );
    template< unsigned int P, unsigned int Q >
    virtual MatrixBase& Assign( const MatrixBase< T, P, Q >& ac_roMatrix );
    virtual MatrixBase& Assign( const T& ac_rFill );
    virtual MatrixBase& Assign( const T (&ac_raData)[ M*N ] );
    virtual MatrixBase& Assign( const T (&ac_raaData)[ M ][ N ] );
    virtual MatrixBase& Assign( const ColumnVectorType (&ac_raColumns)[ N ] );
    virtual MatrixBase& Assign( const ColumnVectorType* const (&ac_rpoaColumns)[ N ] );
    virtual MatrixBase& Assign( const RowVectorType (&ac_raRows)[ M ] );
    virtual MatrixBase& Assign( const RowVectorType* const (&ac_rpoaRows)[ M ] );

    // elements of the matrix
    T m_aaData[ M ][ N ];

};

// Used whenever values at a given coordinate aren't specified, as in
// constructing a matrix from another matrix with smaller dimensions.
template< typename T >
struct MatrixFill
{
    // redefine for non-numeric types
    static const T DEFAULT = 0;
};
template< typename T >
struct MatrixFill< T* >
{
    static const T* DEFAULT;
};

//
// For non-numeric types, be sure to define the following:
//
//  // YourType.h:
//  template<>
//  struct MatrixFill< YourType >
//  {
//      static const YourType DEFAULT;
//  };
//
//  // YourType.cpp:
//  const YourType MatrixFill< YourType >::DEFAULT = /* default YourType */;
//

}   // namespace Math

// MatrixBase *must* be defined before VectorBase.
#include "VectorBase.h"

#endif  // _MATRIX_BASE_H_
