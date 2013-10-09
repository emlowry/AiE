/** ***************************************************************************
 * @file      LeakDebug.h
 * @author    Elizabeth Lowry
 * @date      October 7, 2013 - October 8, 2013
 * @brief     Memory leak logging.
 * @details   The header file that defines the functions in the static library.
 * @par       Last Modification:
 *              Adding some comments, default parameter values, and overloads.
 **************************************************************************** */

#ifndef _LEAK_DEBUG_LIB_H_
#define _LEAK_DEBUG_LIB_H_

#include <iostream>
#include <map>
#include <new>

namespace LeakDebug
{

/**
 * Flags indicating what events to log to an output stream.
 */
enum OutputFlags
{
    NONE = 0,

    // Individual things that can be logged are represented by powers of two so
    // that they can be checked for in combined tags using bit logic.
    FAILED_ALLOCATIONS = 1 << 0,
    SUCCESSFUL_ALLOCATIONS = 1 << 1,
    DEALLOCATIONS = 1 << 2,

    // The individual flags can be combined into flags representing more than
    // one thing.
    ALLOCATIONS = FAILED_ALLOCATIONS | SUCCESSFUL_ALLOCATIONS,
    SUCCESSES = SUCCESSFUL_ALLOCATIONS | DEALLOCATIONS,
    FAILURES = FAILED_ALLOCATIONS,
    ALL = SUCCESSES | FAILURES
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

// These are the functions exposed to library users.
void _Delete( void* a_pMemory,
              OutputFlags a_eClogFlags = OutputFlags::SUCCESSES,
              OutputFlags a_eCerrFlags = OutputFlags::FAILURES ) throw();
void _Delete( void* a_pMemory,
              char* const a_pccFile,
              unsigned int a_uiLine,
              OutputFlags a_eClogFlags = OutputFlags::SUCCESSES,
              OutputFlags a_eCerrFlags = OutputFlags::FAILURES ) throw();
void _DumpLeaks( std::ostream& a_roOut );
LeakMap _GetLeaks();
void* _New( std::size_t a_iSize,
            OutputFlags a_eClogFlags = OutputFlags::SUCCESSES,
            OutputFlags a_eCerrFlags = OutputFlags::FAILURES,
            bool a_bNoThrow = false ) throw( std::bad_alloc );
void* _New( std::size_t a_iSize,
            char* const a_pccFile,
            unsigned int a_uiLine,
            OutputFlags a_eClogFlags = OutputFlags::SUCCESSES,
            OutputFlags a_eCerrFlags = OutputFlags::FAILURES,
            bool a_bNoThrow = false ) throw( std::bad_alloc );
std::ostream& operator<<( std::ostream& a_roOut, const Leak& ac_roLeak );
void _StoreFileLine( char* const a_pccFile, unsigned int a_iLine ) throw();
void _UnstoreFileLine() throw();

}   // namespace LeakDebug

#endif // _LEAK_DEBUG_LIB_H_
