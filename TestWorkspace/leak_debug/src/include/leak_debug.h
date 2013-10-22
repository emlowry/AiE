/** ***************************************************************************
 * @file      leak_debug.h
 * @author    Elizabeth Lowry
 * @date      October 7, 2013 - October 16, 2013
 * @brief     Memory leak logging.
 * @details   The header file to include in order to use the memory leak logging
 *              static library.
 * @pre       Make sure your project links to leak_debug.a or leak_debug_d.a
 *              before including this, and make sure your preprocessor
 *              directives can correctly determine whether or not to use this
 *              logging (modify lines 24-26 if necessary).
 * @par       Last Modification:
 *              Refactoring.
 **************************************************************************** */

// If you're including this external-use header, then you shouldn't include the
// library's internal-use header LeakDebug.h
#ifndef _LEAK_DEBUG_H_
#define _LEAK_DEBUG_H_

// Figure out whether or not to log allocations and deallocations.  Visual
// Studio indicates debug mode by defining the _DEBUG flag, other compilers may
// use different methods.  Edit the copy of this file in your project as needed.
#ifdef _DEBUG
#define LEAK_DEBUG_LOGGING
#endif  // _DEBUG

#include <iostream>
#include <map>
#include <string>

#ifdef LEAK_DEBUG_LOGGING
#include <new>
#endif  // LEAK_DEBUG_LOGGING

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
    std::string file;   //!< Name of the code file that allocated the memory.
    unsigned int line;  //!< Line of code on which the memory was allocated.
};

// operators for the Leak struct
extern std::ostream& operator<<( std::ostream& a_roOut, const Leak& ac_roLeak );
extern bool operator==( const Leak& ac_roLeftLeak, const Leak& ac_roRightLeak );
extern bool operator!=( const Leak& ac_roLeftLeak, const Leak& ac_roRightLeak );
extern bool operator>( const Leak& ac_roLeftLeak, const Leak& ac_roRightLeak );
extern bool operator>=( const Leak& ac_roLeftLeak, const Leak& ac_roRightLeak );
extern bool operator<( const Leak& ac_roLeftLeak, const Leak& ac_roRightLeak );
extern bool operator<=( const Leak& ac_roLeftLeak, const Leak& ac_roRightLeak );

/**
 * A map of Leak structs describing allocated dynamic memory, keyed by address.
 */
typedef std::map< void*, Leak > LeakMap;

#ifdef LEAK_DEBUG_LOGGING

// The logging implementations are only imported from libLeakDebug.a when in
// debug mode.
extern void DebugDelete( void* a_pMemory ) throw();
extern void DebugDelete( void* a_pMemory,
                         const OutputFlags ac_eClogFlags,
                         const OutputFlags ac_eCerrFlags ) throw();
extern void* DebugNew( std::size_t a_iSize, const bool ac_bNoThrow = false )
    throw( std::bad_alloc );
extern void* DebugNew( std::size_t a_iSize,
                       const OutputFlags ac_eClogFlags,
                       const OutputFlags ac_eCerrFlags,
                       const bool ac_bNoThrow = false ) throw( std::bad_alloc );
extern void DumpLeaks( std::ostream& a_roOut = std::cout );
extern LeakMap GetLeaks();
extern bool IsOn();
extern void SetOutputFlags( OutputFlags a_eDefaultClogFlags,
                            OutputFlags a_eDefaultCerrFlags );
extern void Start();
extern void Start( OutputFlags a_eDefaultClogFlags,
                   OutputFlags a_eDefaultCerrFlags );
extern void Stop();
extern void StoreFileLine( const char* const ac_pccFile,
                           const unsigned int ac_uiLine );

#else

inline void DumpLeaks( std::ostream& a_roOut = std::cout ) {}
inline LeakMap GetLeaks() { return LeakMap(); }
inline bool IsOn() { return false; }
inline void SetOutputFlags( OutputFlags a_eDefaultClogFlags,
                            OutputFlags a_eDefaultCerrFlags ) {}
inline void Start() {}
inline void Start( OutputFlags a_eDefaultClogFlags,
                   OutputFlags a_eDefaultCerrFlags ) {}
inline void Stop() {}

#endif  // LEAK_DEBUG_LOGGING

}   // namespace LeakDebug

#ifdef LEAK_DEBUG_LOGGING

// What events should be printed to std::clog?
#ifndef LEAK_DEBUG_CLOG_FLAGS
#define LEAK_DEBUG_CLOG_FLAGS LeakDebug::OutputFlags::NONE
#endif  // LEAK_DEBUG_CLOG_FLAGS

// What events should be printed to std::cerr?
#ifndef LEAK_DEBUG_CERR_FLAGS
#define LEAK_DEBUG_CERR_FLAGS LeakDebug::OutputFlags::FAILURES
#endif  // LEAK_DEBUG_CERR_FLAGS

// In debug mode, override the dynamic allocation/deallocation operators to call
// the logging implementations from the library.
void* operator new( std::size_t a_iSize ) throw(std::bad_alloc)
{
    return LeakDebug::DebugNew( a_iSize );
}
void* operator new[]( std::size_t a_iSize ) throw(std::bad_alloc)
{
    return LeakDebug::DebugNew( a_iSize );
}
void* operator new( std::size_t a_iSize, const std::nothrow_t& )
{
    return LeakDebug::DebugNew( a_iSize, true );
}
void* operator new[]( std::size_t a_iSize, const std::nothrow_t& )
{
    return LeakDebug::DebugNew( a_iSize, true );
}
void operator delete( void* a_pMemory ) throw()
{
    LeakDebug::DebugDelete( a_pMemory );
}
void operator delete[]( void* a_pMemory ) throw()
{
    LeakDebug::DebugDelete( a_pMemory );
}
void operator delete( void* a_pMemory, const std::nothrow_t& ) throw()
{
    LeakDebug::DebugDelete( a_pMemory );
}
void operator delete[]( void* a_pMemory, const std::nothrow_t& ) throw()
{
    LeakDebug::DebugDelete( a_pMemory );
}

// Macros replace simple new and delete calls so that the file and line of the
// invocation are stored for the use of the logging implementation.
#define new ( LeakDebug::StoreFileLine( __FILE__, __LINE__ ), false ) \
            ? nullptr : new
#define delete LeakDebug::StoreFileLine( __FILE__, __LINE__ ), delete

// Macros provide easy calls to start and stop logging and to dump the leaks,
// macros that expand to nothing when logging is disabled.
#define LEAK_DEBUG_START LeakDebug::Start( LEAK_DEBUG_CLOG_FLAGS, \
                                           LEAK_DEBUG_CERR_FLAGS );
#define LEAK_DEBUG_DUMP LeakDebug::DumpLeaks();
#define LEAK_DEBUG_STOP LeakDebug::Stop();

#else

#define LEAK_DEBUG_START
#define LEAK_DEBUG_DUMP
#define LEAK_DEBUG_STOP

#endif  // LEAK_DEBUG_LOGGING

#endif  // LEAK_DEBUG_H_
