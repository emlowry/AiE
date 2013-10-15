/** ***************************************************************************
 * @file      LeakDebugTest.h
 * @author    Elizabeth Lowry
 * @date      October 14, 2013 - October 14, 2013
 * @brief     Memory leak logging test fixture.
 * @details   Declares a Google Test test fixture for testing the publicly-
 *              available functions in the LeakDebug namespace in leak_debug.a.
 * @par       Last Modification:
 *              Creation.
 **************************************************************************** */

#ifndef _LEAK_DEBUG_TEST_H_
#define _LEAK_DEBUG_TEST_H_

#include "../gtest/gtest.h"

/**
 * Handles clean-up tasks before and after each LeakDebug test.
 */
class LeakDebugTest : public testing::Test
{
protected:

    virtual void SetUp();
    virtual void TearDown();

private:

    void Clear();

};

#endif  // _LEAK_DEBUG_TEST_H_
