/** ***************************************************************************
 * @file      LeakDebug_tests.cpp
 * @author    Elizabeth Lowry
 * @date      October 14, 2013 - October 16, 2013
 * @brief     Memory leak logging tests.
 * @details   Tests for the functions in the LeakDebug namespace.
 * @par       Last Modification:
 *              Starting to implement.
 **************************************************************************** */

#include "externs/LeakDebug.h"
#include "fixtures/LeakDebugTest.h"
#include "gtest/gtest.h"
#include <cstring>

using LeakDebug::OutputFlags;
using LeakDebug::Leak;
using LeakDebug::LeakMap;

TEST_F( LeakDebugTest, TrackOneNoLine )
{
    // data to put in allocated memory
    char acData[] = "Memory leak one";
    unsigned int acDataSize = strlen( acData ) + 1;

    // start tracking memory leaks
    LeakDebug::Start();

    // allocate some memory
    char* pcDataCopy = (char*)LeakDebug::DebugNew( acDataSize );
    strcpy( pcDataCopy, acData );

    // make sure the leak is being tracked
    LeakMap oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 1 );
    EXPECT_NE( oLeaks.find(pcDataCopy), oLeaks.end() );

    // make sure the tracked leak has the expected attributes
    Leak oLeak = oLeaks[pcDataCopy];
    EXPECT_EQ( oLeak.pointer, pcDataCopy );
    EXPECT_EQ( oLeak.size, acDataSize );
    EXPECT_STREQ( oLeak.file, "" );
    EXPECT_EQ( oLeak.line, 0 );

    // deallocate the leak
    LeakDebug::DebugDelete( pcDataCopy );

    // make sure the leak is no longer being tracked
    oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 0 );
    EXPECT_EQ( oLeaks.find(pcDataCopy), oLeaks.end() );

    // make sure nothing happens if you try to deallocate the link again
    LeakDebug::DebugDelete( pcDataCopy );
    oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 0 );
    EXPECT_EQ( oLeaks.find(pcDataCopy), oLeaks.end() );

    // stop tracking memory leaks
    LeakDebug::Stop();
}

TEST_F( LeakDebugTest, TrackTwoNoLine )
{
    // data to put in allocated memory
    char acDataOne[] = "Memory leak one";
    char acDataTwo[] = "Memory leak two";
    unsigned int acDataSize = strlen( acDataOne ) + 1;

    // start tracking memory leaks
    LeakDebug::Start();

    // allocate some memory
    char* pcDataCopyOne = (char*)LeakDebug::DebugNew( acDataSize );
    strcpy( pcDataCopyOne, acDataOne );

    // make sure the leak is being tracked
    LeakMap oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 1 );
    EXPECT_NE( oLeaks.find(pcDataCopyOne), oLeaks.end() );

    // make sure the tracked leak has the expected attributes
    Leak oLeak = oLeaks[pcDataCopyOne];
    EXPECT_EQ( oLeak.pointer, pcDataCopyOne );
    EXPECT_EQ( oLeak.size, acDataSize );
    EXPECT_STREQ( oLeak.file, "" );
    EXPECT_EQ( oLeak.line, 0 );

    // allocate some more memory
    char* pcDataCopyTwo = (char*)LeakDebug::DebugNew( acDataSize );
    strcpy( pcDataCopyTwo, acDataTwo );

    // make sure both leaks are being tracked
    oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 2 );
    EXPECT_NE( oLeaks.find(pcDataCopyOne), oLeaks.end() );
    EXPECT_NE( oLeaks.find(pcDataCopyTwo), oLeaks.end() );

    // make sure the tracked leaks have the expected attributes
    oLeak = oLeaks[pcDataCopyOne];
    EXPECT_EQ( oLeak.pointer, pcDataCopyOne );
    EXPECT_EQ( oLeak.size, acDataSize );
    EXPECT_STREQ( oLeak.file, "" );
    EXPECT_EQ( oLeak.line, 0 );
    oLeak = oLeaks[pcDataCopyTwo];
    EXPECT_EQ( oLeak.pointer, pcDataCopyTwo );
    EXPECT_EQ( oLeak.size, acDataSize );
    EXPECT_STREQ( oLeak.file, "" );
    EXPECT_EQ( oLeak.line, 0 );

    // deallocate the first leak
    LeakDebug::DebugDelete( pcDataCopyOne );

    // make sure the first leak is no longer being tracked but the second leak
    // still is
    oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 1 );
    EXPECT_EQ( oLeaks.find(pcDataCopyOne), oLeaks.end() );
    EXPECT_NE( oLeaks.find(pcDataCopyTwo), oLeaks.end() );

    // Make sure the leak still being tracked has the expected attributes
    oLeak = oLeaks[pcDataCopyTwo];
    EXPECT_EQ( oLeak.pointer, pcDataCopyTwo );
    EXPECT_EQ( oLeak.size, acDataSize );
    EXPECT_STREQ( oLeak.file, "" );
    EXPECT_EQ( oLeak.line, 0 );

    // deallocate the second leak
    LeakDebug::DebugDelete( pcDataCopyTwo );

    // make sure neither leak is still being tracked
    oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 0 );
    EXPECT_EQ( oLeaks.find(pcDataCopyOne), oLeaks.end() );
    EXPECT_EQ( oLeaks.find(pcDataCopyTwo), oLeaks.end() );

    // stop tracking memory leaks
    LeakDebug::Stop();
}

///TODO Write tests
