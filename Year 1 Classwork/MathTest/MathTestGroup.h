/******************************************************************************
 * File:               MathTestGroup.h
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        Common math functionality tests.
 * Last Modified:      January 5, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

#ifndef MATH_TEST_GROUP__H
#define MATH_TEST_GROUP__H

#include "UnitTestGroup.h"

class MathTestGroup : public UnitTestGroup
{
public:

    MathTestGroup();

private:

    static UnitTest::Result Conversions();
    static UnitTest::Result Interpolation();
    static UnitTest::Result NearestPower();
    static UnitTest::Result ColorBitwise();

};

#endif  // MATH_TEST_GROUP__H
