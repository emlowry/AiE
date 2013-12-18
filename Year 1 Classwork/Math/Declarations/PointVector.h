/******************************************************************************
 * File:               PointVector.h
 * Author:             Elizabeth Lowry
 * Date Created:       December 17, 2013
 * Description:        Vectors for representing points in 2D or 3D space.
 * Last Modified:      December 17, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef POINT_VECTORS__H
#define POINT_VECTORS__H

#include "Vector.h"

namespace Plane
{

// Represent a point in 2D space
class PointVector : public Math::Vector< double, 2 >
{
public:

    // simplify typing
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
                 double _dFill = 0 );
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

    // public access to X and Y coordinates
    double& x;
    double& y;

};   // Plane::PointVector

}   // namespace Plane

namespace Space
{

// Represent a point in 3D space
class PointVector : public Math::Vector< double, 3 >
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
                 double _dFill = 0 );
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

    // public access to X, Y, and Z coordinates
    double& x;
    double& y;
    double& z;

};   // Space::PointVector

}   // namespace Space

#include "Implementations/PointVector.inl"

#endif // POINT_VECTORS__H