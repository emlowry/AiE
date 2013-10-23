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
 * The address stored here is stored as a pointer to const data to discourage
 * users from using it for deallocation - deallocate from the code that
 * originally allocated the leak instead!  Besides, the memory might have been
 * deallocated after tracking was paused or after this object was retrieved, so
 * trying to do anything to it could cause a segmentation fault.
 */
class Leak
{
public:

    Leak();
    Leak( const void* const ac_cpAddress,
          const std::size_t ac_uiSize,
          const char* const ac_cpcFile,
          const unsigned int ac_uiLine );
    Leak( const Leak& ac_roLeak );
    ~Leak();
    Leak& operator=( const Leak& ac_roLeak );

    const void* GetAddress() const;
    const char* GetFile() const;
    unsigned int GetLine() const;
    std::size_t GetSize() const;

    void SetAddress( const void* const ac_cpAddress );
    void SetFile( const char* const ac_cpcFile );
    void SetLine( const unsigned int ac_uiLine );
    void SetSize( const std::size_t ac_uiSize );

private:

    const void* m_pAddress; //!< Address of the allocated memory.
    std::size_t m_uiSize;   //!< Size in bytes of the block of allocated memory.
    char* m_pcFile;         //!< Name of code file that allocated the memory.
    unsigned int m_uiLine;  //!< Line of code on which the memory was allocated.

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
typedef std::map< const void*, Leak > LeakMap;

}   // namespace LeakDebug

#endif // _LEAK_H_
