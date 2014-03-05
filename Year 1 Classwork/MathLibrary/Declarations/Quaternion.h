/******************************************************************************
 * File:               Quaternion.h
 * Author:             Elizabeth Lowry
 * Date Created:       March 3, 2014
 * Description:        Class representing a quaternion {{w,x,y,z}}.
 *                      For a rotation of A radians about a normalized axis
 *                      {{Bx,By,Bz}}, the resulting quaternion {{w,x,y,z}} would
 *                      be {{cos(A/2),sin(A/2)Bx,sin(A/2)By,sin(A/2)Bz}}.
 * Last Modified:      March 5, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

#ifndef QUATERNION__H
#define QUATERNION__H

#include "PointVector.h"
#include "Transform.h"
#include "Vector.h"

#include "ImExportMacro.h"

namespace Space
{

// Represents a quaternion
class IMEXPORT_CLASS Quaternion : protected Math::Vector< double, 4 >
{
public:

    // Constructors
    Quaternion( const Quaternion& ac_roQuaternion );
    Quaternion( double a_dAngle = 0.0,
                const Point3D& ac_roAxis = Point3D::Unit(2) );
    Quaternion( double a_dYaw, double a_dPitch, double a_dRoll = 0.0 );
    Quaternion( const Point3D& ac_roForward,
                const Point3D& ac_roUp = Point3D::Zero() );

    // Destructor
    virtual ~Quaternion();

    // Assignment
    Quaternion& operator=( const Quaternion& ac_roQuaternion );

    // Equality and inequality checks
    bool operator==( const Quaternion& ac_roQuaternion ) const;
    bool operator!=( const Quaternion& ac_roQuaternion ) const;

    // Access
    double& operator[]( unsigned int a_uiIndex );
    double& At( unsigned int a_uiIndex );
    const double& operator[]( unsigned int a_uiIndex ) const;
    const double& At( unsigned int a_uiIndex ) const;

    // Multiplication - multiplying Q1 by Q2 yields a rotation equal to first
    // performing rotation Q1, then performing rotation Q2.  Division is just
    // multiplication by an inverse
    Quaternion operator*( const Quaternion& ac_roQuaternion ) const;
    Quaternion& operator*=( const Quaternion& ac_roQuaternion );
    Quaternion operator/( const Quaternion& ac_roQuaternion ) const;
    Quaternion& operator/=( const Quaternion& ac_roQuaternion );

    // Raising to a scalar power = multiplying rotation angle by that scalar
    template< typename T >
    typename std::enable_if< std::is_scalar< T >::value, Quaternion >::type
        operator^( const T& ac_rScalar ) const;
    template< typename T >
    typename std::enable_if< std::is_scalar< T >::value, Quaternion& >::type
        operator^=( const T& ac_rScalar );

    // Get properties
    double GetAngle() const;
    Point3D GetAxis() const;
    double GetYaw() const;
    double GetPitch() const;
    double GetRoll() const;
    void GetTaitBryanAngles( double& a_rdYaw,
                             double& a_rdPitch,
                             double& a_rdRoll ) const;

    // Set properties
    Quaternion& SetAngle( double a_dAngle = 0.0 );
    Quaternion& SetAxis( const Point3D& ac_roAxis = Point3D::Unit(2) );
    Quaternion& SetYaw( double a_dYaw = 0.0 );
    Quaternion& SetPitch( double a_dPitch = 0.0 );
    Quaternion& SetRoll( double a_dRoll = 0.0 );

    // Set entire quaternion
    Quaternion& Set( double a_dAngle = 0.0,
                     const Point3D& ac_roAxis = Point3D::Unit(2) );
    Quaternion& Set( const Point3D& ac_roForward,
                     const Point3D& ac_roUp = Point3D::Zero() );
    Quaternion& Set( double a_dYaw, double a_dPitch, double a_dRoll = 0.0 );

    // Apply this rotation to the given point
    Point3D AppliedTo( const Point3D& ac_roPoint ) const;
    Point3D& ApplyTo( Point3D& a_roPoint ) const;

    // Adjust so that angle of rotation is in the range [0,PI]
    Quaternion Clamped() const;
    Quaternion& Clamp();

    // Inversion
    Quaternion Inverse() const;
    Quaternion& Invert();

    // Keep the quaternion Normalized
    Quaternion& Normalize();

    // Spherical linear interpolation
    Quaternion Slerped( const Quaternion& ac_roQuaternion,
                        double a_dProgress = 0.5f ) const;
    Quaternion& Slerp( const Quaternion& ac_roQuaternion,
                       double a_dProgress = 0.5 );
    Quaternion Slerped( const Quaternion& ac_roQuaternion,
                        double a_dRadiansPerSecond, double a_dSeconds,
                        bool a_bClamp = true ) const;
    Quaternion& Slerp( const Quaternion& ac_roQuaternion,
                       double a_dRadiansPerSecond, double a_dSeconds,
                       bool a_bClamp = true );

    // Turn into transform
    Transform3D MakeTransform() const;
    void MakeTransform( Transform3D& a_roTransform ) const;
    PointTransform3D MakePointTransform() const;
    void MakePointTransform( PointTransform3D& a_roTransform ) const;

    // Rotation by PI radians about the given axis (default is z-axis)
    static const Quaternion& Half( unsigned int a_uiAxis = 2 );

    // Quaternion representing no rotation
    static const Quaternion& None();

protected:
    
    typedef Math::Vector< double, 4 > BaseType;
    typedef BaseType::BaseType RootType;

    // Construct with specific values
    Quaternion( double a_dW, double a_dX, double a_dY, double a_dZ );

    // construct from a vector
    Quaternion( const BaseType& ac_roVector );
    Quaternion& operator=( const BaseType& ac_roVector );

    // references to members
    double& w;  // m_aaData[0][0]
    double& x;  // m_aaData[0][1]
    double& y;  // m_aaData[0][2]
    double& z;  // m_aaData[0][3]

};  // class Quaternion

}   // namespace Space
typedef Space::Quaternion Rotation3D;

// Quaternion scalar multiplication and division in the other direction
template< typename T >
typename std::enable_if< std::is_scalar< T >::value, Space::Quaternion >::type
    operator*( const T& ac_rScalar, const Space::Quaternion& ac_roQuaternion );
template< typename T >
typename std::enable_if< std::is_scalar< T >::value, Space::Quaternion >::type
    operator/( const T& ac_rScalar, const Space::Quaternion& ac_roQuaternion );

// Always include template implementations
#include "../Implementations/Quaternion_Templates.inl"
#ifdef INLINE_IMPLEMENTATION
#include "../Implementations/Quaternion.inl"
#endif

#endif  // QUATERNION__H
