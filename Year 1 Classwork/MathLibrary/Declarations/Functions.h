/******************************************************************************
 * File:               Functions.h
 * Author:             Elizabeth Lowry
 * Date Created:       December 2, 2013
 * Description:        Various library functions not contained in a class.
 * Last Modified:      March 5, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

#ifndef FUNCTIONS__H
#define FUNCTIONS__H

#include <type_traits>  // for enable_if, is_same, and is_floating_point

namespace Math
{

// Degrees/Radians in a circle
const unsigned short DEGREES_IN_A_CIRCLE = 360;
const long double PI = 3.14159265358979323846264338327950288419716939937510582L;
const long double HALF_PI = PI / 2;
const long double RADIANS_IN_A_CIRCLE = 2 * PI;
const long double DEGREES_IN_A_RADIAN = 180L / PI;

// other useful constants
const float FLOAT_ERROR = 1.0f / ( 1 << ( 8*sizeof( float ) -1 ) );
const double DOUBLE_ERROR = 1.0 / ( (long long)1 << ( 8*sizeof( double ) -1 ) );
const long double EULERS_NUMBER = 2.718281828459045235360287471352662497757247L;

// simplify typing for array reference parameter/return types
template< typename T, unsigned int N >
struct ArrayReference
{
    typedef T (&type)[ N ];
};
template< typename T, unsigned int M, unsigned int N = M >
struct Array2DReference
{
    typedef T (&type)[ M ][ N ];
};

// Used to determine type of matrix inversion operations
template< typename T >
struct InverseOf
{
    typedef
        typename std::conditional<
            std::is_same< long double, T >::value, long double,
            typename std::conditional<
                std::is_same< float, T >::value, float, double
            >::type
        >::type Type;
};

// Used whenever values at a given coordinate aren't specified, as in
// constructing a matrix from another matrix with smaller dimensions.
template< typename T >
const T& DefaultValue();

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
template< typename T, typename U >
typename std::enable_if< !std::is_floating_point< T >::value &&
                         !std::is_floating_point< U >::value,
                         typename std::common_type< T, U >::type >::type
    Modulo( const T& ac_rDividend, const U& ac_rDivisor );
template< typename T, typename U >
typename std::enable_if< !std::is_floating_point< T >::value &&
                         !std::is_floating_point< U >::value, T& >::type
    ModuloAssign( T& a_rDividend, const U& ac_rDivisor );
template< typename T, typename U >
typename std::enable_if< std::is_floating_point< T >::value ||
                         std::is_floating_point< U >::value,
                         typename std::common_type< T, U >::type >::type
    Modulo( const T& ac_rDividend, const U& ac_rDivisor );
template< typename T, typename U >
typename std::enable_if< std::is_floating_point< T >::value ||
                         std::is_floating_point< U >::value, T& >::type
    ModuloAssign( T& a_rDividend, const U& ac_rDivisor );

// Return the power of two closest to the given value
template< typename T >
typename std::enable_if< std::is_scalar< T >::value, T >::type
    NearestPowerOfTwo( const T& ac_rValue );

template< typename T >
typename std::enable_if< std::is_scalar< T >::value, T >::type
    Round( const T& ac_rValue );

// Scroll a value into the given bounds, [ ac_rMin, ac_rMax ).
template< typename T >
typename std::enable_if< std::is_scalar< T >::value, T >::type
    Scroll( const T& ac_rValue, const T& ac_rMax,
            const T& ac_rMin = DefaultValue< T >() );

// Scroll a value into the the bounds ( -PI, PI ].
template< typename T >
typename std::enable_if< std::is_scalar< T >::value, T >::type
    ScrollRadians( const T& ac_rValue );

// Complex conjugate (if you ever want to use a matrix full of complex numbers,
// you'll need to define an explicit specialization for this function).
template< typename T >
T ComplexConjugate( const T& ac_rValue );

}   // namespace Math

// Always include template function implementations with this header
#include "../Implementations/Functions.inl"
#include "../Implementations/Functions_Instantiations.inl"

#endif  // FUNCTIONS__H
