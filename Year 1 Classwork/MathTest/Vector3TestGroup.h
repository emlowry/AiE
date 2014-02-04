/******************************************************************************
 * File:               Vector3TestGroup.h
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        Vector3 tests.
 * Last Modified:      January 5, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

#ifndef VECTOR3_TEST_GROUP__H
#define VECTOR3_TEST_GROUP__H

#include "UnitTestGroup.h"

class Vector3TestGroup : public UnitTestGroup
{
public:

    Vector3TestGroup();

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

#endif  // VECTOR3_TEST_GROUP__H
