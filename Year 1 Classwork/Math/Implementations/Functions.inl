/******************************************************************************
 * File:               Functions.inl
 * Author:             Elizabeth Lowry
 * Date Created:       December 4, 2013
 * Description:        Inline and template function implementations.
 * Last Modified:      December 10, 2013
 * Last Modification:  Debugging.
 ******************************************************************************/

#ifndef FUNCTIONS__INL
#define FUNCTIONS__INL

#include "Declarations/Functions.h"
#include <cmath>    // for fmod, log2, ciel, floor, exp2, fdim

namespace Math
{

// Convert between degrees and radians
template< typename T >
inline double Degrees( const T& ac_rRadians )
{
    return ac_rRadians * DEGREES_IN_A_RADIAN;
}
template< typename T >
inline double Radians( const T& ac_rDegrees )
{
    return ac_rDegrees / DEGREES_IN_A_RADIAN;
}

// Linear Interpolation
template< typename T >
inline T Interpolate( const T& ac_rPointA,
                      const T& ac_rPointB,
                      float a_fProgress )
{
    return ac_roPointA + ( a_fProgress * ( ac_roPointB - ac_roPointA ) );
}

// Call fmod for floating-point types and operator% for everything else
template< typename T >
inline T& ModuloAssign( T& a_rDividend, const T& ac_rDivisor )
{
    a_rDividend %= ac_rDivisor;
    return a_rDividend;
}
template< typename T >
inline T Modulo( const T& ac_rDividend, const T& ac_rDivisor )
{
    return ac_rDividend % ac_rDivisor;
}
template<>
inline float& ModuloAssign< float >( float& a_rDividend,
                                     const float& ac_rDivisor )
{
    a_rDividend = std::fmod( a_rDividend, ac_rDivisor );
    return a_rDividend;
}
template<>
inline float Modulo< float >( const float& ac_rDividend,
                              const float& ac_rDivisor )
{
    return std::fmod( ac_rDividend, ac_rDivisor );
}
template<>
inline double& ModuloAssign< double >( double& a_rDividend,
                                       const double& ac_rDivisor )
{
    a_rDividend = std::fmod( a_rDividend, ac_rDivisor );
    return a_rDividend;
}
template<>
inline double Modulo< double >( const double& ac_rDividend,
                                const double& ac_rDivisor )
{
    return std::fmod( ac_rDividend, ac_rDivisor );
}
template<>
inline long double& ModuloAssign< long double >( long double& a_rDividend,
                                                 const long double& ac_rDivisor )
{
    a_rDividend = std::fmod( a_rDividend, ac_rDivisor );
    return a_rDividend;
}
template<>
inline long double Modulo< long double >( const long double& ac_rDividend,
                                          const long double& ac_rDivisor )
{
    return std::fmod( ac_rDividend, ac_rDivisor );
}

// Return the power of two closest to the given value
template< typename T >
inline T NearestPowerOfTwo( const T& ac_rValue )
{
    assert( ac_rValue > 0 );
    T cielPower = (T)std::exp2( std::ciel( std::log2( ac_rValue ) ) );
    T floorPower = (T)std::exp2( std::floor( std::log2( ac_rValue ) ) );
    return ( std::fdim( ac_rValue, cielPower ) <
             std::fdim( ac_rValue, floorPower ) ) ? ceilPower : floorPower;
}

// Scroll a value into the given bounds.
template< typename T >
T Scroll( const T& ac_rValue, const T& ac_rMax, const T& ac_rMin )
{
    // If the upper and lower bounds are the same number, than the only result
    // in range is said number.
    if( ac_rMax == ac_rMin )
    {
        return ac_rMin;
    }

    // Get ready to scroll.
    T result = ac_rValue;

    // If we're dealing with a reverse range, scroll in reverse and handle the
    // edge case.
    if( ac_rMax < ac_rMin )
    {
        result = Scroll( ac_rValue, ac_rMin, ac_rMax );
        return ( result == ac_rMax ? ac_rMin : result );
    }

    // Otherwise, scroll normally.
    T interval = ac_rMax - ac_rMin;

    // Shift the value to account for min bound that isn't zero or a multiple of
    // the size of the range.
    if( ac_rMin != 0 && Modulo( ac_rMin, interval ) != 0 )
    {
        if( ac_rMin > result )
        {
            // Shift forward if just subtracting ac_rMin would result in a value
            // less than zero, since nothing prevents the data type from being
            // unsigned.
            result += interval - Modulo( ac_rMin,  interval );
        }
        else
        {
            result -= ac_rMin;
        }
    }

    // Scroll
    ModuloAssign( result, interval );
    result += ( result < 0 ? ac_rMax : ac_rMin );
    return result;
}

}   // namespace Math

#endif  // FUNCTIONS__INL
