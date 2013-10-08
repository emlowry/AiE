/** ***************************************************************************
 * @file      LeakDebugLib.cpp
 * @author    Elizabeth Lowry
 * @date      October 7, 2013 - October 7, 2013
 * @brief     Memory leak logging.
 * @details   Implementations for the functions in the static library.
 * @par       Last Modification:
 *              Creation.
 * @todo      Implement!
 **************************************************************************** */

#include "LeakDebugLib.h"
#include <iostream>
#include <map>
#include <new>

void LeakDebug::_DumpLeaks( std::ostream& a_roOut )
{
}

LeakDebug::LeakMap LeakDebug::_GetLeaks()
{
    return LeakMap();
}

void* LeakDebug::_New( std::size_t a_iSize,
                      const LoggingFlags ac_eClogFlags,
                      const LoggingFlags ac_eCerrFlags,
                      const bool a_bNoThrow = false ) throw( std::bad_alloc )
{
    return nullptr;
}

void LeakDebug::_Delete( void* a_pMemory,
                        const LoggingFlags ac_eClogFlags,
                        const LoggingFlags ac_eCerrFlags,
                        const bool a_bNoThrow = false ) throw()
{
}

void LeakDebug::_StoreFileLine( char* a_pcFile, unsigned int a_iLine )
{
}
