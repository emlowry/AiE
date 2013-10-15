/** ***************************************************************************
 * @file      LeakDebug_externs.h
 * @author    Elizabeth Lowry
 * @date      October 14, 2013 - October 14, 2013
 * @brief     Memory leak logging test fixture.
 * @details   Imports leak_debug.a library functions and structs for testing.
 * @par       Last Modification:
 *              Creation.
 **************************************************************************** */

#ifndef _LEAK_DEBUG_EXTERNS_H_
#define _LEAK_DEBUG_EXTERNS_H_

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

// operators for the Leak struct
extern std::ostream& operator<<( std::ostream& a_roOut, const Leak& ac_roLeak );
extern bool operator==( const Leak& ac_roLeftLeak, const Leak& ac_roRightLeak );
extern bool operator!=( const Leak& ac_roLeftLeak, const Leak& ac_roRightLeak );
extern bool operator<=( const Leak& ac_roLeftLeak, const Leak& ac_roRightLeak );
extern bool operator>=( const Leak& ac_roLeftLeak, const Leak& ac_roRightLeak );
extern bool operator<( const Leak& ac_roLeftLeak, const Leak& ac_roRightLeak );
extern bool operator>( const Leak& ac_roLeftLeak, const Leak& ac_roRightLeak );

/**
 * A map of Leak structs describing allocated dynamic memory, keyed by address.
 */
typedef std::map< void*, Leak > LeakMap;

extern void DebugDelete( void* a_pMemory,
                         OutputFlags a_eClogFlags = OutputFlags::SUCCESSES,
                         OutputFlags a_eCerrFlags = OutputFlags::FAILURES )
    throw();
extern void DebugDelete( void* a_pMemory,
                         char* const a_pccFile,
                         unsigned int a_uiLine,
                         OutputFlags a_eClogFlags = OutputFlags::SUCCESSES,
                         OutputFlags a_eCerrFlags = OutputFlags::FAILURES )
    throw();
extern void DebugDumpLeaks( std::ostream& a_roOut );
extern LeakMap DebugGetLeaks();
extern void* DebugNew( std::size_t a_iSize,
                       OutputFlags a_eClogFlags = OutputFlags::SUCCESSES,
                       OutputFlags a_eCerrFlags = OutputFlags::FAILURES,
                       bool a_bNoThrow = false ) throw( std::bad_alloc );
extern void* DebugNew( std::size_t a_iSize,
                       char* const a_pccFile,
                       unsigned int a_uiLine,
                       OutputFlags a_eClogFlags = OutputFlags::SUCCESSES,
                       OutputFlags a_eCerrFlags = OutputFlags::FAILURES,
                       bool a_bNoThrow = false ) throw( std::bad_alloc );
extern void DebugStoreFileLine( char* const a_pccFile,
                                unsigned int a_iLine ) throw();
extern void DebugUnstoreFileLine() throw();

}   // namespace LeakDebug

#endif  // _LEAK_DEBUG_EXTERNS_H_
