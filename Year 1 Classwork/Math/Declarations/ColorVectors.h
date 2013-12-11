/******************************************************************************
 * File:               ColorVectors.h
 * Author:             Elizabeth Lowry
 * Date Created:       December 11, 2013
 * Description:        Vectors for representing RGB and RGBA colors.
 * Last Modified:      December 11, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef COLOR_VECTORS__H
#define COLOR_VECTORS__H

#include "Vector.h"

namespace Color
{

// Handles RGB colors (no transparency)
class RGBColor : public Math::Vector< unsigned char, 3 >
{
    typedef Vector< unsigned char, 3 > BaseType;
    typedef typename BaseType::RootType RootType;
    typedef typename BaseType::BaseType VectorBaseType;
};

}   // namespace Color

#endif  // COLOR_VECTORS__H
