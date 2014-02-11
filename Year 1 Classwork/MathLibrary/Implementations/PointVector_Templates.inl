/******************************************************************************
 * File:               PointVector_Templates.inl
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        Template function implementations for PointVector.
 * Last Modified:      January 5, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

#ifndef POINT_VECTOR__TEMPLATES__INL
#define POINT_VECTOR__TEMPLATES__INL

#include "Declarations/PointVector.h"
#include "Declarations/HomogeneousVector.h"
#include "Declarations/ImExportMacro.h"

namespace Plane
{

// Constructors that forward to base class constructors
template< typename T >
template< typename U, unsigned int Q, bool t_bOtherIsRow >
INLINE PointVector< T >::
    PointVector( const Vector< U, Q, t_bOtherIsRow >& ac_roVector,
                 const T& ac_rFill )
    : BaseType( ac_roVector, ac_rFill ),
      x( m_aaData[0][0] ), y( m_aaData[0][1] ) {}
template< typename T >
template< typename U, unsigned int P, unsigned int Q >
INLINE PointVector< T >::PointVector( const Matrix< U, P, Q >& ac_roMatrix,
                                      const T& ac_rFill )
    : BaseType( ac_roMatrix, ac_rFill ),
      x( m_aaData[0][0] ), y( m_aaData[0][1] ) {}

// Assignment operators that pass to base class
template< typename T >
template< typename U, unsigned int Q, bool t_bOtherIsRow >
INLINE PointVector< T >& PointVector< T >::
    operator=( const Vector< U, Q, t_bOtherIsRow >& ac_roVector )
{
    BaseType::operator=( ac_roVector );
    return *this;
}
template< typename T >
template< typename U, unsigned int P, unsigned int Q >
INLINE PointVector< T >& PointVector< T >::
    operator=( const Matrix< U, P, Q >& ac_roMatrix )
{
    BaseType::operator=( ac_roMatrix );
    return *this;
}

}   // namespace Plane

namespace Space
{

// Constructors that forward to base class constructors
template< typename T >
template< typename U, unsigned int Q, bool t_bOtherIsRow >
INLINE PointVector< T >::
    PointVector( const Vector< U, Q, t_bOtherIsRow >& ac_roVector,
                 const T& ac_rFill )
    : BaseType( ac_roVector, ac_rFill ),
      x( m_aaData[0][0] ), y( m_aaData[0][1] ), z( m_aaData[0][2] ) {}
template< typename T >
template< typename U, unsigned int P, unsigned int Q >
INLINE PointVector< T >::PointVector( const Matrix< U, P, Q >& ac_roMatrix,
                                      const T& ac_rFill )
    : BaseType( ac_roMatrix, ac_rFill ),
      x( m_aaData[0][0] ), y( m_aaData[0][1] ), z( m_aaData[0][2] ) {}

// Assignment operators that pass to base class
template< typename T >
template< typename U, unsigned int Q, bool t_bOtherIsRow >
INLINE PointVector< T >& PointVector< T >::
    operator=( const Vector< U, Q, t_bOtherIsRow >& ac_roVector )
{
    BaseType::operator=( ac_roVector );
    return *this;
}
template< typename T >
template< typename U, unsigned int P, unsigned int Q >
INLINE PointVector< T >& PointVector< T >::
    operator=( const Matrix< U, P, Q >& ac_roMatrix )
{
    BaseType::operator=( ac_roMatrix );
    return *this;
}

}   // namespace Space

#endif  // POINT_VECTOR__TEMPLATES__INL
