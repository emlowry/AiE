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
 * Last Modified:      December 18, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef HOMOGENEOUS_VECTOR__H
#define HOMOGENEOUS_VECTOR__H

#include "Vector.h"
#include "PointVector.h"

// forward declare homogeneous space vector
namespace Space
{
class HomogeneousVector;
}

namespace Plane
{

// Represent homogeneous coordinates for a point in 2D space
class HomogeneousVector : public Math::Vector< double, 3 >
{
public:

    // simplify typing
    typedef Math::Matrix< double, 3 > Transform;
    typedef Math::Matrix< double, 3, 2 > LineProjection;
    typedef Math::Matrix< double, 3, 4 > SpaceProjection;
    typedef Math::Vector< double, 3 > BaseType;
    typedef BaseType::BaseType VectorBaseType;
    typedef BaseType::RootType RootType;

    // inherit assignment operators
    using BaseType::operator=;

    // destructor
    virtual ~HomogeneousVector();

    // Constructors that forward to base class constructors
    HomogeneousVector();
    HomogeneousVector( const HomogeneousVector& ac_roVector );
    HomogeneousVector( const BaseType& ac_roVector );
    HomogeneousVector( const VectorBaseType& ac_roVector );
    HomogeneousVector( const RootType& ac_roMatrix );
    HomogeneousVector( HomogeneousVector&& a_rroVector );
    HomogeneousVector( BaseType&& a_rroVector );
    HomogeneousVector( VectorBaseType&& a_rroVector );
    HomogeneousVector( RootType&& a_rroMatrix );
    template< typename U, unsigned int Q, bool t_bOtherIsRow >
    HomogeneousVector( const Vector< U, Q, t_bOtherIsRow >& ac_roVector,
                       double a_dFill = 0 );
    template< unsigned int Q, bool t_bOtherIsRow >
    HomogeneousVector( Vector< double, Q, t_bOtherIsRow >&& a_rroVector,
                       double a_dFill = 0 );
    template< typename U, unsigned int Q, bool t_bOtherIsRow >
    HomogeneousVector( const VectorBase< U, Q, t_bOtherIsRow >& ac_roVector,
                       double a_dFill = 0 );
    template< unsigned int Q, bool t_bOtherIsRow >
    HomogeneousVector( VectorBase< double, Q, t_bOtherIsRow >&& a_rroVector,
                       double a_dFill = 0 );
    template< typename U, unsigned int P, unsigned int Q >
    HomogeneousVector( const MatrixBase< U, P, Q >& ac_roMatrix,
                       double a_dFill = 0 );
    template< unsigned int P, unsigned int Q >
    HomogeneousVector( MatrixBase< double, P, Q >&& a_rroMatrix,
                       double a_dFill = 0 );
    HomogeneousVector( double a_dFill );
    HomogeneousVector( const double (&ac_radData)[ 3 ] );
    HomogeneousVector( const double* const ac_cpdData,
                       const unsigned int ac_uiSize,
                       double a_dFill = 0 );

    // Construct from the given coordinates
    HomogeneousVector( double a_dX, double a_dY, double a_dH = 1.0 );

    // Construct from a 2D point or a 3D homogeneous vector
    HomogeneousVector( const PointVector& ac_roPoint, double a_dH = 1.0 );
    HomogeneousVector( const Space::HomogeneousVector& ac_roVector );
    HomogeneousVector& operator=( const Space::HomogeneousVector& ac_roVector );

    // re-implement addition and subtraction to account for h value
    // this will hide all parent class addition and subtraction operators.
    HomogeneousVector operator+( const HomogeneousVector& ac_roVector ) const;
    HomogeneousVector& operator+=( const HomogeneousVector& ac_roVector );
    HomogeneousVector operator-( const HomogeneousVector& ac_roVector ) const;
    HomogeneousVector& operator-=( const HomogeneousVector& ac_roVector );

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

namespace Space
{

// Represent homogenous coordinates for a point in 3D space
class HomogeneousVector : public Math::Vector< double, 4 >
{
public:

    // simplify typing
    typedef Math::Matrix< double, 4 > Transform;
    typedef Math::Matrix< double, 4, 3 > PlaneProjection;
    typedef Math::Vector< double, 4 > BaseType;
    typedef BaseType::BaseType VectorBaseType;
    typedef BaseType::RootType RootType;

    // inherit assignment operators
    using BaseType::operator=;

    // destructor
    virtual ~HomogeneousVector();

    // Constructors that forward to base class constructors
    HomogeneousVector();
    HomogeneousVector( const HomogeneousVector& ac_roVector );
    HomogeneousVector( const BaseType& ac_roVector );
    HomogeneousVector( const VectorBaseType& ac_roVector );
    HomogeneousVector( const RootType& ac_roMatrix );
    HomogeneousVector( HomogeneousVector&& a_rroVector );
    HomogeneousVector( BaseType&& a_rroVector );
    HomogeneousVector( VectorBaseType&& a_rroVector );
    HomogeneousVector( RootType&& a_rroMatrix );
    template< typename U, unsigned int Q, bool t_bOtherIsRow >
    HomogeneousVector( const Vector< U, Q, t_bOtherIsRow >& ac_roVector,
                       double a_dFill = 0 );
    template< unsigned int Q, bool t_bOtherIsRow >
    HomogeneousVector( Vector< double, Q, t_bOtherIsRow >&& a_rroVector,
                       double a_dFill = 0 );
    template< typename U, unsigned int Q, bool t_bOtherIsRow >
    HomogeneousVector( const VectorBase< U, Q, t_bOtherIsRow >& ac_roVector,
                       double a_dFill = 0 );
    template< unsigned int Q, bool t_bOtherIsRow >
    HomogeneousVector( VectorBase< double, Q, t_bOtherIsRow >&& a_rroVector,
                       double a_dFill = 0 );
    template< typename U, unsigned int P, unsigned int Q >
    HomogeneousVector( const MatrixBase< U, P, Q >& ac_roMatrix,
                       double a_dFill = 0 );
    template< unsigned int P, unsigned int Q >
    HomogeneousVector( MatrixBase< double, P, Q >&& a_rroMatrix,
                       double a_dFill = 0 );
    HomogeneousVector( double a_dFill );
    HomogeneousVector( const double (&ac_radData)[ 4 ] );
    HomogeneousVector( const double* const ac_cpdData,
                       const unsigned int ac_uiSize,
                       double a_dFill = 0 );

    // Construct from the given coordinates
    HomogeneousVector( double a_dX, double a_dY, double a_dZ, double a_dH = 1.0 );

    // Construct from a 3D point or a 2D homogeneous vector
    HomogeneousVector( const PointVector& ac_roPoint, double a_dH = 1.0 );
    HomogeneousVector( const Plane::HomogeneousVector& ac_roVector,
                       double a_dH = 1.0 );
    HomogeneousVector( const Plane::HomogeneousVector& ac_roVector,
                       double a_dH, double a_dZ );

    // re-implement addition and subtraction to account for h value
    // this will hide all parent class addition and subtraction operators.
    HomogeneousVector operator+( const HomogeneousVector& ac_roVector ) const;
    HomogeneousVector& operator+=( const HomogeneousVector& ac_roVector );
    HomogeneousVector operator-( const HomogeneousVector& ac_roVector ) const;
    HomogeneousVector& operator-=( const HomogeneousVector& ac_roVector );

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

#include "Implementations/HomogeneousVector_Plane.inl"
#include "Implementations/HomogeneousVector_Space.inl"

#endif  // HOMOGENEOUS_VECTOR__H
