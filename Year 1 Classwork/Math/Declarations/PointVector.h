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
 * Last Modified:      January 5, 2014
 * Last Modification:  Added import/export macro.
 ******************************************************************************/

#ifndef POINT_VECTOR__H
#define POINT_VECTOR__H

#include "ImExportMacro.h"
#include "Vector.h"
#include "Matrix.h"

namespace Plane
{

// forward declare HomogeneousVector
class HomogeneousVector;

// Represent a point in 2D space
IMEXPORT_CLASS class PointVector : public Math::Vector< double, 2 >
{
public:

    typedef Math::Vector< double, 2 > BaseType;
    typedef BaseType::BaseType VectorBaseType;
    typedef BaseType::RootType RootType;

    // inherit assignment operators
    using BaseType::operator=;

    // destructor
    virtual ~PointVector();

    // Constructors that forward to base class constructors
    PointVector();
    PointVector( const PointVector& ac_roVector );
    PointVector( const BaseType& ac_roVector );
    PointVector( const VectorBaseType& ac_roVector );
    PointVector( const RootType& ac_roMatrix );
    PointVector( PointVector&& a_rroVector );
    PointVector( BaseType&& a_rroVector );
    PointVector( VectorBaseType&& a_rroVector );
    PointVector( RootType&& a_rroMatrix );
    template< typename U, unsigned int Q, bool t_bOtherIsRow >
    PointVector( const Vector< U, Q, t_bOtherIsRow >& ac_roVector,
                 double a_dFill = 0 );
    template< unsigned int Q, bool t_bOtherIsRow >
    PointVector( Vector< double, Q, t_bOtherIsRow >&& a_rroVector,
                 double a_dFill = 0 );
    template< typename U, unsigned int Q, bool t_bOtherIsRow >
    PointVector( const VectorBase< U, Q, t_bOtherIsRow >& ac_roVector,
                 double a_dFill = 0 );
    template< unsigned int Q, bool t_bOtherIsRow >
    PointVector( VectorBase< double, Q, t_bOtherIsRow >&& a_rroVector,
                 double a_dFill = 0 );
    template< typename U, unsigned int P, unsigned int Q >
    PointVector( const MatrixBase< U, P, Q >& ac_roMatrix,
                 double a_dFill = 0 );
    template< unsigned int P, unsigned int Q >
    PointVector( MatrixBase< double, P, Q >&& a_rroMatrix,
                 double a_dFill = 0 );
    PointVector( double a_dFill );
    PointVector( const double (&ac_radData)[ 2 ] );
    PointVector( const double* const ac_cpdData,
                 const unsigned int ac_uiSize,
                 double a_dFill = 0 );

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
IMEXPORT_CLASS class PointVector : public Math::Vector< double, 3 >
{
public:

    // simplify typing
    typedef Math::Vector< double, 3 > BaseType;
    typedef BaseType::BaseType VectorBaseType;
    typedef BaseType::RootType RootType;

    // inherit assignment operators
    using BaseType::operator=;

    // destructor
    virtual ~PointVector();

    // Constructors that forward to base class constructors
    PointVector();
    PointVector( const PointVector& ac_roVector );
    PointVector( const BaseType& ac_roVector );
    PointVector( const VectorBaseType& ac_roVector );
    PointVector( const RootType& ac_roMatrix );
    PointVector( PointVector&& a_rroVector );
    PointVector( BaseType&& a_rroVector );
    PointVector( VectorBaseType&& a_rroVector );
    PointVector( RootType&& a_rroMatrix );
    template< typename U, unsigned int Q, bool t_bOtherIsRow >
    PointVector( const Vector< U, Q, t_bOtherIsRow >& ac_roVector,
                 double a_dFill = 0 );
    template< unsigned int Q, bool t_bOtherIsRow >
    PointVector( Vector< double, Q, t_bOtherIsRow >&& a_rroVector,
                 double a_dFill = 0 );
    template< typename U, unsigned int Q, bool t_bOtherIsRow >
    PointVector( const VectorBase< U, Q, t_bOtherIsRow >& ac_roVector,
                 double a_dFill = 0 );
    template< unsigned int Q, bool t_bOtherIsRow >
    PointVector( VectorBase< double, Q, t_bOtherIsRow >&& a_rroVector,
                 double a_dFill = 0 );
    template< typename U, unsigned int P, unsigned int Q >
    PointVector( const MatrixBase< U, P, Q >& ac_roMatrix,
                 double a_dFill = 0 );
    template< unsigned int P, unsigned int Q >
    PointVector( MatrixBase< double, P, Q >&& a_rroMatrix,
                 double a_dFill = 0 );
    PointVector( double a_dFill );
    PointVector( const double (&ac_radData)[ 3 ] );
    PointVector( const double* const ac_cpdData,
                 const unsigned int ac_uiSize,
                 double a_dFill = 0 );

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

// Always include template function implementations with this header
#include "Implementations/PointVector_Templates.inl"

#endif // POINT_VECTOR__H