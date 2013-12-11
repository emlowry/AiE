/******************************************************************************
 * File:               Functions.h
 * Author:             Elizabeth Lowry
 * Date Created:       December 2, 2013
 * Description:        Various library functions not contained in a class.
 * Last Modified:      December 10, 2013
 * Last Modification:  Switched from calculating PI to defining it literally.
 ******************************************************************************/

#ifndef FUNCTIONS__H
#define FUNCTIONS__H

#include "Vector.h"

namespace Math
{

// Degrees/Radians in a circle
const unsigned short DEGREES_IN_A_CIRCLE = 360;
const long double PI = 3.14159265358979323846264338327950288419716939937510582L;
const long double RADIANS_IN_A_CIRCLE = 2 * PI;
const long double DEGREES_IN_A_RADIAN = 180L / PI;

// Convert between degrees and radians
template< typename T >
double Degrees( const T& ac_rRadians );
template< typename T >
double Radians( const T& ac_rDegrees );

// Linear Interpolation
template< typename T >
T Interpolate( const T& ac_rPointA,
               const T& ac_rPointB,
               float a_fProgress = 0.5f );

// Call fmod for floating-point types and operator% for everything else
template< typename T >
T& ModuloAssign( T& a_rDividend, const T& ac_rDivisor );
template< typename T >
T Modulo( const T& ac_rDividend, const T& ac_rDivisor );
template<>
float& ModuloAssign< float >( float& a_rDividend, const float& ac_rDivisor );
template<>
float Modulo< float >( const float& ac_rDividend, const float& ac_rDivisor );
template<>
double& ModuloAssign< double >( double& a_rDividend,
                                const double& ac_rDivisor );
template<>
double Modulo< double >( const double& ac_rDividend,
                                 const double& ac_rDivisor );
template<>
long double& ModuloAssign< long double >( long double& a_rDividend,
                                          const long double& ac_rDivisor );
template<>
long double Modulo< long double >( const long double& ac_rDividend,
                                   const long double& ac_rDivisor );

// Return the power of two closest to the given value
template< typename T >
T NearestPowerOfTwo( const T& ac_rValue );

// Scroll a value into the given bounds.
template< typename T >
T Scroll( const T& ac_rValue, const T& ac_rMax, const T& ac_rMin = 0 );

}   // namespace Math

#include "Implementations/Functions.inl"

#endif  // FUNCTIONS__H
