/******************************************************************************
 * File:               Font.h
 * Author:             Elizabeth Lowry
 * Date Created:       March 18, 2014
 * Description:        Class representing a font.
 * Last Modified:      March 21, 2014
 * Last Modification:  Refactoring and debugging.
 ******************************************************************************/

#ifndef FONT__H
#define FONT__H

#include "CharacterMap.h"
#include "Frame.h"
#include "Sprite.h"
#include "Texture.h"
#include "MyFirstEngineMacros.h"

namespace MyFirstEngine
{

class IMEXPORT_CLASS Font
{
public:

    // Frame center (as determined by offset) should be on the baseline at the
    // beginning of the character.  Default kerning should be handled via choice
    // of frame size, slice size, and slice offset - the default distance
    // between the "centers" of the "a" and "b" frames when printing "ab" is the
    // width of the "a" frame.
    Font( Texture& a_roTexture, const Frame::Array& ac_roFrameList,
          const char* ac_pcFrameCharacters = " !\"#$%&'()*+,-./0123456789:;<=>?"
                                             "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
                                             "`abcdefghijklmnopqrstuvwxyz{|}~",
          unsigned int a_uiLeading = 0, unsigned int a_uiEm = 0,
          char a_cUnknown = '?' );
    Font( Texture& a_roTexture, unsigned int a_uiLeading = 0,
          unsigned int a_uiEm = 0, char a_cUnknown = '?' );

    // Get the number of pixels in an em
    unsigned int Em() const;

    // Does this font have a non-zero frame defined for this character?
    bool Has( char a_cCharacter ) const;
    bool Has( const char* ac_pcCharacterName ) const;
    char GetCharacter( const char* ac_pcCharacterName ) const;

    // Get the number of pixels between baselines
    unsigned int Leading() const
    { return ( 0 != m_uiLeading ? m_uiLeading : Em() ); }

    // Character that substitutes for characters not present in the font
    // (if absent, (space) is used if present and Frame::Zero if not )
    char UnknownCharacter() const { return m_cUnknown; }

    // for getting and setting character frames directly
    Frame& operator[]( char a_cCharacter )
    { return m_oFrameList[ ((unsigned int)a_cCharacter) % 256 ]; }
    const Frame& operator[]( char a_cCharacter ) const
    { return m_oFrameList[ ((unsigned int)a_cCharacter) % 256 ]; }
    Frame& operator[]( const char* ac_pcCharacterName );
    const Frame& operator[]( const char* ac_pcCharacterName ) const;

    // set the frame dimensions for the given character
    Font& Map( char a_cCharacter, const Frame& ac_roFrame );
    Font& Map( char a_cCharacter,
               const IntPoint2D& ac_roSlicePixels,
               const IntPoint2D& ac_roSliceLocation,
               int a_iDescenderHeight = 0 );
    Font& Map( char a_cCharacter,
               int a_iSlicePixelsX, int a_iSlicePixelsY,
               int a_iSliceLocationX, int a_iSliceLocationY,
               int a_iDescenderHeight = 0 );
    
    // Map the given character to the given symbol name and, if provided, set
    // the frame dimensions.
    Font& Map( char a_cCharacter, const char* ac_pcCharacterName );
    Font& Map( char a_cCharacter, const char* ac_pcCharacterName,
               const Frame& ac_roFrame );
    Font& Map( char a_cCharacter, const char* ac_pcCharacterName,
               const IntPoint2D& ac_roSlicePixels,
               const IntPoint2D& ac_roSliceLocation,
               int a_iDescenderHeight = 0 );
    Font& Map( char a_cCharacter, const char* ac_pcCharacterName,
               int a_iSlicePixelsX, int a_iSlicePixelsY,
               int a_iSliceLocationX, int a_iSliceLocationY,
               int a_iDescenderHeight = 0 );

    // set the given sprite to show the given character in this font
    Sprite& SetSlug( Sprite& a_roSlug, char a_cCharacter ) const;
    Sprite& SetSlug( Sprite& a_roSlug, char a_cCharacter,
                     double a_dEmDisplaySize ) const;
    Sprite& SetSlug( Sprite& a_roSlug, const char* ac_pcCharacterName ) const;
    Sprite& SetSlug( Sprite& a_roSlug, const char* ac_pcCharacterName,
                     double a_dEmDisplaySize ) const;

    // set the given sprite to show a tab of the given size
    Sprite& SetTabSlug( Sprite& a_roSlug, double a_dTabDisplaySize,
                        char a_cTabCharacter = ' ' ) const;
    Sprite& SetTabSlug( Sprite& a_roSlug, double a_dTabDisplaySize,
                        double a_dEmDisplaySize,
                        char a_cTabCharacter = ' ' ) const;
    
private:

    Texture* m_poTexture;
    CharacterMap m_oMap;    // if this map doesn't have a symbol, use HTML::Map
#pragma warning(push)               // disable warning about needing a dll
#pragma warning (disable : 4251)    // interface for DynamicArray< Frame > -
    Frame::Array m_oFrameList;      // Frame.h/cpp provides said interface
#pragma warning(pop)
    unsigned int m_uiLeading;   // pixels between baselines - 0 means use 1 em
    unsigned int m_uiEm;    // pixels in an em - 0 means use width of "M" frame
    char m_cUnknown;    // takes the place of characters not in the font

};  // class Font

}   // namespace MyFirstEngine

#endif  // FONT__H
