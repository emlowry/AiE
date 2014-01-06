/******************************************************************************
 * File:               PointVector.inl
 * Author:             Elizabeth Lowry
 * Date Created:       December 17, 2013
 * Description:        Inline function implementations for PointVector.
 * Last Modified:      January 5, 2014
 * Last Modification:  Moved templated constructors to another file.
 ******************************************************************************/

#ifndef POINT_VECTOR__INL
#define POINT_VECTOR__INL

#include "Declarations/PointVector.h"
#include "Declarations/HomogeneousVector.h"

// separate file to reduce file size
#include "PointVector_Templates.inl"

namespace Plane
{

// destructor
inline PointVector::~PointVector() {}

// Constructors that forward to base class constructors
inline PointVector::PointVector() : BaseType(), x( At(0) ), y( At(1) ) {}
inline PointVector::PointVector( const PointVector& ac_roVector )
    : BaseType( ac_roVector ), x( At(0) ), y( At(1) ) {}
inline PointVector::PointVector( const BaseType& ac_roVector )
    : BaseType( ac_roVector ), x( At(0) ), y( At(1) ) {}
inline PointVector::PointVector( const VectorBaseType& ac_roVector )
    : BaseType( ac_roVector ), x( At(0) ), y( At(1) ) {}
inline PointVector::PointVector( const RootType& ac_roMatrix )
    : BaseType( ac_roMatrix ), x( At(0) ), y( At(1) ) {}
inline PointVector::PointVector( PointVector&& a_rroVector )
    : BaseType( std::forward< PointVector >( a_rroVector ) ),
      x( At(0) ), y( At(1) ) {}
inline PointVector::PointVector( BaseType&& a_rroVector )
    : BaseType( std::forward< BaseType >( a_rroVector ) ),
      x( At(0) ), y( At(1) ) {}
inline PointVector::PointVector( VectorBaseType&& a_rroVector )
    : BaseType( std::forward< VectorBaseType >( a_rroVector ) ),
      x( At(0) ), y( At(1) ) {}
inline PointVector::PointVector( RootType&& a_rroMatrix )
    : BaseType( std::forward< RootType >( a_rroMatrix ) ),
      x( At(0) ), y( At(1) ) {}
inline PointVector::PointVector( double a_dFill )
    : BaseType( a_dFill ), x( At(0) ), y( At(1) ) {}
inline PointVector::PointVector( const double (&ac_radData)[ 2 ] )
    : BaseType( ac_radData ), x( At(0) ), y( At(1) ) {}
inline PointVector::PointVector( const double* const ac_cpdData,
                                 const unsigned int ac_uiSize,
                                 double a_dFill )
    : BaseType( ac_cpdData, ac_uiSize, a_dFill ), x( At(0) ), y( At(1) ) {}

// Construct from the given coordinates
inline PointVector::PointVector( double a_dX, double a_dY )
    : x( At(0) ), y( At(1) )
{
    x = a_dX;
    y = a_dY;
}

// Construct from homogenous vector
inline PointVector::PointVector( const HomogeneousVector& ac_roVector )
    : x( At(0) ), y( At(1) )
{
    operator=( ac_roVector );
}
inline PointVector& PointVector::operator=( const HomogeneousVector& ac_roVector )
{
    x = ac_roVector.x / ( ac_roVector.h == 0.0 ? 1.0 : ac_roVector.h );
    y = ac_roVector.y / ( ac_roVector.h == 0.0 ? 1.0 : ac_roVector.h );
    return *this;
}

// Origin of the coordinate system
inline const PointVector& PointVector::Origin()
{
    static PointVector oOrigin( 0.0, 0.0 );
    return oOrigin;
}

}   // namespace Plane

namespace Space
{

// destructor
inline PointVector::~PointVector() {}

// Constructors that forward to base class constructors
inline PointVector::PointVector()
    : BaseType(), x( At(0) ), y( At(1) ), z( At(2) ) {}
inline PointVector::PointVector( const PointVector& ac_roVector )
    : BaseType( ac_roVector ), x( At(0) ), y( At(1) ), z( At(2) ) {}
inline PointVector::PointVector( const BaseType& ac_roVector )
    : BaseType( ac_roVector ), x( At(0) ), y( At(1) ), z( At(2) ) {}
inline PointVector::PointVector( const VectorBaseType& ac_roVector )
    : BaseType( ac_roVector ), x( At(0) ), y( At(1) ), z( At(2) ) {}
inline PointVector::PointVector( const RootType& ac_roMatrix )
    : BaseType( ac_roMatrix ), x( At(0) ), y( At(1) ), z( At(2) ) {}
inline PointVector::PointVector( PointVector&& a_rroVector )
    : BaseType( std::forward< PointVector >( a_rroVector ) ),
      x( At(0) ), y( At(1) ), z( At(2) ) {}
inline PointVector::PointVector( BaseType&& a_rroVector )
    : BaseType( std::forward< BaseType >( a_rroVector ) ),
      x( At(0) ), y( At(1) ), z( At(2) ) {}
inline PointVector::PointVector( VectorBaseType&& a_rroVector )
    : BaseType( std::forward< VectorBaseType >( a_rroVector ) ),
      x( At(0) ), y( At(1) ), z( At(2) ) {}
inline PointVector::PointVector( RootType&& a_rroMatrix )
    : BaseType( std::forward< RootType >( a_rroMatrix ) ),
      x( At(0) ), y( At(1) ), z( At(2) ) {}
inline PointVector::PointVector( double a_dFill )
    : BaseType( a_dFill ), x( At(0) ), y( At(1) ), z( At(2) ) {}
inline PointVector::PointVector( const double (&ac_radData)[ 3 ] )
    : BaseType( ac_radData ), x( At(0) ), y( At(1) ), z( At(2) ) {}
inline PointVector::PointVector( const double* const ac_cpdData,
                                 const unsigned int ac_uiSize,
                                 double a_dFill )
    : BaseType( ac_cpdData, ac_uiSize, a_dFill ),
      x( At(0) ), y( At(1) ), z( At(2) ) {}

// Construct from the given coordinates
inline PointVector::PointVector( double a_dX, double a_dY, double a_dZ )
    : x( At(0) ), y( At(1) ), z( At(2) )
{
    x = a_dX;
    y = a_dY;
    z = a_dZ;
}

// Construct from homogenous vector
inline PointVector::PointVector( const HomogeneousVector& ac_roVector )
    : x( At(0) ), y( At(1) ), z( At(2) )
{
    operator=( ac_roVector );
}
inline PointVector& PointVector::operator=( const HomogeneousVector& ac_roVector )
{
    x = ac_roVector.x / ( ac_roVector.h == 0.0 ? 1.0 : ac_roVector.h );
    y = ac_roVector.y / ( ac_roVector.h == 0.0 ? 1.0 : ac_roVector.h );
    z = ac_roVector.z / ( ac_roVector.h == 0.0 ? 1.0 : ac_roVector.h );
    return *this;
}

// Origin of the coordinate system
inline const PointVector& PointVector::Origin()
{
    static PointVector oOrigin( 0.0, 0.0, 0.0 );
    return oOrigin;
}

}   // namespace Space

#endif  // POINT_VECTOR__INL
