/** ***************************************************************************
 * @file      leak_debug.h
 * @author    Elizabeth Lowry
 * @date      October 7, 2013 - October 8, 2013
 * @brief     Memory leak logging.
 * @details   The header file to include in order to use the memory leak logging
 *              static library.
 * @pre       Make sure your project links to libLeakDebug.a before including
 *              this, and make sure your preprocessor directives can correctly
 *              determine whether or not to use this logging (modify lines 22-24
 *              if necessary).
 * @par       Last Modification:
 *              Added some comments and default parameter values.
 **************************************************************************** */

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
    char* file;         //!< Name of the code file that allocated the memory.
    unsigned int line;  //!< Line of code on which the memory was allocated.
};

/**
 * A map of Leak structs describing allocated dynamic memory, keyed by address.
 */
typedef std::map< void*, Leak > LeakMap;

#ifdef LEAK_DEBUG_LOGGING

// The logging implementations are only imported from libLeakDebug.a when in
// debug mode.
extern void _DumpLeaks( std::ostream& a_roOut );
extern LeakMap _GetLeaks();
extern void* _New( std::size_t a_iSize,
                   OutputFlags a_eClogFlags = OutputFlags::SUCCESSES,
                   OutputFlags a_eCerrFlags = OutputFlags::FAILURES,
                   bool a_bNoThrow = false ) throw( std::bad_alloc );
extern void _Delete( void* a_pMemory,
                     OutputFlags a_eClogFlags = OutputFlags::SUCCESSES,
                     OutputFlags a_eCerrFlags = OutputFlags::FAILURES ) throw();
extern void _StoreFileLine( char* const a_pccFile, unsigned int a_iLine );

#endif  // LEAK_DEBUG_LOGGING

// These functions are included whether you're in debug or not, since they'll be
// called from code that may or may not be in debug mode.  That said, they
// should be empty if you're not in debug mode.

/**
 * Prints a list of allocated dynamic memory to standard output, if debugging.
 */
void DumpLeaks()
{
#ifdef LEAK_DEBUG_LOGGING
    _DumpLeaks( std::cout );
#endif  // LEAK_DEBUG_LOGGING
}

/**
 * Prints a list of allocated dynamic memory to the given stream, if debugging.
 * @param[out] a_roOut  Output stream to write to.
 */
void DumpLeaks( std::ostream& a_roOut )
{
#ifdef LEAK_DEBUG_LOGGING
    _DumpLeaks( a_roOut );
#endif  // LEAK_DEBUG_LOGGING
}

/**
 * Provides a list of objects describing currently allocated dynamic memory.
 * @return  Memory leak structs keyed by address, if debugging (else empty map).
 */
LeakMap GetLeaks()
{
#ifdef LEAK_DEBUG_LOGGING
    return _GetLeaks();
#else
    return LeakMap();
#endif  // LEAK_DEBUG_LOGGING
}

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
    return LeakDebug::_New( a_iSize,
                            (LeakDebug::OutputFlags)LEAK_DEBUG_CLOG_FLAGS,
                            (LeakDebug::OutputFlags)LEAK_DEBUG_CERR_FLAGS );
}
void* operator new[]( std::size_t a_iSize ) throw(std::bad_alloc)
{
    return LeakDebug::_New( a_iSize,
                            (LeakDebug::OutputFlags)LEAK_DEBUG_CLOG_FLAGS,
                            (LeakDebug::OutputFlags)LEAK_DEBUG_CERR_FLAGS );
}
void* operator new( std::size_t a_iSize, const std::nothrow_t& )
{
    return LeakDebug::_New( a_iSize,
                            (LeakDebug::OutputFlags)LEAK_DEBUG_CLOG_FLAGS,
                            (LeakDebug::OutputFlags)LEAK_DEBUG_CERR_FLAGS,
                            true );
}
void* operator new[]( std::size_t a_iSize, const std::nothrow_t& )
{
    return LeakDebug::_New( a_iSize,
                            (LeakDebug::OutputFlags)LEAK_DEBUG_CLOG_FLAGS,
                            (LeakDebug::OutputFlags)LEAK_DEBUG_CERR_FLAGS,
                            true );
}
void operator delete( void* a_pMemory ) throw()
{
    LeakDebug::_Delete( a_pMemory,
                        (LeakDebug::OutputFlags)LEAK_DEBUG_CLOG_FLAGS,
                        (LeakDebug::OutputFlags)LEAK_DEBUG_CERR_FLAGS );
}
void operator delete[]( void* a_pMemory ) throw()
{
    LeakDebug::_Delete( a_pMemory,
                        (LeakDebug::OutputFlags)LEAK_DEBUG_CLOG_FLAGS,
                        (LeakDebug::OutputFlags)LEAK_DEBUG_CERR_FLAGS );
}
void operator delete( void* a_pMemory, const std::nothrow_t& ) throw()
{
    LeakDebug::_Delete( a_pMemory,
                        (LeakDebug::OutputFlags)LEAK_DEBUG_CLOG_FLAGS,
                        (LeakDebug::OutputFlags)LEAK_DEBUG_CERR_FLAGS );
}
void operator delete[]( void* a_pMemory, const std::nothrow_t& ) throw()
{
    LeakDebug::_Delete( a_pMemory,
                        (LeakDebug::OutputFlags)LEAK_DEBUG_CLOG_FLAGS,
                        (LeakDebug::OutputFlags)LEAK_DEBUG_CERR_FLAGS );
}

// Macros replace simple new and delete calls so that the file and line of the
// invocation are stored for the use of the logging implementation.
#define new ( LeakDebug::_StoreFileLine( __FILE__, __LINE__ ), false ) \
            ? nullptr : new
#define delete LeakDebug::_StoreFileLine( __FILE__, __LINE__ ), delete

#endif  // LEAK_DEBUG_LOGGING

#endif  // LEAK_DEBUG_H_
