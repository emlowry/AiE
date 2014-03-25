/******************************************************************************
 * File:               Typewriter.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       March 22, 2014
 * Description:        Implementations for Typewriter class functions.
 * Last Modified:      March 22, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#include "../Declarations/Typewriter.h"
#include "MathLibrary.h"

namespace MyFirstEngine
{

// Constructor
Typewriter::Typewriter()
    : m_oStartPosition( 0 ), m_pcoFont( nullptr ), m_dFontSize( 1 ),
      m_dLetterSpacing( 0 ), m_dLineSpacing( 1 ), m_dTabSize( 4 ) {}

// Start a new line
void Typewriter::DrawNewLine()
{
    double dLead = m_pcoFont->Leading() * m_dFontSize * m_dLineSpacing / m_pcoFont->Em();
    SetPosition( m_oStartPosition.x, m_oPosition.y - dLead );
}

// Tab
void Typewriter::DrawTab()
{
    double dSize = m_dTabSize -
        Math::Modulo( m_oPosition.x - m_oStartPosition.x, m_dTabSize );
    m_pcoFont->SetTabSlug( *this, dSize, m_dFontSize );
    Draw();
    SetPosition( m_oPosition.x + dSize, m_oPosition.y );
}

// Draw a character
void Typewriter::DrawCharacter( char a_cCharacter )
{
    m_pcoFont->SetSlug( *this, a_cCharacter, m_dFontSize );
    Draw();
    SetPosition( m_oPosition.x + DisplaySize().x, m_oPosition.y );
    double dSpace = m_dLetterSpacing * m_pcoFont->Em();
    if( 0.0 != dSpace )
    {
        m_pcoFont->SetTabSlug( *this, dSpace, m_dFontSize );
        Draw();
        SetPosition( m_oPosition.x + dSpace, m_oPosition.y );
    }
}
void Typewriter::DrawSymbol( const char* ac_pcCharacterName )
{
    m_pcoFont->SetSlug( *this, ac_pcCharacterName, m_dFontSize );
    Draw();
    SetPosition( m_oPosition.x + DisplaySize().x, m_oPosition.y );
    double dSpace = m_dLetterSpacing * m_pcoFont->Em();
    if( 0.0 != dSpace )
    {
        m_pcoFont->SetTabSlug( *this, dSpace, m_dFontSize );
        Draw();
        SetPosition( m_oPosition.x + dSpace, m_oPosition.y );
    }
}

//
// Static functions
//

// Type text or a special character
void Typewriter::Type( const char* ac_pcText )
{
    // do nothing if there is no text or font
    if( nullptr == ac_pcText || nullptr == Instance().m_pcoFont )
    {
        return;
    }

    // loop through text, drawing characters as needed
    unsigned int uiLength = std::strlen( ac_pcText );
    for( unsigned int ui = 0; ui < uiLength; ++ui )
    {
        switch( ac_pcText[ ui ] )
        {
        case '\n': Instance().DrawNewLine(); break;
        case '\t': Instance().DrawTab(); break;
        default: Instance().DrawCharacter( ac_pcText[ ui ] ); break;
        }
    }
}
void Typewriter::TypeSymbol( const char* ac_pcCharacterName )
{
    // do nothing if there is no symbol name or font
    if( nullptr == ac_pcCharacterName || nullptr == Instance().m_pcoFont )
    {
        return;
    }

    // Draw symbol
    Instance().DrawSymbol( ac_pcCharacterName );
}
void Typewriter::Tab()
{
    // do nothing if there is no font
    if( nullptr == Instance().m_pcoFont )
    {
        return;
    }

    // Draw symbol
    Instance().DrawTab();
}
void Typewriter::NewLine()
{
    // do nothing if there is no font
    if( nullptr == Instance().m_pcoFont )
    {
        return;
    }

    // Draw symbol
    Instance().DrawNewLine();
}

// Set the position of the next character (and the x-coordinate of the first
// character of all following new lines )
void Typewriter::SetStartPosition( const Point3D& ac_roPosition )
{
    Instance().m_oStartPosition = ac_roPosition;
    Instance().SetPosition( ac_roPosition );
}
void Typewriter::SetStartPosition( double a_dX, double a_dY, double a_dZ )
{
    Instance().m_oStartPosition.x = a_dX;
    Instance().m_oStartPosition.y = a_dY;
    Instance().m_oStartPosition.z = a_dZ;
    Instance().SetPosition( a_dX, a_dY, a_dZ );
}

}   // namespace MyFirstEngine
