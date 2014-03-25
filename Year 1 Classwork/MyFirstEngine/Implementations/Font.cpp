/******************************************************************************
 * File:               Font.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       March 19, 2014
 * Description:        Class representing a font.
 * Last Modified:      March 21, 2014
 * Last Modification:  Refactoring and debugging.
 ******************************************************************************/

#include "../Declarations/Font.h"
#include "../Declarations/HTMLCharacters.h"
#include "MathLibrary.h"
#include <unordered_map>

namespace MyFirstEngine
{

// Frame center (as determined by offset) should be on the baseline at the
// beginning of the character.  Default kerning should be handled via choice
// of frame size, slice size, and slice offset - the default distance
// between the "centers" of the "a" and "b" frames when printing "ab" is the
// width of the "a" frame.
Font::Font( Texture& a_roTexture, const Frame::Array& ac_roFrameList,
            const char* ac_pcFrameCharacters, unsigned int a_uiLeading,
            unsigned int a_uiEm, char a_cUnknown )
    : m_poTexture( &a_roTexture ), m_oFrameList( 256 ),
      m_uiLeading( a_uiLeading ), m_uiEm( a_uiEm ), m_cUnknown( a_cUnknown )
{
    // Zero out all frame dimensions
    for( unsigned int ui = 0; ui < 256; ++ui )
    {
        m_oFrameList[ ui ] = Frame::ZERO;
    }

    // Map provided characters to provided frame dimensions
    if( nullptr != ac_pcFrameCharacters )
    {
        unsigned int uiSize = std::strlen( ac_pcFrameCharacters );
        uiSize = ( uiSize > ac_roFrameList.Size()
                   ? ac_roFrameList.Size() : uiSize );
        for( unsigned int ui = 0; ui < uiSize; ++ui )
        {
            Map( ac_pcFrameCharacters[ ui ], ac_roFrameList[ ui ] );
        }
    }
}
Font::Font( Texture& a_roTexture, unsigned int a_uiLeading,
            unsigned int a_uiEm, char a_cUnknown )
    : m_poTexture( &a_roTexture ), m_oFrameList( 256 ),
      m_uiLeading( a_uiLeading ), m_uiEm( a_uiEm ), m_cUnknown( a_cUnknown )
{
    // Zero out all frame dimensions
    for( unsigned int ui = 0; ui < 256; ++ui )
    {
        m_oFrameList[ ui ] = Frame::ZERO;
    }

    // Map ' ' to an empty frame 1/2 em wide and leading pixels high with a
    // baseline halfway between the center and bottom of the frame.
    unsigned int uiWidth = ( 0 != a_uiEm ? a_uiEm : a_uiLeading ) / 2;
    unsigned int uiHeight = ( 0 != a_uiLeading ? a_uiLeading : a_uiEm );
    Map( ' ', Frame( IntPoint2D( uiWidth, uiHeight ),
                     IntPoint2D::Zero(), IntPoint2D::Zero(),
                     IntPoint2D( -(int)uiWidth / 2, uiHeight / 4 ) ) );
}

// Get the number of pixels in an em
unsigned int Font::Em() const
{
    return ( 0 != m_uiEm ? m_uiEm :
             Has( 'M' ) ? operator[]( 'M' ).framePixels.x :
             Has( m_cUnknown ) ? operator[]( m_cUnknown ).framePixels.x :
             Has( ' ' ) ? operator[]( ' ' ).framePixels.x :
             m_uiLeading );
}

// Does this font have a non-zero frame defined for this character?
bool Font::Has( char a_cCharacter ) const
{
    return ( Frame::ZERO != m_oFrameList[ ((unsigned int)a_cCharacter) % 256 ] );
}
bool Font::Has( const char* ac_pcCharacterName ) const
{
    return ( m_oMap.Has( ac_pcCharacterName )
                ? Has( m_oMap[ ac_pcCharacterName ] ) :
             HTML::Map().Has( ac_pcCharacterName )
                ? Has( HTML::Map()[ ac_pcCharacterName ] ) : false );
}
char Font::GetCharacter( const char* ac_pcCharacterName ) const
{
    return ( m_oMap.Has( ac_pcCharacterName ) ? m_oMap[ ac_pcCharacterName ] :
             HTML::Map().Has( ac_pcCharacterName )
                ? HTML::Map()[ ac_pcCharacterName ] : m_cUnknown );
}

// for getting and setting character frames directly
Frame& Font::operator[]( const char* ac_pcCharacterName )
{
    // If the symbol is mapped in the font's character map, return frame
    if( m_oMap.Has( ac_pcCharacterName ) )
    {
        return m_oFrameList[ m_oMap[ ac_pcCharacterName ] ];
    }

    // Otherwise, check HTML character map
    if( HTML::Map().Has( ac_pcCharacterName ) )
    {
        return m_oFrameList[ HTML::Map()[ ac_pcCharacterName ] ];
    }

    // If neither map has the symbol, return a reference to a static frame not
    // used for any character
    static Frame soAbsentCharacterFrame;
    soAbsentCharacterFrame = Frame::ZERO;
    return soAbsentCharacterFrame;
}
const Frame& Font::operator[]( const char* ac_pcCharacterName ) const
{
    // If the symbol is mapped in the font's character map, return frame
    if( m_oMap.Has( ac_pcCharacterName ) )
    {
        return m_oFrameList[ ((unsigned int)m_oMap[ ac_pcCharacterName ]) % 256 ];
    }

    // Otherwise, check HTML character map
    if( HTML::Map().Has( ac_pcCharacterName ) )
    {
        return m_oFrameList[ ((unsigned int)HTML::Map()[ ac_pcCharacterName ]) % 256 ];
    }

    // If neither map has the symbol, return a reference to the zero frame
    return Frame::ZERO;
}

// set the frame dimensions for the given character
Font& Font::Map( char a_cCharacter, const Frame& ac_roFrame )
{
    m_oFrameList[ ((unsigned int)a_cCharacter) % 256 ] = ac_roFrame;
    return *this;
}
Font& Font::Map( char a_cCharacter,
                 const IntPoint2D& ac_roSlicePixels,
                 const IntPoint2D& ac_roSliceLocation,
                 int a_iDescenderHeight )
{
    IntPoint2D oCenterOffset( -ac_roSlicePixels.x / 2,
                              ac_roSlicePixels.y / 2 - a_iDescenderHeight );
    Frame oFrame( ac_roSlicePixels, ac_roSliceLocation, oCenterOffset );
    return Map( a_cCharacter, oFrame );
}
Font& Font::Map( char a_cCharacter,
                 int a_iSlicePixelsX, int a_iSlicePixelsY,
                 int a_iSliceLocationX, int a_iSliceLocationY,
                 int a_iDescenderHeight )
{
    IntPoint2D oCenterOffset( -a_iSlicePixelsX / 2,
                              a_iSlicePixelsY / 2 - a_iDescenderHeight );
    Frame oFrame( IntPoint2D( a_iSlicePixelsX, a_iSlicePixelsY ),
                  IntPoint2D( a_iSliceLocationX, a_iSliceLocationY ),
                  oCenterOffset );
    return Map( a_cCharacter, oFrame );
}
    
// Map the given character to the given symbol name and, if provided, set
// the frame dimensions.
Font& Font::Map( char a_cCharacter, const char* ac_pcCharacterName )
{
    if( nullptr != ac_pcCharacterName )
    {
        m_oMap[ ac_pcCharacterName ] = a_cCharacter;
    }
    return *this;
}
Font& Font::Map( char a_cCharacter, const char* ac_pcCharacterName,
                 const Frame& ac_roFrame )
{
    Map( a_cCharacter, ac_pcCharacterName );
    return Map( a_cCharacter, ac_roFrame );
}
Font& Font::Map( char a_cCharacter, const char* ac_pcCharacterName,
                 const IntPoint2D& ac_roSlicePixels,
                 const IntPoint2D& ac_roSliceLocation,
                 int a_iDescenderHeight )
{
    Map( a_cCharacter, ac_pcCharacterName );
    return Map( a_cCharacter, ac_roSlicePixels,
                ac_roSliceLocation, a_iDescenderHeight );
}
Font& Font::Map( char a_cCharacter, const char* ac_pcCharacterName,
                 int a_iSlicePixelsX, int a_iSlicePixelsY,
                 int a_iSliceLocationX, int a_iSliceLocationY,
                 int a_iDescenderHeight )
{
    Map( a_cCharacter, ac_pcCharacterName );
    return Map( a_cCharacter, a_iSlicePixelsX, a_iSlicePixelsY,
                a_iSliceLocationX, a_iSliceLocationY, a_iDescenderHeight );
}

// set the given sprite to show the given character in this font
Sprite& Font::SetSlug( Sprite& a_roSlug, char a_cCharacter ) const
{
    char cCharacter = ( Has( a_cCharacter ) ? a_cCharacter :
                        Has( m_cUnknown ) ? m_cUnknown :
                        Has( ' ' ) ? ' ' : 0 );
    a_roSlug.SetTexture( *m_poTexture );
    a_roSlug.SetFrameList( m_oFrameList );
    a_roSlug.SetFrameNumber( (unsigned int)cCharacter );
    a_roSlug.SetScale( a_roSlug.GetScale().y ); // in case previous slug was tab
    return a_roSlug;
}
Sprite& Font::SetSlug( Sprite& a_roSlug, char a_cCharacter,
                       double a_dEmDisplaySize ) const
{
    a_roSlug.SetScale( a_dEmDisplaySize / ( 0 != Em() ? Em() : 1 ) );
    return SetSlug( a_roSlug, a_cCharacter );
}
Sprite& Font::SetSlug( Sprite& a_roSlug, const char* ac_pcCharacterName ) const
{
    return SetSlug( a_roSlug, GetCharacter( ac_pcCharacterName ) );
}
Sprite& Font::SetSlug( Sprite& a_roSlug, const char* ac_pcCharacterName,
                       double a_dEmDisplaySize ) const
{
    return SetSlug( a_roSlug, GetCharacter( ac_pcCharacterName ),
                    a_dEmDisplaySize );
}

// set the given sprite to show a tab of the given size
Sprite& Font::SetTabSlug( Sprite& a_roSlug, double a_dTabDisplaySize,
                          char a_cTabCharacter ) const
{
    SetSlug( a_roSlug, a_cTabCharacter );
    a_roSlug.SetDisplaySize( a_dTabDisplaySize, a_roSlug.DisplaySize().y );
    return a_roSlug;
}
Sprite& Font::SetTabSlug( Sprite& a_roSlug, double a_dTabDisplaySize,
                          double a_dEmDisplaySize, char a_cTabCharacter ) const
{
    SetSlug( a_roSlug, a_cTabCharacter );
    a_roSlug.SetDisplaySize( a_dTabDisplaySize, a_dEmDisplaySize );
    return a_roSlug;
}

}   // namespace MyFirstEngine
