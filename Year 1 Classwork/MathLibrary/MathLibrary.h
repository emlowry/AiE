/******************************************************************************
 * File:               MathLibrary.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 5, 2014
 * Description:        All-inclusive header file for the Math library.
 * Last Modified:      February 5, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef MATH__LIBRARY__H
#define MATH__LIBRARY__H

#if !(defined INCLUDING_STATIC_MATH_LIBRARY) && \
    !(defined INCLUDING_INLINE_MATH_LIBRARY)
#define INCLUDING_DYNAMIC_MATH_LIBRARY
#endif

#include "Declarations/ColorConstants.h"
#include "Declarations/ColorVector.h"
#include "Declarations/Functions.h"
#include "Declarations/Hex.h"
#include "Declarations/HomogeneousVector.h"
#include "Declarations/Matrix.h"
#include "Declarations/MostDerivedAddress.h"
#include "Declarations/PointVector.h"
#include "Declarations/Transform.h"
#include "Declarations/Vector.h"

#endif  // MATH__LIBRARY__H