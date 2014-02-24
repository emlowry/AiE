/******************************************************************************
 * File:               DumbString.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 10, 2014
 * Description:        Simple non-template string to avoid DLL-compile warnings.
 * Last Modified:      February 24, 2014
 * Last Modification:  Moved into Utility namespace from MyFirstEngine project.
 ******************************************************************************/

#ifndef DUMB_STRING__H
#define DUMB_STRING__H

#include "Comparable.h"
#include "Hashable.h"
#include <cstddef>  // fore size_t
#include <functional>   // for hash
#include <iostream>

#include "ImExportMacro.h"

namespace Utility
{

// A simple String structure.  This doesn't implement everything std::string
// does, but it won't result in warnings when compiling a DLL
class IMEXPORT_CLASS DumbString
    : public Hashable, public Comparable< DumbString >,
      public Comparable< char* >, public Comparable< char >
{
public:

    // Constructors
    DumbString();
    DumbString( std::size_t a_uiSize );
    DumbString( const DumbString& ac_roString );
    DumbString( const char* ac_pcData );
    DumbString( char a_cCharacter );
    DumbString( std::istream& a_roInput );

    // Destructor
    virtual ~DumbString();

    // Operators
    char& operator[]( std::size_t a_uiIndex ) { return m_pcData[ a_uiIndex ]; }
    const char& operator[]( std::size_t a_uiIndex ) const { return m_pcData[ a_uiIndex ]; }
    DumbString& operator=( const DumbString& ac_roString );
    DumbString& operator=( const char* ac_pcData );
    DumbString& operator=( char a_cCharacter );
    DumbString& operator+=( const DumbString& ac_roString );
    DumbString& operator+=( const char* ac_pcData );
    DumbString& operator+=( char a_cCharacter );
    DumbString operator+( const DumbString& ac_roString ) const;
    DumbString operator+( const char* ac_pcData ) const;
    DumbString operator+( char a_cCharacter ) const;
    operator const char*() const { return m_pcData; }

    // Get simple properties
    std::size_t Size() const { return m_uiSize; }
    std::size_t Capacity() const { return m_uiCapacity; }
    const char* CString() const { return m_pcData; }
    bool IsEmpty() const { return ( 0 == m_uiSize ); }

    // Implement abstract functions from parent classes
    int Compare( const DumbString& ac_roString ) const;
    int Compare( char ac_rcCharacter ) const;
    int Compare( const char* ac_pcData ) const;
    std::size_t Hash() const;

    // read from or write to stream
    void ReadFrom( std::istream& a_roInput );
    void ReadFrom( std::istream& a_roInput, std::size_t a_uiSize );
    void WriteTo( std::ostream& a_roOutput ) const;
    void WriteTo( std::ostream& a_roOutput, std::size_t a_uiSize ) const;

    // load string from file contents
    static DumbString LoadFrom( const char* ac_pcFileName,
                                const char* ac_pcErrorMessage = nullptr );

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
DumbString operator+( const char* ac_pcData, const DumbString& ac_roString );
DumbString operator+( const char a_cCharacter, const DumbString& ac_roString );

}   // namespace Utility

namespace std
{

template<>
struct hash< Utility::DumbString > : public hash< Utility::Hashable > {};

}   // namespace std

#ifdef INLINE_IMPLEMENTATION
#include "..\Implementations\DumbString.inl"
#endif

#endif  // DUMB_STRING__H
