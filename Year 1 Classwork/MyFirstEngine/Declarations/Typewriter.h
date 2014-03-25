/******************************************************************************
 * File:               Typewriter.h
 * Author:             Elizabeth Lowry
 * Date Created:       March 21, 2014
 * Description:        Class for writing text to the screen.
 *                      TODO: change this to a non-singleton with << and >>
 *                      operators to set what will untimately be drawn.
 * Last Modified:      March 22, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

#ifndef TYPEWRITER__H
#define TYPEWRITER__H

#include "Font.h"
#include "MathLibrary.h"
#include "Sprite.h"
#include "MyFirstEngineMacros.h"

namespace MyFirstEngine
{

class IMEXPORT_CLASS Typewriter
    : private Sprite, private Utility::Singleton< Typewriter >
{
    friend class Utility::Singleton< Typewriter >;
public:

    virtual ~Typewriter() {}

    // Type text or a special character
    static void Type( const char* ac_pcText );
    static void TypeSymbol( const char* ac_pcCharacterName );
    static void Tab();
    static void NewLine();

    // Set the position of the next character (and the x-coordinate of the first
    // character of all following new lines )
    static void SetStartPosition( const Point3D& ac_roPosition );
    static void SetStartPosition( double a_dX, double a_dY, double a_dZ = 0.0 );
    static void ReturnToStart()
    { Instance().SetPosition( Instance().m_oStartPosition ); }

    // Set text properties
    static void SetColor( const Color::ColorVector& ac_roColor )
    { Instance().Sprite::SetColor( ac_roColor ); }
    static void SetFont( const Font& ac_roFont )
    { Instance().m_pcoFont = &ac_roFont; }
    static void SetFontSize( double a_dEmDisplaySize )
    { Instance().m_dFontSize = a_dEmDisplaySize; }
    static void SetLineSpacing( double a_dLines )
    { Instance().m_dLineSpacing = a_dLines; }
    static void SetLetterSpacing( double a_dEms )
    { Instance().m_dLetterSpacing = a_dEms; }
    static void SetTabSize( double a_dDisplaySize )
    { Instance().m_dTabSize = a_dDisplaySize; }

private:

    Typewriter();

    void DrawNewLine();
    void DrawTab();
    void DrawCharacter( char a_cCharacter );
    void DrawSymbol( const char* ac_pcCharacterName );

    Point3D m_oStartPosition;  // Where to draw the first character
    const Font* m_pcoFont;
    double m_dFontSize;
    double m_dLetterSpacing;
    double m_dLineSpacing;
    double m_dTabSize;

};  // class Typewriter

}   // namespace MyFirstEngine

#endif  // TYPEWRITER__H
