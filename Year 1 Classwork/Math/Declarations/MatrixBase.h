/******************************************************************************
 * File:               MatrixBase.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 20, 2013
 * Description:        Base class for matrices of any type.
 * Last Modified:      December 10, 2013
 * Last Modification:  Debugging.
 ******************************************************************************/

#ifndef MATRIX_BASE__H
#define MATRIX_BASE__H

#include "MostDerivedAddress.h"

namespace Math
{

// Forward-declare VectorBase, include definition *after* MatrixBase definition,
// since MatrixBase is the parent of VectorBase.
template< typename T, unsigned int N, bool t_bIsRow/* = true*/ >
class VectorBase;

// Base class for matrices.  For matrices with mathematical operations beyond
// transposition, use the child Matrix class instead.
template< typename T, unsigned int M, unsigned int N = M >
class MatrixBase : public virtual MostDerivedAddress
{
public:

    // Simplify typing
    typedef VectorBase< T, M, false > ColumnVectorType;
    typedef VectorBase< T, N, true > RowVectorType;
    typedef MatrixBase< T, N, M > TransposeType;

    // destructor
    virtual ~MatrixBase();
    
    // Copy/move constructor
    MatrixBase( const MatrixBase& ac_roMatrix );
    MatrixBase( MatrixBase&& a_rroMatrix );

    // Construct/assign from a differently-sized/typed matrix
    template< typename U, unsigned int P, unsigned int Q >
    MatrixBase( const MatrixBase< U, P, Q >& ac_roMatrix,
                const T& ac_rFill = DefaultFill< T >() );
    template< unsigned int P, unsigned int Q >
    MatrixBase( MatrixBase< T, P, Q >&& a_rroMatrix,
                const T& ac_rFill = DefaultFill< T >() );
    template< typename U, unsigned int P, unsigned int Q >
    MatrixBase& operator=( const MatrixBase< U, P, Q >& ac_roMatrix );
    template< unsigned int P, unsigned int Q >
    MatrixBase& operator=( MatrixBase< T, P, Q >&& a_rroMatrix );

    // Construct/assign all values equal to parameter
    MatrixBase( const T& ac_rFill = DefaultFill< T >() );
    MatrixBase& operator=( const T& ac_rFill );

    // Construct/assign with parameter data one row at a time until end of
    // parameter data, then filled with default/previous data
    MatrixBase( const T* const ac_cpData,
                const unsigned int ac_uiSize,
                const T& ac_rFill = DefaultFill< T >() );
    MatrixBase( const T (&ac_raData)[ M*N ] );
    MatrixBase& operator=( const T (&ac_raData)[ M*N ] );

    // Construct/assign with parameter data where given and default/previous
    // data elsewhere
    MatrixBase( const T* const* const ac_cpcpData,
                const unsigned int ac_uiRows,
                const unsigned int ac_uiColumns,
                const T& ac_rFill = DefaultFill< T >() );
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
    bool operator==( const MatrixBase& ac_roMatrix ) const;
    bool operator!=( const MatrixBase& ac_roMatrix ) const;
    
    // Array access - *non-virtual* override in VectorBase child class
    T (&operator[]( unsigned int a_uiRow ))[ N ];
    const T (&operator[]( unsigned int a_uiRow ) const)[ N ];
    T& At( unsigned int a_uiRow, unsigned int a_uiColumn );
    const T& At( unsigned int a_uiRow, unsigned int a_uiColumn ) const;

    // Get row/column vectors - redefine non-virtually in child classes to
    // return correct type, since return type is concrete and not a pointer or
    // reference.
    ColumnVectorType Column( unsigned int ac_uiIndex ) const;
    RowVectorType Row( unsigned int ac_uiIndex ) const;

    // Shift elements right/down the given number of spaces, wrapping around the
    // ends of columns and rows
    // Example:
    // Matrix m = { { 0, 1, 2 }, { 10, 11, 12 }, { 20, 21, 22 } };
    // m.Shift( 1, 1 );
    // // m == { { 22, 20, 21 }, { 2, 0, 1 }, { 12, 10, 11 } }
    // m.Shift( -1, -1 );
    // // m == { { 0, 1, 2 }, { 10, 11, 12 }, { 20, 21, 22 } }
    void Shift( int a_iRight, int a_iDown = 0 );
    
    // Get smaller matrices by removing a row and/or column - redefine
    // non-virtually in child classes to return the correct type.
    MatrixBase< T, ( M > 0 ? M-1 : 0 ), ( N > 0 ? N-1 : 0 ) >
        MinusRowAndColumn( unsigned int a_uiRow,
                           unsigned int a_uiColumn ) const;
    MatrixBase< T, M, ( N > 0 ? N-1 : 0 ) >
        MinusColumn( unsigned int a_uiColumn ) const;
    MatrixBase< T, ( M > 0 ? M-1 : 0 ), N >
        MinusRow( unsigned int a_uiRow ) const;

    // Transpose - redefine non-virtually in child classes to return the correct
    // type
    TransposeType Transpose() const;

    static const unsigned int ROWS = M;
    static const unsigned int COLUMNS = N;

protected:

    // elements of the matrix
    T m_aaData[ M ][ N ];

};

// Used whenever values at a given coordinate aren't specified, as in
// constructing a matrix from another matrix with smaller dimensions.
template< typename T >
const T& DefaultFill();

//
// For non-numeric types, be sure to define the following:
//
//  // YourType.h:
//  const YourType& DefaultFill();
//
//  // YourType.cpp:
//  const YourType& DefaultFill()
//  {
//      // Instead of this, you could just return some other static constant
//      static YourType fill = /* default YourType */;
//      return fill;
//  }
//

}   // namespace Math

// MatrixBase *must* be defined before VectorBase, but VectorBase must be defined
// before MatrixBase implementations.
#include "VectorBase.h"
#include "Implementations/MatrixBase.inl"

#endif  // MATRIX_BASE__H
