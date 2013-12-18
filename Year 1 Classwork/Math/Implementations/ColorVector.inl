/******************************************************************************
 * File:               ColorVector.inl
 * Author:             Elizabeth Lowry
 * Date Created:       December 16, 2013
 * Description:        Inline function implementations for ColorVector class.
 * Last Modified:      December 16, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef COLOR_VECTOR__INL
#define COLOR_VECTOR__INL

#include "Declarations/ColorConstants.h"
#include "ColorVector_Constructors.inl"
#include "ColorVector_AssignmentOperators.inl"

namespace Color
{

// Bitwise operators
inline ColorVector ColorVector::operator~() const
{
    return ColorVector( ~( (Hex)(*this) ) );
}
inline ColorVector
    ColorVector::operator&( const ColorVector& ac_roVector ) const
{
    return operator&( (Hex)(ac_roVector) );
}
inline ColorVector
    ColorVector::operator|( const ColorVector& ac_roVector ) const
{
    return operator|( (Hex)(ac_roVector) );
}
inline ColorVector
    ColorVector::operator^( const ColorVector& ac_roVector ) const
{
    return operator^( (Hex)(ac_roVector) );
}
inline ColorVector& ColorVector::operator&=( const ColorVector& ac_roVector )
{
    return operator&=( (Hex)(ac_roVector) );
}
inline ColorVector& ColorVector::operator|=( const ColorVector& ac_roVector )
{
    return operator|=( (Hex)(ac_roVector) );
}
inline ColorVector& ColorVector::operator^=( const ColorVector& ac_roVector )
{
    return operator^=( (Hex)(ac_roVector) );
}
inline ColorVector ColorVector::operator&( const Hex& ac_rHex ) const
{
    return ( (Hex)(*this) & ac_rHex );
}
inline ColorVector ColorVector::operator|( const Hex& ac_rHex ) const
{
    return ( (Hex)(*this) | ac_rHex );
}
inline ColorVector ColorVector::operator^( const Hex& ac_rHex ) const
{
    return ( (Hex)(*this) ^ ac_rHex );
}
inline ColorVector& ColorVector::operator&=( const Hex& ac_rHex )
{
    operator=( operator&( ac_rHex ) );
    return *this;
}
inline ColorVector& ColorVector::operator|=( const Hex& ac_rHex )
{
    operator=( operator|( ac_rHex ) );
    return *this;
}
inline ColorVector& ColorVector::operator^=( const Hex& ac_rHex )
{
    operator=( operator^( ac_rHex ) );
    return *this;
}

// arithmatic operators for use with scalars
template< typename T >
inline ColorVector ColorVector::operator*( const T& ac_rScalar ) const
{
    return ColorVector( (Hex)(*this) * ac_rScalar );
}
template< typename T >
inline ColorVector ColorVector::operator/( const T& ac_rScalar ) const
{
    return ColorVector( (Hex)(*this) / ac_rScalar );
}
template< typename T >
inline ColorVector ColorVector::operator%( const T& ac_rScalar ) const
{
    return ColorVector( BaseType::operator%( ac_rScalar ) );
}
template< typename T >
inline ColorVector& ColorVector::operator*=( const T& ac_rScalar )
{
    *this = operator*( ac_rScalar );
    return *this;
}
template< typename T >
inline ColorVector& ColorVector::operator/=( const T& ac_rScalar )
{
    *this = operator/( ac_rScalar );
    return *this;
}
template< typename T >
inline ColorVector& ColorVector::operator%=( const T& ac_rScalar )
{
    *this = operator%( ac_rScalar );
    return *this;
}

// arithmatic operators for use with other color vectors
inline ColorVector
    ColorVector::operator+( const ColorVector& ac_roVector ) const
{
    return operator+( (Hex)(ac_roVector) );
}
inline ColorVector
    ColorVector::operator-( const ColorVector& ac_roVector ) const
{
    return operator-( (Hex)(ac_roVector) );
}
inline ColorVector
    ColorVector::operator*( const ColorVector& ac_roVector ) const
{
    return operator*( (Hex)(ac_roVector) );
}
inline ColorVector
    ColorVector::operator/( const ColorVector& ac_roVector ) const
{
    return operator/( (Hex)(ac_roVector) );
}
inline ColorVector& ColorVector::operator+=( const ColorVector& ac_roVector )
{
    return operator+=( (Hex)(ac_roVector) );
}
inline ColorVector& ColorVector::operator-=( const ColorVector& ac_roVector )
{
    return operator-=( (Hex)(ac_roVector) );
}
inline ColorVector& ColorVector::operator*=( const ColorVector& ac_roVector )
{
    return operator*=( (Hex)(ac_roVector) );
}
inline ColorVector& ColorVector::operator/=( const ColorVector& ac_roVector )
{
    return operator/=( (Hex)(ac_roVector) );
}

// arithmatic operators for use with color hexes
inline ColorVector ColorVector::operator+( const Hex& ac_rHex ) const
{
    return ColorVector( (Hex)(*this) + ac_rHex );
}
inline ColorVector ColorVector::operator-( const Hex& ac_rHex ) const
{
    return ColorVector( (Hex)(*this) - ac_rHex );
}
inline ColorVector ColorVector::operator*( const Hex& ac_rHex ) const
{
    return ColorVector( (Hex)(*this) * ac_rHex );
}
inline ColorVector ColorVector::operator/( const Hex& ac_rHex ) const
{
    return ColorVector( (Hex)(*this) / ac_rHex );
}
inline ColorVector& ColorVector::operator+=( const Hex& ac_rHex )
{
    *this = (Hex)(*this) + ac_rHex;
    return *this;
}
inline ColorVector& ColorVector::operator-=( const Hex& ac_rHex )
{
    *this = (Hex)(*this) - ac_rHex;
    return *this;
}
inline ColorVector& ColorVector::operator*=( const Hex& ac_rHex )
{
    *this = (Hex)(*this) * ac_rHex;
    return *this;
}
inline ColorVector& ColorVector::operator/=( const Hex& ac_rHex )
{
    *this = (Hex)(*this) / ac_rHex;
    return *this;
}

// Return rgb values as floats
inline float ColorVector::fAlpha() const
{
    return (float)(a) / 0xFF;
}
inline float ColorVector::fRed() const
{
    return (float)(r) / 0xFF;
}
inline float ColorVector::fGreen() const
{
    return (float)(g) / 0xFF;
}
inline float ColorVector::fBlue() const
{
    return (float)(b) / 0xFF;
}

}   // namespace Color

// ColorVector scalar multiplication and division in the other direction
template< typename U >
inline Color::ColorVector
    operator*( const U& ac_roScalar, const Color::ColorVector ac_roVector )
{
    return ac_roVector.operator*( ac_roScalar );
}
template< typename U >
inline Color::ColorVector
    operator/( const U& ac_roScalar, const Color::ColorVector ac_roVector )
{
    return Color::ColorVector().operator*( ac_roScalar ).operator/( ac_roVector );
}

#endif  // COLOR_VECTOR__INL
