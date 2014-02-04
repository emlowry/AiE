/******************************************************************************
 * File:               Vector2TestGroup.h
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        Vector2 tests.
 * Last Modified:      January 5, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

#ifndef VECTOR2_TEST_GROUP__H
#define VECTOR2_TEST_GROUP__H

#include "UnitTestGroup.h"

class Vector2TestGroup : public UnitTestGroup
{
public:

    Vector2TestGroup();

private:

    static UnitTest::Result DotProduct();
    static UnitTest::Result Normalization();
    static UnitTest::Result CrossProduct();
    static UnitTest::Result Magnitude();
    static UnitTest::Result Operators();
    static UnitTest::Result Arithmatic();
    static UnitTest::Result Multiplication();
    static UnitTest::Result Division();
    static UnitTest::Result DivisionByZero();
    static UnitTest::Result Interpolation();

};

#endif  // VECTOR2_TEST_GROUP__H
