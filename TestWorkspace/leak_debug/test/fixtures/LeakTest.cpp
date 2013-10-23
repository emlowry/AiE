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

/**
 * Constructor sets up the two member Leak structs with equivalent field values.
 */
LeakTest::LeakTest()
    : m_oLeakOne( &m_oLeakOne, sizeof( LeakDebug::Leak ), __FILE__, __LINE__),
      m_oLeakTwo( m_oLeakOne ) {}
