/******************************************************************************
 * File:               Functions.h
 * Author:             Elizabeth Lowry
 * Date Created:       December 2, 2013
 * Description:        Various library functions not contained in a class.
 * Last Modified:      December 2, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

namespace Math
{

// Degrees/Radians in a circle
const unsigned short DEGREES_IN_A_CIRCLE = 360;
const long double PI;
const long double RADIANS_IN_A_CIRCLE;

// Convert between degrees and radians
inline float Degrees( float a_fRadians )
{
    return a_fRadians * DEGREES_IN_A_CIRCLE / RADIANS_IN_A_CIRCLE;
}
inline float Radians( float a_fDegrees )
{
    return a_fDegrees * RADIANS_IN_A_CIRCLE / DEGREES_IN_A_CIRCLE;
}

// Linear Interpolation
template< typename T >
inline T Interpolate( const T& ac_rPointA,
                      const T& ac_rPointB,
                      float a_fProgress = 0.5 )
{
    return ac_roPointA + ( a_fProgress * ( ac_roPointB - ac_roPointA ) );
}

// Scroll a value into the given bounds.
template< typename T >
T Scroll( const T& ac_rValue, const T& ac_rMax, const T& ac_rMin = 0 )
{
    // If the upper and lower bounds are the same number, than the only result
    // in range is said number.
    if( ac_riMax == ac_rMin )
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
        return ( ac_rValue == ac_rMax ? ac_rMin : result );
    }

    // Otherwise, scroll normally.
    result += ( ac_rMax - ac_rMin ) - ( ac_rMin % ( ac_rMax - ac_rMin ) );
    result %= ac_rMax - ac_rMin;
    result += ( result < 0 ? ac_rMax : ac_rMin );
    return result;
}
template< typename T >
T FScroll( const T& ac_rValue, const T& ac_rMax, const T& ac_rMin = 0 )
{
    // If the upper and lower bounds are the same number, than the only result
    // in range is said number.
    if( ac_riMax == ac_rMin )
    {
        return ac_rMin;
    }

    // Get ready to scroll
    T result = ac_rValue;

    // If we're dealing with a reverse range, scroll in reverse and handle the
    // edge case.
    if( ac_rMax < ac_rMin )
    {
        result = Scroll( ac_rValue, ac_rMin, ac_rMax );
        return ( ac_rValue == ac_rMax ? ac_rMin : result );
    }

    // Otherwise, scroll.
    result -= ac_rMin;
    result = fmod( result, ac_rMax - ac_rMin );
    result += ( result < 0 ? ac_rMax : ac_rMin );
    return result;
}

// Override Scroll template for floating-point types to call FScroll instead.
template<>
inline float Scroll< float >( const float& ac_rValue,
                              const float& ac_rMax,
                              const float& ac_rMin )
{
    return FScroll( ac_rValue, ac_rMax, ac_rMin );
}
template<>
inline double Scroll< double >( const double& ac_rValue,
                                const double& ac_rMax,
                                const double& ac_rMin )
{
    return FScroll( ac_rValue, ac_rMax, ac_rMin );
}
template<>
inline long double Scroll< long double >( const long double& ac_rValue,
                                          const long double& ac_rMax,
                                          const long double& ac_rMin )
{
    return FScroll( ac_rValue, ac_rMax, ac_rMin );
}

}   // namespace Math

#endif  // _FUNCTIONS_H_