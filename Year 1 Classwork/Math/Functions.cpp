/******************************************************************************
 * File:               Functions.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       December 2, 2013
 * Description:        Implementations for Functions.h.
 * Last Modified:      December 2, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#include "Functions.h"
#include <cmath>    // for acos

namespace Math
{

// radian-related constants
const long double PI = std::acos( (long double)(-1) );
const long double RADIANS_IN_A_CIRCLE = 2 * PI;
const long double DEGREES_IN_A_RADIAN = 180L / PI;

}