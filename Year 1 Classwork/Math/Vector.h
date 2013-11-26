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
class Vector : public virtual NumericVectorBase< T, N, t_bIsRow >
{
public:

    // simplify typing
    typedef NumericVectorBase< T, N, t_bIsRow > BaseType;
    typedef typename BaseType::BaseType VectorBaseType;

    // virtual destructor needed due to virtual methods
    virtual ~Vector();

    // Constructors that forward to base class constructors
    Vector();
    Vector( const Vector& ac_roVector );
    Vector( const VectorBaseType& ac_roVector );
    Vector( const MatrixType& ac_roMatrix );
    Vector( Vector&& a_rroVector );
    Vector( VectorBaseType&& a_rroVector );
    Vector( MatrixType&& a_rroMatrix );
    template< typename U, unsigned int Q, bool t_bOtherIsRow >
    Vector( const Vector< U, Q, t_bOtherIsRow >& ac_roVector );
    template< typename U, unsigned int Q, bool t_bOtherIsRow >
    Vector( const VectorBase< U, Q, t_bOtherIsRow >& ac_roVector );
    template< typename U, unsigned int P, unsigned int Q >
    Vector( const MatrixBase< U, P, Q >& ac_roMatrix,
            const T& ac_rFill = DEFAULT_FILL );
    template< typename U >
    Vector( const U& ac_rFill );
    template< typename U, unsigned int t_uiSize >
    Vector( const U (&ac_raData)[ t_uiSize ],
            const T& ac_rFill = DEFAULT_FILL );
    template< typename U >
    Vector( const U* const ac_cpData,
            const unsigned int ac_uiSize,
            const T& ac_rFill = DEFAULT_FILL );
};

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

    // virtual destructor needed due to virtual methods
    virtual ~Vector();

    // Constructors that forward to base class constructors
    Vector();
    Vector( const Vector& ac_roVector );
    Vector( const VectorBaseType& ac_roVector );
    Vector( const MatrixType& ac_roMatrix );
    Vector( Vector&& a_rroVector );
    Vector( VectorBaseType&& a_rroVector );
    Vector( MatrixType&& a_rroMatrix );
    template< typename U, unsigned int Q, bool t_bOtherIsRow >
    Vector( const Vector< U, Q, t_bOtherIsRow >& ac_roVector );
    template< typename U, unsigned int Q, bool t_bOtherIsRow >
    Vector( const VectorBase< U, Q, t_bOtherIsRow >& ac_roVector );
    template< typename U, unsigned int P, unsigned int Q >
    Vector( const MatrixBase< U, P, Q >& ac_roMatrix,
            const T& ac_rFill = DEFAULT_FILL );
    template< typename U >
    Vector( const U& ac_rFill );
    template< typename U, unsigned int t_uiSize >
    Vector( const U (&ac_raData)[ t_uiSize ],
            const T& ac_rFill = DEFAULT_FILL );
    template< typename U >
    Vector( const U* const ac_cpData,
            const unsigned int ac_uiSize,
            const T& ac_rFill = DEFAULT_FILL );

    // Matrix multiplication
    template< typename U, unsigned int P >
    Vector< CommonType< T, U >::Type, P, true >
        operator*( const Matrix< U, N, P >& ac_roMatrix ) const;
    // Matrix "division" = multiplication by inverse, if one exists
    template< typename U, unsigned int P >
    Vector< CommonType< T, MatrixInverse< U >::Type >::Type, P, true >
        operator/( const Matrix< U, N, P >& ac_roMatrix ) const;
};

}   // namespace Math

#endif  // _VECTOR_H_
