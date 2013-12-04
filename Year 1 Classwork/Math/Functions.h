/******************************************************************************
 * File:               Functions.h
 * Author:             Elizabeth Lowry
 * Date Created:       December 2, 2013
 * Description:        Various library functions not contained in a class.
 * Last Modified:      December 4, 2013
 * Last Modification:  Added NearestPowerOfTwo function.
 ******************************************************************************/

#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

namespace Math
{

// Degrees/Radians in a circle
const unsigned short DEGREES_IN_A_CIRCLE = 360;
const long double PI;
const long double RADIANS_IN_A_CIRCLE;
const long double DEGREES_IN_A_RADIAN;

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

#endif  // _FUNCTIONS_H_
