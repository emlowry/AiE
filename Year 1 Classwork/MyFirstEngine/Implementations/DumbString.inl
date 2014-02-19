/******************************************************************************
 * File:               DumbString.inl
 * Author:             Elizabeth Lowry
 * Date Created:       February 10, 2014
 * Description:        Inline function implementations for the DumbString class.
 * Last Modified:      February 11, 2014
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

// Constructors
inline DumbString::DumbString()
    : m_uiSize( 0 ), m_uiCapacity( sizeof( int ) ), m_pcData( nullptr )
{
    m_pcData = new char[ m_uiCapacity ];
    m_pcData[0] = '\0';
}
inline DumbString::DumbString( std::size_t a_uiSize )
    : m_uiSize( 0 ), m_uiCapacity( RequiredCapacity( a_uiSize ) ),
      m_pcData( nullptr )
{
    m_pcData = new char[ m_uiCapacity ];
    m_pcData[0] = '\0';
}
inline DumbString::DumbString( const DumbString& ac_roString )
    : m_uiSize( ac_roString.m_uiSize ),
        m_uiCapacity( ac_roString.m_uiCapacity ),
        m_pcData( nullptr )
{
    m_pcData = new char[ m_uiCapacity ];
    strcpy_s( m_pcData, m_uiCapacity, ac_roString.m_pcData );
}
inline DumbString::DumbString( const char* ac_pcData )
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
inline DumbString::DumbString( char a_cCharacter )
    : m_uiSize( '\0' == a_cCharacter ? 0 : 1 ),
      m_uiCapacity( RequiredCapacity( 1 ) ),
      m_pcData( nullptr )
{
    m_pcData = new char[ m_uiCapacity ];
    m_pcData[0] = a_cCharacter;
    m_pcData[1] = '\0';
}
inline DumbString::DumbString( std::istream& a_roInput )
    : m_uiSize( 0 ), m_uiCapacity( sizeof( int ) ), m_pcData( nullptr )
{
    m_pcData = new char[ m_uiCapacity ];
    m_pcData[0] = '\0';
    ReadFrom( a_roInput );
}

// Destructor actually does something
inline DumbString::~DumbString()
{
    if( nullptr != m_pcData )
    {
        delete[] m_pcData;
    }
}

// Assign operators
inline DumbString& DumbString::operator=( const DumbString& ac_roString )
{
    GrowTo( ac_roString.m_uiSize );
    strcpy_s( m_pcData, m_uiCapacity, ac_roString.m_pcData );
    m_uiSize = ac_roString.m_uiSize;
    return *this;
}
inline DumbString& DumbString::operator=( const char* ac_pcData )
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
inline DumbString& DumbString::operator=( char a_cCharacter )
{
    char acData[] = { a_cCharacter, '\0' };
    return operator=( acData );
}

// Concatenation-assign operators
inline DumbString& DumbString::operator+=( const DumbString& ac_roString )
{
    GrowTo( m_uiSize + ac_roString.m_uiSize );
    strcpy_s( m_pcData + m_uiSize, m_uiCapacity - m_uiSize, ac_roString.m_pcData );
    m_uiSize += ac_roString.m_uiSize;
    return *this;
}
inline DumbString& DumbString::operator+=( const char* ac_pcData )
{
    if( nullptr != ac_pcData )
    {
        GrowTo( m_uiSize + strlen( ac_pcData ) );
        strcpy_s( m_pcData + m_uiSize, m_uiCapacity - m_uiSize, ac_pcData );
        m_uiSize += strlen( ac_pcData );
    }
    return *this;
}
inline DumbString& DumbString::operator+=( char a_cCharacter )
{
    char acData[] = { a_cCharacter, '\0' };
    return operator+=( acData );
}

// Concatenation operators
inline DumbString DumbString::operator+( const DumbString& ac_roString ) const
{
    DumbString oResult( m_uiSize + ac_roString.m_uiSize );
    strcpy_s( oResult.m_pcData, oResult.m_uiCapacity, m_pcData );
    strcpy_s( oResult.m_pcData + m_uiSize,
              oResult.m_uiCapacity - m_uiSize,
              ac_roString.m_pcData );
    oResult.m_uiSize = m_uiSize + ac_roString.m_uiSize;
    return oResult;
}
inline DumbString DumbString::operator+( const char* ac_pcData ) const
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
inline DumbString DumbString::operator+( char a_cCharacter ) const
{
    char acData[] = { a_cCharacter, '\0' };
    return operator+( acData );
}
inline DumbString operator+( const char* ac_pcData,
                             const DumbString& ac_roString )
{
    return DumbString( ac_pcData ).operator+( ac_roString );
}
inline DumbString operator+( char a_cCharacter, const DumbString& ac_roString )
{
    return DumbString( a_cCharacter ).operator+( ac_roString );
}

// Expand capacity to fit a string of the given size
inline void DumbString::GrowTo( std::size_t a_uiSize )
{
    if( a_uiSize >= m_uiCapacity )
    {
        char* pcNewData = new char[ RequiredCapacity( a_uiSize ) ];
        std::swap( m_pcData, pcNewData );
        delete[] pcNewData;
    }
}

// Implement abstract functions from parent classes
inline std::size_t DumbString::Hash() const
{
    return std::hash< std::string >()( std::string( m_pcData ) );
}
inline int DumbString::Compare( const DumbString& ac_roString ) const
{
    return strcmp( m_pcData, ac_roString.m_pcData );
}
inline int DumbString::Compare( const char* ac_pcData ) const
{
    return strcmp( m_pcData, ac_pcData );
}
inline int DumbString::Compare( char a_cCharacter ) const
{
    char acData[] = { a_cCharacter, '\0' };
    return strcmp( m_pcData, acData );
}

// Calculate the int-aligned capacity needed for a string of the given size
inline std::size_t DumbString::RequiredCapacity( std::size_t a_uiSize )
{
    return ( ( ( a_uiSize * sizeof( char ) ) + sizeof( int ) )
                / sizeof( int ) ) * sizeof( int );
}

// read from or write to stream
inline void DumbString::ReadFrom( std::istream& a_roInput )
{
    if( a_roInput )
    {
        long long llStart = a_roInput.tellg();
        a_roInput.seekg( std::ios::end );
        long long llEnd = a_roInput.tellg();
        a_roInput.seekg( llStart );
        if( llStart >= 0 && llEnd > 0 && llEnd > llStart )
        {
            ReadFrom( a_roInput, (std::size_t)( llEnd - llStart ) );
        }
    }
}
inline void DumbString::ReadFrom( std::istream& a_roInput,
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
inline void DumbString::WriteTo( std::ostream& a_roOutput ) const
{
    WriteTo( a_roOutput, m_uiSize );
}
inline void DumbString::WriteTo( std::ostream& a_roOutput,
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
inline DumbString DumbString::LoadFrom( const char* ac_pcFileName,
                                 const char* ac_pcErrorMessage )
{
    std::ifstream file( ac_pcFileName );
    if( !file )
    {
        throw std::ios::failure( nullptr == ac_pcErrorMessage
                                 ? "Unable to open text file"
                                 : ac_pcErrorMessage );
    }
    return DumbString( file );
}

#endif  // DUMB_STRING__INL