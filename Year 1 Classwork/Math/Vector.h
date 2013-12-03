/******************************************************************************
 * File:               Vector.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 25, 2013
 * Description:        Base class for vectors of numeric type.
 *                      The library compiles Vector classes with dimensions of
 *                      any of 1, 2, 3, or 4 for all of the numeric primitive
 *                      types.  If a user needs to instantiate a Vector class
 *                      with dimensions beyond these, then they need to include
 *                      T_Vector.h instead.  For a type that doesn't have the
 *                      arithmatic operations defined, include T_VectorBase.h to
 *                      use the base class.
 * Last Modified:      November 25, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "NumericVectorBase.h"

namespace Math
{

// Forward declare the actual Vector class
template< typename T, unsigned int N, bool t_bIsRow = true >
class Vector;

// Row vector implementation has specialized multiplication/division operators
// that return vectors, specifically, when multiplied by a matrix instead of
// just returning a regular one-row matrix
template< typename T, unsigned int N >
class Vector< T, N > : public virtual NumericVectorBase< T, N >
{
public:

    // simplify typing
    typedef NumericVectorBase< T, N, true > BaseType;
    typedef typename BaseType::BaseType VectorBaseType;

    // inherit assignment operators
    using BaseType::operator=;

    // virtual destructor needed due to virtual methods
    virtual ~Vector();

    // Constructors that forward to base class constructors
    Vector();
    Vector( const Vector& ac_roVector );
    Vector& operator=( const Vector& ac_roVector );
    Vector( const BaseType& ac_roVector );
    Vector( const VectorBaseType& ac_roVector );
    Vector( const MatrixType& ac_roMatrix );
    Vector( Vector&& a_rroVector );
    Vector& operator=( Vector&& a_rroVector );
    Vector( BaseType&& a_rroVector );
    Vector( VectorBaseType&& a_rroVector );
    Vector( MatrixType&& a_rroMatrix );
    template< unsigned int Q, bool t_bOtherIsRow >
    Vector( const NumericVectorBase< T, Q, t_bOtherIsRow >& ac_roVector,
            const T& ac_rFill = DEFAULT_FILL );
    template< unsigned int Q, bool t_bOtherIsRow >
    Vector( const VectorBase< T, Q, t_bOtherIsRow >& ac_roVector,
            const T& ac_rFill = DEFAULT_FILL );
    template< typename U >
    Vector( const MatrixBase< U, ROWS, COLUMNS >& ac_roMatrix );
    template< unsigned int P, unsigned int Q >
    Vector( const MatrixBase< T, P, Q >& ac_roMatrix,
            const T& ac_rFill = DEFAULT_FILL );
    Vector( const T& ac_rFill );
    Vector( const T (&ac_raData)[ N ] );
    Vector( const T* const ac_cpData,
            const unsigned int ac_uiSize,
            const T& ac_rFill = DEFAULT_FILL );

    // Matrix multiplication produces another row vector
    template< unsigned int P >
    virtual Vector< T, P >
        operator*( const Matrix< T, N, P >& ac_roMatrix ) const override;
    // Matrix "division" = multiplication by inverse, if one exists
    template< unsigned int P >
    virtual Vector< MatrixInverse< T >::Type, P >
        operator/( const Matrix< T, P, N >& ac_roMatrix ) const override;
};

// Column vector
template< typename T, unsigned int N >
class Vector< T, N, false > : public virtual NumericVectorBase< T, N, false >
{
public:

    // simplify typing
    typedef NumericVectorBase< T, N, false > BaseType;
    typedef typename BaseType::BaseType VectorBaseType;

    // Inherit matrix implementation for multiplication by 1xN (N>1) matrices
    using MatrixType::operator*;
    using MatrixType::operator/;

    // virtual destructor needed due to virtual methods
    virtual ~Vector();

    // Constructors that forward to base class constructors
    Vector();
    Vector( const Vector& ac_roVector );
    Vector& operator=( const Vector& ac_roVector );
    Vector( const BaseType& ac_roVector );
    Vector( const VectorBaseType& ac_roVector );
    Vector( const MatrixType& ac_roMatrix );
    Vector( Vector&& a_rroVector );
    Vector& operator=( Vector&& a_rroVector );
    Vector( BaseType&& a_rroVector );
    Vector( VectorBaseType&& a_rroVector );
    Vector( MatrixType&& a_rroMatrix );
    template< unsigned int Q, bool t_bOtherIsRow >
    Vector( const NumericVectorBase< T, Q, t_bOtherIsRow >& ac_roVector,
            const T& ac_rFill = DEFAULT_FILL );
    template< unsigned int Q, bool t_bOtherIsRow >
    Vector( const VectorBase< T, Q, t_bOtherIsRow >& ac_roVector,
            const T& ac_rFill = DEFAULT_FILL );
    template< typename U >
    Vector( const MatrixBase< U, ROWS, COLUMNS >& ac_roMatrix );
    template< unsigned int P, unsigned int Q >
    Vector( const MatrixBase< T, P, Q >& ac_roMatrix,
            const T& ac_rFill = DEFAULT_FILL );
    Vector( const T& ac_rFill );
    Vector( const T (&ac_raData)[ N ] );
    Vector( const T* const ac_cpData,
            const unsigned int ac_uiSize,
            const T& ac_rFill = DEFAULT_FILL );

    // Matrix multiplication uses matrix implementation unless the multiplier is
    // a 1x1 matrix, in which case another column matrix is produced.
    virtual Vector< T, N, false >
        operator*( const Matrix< T, 1 >& ac_roMatrix ) const override;
    // Matrix "division" = multiplication by inverse, if one exists
    virtual Vector< MatrixInverse< T >::Type, N, false >
        operator/( const Matrix< T, 1 >& ac_roMatrix ) const override;
};

}   // namespace Math

#endif  // _VECTOR_H_
