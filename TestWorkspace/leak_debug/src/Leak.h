/** ***************************************************************************
 * @file      Leak.h
 * @author    Elizabeth Lowry
 * @date      October 15, 2013 - October 15, 2013
 * @brief     Memory leak struct.
 * @details   The header file that defines the memory leak struct.
 * @par       Last Modification:
 *              Splitting off from LeakDebug.h.
 **************************************************************************** */

#ifndef _LEAK_H_
#define _LEAK_H_

#include <iostream>
#include <map>

namespace LeakDebug
{

/**
 * Describes a block of allocated dynamic memory and what line allocated it.
 */
struct Leak
{
    void* pointer;      //!< Address of the allocated memory.
    std::size_t size;   //!< Size in bytes of the block of allocated memory.
    const char* file;   //!< Name of the code file that allocated the memory.
    unsigned int line;  //!< Line of code on which the memory was allocated.
};

// operators for the Leak struct
std::ostream& operator<<( std::ostream& a_roOut, const Leak& ac_roLeak );
bool operator==( const Leak& ac_roLeftLeak, const Leak& ac_roRightLeak );
bool operator!=( const Leak& ac_roLeftLeak, const Leak& ac_roRightLeak );
bool operator>( const Leak& ac_roLeftLeak, const Leak& ac_roRightLeak );
bool operator>=( const Leak& ac_roLeftLeak, const Leak& ac_roRightLeak );
bool operator<( const Leak& ac_roLeftLeak, const Leak& ac_roRightLeak );
bool operator<=( const Leak& ac_roLeftLeak, const Leak& ac_roRightLeak );

/**
 * A map of Leak structs describing allocated dynamic memory, keyed by address.
 */
typedef std::map< void*, Leak > LeakMap;

}   // namespace LeakDebug

#endif // _LEAK_H_
