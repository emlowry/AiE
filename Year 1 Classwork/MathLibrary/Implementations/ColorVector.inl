/******************************************************************************
 * File:               ColorVector.inl
 * Author:             Elizabeth Lowry
 * Date Created:       December 16, 2013
 * Description:        Inline function implementations for ColorVector class.
 * Last Modified:      February 4, 2014
 * Last Modification:  Switching from regular inline to macro inline.
 ******************************************************************************/

#ifndef COLOR_VECTOR__INL
#define COLOR_VECTOR__INL

#include "Declarations/ColorConstants.h"
#include "Declarations/ColorVector.h"
#include "Declarations/ImExportMacro.h"

// separate file for template functions to keep filesize down
#include "ColorVector_Templates.inl"

namespace Color
{

// Destructor does nothing
INLINE ColorVector::~ColorVector() {}

// Constructors that forward to base class constructors
INLINE ColorVector::ColorVector()
    : BaseType( 0xFF ),
      a( m_aaData[0][0] ),
      r( m_aaData[0][1] ),
      g( m_aaData[0][2] ),
      b( m_aaData[0][3] ) {}
INLINE ColorVector::ColorVector( const ColorVector& ac_roVector )
    : BaseType( ac_roVector ),
      a( m_aaData[0][0] ),
      r( m_aaData[0][1] ),
      g( m_aaData[0][2] ),
      b( m_aaData[0][3] ) {}
INLINE ColorVector::ColorVector( const RootType& ac_roMatrix )
    : BaseType( ac_roMatrix ),
      a( m_aaData[0][0] ),
      r( m_aaData[0][1] ),
      g( m_aaData[0][2] ),
      b( m_aaData[0][3] ) {}
INLINE ColorVector::ColorVector( ColorVector&& a_rroVector )
    : BaseType( std::forward< ColorVector >( a_rroVector ) ),
      a( m_aaData[0][0] ),
      r( m_aaData[0][1] ),
      g( m_aaData[0][2] ),
      b( m_aaData[0][3] ) {}
INLINE ColorVector::ColorVector( const Channel& ac_rFill )
    : BaseType( ac_rFill ),
      a( m_aaData[0][0] ),
      r( m_aaData[0][1] ),
      g( m_aaData[0][2] ),
      b( m_aaData[0][3] ) {}
INLINE ColorVector::ColorVector( const Channel (&ac_raData)[ 4 ] )
    : BaseType( ac_raData ),
      a( m_aaData[0][0] ),
      r( m_aaData[0][1] ),
      g( m_aaData[0][2] ),
      b( m_aaData[0][3] ) {}

// Assignment operators that pass to base class
INLINE ColorVector& ColorVector::operator=( const Channel& ac_rFill )
{
    BaseType::operator=( ac_rFill );
    return *this;
}
INLINE ColorVector& ColorVector::operator=( const Channel (&ac_raData)[ 4 ] )
{
    BaseType::operator=( ac_raData );
    return *this;
}

// Construct from hex value
INLINE ColorVector::ColorVector( Channel a_ucRed,
                                 Channel a_ucGreen,
                                 Channel a_ucBlue,
                                 Channel a_ucAlpha )
    : BaseType(),
      a( m_aaData[0][0] ),
      r( m_aaData[0][1] ),
      g( m_aaData[0][2] ),
      b( m_aaData[0][3] )
{
    a = a_ucAlpha;
    r = a_ucRed;
    g = a_ucGreen;
    b = a_ucBlue;
}
INLINE ColorVector::ColorVector( float a_fRed,
                                 float a_fGreen,
                                 float a_fBlue,
                                 float a_fAlpha )
    : BaseType(),
      a( m_aaData[0][0] ),
      r( m_aaData[0][1] ),
      g( m_aaData[0][2] ),
      b( m_aaData[0][3] )
{
    a = (Channel)( a_fAlpha * 0xFF );
    r = (Channel)( a_fRed * 0xFF );
    g = (Channel)( a_fGreen * 0xFF );
    b = (Channel)( a_fBlue * 0xFF );
}
INLINE ColorVector::ColorVector( FourChannelInt a_uiHex )
    : BaseType(),
      a( m_aaData[0][0] ),
      r( m_aaData[0][1] ),
      g( m_aaData[0][2] ),
      b( m_aaData[0][3] )
{
    a = Hex(a_uiHex).a;
    r = Hex(a_uiHex).r;
    g = Hex(a_uiHex).g;
    b = Hex(a_uiHex).b;
}
INLINE ColorVector::ColorVector( const Hex& ac_rHex )
    : BaseType(),
      a( m_aaData[0][0] ),
      r( m_aaData[0][1] ),
      g( m_aaData[0][2] ),
      b( m_aaData[0][3] )
{
    a = ac_rHex.a;
    r = ac_rHex.r;
    g = ac_rHex.g;
    b = ac_rHex.b;
}

// Assign from or convert to color Hex value
INLINE ColorVector& ColorVector::operator=( FourChannelInt a_uiHex )
{
    return operator=( Hex( a_uiHex ) );
}
INLINE ColorVector& ColorVector::operator=( const Hex& ac_rHex )
{
    a = ac_rHex.a;
    r = ac_rHex.r;
    g = ac_rHex.g;
    b = ac_rHex.b;
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

// Return rgb values as floats
INLINE float ColorVector::fAlpha() const
{
    return (float)(a) / 0xFF;
}
INLINE float ColorVector::fRed() const
{
    return (float)(r) / 0xFF;
}
INLINE float ColorVector::fGreen() const
{
    return (float)(g) / 0xFF;
}
INLINE float ColorVector::fBlue() const
{
    return (float)(b) / 0xFF;
}

}   // namespace Color

#endif  // COLOR_VECTOR__INL
