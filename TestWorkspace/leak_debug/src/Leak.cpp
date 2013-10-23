/** ***************************************************************************
 * @file      Leak.cpp
 * @author    Elizabeth Lowry
 * @date      October 15, 2013 - October 16, 2013
 * @brief     Memory leak logging.
 * @details   Implementations for the Leak struct operators.
 * @par       Last Modification:
 *              Debugging.
 **************************************************************************** */

#include "Leak.h"
#include <cstdlib>
#include <cstring>
#include <iostream>

// only used within this file
static int CompareCStrings( const char* const ac_cpFirstCString,
                            const char* const ac_cpSecondCString );
static int ComparePointers( const void* const ac_cpFirstPointer,
                            const void* const ac_cpSecondPointer );

/**
 * Default constructor - leak points to null, has a size of 0, and no origin.
 */
LeakDebug::Leak::Leak() : Leak( nullptr, 0, nullptr, 0 ) {}

/**
 * Parameterized constructor deep copies file name.
 * @param ac_cpAddress  Memory address of the leak.
 * @param ac_uiSize     Size of the leak.
 * @param ac_cpcFile    File that allocated the leak.
 * @param ac_uiLine     Line on which the leak was allocated.
 */
LeakDebug::Leak::Leak( const void* const ac_cpAddress,
                       const std::size_t ac_uiSize,
                       const char* const ac_cpcFile,
                       const unsigned int ac_uiLine )
    : m_pAddress( ac_cpAddress ), m_uiSize( ac_uiSize ), m_uiLine( ac_uiLine )
{
    if( nullptr == ac_cpcFile )
    {
        m_pcFile = nullptr;
    }
    else
    {
        m_pcFile = (char*)std::malloc( sizeof( char ) *
                                       ( strlen( ac_cpcFile ) + 1 ) );
        strcpy( m_pcFile, ac_cpcFile );
    }
}

/**
 * Copy constructor.  Calls parameterized constructor to deep copy file name.
 * @param ac_roLeak The Leak to copy from.
 */
LeakDebug::Leak::Leak( const Leak& ac_roLeak )
    : Leak( ac_roLeak.m_pAddress, ac_roLeak.m_uiSize,
            ac_roLeak.m_pcFile, ac_roLeak.m_uiLine ) {}

/**
 * Destructor deallocates file name
 */
LeakDebug::Leak::~Leak()
{
    std::free( m_pcFile );
    m_pcFile = nullptr;
}

/**
 * Assignement operator deep copies file name.
 * @param ac_roLeak The Leak to copy data from.
 * @return  A reference to this leak.
 */
LeakDebug::Leak& LeakDebug::Leak::operator=( const Leak& ac_roLeak )
{
    if( &ac_roLeak != this )
    {
        SetFile( ac_roLeak.m_pcFile );
        m_uiLine = ac_roLeak.m_uiLine;
        m_pAddress = ac_roLeak.m_pAddress;
        m_uiSize = ac_roLeak.m_uiSize;
    }
    return *this;
}


/**
 * Compares two CStrings, handling null pointers.
 * If both pointers are null, return 0.  If only the first is null, return -1.
 * If only the second is null, return 1.  Otherwise, use strcmp.
 * @param ac_cpFirstCString     First CString to compare.
 * @param ac_cpSecondCString    First CString to compare.
 * @return
 */
static int CompareCStrings( const char* const ac_cpFirstCString,
                            const char* const ac_cpSecondCString )
{
    if( nullptr == ac_cpFirstCString && nullptr == ac_cpSecondCString )
    {
        return 0;
    }
    if( nullptr == ac_cpFirstCString )
    {
        return -1;
    }
    if( nullptr == ac_cpSecondCString )
    {
        return 1;
    }
    return strcmp( ac_cpFirstCString, ac_cpSecondCString );
}

/**
 * Compares two pointers.
 * If both are null, return 0.  If only first is null, return -1.  If only
 * second is null, return 1.  If neither is null, compare based on integer value
 * of addresses.
 * @param a_pFirstPointer   First pointer in comparison.
 * @param a_pSecondPointer  Second pointer in comparison.
 * @return  0, 1, or -1, depending on how first pointer compares to second.
 */
static int ComparePointers( const void* const ac_cpFirstPointer,
                            const void* const ac_cpSecondPointer )
{
    // If one or both pointers are null, comparison is easy
    if( nullptr == ac_cpFirstPointer && nullptr == ac_cpSecondPointer )
    {
        return 0;
    }
    if( nullptr == ac_cpFirstPointer )
    {
        return -1;
    }
    if( nullptr == ac_cpSecondPointer )
    {
        return 1;
    }

    // Otherwise, convert addresses to unsigned long long integers - hopefully
    // this will be a large enough integer type to hold any pointer value.
    unsigned long long ullFirst = (unsigned long long)ac_cpFirstPointer;
    unsigned long long ullSecond = (unsigned long long)ac_cpSecondPointer;
    if( ullFirst < ullSecond )
    {
        return -1;
    }
    if( ullFirst > ullSecond )
    {
        return 1;
    }
    return 0;
}

/**
 * Memory address accessor.
 * @return  The memory address for this leak.
 */
const void* LeakDebug::Leak::GetAddress() const
{
    return m_pAddress;
}

/**
 * File name accessor.
 * @return  The file that allocated this leak.
 */
const char* LeakDebug::Leak::GetFile() const
{
    return m_pcFile;
}

/**
 * Line number accessor.
 * @return  The line on which the leak was allocated.
 */
unsigned int LeakDebug::Leak::GetLine() const
{
    return m_uiLine;
}

/**
 * Size accessor.
 * @return  The size of this leak.
 */
std::size_t LeakDebug::Leak::GetSize() const
{
    return m_uiSize;
}


/**
 * Allows the printing of a Leak struct to an output stream via the << operator.
 * Format is "<size> bytes at <address> allocated by <file>(<line>)".
 * @param[out] a_roOut  The output stream to print to.
 * @param[in] ac_roLeak The struct to print describing a block of memory.
 * @return  A reference to the output stream.
 */
std::ostream& LeakDebug::operator<<( std::ostream& a_roOut,
                                     const Leak& ac_roLeak )
{
    a_roOut << ac_roLeak.GetSize() << " bytes at "
            << ac_roLeak.GetAddress() << " allocated by ";
    if( nullptr != ac_roLeak.GetFile() && strlen( ac_roLeak.GetFile() ) > 0 )
    {
        a_roOut << ac_roLeak.GetFile() << "(" << ac_roLeak.GetLine() << ")";
    }
    else
    {
        a_roOut << "unknown";
    }
    return a_roOut;
}

/**
 * Leak equality.
 * Two Leak structs are equal if the values of all their fields are equal.
 * @param ac_roLeftLeak
 * @param ac_roRightLeak
 * @return true if the two Leak structs are equal.
 */
bool LeakDebug::operator==( const Leak& ac_roLeftLeak,
                            const Leak& ac_roRightLeak )
{
    return ( ComparePointers( ac_roLeftLeak.GetAddress(),
                              ac_roRightLeak.GetAddress() ) == 0 &&
             ac_roLeftLeak.GetSize() == ac_roRightLeak.GetSize() &&
             CompareCStrings( ac_roLeftLeak.GetFile(),
                              ac_roRightLeak.GetFile() ) == 0 &&
             ac_roLeftLeak.GetLine() == ac_roRightLeak.GetLine() );
}

/**
 * Leak inequality.
 * Two leak structs are not equal if any of their fields are not equal.
 * @param ac_roLeftLeak
 * @param ac_roRightLeak
 * @return true if the two leak structs are not equal.
 */
bool LeakDebug::operator!=( const Leak& ac_roLeftLeak,
                            const Leak& ac_roRightLeak )
{
    return ( ComparePointers( ac_roLeftLeak.GetAddress(),
                              ac_roRightLeak.GetAddress() ) != 0 ||
             ac_roLeftLeak.GetSize() != ac_roRightLeak.GetSize() ||
             CompareCStrings( ac_roLeftLeak.GetFile(),
                              ac_roRightLeak.GetFile() ) != 0 ||
             ac_roLeftLeak.GetLine() != ac_roRightLeak.GetLine() );
}

/**
 * Leak greater-than comparison.
 * One Leak struct is greater than a second if the first of its fields with a
 * different value than the corresponding field in the second has a greater
 * value than said corresponding field.
 * @param ac_roLeftLeak
 * @param ac_roRightLeak
 * @return true if the left Leak is greater than the right Leak.
 */
bool LeakDebug::operator>( const Leak& ac_roLeftLeak,
                           const Leak& ac_roRightLeak )
{
    // Check address first
    int iCmp = ComparePointers( ac_roLeftLeak.GetAddress(),
                                ac_roRightLeak.GetAddress() );
    if( iCmp > 0 )
        return true;
    if( iCmp < 0 )
        return false;

    // Check size next
    if( ac_roLeftLeak.GetSize() > ac_roRightLeak.GetSize() )
        return true;
    if( ac_roLeftLeak.GetSize() < ac_roRightLeak.GetSize() )
        return false;

    // Check file next
    iCmp = CompareCStrings( ac_roLeftLeak.GetFile(), ac_roRightLeak.GetFile() );
    if( iCmp > 0 )
        return true;
    if( iCmp < 0 )
        return false;

    // If all of the above were equal, compare line number
    return ac_roLeftLeak.GetLine() > ac_roRightLeak.GetLine();
}

/**
 * Leak greater-than-or-equal-to comparison.
 * One Leak struct is greater than a second if the first of its fields with a
 * different value than the corresponding field in the second has a greater
 * value than said corresponding field.
 * @param ac_roLeftLeak
 * @param ac_roRightLeak
 * @return true if the left Leak is greater than or equal to the right Leak.
 */
bool LeakDebug::operator>=( const Leak& ac_roLeftLeak,
                            const Leak& ac_roRightLeak )
{
    // Check address first
    int iCmp = ComparePointers( ac_roLeftLeak.GetAddress(),
                                ac_roRightLeak.GetAddress() );
    if( iCmp > 0 )
        return true;
    if( iCmp < 0 )
        return false;

    // Check size next
    if( ac_roLeftLeak.GetSize() > ac_roRightLeak.GetSize() )
        return true;
    if( ac_roLeftLeak.GetSize() < ac_roRightLeak.GetSize() )
        return false;

    // Check file next
    iCmp = CompareCStrings( ac_roLeftLeak.GetFile(), ac_roRightLeak.GetFile() );
    if( iCmp > 0 )
        return true;
    if( iCmp < 0 )
        return false;

    // If all of the above were equal, compare line number
    return ac_roLeftLeak.GetLine() >= ac_roRightLeak.GetLine();
}

/**
 * Leak less-than comparison.
 * One Leak struct is less than a second if the first of its fields with a
 * different value than the corresponding field in the second has a lesser value
 * than said corresponding field.
 * @param ac_roLeftLeak
 * @param ac_roRightLeak
 * @return true if the left Leak is less than the right Leak.
 */
bool LeakDebug::operator<( const Leak& ac_roLeftLeak,
                           const Leak& ac_roRightLeak )
{
    // Check address first
    int iCmp = ComparePointers( ac_roLeftLeak.GetAddress(),
                                ac_roRightLeak.GetAddress() );
    if( iCmp < 0 )
        return true;
    if( iCmp > 0 )
        return false;

    // Check size next
    if( ac_roLeftLeak.GetSize() < ac_roRightLeak.GetSize() )
        return true;
    if( ac_roLeftLeak.GetSize() > ac_roRightLeak.GetSize() )
        return false;

    // Check file next
    iCmp = CompareCStrings( ac_roLeftLeak.GetFile(), ac_roRightLeak.GetFile() );
    if( iCmp < 0 )
        return true;
    if( iCmp > 0 )
        return false;

    // If all of the above were equal, compare line number
    return ac_roLeftLeak.GetLine() < ac_roRightLeak.GetLine();
}

/**
 * Leak less-than-or-equal-to comparison.
 * One Leak struct is less than a second if the first of its fields with a
 * different value than the corresponding field in the second has a lesser value
 * than said corresponding field.
 * @param ac_roLeftLeak
 * @param ac_roRightLeak
 * @return true if the left Leak is less than or equal to the right Leak.
 */
bool LeakDebug::operator<=( const Leak& ac_roLeftLeak,
                            const Leak& ac_roRightLeak )
{
    // Check address first
    int iCmp = ComparePointers( ac_roLeftLeak.GetAddress(),
                                ac_roRightLeak.GetAddress() );
    if( iCmp < 0 )
        return true;
    if( iCmp > 0 )
        return false;

    // Check size next
    if( ac_roLeftLeak.GetSize() < ac_roRightLeak.GetSize() )
        return true;
    if( ac_roLeftLeak.GetSize() > ac_roRightLeak.GetSize() )
        return false;

    // Check file next
    iCmp = CompareCStrings( ac_roLeftLeak.GetFile(), ac_roRightLeak.GetFile() );
    if( iCmp < 0 )
        return true;
    if( iCmp > 0 )
        return false;

    // If all of the above were equal, compare line number
    return ac_roLeftLeak.GetLine() <= ac_roRightLeak.GetLine();
}

/**
 * Memory address mutator.
 * @param ac_pAddress   New value for the memory address field.
 */
void LeakDebug::Leak::SetAddress( const void* const ac_pAddress )
{
    m_pAddress = ac_pAddress;
}

/**
 * File name mutator.  Copies parameter string content, not address.
 * @param ac_cpcFile    New data for the file name field.
 */
void LeakDebug::Leak::SetFile( const char* const ac_cpcFile )
{
    // If the new file name is null or a different length than the current one,
    // make sure the current filename is properly deallocated.
    if( nullptr != m_pcFile &&
        ( nullptr == ac_cpcFile ||
          strlen( m_pcFile ) != strlen( ac_cpcFile ) ) )
    {
        std::free( m_pcFile );
        m_pcFile = nullptr;
    }

    // Copy the new filename
    if( nullptr != ac_cpcFile )
    {
        // Allocate memory, if necessary.
        if( nullptr == m_pcFile )
        {
            m_pcFile = (char*)std::malloc( sizeof( char ) *
                                           ( strlen( ac_cpcFile ) + 1 ) );
        }
        strcpy( m_pcFile, ac_cpcFile );
    }
}

/**
 * Line number mutator.
 * @param ac_uiLine New value for the line number field.
 */
void LeakDebug::Leak::SetLine( const unsigned int ac_uiLine )
{
    m_uiLine = ac_uiLine;
}

/**
 * Size mutator.
 * @param ac_uiSize New value for the size field.
 */
void LeakDebug::Leak::SetSize( const std::size_t ac_uiSize )
{
    m_uiSize = ac_uiSize;
}
