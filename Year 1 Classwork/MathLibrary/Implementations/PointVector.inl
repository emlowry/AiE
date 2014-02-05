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
#include "Declarations/ImExportMacro.h"

namespace Plane
{

// destructor
INLINE PointVector::~PointVector() {}

// Constructors that forward to base class constructors
INLINE PointVector::PointVector()
    : BaseType(), x( m_aaData[0][0] ), y( m_aaData[0][1] ) {}
INLINE PointVector::PointVector( const PointVector& ac_roVector )
    : BaseType( ac_roVector ), x( m_aaData[0][0] ), y( m_aaData[0][1] ) {}
INLINE PointVector::PointVector( PointVector&& a_rroVector )
    : BaseType( std::forward< PointVector >( a_rroVector ) ),
      x( m_aaData[0][0] ), y( m_aaData[0][1] ) {}
INLINE PointVector::PointVector( const RootType& ac_roMatrix )
    : BaseType( ac_roMatrix ), x( m_aaData[0][0] ), y( m_aaData[0][1] ) {}
INLINE PointVector::PointVector( double a_dFill )
    : BaseType( a_dFill ), x( m_aaData[0][0] ), y( m_aaData[0][1] ) {}
INLINE PointVector::PointVector( const double (&ac_radData)[ 2 ] )
    : BaseType( ac_radData ), x( m_aaData[0][0] ), y( m_aaData[0][1] ) {}

// Assignment operators that pass to base class
INLINE PointVector& PointVector::operator=( const double& ac_rFill )
{
    BaseType::operator=( ac_rFill );
    return *this;
}
INLINE PointVector& PointVector::operator=( const double (&ac_raData)[ 2 ] )
{
    BaseType::operator=( ac_raData );
    return *this;
}

// Construct from the given coordinates
INLINE PointVector::PointVector( double a_dX, double a_dY )
    : BaseType(), x( m_aaData[0][0] ), y( m_aaData[0][1] )
{
    x = a_dX;
    y = a_dY;
}

// Construct from homogenous vector
INLINE PointVector::PointVector( const HomogeneousVector& ac_roVector )
    : BaseType(), x( m_aaData[0][0] ), y( m_aaData[0][1] )
{
    operator=( ac_roVector );
}
INLINE PointVector& PointVector::operator=( const HomogeneousVector& ac_roVector )
{
    x = ac_roVector.x / ( ac_roVector.h == 0.0 ? 1.0 : ac_roVector.h );
    y = ac_roVector.y / ( ac_roVector.h == 0.0 ? 1.0 : ac_roVector.h );
    return *this;
}

// Origin of the coordinate system
INLINE const PointVector& PointVector::Origin()
{
    static PointVector oOrigin( 0.0, 0.0 );
    return oOrigin;
}

}   // namespace Plane

namespace Space
{

// destructor
INLINE PointVector::~PointVector() {}

// Constructors that forward to base class constructors
INLINE PointVector::PointVector()
    : BaseType(),
      x( m_aaData[0][0] ), y( m_aaData[0][1] ), z( m_aaData[0][2] ) {}
INLINE PointVector::PointVector( const PointVector& ac_roVector )
    : BaseType( ac_roVector ),
      x( m_aaData[0][0] ), y( m_aaData[0][1] ), z( m_aaData[0][2] ) {}
INLINE PointVector::PointVector( PointVector&& a_rroVector )
    : BaseType( std::forward< PointVector >( a_rroVector ) ),
      x( m_aaData[0][0] ), y( m_aaData[0][1] ), z( m_aaData[0][2] ) {}
INLINE PointVector::PointVector( const RootType& ac_roMatrix )
    : BaseType( ac_roMatrix ),
      x( m_aaData[0][0] ), y( m_aaData[0][1] ), z( m_aaData[0][2] ) {}
INLINE PointVector::PointVector( double a_dFill )
    : BaseType( a_dFill ),
      x( m_aaData[0][0] ), y( m_aaData[0][1] ), z( m_aaData[0][2] ) {}
INLINE PointVector::PointVector( const double (&ac_radData)[ 3 ] )
    : BaseType( ac_radData ),
      x( m_aaData[0][0] ), y( m_aaData[0][1] ), z( m_aaData[0][2] ) {}

// Assignment operators that pass to base class
INLINE PointVector& PointVector::operator=( const double& ac_rFill )
{
    BaseType::operator=( ac_rFill );
    return *this;
}
INLINE PointVector& PointVector::operator=( const double (&ac_raData)[ 3 ] )
{
    BaseType::operator=( ac_raData );
    return *this;
}

// Construct from the given coordinates
INLINE PointVector::PointVector( double a_dX, double a_dY, double a_dZ )
    : BaseType(), x( m_aaData[0][0] ), y( m_aaData[0][1] ), z( m_aaData[0][2] )
{
    x = a_dX;
    y = a_dY;
    z = a_dZ;
}

// Construct from homogenous vector
INLINE PointVector::PointVector( const HomogeneousVector& ac_roVector )
    : BaseType(), x( m_aaData[0][0] ), y( m_aaData[0][1] ), z( m_aaData[0][2] )
{
    operator=( ac_roVector );
}
INLINE PointVector& PointVector::operator=( const HomogeneousVector& ac_roVector )
{
    x = ac_roVector.x / ( ac_roVector.h == 0.0 ? 1.0 : ac_roVector.h );
    y = ac_roVector.y / ( ac_roVector.h == 0.0 ? 1.0 : ac_roVector.h );
    z = ac_roVector.z / ( ac_roVector.h == 0.0 ? 1.0 : ac_roVector.h );
    return *this;
}

// Origin of the coordinate system
INLINE const PointVector& PointVector::Origin()
{
    static PointVector oOrigin( 0.0, 0.0, 0.0 );
    return oOrigin;
}

}   // namespace Space

#endif  // POINT_VECTOR__INL
