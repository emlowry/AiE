/******************************************************************************
 * File:               PointVector.h
 * Author:             Elizabeth Lowry
 * Date Created:       December 17, 2013
 * Description:        Vectors for representing points in 2D or 3D space.
 *                      Row vectors are used so that transformations can be
 *                      applied using the =* operator.  This means that
 *                      transformed point = original point * transform matrix,
 *                      instead of transform matrix * original point as it
 *                      would be if column vectors were used.
 * Last Modified:      February 5, 2014
 * Last Modification:  Refactoring.
 ******************************************************************************/

#ifndef POINT_VECTOR__H
#define POINT_VECTOR__H

#include "Vector.h"
#include "Matrix.h"
#include "ImExportMacro.h"

namespace Plane
{

// forward declare HomogeneousVector
class HomogeneousVector;

// Represent a point in 2D space
class IMEXPORT_CLASS PointVector : public Math::Vector< double, 2 >
{
public:

    typedef Math::Vector< double, 2 > BaseType;
    typedef BaseType::BaseType RootType;

    // destructor
    virtual ~PointVector();

    // Constructors that forward to base class constructors
    PointVector();
    PointVector( const PointVector& ac_roVector );
    PointVector( PointVector&& a_rroVector );
    PointVector( const RootType& ac_roMatrix );
    template< typename U, unsigned int Q, bool t_bOtherIsRow >
    PointVector( const Vector< U, Q, t_bOtherIsRow >& ac_roVector,
                 double a_dFill = 0 );
    template< typename U, unsigned int P, unsigned int Q >
    PointVector( const Matrix< U, P, Q >& ac_roMatrix,
                 double a_dFill = 0 );
    PointVector( double a_dFill );
    PointVector( const double (&ac_radData)[ 2 ] );
    
    // Assignment operators that pass to base class
    template< typename U, unsigned int Q, bool t_bOtherIsRow >
    PointVector& operator=( const Vector< U, Q, t_bOtherIsRow >& ac_roVector );
    template< typename U, unsigned int P, unsigned int Q >
    PointVector& operator=( const Matrix< U, P, Q >& ac_roMatrix );
    PointVector& operator=( const double& ac_rFill );
    PointVector& operator=( const double (&ac_raData)[ 2 ] );
    
    // Construct from the given coordinates
    PointVector( double a_dX, double a_dY );

    // Construct from homogenous vector
    PointVector( const HomogeneousVector& ac_roVector );
    PointVector& operator=( const HomogeneousVector& ac_roVector );

    // Origin of the coordinate system
    static const PointVector& Origin();

    // public access to X and Y coordinates
    double& x;
    double& y;

};   // Plane::PointVector
typedef PointVector Point;

}   // namespace Plane
typedef Plane::PointVector PointVector2D;
typedef Plane::Point Point2D;

namespace Space
{

// forward declare HomogeneousVector
class HomogeneousVector;

// Represent a point in 3D space
class IMEXPORT_CLASS PointVector : public Math::Vector< double, 3 >
{
public:

    // simplify typing
    typedef Math::Vector< double, 3 > BaseType;
    typedef BaseType::BaseType RootType;

    // destructor
    virtual ~PointVector();

    // Constructors that forward to base class constructors
    PointVector();
    PointVector( const PointVector& ac_roVector );
    PointVector( PointVector&& a_rroVector );
    PointVector( const RootType& ac_roMatrix );
    template< typename U, unsigned int Q, bool t_bOtherIsRow >
    PointVector( const Vector< U, Q, t_bOtherIsRow >& ac_roVector,
                 double a_dFill = 0 );
    template< typename U, unsigned int P, unsigned int Q >
    PointVector( const Matrix< U, P, Q >& ac_roMatrix,
                 double a_dFill = 0 );
    PointVector( double a_dFill );
    PointVector( const double (&ac_radData)[ 3 ] );
    
    // Assignment operators that pass to base class
    template< typename U, unsigned int Q, bool t_bOtherIsRow >
    PointVector& operator=( const Vector< U, Q, t_bOtherIsRow >& ac_roVector );
    template< typename U, unsigned int P, unsigned int Q >
    PointVector& operator=( const Matrix< U, P, Q >& ac_roMatrix );
    PointVector& operator=( const double& ac_rFill );
    PointVector& operator=( const double (&ac_raData)[ 3 ] );
    
    // Construct from the given coordinates
    PointVector( double a_dX, double a_dY, double a_dZ );

    // Construct from HomogeneousVector
    PointVector( const HomogeneousVector& ac_roVector );
    PointVector& operator=( const HomogeneousVector& ac_roVector );

    // Origin of the coordinate system
    static const PointVector& Origin();

    // public access to X, Y, and Z coordinates
    double& x;
    double& y;
    double& z;

};   // Space::PointVector
typedef PointVector Point;

}   // namespace Space
typedef Space::PointVector PointVector3D;
typedef Space::Point Point3D;

#include "Declarations/HomogeneousVector.h"
// Always include template function implementations with this header
#include "Implementations/PointVector_Templates.inl"
#ifdef INLINE_IMPLEMENTATION
#include "Implementations/PointVector.inl"
#endif

#endif // POINT_VECTOR__H