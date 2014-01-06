/******************************************************************************
 * File:               PointVector_Templates.inl
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        Template function implementations for PointVector.
 * Last Modified:      January 5, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef POINT_VECTOR__TEMPLATES__INL
#define POINT_VECTOR__TEMPLATES__INL

#include "Declarations/PointVector.h"
#include "Declarations/HomogeneousVector.h"

namespace Plane
{

// Constructors that forward to base class constructors
template< typename U, unsigned int Q, bool t_bOtherIsRow >
inline PointVector::
    PointVector( const Vector< U, Q, t_bOtherIsRow >& ac_roVector,
                 double a_dFill )
    : BaseType( ac_roVector, a_dFill ), x( At(0) ), y( At(1) ) {}
template< unsigned int Q, bool t_bOtherIsRow >
inline PointVector::
    PointVector( Vector< double, Q, t_bOtherIsRow >&& a_rroVector,
                 double a_dFill )
    : BaseType( std::forward< Vector< double, Q, t_bOtherIsRow > >( a_rroVector ),
                a_dFill ),
      x( At(0) ), y( At(1) ) {}
template< typename U, unsigned int Q, bool t_bOtherIsRow >
inline PointVector::
    PointVector( const VectorBase< U, Q, t_bOtherIsRow >& ac_roVector,
                 double a_dFill )
    : BaseType( ac_roVector, a_dFill ), x( At(0) ), y( At(1) ) {}
template< unsigned int Q, bool t_bOtherIsRow >
inline PointVector::
    PointVector( VectorBase< double, Q, t_bOtherIsRow >&& a_rroVector,
                 double a_dFill )
    : BaseType( std::forward< VectorBase< double, Q, t_bOtherIsRow > >( a_rroVector ),
                a_dFill ),
      x( At(0) ), y( At(1) ) {}
template< typename U, unsigned int P, unsigned int Q >
inline PointVector::PointVector( const MatrixBase< U, P, Q >& ac_roMatrix,
                                 double a_dFill )
    : BaseType( ac_roMatrix, a_dFill ), x( At(0) ), y( At(1) ) {}
template< unsigned int P, unsigned int Q >
inline PointVector::PointVector( MatrixBase< double, P, Q >&& a_rroMatrix,
                                 double a_dFill )
    : BaseType( std::forward< MatrixBase< double, Q, t_bOtherIsRow > >( a_rroMatrix ),
                a_dFill ),
      x( At(0) ), y( At(1) ) {}

}   // namespace Plane

namespace Space
{

// Constructors that forward to base class constructors
template< typename U, unsigned int Q, bool t_bOtherIsRow >
inline PointVector::
    PointVector( const Vector< U, Q, t_bOtherIsRow >& ac_roVector,
                 double a_dFill )
    : BaseType( ac_roVector, a_dFill ), x( At(0) ), y( At(1) ), z( At(2) ) {}
template< unsigned int Q, bool t_bOtherIsRow >
inline PointVector::
    PointVector( Vector< double, Q, t_bOtherIsRow >&& a_rroVector,
                 double a_dFill )
    : BaseType( std::forward< Vector< double, Q, t_bOtherIsRow > >( a_rroVector ),
                a_dFill ),
      x( At(0) ), y( At(1) ), z( At(2) ) {}
template< typename U, unsigned int Q, bool t_bOtherIsRow >
inline PointVector::
    PointVector( const VectorBase< U, Q, t_bOtherIsRow >& ac_roVector,
                 double a_dFill )
    : BaseType( ac_roVector, a_dFill ), x( At(0) ), y( At(1) ), z( At(2) ) {}
template< unsigned int Q, bool t_bOtherIsRow >
inline PointVector::
    PointVector( VectorBase< double, Q, t_bOtherIsRow >&& a_rroVector,
                 double a_dFill )
    : BaseType( std::forward< VectorBase< double, Q, t_bOtherIsRow > >( a_rroVector ),
                a_dFill ),
      x( At(0) ), y( At(1) ), z( At(2) ) {}
template< typename U, unsigned int P, unsigned int Q >
inline PointVector::PointVector( const MatrixBase< U, P, Q >& ac_roMatrix,
                                 double a_dFill )
    : BaseType( ac_roMatrix, a_dFill ), x( At(0) ), y( At(1) ), z( At(2) ) {}
template< unsigned int P, unsigned int Q >
inline PointVector::PointVector( MatrixBase< double, P, Q >&& a_rroMatrix,
                                 double a_dFill )
    : BaseType( std::forward< MatrixBase< double, Q, t_bOtherIsRow > >( a_rroMatrix ),
                a_dFill ),
      x( At(0) ), y( At(1) ), z( At(2) ) {}

}   // namespace Space

#endif  // POINT_VECTOR__TEMPLATES__INL
