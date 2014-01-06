/******************************************************************************
 * File:               HomogeneousVector_Plane.inl
 * Author:             Elizabeth Lowry
 * Date Created:       December 18, 2013
 * Description:        Inline function implementations for 2D HomogeneousVector.
 * Last Modified:      January 5, 2014
 * Last Modification:  Moving template function implementations to another file.
 ******************************************************************************/

#ifndef HOMOGENEOUS_VECTOR__PLANE__INL
#define HOMOGENEOUS_VECTOR__PLANE__INL

#include "Declarations/HomogeneousVector.h"
#include "Declarations/PointVector.h"
#include <stdexcept>    // for std::invalid_argument

namespace Plane
{

// destructor
inline HomogeneousVector::~HomogeneousVector() {}

// Constructors that forward to base class constructors
inline HomogeneousVector::HomogeneousVector()
    : BaseType(), x( At(0) ), y( At(1) ), h( At(2) )
{
    h = 1.0;
}
inline HomogeneousVector::
    HomogeneousVector( const HomogeneousVector& ac_roVector )
    : BaseType( ac_roVector ), x( At(0) ), y( At(1) ), h( At(2) ) {}
inline HomogeneousVector::HomogeneousVector( const BaseType& ac_roVector )
    : BaseType( ac_roVector ), x( At(0) ), y( At(1) ), h( At(2) ) {}
inline HomogeneousVector::
    HomogeneousVector( const VectorBaseType& ac_roVector )
    : BaseType( ac_roVector ), x( At(0) ), y( At(1) ), h( At(2) ) {}
inline HomogeneousVector::HomogeneousVector( const RootType& ac_roMatrix )
    : BaseType( ac_roMatrix ), x( At(0) ), y( At(1) ), h( At(2) ) {}
inline HomogeneousVector::HomogeneousVector( HomogeneousVector&& a_rroVector )
    : BaseType( std::forward< HomogeneousVector >( a_rroVector ) ),
      x( At(0) ), y( At(1) ), h( At(2) ) {}
inline HomogeneousVector::HomogeneousVector( BaseType&& a_rroVector )
    : BaseType( std::forward< BaseType >( a_rroVector ) ),
      x( At(0) ), y( At(1) ), h( At(2) ) {}
inline HomogeneousVector::HomogeneousVector( VectorBaseType&& a_rroVector )
    : BaseType( std::forward< VectorBaseType >( a_rroVector ) ),
      x( At(0) ), y( At(1) ), h( At(2) ) {}
inline HomogeneousVector::HomogeneousVector( RootType&& a_rroMatrix )
    : BaseType( std::forward< RootType >( a_rroMatrix ) ),
      x( At(0) ), y( At(1) ), h( At(2) ) {}
inline HomogeneousVector::HomogeneousVector( double a_dFill )
    : BaseType( a_dFill ), x( At(0) ), y( At(1) ), h( At(2) ) {}
inline HomogeneousVector::HomogeneousVector( const double (&ac_radData)[ 3 ] )
    : BaseType( ac_radData ), x( At(0) ), y( At(1) ), h( At(2) ) {}
inline HomogeneousVector::HomogeneousVector( const double* const ac_cpdData,
                                             const unsigned int ac_uiSize,
                                             double a_dFill )
    : BaseType( ac_cpdData, ac_uiSize, a_dFill ),
      x( At(0) ), y( At(1) ), h( At(2) ) {}

// Construct from the given coordinates
inline HomogeneousVector::
    HomogeneousVector( double a_dX, double a_dY, double a_dH )
    : x( At(0) ), y( At(1) ), h( At(2) )
{
    x = a_dX;
    y = a_dY;
    h = a_dH;
}

// Construct from a 2D point
inline HomogeneousVector::
    HomogeneousVector( const PointVector& ac_roPoint, double a_dH )
    : BaseType( ac_roPoint ), x( At(0) ), y( At(1) ), h( At(2) )
{
    h = a_dH;
    operator=( ac_roPoint );
}
inline HomogeneousVector& HomogeneousVector::operator=( const PointVector& ac_roPoint )
{
    x = ac_roPoint.x * h;
    y = ac_roPoint.y * h;
}

// re-implement addition and subtraction to account for h value
// this will hide all parent class addition and subtraction operators.
inline HomogeneousVector
    HomogeneousVector::operator+( const HomogeneousVector& ac_roVector ) const
{
    HomogeneousVector oArgument = ac_roVector;
    oArgument *= ( ac_roVector.h == 0.0 ? 1.0 : h / ac_roVector.h );
    oArgument.h = 0.0;
    return HomogeneousVector( BaseType::operator+( oArgument ) );
}
inline HomogeneousVector&
    HomogeneousVector::operator+=( const HomogeneousVector& ac_roVector )
{
    HomogeneousVector oArgument = ac_roVector;
    oArgument *= ( ac_roVector.h == 0.0 ? 1.0 : h / ac_roVector.h );
    oArgument.h = 0.0;
    BaseType::operator+=( oArgument );
    return *this;
}
inline HomogeneousVector
    HomogeneousVector::operator-( const HomogeneousVector& ac_roVector ) const
{
    HomogeneousVector oArgument = ac_roVector;
    oArgument *= ( ac_roVector.h == 0.0 ? 1.0 : h / ac_roVector.h );
    oArgument.h = 0.0;
    return HomogeneousVector( BaseType::operator-( oArgument ) );
}
inline HomogeneousVector&
    HomogeneousVector::operator-=( const HomogeneousVector& ac_roVector )
{
    HomogeneousVector oArgument = ac_roVector;
    oArgument *= ( ac_roVector.h == 0.0 ? 1.0 : h / ac_roVector.h );
    oArgument.h = 0.0;
    BaseType::operator-=( oArgument );
    return *this;
}

// Matrix multiplication and division
inline HomogeneousVector& HomogeneousVector::
    operator*=( const Math::Matrix< double, 3 >& ac_roMatrix )
{
    Homogenize();
    BaseType::operator*=( ac_roMatrix );
    return *this;
}
inline HomogeneousVector& HomogeneousVector::
    operator/=( const Math::Matrix< double, 3 >& ac_roMatrix )
{
    if( !ac_roMatrix.IsInvertable() )
    {
        throw std::invalid_argument( "Cannot divide by a non-invertable matrix" );
    }
    Homogenize();
    BaseType::operator/=( ac_roMatrix );
    return *this;
}

// re-implement equality and inequality checks to account for h
inline bool HomogeneousVector::operator==( const HomogeneousVector& ac_roVector ) const
{
    return ( PointVector( *this ) == PointVector( ac_roVector ) );
}
inline bool HomogeneousVector::operator!=( const HomogeneousVector& ac_roVector ) const
{
    return ( PointVector( *this ) != PointVector( ac_roVector ) );
}

// re-implement normalization to account for h value
inline double HomogeneousVector::Magnitude() const
{
    return PointVector( *this ).Magnitude();
}
inline double HomogeneousVector::MagnitudeSquared() const
{
    return PointVector( *this ).Magnitude();
}
inline void HomogeneousVector::Normalize()
{
    Homogenize();
    BaseType::Normalize();
}
inline HomogeneousVector HomogeneousVector::Normal() const
{
    return HomogeneousVector( PointVector( *this ).Normal() );
}

// Adjust values so that h = 1 or 0
inline HomogeneousVector& HomogeneousVector::Homogenize()
{
    if( h != 0.0 )
    {
        operator/=( h );
    }
    return *this;
}

// Origin of the coordinate system
inline const HomogeneousVector& HomogeneousVector::Origin()
{
    static HomogeneousVector oOrigin( 0.0, 0.0, 1.0 );
    return oOrigin;
}

}   // namespace Plane

#endif  // HOMOGENEOUS_VECTOR__PLANE__INL
