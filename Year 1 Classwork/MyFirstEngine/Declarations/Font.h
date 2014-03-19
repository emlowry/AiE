/******************************************************************************
 * File:               Font.h
 * Author:             Elizabeth Lowry
 * Date Created:       March 18, 2014
 * Description:        Class representing a font.
 * Last Modified:      March 18, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef FONT__H
#define FONT__H

#include "Frame.h"
#include "Texture.h"
#include "MyFirstEngineMacros.h"

namespace MyFirstEngine
{

class IMEXPORT_CLASS Font
{
public:

    // Frame list is for the printable ascii characters 32-126, in order. Frame
    // center (as determined by offset) should be on the baseline at the
    // beginning of the character.  Default kerning should be handled via choice
    // of frame size, slice size, and slice offset - the default distance
    // between the "centers" of the "a" and "b" frames when printing "ab" is the
    // width of the "a" frame.
    Font( Texture& a_roTexture, const Frame::Array& ac_roFrameList,
          unsigned int a_uiLeading = 0, unsigned int a_uiEm = 0 )
        : m_poTexture( &a_roTexture ), m_oFrameList( ac_roFrameList ), 
    Font( Texture& a_roTexture,
          unsigned int a_uiLeading = 0, unsigned int a_uiEm = 0 );
    
private:

    Texture* m_poTexture;
    Frame::Array m_oFrameList;
    unsigned int m_uiLeading;   // pixels between baselines - 0 means use 1 em
    unsigned int m_uiEm;    // pixels in an em - 0 means use width of "M" frame

};  // class Font

}   // namespace MyFirstEngine

#endif  // FONT__H
