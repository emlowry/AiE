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
 * Last Modified:      January 5, 2014
 * Last Modification:  Added import/export macro.
 ******************************************************************************/

#ifndef HOMOGENEOUS_VECTOR__H
#define HOMOGENEOUS_VECTOR__H

#include "ImExportMacro.h"
#include "Vector.h"
#include "PointVector.h"

namespace Plane
{

// Represent homogeneous coordinates for a point in 2D space
class IMEXPORT_CLASS HomogeneousVector : public Math::Vector< double, 3 >
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

    // Construct from a 2D point
    HomogeneousVector( const PointVector& ac_roPoint, double a_dH = 1.0 );
    HomogeneousVector& operator=( const PointVector& ac_roVector );

    // re-implement addition and subtraction to account for h value
    // this will hide all parent class addition and subtraction operators.
    HomogeneousVector operator+( const HomogeneousVector& ac_roVector ) const;
    HomogeneousVector& operator+=( const HomogeneousVector& ac_roVector );
    HomogeneousVector operator-( const HomogeneousVector& ac_roVector ) const;
    HomogeneousVector& operator-=( const HomogeneousVector& ac_roVector );

    // re-implement scalar multiplication to account for h value
    template< typename T >
    HomogeneousVector operator*( const T& ac_rScalar ) const;
    template< typename T >
    HomogeneousVector& operator*=( const T& ac_rScalar );
    template< typename T >
    HomogeneousVector operator/( const T& ac_rScalar ) const;
    template< typename T >
    HomogeneousVector& operator/=( const T& ac_rScalar );
    template< typename T >
    HomogeneousVector operator%( const T& ac_rScalar ) const;
    template< typename T >
    HomogeneousVector& operator%=( const T& ac_rScalar );

    // re-implement matrix multiplication and division to homogenize first
    template< unsigned int N >
    Math::Matrix< double, 1, N >
        operator*( const Math::Matrix< double, 3, N >& ac_roMatrix ) const;
    template< unsigned int N >
    Math::Matrix< double, 1, N >
        operator/( const Math::Matrix< double, N, 3 >& ac_roMatrix ) const;
    HomogeneousVector& operator*=( const Math::Matrix< double, 3 >& ac_roMatrix );
    HomogeneousVector& operator/=( const Math::Matrix< double, 3 >& ac_roMatrix );

    // re-implement equality and inequality checks to account for h
    bool operator==( const HomogeneousVector& ac_roVector ) const;
    bool operator!=( const HomogeneousVector& ac_roVector ) const;

    // re-implement normalization to account for h value
    double Magnitude() const;
    double MagnitudeSquared() const; // for efficiency in complex calculations
    void Normalize();
    HomogeneousVector Normal() const;

    // Adjust values so that h = 1 or 0
    HomogeneousVector& Homogenize();

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

// Vector scalar multiplication and division in the other direction
template< typename U >
Plane::HomogeneousVector
    operator*( const U& ac_rScalar,
               const Plane::HomogeneousVector& ac_roVector );
template< typename U >
Plane::HomogeneousVector
    operator/( const U& ac_rScalar,
               const Plane::HomogeneousVector& ac_roVector );

namespace Space
{

// Represent homogenous coordinates for a point in 3D space
class IMEXPORT_CLASS HomogeneousVector : public Math::Vector< double, 4 >
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

    // Construct from a 3D point
    HomogeneousVector( const PointVector& ac_roPoint, double a_dH = 1.0 );
    HomogeneousVector& operator=( const PointVector& ac_roPoint );

    // re-implement addition and subtraction to account for h value
    // this will hide all parent class addition and subtraction operators.
    HomogeneousVector operator+( const HomogeneousVector& ac_roVector ) const;
    HomogeneousVector& operator+=( const HomogeneousVector& ac_roVector );
    HomogeneousVector operator-( const HomogeneousVector& ac_roVector ) const;
    HomogeneousVector& operator-=( const HomogeneousVector& ac_roVector );

    // re-implement scalar multiplication to account for h value
    template< typename T >
    HomogeneousVector operator*( const T& ac_rScalar ) const;
    template< typename T >
    HomogeneousVector& operator*=( const T& ac_rScalar );
    template< typename T >
    HomogeneousVector operator/( const T& ac_rScalar ) const;
    template< typename T >
    HomogeneousVector& operator/=( const T& ac_rScalar );
    template< typename T >
    HomogeneousVector operator%( const T& ac_rScalar ) const;
    template< typename T >
    HomogeneousVector& operator%=( const T& ac_rScalar );

    // re-implement matrix multiplication and division to homogenize first
    template< unsigned int N >
    Math::Matrix< double, 1, N >
        operator*( const Math::Matrix< double, 4, N >& ac_roMatrix ) const;
    template< unsigned int N >
    Math::Matrix< double, 1, N >
        operator/( const Math::Matrix< double, N, 4 >& ac_roMatrix ) const;
    HomogeneousVector& operator*=( const Math::Matrix< double, 4 >& ac_roMatrix );
    HomogeneousVector& operator/=( const Math::Matrix< double, 4 >& ac_roMatrix );

    // re-implement equality and inequality checks to account for h
    bool operator==( const HomogeneousVector& ac_roVector ) const;
    bool operator!=( const HomogeneousVector& ac_roVector ) const;

    // re-implement normalization to account for h value
    double Magnitude() const;
    double MagnitudeSquared() const; // for efficiency in complex calculations
    void Normalize();
    HomogeneousVector Normal() const;

    // Adjust values so that h = 1 or 0
    HomogeneousVector& Homogenize();

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

// Vector scalar multiplication and division in the other direction
template< typename U >
Space::HomogeneousVector
    operator*( const U& ac_rScalar,
               const Space::HomogeneousVector& ac_roVector );
template< typename U >
Space::HomogeneousVector
    operator/( const U& ac_rScalar,
               const Space::HomogeneousVector& ac_roVector );

// Always include template function implementations with this header
#include "Implementations/HomogeneousVector_Templates.inl"

#endif  // HOMOGENEOUS_VECTOR__H
