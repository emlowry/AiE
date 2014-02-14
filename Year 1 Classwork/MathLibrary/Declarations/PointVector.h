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
 * Last Modified:      February 12, 2014
 * Last Modification:  Refactoring.
 ******************************************************************************/

#ifndef POINT_VECTOR__H
#define POINT_VECTOR__H

#include "Functions.h"
#include "Vector.h"
#include "Matrix.h"

namespace Plane
{

using namespace Math;

// forward declare HomogeneousVector
class HomogeneousVector;

// Represent a point in 2D space
template< typename T >
class PointVector : public Vector< T, 2 >
{
public:

    typedef Vector< T, 2 > BaseType;
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
                 const T& ac_rFill = DefaultValue< T >() );
    template< typename U, unsigned int P, unsigned int Q >
    PointVector( const Matrix< U, P, Q >& ac_roMatrix,
                 const T& ac_rFill = DefaultValue< T >() );
    PointVector( const T& a_dFill );
    PointVector( const T (&ac_radData)[ 2 ] );
    
    // Assignment operators that pass to base class
    template< typename U, unsigned int Q, bool t_bOtherIsRow >
    PointVector& operator=( const Vector< U, Q, t_bOtherIsRow >& ac_roVector );
    template< typename U, unsigned int P, unsigned int Q >
    PointVector& operator=( const Matrix< U, P, Q >& ac_roMatrix );
    PointVector& operator=( const T& ac_rFill );
    PointVector& operator=( const T (&ac_raData)[ 2 ] );
    
    // Construct from the given coordinates
    PointVector( const T& a_dX, const T& a_dY );

    // Construct from homogenous vector
    PointVector( const HomogeneousVector& ac_roVector );
    PointVector& operator=( const HomogeneousVector& ac_roVector );

    // Origin of the coordinate system
    static const PointVector& Origin();

    // public access to X and Y coordinates
    T& x;
    T& y;

};   // Plane::PointVector
typedef PointVector< double > Point;
typedef PointVector< int > IntPoint;

}   // namespace Plane
typedef Plane::PointVector< double > PointVector2D;
typedef Plane::Point Point2D;
typedef Plane::PointVector< int > IntPointVector2D;
typedef Plane::IntPoint IntPoint2D;

namespace Space
{

using namespace Math;

// forward declare HomogeneousVector
class HomogeneousVector;

// Represent a point in 3D space
template< typename T >
class PointVector : public Vector< T, 3 >
{
public:

    // simplify typing
    typedef Vector< T, 3 > BaseType;
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
                 const T& ac_rFill = DefaultValue< T >() );
    template< typename U, unsigned int P, unsigned int Q >
    PointVector( const Matrix< U, P, Q >& ac_roMatrix,
                 const T& ac_rFill = DefaultValue< T >() );
    PointVector( const T& a_dFill );
    PointVector( const T (&ac_radData)[ 3 ] );
    
    // Assignment operators that pass to base class
    template< typename U, unsigned int Q, bool t_bOtherIsRow >
    PointVector& operator=( const Vector< U, Q, t_bOtherIsRow >& ac_roVector );
    template< typename U, unsigned int P, unsigned int Q >
    PointVector& operator=( const Matrix< U, P, Q >& ac_roMatrix );
    PointVector& operator=( const T& ac_rFill );
    PointVector& operator=( const T (&ac_raData)[ 3 ] );
    
    // Construct from the given coordinates
    PointVector( const T& a_dX, const T& a_dY, const T& a_dZ );

    // Construct from HomogeneousVector
    PointVector( const HomogeneousVector& ac_roVector );
    PointVector& operator=( const HomogeneousVector& ac_roVector );

    // Origin of the coordinate system
    static const PointVector& Origin();

    // public access to X, Y, and Z coordinates
    T& x;
    T& y;
    T& z;

};   // Space::PointVector
typedef PointVector< double > Point;
typedef PointVector< int > IntPoint;

}   // namespace Space
typedef Space::PointVector< double > PointVector3D;
typedef Space::Point Point3D;
typedef Space::PointVector< int > IntPointVector3D;
typedef Space::IntPoint IntPoint3D;

#include "HomogeneousVector.h"
#include "../Implementations/PointVector.inl"

// explicit instantiations
EXTERN_T_INST template class IMEXPORT_T_INST Plane::PointVector< double >;
EXTERN_T_INST template class IMEXPORT_T_INST Plane::PointVector< int >;
EXTERN_T_INST template class IMEXPORT_T_INST Space::PointVector< double >;
EXTERN_T_INST template class IMEXPORT_T_INST Space::PointVector< int >;


#endif // POINT_VECTOR__H