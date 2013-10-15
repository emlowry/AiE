/** ***************************************************************************
 * @file      Leak_tests.cpp
 * @author    Elizabeth Lowry
 * @date      October 14, 2013 - October 14, 2013
 * @brief     Memory leak operator tests.
 * @details   Tests for the functions in the LeakDebug namespace.
 * @par       Last Modification:
 *              Creation.
 **************************************************************************** */

#include "../gtest/gtest.h"
#include "LeakDebug_externs.h"

using LeakDebug::Leak;

TEST(LeakDebug, LeakOutputOperator)
{
    // Create a leak struct
    Leak oLeak;
    oLeak.pointer = &oLeak;
    oLeak.size = sizeof(Leak);
    oLeak.file = __FILE__;
    unsigned int uiLine = __LINE__ - 3;
    oLeak.line = uiLine;

    // Print what you expect the leak to print as and the leak to string streams
    std::stringstream oExpectedStream, oActualStream;
    oExpectedStream << sizeof(Leak) << " bytes at " << &oLeak
                    << " allocated by " << __FILE__ << "(" << uiLine << ")";
    oActualStream << oLeak;

    // Make sure both are the same.
    std::string oExpected, oActual;
    oExpectedStream >> oExpected;
    oActualStream >> oActual;
    ASSERT_EQ(oExpected.compare(oActual), 0) << "Expected: \"" << oExpected
                                             << "\", Actual: \"" << oActual
                                             << "\"";
}

///TODO Write tests
