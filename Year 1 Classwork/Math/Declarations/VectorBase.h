/******************************************************************************
 * File:               VectorBase.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 25, 2013
 * Description:        Base class for vectors of any type.
 * Last Modified:      December 10, 2013
 * Last Modification:  Debugging.
 ******************************************************************************/

#ifndef VECTOR_BASE__H
#define VECTOR_BASE__H

#include "MatrixBase.h"

namespace Math
{

// If a one-row or one-column matrix is explicitly a vector, then certain things
// work differently.  To treat a vector as a matrix, cast it or work through a
// matrix-type reference or pointer.
template< typename T, unsigned int N, bool t_bIsRow = true >
class VectorBase : public virtual MatrixBase< T,
                                              ( t_bIsRow ? 1 : N ),
                                              ( t_bIsRow ? N : 1 ) >
{
public:

    // Simplify typing
    typedef MatrixBase< T, ROWS, COLUMNS > BaseType;
    typedef VectorBase< T, N, false > ColumnVectorType;
    typedef VectorBase< T, N > RowVectorType;
    typedef VectorBase< T, N, !t_bIsRow > TransposeType;

    // inherit assignment operators
    using BaseType::operator=;

    // destructor
    virtual ~VectorBase();
    
    // Constructors that forward to base class constructors
    VectorBase();
    VectorBase( const VectorBase& ac_roVector );
    VectorBase( const BaseType& ac_roMatrix );
    VectorBase( VectorBase&& a_rroVector );
    VectorBase( BaseType&& a_rroMatrix );
    template< typename U, unsigned int P, unsigned int Q >
    VectorBase( const MatrixBase< U, P, Q >& ac_roMatrix,
                const T& ac_rFill = DefaultFill< T >() );
    template< unsigned int P, unsigned int Q >
    VectorBase( MatrixBase< T, P, Q >&& a_rroMatrix,
                const T& ac_rFill = DefaultFill< T >() );
    VectorBase( const T& ac_rFill );
    VectorBase( const T (&ac_raData)[ N ] );
    VectorBase( const T* const ac_cpData,
                const unsigned int ac_uiSize,
                const T& ac_rFill = DefaultFill< T >() );

    // Construct from another type of vector
    template< typename U, unsigned int Q, bool t_bOtherIsRow >
    VectorBase( const VectorBase< U, Q, t_bOtherIsRow >& ac_roVector,
                const T& ac_rFill = DefaultFill< T >() );
    template< typename U, unsigned int Q, bool t_bOtherIsRow >
    VectorBase& operator=( const VectorBase< U, Q, t_bOtherIsRow >& ac_roVector );
    template< unsigned int Q, bool t_bOtherIsRow >
    VectorBase( VectorBase< T, Q, t_bOtherIsRow >&& a_rroVector,
                const T& ac_rFill = DefaultFill< T >() );
    template< unsigned int Q, bool t_bOtherIsRow >
    VectorBase& operator=( VectorBase< T, Q, t_bOtherIsRow >&& a_rroVector );

    // Element access - hides parent class row-returning implementation
    T& operator[]( unsigned int a_uiIndex );
    const T& operator[]( unsigned int a_uiIndex ) const;

    // Instead of getting a row or column of a matrix, return this vector in row
    // or column form.
    ColumnVectorType Column() const;
    RowVectorType Row() const;

    // Get a smaller vector by removing an element
    VectorBase< T, ( N > 0 ? N-1 : 0 ), t_bIsRow >
        MinusElement( unsigned int a_uiIndex ) const;

    // Transpose - non-virtual override, since result is a concrete type instead
    // of a pointer or a reference
    TransposeType Transpose() const;

    // Shift elements by the given number of places
    void Shift( int a_iPlaces );

    static const unsigned int IS_ROW_VECTOR = t_bIsRow;
    static const unsigned int SIZE = N;

protected:

    // used by operator[] and other places that need to get an element
    T& At( const unsigned int ac_uiIndex );
    const T& At( const unsigned int ac_uiIndex ) const;

private:

    // Non-virtual override - if explicitly treated as a matrix, then matrix
    // implementation should be available, otherwise no implementation should be
    // available
    typedef typename BaseType::ColumnVectorType BaseColumnVectorType;
    BaseColumnVectorType Column( unsigned int ac_uiIndex ) const;
    typedef typename BaseType::RowVectorType BaseRowVectorType;
    BaseRowVectorType Row( unsigned int ac_uiIndex ) const;
    MatrixBase< T, ( !t_bIsRow && N > 0 ? N-1 : 0 ), ( t_bIsRow && N > 0 ? N-1 : 0 ) >
        MinusRowAndColumn( unsigned int a_uiRow, unsigned int a_uiColumn ) const;
    MatrixBase< T, ( !t_bIsRow ? N : 1 ), ( t_bIsRow && N > 0 ? N-1 : 0 ) >
        MinusColumn( unsigned int a_uiColumn ) const;
    MatrixBase< T, ( !t_bIsRow && N > 0 ? N-1 : 0 ), ( t_bIsRow ? N : 1 ) >
        MinusRow( unsigned int a_uiRow ) const;
    void Shift( int a_iRight, int a_iDown = 0 );

};

}   // namespace Math

#include "Implementations/VectorBase.inl"

#endif  // VECTOR_BASE__H