/** ***************************************************************************
 * @file      LeakDebug.cpp
 * @author    Elizabeth Lowry
 * @date      October 7, 2013 - October 16, 2013
 * @brief     Memory leak logging.
 * @details   Implementations for the functions in the static library.
 * @par       Last Modification:
 *              Refactoring.
 **************************************************************************** */

#include "Leak.h"
#include "LeakDebug.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <new>

using LeakDebug::OutputFlags;

// These functions are only used inside this cpp.  There's no need to expose
// them to library users.
template< typename... Args >
static void ClogAndCerrMessages( const OutputFlags ac_eClogFlags,
                                 const OutputFlags ac_eCerrFlags,
                                 const OutputFlags ac_eRequiredFlags,
                                 const Args&... ac_rArgs ) throw();
static void LogAllocation( const void* const a_pPointer,
                           const std::size_t ac_uiSize,
                           const char* const ac_cpcFile,
                           const unsigned int ac_uiLine,
                           const OutputFlags ac_eClogFlags,
                           const OutputFlags ac_eCerrFlags ) throw();
static void LogDeallocation( const void* const ac_cpMemory,
                             const char* const ac_cpcFile,
                             const unsigned int ac_uiLine,
                             const OutputFlags ac_eClogFlags,
                             const OutputFlags ac_eCerrFlags ) throw();
template< typename... Args >
static void OutputMessage( std::ostream& a_roOut,
                           const OutputFlags ac_eFlags,
                           const OutputFlags ac_eRequiredFlags,
                           const Args&... ac_rArgs ) throw();
template< typename T, typename... Args >
static void OutputMessage( std::ostream& a_roOut,
                           const T& ac_rArg, const Args&... ac_rArgs );
template< typename T >
static void OutputMessage( std::ostream& a_roOut, const T& ac_rArg );

/**
 * If the things to print to std::clog aren't specified, what should they be?
 */
static LeakDebug::OutputFlags sg_eDefaultClogFlags = LeakDebug::OutputFlags::SUCCESSES;

/**
 * If the things to print to std::cerr aren't specified, what should they be?
 */
static LeakDebug::OutputFlags sg_eDefaultCerrFlags = LeakDebug::OutputFlags::FAILURES;

/**
 * Map of allocated memory
 */
static LeakDebug::LeakMap sg_oLeaks;

/**
 * Recursion level for DebugNew and DebugDelete calls, so we don't end up
 * logging the allocation of everything used for allocation logging - otherwise,
 * we'd end up in an infinite loop whenever we allocated/deallocated dynamic
 * memory.  Initially set to prevent logging, so the logging only starts when
 * we want leaks tracked and not during sensitive initialization tasks.
 */
static unsigned int sg_uiRecursionLevel = 1;

/**
 *  The file name stored by _StoreFileLine
 */
static char* sg_pcStoredFile = nullptr;

/**
 * The line number stored by _StoreFileLine
 */
static unsigned int sg_uiStoredLine = 0;

/**
 * Print a message to the standard log and/or error streams, as appropriate.
 * @param ac_eClogFlags     What should be noted in the standard log stream?
 * @param ac_eCerrFlags     What should be noted in the standard error stream?
 * @param ac_eRequiredFlags What is there to note?
 * @param ac_rArgs          The list of objects that the message is composed of.
 */
template< typename... Args >
static void ClogAndCerrMessages( const OutputFlags ac_eClogFlags,
                                 const OutputFlags ac_eCerrFlags,
                                 const OutputFlags ac_eRequiredFlags,
                                 const Args&... ac_rArgs ) throw()
{
    OutputMessage( std::clog, ac_eClogFlags, ac_eRequiredFlags, ac_rArgs... );
    OutputMessage( std::cerr, ac_eCerrFlags, ac_eRequiredFlags, ac_rArgs... );
}

/**
 * Deallocate a block of dynamic memory and log the deallocation.
 * @param[in,out] a_cpMemory    Address of the memory to deallocate.
 */
void LeakDebug::DebugDelete( void* const a_cpMemory ) throw()
{
    DebugDelete( a_cpMemory, sg_eDefaultClogFlags, sg_eDefaultCerrFlags );
}

/**
 * Deallocate a block of dynamic memory and log the deallocation.
 * @param[in,out] a_cpMemory    Address of the memory to deallocate.
 * @param[in] ac_eClogFlags     What should be noted in standard log stream?
 * @param[in] ac_eCerrFlags     What should be noted in standard error stream?
 */
void LeakDebug::DebugDelete( void* const a_cpMemory,
                             const OutputFlags ac_eClogFlags,
                             const OutputFlags ac_eCerrFlags ) throw()
{
    DebugDelete( a_cpMemory, sg_pcStoredFile, sg_uiStoredLine,
                 ac_eClogFlags, ac_eCerrFlags );
}

/**
 * Deallocate a block of dynamic memory and log the deallocation.
 * @param[in,out] a_cpMemory    Address of the memory to deallocate.
 * @param[in] ac_cpcFile        File from which the call originated.
 * @param[in] ac_uiLine         Line from which the call originated.
 */
void LeakDebug::DebugDelete( void* const a_cpMemory,
                             const char* const ac_cpcFile,
                             const unsigned int ac_uiLine ) throw()
{
    DebugDelete( a_cpMemory, ac_cpcFile, ac_uiLine,
                 sg_eDefaultClogFlags, sg_eDefaultCerrFlags );
}

/**
 * Deallocate a block of dynamic memory and log the deallocation.
 * @param[in,out] a_cpMemory    Address of the memory to deallocate.
 * @param[in] ac_cpcFile        File from which the call originated.
 * @param[in] ac_uiLine         Line from which the call originated.
 * @param[in] ac_eClogFlags     What should be noted in standard log stream?
 * @param[in] ac_eCerrFlags     What should be noted in standard error stream?
 */
void LeakDebug::DebugDelete( void* const a_cpMemory,
                             const char* const ac_cpcFile,
                             const unsigned int ac_uiLine,
                             const OutputFlags ac_eClogFlags,
                             const OutputFlags ac_eCerrFlags ) throw()
{
    // increase recursion level so recursive new/delete calls won't be logged
    ++sg_uiRecursionLevel;

    // deallocate memory
    if( a_cpMemory != nullptr )
    {
        std::free( a_cpMemory );
    }

    // As long as this isn't a recursion from an earlier deallocation, log it.
    if( sg_uiRecursionLevel <= 1 )
    {
        LogDeallocation( a_cpMemory, ac_cpcFile, ac_uiLine,
                         ac_eClogFlags, ac_eCerrFlags );
        UnstoreFileLine();
    }

    // decrease recursion level so subsequent new/delete calls will be logged.
    --sg_uiRecursionLevel;
}

/**
 * Allocate a block of dynamic memory and log the allocation.
 * @param ac_uiSize      How much memory to allocate.
 * @param ac_bNoThrow   On failure, return a nullptr, don't throw a bad_alloc.
 * @return  A pointer to the allocated dynamic memory.
 */
void* LeakDebug::DebugNew( const std::size_t ac_uiSize, const bool ac_bNoThrow )
    throw( std::bad_alloc )
{
    return DebugNew( ac_uiSize, sg_eDefaultClogFlags,
                     sg_eDefaultCerrFlags, ac_bNoThrow );
}

/**
 * Allocate a block of dynamic memory and log the allocation.
 * @param ac_uiSize     How much memory to allocate.
 * @param ac_eClogFlags What should be noted in the standard log stream?
 * @param ac_eCerrFlags What should be noted in the standard error stream?
 * @param ac_bNoThrow   On failure, return a nullptr, don't throw a bad_alloc.
 * @return  A pointer to the allocated dynamic memory.
 */
void* LeakDebug::DebugNew( const std::size_t ac_uiSize,
                           const OutputFlags ac_eClogFlags,
                           const OutputFlags ac_eCerrFlags,
                           const bool ac_bNoThrow ) throw( std::bad_alloc )
{
    return DebugNew( ac_uiSize, sg_pcStoredFile, sg_uiStoredLine,
                     ac_eClogFlags, ac_eCerrFlags, ac_bNoThrow );
}

/**
 * Allocate a block of dynamic memory and log the allocation.
 * @param ac_uiSize     How much memory to allocate.
 * @param ac_pccFile    File from which the allocation call originated.
 * @param ac_uiLine     Line from which the allocation call originated.
 * @param ac_bNoThrow   On failure, return a nullptr, don't throw a bad_alloc.
 * @return  A pointer to the allocated dynamic memory.
 */
void* LeakDebug::DebugNew( const std::size_t ac_uiSize,
                           const char* const ac_cpcFile,
                           const unsigned int ac_uiLine,
                           const bool ac_bNoThrow ) throw( std::bad_alloc )
{
    return DebugNew( ac_uiSize, ac_cpcFile, ac_uiLine,
                     sg_eDefaultClogFlags, sg_eDefaultCerrFlags, ac_bNoThrow );
}

/**
 * Allocate a block of dynamic memory and log the allocation.
 * @param ac_uiSize     How much memory to allocate.
 * @param ac_cpcFile    File from which the allocation call originated.
 * @param ac_uiLine     Line from which the allocation call originated.
 * @param ac_eClogFlags What should be noted in the standard log stream?
 * @param ac_eCerrFlags What should be noted in the standard error stream?
 * @param ac_bNoThrow   On failure, return a nullptr, don't throw a bad_alloc.
 * @return  A pointer to the allocated dynamic memory.
 */
void* LeakDebug::DebugNew( const std::size_t ac_uiSize,
                           const char* const ac_cpcFile,
                           const unsigned int ac_uiLine,
                           const OutputFlags ac_eClogFlags,
                           const OutputFlags ac_eCerrFlags,
                           const bool ac_bNoThrow ) throw( std::bad_alloc )
{
    // increase recursion level so recursive new/delete calls won't be logged
    ++sg_uiRecursionLevel;

    // Handle zero-byte requests.
    std::size_t iSize = ac_uiSize < 1 ? 1 : ac_uiSize;

    // The value to eventually return.
    void* pResult = std::malloc( iSize );

    // If allocation failed, try to call the new_handler.
    while( pResult == nullptr )
    {
        std::new_handler oHandler = std::set_new_handler( 0 );
        std::set_new_handler( oHandler );
        if( !oHandler )
        {
            break;
        }
        (*oHandler)();
        pResult = std::malloc( iSize );
    }

    // As long as this isn't a recursion from an earlier allocation, log it.
    if( sg_uiRecursionLevel <= 1 )
    {
        LogAllocation( pResult, iSize, ac_cpcFile, ac_uiLine,
                       ac_eClogFlags, ac_eCerrFlags );
        UnstoreFileLine();
    }

    // decrease recursion level so subsequent new/delete calls will be logged.
    --sg_uiRecursionLevel;

    // If allocation failed even after trying to call the new_handler, throw up.
    if( !ac_bNoThrow && pResult == nullptr )
    {
        throw std::bad_alloc();
    }

    // Otherwise, return pointer to allocated memory.
    return pResult;
}

/**
 * Prints a list of allocated dynamic memory to the given stream, if debugging.
 * @param[out] a_roOut  Output stream to write to.
 */
void LeakDebug::DumpLeaks( std::ostream& a_roOut )
{
    // increase recursion level so recursive new/delete calls won't be logged
    ++sg_uiRecursionLevel;

    // loop to print leaks
    for( LeakMap::value_type oEntry : sg_oLeaks )
    {
        a_roOut << oEntry.second << std::endl;
    }

    // decrease recursion level so subsequent new/delete calls will be logged.
    --sg_uiRecursionLevel;
}

/**
 * Provides a list of objects describing currently allocated dynamic memory.
 * @return  Memory leak structs keyed by address, if debugging (else empty map).
 */
LeakDebug::LeakMap LeakDebug::GetLeaks()
{
    // increase recursion level so recursive new/delete calls won't be logged
    ++sg_uiRecursionLevel;

    // Deep copy the list of allocated memory.
    LeakMap oCopy;
    for( LeakMap::value_type oEntry : sg_oLeaks )
    {
        oCopy[ oEntry.first ] = oEntry.second;
    }

    // decrease recursion level so subsequent new/delete calls will be logged.
    --sg_uiRecursionLevel;

    // return deep copy
    return oCopy;
}

/**
 * Is dynamic memory allocation and deallocation being tracked and logged?
 * @return true if recursion level is 0, false otherwise.
 */
bool LeakDebug::IsOn()
{
    return sg_uiRecursionLevel == 0;
}

/**
 * Log a memory allocation to the appropriate streams and start tracking it.
 * @param ac_cpPointer  Address of the allocated memory.
 * @param ac_iSize      Size of the block of memory.
 * @param a_cpcFile     File from which the allocation call originated.
 * @param ac_uiLine     File from which the allocation call originated.
 * @param ac_eClogFlags What should be noted in the standard log stream?
 * @param ac_eCerrFlags What should be noted in the standard error stream?
 */
static void LogAllocation( const void* const ac_cpPointer,
                           const std::size_t ac_iSize,
                           const char* const ac_cpcFile,
                           const unsigned int ac_uiLine,
                           const OutputFlags ac_eClogFlags,
                           const OutputFlags ac_eCerrFlags ) throw()
{
    // If allocation failed, just output an error message to the appropriate
    // stream(s) and return.
    if( nullptr == ac_cpPointer )
    {
        if( nullptr != ac_cpcFile && strlen( ac_cpcFile ) > 0 )
        {
            ClogAndCerrMessages( ac_eClogFlags, ac_eCerrFlags,
                                 OutputFlags::FAILED_ALLOCATIONS,
                                 "FAILED ALLOCATION of ", ac_iSize,
                                 " bytes by ", ac_cpcFile,
                                 "(", ac_uiLine, ")" );
        }
        else
        {
            ClogAndCerrMessages( ac_eClogFlags, ac_eCerrFlags,
                                 OutputFlags::FAILED_ALLOCATIONS,
                                 "FAILED ALLOCATION of ", ac_iSize,
                                 " bytes by unknown" );
        }
        return;
    }

    // Create and store a leak object.
    LeakDebug::Leak oLeak( ac_cpPointer, ac_iSize, ac_cpcFile, ac_uiLine );
    sg_oLeaks[ ac_cpPointer ] = oLeak;

    // Output a success message to the appropriate streams.
    ClogAndCerrMessages( ac_eClogFlags, ac_eCerrFlags,
                         OutputFlags::SUCCESSFUL_ALLOCATIONS, oLeak );
}

/**
 * Log a memory deallocation to the appropriate streams and stop tracking it.
 * @param ac_cpMemory   Address of the deallocated memory.
 * @param ac_cpcFile    File from which the deallocation call originated.
 * @param ac_uiLine     File from which the deallocation call originated.
 * @param ac_eClogFlags What should be noted in the standard log stream?
 * @param ac_eCerrFlags What should be noted in the standard error stream?
 */
static void LogDeallocation( const void* const ac_cpMemory,
                             const char* const ac_cpcFile,
                             const unsigned int ac_uiLine,
                             const OutputFlags ac_eClogFlags,
                             const OutputFlags ac_eCerrFlags ) throw()
{
    // If trying to deallocate the null pointer, just print a message.
    if( ac_cpMemory == nullptr )
    {
        if( nullptr != ac_cpcFile && strlen( ac_cpcFile ) > 0 )
        {
            ClogAndCerrMessages( ac_eClogFlags, ac_eCerrFlags,
                                 OutputFlags::DEALLOCATIONS,
                                 "Null pointer deallocated by ",
                                 ac_cpcFile, "(", ac_uiLine, ")" );
        }
        else
        {
            ClogAndCerrMessages( ac_eClogFlags, ac_eCerrFlags,
                                 OutputFlags::DEALLOCATIONS,
                                 "Null pointer deallocated by unknown" );
        }
        return;
    }

    // Do the same for pointers to memory that wasn't allocated before anyway.
    if( sg_oLeaks.count( ac_cpMemory ) < 1 )
    {
        if( nullptr != ac_cpcFile && strlen( ac_cpcFile ) > 0 )
        {
            ClogAndCerrMessages( ac_eClogFlags, ac_eCerrFlags,
                                 OutputFlags::DEALLOCATIONS,
                                 "Pointer to unallocated memory at ",
                                 ac_cpMemory, " deallocated by ",
                                 ac_cpcFile, "(", ac_uiLine, ")" );
        }
        else
        {
            ClogAndCerrMessages( ac_eClogFlags, ac_eCerrFlags,
                                 OutputFlags::DEALLOCATIONS,
                                 "Pointer to unallocated memory at ",
                                 ac_cpMemory, " deallocated by unknown" );
        }
        return;
    }

    // Remove the leak object from the map
    LeakDebug::Leak oLeak = sg_oLeaks[ ac_cpMemory ];
    sg_oLeaks.erase( ac_cpMemory );

    // Print message to appropriate output streams
    if( nullptr != ac_cpcFile && strlen( ac_cpcFile ) > 0 )
    {
        ClogAndCerrMessages( ac_eClogFlags, ac_eCerrFlags,
                             OutputFlags::DEALLOCATIONS,
                             oLeak, " deallocated by ",
                             ac_cpcFile, "(", ac_uiLine, ")" );
    }
    else
    {
        ClogAndCerrMessages( ac_eClogFlags, ac_eCerrFlags,
                             OutputFlags::DEALLOCATIONS,
                             oLeak, " deallocated by unknown" );
    }
}

/**
 * Print a message to the given stream, if appropriate.
 * @param[out] a_roOut          The output stream to print to.
 * @param[in] ac_eFlags         What should be noted?
 * @param[in] ac_eRequiredFlags What is there to note?
 * @param[in] ac_rArgs          The list of objects that the message is made of.
 */
template< typename... Args >
static void OutputMessage( std::ostream& a_roOut,
                           const OutputFlags ac_eFlags,
                           const OutputFlags ac_eRequiredFlags,
                           const Args&... ac_rArgs ) throw()
{
    // If the required flags aren't in the given flags, don't do anything.
    if( !( ac_eFlags & ac_eRequiredFlags ) )
    {
        return;
    }

    // Otherwise, try to print the message, eating any exceptions thrown.
    try
    {
        OutputMessage( a_roOut, ac_rArgs... );
        a_roOut << std::endl;
    }
    catch( std::exception& oException ) {}  // eat exception
}

/**
 * Print the given arguments to the given stream recursively.
 * @param[out] a_roOut  The output stream to print to.
 * @param[in] ac_rArg   The argument to print before recursing.
 * @param[in] ac_rArgs  The rest of the arguments.
 */
template< typename T, typename... Args >
static void OutputMessage( std::ostream& a_roOut,
                           const T& ac_rArg,
                           const Args&... ac_rArgs )
{
    // Print the first part of the message...
    OutputMessage( a_roOut, ac_rArg );

    // ... then recurse to print the rest of it.
    OutputMessage( a_roOut, ac_rArgs... );
}

/**
 * Print the given object to the given stream.
 * @param[out] a_roOut  The output stream to print to.
 * @param[in] ac_rArg   The argument to print.
 */
template< typename T >
static void OutputMessage( std::ostream& a_roOut, const T& ac_rArg )
{
    a_roOut << ac_rArg;
}

/**
 * Set flags for what to print to std::clog and std::cerr if not specified.
 * @param ac_eDefaultClogFlags  What should be noted in standard log stream?
 * @param ac_eDefaultCerrFlags  What should be noted in standard error stream?
 */
void LeakDebug::SetOutputFlags( const OutputFlags ac_eDefaultClogFlags,
                                const OutputFlags ac_eDefaultCerrFlags )
{
    sg_eDefaultClogFlags = ac_eDefaultClogFlags;
    sg_eDefaultCerrFlags = ac_eDefaultCerrFlags;
}

/**
 * Start tracking dynamic memory allocations and deallocations.
 * Set the recursion level to zero so that non-recursed calls to DebugNew and
 * DebugDelete will be tracked and logged.
 */
void LeakDebug::Start()
{
    sg_uiRecursionLevel = 0;
}

/**
 * Start tracking dynamic memory allocations and deallocations.
 * Set the recursion level to zero so that non-recursed calls to DebugNew and
 * DebugDelete will be tracked and logged.  Set default output flags for what to
 * print to std::clog and std::cerr if no flags are specified.
 * @param ac_eDefaultClogFlags  What should be noted in standard log stream?
 * @param ac_eDefaultCerrFlags  What should be noted in standard error stream?
 */
void LeakDebug::Start( const OutputFlags ac_eDefaultClogFlags,
                       const OutputFlags ac_eDefaultCerrFlags )
{
    SetOutputFlags( ac_eDefaultClogFlags, ac_eDefaultCerrFlags );
    Start();
}

/**
 * Set the recursion level to one so that even non-recursed calls to DebugNew
 * and DebugDelete will not be tracked or logged.
 */
void LeakDebug::Stop()
{
    sg_uiRecursionLevel = 1;
}

/**
 * Stores a file name and line number for use by a subsequent _New or _Delete.
 * This way, DebugNew() and DebugDelete() can be called from the code without
 * having to pass in parameters for file and line, which makes it easier to set
 * up macros calling redefined new and delete operators.
 * @see leak_debug.h for macros that use this.
 * @param ac_cpcFile    File from which a later DebugNew/Delete will originate.
 * @param ac_uiLine     Line from which a later DebugNew/Delete will originate.
 */
void LeakDebug::StoreFileLine( const char* const ac_cpcFile,
                               const unsigned int ac_uiLine )
    throw()
{
    // increase recursion level so recursive new/delete calls won't be logged
    ++sg_uiRecursionLevel;

    // store file name
    if( nullptr != sg_pcStoredFile )
    {
        std::free( sg_pcStoredFile );
    }
    if( nullptr != ac_cpcFile )
    {
        sg_pcStoredFile = (char*)std::malloc( sizeof( char ) *
                                              ( strlen( ac_cpcFile ) + 1 ) );
        strcpy( sg_pcStoredFile, ac_cpcFile );
    }
    else
    {
        sg_pcStoredFile = nullptr;
    }

    // store line
    sg_uiStoredLine = ac_uiLine;

    // decrease recursion level so subsequent new/delete calls will be logged.
    --sg_uiRecursionLevel;
}

/**
 * Clear the file name and line number stored by StoreFileLine().
 */
void LeakDebug::UnstoreFileLine() throw()
{
    // increase recursion level so recursive new/delete calls won't be logged
    ++sg_uiRecursionLevel;

    // reset file name and line
    if( nullptr != sg_pcStoredFile )
    {
        std::free( sg_pcStoredFile );
        sg_pcStoredFile = nullptr;
    }
    sg_uiStoredLine = 0;

    // decrease recursion level so subsequent new/delete calls will be logged.
    --sg_uiRecursionLevel;
}
