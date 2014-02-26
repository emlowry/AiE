/******************************************************************************
 * File:               DumbString.inl
 * Author:             Elizabeth Lowry
 * Date Created:       February 10, 2014
 * Description:        Inline function implementations for the DumbString class.
 * Last Modified:      February 25, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

#ifndef DUMB_STRING__INL
#define DUMB_STRING__INL

#include "..\Declarations\DumbString.h"
#include <functional>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>  // for swap

#include "..\Declarations\ImExportMacro.h"

namespace Utility
{

// Constructors
INLINE DumbString::DumbString()
    : m_uiSize( 0 ), m_uiCapacity( sizeof( int ) ), m_pcData( nullptr )
{
    m_pcData = new char[ m_uiCapacity ];
    m_pcData[0] = '\0';
}
INLINE DumbString::DumbString( std::size_t a_uiSize )
    : m_uiSize( 0 ), m_uiCapacity( RequiredCapacity( a_uiSize ) ),
      m_pcData( nullptr )
{
    m_pcData = new char[ m_uiCapacity ];
    m_pcData[0] = '\0';
}
INLINE DumbString::DumbString( const DumbString& ac_roString )
    : m_uiSize( ac_roString.m_uiSize ),
        m_uiCapacity( ac_roString.m_uiCapacity ),
        m_pcData( nullptr )
{
    m_pcData = new char[ m_uiCapacity ];
    strcpy_s( m_pcData, m_uiCapacity, ac_roString.m_pcData );
}
INLINE DumbString::DumbString( const char* ac_pcData )
    : m_uiSize( strlen( ac_pcData ) ),
        m_uiCapacity( RequiredCapacity( m_uiSize ) ),
        m_pcData( nullptr )
{
    m_pcData = new char[ m_uiCapacity ];
    if( nullptr == ac_pcData )
    {
        m_pcData[0] = '\0';
    }
    else
    {
        strcpy_s( m_pcData, m_uiCapacity, ac_pcData );
    }
}
INLINE DumbString::DumbString( char a_cCharacter )
    : m_uiSize( '\0' == a_cCharacter ? 0 : 1 ),
      m_uiCapacity( RequiredCapacity( 1 ) ),
      m_pcData( nullptr )
{
    m_pcData = new char[ m_uiCapacity ];
    m_pcData[0] = a_cCharacter;
    m_pcData[1] = '\0';
}
INLINE DumbString::DumbString( std::istream& a_roInput )
    : m_uiSize( 0 ), m_uiCapacity( sizeof( int ) ), m_pcData( nullptr )
{
    m_pcData = new char[ m_uiCapacity ];
    m_pcData[0] = '\0';
    ReadFrom( a_roInput );
}

// Destructor actually does something
INLINE DumbString::~DumbString()
{
    if( nullptr != m_pcData )
    {
        delete[] m_pcData;
    }
}

// Assign operators
INLINE DumbString& DumbString::operator=( const DumbString& ac_roString )
{
    GrowTo( ac_roString.m_uiSize );
    strcpy_s( m_pcData, m_uiCapacity, ac_roString.m_pcData );
    m_uiSize = ac_roString.m_uiSize;
    return *this;
}
INLINE DumbString& DumbString::operator=( const char* ac_pcData )
{
    if( nullptr == ac_pcData )
    {
        m_pcData[0] = '\0';
    }
    else
    {
        GrowTo( strlen( ac_pcData ) );
        strcpy_s( m_pcData, m_uiCapacity, ac_pcData );
        m_uiSize = strlen( ac_pcData );
    }
    return *this;
}
INLINE DumbString& DumbString::operator=( char a_cCharacter )
{
    char acData[] = { a_cCharacter, '\0' };
    return operator=( acData );
}

// Concatenation-assign operators
INLINE DumbString& DumbString::operator+=( const DumbString& ac_roString )
{
    GrowTo( m_uiSize + ac_roString.m_uiSize );
    strcpy_s( m_pcData + m_uiSize, m_uiCapacity - m_uiSize, ac_roString.m_pcData );
    m_uiSize += ac_roString.m_uiSize;
    return *this;
}
INLINE DumbString& DumbString::operator+=( const char* ac_pcData )
{
    if( nullptr != ac_pcData )
    {
        GrowTo( m_uiSize + strlen( ac_pcData ) );
        strcpy_s( m_pcData + m_uiSize, m_uiCapacity - m_uiSize, ac_pcData );
        m_uiSize += strlen( ac_pcData );
    }
    return *this;
}
INLINE DumbString& DumbString::operator+=( char a_cCharacter )
{
    char acData[] = { a_cCharacter, '\0' };
    return operator+=( acData );
}

// Concatenation operators
INLINE DumbString DumbString::operator+( const DumbString& ac_roString ) const
{
    DumbString oResult( m_uiSize + ac_roString.m_uiSize );
    strcpy_s( oResult.m_pcData, oResult.m_uiCapacity, m_pcData );
    strcpy_s( oResult.m_pcData + m_uiSize,
              oResult.m_uiCapacity - m_uiSize,
              ac_roString.m_pcData );
    oResult.m_uiSize = m_uiSize + ac_roString.m_uiSize;
    return oResult;
}
INLINE DumbString DumbString::operator+( const char* ac_pcData ) const
{
    if( nullptr == ac_pcData )
    {
        return *this ;
    }
    DumbString oResult( m_uiSize + strlen( ac_pcData ) );
    strcpy_s( oResult.m_pcData, oResult.m_uiCapacity, m_pcData );
    strcpy_s( oResult.m_pcData + m_uiSize,
              oResult.m_uiCapacity - m_uiSize,
              ac_pcData );
    oResult.m_uiSize = m_uiSize + strlen( ac_pcData );
    return oResult;
}
INLINE DumbString DumbString::operator+( char a_cCharacter ) const
{
    char acData[] = { a_cCharacter, '\0' };
    return operator+( acData );
}
INLINE DumbString operator+( const char* ac_pcData,
                             const DumbString& ac_roString )
{
    return DumbString( ac_pcData ).operator+( ac_roString );
}
INLINE DumbString operator+( char a_cCharacter, const DumbString& ac_roString )
{
    return DumbString( a_cCharacter ).operator+( ac_roString );
}

// Expand capacity to fit a string of the given size
INLINE void DumbString::GrowTo( std::size_t a_uiSize )
{
    if( a_uiSize >= m_uiCapacity )
    {
        unsigned int uiCapacity = RequiredCapacity( a_uiSize );
        char* pcNewData = new char[ uiCapacity ];
        std::swap( m_pcData, pcNewData );
        m_uiCapacity = uiCapacity;
        delete[] pcNewData;
    }
}

// Implement abstract functions from parent classes
INLINE std::size_t DumbString::Hash() const
{
    return std::hash< std::string >()( std::string( m_pcData ) );
}
INLINE int DumbString::Compare( const DumbString& ac_roString ) const
{
    return strcmp( m_pcData, ac_roString.m_pcData );
}
INLINE int DumbString::Compare( const char* ac_pcData ) const
{
    return strcmp( m_pcData, ac_pcData );
}
INLINE int DumbString::Compare( char a_cCharacter ) const
{
    char acData[] = { a_cCharacter, '\0' };
    return strcmp( m_pcData, acData );
}

// Calculate the int-aligned capacity needed for a string of the given size
INLINE std::size_t DumbString::RequiredCapacity( std::size_t a_uiSize )
{
    return ( ( ( a_uiSize * sizeof( char ) ) + sizeof( int ) )
                / sizeof( int ) ) * sizeof( int );
}

// read from or write to stream
INLINE void DumbString::ReadFrom( std::istream& a_roInput )
{
    if( a_roInput )
    {
        long long llStart = a_roInput.tellg();
        a_roInput.seekg( 0, std::ios::end );
        long long llEnd = a_roInput.tellg();
        a_roInput.seekg( llStart );
        if( llStart >= 0 && llEnd > 0 && llEnd > llStart )
        {
            ReadFrom( a_roInput, (std::size_t)( llEnd - llStart ) );
        }
    }
}
INLINE void DumbString::ReadFrom( std::istream& a_roInput,
                                  std::size_t a_uiSize )
{
    if( a_roInput )
    {
        GrowTo( a_uiSize );
        a_roInput.read( m_pcData, a_uiSize );
        m_uiSize = (unsigned int)( a_roInput.gcount() );
        m_pcData[ m_uiSize ] = '\0';
    }
}
INLINE void DumbString::WriteTo( std::ostream& a_roOutput ) const
{
    WriteTo( a_roOutput, m_uiSize );
}
INLINE void DumbString::WriteTo( std::ostream& a_roOutput,
                                 std::size_t a_uiSize ) const
{
    if( a_roOutput )
    {
        a_roOutput.write( m_pcData, a_uiSize < m_uiSize ? a_uiSize : m_uiSize );
    }
}

//
// Static functions
//

// load string from file contents
INLINE DumbString DumbString::LoadFrom( const char* ac_pcFileName,
                                 const char* ac_pcErrorMessage )
{
    std::ifstream file( ac_pcFileName );
    if( !file )
    {
        throw std::ios::failure( nullptr == ac_pcErrorMessage
                                 ? "Unable to open text file"
                                 : ac_pcErrorMessage );
    }
    DumbString oString( file );
    file.close();
    return oString;
}

}   // namespace Utility

#endif  // DUMB_STRING__INL