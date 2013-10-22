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
#include <string>

using LeakDebug::OutputFlags;

// These functions are only used inside this cpp.  There's no need to expose
// them to library users.
template< typename... Args >
static void ClogAndCerrMessages( const OutputFlags ac_eClogFlags,
                                 const OutputFlags ac_eCerrFlags,
                                 const OutputFlags ac_eRequiredFlags,
                                 Args&... a_rArgs ) throw();
static void LogAllocation( void* a_pPointer,
                           std::size_t a_iSize,
                           const std::string& ac_roFile,
                           const unsigned int ac_uiLine,
                           const OutputFlags ac_eClogFlags,
                           const OutputFlags ac_eCerrFlags ) throw();
static void LogDeallocation( void* a_pMemory,
                             const std::string& ac_roFile,
                             const unsigned int ac_uiLine,
                             const OutputFlags ac_eClogFlags,
                             const OutputFlags ac_eCerrFlags ) throw();
template< typename... Args >
static void OutputMessage( std::ostream& a_roOut,
                           const OutputFlags ac_eFlags,
                           const OutputFlags ac_eRequiredFlags,
                           Args&... a_rArgs ) throw();
template< typename T, typename... Args >
static void OutputMessage( std::ostream& a_roOut, T& a_rArg, Args&... a_rArgs );
template< typename T >
static void OutputMessage( std::ostream& a_roOut, T& a_rArg );

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
static std::string sg_oStoredFile = "";

/**
 * The line number stored by _StoreFileLine
 */
static unsigned int sg_uiStoredLine = 0;

/**
 * Print a message to the standard log and/or error streams, as appropriate.
 * @param a_eClogFlags      What should be noted in the standard log stream?
 * @param a_eCerrFlags      What should be noted in the standard error stream?
 * @param a_eRequiredFlags  What is there to note?
 * @param a_rArgs           The list of objects that the message is composed of.
 */
template< typename... Args >
static void ClogAndCerrMessages( const OutputFlags ac_eClogFlags,
                                 const OutputFlags ac_eCerrFlags,
                                 const OutputFlags ac_eRequiredFlags,
                                 Args&... a_rArgs ) throw()
{
    OutputMessage( std::clog, ac_eClogFlags, ac_eRequiredFlags, a_rArgs... );
    OutputMessage( std::cerr, ac_eCerrFlags, ac_eRequiredFlags, a_rArgs... );
}

/**
 * Deallocate a block of dynamic memory and log the deallocation.
 * @param[in,out] a_pMemory Address of the memory to deallocate.
 */
void LeakDebug::DebugDelete( void* a_pMemory ) throw()
{
    DebugDelete( a_pMemory, sg_eDefaultClogFlags, sg_eDefaultCerrFlags );
}

/**
 * Deallocate a block of dynamic memory and log the deallocation.
 * @param[in,out] a_pMemory Address of the memory to deallocate.
 * @param[in] a_eClogFlags  What should be noted in the standard log stream?
 * @param[in] a_eCerrFlags  What should be noted in the standard error stream?
 */
void LeakDebug::DebugDelete( void* a_pMemory,
                             const OutputFlags ac_eClogFlags,
                             const OutputFlags ac_eCerrFlags ) throw()
{
    DebugDelete( a_pMemory, sg_oStoredFile.c_str(), sg_uiStoredLine,
                 ac_eClogFlags, ac_eCerrFlags );
    UnstoreFileLine();
}

/**
 * Deallocate a block of dynamic memory and log the deallocation.
 * @param[in,out] a_pMemory Address of the memory to deallocate.
 * @param[in] a_pccFile     File from which the deallocation call originated.
 * @param[in] a_uiLine      Line from which the deallocation call originated.
 */
void LeakDebug::DebugDelete( void* a_pMemory,
                             const char* const ac_pccFile,
                             const unsigned int ac_uiLine ) throw()
{
    DebugDelete( a_pMemory, ac_pccFile, ac_uiLine,
                 sg_eDefaultClogFlags, sg_eDefaultCerrFlags );
}

/**
 * Deallocate a block of dynamic memory and log the deallocation.
 * @param[in,out] a_pMemory Address of the memory to deallocate.
 * @param[in] a_pccFile     File from which the deallocation call originated.
 * @param[in] a_uiLine      Line from which the deallocation call originated.
 * @param[in] a_eClogFlags  What should be noted in the standard log stream?
 * @param[in] a_eCerrFlags  What should be noted in the standard error stream?
 */
void LeakDebug::DebugDelete( void* a_pMemory,
                             const char* const ac_pccFile,
                             const unsigned int ac_uiLine,
                             const OutputFlags ac_eClogFlags,
                             const OutputFlags ac_eCerrFlags ) throw()
{
    // increase recursion level so recursive new/delete calls won't be logged
    ++sg_uiRecursionLevel;

    // deallocate memory
    if( a_pMemory != nullptr )
    {
        free(a_pMemory);
    }

    // As long as this isn't a recursion from an earlier deallocation, log it.
    if( sg_uiRecursionLevel <= 1 )
    {
        std::string oFile = ac_pccFile;
        LogDeallocation( a_pMemory, oFile, ac_uiLine,
                         ac_eClogFlags, ac_eCerrFlags );
    }

    // decrease recursion level so subsequent new/delete calls will be logged.
    --sg_uiRecursionLevel;
}

/**
 * Allocate a block of dynamic memory and log the allocation.
 * @param a_iSize       How much memory to allocate.
 * @param a_bNoThrow    On failure, return a nullptr, don't throw a bad_alloc.
 * @return  A pointer to the allocated dynamic memory.
 */
void* LeakDebug::DebugNew( std::size_t a_iSize, const bool ac_bNoThrow )
    throw( std::bad_alloc )
{
    return DebugNew( a_iSize, sg_eDefaultClogFlags,
                     sg_eDefaultCerrFlags, ac_bNoThrow );
}

/**
 * Allocate a block of dynamic memory and log the allocation.
 * @param a_iSize       How much memory to allocate.
 * @param a_eClogFlags  What should be noted in the standard log stream?
 * @param a_eCerrFlags  What should be noted in the standard error stream?
 * @param a_bNoThrow    On failure, return a nullptr, don't throw a bad_alloc.
 * @return  A pointer to the allocated dynamic memory.
 */
void* LeakDebug::DebugNew( std::size_t a_iSize,
                           const OutputFlags ac_eClogFlags,
                           const OutputFlags ac_eCerrFlags,
                           const bool ac_bNoThrow ) throw( std::bad_alloc )
{
    try
    {
        // Try to allocate memory, using the stored filename and line.
        void* toReturn = DebugNew( a_iSize, sg_oStoredFile.c_str(),
                                   sg_uiStoredLine, ac_eClogFlags,
                                   ac_eCerrFlags, ac_bNoThrow );

        // If allocation succeeded, clear stored filename and line, then return.
        UnstoreFileLine();
        return toReturn;
    }
    catch( std::bad_alloc& oException )
    {
        // If allocation failed, clear stored filename and line, then throw up.
        UnstoreFileLine();
        throw oException;
    }
}

/**
 * Allocate a block of dynamic memory and log the allocation.
 * @param a_iSize       How much memory to allocate.
 * @param a_pccFile     File from which the allocation call originated.
 * @param a_uiLine      Line from which the allocation call originated.
 * @param a_bNoThrow    On failure, return a nullptr, don't throw a bad_alloc.
 * @return  A pointer to the allocated dynamic memory.
 */
void* LeakDebug::DebugNew( std::size_t a_iSize,
                           const char* const ac_pccFile,
                           const unsigned int ac_uiLine,
                           const bool ac_bNoThrow ) throw( std::bad_alloc )
{
    return DebugNew( a_iSize, ac_pccFile, ac_uiLine,
                     sg_eDefaultClogFlags, sg_eDefaultCerrFlags, ac_bNoThrow );
}

/**
 * Allocate a block of dynamic memory and log the allocation.
 * @param a_iSize       How much memory to allocate.
 * @param a_pccFile     File from which the allocation call originated.
 * @param a_uiLine      Line from which the allocation call originated.
 * @param a_eClogFlags  What should be noted in the standard log stream?
 * @param a_eCerrFlags  What should be noted in the standard error stream?
 * @param a_bNoThrow    On failure, return a nullptr, don't throw a bad_alloc.
 * @return  A pointer to the allocated dynamic memory.
 */
void* LeakDebug::DebugNew( std::size_t a_iSize,
                           const char* const ac_pccFile,
                           const unsigned int ac_uiLine,
                           const OutputFlags ac_eClogFlags,
                           const OutputFlags ac_eCerrFlags,
                           const bool ac_bNoThrow ) throw( std::bad_alloc )
{
    // increase recursion level so recursive new/delete calls won't be logged
    ++sg_uiRecursionLevel;

    // Handle zero-byte requests.
    std::size_t iSize = a_iSize < 1 ? 1 : a_iSize;

    // The value to eventually return.
    void* pResult = malloc(iSize);

    // If allocation failed, try to call the new_handler.
    while( pResult == nullptr )
    {
        std::new_handler oHandler = std::set_new_handler(0);
        std::set_new_handler(oHandler);
        if( !oHandler )
        {
            break;
        }
        (*oHandler)();
        pResult = malloc(iSize);
    }

    // As long as this isn't a recursion from an earlier allocation, log it.
    if( sg_uiRecursionLevel <= 1 )
    {
        std::string oFile = ac_pccFile;
        LogAllocation( pResult, a_iSize, oFile, ac_uiLine,
                       ac_eClogFlags, ac_eCerrFlags );
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
 * @param a_pPointer    Address of the allocated memory.
 * @param a_iSize       Size of the block of memory.
 * @param a_pccFile     File from which the allocation call originated.
 * @param a_uiLine      File from which the allocation call originated.
 * @param a_eClogFlags  What should be noted in the standard log stream?
 * @param a_eCerrFlags  What should be noted in the standard error stream?
 */
static void LogAllocation( void* a_pPointer,
                           std::size_t a_iSize,
                           const std::string& ac_roFile,
                           const unsigned int ac_uiLine,
                           const OutputFlags ac_eClogFlags,
                           const OutputFlags ac_eCerrFlags ) throw()
{
    // If allocation failed, just output an error message to the appropriate
    // stream(s) and return.
    if( a_pPointer == nullptr )
    {
        if( !ac_roFile.empty() )
        {
            ClogAndCerrMessages( ac_eClogFlags, ac_eCerrFlags,
                                 OutputFlags::FAILED_ALLOCATIONS,
                                 "FAILED ALLOCATION of ", a_iSize, " bytes by ",
                                 ac_roFile, "(", ac_uiLine, ")" );
        }
        else
        {
            ClogAndCerrMessages( ac_eClogFlags, ac_eCerrFlags,
                                 OutputFlags::FAILED_ALLOCATIONS,
                                 "FAILED ALLOCATION of ", a_iSize, " bytes by ",
                                 "unknown" );
        }
        return;
    }

    // Create a Leak struct.
    LeakDebug::Leak oLeak = { a_pPointer, a_iSize, ac_roFile, ac_uiLine };

    // Store a copy of the struct.
    sg_oLeaks[ a_pPointer ] = oLeak;

    // Output a success message to the appropriate streams.
    ClogAndCerrMessages( ac_eClogFlags, ac_eCerrFlags,
                         OutputFlags::SUCCESSFUL_ALLOCATIONS, oLeak );
}

/**
 * Log a memory deallocation to the appropriate streams and stop tracking it.
 * @param a_pMemory     Address of the deallocated memory.
 * @param a_pccFile     File from which the deallocation call originated.
 * @param a_uiLine      File from which the deallocation call originated.
 * @param a_eClogFlags  What should be noted in the standard log stream?
 * @param a_eCerrFlags  What should be noted in the standard error stream?
 */
static void LogDeallocation( void* a_pMemory,
                             const std::string& ac_roFile,
                             const unsigned int ac_uiLine,
                             const OutputFlags ac_eClogFlags,
                             const OutputFlags ac_eCerrFlags ) throw()
{
    // If trying to deallocate the null pointer, just print a message.
    if( a_pMemory == nullptr )
    {
        if( !ac_roFile.empty() )
        {
            ClogAndCerrMessages( ac_eClogFlags, ac_eCerrFlags,
                                 OutputFlags::DEALLOCATIONS,
                                 "Null pointer deallocated by ",
                                 ac_roFile, "(", ac_uiLine, ")" );
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
    if( sg_oLeaks.count( a_pMemory ) < 1 )
    {
        if( !ac_roFile.empty() )
        {
            ClogAndCerrMessages( ac_eClogFlags, ac_eCerrFlags,
                                 OutputFlags::DEALLOCATIONS,
                                 "Pointer to unallocated memory at ",
                                 a_pMemory, " deallocated by ",
                                 ac_roFile, "(", ac_uiLine, ")" );
        }
        else
        {
            ClogAndCerrMessages( ac_eClogFlags, ac_eCerrFlags,
                                 OutputFlags::DEALLOCATIONS,
                                 "Pointer to unallocated memory at ",
                                 a_pMemory, " deallocated by unknown" );
        }
        return;
    }

    // Remove the leak object from the map
    LeakDebug::Leak oLeak = sg_oLeaks[ a_pMemory ];
    sg_oLeaks.erase( a_pMemory );

    // Print message to appropriate output streams
    if( !ac_roFile.empty() )
    {
        ClogAndCerrMessages( ac_eClogFlags, ac_eCerrFlags,
                             OutputFlags::DEALLOCATIONS,
                             oLeak, " deallocated by ",
                             ac_roFile, "(", ac_uiLine, ")" );
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
 * @param[in] a_eFlags          What should be noted?
 * @param[in] a_eRequiredFlags  What is there to note?
 * @param[in] a_rArgs           The list of objects that the message is made of.
 */
template< typename... Args >
static void OutputMessage( std::ostream& a_roOut,
                           const OutputFlags ac_eFlags,
                           const OutputFlags ac_eRequiredFlags,
                           Args&... a_rArgs ) throw()
{
    // If the required flags aren't in the given flags, don't do anything.
    if( !( ac_eFlags & ac_eRequiredFlags ) )
    {
        return;
    }

    // Otherwise, try to print the message, eating any exceptions thrown.
    try
    {
        OutputMessage( a_roOut, a_rArgs... );
        a_roOut << std::endl;
    }
    catch( std::exception& oException ) {}  // eat exception
}

/**
 * Print the given arguments to the given stream recursively.
 * @param[out] a_roOut  The output stream to print to.
 * @param[in] a_rArg    The argument to print before recursing.
 * @param[in] a_rArgs   The rest of the arguments.
 */
template< typename T, typename... Args >
static void OutputMessage( std::ostream& a_roOut, T& a_rArg, Args&... a_rArgs )
{
    // Print the first part of the message...
    OutputMessage( a_roOut, a_rArg );

    // ... then recurse to print the rest of it.
    OutputMessage( a_roOut, a_rArgs... );
}

/**
 * Print the given object to the given stream.
 * @param[out] a_roOut  The output stream to print to.
 * @param[in] a_rArg    The argument to print.
 */
template< typename T >
static void OutputMessage( std::ostream& a_roOut, T& a_rArg )
{
    a_roOut << a_rArg;
}

/**
 * Set flags for what to print to std::clog and std::cerr if not specified.
 * @param a_eDefaultClogFlags What should be noted in the standard log stream?
 * @param a_eDefaultCerrFlags What should be noted in the standard error stream?
 */
void LeakDebug::SetOutputFlags( OutputFlags a_eDefaultClogFlags,
                                OutputFlags a_eDefaultCerrFlags )
{
    sg_eDefaultClogFlags = a_eDefaultClogFlags;
    sg_eDefaultCerrFlags = a_eDefaultCerrFlags;
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
 * @param a_eDefaultClogFlags
 * @param a_eDefaultCerrFlags
 */
void LeakDebug::Start( OutputFlags a_eDefaultClogFlags,
                       OutputFlags a_eDefaultCerrFlags )
{
    SetOutputFlags( a_eDefaultClogFlags, a_eDefaultCerrFlags );
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
 * @param a_pccFile File from which a following DebugNew/Delete will originate.
 * @param a_iLine   Line from which a following DebugNew/Delete will originate.
 */
void LeakDebug::StoreFileLine( const char* const ac_pccFile,
                               const unsigned int ac_uiLine )
    throw()
{
    // increase recursion level so recursive new/delete calls won't be logged
    ++sg_uiRecursionLevel;

    // store file name and line
    sg_oStoredFile = ac_pccFile;
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
    sg_oStoredFile = "";
    sg_uiStoredLine = 0;

    // decrease recursion level so subsequent new/delete calls will be logged.
    --sg_uiRecursionLevel;
}
