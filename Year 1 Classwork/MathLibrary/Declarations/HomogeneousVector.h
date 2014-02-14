/******************************************************************************
 * File:               HomogeneousVector.h
 * Author:             Elizabeth Lowry
 * Date Created:       December 18, 2013
 * Description:        Vectors for representing homogeneous 2D/3D coordinates.
 *                      Row vectors are used so that transformations can be
 *                      applied using the =* operator.  This means that
 *                      transformed vector = original vector * transform matrix,
 *                      instead of transform matrix * original vector as it
 *                      would be if column vectors were used.
 * Last Modified:      February 10, 2014
 * Last Modification:  Templatizing PointVector.
 ******************************************************************************/

#ifndef HOMOGENEOUS_VECTOR__H
#define HOMOGENEOUS_VECTOR__H

#include "Vector.h"
#include "ImExportMacro.h"

namespace Space
{

template< typename T/* = double*/ >
class PointVector;

// Represent homogenous coordinates for a point in 3D space
class IMEXPORT_CLASS HomogeneousVector : public Math::Vector< double, 4 >
{
public:

    // simplify typing
    typedef Math::Vector< double, 4 > BaseType;
    typedef BaseType::BaseType RootType;
    typedef PointVector< double > PointType;

    // destructor
    virtual ~HomogeneousVector();

    // Constructors that forward to base class constructors
    HomogeneousVector();
    HomogeneousVector( const HomogeneousVector& ac_roVector );
    HomogeneousVector( HomogeneousVector&& a_rroVector );
    HomogeneousVector( const RootType& ac_roMatrix );
    template< typename U, unsigned int Q, bool t_bOtherIsRow >
    HomogeneousVector( const Vector< U, Q, t_bOtherIsRow >& ac_roVector,
                       double a_dFill = 0 );
    template< typename U, unsigned int P, unsigned int Q >
    HomogeneousVector( const Matrix< U, P, Q >& ac_roMatrix,
                       double a_dFill = 0 );
    HomogeneousVector( double a_dFill );
    HomogeneousVector( const double (&ac_radData)[ 4 ] );
    
    // Assignment operators that pass to base class
    template< typename U, unsigned int Q, bool t_bOtherIsRow >
    HomogeneousVector& operator=( const Vector< U, Q, t_bOtherIsRow >& ac_roVector );
    template< typename U, unsigned int P, unsigned int Q >
    HomogeneousVector& operator=( const Matrix< U, P, Q >& ac_roMatrix );
    HomogeneousVector& operator=( const double& ac_rFill );
    HomogeneousVector& operator=( const double (&ac_raData)[ 4 ] );
    
    // Construct from the given coordinates
    HomogeneousVector( double a_dX, double a_dY, double a_dZ, double a_dH = 1.0 );

    // Construct from a 3D point
    HomogeneousVector( const PointType& ac_roPoint, double a_dH = 1.0 );
    HomogeneousVector& operator=( const PointType& ac_roPoint );

    // re-implement equality and inequality checks to account for h
    bool operator==( const HomogeneousVector& ac_roVector ) const;
    bool operator!=( const HomogeneousVector& ac_roVector ) const;

    // re-implement normalization to account for h value
    double Magnitude() const;
    double MagnitudeSquared() const; // for efficiency in complex calculations
    HomogeneousVector& Normalize();
    HomogeneousVector Normal() const;

    // Adjust values so that h = 1 or 0
    HomogeneousVector& Homogenize();

    // bring base class multiplication and division operators so they won't be
    // hidden by this class's overrides
    using BaseType::operator*;
    using BaseType::operator/;
    using BaseType::operator*=;
    using BaseType::operator/=;

    // override matrix multiplication to homogenize first
    template< unsigned int P >
    typename std::conditional< P == 4, HomogeneousVector,
                                       Math::Vector< double, P > >::type
        operator*( const Math::Matrix< double, 4, P >& ac_roMatrix ) const;
    template< unsigned int P >
    typename std::conditional< P == 4, HomogeneousVector,
                                       Math::Vector< double, P > >::type
        operator/( const Math::Matrix< double, P, 4 >& ac_roMatrix ) const;
    HomogeneousVector&
        operator*=( const Math::Matrix< double, 4 >& ac_roMatrix );
    HomogeneousVector&
        operator/=( const Math::Matrix< double, 4 >& ac_roMatrix );

    // Origin of the coordinate system
    static const HomogeneousVector& Origin();

    // public access to X, Y, Z, and H coordinates
    double& x;
    double& y;
    double& z;
    double& h;

};  // HomogeneousVector
typedef HomogeneousVector HVector;

}   // namespace Space
typedef Space::HVector HVector3D;
typedef Space::HomogeneousVector HomogeneousVector3D;

namespace Plane
{
    
template< typename T/* = double*/ >
class PointVector;

// Represent homogeneous coordinates for a point in 2D space
class IMEXPORT_CLASS HomogeneousVector : public Math::Vector< double, 3 >
{
public:

    // simplify typing
    typedef Math::Vector< double, 3 > BaseType;
    typedef BaseType::BaseType RootType;
    typedef PointVector< double > PointType;

    // destructor
    virtual ~HomogeneousVector();

    // Constructors that forward to base class constructors
    HomogeneousVector();
    HomogeneousVector( const HomogeneousVector& ac_roVector );
    HomogeneousVector( HomogeneousVector&& a_rroVector );
    HomogeneousVector( const RootType& ac_roMatrix );
    template< typename U, unsigned int Q, bool t_bOtherIsRow >
    HomogeneousVector( const Vector< U, Q, t_bOtherIsRow >& ac_roVector,
                       double a_dFill = 0 );
    template< typename U, unsigned int P, unsigned int Q >
    HomogeneousVector( const Matrix< U, P, Q >& ac_roMatrix,
                       double a_dFill = 0 );
    HomogeneousVector( double a_dFill );
    HomogeneousVector( const double (&ac_radData)[ 3 ] );
    
    // Assignment operators that pass to base class
    template< typename U, unsigned int Q, bool t_bOtherIsRow >
    HomogeneousVector& operator=( const Vector< U, Q, t_bOtherIsRow >& ac_roVector );
    template< typename U, unsigned int P, unsigned int Q >
    HomogeneousVector& operator=( const Matrix< U, P, Q >& ac_roMatrix );
    HomogeneousVector& operator=( const double& ac_rFill );
    HomogeneousVector& operator=( const double (&ac_raData)[ 3 ] );
    
    // Construct from the given coordinates
    HomogeneousVector( double a_dX, double a_dY, double a_dH = 1.0 );

    // Construct from a 2D point
    HomogeneousVector( const PointType& ac_roPoint, double a_dH = 1.0 );
    HomogeneousVector& operator=( const PointType& ac_roVector );

    // Construct from a 3D homogeneous vector
    HomogeneousVector( const Space::HomogeneousVector& ac_roVector );
    HomogeneousVector& operator=( const Space::HomogeneousVector& ac_roVector );

    // re-implement equality and inequality checks to account for h
    bool operator==( const HomogeneousVector& ac_roVector ) const;
    bool operator!=( const HomogeneousVector& ac_roVector ) const;

    // re-implement normalization to account for h value
    double Magnitude() const;
    double MagnitudeSquared() const; // for efficiency in complex calculations
    HomogeneousVector& Normalize();
    HomogeneousVector Normal() const;

    // Adjust values so that h = 1 or 0
    HomogeneousVector& Homogenize();

    // bring base class multiplication and division operators so they won't be
    // hidden by this class's overrides
    using BaseType::operator*;
    using BaseType::operator/;
    using BaseType::operator*=;
    using BaseType::operator/=;

    // override matrix multiplication to homogenize first
    template< unsigned int P >
    typename std::conditional< P == 3, HomogeneousVector,
                                       Math::Vector< double, P > >::type
        operator*( const Math::Matrix< double, 3, P >& ac_roMatrix ) const;
    template< unsigned int P >
    typename std::conditional< P == 3, HomogeneousVector,
                                       Math::Vector< double, P > >::type
        operator/( const Math::Matrix< double, P, 3 >& ac_roMatrix ) const;
    HomogeneousVector&
        operator*=( const Math::Matrix< double, 3 >& ac_roMatrix );
    HomogeneousVector&
        operator/=( const Math::Matrix< double, 3 >& ac_roMatrix );

    // Origin of the coordinate system
    static const HomogeneousVector& Origin();

    // public access to X, Y, and H coordinates
    double& x;
    double& y;
    double& h;

};  // HomogeneousVector
typedef HomogeneousVector HVector;

}   // namespace Plane
typedef Plane::HVector HVector2D;
typedef Plane::HomogeneousVector HomogeneousVector2D;

#include "PointVector.h"
// Always include template function implementations with this header
#include "../Implementations/HomogeneousVector_Templates.inl"
#ifdef INLINE_IMPLEMENTATION
#include "../Implementations/HomogeneousVector.inl"
#endif

#endif  // HOMOGENEOUS_VECTOR__H
