/******************************************************************************
 * File:               InlineMath.h
 * Author:             Elizabeth Lowry
 * Date Created:       December 10, 2013
 * Description:        Combines all the header files into one.  Use this header
 *                      if you're compiling the source code for the math library
 *                      as part of your project.
 * Last Modified:      January 5, 2014
 * Last Modification:  Including inline implementations.
 ******************************************************************************/

#ifndef MATH__H
#define MATH__H

#include "Declarations/ColorConstants.h"
#include "Implementations/ColorVector.inl"
#include "Declarations/Functions.h"
#include "Declarations/Hex.h"
#include "Implementations/HomogeneousVector.inl"
#include "Declarations/Matrix.h"
#include "Declarations/MatrixBase.h"
#include "Declarations/MostDerivedAddress.h"
#include "Implementations/PointVector.inl"
#include "Implementations/Transform.inl"
#include "Declarations/Vector.h"
#include "Declarations/VectorBase.h"

#endif  // MATH__H