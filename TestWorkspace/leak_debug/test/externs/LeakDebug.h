/** ***************************************************************************
 * @file      LeakDebug.h
 * @author    Elizabeth Lowry
 * @date      October 15, 2013 - October 16, 2013
 * @brief     LeakDebug library functions.
 * @details   Imports leak_debug library functions for testing.
 * @par       Last Modification:
 *              Refactoring.
 **************************************************************************** */

#ifndef _LEAK_DEBUG_H_
#define _LEAK_DEBUG_H_

#include "Leak.h"

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

// library functions
extern void DebugDelete( void* a_pMemory ) throw();
extern void DebugDelete( void* a_pMemory,
                         const OutputFlags ac_eClogFlags,
                         const OutputFlags ac_eCerrFlags ) throw();
extern void DebugDelete( void* a_pMemory,
                         const char* const ac_pccFile,
                         const unsigned int ac_uiLine ) throw();
extern void DebugDelete( void* a_pMemory,
                         const char* const ac_pccFile,
                         const unsigned int ac_uiLine,
                         const OutputFlags ac_eClogFlags,
                         const OutputFlags ac_eCerrFlags ) throw();
extern void* DebugNew( std::size_t a_iSize, const bool ac_bNoThrow = false )
    throw( std::bad_alloc );
extern void* DebugNew( std::size_t a_iSize,
                       const OutputFlags ac_eClogFlags,
                       const OutputFlags ac_eCerrFlags,
                       const bool ac_bNoThrow = false ) throw( std::bad_alloc );
extern void* DebugNew( std::size_t a_iSize,
                       const char* const ac_pccFile,
                       const unsigned int ac_uiLine,
                       const bool ac_bNoThrow = false ) throw( std::bad_alloc );
extern void* DebugNew( std::size_t a_iSize,
                       const char* const ac_pccFile,
                       const unsigned int ac_uiLine,
                       const OutputFlags ac_eClogFlags,
                       const OutputFlags ac_eCerrFlags,
                       const bool ac_bNoThrow = false ) throw( std::bad_alloc );
extern void DumpLeaks( std::ostream& a_roOut );
extern LeakMap GetLeaks();
extern void SetOutputFlags( OutputFlags a_eDefaultClogFlags,
                            OutputFlags a_eDefaultCerrFlags );
extern void Start();
extern void Stop();
extern void StoreFileLine( const char* const ac_pccFile,
                           const unsigned int ac_uiLine ) throw();
extern void UnstoreFileLine() throw();

}   // namespace LeakDebug

#endif  // _LEAK_DEBUG_H_
