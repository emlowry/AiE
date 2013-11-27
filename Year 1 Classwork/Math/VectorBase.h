/******************************************************************************
 * File:               VectorBase.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 25, 2013
 * Description:        Base class for vectors of any type.
 *                      The library compiles VectorBase classes with dimensions
 *                      of 1, 2, 3, andor 4 for string, char*, and void* types.
 *                      If a user needs to instantiate a MatrixBase class with
 *                      type or dimensions beyond these, then they need to
 *                      include T_VectorBase.h instead.
 * Last Modified:      November 25, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef _VECTOR_BASE_H_
#define _VECTOR_BASE_H_

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
    typedef Matrix< T, ( t_bIsRow ? 1 : N ), ( t_bIsRow ? N : 1 ) > BaseType;
    typedef VectorBase< T, M, false > ColumnVectorType;
    typedef VectorBase< T, N > RowVectorType;
    typedef VectorBase< T, N, !t_bIsRow > TransposeType;

    // inherit assignment operators
    using BaseType::operator=;

    // virtual destructor needed due to virtual methods
    virtual ~VectorBase();
    
    // Constructors that forward to base class constructors
    VectorBase();
    VectorBase( const VectorBase& ac_roVector );
    VectorBase& operator=( const VectorBase& ac_roVector );
    VectorBase( const BaseType& ac_roMatrix );
    VectorBase( VectorBase&& a_rroVector );
    VectorBase& operator=( VectorBase&& a_rroVector );
    VectorBase( BaseType&& a_rroMatrix );
    template< typename U, unsigned int P, unsigned int Q >
    VectorBase( const MatrixBase< U, P, Q >& ac_roMatrix,
                const T& ac_rFill = DEFAULT_FILL );
    template< typename U >
    VectorBase( const U& ac_rFill );
    template< typename U, unsigned int t_uiSize >
    VectorBase( const U (&ac_raData)[ t_uiSize ],
                const T& ac_rFill = DEFAULT_FILL );
    template< typename U >
    VectorBase( const U* const ac_cpData,
                const unsigned int ac_uiSize,
                const T& ac_rFill = DEFAULT_FILL );

    // Construct from another type of vector
    template< typename U, unsigned int Q, bool t_bOtherIsRow >
    VectorBase( const VectorBase< U, Q, t_bOtherIsRow >& ac_roVector,
                const T& ac_rFill = DEFAULT_FILL );
    template< typename U, unsigned int Q, bool t_bOtherIsRow >
    VectorBase& operator=( const VectorBase< U, Q, t_bOtherIsRow >& ac_roVector );

    // Element access - hides parent class row-returning implementation
    T& operator[]( unsigned int a_uiIndex );
    const T& operator[]( unsigned int a_uiIndex ) const;

    // Instead of getting a row or column of a matrix, return this vector in row
    // or column form.  Override in child classes to return correct type.
    virtual ColumnVectorType Column() const;
    virtual RowVectorType Row() const;

    // Transpose - override in child classes to return correct type
    virtual TransposeType Transpose() const override;

    static const unsigned int IS_ROW_VECTOR = t_bIsRow;
    static const unsigned int SIZE = N;

protected:

    // used by assignment operator
    template< typename U, unsigned int Q, bool t_bOtherIsRow >
    VectorBase& Assign( const VectorBase< U, Q, t_bOtherIsRow >& ac_roVector );
    template< typename U, unsigned int Q, bool t_bOtherIsRow >
    VectorBase& Assign( VectorBase< U, Q, t_bOtherIsRow >&& a_rroVector );

    // used by operator[] and other places that need to get an element
    T& At( const unsigned int ac_uiIndex );
    const T& At( const unsigned int ac_uiIndex ) const;

};

}   // namespace Math

#endif  // _VECTOR_BASE_H_