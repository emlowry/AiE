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
#include <cstring>
#include <iostream>
#include <string>

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
    a_roOut << ac_roLeak.size << " bytes at "
            << ac_roLeak.pointer << " allocated by ";
    if( strlen( ac_roLeak.file ) > 0 )
    {
        a_roOut << ac_roLeak.file << "(" << ac_roLeak.line << ")";
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
    return ( ac_roLeftLeak.pointer == ac_roRightLeak.pointer &&
             ac_roLeftLeak.size == ac_roRightLeak.size &&
             strcmp(ac_roLeftLeak.file, ac_roRightLeak.file) == 0 &&
             ac_roLeftLeak.line == ac_roRightLeak.line );
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
    return ( ac_roLeftLeak.pointer != ac_roRightLeak.pointer ||
             ac_roLeftLeak.size != ac_roRightLeak.size ||
             strcmp(ac_roLeftLeak.file, ac_roRightLeak.file) != 0 ||
             ac_roLeftLeak.line != ac_roRightLeak.line );
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
    if( ac_roLeftLeak.pointer > ac_roRightLeak.pointer )
        return true;
    if( ac_roLeftLeak.pointer < ac_roRightLeak.pointer )
        return false;

    // Check size next
    if( ac_roLeftLeak.size > ac_roRightLeak.size )
        return true;
    if( ac_roLeftLeak.size < ac_roRightLeak.size )
        return false;

    // Check file next
    int iCmp = strcmp(ac_roLeftLeak.file, ac_roRightLeak.file);
    if( iCmp > 0 )
        return true;
    if( iCmp < 0 )
        return false;

    // If all of the above were equal, compare line number
    return ac_roLeftLeak.line > ac_roRightLeak.line;
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
    if( ac_roLeftLeak.pointer > ac_roRightLeak.pointer )
        return true;
    if( ac_roLeftLeak.pointer < ac_roRightLeak.pointer )
        return false;

    // Check size next
    if( ac_roLeftLeak.size > ac_roRightLeak.size )
        return true;
    if( ac_roLeftLeak.size < ac_roRightLeak.size )
        return false;

    // Check file next
    int iCmp = strcmp(ac_roLeftLeak.file, ac_roRightLeak.file);
    if( iCmp > 0 )
        return true;
    if( iCmp < 0 )
        return false;

    // If all of the above were equal, compare line number
    return ac_roLeftLeak.line >= ac_roRightLeak.line;
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
    if( ac_roLeftLeak.pointer < ac_roRightLeak.pointer )
        return true;
    if( ac_roLeftLeak.pointer > ac_roRightLeak.pointer )
        return false;

    // Check size next
    if( ac_roLeftLeak.size < ac_roRightLeak.size )
        return true;
    if( ac_roLeftLeak.size > ac_roRightLeak.size )
        return false;

    // Check file next
    int iCmp = strcmp(ac_roLeftLeak.file, ac_roRightLeak.file);
    if( iCmp < 0 )
        return true;
    if( iCmp > 0 )
        return false;

    // If all of the above were equal, compare line number
    return ac_roLeftLeak.line < ac_roRightLeak.line;
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
    if( ac_roLeftLeak.pointer < ac_roRightLeak.pointer )
        return true;
    if( ac_roLeftLeak.pointer > ac_roRightLeak.pointer )
        return false;

    // Check size next
    if( ac_roLeftLeak.size < ac_roRightLeak.size )
        return true;
    if( ac_roLeftLeak.size > ac_roRightLeak.size )
        return false;

    // Check file next
    int iCmp = strcmp(ac_roLeftLeak.file, ac_roRightLeak.file);
    if( iCmp < 0 )
        return true;
    if( iCmp > 0 )
        return false;

    // If all of the above were equal, compare line number
    return ac_roLeftLeak.line <= ac_roRightLeak.line;
}
