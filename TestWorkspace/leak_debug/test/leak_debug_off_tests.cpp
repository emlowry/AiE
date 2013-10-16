/** ***************************************************************************
 * @file      leak_debug_off_tests.cpp
 * @author    Elizabeth Lowry
 * @date      October 14, 2013 - October 14, 2013
 * @brief     Memory leak logging tests.
 * @details   Tests to make sure allocated memory is not tracked and that trying
 *              to dump it does nothing when leak_debug.h is included and the
 *              environment is not in debug mode.
 * @par       Last Modification:
 *              Creation.
 **************************************************************************** */

// If in debug mode, exit it and remember to re-enter it at the end.
#ifdef _DEBUG
#define INITIAL_STATE_IS_DEBUG
#undef _DEBUG
#endif

#include "fixtures/LeakDebugTest.h"
#include "gtest/gtest.h"
#include "leak_debug.h"

///TODO Write tests

// If in debug mode before these tests, re-enter debug mode.
#ifdef INITIAL_STATE_IS_DEBUG
#define _DEBUG
#endif
