/** ***************************************************************************
 * @file      LeakDebug.h
 * @author    Elizabeth Lowry
 * @date      October 7, 2013 - October 7, 2013
 * @brief     Memory leak logging.
 * @details   The header file to include in order to use the memory leak logging
 *              static library.
 * @pre       Make sure your project links to leakDebug.lib.
 * @par       Last Modification:
 *              Creation.
 **************************************************************************** */

#ifndef _LEAK_DEBUG_H_
#define _LEAK_DEBUG_H_

// Figure out whether or not to log allocations and deallocations.  Visual
// Studio indicates debug mode by defining the _DEBUG flag, other compilers may
// use different methods.
//#ifdef _DEBUG
#define LEAK_DEBUG_LOGGING
//#endif  // _DEBUG

#include <iostream>
#include <map>

#ifdef LEAK_DEBUG_LOGGING
#include <new>
#endif  // LEAK_DEBUG_LOGGING

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

// The implementations are only imported from LeakDebug.lib when in debug mode.

#ifdef LEAK_DEBUG_LOGGING

extern void _DumpLeaks( std::ostream& a_roOut );
extern LeakMap _GetLeaks();
extern void* _New( std::size_t a_iSize,
                      const LoggingFlags ac_eClogFlags,
                      const LoggingFlags ac_eCerrFlags,
                      const bool a_bNoThrow = false ) throw( std::bad_alloc );
extern void _Delete( void* a_pMemory,
                        const LoggingFlags ac_eClogFlags,
                        const LoggingFlags ac_eCerrFlags,
                        const bool a_bNoThrow = false ) throw();
extern void _StoreFileLine( char* a_pcFile, unsigned int a_iLine );

#endif  // LEAK_DEBUG_LOGGING

// These functions are included whether you're in debug or not, since they'll be
// called from code that may or may not be in debug mode.  That said, they
// should be empty if you're not in debug mode.

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
 * Prints a list of allocated dynamic memory to standard output, if debugging.
 */
void DumpLeaks()
{
#ifdef LEAK_DEBUG_LOGGING
    _DumpLeaks( std::cout );
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

}   // namespace MemoryLeak

// Similarly, the logging implementations of new and delete only exist in debug.

#ifdef LEAK_DEBUG_LOGGING

#ifndef LEAK_DEBUG_CLOG_FLAGS
#define LEAK_DEBUG_CLOG_FLAGS LeakDebug::LoggingFlags::NONE
#endif  // LEAK_DEBUG_CLOG_FLAGS

#ifndef LEAK_DEBUG_CERR_FLAGS
#define LEAK_DEBUG_CERR_FLAGS LeakDebug::LoggingFlags::NONE
#endif  // LEAK_DEBUG_CERR_FLAGS

void* operator new( std::size_t a_iSize ) throw(std::bad_alloc)
{
    return LeakDebug::_New( a_iSize,
                            (LeakDebug::LoggingFlags)LEAK_DEBUG_CLOG_FLAGS,
                            (LeakDebug::LoggingFlags)LEAK_DEBUG_CERR_FLAGS );
}
void* operator new[]( std::size_t a_iSize ) throw(std::bad_alloc)
{
    return LeakDebug::_New( a_iSize,
                            (LeakDebug::LoggingFlags)LEAK_DEBUG_CLOG_FLAGS,
                            (LeakDebug::LoggingFlags)LEAK_DEBUG_CERR_FLAGS );
}
void* operator new( std::size_t a_iSize, const std::nothrow_t& )
{
    return LeakDebug::_New( a_iSize,
                            (LeakDebug::LoggingFlags)LEAK_DEBUG_CLOG_FLAGS,
                            (LeakDebug::LoggingFlags)LEAK_DEBUG_CERR_FLAGS,
                            true );
}
void* operator new[]( std::size_t a_iSize, const std::nothrow_t& )
{
    return LeakDebug::_New( a_iSize,
                            (LeakDebug::LoggingFlags)LEAK_DEBUG_CLOG_FLAGS,
                            (LeakDebug::LoggingFlags)LEAK_DEBUG_CERR_FLAGS,
                            true );
}

void operator delete( void* a_pMemory ) throw()
{
    LeakDebug::_Delete( a_pMemory,
                        (LeakDebug::LoggingFlags)LEAK_DEBUG_CLOG_FLAGS,
                        (LeakDebug::LoggingFlags)LEAK_DEBUG_CERR_FLAGS );
}
void operator delete[]( void* a_pMemory ) throw()
{
    LeakDebug::_Delete( a_pMemory,
                        (LeakDebug::LoggingFlags)LEAK_DEBUG_CLOG_FLAGS,
                        (LeakDebug::LoggingFlags)LEAK_DEBUG_CERR_FLAGS );
}
void operator delete( void* a_pMemory, const std::nothrow_t& )
{
    LeakDebug::_Delete( a_pMemory,
                        (LeakDebug::LoggingFlags)LEAK_DEBUG_CLOG_FLAGS,
                        (LeakDebug::LoggingFlags)LEAK_DEBUG_CERR_FLAGS,
                        true );
}
void operator delete[]( void* a_pMemory, const std::nothrow_t& )
{
    LeakDebug::_Delete( a_pMemory,
                        (LeakDebug::LoggingFlags)LEAK_DEBUG_CLOG_FLAGS,
                        (LeakDebug::LoggingFlags)LEAK_DEBUG_CERR_FLAGS,
                        true );
}

#define new ( LeakDebug::_StoreFileLine( __FILE__, __LINE__ ), false ) \
            ? nullptr : new
#define delete LeakDebug::_StoreFileLine( __FILE__, __LINE__ ), delete

#endif  // LEAK_DEBUG_LOGGING

#endif  // LEAK_DEBUG_H_
