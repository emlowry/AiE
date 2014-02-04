/******************************************************************************
 * File:               HomogeneousVector.inl
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        Inline function implementations for HomogeneousVector.
 * Last Modified:      January 5, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

#ifndef HOMOGENEOUS_VECTOR__INL
#define HOMOGENEOUS_VECTOR__INL

#include "Declarations/HomogeneousVector.h"
#include "Declarations/PointVector.h"

namespace Plane
{

// destructor
inline HomogeneousVector::~HomogeneousVector() {}

// Constructors that forward to base class constructors
inline HomogeneousVector::HomogeneousVector()
    : BaseType(),
      x( m_aaData[0][0] ), y( m_aaData[0][1] ), h( m_aaData[0][2] )
{
    h = 1.0;
}
inline HomogeneousVector::
    HomogeneousVector( const HomogeneousVector& ac_roVector )
    : BaseType( ac_roVector ),
      x( m_aaData[0][0] ), y( m_aaData[0][1] ), h( m_aaData[0][2] ) {}
inline HomogeneousVector::HomogeneousVector( HomogeneousVector&& a_rroVector )
    : BaseType( std::forward< HomogeneousVector >( a_rroVector ) ),
      x( m_aaData[0][0] ), y( m_aaData[0][1] ), h( m_aaData[0][2] ) {}
inline HomogeneousVector::
    HomogeneousVector( const RootType& ac_roMatrix )
    : BaseType( ac_roMatrix ),
      x( m_aaData[0][0] ), y( m_aaData[0][1] ), h( m_aaData[0][2] ) {}
inline HomogeneousVector::HomogeneousVector( double a_dFill )
    : BaseType( a_dFill ),
      x( m_aaData[0][0] ), y( m_aaData[0][1] ), h( m_aaData[0][2] ) {}
inline HomogeneousVector::HomogeneousVector( const double (&ac_radData)[ 3 ] )
    : BaseType( ac_radData ),
      x( m_aaData[0][0] ), y( m_aaData[0][1] ), h( m_aaData[0][2] ) {}

// Assignment operators that pass to base class
inline HomogeneousVector& HomogeneousVector::operator=( const double& ac_rFill )
{
    BaseType::operator=( ac_rFill );
    return *this;
}
inline HomogeneousVector& HomogeneousVector::operator=( const double (&ac_raData)[ 3 ] )
{
    BaseType::operator=( ac_raData );
    return *this;
}

// Construct from the given coordinates
inline HomogeneousVector::
    HomogeneousVector( double a_dX, double a_dY, double a_dH )
    : BaseType(),
      x( m_aaData[0][0] ), y( m_aaData[0][1] ), h( m_aaData[0][2] )
{
    x = a_dX;
    y = a_dY;
    h = a_dH;
}

// Construct from a 2D point
inline HomogeneousVector::
    HomogeneousVector( const PointVector& ac_roPoint, double a_dH )
    : BaseType( ac_roPoint ),
      x( m_aaData[0][0] ), y( m_aaData[0][1] ), h( m_aaData[0][2] )
{
    h = a_dH;
}
inline HomogeneousVector&
    HomogeneousVector::operator=( const PointVector& ac_roPoint )
{
    x = ac_roPoint.x * h;
    y = ac_roPoint.y * h;
    return *this;
}

// Construct from a 3D homogeneous vector
inline HomogeneousVector::
    HomogeneousVector( const Space::HomogeneousVector& ac_roVector )
    : BaseType( Space::PointVector( ac_roVector ) ),
      x( m_aaData[0][0] ), y( m_aaData[0][1] ), h( m_aaData[0][2] ) {}
inline HomogeneousVector&
    HomogeneousVector::operator=( const Space::HomogeneousVector& ac_roVector )
{
    operator=( Space::PointVector( ac_roVector ) );
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
inline HomogeneousVector& HomogeneousVector::Normalize()
{
    operator=( this->Normal() );
    return *this;
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

// override matrix multiplication to homogenize first
inline HomogeneousVector& HomogeneousVector::
    operator*=( const Math::Matrix< double, 3 >& ac_roMatrix )
{
    Homogenize();
    BaseType::operator*=( ac_roMatrix );
    return Homogenize();
}
inline HomogeneousVector& HomogeneousVector::
    operator/=( const Math::Matrix< double, 3 >& ac_roMatrix )
{
    Homogenize();
    BaseType::operator/=( ac_roMatrix );
    return Homogenize();
}

// Origin of the coordinate system
inline const HomogeneousVector& HomogeneousVector::Origin()
{
    static HomogeneousVector oOrigin( 0.0, 0.0, 1.0 );
    return oOrigin;
}

}   // namespace Plane

namespace Space
{

// destructor
inline HomogeneousVector::~HomogeneousVector() {}

// Constructors that forward to base class constructors
inline HomogeneousVector::HomogeneousVector()
    : BaseType(),
      x( m_aaData[0][0] ),
      y( m_aaData[0][1] ),
      z( m_aaData[0][2] ),
      h( m_aaData[0][3] )
{
    h = 1.0;
}
inline HomogeneousVector::
    HomogeneousVector( const HomogeneousVector& ac_roVector )
    : BaseType( ac_roVector ),
      x( m_aaData[0][0] ),
      y( m_aaData[0][1] ),
      z( m_aaData[0][2] ),
      h( m_aaData[0][3] ) {}
inline HomogeneousVector::HomogeneousVector( HomogeneousVector&& a_rroVector )
    : BaseType( std::forward< HomogeneousVector >( a_rroVector ) ),
      x( m_aaData[0][0] ),
      y( m_aaData[0][1] ),
      z( m_aaData[0][2] ),
      h( m_aaData[0][3] ) {}
inline HomogeneousVector::
    HomogeneousVector( const RootType& ac_roMatrix )
    : BaseType( ac_roMatrix ),
      x( m_aaData[0][0] ),
      y( m_aaData[0][1] ),
      z( m_aaData[0][2] ),
      h( m_aaData[0][3] ) {}
inline HomogeneousVector::HomogeneousVector( double a_dFill )
    : BaseType( a_dFill ),
      x( m_aaData[0][0] ),
      y( m_aaData[0][1] ),
      z( m_aaData[0][2] ),
      h( m_aaData[0][3] ) {}
inline HomogeneousVector::HomogeneousVector( const double (&ac_radData)[ 4 ] )
    : BaseType( ac_radData ),
      x( m_aaData[0][0] ),
      y( m_aaData[0][1] ),
      z( m_aaData[0][2] ),
      h( m_aaData[0][3] ) {}

// Assignment operators that pass to base class
inline HomogeneousVector& HomogeneousVector::operator=( const double& ac_rFill )
{
    BaseType::operator=( ac_rFill );
    return *this;
}
inline HomogeneousVector& HomogeneousVector::operator=( const double (&ac_raData)[ 4 ] )
{
    BaseType::operator=( ac_raData );
    return *this;
}

// Construct from the given coordinates
inline HomogeneousVector::
    HomogeneousVector( double a_dX, double a_dY, double a_dZ, double a_dH )
    : BaseType(),
      x( m_aaData[0][0] ),
      y( m_aaData[0][1] ),
      z( m_aaData[0][2] ),
      h( m_aaData[0][3] )
{
    x = a_dX;
    y = a_dY;
    z = a_dZ;
    h = a_dH;
}

// Construct from a 3D point
inline HomogeneousVector::
    HomogeneousVector( const PointVector& ac_roPoint, double a_dH )
    : BaseType( ac_roPoint ),
      x( m_aaData[0][0] ),
      y( m_aaData[0][1] ),
      z( m_aaData[0][2] ),
      h( m_aaData[0][3] )
{
    h = a_dH;
    operator=( ac_roPoint );
}
inline HomogeneousVector& HomogeneousVector::operator=( const PointVector& ac_roPoint )
{
    x = ac_roPoint.x * h;
    y = ac_roPoint.y * h;
    z = ac_roPoint.z * h;
    return *this;
}

// re-implement equality and inequality checks to account for h
inline bool HomogeneousVector::
    operator==( const HomogeneousVector& ac_roVector ) const
{
    return ( PointVector( *this ) == PointVector( ac_roVector ) );
}
inline bool HomogeneousVector::
    operator!=( const HomogeneousVector& ac_roVector ) const
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
inline HomogeneousVector& HomogeneousVector::Normalize()
{
    operator=( this->Normal() );
    return *this;
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

// override matrix multiplication to homogenize first
inline HomogeneousVector& HomogeneousVector::
    operator*=( const Math::Matrix< double, 4 >& ac_roMatrix )
{
    Homogenize();
    BaseType::operator*=( ac_roMatrix );
    return Homogenize();
}
inline HomogeneousVector& HomogeneousVector::
    operator/=( const Math::Matrix< double, 4 >& ac_roMatrix )
{
    Homogenize();
    BaseType::operator/=( ac_roMatrix );
    return Homogenize();
}

// Origin of the coordinate system
inline const HomogeneousVector& HomogeneousVector::Origin()
{
    static HomogeneousVector oOrigin( 0.0, 0.0, 0.0, 1.0 );
    return oOrigin;
}

}   // namespace Space

#endif  // HOMOGENEOUS_VECTOR__INL
