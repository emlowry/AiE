/** ***************************************************************************
 * @file      LeakTest.h
 * @author    Elizabeth Lowry
 * @date      October 15, 2013 - October 15, 2013
 * @brief     Memory leak struct operator test fixture.
 * @details   Implements the constructor for the test fixture that handles Leak
 *              struct operator testing.
 * @par       Last Modification:
 *              Creation.
 **************************************************************************** */

#include "externs/Leak.h"
#include "LeakTest.h"

const char* const LeakTest::sm_cpcFileNameCopyOne = __FILE__;
const char* const LeakTest::sm_cpcFileNameCopyTwo = __FILE__;

/**
 * Constructor sets up the two member Leak structs with equivalent field values.
 */
LeakTest::LeakTest()
{
    unsigned int uiLine = __LINE__;
    m_oLeakOne.pointer = m_oLeakTwo.pointer = &m_oLeakOne;
    m_oLeakOne.size = m_oLeakTwo.size = sizeof(LeakDebug::Leak);
    m_oLeakOne.file = sm_cpcFileNameCopyOne;
    m_oLeakTwo.file = sm_cpcFileNameCopyTwo;
    m_oLeakOne.line = m_oLeakTwo.line = uiLine;
}
