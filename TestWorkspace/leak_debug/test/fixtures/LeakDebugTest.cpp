/** ***************************************************************************
 * @file      LeakDebugTest.cpp
 * @author    Elizabeth Lowry
 * @date      October 14, 2013 - October 16, 2013
 * @brief     Memory leak logging test fixture.
 * @details   Implementations for the functions of the LeakDebugTest test
 *              fixture class.
 * @par       Last Modification:
 *              Debugging.
 **************************************************************************** */

#include "externs/LeakDebug.h"
#include "LeakDebugTest.h"

using LeakDebug::OutputFlags;

/**
 * Frees all tracked allocated memory at the end of each test.
 */
void LeakDebugTest::Clear()
{
    // make sure there are no pre-existing leaks
    LeakDebug::LeakMap oLeaks = LeakDebug::GetLeaks();
    for( LeakDebug::LeakMap::value_type oEntry : oLeaks )
    {
        LeakDebug::DebugDelete( oEntry.second.pointer );
    }

    // make sure there is no stored line locations
    LeakDebug::UnstoreFileLine();
}

/**
 * Sets up the test case before each test.
 */
void LeakDebugTest::SetUp()
{
    LeakDebug::SetOutputFlags( OutputFlags::NONE, OutputFlags::NONE );
    Clear();
}

/**
 * Performs clean-up tasks after each test.
 */
void LeakDebugTest::TearDown()
{
    LeakDebug::Stop();
    EXPECT_EQ( LeakDebug::GetLeaks().size(), 0 ) << "Poorly written test - "
                                                 << "left behind memory leaks!";
    Clear();
}
