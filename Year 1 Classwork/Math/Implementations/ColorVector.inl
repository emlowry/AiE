/******************************************************************************
 * File:               ColorVector.inl
 * Author:             Elizabeth Lowry
 * Date Created:       December 16, 2013
 * Description:        Inline function implementations for ColorVector class.
 * Last Modified:      January 5, 2014
 * Last Modification:  Redistributed implementations between this file and other
 *                      inl files.
 ******************************************************************************/

#ifndef COLOR_VECTOR__INL
#define COLOR_VECTOR__INL

#include "Declarations/ColorConstants.h"
#include "Declarations/ColorVector.h"

// separate file for template functions to keep filesize down
#include "ColorVector_Templates.inl"

namespace Color
{

// Destructor does nothing
inline ColorVector::~ColorVector() {}

// Constructors that forward to base class constructors
inline ColorVector::ColorVector()
    : BaseType( 0xFF ), a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) ) {}
inline ColorVector::ColorVector( const ColorVector& ac_roVector )
    : BaseType( ac_roVector ), a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) ) {}
inline ColorVector::ColorVector( const BaseType& ac_roVector )
    : BaseType( ac_roVector ), a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) ) {}
inline ColorVector::ColorVector( const VectorBaseType& ac_roVector )
    : BaseType( ac_roVector ), a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) ) {}
inline ColorVector::ColorVector( const RootType& ac_roMatrix )
    : BaseType( ac_roMatrix ), a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) ) {}
inline ColorVector::ColorVector( ColorVector&& a_rroVector )
    : BaseType( std::forward< ColorVector >( a_rroVector ) ),
      a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) ) {}
inline ColorVector::ColorVector( BaseType&& a_rroVector )
    : BaseType( std::forward< BaseType >( a_rroVector ) ),
      a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) ) {}
inline ColorVector::ColorVector( VectorBaseType&& a_rroVector )
    : BaseType( std::forward< VectorBaseType >( a_rroVector ) ),
      a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) ) {}
inline ColorVector::ColorVector( RootType&& a_rroMatrix )
    : BaseType( std::forward< RootType >( a_rroMatrix ) ),
      a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) ) {}
inline ColorVector::ColorVector( const Channel& ac_rFill )
    : BaseType( ac_rFill ), a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) ) {}
inline ColorVector::ColorVector( const Channel (&ac_raData)[ 4 ] )
    : BaseType( ac_raData ), a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) ) {}
inline ColorVector::ColorVector( const Channel* const ac_cpData,
                                 const unsigned int ac_uiSize,
                                 const Channel& ac_rFill )
    : BaseType( ac_cpData, ac_uiSize, ac_rFill ),
      a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) ) {}

// Construct from hex value
inline ColorVector::ColorVector( Channel a_ucRed,
                                 Channel a_ucGreen,
                                 Channel a_ucBlue,
                                 Channel a_ucAlpha )
    : a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) )
{
    a = a_ucAlpha;
    r = a_ucRed;
    g = a_ucGreen;
    b = a_ucBlue;
}
inline ColorVector::ColorVector( float a_fRed,
                                 float a_fGreen,
                                 float a_fBlue,
                                 float a_fAlpha )
    : a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) )
{
    a = (Channel)( a_fAlpha * 0xFF );
    r = (Channel)( a_fRed * 0xFF );
    g = (Channel)( a_fGreen * 0xFF );
    b = (Channel)( a_fBlue * 0xFF );
}
inline ColorVector::ColorVector( FourChannelInt a_uiHex )
    : a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) )
{
    a = Hex(a_uiHex).a;
    r = Hex(a_uiHex).r;
    g = Hex(a_uiHex).g;
    b = Hex(a_uiHex).b;
}
inline ColorVector::ColorVector( const Hex& ac_rHex )
    : a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) )
{
    a = ac_rHex.a;
    r = ac_rHex.r;
    g = ac_rHex.g;
    b = ac_rHex.b;
}

// Assign from or convert to color Hex value
inline ColorVector& ColorVector::operator=( FourChannelInt a_uiHex )
{
    return operator=( Hex( a_uiHex ) );
}
inline ColorVector& ColorVector::operator=( const Hex& ac_rHex )
{
    a = ac_rHex.a;
    r = ac_rHex.r;
    g = ac_rHex.g;
    b = ac_rHex.b;
    return *this;
}
inline ColorVector::operator Hex() const
{
    return Hex( r, g, b, a );
}

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

#endif  // COLOR_VECTOR__INL
