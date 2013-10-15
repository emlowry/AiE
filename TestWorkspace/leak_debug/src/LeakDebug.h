/** ***************************************************************************
 * @file      LeakDebug.h
 * @author    Elizabeth Lowry
 * @date      October 7, 2013 - October 8, 2013
 * @brief     Memory leak logging.
 * @details   The header file that defines the functions in the static library.
 * @par       Last Modification:
 *              Adding some comments, default parameter values, and overloads.
 **************************************************************************** */

// If you're including this internal-use header, then you shouldn't include the
// external-use header leak_debug.h
#ifndef _LEAK_DEBUG_H_
#define _LEAK_DEBUG_H_

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
void DebugDelete( void* a_pMemory,
                  OutputFlags a_eClogFlags = OutputFlags::SUCCESSES,
                  OutputFlags a_eCerrFlags = OutputFlags::FAILURES ) throw();
void DebugDelete( void* a_pMemory,
                  char* const a_pccFile,
                  unsigned int a_uiLine,
                  OutputFlags a_eClogFlags = OutputFlags::SUCCESSES,
                  OutputFlags a_eCerrFlags = OutputFlags::FAILURES ) throw();
void DebugDumpLeaks( std::ostream& a_roOut );
LeakMap DebugGetLeaks();
void* DebugNew( std::size_t a_iSize,
                OutputFlags a_eClogFlags = OutputFlags::SUCCESSES,
                OutputFlags a_eCerrFlags = OutputFlags::FAILURES,
                bool a_bNoThrow = false ) throw( std::bad_alloc );
void* DebugNew( std::size_t a_iSize,
                char* const a_pccFile,
                unsigned int a_uiLine,
                OutputFlags a_eClogFlags = OutputFlags::SUCCESSES,
                OutputFlags a_eCerrFlags = OutputFlags::FAILURES,
                bool a_bNoThrow = false ) throw( std::bad_alloc );
void DebugStoreFileLine( char* const a_pccFile, unsigned int a_iLine ) throw();
void DebugUnstoreFileLine() throw();
std::ostream& operator<<( std::ostream& a_roOut, const Leak& ac_roLeak );
bool operator==( const Leak& ac_roLeftLeak, const Leak& ac_roRightLeak );
bool operator!=( const Leak& ac_roLeftLeak, const Leak& ac_roRightLeak );
bool operator<=( const Leak& ac_roLeftLeak, const Leak& ac_roRightLeak );
bool operator>=( const Leak& ac_roLeftLeak, const Leak& ac_roRightLeak );
bool operator<( const Leak& ac_roLeftLeak, const Leak& ac_roRightLeak );
bool operator>( const Leak& ac_roLeftLeak, const Leak& ac_roRightLeak );

}   // namespace LeakDebug

#endif // _LEAK_DEBUG_H_
