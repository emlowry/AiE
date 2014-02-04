/******************************************************************************
 * File:               Vector4TestGroup.h
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        Vector4 tests.
 * Last Modified:      January 5, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

#ifndef VECTOR4_TEST_GROUP__H
#define VECTOR4_TEST_GROUP__H

#include "UnitTestGroup.h"

class Vector4TestGroup : public UnitTestGroup
{
public:

    Vector4TestGroup();

private:

    static UnitTest::Result ColorConstInit();
    static UnitTest::Result ColorHexInit();
    static UnitTest::Result ColorBitwiseOp();
    static UnitTest::Result Normalization();

};

#endif  // VECTOR4_TEST_GROUP__H
