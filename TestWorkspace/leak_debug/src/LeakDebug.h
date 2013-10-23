/** ***************************************************************************
 * @file      LeakDebug.h
 * @author    Elizabeth Lowry
 * @date      October 7, 2013 - October 16, 2013
 * @brief     Memory leak logging.
 * @details   The header file that defines the functions in the static library.
 * @par       Last Modification:
 *              Refactoring.
 **************************************************************************** */

// If you're including this internal-use header, then you shouldn't include the
// external-use header leak_debug.h
#ifndef _LEAK_DEBUG_H_
#define _LEAK_DEBUG_H_

#include "Leak.h"
#include <iostream>
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

// These are the functions exposed to library users.
void DebugDelete( void* const a_cpMemory ) throw();
void DebugDelete( void* const a_cpMemory,
                  const OutputFlags ac_eClogFlags,
                  const OutputFlags ac_eCerrFlags ) throw();
void DebugDelete( void* const a_cpMemory,
                  const char* const ac_cpcFile,
                  const unsigned int ac_uiLine ) throw();
void DebugDelete( void* const a_cpMemory,
                  const char* const ac_cpcFile,
                  const unsigned int ac_uiLine,
                  const OutputFlags ac_eClogFlags,
                  const OutputFlags ac_eCerrFlags ) throw();
void* DebugNew( const std::size_t ac_uiSize, const bool ac_bNoThrow = false )
    throw( std::bad_alloc );
void* DebugNew( const std::size_t ac_uiSize,
                const OutputFlags ac_eClogFlags,
                const OutputFlags ac_eCerrFlags,
                const bool ac_bNoThrow = false ) throw( std::bad_alloc );
void* DebugNew( const std::size_t ac_uiSize,
                const char* const ac_cpcFile,
                const unsigned int ac_uiLine,
                const bool ac_bNoThrow = false ) throw( std::bad_alloc );
void* DebugNew( const std::size_t ac_uiSize,
                const char* const ac_cpcFile,
                const unsigned int ac_uiLine,
                const OutputFlags ac_eClogFlags,
                const OutputFlags ac_eCerrFlags,
                const bool ac_bNoThrow = false ) throw( std::bad_alloc );
void DumpLeaks( std::ostream& a_roOut = std::cout );
LeakMap GetLeaks();
bool IsOn();
void SetOutputFlags( const OutputFlags ac_eDefaultClogFlags,
                     const OutputFlags ac_eDefaultCerrFlags );
void Start();
void Start( const OutputFlags ac_eDefaultClogFlags,
            const OutputFlags ac_eDefaultCerrFlags );
void Stop();
void StoreFileLine( const char* const ac_cpcFile,
                    const unsigned int ac_uiLine ) throw();
void UnstoreFileLine() throw();

}   // namespace LeakDebug

#endif // _LEAK_DEBUG_H_
