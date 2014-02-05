/******************************************************************************
 * File:               ColorConstants.h
 * Author:             Elizabeth Lowry
 * Date Created:       December 16, 2013
 * Description:        Constant Hex values for various colors.
 * Last Modified:      January 5, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

#ifndef COLOR_CONSTANTS__H
#define COLOR_CONSTANTS__H

#include "Hex.h"

namespace Color
{

// Hex values for different opacities
const Hex OPAQUE =      0xFFFFFFFF;
const Hex TRANSPARENT = 0x00FFFFFF;
namespace Opacity
{
    using Color::OPAQUE;
    using Color::TRANSPARENT;

    const Hex ONE_QUARTER =     0x3FFFFFFF;
    const Hex ONE_THIRD =       0x55FFFFFF;
    const Hex HALF =            0x7FFFFFFF;
    const Hex ONE_HALF =        HALF;
    const Hex TWO_THIRDS =      0xAAFFFFFF;
    const Hex THREE_QUARTERS =  0xBFFFFFFF;

    const Hex PERCENT_0 =       TRANSPARENT;
    const Hex PERCENT_10 =      0x1AFFFFFF;
    const Hex PERCENT_20 =      0x33FFFFFF;
    const Hex PERCENT_25 =      ONE_QUARTER;
    const Hex PERCENT_30 =      0x4DFFFFFF;
    const Hex PERCENT_33 =      ONE_THIRD;
    const Hex PERCENT_40 =      0x66FFFFFF;
    const Hex PERCENT_50 =      HALF;
    const Hex PERCENT_60 =      0x99FFFFFF;
    const Hex PERCENT_66 =      TWO_THIRDS;
    const Hex PERCENT_70 =      0xB3FFFFFF;
    const Hex PERCENT_75 =      THREE_QUARTERS;
    const Hex PERCENT_80 =      0xCCFFFFFF;
    const Hex PERCENT_90 =      0xE6FFFFFF;
    const Hex PERCENT_100 =     OPAQUE;
}   // namespace Opacity

// Hex values for different grayscale values
const Hex WHITE =       0xFFFFFFFF;
const Hex BLACK =       0xFF000000;
namespace  GrayScale
{
    using Color::BLACK;
    using Color::WHITE;

    const Hex ONE_QUARTER =     0xFF3F3F3F;
    const Hex ONE_THIRD =       0xFF555555;
    const Hex HALF =            0xFF7F7F7F;
    const Hex ONE_HALF =        HALF;
    const Hex TWO_THIRDS =      0xFFAAAAAA;
    const Hex THREE_QUARTERS =  0xFFBFBFBF;

    const Hex PERCENT_0 =       BLACK;
    const Hex PERCENT_10 =      0xFF1A1A1A;
    const Hex PERCENT_20 =      0xFF333333;
    const Hex PERCENT_25 =      ONE_QUARTER;
    const Hex PERCENT_30 =      0xFF4D4D4D;
    const Hex PERCENT_33 =      ONE_THIRD;
    const Hex PERCENT_40 =      0xFF666666;
    const Hex PERCENT_50 =      HALF;
    const Hex PERCENT_60 =      0xFF999999;
    const Hex PERCENT_66 =      TWO_THIRDS;
    const Hex PERCENT_70 =      0xFFB3B3B3;
    const Hex PERCENT_75 =      THREE_QUARTERS;
    const Hex PERCENT_80 =      0xFFCCCCCC;
    const Hex PERCENT_90 =      0xFFE6E6E6;
    const Hex PERCENT_100 =     WHITE;
}   // namespace Grayscale

// Hex values for different shades of red
const Hex RED = 0xFFFF0000;
namespace Red
{
    using Color::RED;

    const Hex ONE_QUARTER =     RED & GrayScale::ONE_QUARTER;
    const Hex ONE_THIRD =       RED & GrayScale::ONE_THIRD;
    const Hex HALF =            RED & GrayScale::HALF;
    const Hex ONE_HALF =        HALF;
    const Hex TWO_THIRDS =      RED & GrayScale::TWO_THIRDS;
    const Hex THREE_QUARTERS =  RED & GrayScale::THREE_QUARTERS;

    const Hex PERCENT_0 =       BLACK;
    const Hex PERCENT_10 =      RED & GrayScale::PERCENT_10;
    const Hex PERCENT_20 =      RED & GrayScale::PERCENT_20;
    const Hex PERCENT_25 =      ONE_QUARTER;
    const Hex PERCENT_30 =      RED & GrayScale::PERCENT_30;
    const Hex PERCENT_33 =      ONE_THIRD;
    const Hex PERCENT_40 =      RED & GrayScale::PERCENT_40;
    const Hex PERCENT_50 =      HALF;
    const Hex PERCENT_60 =      RED & GrayScale::PERCENT_60;
    const Hex PERCENT_66 =      TWO_THIRDS;
    const Hex PERCENT_70 =      RED & GrayScale::PERCENT_70;
    const Hex PERCENT_75 =      THREE_QUARTERS;
    const Hex PERCENT_80 =      RED & GrayScale::PERCENT_80;
    const Hex PERCENT_90 =      RED & GrayScale::PERCENT_90;
    const Hex PERCENT_100 =     RED;
}   // namespace Red

// Hex values for different shades of green
const Hex GREEN = 0xFF00FF00;
namespace Green
{
    using Color::GREEN;

    const Hex ONE_QUARTER =     GREEN & GrayScale::ONE_QUARTER;
    const Hex ONE_THIRD =       GREEN & GrayScale::ONE_THIRD;
    const Hex HALF =            GREEN & GrayScale::HALF;
    const Hex ONE_HALF =        HALF;
    const Hex TWO_THIRDS =      GREEN & GrayScale::TWO_THIRDS;
    const Hex THREE_QUARTERS =  GREEN & GrayScale::THREE_QUARTERS;

    const Hex PERCENT_0 =       BLACK;
    const Hex PERCENT_10 =      GREEN & GrayScale::PERCENT_10;
    const Hex PERCENT_20 =      GREEN & GrayScale::PERCENT_20;
    const Hex PERCENT_25 =      ONE_QUARTER;
    const Hex PERCENT_30 =      GREEN & GrayScale::PERCENT_30;
    const Hex PERCENT_33 =      ONE_THIRD;
    const Hex PERCENT_40 =      GREEN & GrayScale::PERCENT_40;
    const Hex PERCENT_50 =      HALF;
    const Hex PERCENT_60 =      GREEN & GrayScale::PERCENT_60;
    const Hex PERCENT_66 =      TWO_THIRDS;
    const Hex PERCENT_70 =      GREEN & GrayScale::PERCENT_70;
    const Hex PERCENT_75 =      THREE_QUARTERS;
    const Hex PERCENT_80 =      GREEN & GrayScale::PERCENT_80;
    const Hex PERCENT_90 =      GREEN & GrayScale::PERCENT_90;
    const Hex PERCENT_100 =     GREEN;
}   // namespace Green

// Hex values for different shades of blue
const Hex BLUE = 0xFF0000FF;
namespace Blue
{
    using Color::BLUE;

    const Hex ONE_QUARTER =     BLUE & GrayScale::ONE_QUARTER;
    const Hex ONE_THIRD =       BLUE & GrayScale::ONE_THIRD;
    const Hex HALF =            BLUE & GrayScale::HALF;
    const Hex ONE_HALF =        HALF;
    const Hex TWO_THIRDS =      BLUE & GrayScale::TWO_THIRDS;
    const Hex THREE_QUARTERS =  BLUE & GrayScale::THREE_QUARTERS;

    const Hex PERCENT_0 =       BLACK;
    const Hex PERCENT_10 =      BLUE & GrayScale::PERCENT_10;
    const Hex PERCENT_20 =      BLUE & GrayScale::PERCENT_20;
    const Hex PERCENT_25 =      ONE_QUARTER;
    const Hex PERCENT_30 =      BLUE & GrayScale::PERCENT_30;
    const Hex PERCENT_33 =      ONE_THIRD;
    const Hex PERCENT_40 =      BLUE & GrayScale::PERCENT_40;
    const Hex PERCENT_50 =      HALF;
    const Hex PERCENT_60 =      BLUE & GrayScale::PERCENT_60;
    const Hex PERCENT_66 =      TWO_THIRDS;
    const Hex PERCENT_70 =      BLUE & GrayScale::PERCENT_70;
    const Hex PERCENT_75 =      THREE_QUARTERS;
    const Hex PERCENT_80 =      BLUE & GrayScale::PERCENT_80;
    const Hex PERCENT_90 =      BLUE & GrayScale::PERCENT_90;
    const Hex PERCENT_100 =     BLUE;
}   // namespace Blue

// Hex values for the VGA color set
namespace VGA
{
    using Color::WHITE;
    const Hex SILVER = GrayScale::THREE_QUARTERS;
    const Hex GRAY = GrayScale::HALF;
    using Color::BLACK;

    using Color::RED;
    const Hex MAROON = Red::HALF;
    const Hex LIME = Color::GREEN;
    const Hex GREEN = Green::HALF;
    using Color::BLUE;
    const Hex NAVY = Blue::HALF;

    const Hex AQUA = LIME | BLUE;
    const Hex TEAL = GREEN | NAVY;
    const Hex YELLOW = RED | LIME;
    const Hex OLIVE = MAROON | GREEN;
    const Hex FUSCHIA = RED | BLUE;
    const Hex PURPLE = MAROON | NAVY;
}   // namespace VGA

// Hex values for a color wheel
namespace ColorWheel
{
    using Color::RED;
    const Hex RED_ORANGE = RED | Green::ONE_QUARTER;
    const Hex ORANGE = RED | Green::ONE_HALF;
    const Hex GOLD = RED | Green::THREE_QUARTERS;
    using VGA::YELLOW;
    const Hex GREEN_YELLOW = GREEN | Red::THREE_QUARTERS;
    const Hex CHARTREUSE = GREEN | Red::ONE_HALF;
    const Hex HARLEQUIN_GREEN = GREEN | Red::ONE_QUARTER;
    using Color::GREEN;
    const Hex LEAF_GREEN = GREEN | Blue::ONE_QUARTER;
    const Hex SPRING_GREEN = GREEN | Blue::ONE_HALF;
    const Hex AQUAMARINE = GREEN | Blue::THREE_QUARTERS;
    const Hex CYAN = VGA::AQUA;
    const Hex SKY_BLUE = BLUE | Green::THREE_QUARTERS;
    const Hex MEGAMAN_BLUE = BLUE | Green::ONE_HALF;
    const Hex ROYAL_BLUE = BLUE | Green::ONE_QUARTER;
    using Color::BLUE;
    const Hex VIOLET_BLUE = BLUE | Red::ONE_QUARTER;
    const Hex VIOLET = BLUE | Red::ONE_HALF;
    const Hex PURPLE = BLUE | Red::THREE_QUARTERS;
    const Hex MAGENTA = VGA::FUSCHIA;
    const Hex VIOLET_RED = RED | Blue::THREE_QUARTERS;
    const Hex ROSE = RED | Blue::ONE_HALF;
    const Hex CRIMSON = RED | Blue::ONE_QUARTER;
}

}   // namespace Color

#endif  // COLOR_CONSTANTS__H
