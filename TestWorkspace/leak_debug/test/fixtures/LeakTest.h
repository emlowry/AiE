/** ***************************************************************************
 * @file      LeakTest.h
 * @author    Elizabeth Lowry
 * @date      October 15, 2013 - October 15, 2013
 * @brief     Memory leak struct operator test fixture.
 * @details   Declares a Google Test test fixture for testing the operators
 *              defined for the Leak struct.
 * @par       Last Modification:
 *              Creation.
 **************************************************************************** */

#ifndef _LEAK_TEST_H_
#define _LEAK_TEST_H_

#include "externs/Leak.h"
#include "gtest/gtest.h"

/**
 * Handles clean-up tasks before and after each LeakDebug test.
 */
class LeakTest : public testing::Test
{
public:

    LeakTest();

protected:

    // Strings with identical contents but at different addresses.
    static const char* const sm_cpcFileNameCopyOne;
    static const char* const sm_cpcFileNameCopyTwo;

    // These two structs will be equivalent at the start of each test.
    LeakDebug::Leak m_oLeakOne;
    LeakDebug::Leak m_oLeakTwo;

};

#endif  // _LEAK_TEST_H_
