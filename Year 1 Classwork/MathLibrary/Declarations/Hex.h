/******************************************************************************
 * File:               Hex.h
 * Author:             Elizabeth Lowry
 * Date Created:       December 16, 2013
 * Description:        A union for representing color hex values.
 * Last Modified:      February 25, 2014
 * Last Modification:  Changed how constructor handles float parameters.
 ******************************************************************************/

#ifndef HEX__H
#define HEX__H

#include "Functions.h"
#include <algorithm>
#include <cstdint>

#define LITTLE_ENDIAN 0x41424344UL 
#define BIG_ENDIAN    0x44434241UL
#define PDP_ENDIAN    0x42414443UL
#define REVERSE_PDP_ENDIAN    0x43444142UL
#define ENDIAN_ORDER  ('ABCD') 

namespace Color
{

typedef uint8_t Channel;
typedef uint32_t FourChannelInt;

// Convenient union for representing color hex values
// Cast to uint32_t for arithmatic operations.
union Hex
{
    // Members of the union
    FourChannelInt i;
    Channel c[4];   // be sure you know system endianness if you use this member
    struct
    {
#if ENDIAN_ORDER==LITTLE_ENDIAN
        Channel b;
        Channel g;
        Channel r;
        Channel a;
#elif ENDIAN_ORDER==BIG_ENDIAN
        Channel a;
        Channel r;
        Channel g;
        Channel b;
#elif ENDIAN_ORDER==PDP_ENDIAN
        Channel g;
        Channel b;
        Channel a;
        Channel r;
#elif ENDIAN_ORDER==REVERSE_PDP_ENDIAN
        Channel r;
        Channel a;
        Channel b;
        Channel g;
#else
    #error "Unrecognizeable byte order - unable to compile color hex union"
#endif
    };

    // Union constructors and assignment operators
    // For some reason, none of these compile if I implement them externally.
    Hex() : i( 0xFF000000 ) {}
    Hex( Channel a_r, Channel a_g, Channel a_b, Channel a_a = 0xFF )
        : a( a_a ), r( a_r ), g( a_g ), b( a_b ) {}
    Hex( float a_r, float a_g, float a_b, float a_a = 1.0 )
        : a( a_a < 0.0 ? 0
            : a_a > 1.0 ? 0xFF
            : (Channel)Math::Round( a_a * 0xFF ) ),
          r( a_r < 0.0 ? 0
            : a_r > 1.0 ? 0xFF
            : (Channel)Math::Round( a_r * 0xFF ) ),
          g( a_g < 0.0 ? 0
            : a_g > 1.0 ? 0xFF
            : (Channel)Math::Round( a_g * 0xFF ) ),
          b( a_b < 0.0 ? 0
            : a_b > 1.0 ? 0xFF
            : (Channel)Math::Round( a_b * 0xFF ) ) {}
    Hex( FourChannelInt a_i ) : i( a_i ) {}
    Hex& operator=( FourChannelInt a_i )
    {
        i = a_i;
        return *this;
    }

    // be sure you know system endianness if you assign/construct from an array
    Hex( const Channel (&ac_aC)[4] )
    {
        for( unsigned int i = 0; i < 4; ++i )
        {
            c[i] = ac_aC[i];
        }
    }
    Hex& operator=( const Channel (&ac_aC)[4] )
    {
        for( unsigned int i = 0; i < 4; ++i )
        {
            c[i] = ac_aC[i];
        }
        return *this;
    }

    // conversion operators
    typedef Channel (&C)[4];
    operator C() { return c; }
    operator FourChannelInt&() { return i; }

    // bitwise assign-operations
    Hex& operator&=( const Hex& ac_rHex )
    {
        i &= ac_rHex.i;
        return *this;
    }
    Hex& operator|=( const Hex& ac_rHex )
    {
        i |= ac_rHex.i;
        return *this;
    }
    Hex& operator^=( const Hex& ac_rHex )
    {
        i ^= ac_rHex.i;
        return *this;
    }
    Hex& operator<<=( unsigned char a_ucBits )
    {
        a <<= a_ucBits;
        r <<= a_ucBits;
        g <<= a_ucBits;
        b <<= a_ucBits;
        return *this;
    }
    Hex& operator>>=( unsigned char a_ucBits )
    {
        a >>= a_ucBits;
        r >>= a_ucBits;
        g >>= a_ucBits;
        b >>= a_ucBits;
        return *this;
    }

    // bitwise operations
    Hex operator~() const
    {
        return Hex( ~i );
    }
    Hex operator&( const Hex& ac_rHex ) const
    {
        return Hex( i & ac_rHex.i );
    }
    Hex operator|( const Hex& ac_rHex ) const
    {
        return Hex( i | ac_rHex.i );
    }
    Hex operator^( const Hex& ac_rHex ) const
    {
        return Hex( i ^ ac_rHex.i );
    }
    Hex operator<<( unsigned char a_ucBits ) const
    {
        return Hex( (Channel)( r << a_ucBits ),
                    (Channel)( g << a_ucBits ),
                    (Channel)( b << a_ucBits ),
                    (Channel)( a << a_ucBits ) );
    }
    Hex operator>>( unsigned char a_ucBits ) const
    {
        return Hex( (Channel)( r >> a_ucBits ),
                    (Channel)( g >> a_ucBits ),
                    (Channel)( b >> a_ucBits ),
                    (Channel)( a >> a_ucBits ) );
    }

    // arithmatic assign-operations
    Hex& operator+=( const Hex& ac_rHex )
    {
        a += ( ac_rHex.a > 0xFF - a ? 0xFF - a : ac_rHex.a );
        r += ( ac_rHex.r > 0xFF - r ? 0xFF - r : ac_rHex.r );
        g += ( ac_rHex.g > 0xFF - g ? 0xFF - g : ac_rHex.g );
        b += ( ac_rHex.b > 0xFF - b ? 0xFF - b : ac_rHex.b );
        return *this;
    }
    Hex& operator-=( const Hex& ac_rHex )
    {
        a -= ( ac_rHex.a > a ? a : ac_rHex.a );
        r -= ( ac_rHex.r > r ? r : ac_rHex.r );
        g -= ( ac_rHex.g > g ? g : ac_rHex.g );
        b -= ( ac_rHex.b > b ? b : ac_rHex.b );
        return *this;
    }
    Hex& operator*=( const Hex& ac_rHex )
    {
        a = (Channel)( a * (float)ac_rHex.a / 0xFF );
        r = (Channel)( r * (float)ac_rHex.r / 0xFF );
        g = (Channel)( g * (float)ac_rHex.g / 0xFF );
        b = (Channel)( b * (float)ac_rHex.b / 0xFF );
        return *this;
    }
    Hex& operator/=( const Hex& ac_rHex )
    {
        a = ( ac_rHex.a == 0x00
              ? 0xFF : (Channel)std::min( 255.0f, 255.0f * a / ac_rHex.a ) );
        r = ( ac_rHex.r == 0x00
              ? 0xFF : (Channel)std::min( 255.0f, 255.0f * r / ac_rHex.r ) );
        g = ( ac_rHex.g == 0x00
              ? 0xFF : (Channel)std::min( 255.0f, 255.0f * g / ac_rHex.g ) );
        b = ( ac_rHex.b == 0x00
              ? 0xFF : (Channel)std::min( 255.0f, 255.0f * b / ac_rHex.b ) );
        return *this;
    }
    template< typename T >
    Hex& operator*=( const T& ac_rScalar )
    {
        if( ac_rScalar < 0 )
        {
            *this = ~(*this);
            return operator*=( ac_rScalar * -1 );
        }
        a = (Channel)std::min( 0xFF, a * ac_rScalar );
        r = (Channel)std::min( 0xFF, r * ac_rScalar );
        g = (Channel)std::min( 0xFF, g * ac_rScalar );
        b = (Channel)std::min( 0xFF, b * ac_rScalar );
        return *this;
    }
    template< typename T >
    Hex& operator/=( const T& ac_scalar )
    {
        if( ac_rScalar < 0 )
        {
            *this = ~(*this);
            return operator*=( ac_rScalar * -1 );
        }
        a = ( ac_rScalar == (T)0
              ? 0xFF : (Channel)std::min( 0xFF, a / ac_rScalar ) );
        r = ( ac_rScalar == (T)0
              ? 0xFF : (Channel)std::min( 0xFF, r / ac_rScalar ) );
        g = ( ac_rScalar == (T)0
              ? 0xFF : (Channel)std::min( 0xFF, g / ac_rScalar ) );
        b = ( ac_rScalar == (T)0
              ? 0xFF : (Channel)std::min( 0xFF, b / ac_rScalar ) );
        return *this;
    }

    // arithmatic operations
    Hex operator-() const
    {
        return operator*( -1 );
    }
    Hex operator+( const Hex& ac_rHex ) const
    {
        Hex result = *this;
        result += ac_rHex;
        return result;
    }
    Hex operator-( const Hex& ac_rHex ) const
    {
        Hex result = *this;
        result -= ac_rHex;
        return result;
    }
    Hex operator*( const Hex& ac_rHex ) const
    {
        Hex result = *this;
        result *= ac_rHex;
        return result;
    }
    Hex operator/( const Hex& ac_rHex ) const
    {
        Hex result = *this;
        result /= ac_rHex;
        return result;
    }
    template< typename T >
    Hex operator*( const T& ac_rScalar ) const
    {
        Hex result = *this;
        result *= ac_rScalar;
        return result;
    }
    template< typename T >
    Hex operator/( const T& ac_rScalar ) const
    {
        Hex result = *this;
        result /= ac_rScalar;
        return result;
    }

    // get channels as floats
    float fA() const { return (float)a / 0xFF; }
    float fR() const { return (float)r / 0xFF; }
    float fG() const { return (float)g / 0xFF; }
    float fB() const { return (float)b / 0xFF; }

};  // union Hex

}   // namespace Color

#endif  // HEX__H
