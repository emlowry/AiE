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
#include <string>
#include <utility>  // for swap

#include "..\Declarations\MyFirstEngineMacros.h"

// Constructors
INLINE DumbString::DumbString()
    : m_uiSize( 0 ), m_uiCapacity( sizeof( int ) ),
        m_pcData( nullptr )
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
    strcpy_s( m_pcData, m_uiCapacity, ac_pcData );
}

// Destructor actually does something
INLINE DumbString::~DumbString()
{
    if( nullptr != m_pcData )
    {
        delete[] m_pcData;
    }
}

// Access operators
INLINE char& DumbString::operator[]( std::size_t a_uiIndex )
{
    return m_pcData[ a_uiIndex ];
}
INLINE const char& DumbString::operator[]( std::size_t a_uiIndex ) const
{
    return m_pcData[ a_uiIndex ];
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
    GrowTo( strlen( ac_pcData ) );
    strcpy_s( m_pcData, m_uiCapacity, ac_pcData );
    m_uiSize = strlen( ac_pcData );
    return *this;
}
INLINE DumbString& DumbString::operator=( char a_cCharacter )
{
    char acData[] = { ac_Character, '\0' };
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
    GrowTo( m_uiSize + strlen( ac_pcData ) );
    strcpy_s( m_pcData + m_uiSize, m_uiCapacity - m_uiSize, ac_pcData );
    m_uiSize += strlen( ac_pcData );
    return *this;
}
INLINE DumbString& DumbString::operator+=( char a_cCharacter )
{
    char acData[] = { ac_Character, '\0' };
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
    DumbString oResult( m_uiSize + strlen( ac_pcData ) );
    strcpy_s( oResult.m_pcData, oResult.m_uiCapacity, m_pcData );
    strcpy_s( oResult.m_pcData + m_uiSize,
              oResult.m_uiCapacity - m_uiSize,
              ac_pcData );
    oResult.m_uiSize = m_uiSize + strlen( ac_pcData );
    return oResult;
}
INLINE DumbString& DumbString::operator+( char a_cCharacter ) const
{
    char acData[] = { ac_Character, '\0' };
    return operator+( acData );
}

// Comparison operators
INLINE bool DumbString::operator==( const DumbString& ac_roString ) const
{
    return ( strcmp( m_pcData, ac_roString.m_pcData ) == 0 );
}
INLINE bool DumbString::operator==( const char* ac_pcData ) const
{
    return ( strcmp( m_pcData, ac_pcData ) == 0 );
}
INLINE bool DumbString::operator==( char a_cCharacter ) const
{
    char acData[] = { ac_Character, '\0' };
    return operator==( acData );
}
INLINE bool DumbString::operator!=( const DumbString& ac_roString ) const
{
    return ( strcmp( m_pcData, ac_roString.m_pcData ) != 0 );
}
INLINE bool DumbString::operator!=( const char* ac_pcData ) const
{
    return ( strcmp( m_pcData, ac_pcData ) != 0 );
}
INLINE bool DumbString::operator!=( char a_cCharacter ) const
{
    char acData[] = { ac_Character, '\0' };
    return operator!=( acData );
}
INLINE bool DumbString::operator<=( const DumbString& ac_roString ) const
{
    return ( strcmp( m_pcData, ac_roString.m_pcData ) <= 0 );
}
INLINE bool DumbString::operator<=( const char* ac_pcData ) const
{
    return ( strcmp( m_pcData, ac_pcData ) <= 0 );
}
INLINE bool DumbString::operator<=( char a_cCharacter ) const
{
    char acData[] = { ac_Character, '\0' };
    return operator<=( acData );
}
INLINE bool DumbString::operator>=( const DumbString& ac_roString ) const
{
    return ( strcmp( m_pcData, ac_roString.m_pcData ) >= 0 );
}
INLINE bool DumbString::operator>=( const char* ac_pcData ) const
{
    return ( strcmp( m_pcData, ac_pcData ) >= 0 );
}
INLINE bool DumbString::operator>=( char a_cCharacter ) const
{
    char acData[] = { ac_Character, '\0' };
    return operator>=( acData );
}
INLINE bool DumbString::operator<( const DumbString& ac_roString ) const
{
    return ( strcmp( m_pcData, ac_roString.m_pcData ) < 0 );
}
INLINE bool DumbString::operator<( const char* ac_pcData ) const
{
    return ( strcmp( m_pcData, ac_pcData ) < 0 );
}
INLINE bool DumbString::operator<( char a_cCharacter ) const
{
    char acData[] = { ac_Character, '\0' };
    return operator<( acData );
}
INLINE bool DumbString::operator>( const DumbString& ac_roString ) const
{
    return ( strcmp( m_pcData, ac_roString.m_pcData ) > 0 );
}
INLINE bool DumbString::operator>( const char* ac_pcData ) const
{
    return ( strcmp( m_pcData, ac_pcData ) > 0 );
}
INLINE bool DumbString::operator>( char a_cCharacter ) const
{
    char acData[] = { ac_Character, '\0' };
    return operator>( acData );
}

// Expand capacity to fit a string of the given size
INLINE void DumbString::GrowTo( std::size_t a_uiSize )
{
    if( a_uiSize >= m_uiCapacity )
    {
        char* pcNewData = new char[ RequiredCapacity( a_uiSize ) ];
        std::swap( m_pcData, pcNewData );
        delete[] pcNewData;
    }
}

// Hash
template<>
INLINE std::size_t std::hash< DumbString >::
    operator()( const DumbString& ac_roString ) const
{
    return std::hash< std::string >()( std::string( ac_roString.CString() ) );
}

// Calculate the int-aligned capacity needed for a string of the given size
INLINE std::size_t DumbString::RequiredCapacity( std::size_t a_uiSize )
{
    return ( ( ( a_uiSize * sizeof( char ) ) + sizeof( int ) )
                / sizeof( int ) ) * sizeof( int );
}

#endif  // DUMB_STRING__INL