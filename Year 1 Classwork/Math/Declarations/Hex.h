/******************************************************************************
 * File:               Hex.h
 * Author:             Elizabeth Lowry
 * Date Created:       December 16, 2013
 * Description:        A union for representing color hex values.
 * Last Modified:      December 16, 2013
 * Last Modification:  Split off from ColorHexValues.h.
 ******************************************************************************/

#ifndef HEX__H
#define HEX__H

#include <cstdint>

namespace Color
{

typedef uint8_t Channel;
typedef uint32_t FourChannelInt;

// Convenient union for representing color hex values
// Cast to uint32_t for arithmatic operations.
union Hex
{
    // Members of the union
    struct
    {
        Channel a;
        Channel r;
        Channel g;
        Channel b;
    };
    Channel c[4];
    FourChannelInt i;

    // Union constructors and assignment operators
    Hex() : i( 0xFF000000 ) {}
    Hex( Channel a_r, Channel a_g, Channel a_b, Channel a_a = 0xFF )
        : a( a_a ), r( a_r ), g( a_g ), b( a_b ) {}
    Hex( float a_r, float a_g, float a_b, float a_a = 1.0 )
        : a( a_a < 0.0 ? 0 : a_a > 1.0 ? 0xFF : (Channel)( a_a * 0xFF ) ),
          r( a_r < 0.0 ? 0 : a_r > 1.0 ? 0xFF : (Channel)( a_r * 0xFF ) ),
          g( a_g < 0.0 ? 0 : a_g > 1.0 ? 0xFF : (Channel)( a_g * 0xFF ) ),
          b( a_b < 0.0 ? 0 : a_b > 1.0 ? 0xFF : (Channel)( a_b * 0xFF ) ) {}
    Hex( FourChannelInt a_i ) : i( a ) {}
    Hex& operator=( FourChannelInt a_i )
    {
        i = a_i;
        return *this;
    }
    Hex( const Channel (&ac_aC)[4] )
    {
        for( Channel ui = 0; ui < 4; ++ui )
        {
            c[ui] = ac_aC[ui];
        }
    }
    Hex& operator=( const Channel (&ac_aC)[4] )
    {
        for( Channel ui = 0; ui < 4; ++ui )
        {
            c[ui] = ac_aC[ui];
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

    // bitwise operations
    Hex operator~() const
    {
        return Hex( ~r, ~g, ~b, a );
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

    // arithmatic assign-operations
    Hex& operator+=( const Hex& ac_rHex )
    {
        float fA = (float)(ac_rHex.a) / 0xFF;
        r += ( fA * ac_rHex.r <= 0xFF - r )
                ? (Channel)( fA * ac_rHex.r ) : 0xFF - r;
        g += ( fA * ac_rHex.g <= 0xFF - g )
                ? (Channel)( fA * ac_rHex.g ) : 0xFF - g;
        b += ( fA * ac_rHex.b <= 0xFF - b )
                ? (Channel)( fA * ac_rHex.b ) : 0xFF - b;
        return *this;
    }
    Hex& operator-=( const Hex& ac_rHex )
    {
        float fA = (float)(ac_rHex.a) / 0xFF;
        r -= ( fA * ac_rHex.r < r ) ? (Channel)( fA * ac_rHex.r ) : r;
        g -= ( fA * ac_rHex.g < g ) ? (Channel)( fA * ac_rHex.g ) : g;
        b -= ( fA * ac_rHex.b < b ) ? (Channel)( fA * ac_rHex.b ) : b;
        return *this;
    }
    Hex& operator*=( const Hex& ac_rHex )
    {
        float fA = (float)(ac_rHex.a) / 0xFF;
        r = (Channel)( ( 1.0f - fA + ( fA * (float)(ac_rHex.r) / 0xFF ) ) * r );
        g = (Channel)( ( 1.0f - fA + ( fA * (float)(ac_rHex.g) / 0xFF ) ) * g );
        b = (Channel)( ( 1.0f - fA + ( fA * (float)(ac_rHex.b) / 0xFF ) ) * b );
        return *this;
    }
    Hex& operator/=( const Hex& ac_rHex )
    {
        float fA = (float)(ac_rHex.a) / 0xFF;
        float fOff = ( 1.0f - fA ) * 0xFF;
        r = ( fOff + ( ac_rHex.r * fA ) <= r )
            ? 0xFF : (Channel)( ( (float)(r) * 0xFF ) /
                                ( fOff + ( fA * ac_rHex.r ) ) );
        g = ( fOff + ( ac_rHex.g * fA ) <= g )
            ? 0xFF : (Channel)( ( (float)(g) * 0xFF ) /
                                ( fOff + ( fA * ac_rHex.g ) ) );
        b = ( fOff + ( ac_rHex.b * fA ) <= b )
            ? 0xFF : (Channel)( ( (float)(b) * 0xFF ) /
                                ( fOff + ( fA * ac_rHex.b ) ) );
        return *this;
    }
    template< typename T >
    Hex& operator*=( const T& ac_rScalar )
    {
        if( ac_rScalar < 0 )
        {
            i = ~i;
            a = ~a;
            return operator*= ac_rScalar * -1;
        }
        r = ( ac_rScalar >= ( 255.0f / r ) )
                ? 0xFF : (Channel)( ac_rScalar * r );
        g = ( ac_rScalar >= ( 255.0f / g ) )
                ? 0xFF : (Channel)( ac_rScalar * g );
        b = ( ac_rScalar >= ( 255.0f / b ) )
                ? 0xFF : (Channel)( ac_rScalar * b );
        return *this;
    }
    template< typename T >
    Hex& operator/=( const T& ac_scalar )
    {
        if( ac_rScalar < 0 )
        {
            i = ~i;
            a = ~a;
            return operator*= ac_rScalar * -1;
        }
        r = ( ac_rScalar <= ( (float)(r) / 0xFF ) ) ? 0xFF : ( r / ac_rScalar );
        g = ( ac_rScalar <= ( (float)(g) / 0xFF ) ) ? 0xFF : ( g / ac_rScalar );
        b = ( ac_rScalar <= ( (float)(b) / 0xFF ) ) ? 0xFF : ( b / ac_rScalar );
        return *this;
    }

    // arithmatic operations
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

};  // union Hex

}   // namespace Color

#endif  // HEX__H
