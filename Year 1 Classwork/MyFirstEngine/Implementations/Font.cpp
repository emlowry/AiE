/******************************************************************************
 * File:               Font.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       March 19, 2014
 * Description:        Class representing a font.
 * Last Modified:      March 19, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#include "../Declarations/Font.h"
#include <unordered_map>

namespace MyFirstEngine
{

// declare classes instead of typedefs to avoid compiler warnings
// definition is only in cpp
class Font::CharacterMap : public std::unordered_map< char, unsigned int >
{
public:
    virtual ~CharacterMap() {}
};

// Frame center (as determined by offset) should be on the baseline at the
// beginning of the character.  Default kerning should be handled via choice
// of frame size, slice size, and slice offset - the default distance
// between the "centers" of the "a" and "b" frames when printing "ab" is the
// width of the "a" frame.
Font::Font( Texture& a_roTexture, const Frame::Array& ac_roFrameList,
            const char* ac_pcFrameCharacters, unsigned int a_uiLeading,
            unsigned int a_uiEm, char a_cUnknown )
    : m_poTexture( &a_roTexture ), m_poMap( new CharacterMap() ),
      m_oFrameList( ac_roFrameList.Size() ), m_uiLeading( a_uiLeading ),
      m_uiEm( a_uiEm ), m_cUnknown( a_cUnknown )
{
    if( nullptr != ac_pcFrameCharacters )
    {
        unsigned int uiCount = std::strlen( ac_pcFrameCharacters );
        uiCount = ( ac_roFrameList.Size() < uiCount
                    ? ac_roFrameList.Size() : uiCount );
        for( unsigned int ui = 0; ui < uiCount; ++ui )
        {
            (*m_poMap)[ ac_pcFrameCharacters[ ui ] ] = ui;
        }
    }
}
Font::Font( Texture& a_roTexture, unsigned int a_uiLeading,
            unsigned int a_uiEm, char a_cUnknown )
    : m_poTexture( &a_roTexture ), m_poMap( new CharacterMap() ),
      m_oFrameList( Frame( IntPoint2D( a_uiEm, a_uiLeading ),
                           IntPoint2D::Zero(), IntPoint2D::Zero(),
                           IntPoint2D( -(int)a_uiEm / 2, a_uiLeading / 2 ) ) ),
      m_uiLeading( a_uiLeading ), m_uiEm( a_uiEm ),
      m_cUnknown( a_cUnknown )
{
    (*m_poMap)[ m_cUnknown ] = 0;
}

// Destructor actually does something
Font::~Font()
{
    if( nullptr != m_poMap )
    {
        CharacterMap* poMap = m_poMap;
        m_poMap = nullptr;
        delete poMap;
    }
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
    return ( 0 < m_poMap->count( a_cCharacter ) );
}

// for getting and setting character frames directly
Frame& Font::operator[]( char a_cCharacter )
{
    if( !Has( a_cCharacter ) )
    {
        unsigned int uiIndex = m_oFrameList.Size();
        m_oFrameList.SetSize( uiIndex + 1 );
        m_oFrameList[ uiIndex ] =
            ( Has( m_cUnknown ) ? operator[]( m_cUnknown ) : Frame::ZERO );
        (*m_poMap)[ a_cCharacter ] = uiIndex;
    }
    return m_oFrameList[ m_poMap->at( a_cCharacter ) ];
}
const Frame& Font::operator[]( char a_cCharacter ) const
{
    return ( Has( a_cCharacter ) ? m_oFrameList[ m_poMap->at( a_cCharacter ) ] :
             Has( m_cUnknown ) ? m_oFrameList[ m_poMap->at( m_cUnknown ) ] :
             Frame::ZERO );
}

// set the frame dimensions for the given character
Font& Font::Map( char a_cCharacter, const Frame& ac_roFrame )
{
    if( Has( a_cCharacter ) )
    {
        m_oFrameList[ m_poMap->at( a_cCharacter ) ] = ac_roFrame;
    }
    else
    {
        unsigned int uiIndex = m_oFrameList.Size();
        m_oFrameList.SetSize( uiIndex + 1 );
        m_oFrameList[ uiIndex ] = ac_roFrame;
        (*m_poMap)[ a_cCharacter ] = uiIndex;
    }
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

// set the given sprite to show the given character in this font
Sprite& Font::SetSlug( Sprite& a_roSlug, char a_cCharacter ) const
{
    unsigned int uiIndex = ( Has( a_cCharacter ) ? m_poMap->at( a_cCharacter ) :
                             Has( m_cUnknown ) ? m_poMap->at( m_cUnknown ) :
                             Has( ' ' ) ? m_poMap->at( ' ' ) : 0 );
    a_roSlug.SetTexture( *m_poTexture );
    a_roSlug.SetFrameList( m_oFrameList );
    a_roSlug.SetFrameNumber( uiIndex );
    return a_roSlug;
}
Sprite& Font::SetSlug( Sprite& a_roSlug, char a_cCharacter,
                       double a_dEmDisplaySize ) const
{
    a_roSlug.SetScale( a_dEmDisplaySize / ( 0 != Em() ? Em() : 1 ) );
    return SetSlug( a_roSlug, a_cCharacter );
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
