/** ***************************************************************************
 * @file      leak_debug_on_tests.cpp
 * @author    Elizabeth Lowry
 * @date      October 14, 2013 - October 14, 2013
 * @brief     Memory leak logging tests.
 * @details   Tests to make sure allocated memory is tracked and can be dumped
 *              when leak_debug.h is included and the environment is in debug
 *              mode.
 * @par       Last Modification:
 *              Creation.
 **************************************************************************** */

// If not already in debug mode, enter it and remember to exit it at the end.
#ifndef _DEBUG
#define INITIAL_STATE_IS_NOT_DEBUG
#define _DEBUG
#endif

#include "../gtest/gtest.h"
#include "LeakDebugTest.h"
#include "leak_debug.h"

///TODO Write tests

// If not in debug mode before these tests, exit debug mode.
#ifdef INITIAL_STATE_NOT_DEBUG
#undef _DEBUG
#endif
