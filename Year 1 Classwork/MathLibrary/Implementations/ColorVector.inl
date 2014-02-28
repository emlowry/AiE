/******************************************************************************
 * File:               ColorVector.inl
 * Author:             Elizabeth Lowry
 * Date Created:       December 16, 2013
 * Description:        Inline function implementations for ColorVector class.
 * Last Modified:      February 27, 2014
 * Last Modification:  Adding functions.
 ******************************************************************************/

#ifndef COLOR_VECTOR__INL
#define COLOR_VECTOR__INL

#include "../Declarations/ColorConstants.h"
#include "../Declarations/ColorVector.h"
#include "../Declarations/Functions.h"
#include "../Declarations/ImExportMacro.h"

// separate file for template functions to keep filesize down
#include "ColorVector_Templates.inl"

namespace Color
{

// Destructor does nothing
INLINE ColorVector::~ColorVector() {}

// Constructors that forward to base class constructors
INLINE ColorVector::ColorVector()
    : BaseType( 1.0f ),
      r( m_aaData[0][0] ),
      g( m_aaData[0][1] ),
      b( m_aaData[0][2] ),
      a( m_aaData[0][3] ) {}
INLINE ColorVector::ColorVector( const ColorVector& ac_roVector )
    : BaseType( ac_roVector ),
      r( m_aaData[0][0] ),
      g( m_aaData[0][1] ),
      b( m_aaData[0][2] ),
      a( m_aaData[0][3] ) {}
INLINE ColorVector::ColorVector( const RootType& ac_roMatrix )
    : BaseType( ac_roMatrix ),
      r( m_aaData[0][0] ),
      g( m_aaData[0][1] ),
      b( m_aaData[0][2] ),
      a( m_aaData[0][3] ) {}
INLINE ColorVector::ColorVector( ColorVector&& a_rroVector )
    : BaseType( std::forward< ColorVector >( a_rroVector ) ),
      r( m_aaData[0][0] ),
      g( m_aaData[0][1] ),
      b( m_aaData[0][2] ),
      a( m_aaData[0][3] ) {}
INLINE ColorVector::ColorVector( float a_fFill )
    : BaseType( a_fFill ),
      r( m_aaData[0][0] ),
      g( m_aaData[0][1] ),
      b( m_aaData[0][2] ),
      a( m_aaData[0][3] ) {}
INLINE ColorVector::ColorVector( const float (&ac_rafData)[ 4 ] )
    : BaseType( ac_rafData ),
      r( m_aaData[0][0] ),
      g( m_aaData[0][1] ),
      b( m_aaData[0][2] ),
      a( m_aaData[0][3] ) {}

// Assignment operators that pass to base class
INLINE ColorVector& ColorVector::operator=( float a_fFill )
{
    BaseType::operator=( a_fFill );
    return *this;
}
INLINE ColorVector& ColorVector::operator=( const float (&ac_rafData)[ 4 ] )
{
    BaseType::operator=( ac_rafData );
    return *this;
}

// Construct from hex value
INLINE ColorVector::ColorVector( Channel a_ucRed,
                                 Channel a_ucGreen,
                                 Channel a_ucBlue,
                                 Channel a_ucAlpha )
    : BaseType(),
      r( m_aaData[0][0] ),
      g( m_aaData[0][1] ),
      b( m_aaData[0][2] ),
      a( m_aaData[0][3] )
{
    r = (float)a_ucRed / 0xFF;
    g = (float)a_ucGreen / 0xFF;
    b = (float)a_ucBlue / 0xFF;
    a = (float)a_ucAlpha / 0xFF;
}
INLINE ColorVector::ColorVector( float a_fRed,
                                 float a_fGreen,
                                 float a_fBlue,
                                 float a_fAlpha )
    : BaseType(),
      r( m_aaData[0][0] ),
      g( m_aaData[0][1] ),
      b( m_aaData[0][2] ),
      a( m_aaData[0][3] )
{
    r = a_fRed;
    g = a_fGreen;
    b = a_fBlue;
    a = a_fAlpha;
}
INLINE ColorVector::ColorVector( FourChannelInt a_uiHex )
    : BaseType(),
      r( m_aaData[0][0] ),
      g( m_aaData[0][1] ),
      b( m_aaData[0][2] ),
      a( m_aaData[0][3] )
{
    r = (float)( Hex(a_uiHex).r ) / 0xFF;
    g = (float)( Hex(a_uiHex).g ) / 0xFF;
    b = (float)( Hex(a_uiHex).b ) / 0xFF;
    a = (float)( Hex(a_uiHex).a ) / 0xFF;
}
INLINE ColorVector::ColorVector( const Hex& ac_rHex )
    : BaseType(),
      r( m_aaData[0][0] ),
      g( m_aaData[0][1] ),
      b( m_aaData[0][2] ),
      a( m_aaData[0][3] )
{
    r = (float)( ac_rHex.r ) / 0xFF;
    g = (float)( ac_rHex.g ) / 0xFF;
    b = (float)( ac_rHex.b ) / 0xFF;
    a = (float)( ac_rHex.a ) / 0xFF;
}

// Assign from or convert to color Hex value
INLINE ColorVector& ColorVector::operator=( FourChannelInt a_uiHex )
{
    return operator=( Hex( a_uiHex ) );
}
INLINE ColorVector& ColorVector::operator=( const Hex& ac_rHex )
{
    r = (float)( ac_rHex.r ) / 0xFF;
    g = (float)( ac_rHex.g ) / 0xFF;
    b = (float)( ac_rHex.b ) / 0xFF;
    a = (float)( ac_rHex.a ) / 0xFF;
    return *this;
}
INLINE ColorVector::operator Hex() const
{
    return Hex( r, g, b, a );
}

// Bitwise operators
INLINE ColorVector ColorVector::operator~() const
{
    return ColorVector( ~( (Hex)(*this) ) );
}
INLINE ColorVector ColorVector::operator&( const ColorVector& ac_roVector ) const
{
    return operator&( (Hex)ac_roVector );
}
INLINE ColorVector ColorVector::operator|( const ColorVector& ac_roVector ) const
{
    return operator|( (Hex)ac_roVector );
}
INLINE ColorVector ColorVector::operator^( const ColorVector& ac_roVector ) const
{
    return operator^( (Hex)ac_roVector );
}
INLINE ColorVector
    ColorVector::operator&( const Hex& ac_roHex ) const
{
    return ColorVector( (Hex)(*this) & ac_roHex );
}
INLINE ColorVector
    ColorVector::operator|( const Hex& ac_roHex ) const
{
    return ColorVector( (Hex)(*this) | ac_roHex );
}
INLINE ColorVector
    ColorVector::operator^( const Hex& ac_roHex ) const
{
    return ColorVector( (Hex)(*this) ^ ac_roHex );
}
INLINE ColorVector
    ColorVector::operator<<( unsigned char a_ucBits ) const
{
    return ColorVector( (Hex)(*this) << a_ucBits );
}
INLINE ColorVector
    ColorVector::operator>>( unsigned char a_ucBits ) const
{
    return ColorVector( (Hex)(*this) << a_ucBits );
}
INLINE ColorVector& ColorVector::operator&=( const ColorVector& ac_roVector )
{
    return operator&=( (Hex)ac_roVector );
}
INLINE ColorVector& ColorVector::operator|=( const ColorVector& ac_roVector )
{
    return operator|=( (Hex)ac_roVector );
}
INLINE ColorVector& ColorVector::operator^=( const ColorVector& ac_roVector )
{
    return operator^=( (Hex)ac_roVector );
}
INLINE ColorVector& ColorVector::operator&=( const Hex& ac_roHex )
{
    return operator=( (Hex)(*this) & ac_roHex );
}
INLINE ColorVector& ColorVector::operator|=( const Hex& ac_roHex )
{
    return operator=( (Hex)(*this) | ac_roHex );
}
INLINE ColorVector& ColorVector::operator^=( const Hex& ac_roHex )
{
    return operator=( (Hex)(*this) ^ ac_roHex );
}
INLINE ColorVector& ColorVector::operator<<=( unsigned char a_ucBits )
{
    return operator=( (Hex)(*this) << a_ucBits );
}
INLINE ColorVector& ColorVector::operator>>=( unsigned char a_ucBits )
{
    return operator=( (Hex)(*this) >> a_ucBits );
}

// Return rgb values as 8-bit channel values
INLINE Channel ColorVector::AlphaChannel() const
{
    return 0.0f > a ? 0x00
        : 1.0f < a ? 0xFF
        : (Channel)Math::Round( a * 0xFF );
}
INLINE Channel ColorVector::RedChannel() const
{
    return 0.0f > r ? 0x00
        : 1.0f < r ? 0xFF
        : (Channel)Math::Round( r * 0xFF );
}
INLINE Channel ColorVector::GreenChannel() const
{
    return 0.0f > g ? 0x00
        : 1.0f < g ? 0xFF
        : (Channel)Math::Round( g * 0xFF );
}
INLINE Channel ColorVector::BlueChannel() const
{
    return 0.0f > b ? 0x00
        : 1.0f < b ? 0xFF
        : (Channel)Math::Round( b * 0xFF );
}

// Set individual rgba values using 8-bit channel values
INLINE ColorVector& ColorVector::AlphaChannel( Channel a_ucAlpha )
{
    a = (float)a_ucAlpha / 255.0f;
    return *this;
}
INLINE ColorVector& ColorVector::RedChannel( Channel a_ucRed )
{
    r = (float)a_ucRed / 255.0f;
    return *this;
}
INLINE ColorVector& ColorVector::GreenChannel( Channel a_ucGreen )
{
    g = (float)a_ucGreen / 255.0f;
    return *this;
}
INLINE ColorVector& ColorVector::BlueChannel( Channel a_ucBlue )
{
    b = (float)a_ucBlue / 255.0f;
    return *this;
}

}   // namespace Color

#endif  // COLOR_VECTOR__INL
