/******************************************************************************
 * File:               ColorHexValues.h
 * Author:             Elizabeth Lowry
 * Date Created:       December 11, 2013
 * Description:        Enums containing hex values for .
 * Last Modified:      December 11, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef COLOR_HEX_VALUES__H
#define COLOR_HEX_VALUES__H

#include <cstdint>

namespace Color
{

// Convenient union for representing hex values
union Hex
{
    struct
    {
        uint8_t a;
        uint8_t r;
        uint8_t g;
        uint8_t b;
    };
    uint8_t c[4];
    uint32_t i;

    Hex( uint8_t a_r, uint8_t a_g, uint8_t a_b, uint8_t a_a = 0 )
        : a( a_a ), r( a_r ), g( a_g ), b( a_b ) {}
    Hex( uint32_t a_i ) : i( a ) {}
    Hex& operator=( uint32_t a_i )
    {
        i = a_i;
        return *this;
    }
    Hex( uint8_t (&a_c)[4] )
    {
        for( uint8_t ui = 0; ui < 4; ++ui )
        {
            c[ui] = a_c[ui];
        }
    }
    Hex& operator=( uint8_t (&a_c)[4] )
    {
        for( uint8_t ui = 0; ui < 4; ++ui )
        {
            c[ui] = a_c[ui];
        }
        return *this;
    }

    typedef uint8_t (&C)[4];
    operator C() { return c; }
    operator uint32_t&() { return i; }
};

// Hex values for different opacities
enum Opacity : uint32_t
{
    TRANSPARENT =         0x00FFFFFF,
    OPAQUE =              0xFFFFFFFF,
    HALF_OPAQUE =         0x80FFFFFF,
    HALF_TRANSPARENT =    HALF_OPAQUE,
    OPACITY_0_PERCENT =   TRANSPARENT,
    OPACITY_10_PERCENT =  0x1AFFFFFF,
    OPACITY_20_PERCENT =  0x33FFFFFF,
    OPACITY_25_PERCENT =  0x40FFFFFF,
    OPACITY_30_PERCENT =  0x4DFFFFFF,
    OPACITY_1_THIRD =     0x55FFFFFF,
    OPACITY_40_PERCENT =  0x66FFFFFF,
    OPACITY_50_PERCENT =  HALF_OPAQUE,
    OPACITY_60_PERCENT =  0x99FFFFFF,
    OPACITY_2_THIRDS =    0xAAFFFFFF,
    OPACITY_70_PERCENT =  0xB3FFFFFF,
    OPACITY_75_PERCENT =  0xC0FFFFFF,
    OPACITY_80_PERCENT =  0xCCFFFFFF,
    OPACITY_90_PERCENT =  0xE6FFFFFF,
    OPACITY_100_PERCENT = OPAQUE,
};

enum GrayScale : uint32_t
{
    BLACK = 0xFF000000,
    WHITE = 0xFFFFFFFF,
    GRAY =  0xFF808080,
    SILVER = 0xFFC0C0C0,
    DARK_GREY = 0xFF404040,
    RED = 0xFFFF0000,
    HALF_RED = 0xFF800000,
    GREEN = 0xFF00FF00,
    HALF_GREEN = 0xFF00FF00,
    HALF_GREEN = 0xFF008000,
    BLUE = 0xFF0000FF,

    YELLOW = RED | GREEN,

};

}   // namespace Color

#endif  // COLOR_HEX_VALUES__H
