/******************************************************************************
 * File:               Matrix3x3TestGroup.h
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        3x3 Matrix tests.
 * Last Modified:      January 5, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

#ifndef MATRIX_3X3_TEST_GROUP__H
#define MATRIX_3X3_TEST_GROUP__H

#include "UnitTestGroup.h"

class Matrix3x3TestGroup : public UnitTestGroup
{
public:

    Matrix3x3TestGroup();

private:

    static UnitTest::Result Scale();
    static UnitTest::Result Rotate();
    static UnitTest::Result Translate();
    static UnitTest::Result PointScale();
    static UnitTest::Result PointRotate();
    static UnitTest::Result Multiply();

};

#endif  // MATRIX_3X3_TEST_GROUP__H
