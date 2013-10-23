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

TEST_F( LeakDebugTest, StartStopAndIsOn )
{
    // tracking hasn't started yet
    EXPECT_FALSE( LeakDebug::IsOn() );
    LeakMap oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 0 );

    // Allocate without tracking
    char* pcDataCopy = (char*)LeakDebug::DebugNew( smc_uiDataSize );
}

TEST_F( LeakDebugTest, TrackOneWithNoLine )
{
    // start tracking memory leaks
    LeakDebug::Start();

    // allocate some memory
    char* pcDataCopy = (char*)LeakDebug::DebugNew( smc_uiDataSize );
    strcpy( pcDataCopy, smc_cpcDataOne );

    // make sure the leak is being tracked
    LeakMap oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 1 );
    EXPECT_NE( oLeaks.find( pcDataCopy ), oLeaks.end() );

    // make sure the tracked leak has the expected attributes
    Leak oLeak = oLeaks[ pcDataCopy ];
    EXPECT_EQ( oLeak.GetAddress(), pcDataCopy );
    EXPECT_EQ( oLeak.GetSize(), smc_uiDataSize );
    EXPECT_STREQ( oLeak.GetFile(), nullptr );
    EXPECT_EQ( oLeak.GetLine(), 0 );

    // deallocate the leak
    LeakDebug::DebugDelete( pcDataCopy );

    // make sure the leak is no longer being tracked
    oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 0 );
    EXPECT_EQ( oLeaks.find( pcDataCopy ), oLeaks.end() );

    // make sure nothing happens if you try to deallocate the link again
    LeakDebug::DebugDelete( pcDataCopy );
    oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 0 );
    EXPECT_EQ( oLeaks.find( pcDataCopy ), oLeaks.end() );

    // stop tracking memory leaks
    LeakDebug::Stop();
}

TEST_F( LeakDebugTest, TrackTwoWithNoLine )
{
    // start tracking memory leaks
    LeakDebug::Start();

    // allocate some memory
    char* pcDataCopyOne = (char*)LeakDebug::DebugNew( smc_uiDataSize );
    strcpy( pcDataCopyOne, smc_cpcDataOne );

    // make sure the leak is being tracked
    LeakMap oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 1 );
    EXPECT_NE( oLeaks.find( pcDataCopyOne ), oLeaks.end() );

    // make sure the tracked leak has the expected attributes
    Leak oLeak = oLeaks[ pcDataCopyOne ];
    EXPECT_EQ( oLeak.GetAddress(), pcDataCopyOne );
    EXPECT_EQ( oLeak.GetSize(), smc_uiDataSize );
    EXPECT_STREQ( oLeak.GetFile(), nullptr );
    EXPECT_EQ( oLeak.GetLine(), 0 );

    // allocate some more memory
    char* pcDataCopyTwo = (char*)LeakDebug::DebugNew( smc_uiDataSize );
    strcpy( pcDataCopyTwo, smc_cpcDataTwo );

    // make sure both leaks are being tracked
    oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 2 );
    EXPECT_NE( oLeaks.find( pcDataCopyOne ), oLeaks.end() );
    EXPECT_NE( oLeaks.find( pcDataCopyTwo ), oLeaks.end() );

    // make sure the tracked leaks have the expected attributes
    oLeak = oLeaks[ pcDataCopyOne ];
    EXPECT_EQ( oLeak.GetAddress(), pcDataCopyOne );
    EXPECT_EQ( oLeak.GetSize(), smc_uiDataSize );
    EXPECT_STREQ( oLeak.GetFile(), nullptr );
    EXPECT_EQ( oLeak.GetLine(), 0 );
    oLeak = oLeaks[ pcDataCopyTwo ];
    EXPECT_EQ( oLeak.GetAddress(), pcDataCopyTwo );
    EXPECT_EQ( oLeak.GetSize(), smc_uiDataSize );
    EXPECT_STREQ( oLeak.GetFile(), nullptr );
    EXPECT_EQ( oLeak.GetLine(), 0 );

    // deallocate the first leak
    LeakDebug::DebugDelete( pcDataCopyOne );

    // make sure the first leak is no longer being tracked but the second leak
    // still is
    oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 1 );
    EXPECT_EQ( oLeaks.find( pcDataCopyOne ), oLeaks.end() );
    EXPECT_NE( oLeaks.find( pcDataCopyTwo ), oLeaks.end() );

    // Make sure the leak still being tracked has the expected attributes
    oLeak = oLeaks[ pcDataCopyTwo ];
    EXPECT_EQ( oLeak.GetAddress(), pcDataCopyTwo );
    EXPECT_EQ( oLeak.GetSize(), smc_uiDataSize );
    EXPECT_STREQ( oLeak.GetFile(), nullptr );
    EXPECT_EQ( oLeak.GetLine(), 0 );

    // deallocate the second leak
    LeakDebug::DebugDelete( pcDataCopyTwo );

    // make sure neither leak is still being tracked
    oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 0 );
    EXPECT_EQ( oLeaks.find( pcDataCopyOne ), oLeaks.end() );
    EXPECT_EQ( oLeaks.find( pcDataCopyTwo ), oLeaks.end() );

    // stop tracking memory leaks
    LeakDebug::Stop();
}

TEST_F( LeakDebugTest, TrackOneWithLine )
{
    // start tracking memory leaks
    LeakDebug::Start();

    // allocate some memory
    unsigned int uiLine = __LINE__ + 2;
    char* pcDataCopy = (char*)LeakDebug::DebugNew( smc_uiDataSize,
                                                   __FILE__, __LINE__ );
    strcpy( pcDataCopy, smc_cpcDataOne );

    // make sure the leak is being tracked
    LeakMap oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 1 );
    EXPECT_NE( oLeaks.find( pcDataCopy ), oLeaks.end() );

    // make sure the tracked leak has the expected attributes
    Leak oLeak = oLeaks[ pcDataCopy ];
    EXPECT_EQ( oLeak.GetAddress(), pcDataCopy );
    EXPECT_EQ( oLeak.GetSize(), smc_uiDataSize );
    EXPECT_STREQ( oLeak.GetFile(), __FILE__ );
    EXPECT_EQ( oLeak.GetLine(), uiLine );

    // deallocate the leak
    LeakDebug::DebugDelete( pcDataCopy, __FILE__, __LINE__ );

    // make sure the leak is no longer being tracked
    oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 0 );
    EXPECT_EQ( oLeaks.find( pcDataCopy ), oLeaks.end() );

    // make sure nothing happens if you try to deallocate the link again
    LeakDebug::DebugDelete( pcDataCopy, __FILE__, __LINE__ );
    oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 0 );
    EXPECT_EQ( oLeaks.find( pcDataCopy ), oLeaks.end() );

    // stop tracking memory leaks
    LeakDebug::Stop();
}

TEST_F( LeakDebugTest, TrackTwoWithLine )
{
    // start tracking memory leaks
    LeakDebug::Start();

    // allocate some memory
    unsigned int uiLineOne = __LINE__ + 2;
    char* pcDataCopyOne = (char*)LeakDebug::DebugNew( smc_uiDataSize,
                                                      __FILE__, __LINE__ );
    strcpy( pcDataCopyOne, smc_cpcDataOne );

    // make sure the leak is being tracked
    LeakMap oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 1 );
    EXPECT_NE( oLeaks.find( pcDataCopyOne ), oLeaks.end() );

    // make sure the tracked leak has the expected attributes
    Leak oLeak = oLeaks[ pcDataCopyOne ];
    EXPECT_EQ( oLeak.GetAddress(), pcDataCopyOne );
    EXPECT_EQ( oLeak.GetSize(), smc_uiDataSize );
    EXPECT_STREQ( oLeak.GetFile(), __FILE__ );
    EXPECT_EQ( oLeak.GetLine(), uiLineOne );

    // allocate some more memory
    unsigned int uiLineTwo = __LINE__ + 2;
    char* pcDataCopyTwo = (char*)LeakDebug::DebugNew( smc_uiDataSize,
                                                      __FILE__, __LINE__ );
    strcpy( pcDataCopyTwo, smc_cpcDataTwo );

    // make sure both leaks are being tracked
    oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 2 );
    EXPECT_NE( oLeaks.find( pcDataCopyOne ), oLeaks.end() );
    EXPECT_NE( oLeaks.find( pcDataCopyTwo ), oLeaks.end() );

    // make sure the tracked leaks have the expected attributes
    oLeak = oLeaks[ pcDataCopyOne ];
    EXPECT_EQ( oLeak.GetAddress(), pcDataCopyOne );
    EXPECT_EQ( oLeak.GetSize(), smc_uiDataSize );
    EXPECT_STREQ( oLeak.GetFile(), __FILE__ );
    EXPECT_EQ( oLeak.GetLine(), uiLineOne );
    oLeak = oLeaks[ pcDataCopyTwo ];
    EXPECT_EQ( oLeak.GetAddress(), pcDataCopyTwo );
    EXPECT_EQ( oLeak.GetSize(), smc_uiDataSize );
    EXPECT_STREQ( oLeak.GetFile(), __FILE__ );
    EXPECT_EQ( oLeak.GetLine(), uiLineTwo );

    // deallocate the first leak
    LeakDebug::DebugDelete( pcDataCopyOne, __FILE__, __LINE__ );

    // make sure the first leak is no longer being tracked but the second leak
    // still is
    oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 1 );
    EXPECT_EQ( oLeaks.find( pcDataCopyOne ), oLeaks.end() );
    EXPECT_NE( oLeaks.find( pcDataCopyTwo ), oLeaks.end() );

    // Make sure the leak still being tracked has the expected attributes
    oLeak = oLeaks[ pcDataCopyTwo ];
    EXPECT_EQ( oLeak.GetAddress(), pcDataCopyTwo );
    EXPECT_EQ( oLeak.GetSize(), smc_uiDataSize );
    EXPECT_STREQ( oLeak.GetFile(), __FILE__ );
    EXPECT_EQ( oLeak.GetLine(), uiLineTwo );

    // deallocate the second leak
    LeakDebug::DebugDelete( pcDataCopyTwo, __FILE__, __LINE__ );

    // make sure neither leak is still being tracked
    oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 0 );
    EXPECT_EQ( oLeaks.find( pcDataCopyOne ), oLeaks.end() );
    EXPECT_EQ( oLeaks.find( pcDataCopyTwo ), oLeaks.end() );

    // stop tracking memory leaks
    LeakDebug::Stop();
}

TEST_F( LeakDebugTest, TrackOneWithStoredLine )
{
    // start tracking memory leaks
    LeakDebug::Start();

    // allocate some memory
    unsigned int uiLine = __LINE__ + 2;
    LeakDebug::StoreFileLine( __FILE__, __LINE__ + 1 );
    char* pcDataCopy = (char*)LeakDebug::DebugNew( smc_uiDataSize );
    strcpy( pcDataCopy, smc_cpcDataOne );

    // make sure the leak is being tracked
    LeakMap oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 1 );
    EXPECT_NE( oLeaks.find( pcDataCopy ), oLeaks.end() );

    // make sure the tracked leak has the expected attributes
    Leak oLeak = oLeaks[ pcDataCopy ];
    EXPECT_EQ( oLeak.GetAddress(), pcDataCopy );
    EXPECT_EQ( oLeak.GetSize(), smc_uiDataSize );
    EXPECT_STREQ( oLeak.GetFile(), __FILE__ );
    EXPECT_EQ( oLeak.GetLine(), uiLine );

    // deallocate the leak
    LeakDebug::StoreFileLine( __FILE__, __LINE__ + 1 );
    LeakDebug::DebugDelete( pcDataCopy );

    // make sure the leak is no longer being tracked
    oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 0 );
    EXPECT_EQ( oLeaks.find( pcDataCopy ), oLeaks.end() );

    // make sure nothing happens if you try to deallocate the link again
    LeakDebug::StoreFileLine( __FILE__, __LINE__ + 1 );
    LeakDebug::DebugDelete( pcDataCopy );
    oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 0 );
    EXPECT_EQ( oLeaks.find( pcDataCopy ), oLeaks.end() );

    // stop tracking memory leaks
    LeakDebug::Stop();
}

TEST_F( LeakDebugTest, TrackTwoWithStoredLine )
{
    // start tracking memory leaks
    LeakDebug::Start();

    // allocate some memory
    unsigned int uiLineOne = __LINE__ + 2;
    LeakDebug::StoreFileLine( __FILE__, __LINE__ + 1 );
    char* pcDataCopyOne = (char*)LeakDebug::DebugNew( smc_uiDataSize );
    strcpy( pcDataCopyOne, smc_cpcDataOne );

    // make sure the leak is being tracked
    LeakMap oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 1 );
    EXPECT_NE( oLeaks.find( pcDataCopyOne ), oLeaks.end() );

    // make sure the tracked leak has the expected attributes
    Leak oLeak = oLeaks[ pcDataCopyOne ];
    EXPECT_EQ( oLeak.GetAddress(), pcDataCopyOne );
    EXPECT_EQ( oLeak.GetSize(), smc_uiDataSize );
    EXPECT_STREQ( oLeak.GetFile(), __FILE__ );
    EXPECT_EQ( oLeak.GetLine(), uiLineOne );

    // allocate some more memory
    unsigned int uiLineTwo = __LINE__ + 2;
    LeakDebug::StoreFileLine( __FILE__, __LINE__ + 1 );
    char* pcDataCopyTwo = (char*)LeakDebug::DebugNew( smc_uiDataSize );
    strcpy( pcDataCopyTwo, smc_cpcDataTwo );

    // make sure both leaks are being tracked
    oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 2 );
    EXPECT_NE( oLeaks.find( pcDataCopyOne ), oLeaks.end() );
    EXPECT_NE( oLeaks.find( pcDataCopyTwo ), oLeaks.end() );

    // make sure the tracked leaks have the expected attributes
    oLeak = oLeaks[ pcDataCopyOne ];
    EXPECT_EQ( oLeak.GetAddress(), pcDataCopyOne );
    EXPECT_EQ( oLeak.GetSize(), smc_uiDataSize );
    EXPECT_STREQ( oLeak.GetFile(), __FILE__ );
    EXPECT_EQ( oLeak.GetLine(), uiLineOne );
    oLeak = oLeaks[ pcDataCopyTwo ];
    EXPECT_EQ( oLeak.GetAddress(), pcDataCopyTwo );
    EXPECT_EQ( oLeak.GetSize(), smc_uiDataSize );
    EXPECT_STREQ( oLeak.GetFile(), __FILE__ );
    EXPECT_EQ( oLeak.GetLine(), uiLineTwo );

    // deallocate the first leak
    LeakDebug::StoreFileLine( __FILE__, __LINE__ + 1 );
    LeakDebug::DebugDelete( pcDataCopyOne );

    // make sure the first leak is no longer being tracked but the second leak
    // still is
    oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 1 );
    EXPECT_EQ( oLeaks.find( pcDataCopyOne ), oLeaks.end() );
    EXPECT_NE( oLeaks.find( pcDataCopyTwo ), oLeaks.end() );

    // Make sure the leak still being tracked has the expected attributes
    oLeak = oLeaks[ pcDataCopyTwo ];
    EXPECT_EQ( oLeak.GetAddress(), pcDataCopyTwo );
    EXPECT_EQ( oLeak.GetSize(), smc_uiDataSize );
    EXPECT_STREQ( oLeak.GetFile(), __FILE__ );
    EXPECT_EQ( oLeak.GetLine(), uiLineTwo );

    // deallocate the second leak
    LeakDebug::StoreFileLine( __FILE__, __LINE__ + 1 );
    LeakDebug::DebugDelete( pcDataCopyTwo );

    // make sure neither leak is still being tracked
    oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 0 );
    EXPECT_EQ( oLeaks.find( pcDataCopyOne ), oLeaks.end() );
    EXPECT_EQ( oLeaks.find( pcDataCopyTwo ), oLeaks.end() );

    // stop tracking memory leaks
    LeakDebug::Stop();
}

TEST_F( LeakDebugTest, TrackOneWithFlagsAndNoLine )
{
    // start tracking memory leaks
    LeakDebug::Start();

    // allocate some memory
    char* pcDataCopy = (char*)LeakDebug::DebugNew( smc_uiDataSize,
                                                   OutputFlags::NONE,
                                                   OutputFlags::NONE );
    strcpy( pcDataCopy, smc_cpcDataOne );

    // make sure the leak is being tracked
    LeakMap oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 1 );
    EXPECT_NE( oLeaks.find( pcDataCopy ), oLeaks.end() );

    // make sure the tracked leak has the expected attributes
    Leak oLeak = oLeaks[ pcDataCopy ];
    EXPECT_EQ( oLeak.GetAddress(), pcDataCopy );
    EXPECT_EQ( oLeak.GetSize(), smc_uiDataSize );
    EXPECT_STREQ( oLeak.GetFile(), nullptr );
    EXPECT_EQ( oLeak.GetLine(), 0 );

    // deallocate the leak
    LeakDebug::DebugDelete( pcDataCopy, OutputFlags::NONE, OutputFlags::NONE );

    // make sure the leak is no longer being tracked
    oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 0 );
    EXPECT_EQ( oLeaks.find( pcDataCopy ), oLeaks.end() );

    // make sure nothing happens if you try to deallocate the link again
    LeakDebug::DebugDelete( pcDataCopy, OutputFlags::NONE, OutputFlags::NONE );
    oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 0 );
    EXPECT_EQ( oLeaks.find( pcDataCopy ), oLeaks.end() );

    // stop tracking memory leaks
    LeakDebug::Stop();
}

TEST_F( LeakDebugTest, TrackTwoWithFlagsAndNoLine )
{
    // start tracking memory leaks
    LeakDebug::Start();

    // allocate some memory
    char* pcDataCopyOne = (char*)LeakDebug::DebugNew( smc_uiDataSize,
                                                      OutputFlags::NONE,
                                                      OutputFlags::NONE );
    strcpy( pcDataCopyOne, smc_cpcDataOne );

    // make sure the leak is being tracked
    LeakMap oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 1 );
    EXPECT_NE( oLeaks.find( pcDataCopyOne ), oLeaks.end() );

    // make sure the tracked leak has the expected attributes
    Leak oLeak = oLeaks[ pcDataCopyOne ];
    EXPECT_EQ( oLeak.GetAddress(), pcDataCopyOne );
    EXPECT_EQ( oLeak.GetSize(), smc_uiDataSize );
    EXPECT_STREQ( oLeak.GetFile(), nullptr );
    EXPECT_EQ( oLeak.GetLine(), 0 );

    // allocate some more memory
    char* pcDataCopyTwo = (char*)LeakDebug::DebugNew( smc_uiDataSize,
                                                      OutputFlags::NONE,
                                                      OutputFlags::NONE );
    strcpy( pcDataCopyTwo, smc_cpcDataTwo );

    // make sure both leaks are being tracked
    oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 2 );
    EXPECT_NE( oLeaks.find( pcDataCopyOne ), oLeaks.end() );
    EXPECT_NE( oLeaks.find( pcDataCopyTwo ), oLeaks.end() );

    // make sure the tracked leaks have the expected attributes
    oLeak = oLeaks[ pcDataCopyOne ];
    EXPECT_EQ( oLeak.GetAddress(), pcDataCopyOne );
    EXPECT_EQ( oLeak.GetSize(), smc_uiDataSize );
    EXPECT_STREQ( oLeak.GetFile(), nullptr );
    EXPECT_EQ( oLeak.GetLine(), 0 );
    oLeak = oLeaks[ pcDataCopyTwo ];
    EXPECT_EQ( oLeak.GetAddress(), pcDataCopyTwo );
    EXPECT_EQ( oLeak.GetSize(), smc_uiDataSize );
    EXPECT_STREQ( oLeak.GetFile(), nullptr );
    EXPECT_EQ( oLeak.GetLine(), 0 );

    // deallocate the first leak
    LeakDebug::DebugDelete( pcDataCopyOne,
                            OutputFlags::NONE, OutputFlags::NONE );

    // make sure the first leak is no longer being tracked but the second leak
    // still is
    oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 1 );
    EXPECT_EQ( oLeaks.find( pcDataCopyOne ), oLeaks.end() );
    EXPECT_NE( oLeaks.find( pcDataCopyTwo ), oLeaks.end() );

    // Make sure the leak still being tracked has the expected attributes
    oLeak = oLeaks[ pcDataCopyTwo ];
    EXPECT_EQ( oLeak.GetAddress(), pcDataCopyTwo );
    EXPECT_EQ( oLeak.GetSize(), smc_uiDataSize );
    EXPECT_STREQ( oLeak.GetFile(), nullptr );
    EXPECT_EQ( oLeak.GetLine(), 0 );

    // deallocate the second leak
    LeakDebug::DebugDelete( pcDataCopyTwo,
                            OutputFlags::NONE, OutputFlags::NONE );

    // make sure neither leak is still being tracked
    oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 0 );
    EXPECT_EQ( oLeaks.find( pcDataCopyOne ), oLeaks.end() );
    EXPECT_EQ( oLeaks.find( pcDataCopyTwo ), oLeaks.end() );

    // stop tracking memory leaks
    LeakDebug::Stop();
}

TEST_F( LeakDebugTest, TrackOneWithFlagsAndLine )
{
    // start tracking memory leaks
    LeakDebug::Start();

    // allocate some memory
    unsigned int uiLine = __LINE__ + 2;
    char* pcDataCopy = (char*)LeakDebug::DebugNew( smc_uiDataSize,
                                                   __FILE__, __LINE__,
                                                   OutputFlags::NONE,
                                                   OutputFlags::NONE );
    strcpy( pcDataCopy, smc_cpcDataOne );

    // make sure the leak is being tracked
    LeakMap oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 1 );
    EXPECT_NE( oLeaks.find( pcDataCopy ), oLeaks.end() );

    // make sure the tracked leak has the expected attributes
    Leak oLeak = oLeaks[ pcDataCopy ];
    EXPECT_EQ( oLeak.GetAddress(), pcDataCopy );
    EXPECT_EQ( oLeak.GetSize(), smc_uiDataSize );
    EXPECT_STREQ( oLeak.GetFile(), __FILE__ );
    EXPECT_EQ( oLeak.GetLine(), uiLine );

    // deallocate the leak
    LeakDebug::DebugDelete( pcDataCopy, __FILE__, __LINE__,
                            OutputFlags::NONE, OutputFlags::NONE );

    // make sure the leak is no longer being tracked
    oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 0 );
    EXPECT_EQ( oLeaks.find( pcDataCopy ), oLeaks.end() );

    // make sure nothing happens if you try to deallocate the link again
    LeakDebug::DebugDelete( pcDataCopy, __FILE__, __LINE__,
                            OutputFlags::NONE, OutputFlags::NONE );
    oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 0 );
    EXPECT_EQ( oLeaks.find( pcDataCopy ), oLeaks.end() );

    // stop tracking memory leaks
    LeakDebug::Stop();
}

TEST_F( LeakDebugTest, TrackTwoWithFlagsAndLine )
{
    // start tracking memory leaks
    LeakDebug::Start();

    // allocate some memory
    unsigned int uiLineOne = __LINE__ + 2;
    char* pcDataCopyOne = (char*)LeakDebug::DebugNew( smc_uiDataSize,
                                                      __FILE__, __LINE__,
                                                      OutputFlags::NONE,
                                                      OutputFlags::NONE );
    strcpy( pcDataCopyOne, smc_cpcDataOne );

    // make sure the leak is being tracked
    LeakMap oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 1 );
    EXPECT_NE( oLeaks.find( pcDataCopyOne ), oLeaks.end() );

    // make sure the tracked leak has the expected attributes
    Leak oLeak = oLeaks[ pcDataCopyOne ];
    EXPECT_EQ( oLeak.GetAddress(), pcDataCopyOne );
    EXPECT_EQ( oLeak.GetSize(), smc_uiDataSize );
    EXPECT_STREQ( oLeak.GetFile(), __FILE__ );
    EXPECT_EQ( oLeak.GetLine(), uiLineOne );

    // allocate some more memory
    unsigned int uiLineTwo = __LINE__ + 2;
    char* pcDataCopyTwo = (char*)LeakDebug::DebugNew( smc_uiDataSize,
                                                      __FILE__, __LINE__,
                                                      OutputFlags::NONE,
                                                      OutputFlags::NONE );
    strcpy( pcDataCopyTwo, smc_cpcDataTwo );

    // make sure both leaks are being tracked
    oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 2 );
    EXPECT_NE( oLeaks.find( pcDataCopyOne ), oLeaks.end() );
    EXPECT_NE( oLeaks.find( pcDataCopyTwo ), oLeaks.end() );

    // make sure the tracked leaks have the expected attributes
    oLeak = oLeaks[ pcDataCopyOne ];
    EXPECT_EQ( oLeak.GetAddress(), pcDataCopyOne );
    EXPECT_EQ( oLeak.GetSize(), smc_uiDataSize );
    EXPECT_STREQ( oLeak.GetFile(), __FILE__ );
    EXPECT_EQ( oLeak.GetLine(), uiLineOne );
    oLeak = oLeaks[ pcDataCopyTwo ];
    EXPECT_EQ( oLeak.GetAddress(), pcDataCopyTwo );
    EXPECT_EQ( oLeak.GetSize(), smc_uiDataSize );
    EXPECT_STREQ( oLeak.GetFile(), __FILE__ );
    EXPECT_EQ( oLeak.GetLine(), uiLineTwo );

    // deallocate the first leak
    LeakDebug::DebugDelete( pcDataCopyOne, __FILE__, __LINE__,
                            OutputFlags::NONE, OutputFlags::NONE );

    // make sure the first leak is no longer being tracked but the second leak
    // still is
    oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 1 );
    EXPECT_EQ( oLeaks.find( pcDataCopyOne ), oLeaks.end() );
    EXPECT_NE( oLeaks.find( pcDataCopyTwo ), oLeaks.end() );

    // Make sure the leak still being tracked has the expected attributes
    oLeak = oLeaks[ pcDataCopyTwo ];
    EXPECT_EQ( oLeak.GetAddress(), pcDataCopyTwo );
    EXPECT_EQ( oLeak.GetSize(), smc_uiDataSize );
    EXPECT_STREQ( oLeak.GetFile(), __FILE__ );
    EXPECT_EQ( oLeak.GetLine(), uiLineTwo );

    // deallocate the second leak
    LeakDebug::DebugDelete( pcDataCopyTwo, __FILE__, __LINE__,
                            OutputFlags::NONE, OutputFlags::NONE );

    // make sure neither leak is still being tracked
    oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 0 );
    EXPECT_EQ( oLeaks.find( pcDataCopyOne ), oLeaks.end() );
    EXPECT_EQ( oLeaks.find( pcDataCopyTwo ), oLeaks.end() );

    // stop tracking memory leaks
    LeakDebug::Stop();
}

TEST_F( LeakDebugTest, TrackOneWithFlagsAndStoredLine )
{
    // start tracking memory leaks
    LeakDebug::Start();

    // allocate some memory
    unsigned int uiLine = __LINE__ + 2;
    LeakDebug::StoreFileLine( __FILE__, __LINE__ + 1 );
    char* pcDataCopy = (char*)LeakDebug::DebugNew( smc_uiDataSize,
                                                   OutputFlags::NONE,
                                                   OutputFlags::NONE );
    strcpy( pcDataCopy, smc_cpcDataOne );

    // make sure the leak is being tracked
    LeakMap oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 1 );
    EXPECT_NE( oLeaks.find( pcDataCopy ), oLeaks.end() );

    // make sure the tracked leak has the expected attributes
    Leak oLeak = oLeaks[ pcDataCopy ];
    EXPECT_EQ( oLeak.GetAddress(), pcDataCopy );
    EXPECT_EQ( oLeak.GetSize(), smc_uiDataSize );
    EXPECT_STREQ( oLeak.GetFile(), __FILE__ );
    EXPECT_EQ( oLeak.GetLine(), uiLine );

    // deallocate the leak
    LeakDebug::StoreFileLine( __FILE__, __LINE__ + 1 );
    LeakDebug::DebugDelete( pcDataCopy, OutputFlags::NONE, OutputFlags::NONE );

    // make sure the leak is no longer being tracked
    oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 0 );
    EXPECT_EQ( oLeaks.find( pcDataCopy ), oLeaks.end() );

    // make sure nothing happens if you try to deallocate the link again
    LeakDebug::StoreFileLine( __FILE__, __LINE__ + 1 );
    LeakDebug::DebugDelete( pcDataCopy, OutputFlags::NONE, OutputFlags::NONE );
    oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 0 );
    EXPECT_EQ( oLeaks.find( pcDataCopy ), oLeaks.end() );

    // stop tracking memory leaks
    LeakDebug::Stop();
}

TEST_F( LeakDebugTest, TrackTwoWithFlagsAndStoredLine )
{
    // start tracking memory leaks
    LeakDebug::Start();

    // allocate some memory
    unsigned int uiLineOne = __LINE__ + 2;
    LeakDebug::StoreFileLine( __FILE__, __LINE__ + 1 );
    char* pcDataCopyOne = (char*)LeakDebug::DebugNew( smc_uiDataSize,
                                                      OutputFlags::NONE,
                                                      OutputFlags::NONE );
    strcpy( pcDataCopyOne, smc_cpcDataOne );

    // make sure the leak is being tracked
    LeakMap oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 1 );
    EXPECT_NE( oLeaks.find( (void*)pcDataCopyOne ), oLeaks.end() );

    // make sure the tracked leak has the expected attributes
    Leak oLeak = oLeaks[ pcDataCopyOne ];
    EXPECT_EQ( oLeak.GetAddress(), pcDataCopyOne );
    EXPECT_EQ( oLeak.GetSize(), smc_uiDataSize );
    EXPECT_STREQ( oLeak.GetFile(), __FILE__ );
    EXPECT_EQ( oLeak.GetLine(), uiLineOne );

    // allocate some more memory
    unsigned int uiLineTwo = __LINE__ + 2;
    LeakDebug::StoreFileLine( __FILE__, __LINE__ + 1 );
    char* pcDataCopyTwo = (char*)LeakDebug::DebugNew( smc_uiDataSize,
                                                      OutputFlags::NONE,
                                                      OutputFlags::NONE );
    strcpy( pcDataCopyTwo, smc_cpcDataTwo );

    // make sure both leaks are being tracked
    oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 2 );
    EXPECT_NE( oLeaks.find( pcDataCopyOne ), oLeaks.end() );
    EXPECT_NE( oLeaks.find( pcDataCopyTwo ), oLeaks.end() );

    // make sure the tracked leaks have the expected attributes
    oLeak = oLeaks[ pcDataCopyOne ];
    EXPECT_EQ( oLeak.GetAddress(), pcDataCopyOne );
    EXPECT_EQ( oLeak.GetSize(), smc_uiDataSize );
    EXPECT_STREQ( oLeak.GetFile(), __FILE__ );
    EXPECT_EQ( oLeak.GetLine(), uiLineOne );
    oLeak = oLeaks[ pcDataCopyTwo ];
    EXPECT_EQ( oLeak.GetAddress(), pcDataCopyTwo );
    EXPECT_EQ( oLeak.GetSize(), smc_uiDataSize );
    EXPECT_STREQ( oLeak.GetFile(), __FILE__ );
    EXPECT_EQ( oLeak.GetLine(), uiLineTwo );

    // deallocate the first leak
    LeakDebug::StoreFileLine( __FILE__, __LINE__ + 1 );
    LeakDebug::DebugDelete( pcDataCopyOne,
                            OutputFlags::NONE, OutputFlags::NONE );

    // make sure the first leak is no longer being tracked but the second leak
    // still is
    oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 1 );
    EXPECT_EQ( oLeaks.find( pcDataCopyOne ), oLeaks.end() );
    EXPECT_NE( oLeaks.find( pcDataCopyTwo ), oLeaks.end() );

    // Make sure the leak still being tracked has the expected attributes
    oLeak = oLeaks[ pcDataCopyTwo ];
    EXPECT_EQ( oLeak.GetAddress(), pcDataCopyTwo );
    EXPECT_EQ( oLeak.GetSize(), smc_uiDataSize );
    EXPECT_STREQ( oLeak.GetFile(), __FILE__ );
    EXPECT_EQ( oLeak.GetLine(), uiLineTwo );

    // deallocate the second leak
    LeakDebug::StoreFileLine( __FILE__, __LINE__ + 1 );
    LeakDebug::DebugDelete( pcDataCopyTwo,
                            OutputFlags::NONE, OutputFlags::NONE );

    // make sure neither leak is still being tracked
    oLeaks = LeakDebug::GetLeaks();
    EXPECT_EQ( oLeaks.size(), 0 );
    EXPECT_EQ( oLeaks.find( pcDataCopyOne ), oLeaks.end() );
    EXPECT_EQ( oLeaks.find( pcDataCopyTwo ), oLeaks.end() );

    // stop tracking memory leaks
    LeakDebug::Stop();
}

///TODO Write tests
