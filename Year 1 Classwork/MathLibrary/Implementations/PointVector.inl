/******************************************************************************
 * File:               PointVector.inl
 * Author:             Elizabeth Lowry
 * Date Created:       December 17, 2013
 * Description:        Inline function implementations for PointVector.
 * Last Modified:      February 4, 2014
 * Last Modification:  Switching from regular inline to macro inline.
 ******************************************************************************/

#ifndef POINT_VECTOR__INL
#define POINT_VECTOR__INL

#include "Declarations/HomogeneousVector.h"
#include "Declarations/PointVector.h"
#include "PointVector_Templates.inl"
#include "Declarations/ImExportMacro.h"

namespace Plane
{

// destructor
template< typename T >
INLINE PointVector< T >::~PointVector() {}

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

// Assignment operators that pass to base class
template< typename T >
INLINE PointVector< T >& PointVector< T >::operator=( const T& ac_rFill )
{
    BaseType::operator=( ac_rFill );
    return *this;
}
template< typename T >
INLINE PointVector< T >& PointVector< T >::operator=( const T (&ac_raData)[ 2 ] )
{
    BaseType::operator=( ac_raData );
    return *this;
}

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

// Origin of the coordinate system
template< typename T >
INLINE const PointVector< T >& PointVector< T >::Origin()
{
    static PointVector oOrigin = Zero();
    return oOrigin;
}

// explicit instantiations
template class IMEXPORT_T_INST PointVector< double >;
template class IMEXPORT_T_INST PointVector< int >;

}   // namespace Plane

namespace Space
{

// destructor
template< typename T >
INLINE PointVector< T >::~PointVector() {}

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

// Assignment operators that pass to base class
template< typename T >
INLINE PointVector< T >& PointVector< T >::operator=( const T& ac_rFill )
{
    BaseType::operator=( ac_rFill );
    return *this;
}
template< typename T >
INLINE PointVector< T >& PointVector< T >::operator=( const T (&ac_raData)[ 3 ] )
{
    BaseType::operator=( ac_raData );
    return *this;
}

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

// Origin of the coordinate system
template< typename T >
INLINE const PointVector< T >& PointVector< T >::Origin()
{
    static PointVector oOrigin = Zero();
    return oOrigin;
}

// explicit instantiations
template class IMEXPORT_T_INST PointVector< double >;
template class IMEXPORT_T_INST PointVector< int >;

}   // namespace Space

#endif  // POINT_VECTOR__INL
