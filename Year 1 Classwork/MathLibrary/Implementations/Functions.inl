/******************************************************************************
 * File:               Functions.inl
 * Author:             Elizabeth Lowry
 * Date Created:       December 4, 2013
 * Description:        Inline and template function implementations.
 * Last Modified:      February 12, 2014
 * Last Modification:  Refactoring.
 ******************************************************************************/

#ifndef FUNCTIONS__INL
#define FUNCTIONS__INL

#include "Declarations/Functions.h"
#include <cmath>    // for fmod, log, pow, abs
#include <type_traits>  // for enable_if, is_same, and is_floating_point

namespace Math
{

// Used whenever values at a given coordinate aren't specified, as in
// constructing a matrix from another matrix with smaller dimensions.
template< typename T >
const T& DefaultValue()
{
    static T fill = 0;
    return fill;
}

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
    return (T)( ac_rPointA + ( a_fProgress * ( ac_rPointB - ac_rPointA ) ) );
}

// Call fmod for floating-point types and operator% for everything else
template< typename T, typename U >
inline typename std::enable_if< !std::is_floating_point< T >::value &&
                                !std::is_floating_point< U >::value, T >::type
    Modulo( const T& ac_rDividend, const U& ac_rDivisor )
{
    return ac_rDividend % ac_rDivisor;
}
template< typename T, typename U >
inline typename std::enable_if< !std::is_floating_point< T >::value &&
                                !std::is_floating_point< U >::value, T& >::type
     ModuloAssign( T& a_rDividend, const U& ac_rDivisor )
{
    a_rDividend %= ac_rDivisor;
    return a_rDividend;
}
template< typename T, typename U >
inline typename std::enable_if< std::is_same< long double, T >::value ||
                                std::is_same< long double, U >::value, T >::type
    Modulo( const T& ac_rDividend, const float& ac_rDivisor )
{
    return (T)std::fmod( (long double)a_rDividend, (long double)ac_rDivisor );
}
template< typename T, typename U >
inline typename std::enable_if< std::is_same< long double, T >::value ||
                                std::is_same< long double, U >::value, T& >::type
     ModuloAssign( T& a_rDividend, const U& ac_rDivisor )
{
    a_rDividend = (T)std::fmod( (long double)a_rDividend, (long double)ac_rDivisor );
    return a_rDividend;
}
template< typename T, typename U >
inline typename std::enable_if< std::is_same< float, T >::value &&
                                std::is_same< float, U >::value, T >::type
    Modulo( const T& ac_rDividend, const float& ac_rDivisor )
{
    return (T)std::fmod( (float)ac_rDividend, (float)ac_rDivisor );
}
template< typename T, typename U >
inline typename std::enable_if< std::is_same< float, T >::value &&
                                std::is_same< float, U >::value, T& >::type
     ModuloAssign( T& a_rDividend, const U& ac_rDivisor )
{
    a_rDividend = (T)std::fmod( (float)a_rDividend, (float)ac_rDivisor );
    return a_rDividend;
}
template< typename T, typename U >
inline typename std::enable_if< !std::is_same< long double, T >::value &&
                                !std::is_same< long double, U >::value &&
                                ( std::is_floating_point< T >::value ||
                                  std::is_floating_point< U >::value ) &&
                                !( std::is_same< float, T >::value &&
                                   std::is_same< float, U >::value ), T >::type
    Modulo( const T& ac_rDividend, const float& ac_rDivisor )
{
    return (T)std::fmod( (double)ac_rDividend, (double)ac_rDivisor );
}
template< typename T, typename U >
inline typename std::enable_if< !std::is_same< long double, T >::value &&
                                !std::is_same< long double, U >::value &&
                                ( std::is_floating_point< T >::value ||
                                  std::is_floating_point< U >::value ) &&
                                !( std::is_same< float, T >::value &&
                                   std::is_same< float, U >::value ), T& >::type
     ModuloAssign( T& a_rDividend, const U& ac_rDivisor )
{
    a_rDividend = (T)std::fmod( (double)a_rDividend, (double)ac_rDivisor );
    return a_rDividend;
}

// Return the power of two closest to the given value
template< typename T >
inline typename std::enable_if< std::is_scalar< T >::value, T >::type
    NearestPowerOfTwo( const T& ac_rValue )
{
    if( ac_rValue <= (T)0 )
    {
        return (T)1;
    }
    double dLog = std::log( (double)ac_rValue ) / std::log( 2.0 );
    double dCeilPower = std::pow( 2.0, std::ceil( dLog ) );
    double dFloorPower = std::pow( 2.0, std::floor( dLog ) );
    /*
    double dCeilPower = std::pow( 2.0, (int)( std::log( (double)ac_rValue ) /
                                                std::log( 2.0 ) ) +
                                        ( ac_rValue < 1 ? -1 : 1 ) );
    double dFloorPower = std::pow( 2.0, (int)( std::log( (double)ac_rValue ) /
                                                std::log( 2.0 ) ) );*/
    return (T)( ( std::fabs( (double)ac_rValue - dCeilPower ) <
                  std::fabs( (double)ac_rValue - dFloorPower ) )
                ? dCeilPower : dFloorPower );
}

// Round to nearest whole number
template< typename T >
inline typename std::enable_if< std::is_scalar< T >::value, T >::type
    Round( const T& ac_rValue )
{
    double dCeil = std::ceil( (double)ac_rValue );
    double dFloor = std::floor( (double)ac_rValue );
    return (T)( ( std::fabs( (double)ac_rValue - dCeil ) <
                  std::fabs( (double)ac_rValue - dFloor ) )
                ? dCeil : dFloor );
}

// Scroll a value into the given bounds.
template< typename T >
typename std::enable_if< std::is_scalar< T >::value, T >::type
    Scroll( const T& ac_rValue, const T& ac_rMax, const T& ac_rMin )
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

// Complex conjugate (if you ever want to use a matrix full of complex numbers,
// you'll need to define an explicit specialization for this function).
template< typename T >
inline T ComplexConjugate( const T& ac_rValue )
{
    return ac_rValue;
}

}   // namespace Math

#endif  // FUNCTIONS__INL
