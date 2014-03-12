/******************************************************************************
 * File:               MathLibrary.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 5, 2014
 * Description:        All-inclusive header file for the Math library.
 * Last Modified:      March 5, 2014
 * Last Modification:  Disabled warning about extern template instantiation.
 ******************************************************************************/

#ifndef MATH__LIBRARY__H
#define MATH__LIBRARY__H

#if !(defined INCLUDING_STATIC_MATH_LIBRARY) && \
    !(defined INCLUDING_INLINE_MATH_LIBRARY)
#define INCLUDING_DYNAMIC_MATH_LIBRARY
#endif

//disable warnings on extern before template instantiation
#pragma warning(push)
#pragma warning (disable : 4231)

#include "../Declarations/ColorConstants.h"
#include "../Declarations/ColorVector.h"
#include "../Declarations/Comparable.h"
#include "../Declarations/DumbString.h"
#include "../Declarations/DynamicArray.h"
#include "../Declarations/Functions.h"
#include "../Declarations/Hashable.h"
#include "../Declarations/Hex.h"
#include "../Declarations/HomogeneousVector.h"
#include "../Declarations/InitializeableSingleton.h"
#include "../Declarations/Matrix.h"
#include "../Declarations/MostDerivedAddress.h"
#include "../Declarations/NotCopyable.h"
#include "../Declarations/PointVector.h"
#include "../Declarations/Quaternion.h"
#include "../Declarations/Singleton.h"
#include "../Declarations/Transform.h"
#include "../Declarations/Vector.h"

// reenable warnings
#pragma warning(pop)

#endif  // MATH__LIBRARY__H
