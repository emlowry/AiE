/******************************************************************************
 * File:               Matrix4x4TestGroup.h
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        4x4 Matrix tests.
 * Last Modified:      January 5, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

#ifndef MATRIX_4X4_TEST_GROUP__H
#define MATRIX_4X4_TEST_GROUP__H

#include "UnitTestGroup.h"

class Matrix4x4TestGroup : public UnitTestGroup
{
public:

    Matrix4x4TestGroup();

private:
    
    static UnitTest::Result Project();
    static UnitTest::Result Scale();
    static UnitTest::Result Rotate();
    static UnitTest::Result Translate();
    static UnitTest::Result PointScale();
    static UnitTest::Result PointRotate();
    static UnitTest::Result Multiply();

};

#endif  // MATRIX_4X4_TEST_GROUP__H
