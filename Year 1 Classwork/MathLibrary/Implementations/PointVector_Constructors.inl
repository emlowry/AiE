/******************************************************************************
 * File:               PointVector_Constructors.inl
 * Author:             Elizabeth Lowry
 * Date Created:       February 11, 2014
 * Description:        Inline constructor implementations for PointVector.
 * Last Modified:      February 11, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef POINT_VECTOR__CONSTRUCTORS__INL
#define POINT_VECTOR__CONSTRUCTORS__INL

#include "../Declarations/PointVector.h"
#include "../Declarations/HomogeneousVector.h"
#include "../Declarations/ImExportMacro.h"

namespace Plane
{

// Constructors that forward to base class constructors
template< typename T >
INLINE PointVector< T >::PointVector()
    : BaseType(), x( m_aaData[0][0] ), y( m_aaData[0][1] ) {}
template< typename T >
INLINE PointVector< T >::PointVector( const PointVector& ac_roVector )
    : BaseType( ac_roVector ), x( m_aaData[0][0] ), y( m_aaData[0][1] ) {}
template< typename T >
INLINE PointVector< T >::PointVector( PointVector&& a_rroVector )
    : BaseType( std::forward< PointVector >( a_rroVector ) ),
      x( m_aaData[0][0] ), y( m_aaData[0][1] ) {}
template< typename T >
INLINE PointVector< T >::PointVector( const RootType& ac_roMatrix )
    : BaseType( ac_roMatrix ), x( m_aaData[0][0] ), y( m_aaData[0][1] ) {}
template< typename T >
INLINE PointVector< T >::PointVector( const T& ac_rFill )
    : BaseType( ac_rFill ), x( m_aaData[0][0] ), y( m_aaData[0][1] ) {}
template< typename T >
INLINE PointVector< T >::PointVector( const T (&ac_raData)[ 2 ] )
    : BaseType( ac_raData ), x( m_aaData[0][0] ), y( m_aaData[0][1] ) {}
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

// Construct from the given coordinates
template< typename T >
INLINE PointVector< T >::PointVector( const T& ac_rX, const T& ac_rY )
    : BaseType(), x( m_aaData[0][0] ), y( m_aaData[0][1] )
{
    x = ac_rX;
    y = ac_rY;
}

// Construct from homogenous vector
template< typename T >
INLINE PointVector< T >::PointVector( const HomogeneousVector& ac_roVector )
    : BaseType(), x( m_aaData[0][0] ), y( m_aaData[0][1] )
{
    operator=( ac_roVector );
}
template< typename T >
INLINE PointVector< T >& PointVector< T >::
    operator=( const HomogeneousVector& ac_roVector )
{
    BaseType::operator=( HomogeneousVector( ac_roVector ).Homogenize() );
    return *this;
}

}   // namespace Plane

namespace Space
{

// Constructors that forward to base class constructors
template< typename T >
INLINE PointVector< T >::PointVector()
    : BaseType(),
      x( m_aaData[0][0] ), y( m_aaData[0][1] ), z( m_aaData[0][2] ) {}
template< typename T >
INLINE PointVector< T >::PointVector( const PointVector& ac_roVector )
    : BaseType( ac_roVector ),
      x( m_aaData[0][0] ), y( m_aaData[0][1] ), z( m_aaData[0][2] ) {}
template< typename T >
INLINE PointVector< T >::PointVector( PointVector&& a_rroVector )
    : BaseType( std::forward< PointVector >( a_rroVector ) ),
      x( m_aaData[0][0] ), y( m_aaData[0][1] ), z( m_aaData[0][2] ) {}
template< typename T >
INLINE PointVector< T >::PointVector( const RootType& ac_roMatrix )
    : BaseType( ac_roMatrix ),
      x( m_aaData[0][0] ), y( m_aaData[0][1] ), z( m_aaData[0][2] ) {}
template< typename T >
INLINE PointVector< T >::PointVector( const T& ac_rFill )
    : BaseType( ac_rFill ),
      x( m_aaData[0][0] ), y( m_aaData[0][1] ), z( m_aaData[0][2] ) {}
template< typename T >
INLINE PointVector< T >::PointVector( const T (&ac_raData)[ 3 ] )
    : BaseType( ac_raData ),
      x( m_aaData[0][0] ), y( m_aaData[0][1] ), z( m_aaData[0][2] ) {}
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

// Construct from the given coordinates
template< typename T >
INLINE PointVector< T >::PointVector( const T& ac_rX, const T& ac_rY, const T& ac_rZ )
    : BaseType(), x( m_aaData[0][0] ), y( m_aaData[0][1] ), z( m_aaData[0][2] )
{
    x = ac_rX;
    y = ac_rY;
    z = ac_rZ;
}

// Construct from homogenous vector
template< typename T >
INLINE PointVector< T >::PointVector( const HomogeneousVector& ac_roVector )
    : BaseType(), x( m_aaData[0][0] ), y( m_aaData[0][1] ), z( m_aaData[0][2] )
{
    operator=( ac_roVector );
}
template< typename T >
INLINE PointVector< T >& PointVector< T >::
    operator=( const HomogeneousVector& ac_roVector )
{
    BaseType::operator=( HomogeneousVector( ac_roVector ).Homogenize() );
    return *this;
}

}   // namespace Space

#endif  // POINT_VECTOR__CONSTRUCTORS__INL
