/******************************************************************************
 * File:               Typewriter.h
 * Author:             Elizabeth Lowry
 * Date Created:       March 21, 2014
 * Description:        Class for writing text to the screen.
 *                      TODO: change this to a non-singleton with << and >>
 *                      operators to set what will untimately be drawn.
 * Last Modified:      March 21, 2014
 * Last Modification:  Creation.
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

    // Set the position of the next character (and the x-coordinate of the first
    // character of all following new lines )
    static void SetStartPosition( const Point3D& ac_roPosition );

    // Set text properties
    static void SetColor( const Color::ColorVector& ac_roColor );
    static void SetFont( const Font& ac_roFont );
    static void SetFontSize( double a_dEmDisplaySize );
    static void SetLineSpacing( double a_dLines );
    static void SetLetterSpacing( double a_dEms );

private:

    Typewriter();

    Point3D m_oStartPosition;  // Where to draw the first character
    const Font* m_poFont;
    double m_dFontSize;
    double m_dLetterSpacing;
    double m_dLineSpacing;

};  // class Typewriter

}   // namespace MyFirstEngine

#endif  // TYPEWRITER__H
