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

const char* const LeakDebugTest::smc_cpcDataOne = "Memory leak One";
const char* const LeakDebugTest::smc_cpcDataTwo = "Memory leak Two";
const unsigned int LeakDebugTest::smc_uiDataSize =
    strlen( LeakDebugTest::smc_cpcDataOne ) + 1;

/**
 * Frees all tracked allocated memory at the end of each test.
 */
void LeakDebugTest::Clear()
{
    // check for remaining leaks
    LeakDebug::LeakMap oLeaks = LeakDebug::GetLeaks();
    for( LeakDebug::LeakMap::value_type oEntry : oLeaks )
    {
        // If the leak is still here at this point, then the pointer that
        // originally pointed to it must be out of scope, making this a true
        // leak and safe to deallocate.
        void* pLeak = const_cast< void* >( oEntry.second.GetAddress() );
        LeakDebug::DebugDelete( pLeak );
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
