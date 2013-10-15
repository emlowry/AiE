/** ***************************************************************************
 * @file      LeakDebug.cpp
 * @author    Elizabeth Lowry
 * @date      October 7, 2013 - October 8, 2013
 * @brief     Memory leak logging.
 * @details   Implementations for the functions in the static library.
 * @par       Last Modification:
 *              Implementations!
 **************************************************************************** */

#include "Leak.h"
#include "LeakDebug.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <new>
#include <string>

namespace LeakDebug
{

// These functions are only used inside this cpp.  There's no need to expose
// them to library users.
template< typename... Args >
static void ClogAndCerrMessages( OutputFlags a_eClogFlags,
                                 OutputFlags a_eCerrFlags,
                                 OutputFlags a_eRequiredFlags,
                                 Args&... a_rArgs ) throw();
static void LogAllocation( void* a_pPointer,
                           std::size_t a_iSize,
                           char* const a_pccFile,
                           unsigned int a_uiLine,
                           OutputFlags a_eClogFlags,
                           OutputFlags a_eCerrFlags ) throw();
static void LogDeallocation( void* a_pMemory,
                             char* const a_pccFile,
                             unsigned int a_uiLine,
                             OutputFlags a_eClogFlags,
                             OutputFlags a_eCerrFlags ) throw();
template< typename... Args >
static void OutputMessage( std::ostream& a_roOut,
                           OutputFlags a_eFlags,
                           OutputFlags a_eRequiredFlags,
                           Args&... a_rArgs ) throw();
template< typename T, typename... Args >
static void OutputMessage( std::ostream& a_roOut, T& a_rArg, Args&... a_rArgs );
template< typename T >
static void OutputMessage( std::ostream& a_roOut, T& a_rArg );

}   // namespace LeakDebug

/**
 *  The file name stored by _StoreFileLine
 */
static std::string sg_oStoredFile = "";

/**
 * The line number stored by _StoreFileLine
 */
static unsigned int sg_uiStoredLine = 0;

/**
 * Map of allocated memory
 */
static LeakDebug::LeakMap sg_oLeaks;

/**
 * Recursion level for DebugNew and DebugDelete calls, so we don't end up
 * logging the allocation of everything used for allocation logging - otherwise,
 * we'd end up in an infinite loop whenever we allocated/deallocated dynamic
 * memory.
 */
static unsigned int sg_uiRecursionLevel = 0;

/**
 * Print a message to the standard log and/or error streams, as appropriate.
 * @param a_eClogFlags      What should be noted in the standard log stream?
 * @param a_eCerrFlags      What should be noted in the standard error stream?
 * @param a_eRequiredFlags  What is there to note?
 * @param a_rArgs           The list of objects that the message is composed of.
 */
template< typename... Args >
static void LeakDebug::ClogAndCerrMessages( OutputFlags a_eClogFlags,
                                            OutputFlags a_eCerrFlags,
                                            OutputFlags a_eRequiredFlags,
                                            Args&... a_rArgs ) throw()
{
    OutputMessage( std::clog, a_eClogFlags, a_eRequiredFlags, a_rArgs... );
    OutputMessage( std::cerr, a_eCerrFlags, a_eRequiredFlags, a_rArgs... );
}

/**
 * Deallocate a block of dynamic memory and log the deallocation.
 * @param[in,out] a_pMemory Address of the memory to deallocate.
 * @param[in] a_eClogFlags  What should be noted in the standard log stream?
 * @param[in] a_eCerrFlags  What should be noted in the standard error stream?
 */
void LeakDebug::DebugDelete( void* a_pMemory,
                             OutputFlags a_eClogFlags,
                             OutputFlags a_eCerrFlags ) throw()
{
    char acEmpty[] = "";
    DebugDelete( a_pMemory,
                 sg_oStoredFile.empty() ? acEmpty : &sg_oStoredFile[0],
                 sg_uiStoredLine, a_eClogFlags, a_eCerrFlags );
    UnstoreFileLine();
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
                             char* const a_pccFile,
                             unsigned int ac_uiLine,
                             OutputFlags ac_eClogFlags,
                             OutputFlags ac_eCerrFlags ) throw()
{
    // increase recursion level
    ++sg_uiRecursionLevel;

    // deallocate memory
    if( a_pMemory != nullptr )
    {
        free(a_pMemory);
    }

    // As long as this isn't a recursion from an earlier deallocation, log it.
    if( sg_uiRecursionLevel <= 1 )
    {
        LogDeallocation( a_pMemory, a_pccFile, ac_uiLine,
                         ac_eClogFlags, ac_eCerrFlags );
    }

    // decrease recursion level
    --sg_uiRecursionLevel;
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
                           OutputFlags a_eClogFlags,
                           OutputFlags a_eCerrFlags,
                           bool a_bNoThrow ) throw( std::bad_alloc )
{
    try
    {
        // Try to allocate memory, using the stored filename and line.
        char acEmpty[] = "";
        void* toReturn =
            DebugNew( a_iSize,
                      sg_oStoredFile.empty() ? acEmpty : &sg_oStoredFile[0],
                      sg_uiStoredLine, a_eClogFlags, a_eCerrFlags,
                      a_bNoThrow );

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
 * @param a_eClogFlags  What should be noted in the standard log stream?
 * @param a_eCerrFlags  What should be noted in the standard error stream?
 * @param a_bNoThrow    On failure, return a nullptr, don't throw a bad_alloc.
 * @return  A pointer to the allocated dynamic memory.
 */
void* LeakDebug::DebugNew( std::size_t a_iSize,
                           char* const a_pccFile,
                           unsigned int a_uiLine,
                           OutputFlags a_eClogFlags,
                           OutputFlags a_eCerrFlags,
                           bool a_bNoThrow ) throw( std::bad_alloc )
{
    // increase recursion level
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
        LogAllocation( pResult, a_iSize, a_pccFile, a_uiLine,
                       a_eClogFlags, a_eCerrFlags );
    }

    // decrease recursion level
    --sg_uiRecursionLevel;

    // If allocation failed even after trying to call the new_handler, throw up.
    if( !a_bNoThrow && pResult == nullptr )
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
    for( LeakMap::value_type oEntry : sg_oLeaks )
    {
        a_roOut << oEntry.second << std::endl;
    }
}

/**
 * Provides a list of objects describing currently allocated dynamic memory.
 * @return  Memory leak structs keyed by address, if debugging (else empty map).
 */
LeakDebug::LeakMap LeakDebug::GetLeaks()
{
    // Deep copy the list of allocated memory.
    LeakMap oCopy;
    for( LeakMap::value_type oEntry : sg_oLeaks )
    {
        oCopy[ oEntry.first ] = oEntry.second;
    }
    return oCopy;
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
void LeakDebug::LogAllocation( void* a_pPointer,
                               std::size_t a_iSize,
                               char* const a_pccFile,
                               unsigned int a_uiLine,
                               LeakDebug::OutputFlags a_eClogFlags,
                               LeakDebug::OutputFlags a_eCerrFlags ) throw()
{
    // If allocation failed, just output an error message to the appropriate
    // stream(s) and return.
    if( a_pPointer == nullptr )
    {
        ClogAndCerrMessages( a_eClogFlags, a_eCerrFlags,
                             OutputFlags::FAILED_ALLOCATIONS,
                             "FAILED ALLOCATION of ", a_iSize, " bytes by ",
                             a_pccFile, "(", a_uiLine, ")" );
        return;
    }

    // Create a Leak struct.
    char* pcName = new char[ strlen( a_pccFile ) + 1 ];
    strcpy( pcName, a_pccFile );
    Leak oLeak = { a_pPointer, a_iSize, pcName, a_uiLine };

    // Store a copy of the struct.
    sg_oLeaks[ a_pPointer ] = oLeak;

    // Output a success message to the appropriate streams.
    ClogAndCerrMessages( a_eClogFlags, a_eCerrFlags,
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
void LeakDebug::LogDeallocation( void* a_pMemory,
                                 char* const a_pccFile,
                                 unsigned int a_uiLine,
                                 OutputFlags a_eClogFlags,
                                 OutputFlags a_eCerrFlags ) throw()
{
    // If trying to deallocate the null pointer, just print a message.
    if( a_pMemory == nullptr )
    {
        ClogAndCerrMessages( a_eClogFlags, a_eCerrFlags,
                             OutputFlags::DEALLOCATIONS,
                             "Null pointer deallocated by ",
                             a_pccFile, "(", a_uiLine, ")" );
        return;
    }

    // Do the same for pointers to memory that wasn't allocated before anyway.
    if( sg_oLeaks.count( a_pMemory ) < 1 )
    {
        ClogAndCerrMessages( a_eClogFlags, a_eCerrFlags,
                             OutputFlags::DEALLOCATIONS,
                             "Pointer to unallocated memory at ",
                             a_pMemory, " deallocated by ",
                             a_pccFile, "(", a_uiLine, ")" );
        return;
    }

    // Remove the leak object from the map
    Leak oLeak = sg_oLeaks[ a_pMemory ];
    sg_oLeaks.erase( a_pMemory );

    // Print message to appropriate output streams
    ClogAndCerrMessages( a_eClogFlags, a_eCerrFlags,
                         OutputFlags::DEALLOCATIONS,
                         oLeak, "deallocated by ",
                         a_pccFile, "(", a_uiLine, ")" );

    // free memory used for file name string
    delete[] oLeak.file;
}

/**
 * Print a message to the given stream, if appropriate.
 * @param[out] a_roOut          The output stream to print to.
 * @param[in] a_eFlags          What should be noted?
 * @param[in] a_eRequiredFlags  What is there to note?
 * @param[in] a_rArgs           The list of objects that the message is made of.
 */
template< typename... Args >
static void LeakDebug::OutputMessage( std::ostream& a_roOut,
                                      OutputFlags a_eFlags,
                                      OutputFlags a_eRequiredFlags,
                                      Args&... a_rArgs ) throw()
{
    // If the required flags aren't in the given flags, don't do anything.
    if( !( a_eFlags & a_eRequiredFlags ) )
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
static void LeakDebug::OutputMessage( std::ostream& a_roOut,
                                      T& a_rArg,
                                      Args&... a_rArgs )
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
static void LeakDebug::OutputMessage( std::ostream& a_roOut, T& a_rArg )
{
    a_roOut << a_rArg;
}

/**
 * Stores a file name and line number for use by a subsequent _New or _Delete.
 * This way, _New() and _Delete() can be called from the code without having to
 * pass in parameters for file and line, which makes it easier to set up macros
 * calling redefined new and delete operators.
 * @see LeakDebug.h for macros that use this.
 * @param a_pccFile File from which a following _New or _Delete will originate.
 * @param a_iLine   Line from which a following _New or _Delete will originate.
 */
void LeakDebug::StoreFileLine( char* const a_pccFile,
                                    unsigned int a_iLine )
    throw()
{
    sg_oStoredFile = a_pccFile;
    sg_uiStoredLine = a_iLine;
}

/**
 * Clear the file name and line number stored by _StoreFileLine().
 */
void LeakDebug::UnstoreFileLine() throw()
{
    sg_oStoredFile = "";
    sg_uiStoredLine = 0;
}
