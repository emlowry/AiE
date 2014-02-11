/******************************************************************************
 * File:               DumbString.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 10, 2014
 * Description:        Simple non-template string to avoid DLL-compile warnings.
 * Last Modified:      February 10, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef DUMB_STRING__H
#define DUMB_STRING__H

#include <cstddef>

#include "MyFirstEngineMacros.h"

// A simple String structure.  This doesn't implement everything std::string
// does, but it won't result in warnings when compiling a DLL
class IMEXPORT_CLASS DumbString
{
public:

    // Constructors
    DumbString();
    DumbString( std::size_t a_uiSize );
    DumbString( const DumbString& ac_roString );
    DumbString( const char* ac_pcData );

    // Destructor
    ~DumbString();

    // Operators
    DumbString& operator=( const DumbString& ac_roString );
    DumbString& operator=( const char* ac_pcData );
    DumbString& operator+=( const DumbString& ac_roString );
    DumbString& operator+=( const char* ac_pcData );
    DumbString operator+( const DumbString& ac_roString ) const;
    DumbString operator+( const char* ac_pcData ) const;

    // Get simple properties
    std::size_t Size() const { return m_uiSize; }
    std::size_t Capacity() const { return m_uiCapacity; }
    const char* CString() const { return m_pcData; }
    bool IsEmpty() const { return ( 0 == m_uiSize ); }

private:

    // Expand capacity to fit a string of the given size
    void GrowTo( std::size_t a_uiSize );

    // Calculate the int-aligned capacity needed for a string of the given size
    static std::size_t RequiredCapacity( std::size_t a_uiSize );

    // Data
    char* m_pcData;
    std::size_t m_uiSize;
    std::size_t m_uiCapacity;

};  // class DumbString

#ifdef INLINE_IMPLEMENTATION
#include "Implementations\DumbString.inl"
#endif

#endif  // DUMB_STRING__H