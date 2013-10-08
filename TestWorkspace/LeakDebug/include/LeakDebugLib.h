/** ***************************************************************************
 * @file      LeakDebugLib.h
 * @author    Elizabeth Lowry
 * @date      October 7, 2013 - October 7, 2013
 * @brief     Memory leak logging.
 * @details   The header file that defines the functions in the static library.
 * @par       Last Modification:
 *              Creation.
 **************************************************************************** */

#ifndef _LEAK_DEBUG_LIB_H_
#define _LEAK_DEBUG_LIB_H_

#include <iostream>
#include <map>
#include <new>

namespace LeakDebug
{

enum class LoggingFlags
{
    NONE = 0,

    FAILED_ALLOCATIONS = 1,
    SUCCESSFUL_ALLOCATIONS = 2,
    DEALLOCATIONS = 4,
    ALLOCATIONS = FAILED_ALLOCATIONS + SUCCESSFUL_ALLOCATIONS,
    SUCCESSFUL_OPERATIONS = SUCCESSFUL_ALLOCATIONS + DEALLOCATIONS,

    ALL = ALLOCATIONS + DEALLOCATIONS
};

/**
 * Describes a block of allocated dynamic memory and what line allocated it.
 */
struct Leak
{
    void* pointer;      //!< Address of the allocated memory.
    std::size_t size;   //!< Size in bytes of the block of allocated memory.
    char* file;         //!< Name of the code file that allocated the memory.
    unsigned int line;  //!< Line of code on which the memory was allocated.
};

/**
 * A map of Leak structs describing allocated dynamic memory, keyed by address.
 */
typedef std::map< void*, Leak > LeakMap;

void _DumpLeaks( std::ostream& a_roOut );
LeakMap _GetLeaks();
void* _New( std::size_t a_iSize,
                      const LoggingFlags ac_eClogFlags,
                      const LoggingFlags ac_eCerrFlags,
                      const bool a_bNoThrow = false ) throw( std::bad_alloc );
void _Delete( void* a_pMemory,
                        const LoggingFlags ac_eClogFlags,
                        const LoggingFlags ac_eCerrFlags,
                        const bool a_bNoThrow = false ) throw();
void _StoreFileLine( char* a_pcFile, unsigned int a_iLine );

}   // namespace LeakDebug

#endif // _LEAK_DEBUG_LIB_H_
