/******************************************************************************
 * File:               Quaternion.h
 * Author:             Elizabeth Lowry
 * Date Created:       March 3, 2014
 * Description:        Class representing a quaternion {{w,x,y,z}}.
 *                      For a rotation of A radians about a normalized axis
 *                      {{Bx,By,Bz}}, the resulting quaternion {{w,x,y,z}} would
 *                      be {{cos(A/2),sin(A/2)Bx,sin(A/2)By,sin(A/2)Bz}}.
 * Last Modified:      March 3, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef QUATERNION__H
#define QUATERNION__H

#include "Functions.h"
#include "PointVector.h"
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
    Quaternion( const Point3D& ac_roAxisMultipliedByAngle );
    Quaternion( double a_dYaw, double a_dPitch, double a_dRoll = 0.0 );

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

    // Addition - adding quaternions means adding their elements
    Quaternion operator+( const Quaternion& ac_roQuaternion ) const;
    Quaternion& operator+=( const Quaternion& ac_roQuaternion );
    Quaternion operator-( const Quaternion& ac_roQuaternion ) const;
    Quaternion& operator-=( const Quaternion& ac_roQuaternion );

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

    // Multiplying by a scalar = multiplying each component by that scalar
    Quaternion operator-() const;
    template< typename T >
    typename std::enable_if< std::is_scalar< T >::value, Quaternion >::type
        operator*( const T& ac_rScalar ) const;
    template< typename T >
    typename std::enable_if< std::is_scalar< T >::value, Quaternion& >::type
        operator*=( const T& ac_rScalar );
    template< typename T >
    typename std::enable_if< std::is_scalar< T >::value, Quaternion >::type
        operator/( const T& ac_rScalar ) const;
    template< typename T >
    typename std::enable_if< std::is_scalar< T >::value, Quaternion& >::type
        operator/=( const T& ac_rScalar );

    // Get properties
    double GetAngle() const;
    Point3D GetAxis() const;
    Point3D GetAxisMultipliedByAngle() const;
    double GetYaw() const;
    double GetPitch() const;
    double GetRoll() const;
    void GetTaitBryanAngles( double& a_rdYaw,
                             double& a_rdPitch,
                             double& a_rdRoll ) const;

    // Set properties
    Quaternion& SetAngle( double a_dAngle = 0.0 );
    Quaternion& SetAxis( const Point3D& ac_roAxis = Point3D::Unit(2) );
    Quaternion& SetYaw( double a_dAngle = 0.0 );
    Quaternion& SetPitch( double a_dAngle = 0.0 );
    Quaternion& SetRoll( double a_dAngle = 0.0 );

    // Set entire quaternion
    Quaternion& Set( double a_dAngle = 0.0,
                     const Point3D& ac_roAxis = Point3D::Unit(2) );
    Quaternion& Set( const Point3D& ac_roAxisMultipliedByAngle );
    Quaternion& Set( double a_dYaw, double a_dPitch, double a_dRoll = 0.0 );

    // Add angles
    Quaternion& AddAngle( double a_dAngle );
    Quaternion& AddYaw( double a_dAngle );
    Quaternion& AddPitch( double a_dAngle );
    Quaternion& AddRoll( double a_dAngle );

    // Inversion
    Quaternion Inverse() const;
    Quaternion& Invert();

    // Adjust so that angle of rotation is in the range [0,PI]
    Quaternion Clamped() const;
    Quaternion& Clamp();

    // Conjugation
    // To conjugate quaternion p by quaternion q is to compute q*p*(q^-1)
    Quaternion ConjugationBy( const Quaternion& ac_roQuaternion ) const;
    Quaternion ConjugateBy( const Quaternion& ac_roQuaternion );

    // Magnitude and normalization
    double MagnitudeSquared() const;
    double Magnitude() const;
    Quaternion Normal() const;
    Quaternion& Normalize();

    // Turn into transform
    Transform MakeTransform() const;
    void MakeTransform( Transform& ac_roTransform ) const;
    PointTransform MakePointTransform() const;
    void MakePointTransform() const;

    // Rotation by PI radians about the given axis (default is z-axis)
    const Quaternion& HalfRotationAboutAxis( unsigned int a_uiAxis = 2 );

    // references to members
    double& w;  // m_aaData[0][0]
    double& x;  // m_aaData[0][1]
    double& y;  // m_aaData[0][2]
    double& z;  // m_aaData[0][3]

private:
    
    typedef Math::Vector< double, 4 > BaseType;
    typedef BaseType::BaseType RootType;

    // construct from a vector
    Quaternion( const BaseType& ac_roVector );

};  // class Quaternion

}   // namespace Space

// Spherical Linear Interpolation
namespace Math
{
template<>
Space::Quaternion
    Interpolate< Space::Quaternion >( const Space::Quaternion& ac_roQuaternionA,
                                      const Space::Quaternion& ac_roQuaternionB,
                                      float a_fProgress );
}

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
