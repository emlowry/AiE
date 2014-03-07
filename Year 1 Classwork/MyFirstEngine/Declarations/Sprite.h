/******************************************************************************
 * File:               Sprite.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 27, 2014
 * Description:        Class representing an textured rectangle, or sprite.
 * Last Modified:      March 6, 2014
 * Last Modification:  Refactoring.
 ******************************************************************************/

#ifndef SPRITE__H
#define SPRITE__H

#include "Quad.h"
#include "MyFirstEngineMacros.h"

namespace MyFirstEngine
{

// A textured rectangle
class IMEXPORT_CLASS Sprite : public Quad
{
public:

    // How to handle the sprite area and slice area not matching.  Options other
    // than CROP_TO_SLICE will draw uncropped pixels not within the slice based
    // on the current OpenGL clamping options.
    enum Cropping
    {
        CROP_TO_SLICE = 0,      // draw pixels if and only if inside slice area
        CROP_TO_SPRITE = 1,     // draw pixels if and only if inside sprite area
        CROP_TO_INTERSECTION = 2,   // draw only where sprite and slice overlap
        CROP_TO_UNION = 3,      // draw area that contains both sprite and slice

        CROP_OPTION_COUNT = 4
    };

    // Holds attributes for a single frame
    struct Frame
    {
        IntPoint2D spritePixels;    // size of the sprite in texture pixels
        IntPoint2D centerOffset;    // pixel location of the center of the
                                    // sprite relative to m_oPixels / 2
        IntPoint2D slicePixels;     // size of the slice in texture pixels
        IntPoint2D sliceLocation;   // pixel location of the top-left pixel in
                                    // slice relative to the top-left corner of
                                    // the texture ( +x = down, +y = right )
        IntPoint2D sliceOffset;     // pixel location of the top-left pixel in
                                    // slice relative to the top-left corner of
                                    // the sprite ( +x = down, +y = right )
        Cropping cropping;

        // Compare dimensions
        bool operator==( const Frame& ac_roFrame ) const;
        bool operator!=( const Frame& ac_roFrame ) const;
        bool SameSize( const Frame& ac_roFrame ) const;
    };

    // Holds a sequence of frame attributes
    class FrameArray;

    // TODO main constructor
    Sprite( const Sprite& ac_roSprite );
    Sprite& operator=( const Sprite& ac_roSprite );

    // Destructor actually does something
    virtual ~Sprite();

    // Frame access operators
    Frame& Frame( unsigned int a_uiFrameNumber );
    const Frame& Frame( unsigned int a_uiFrameNumber ) const;
    Frame& operator[]( unsigned int a_uiFrameNumber );
    const Frame& operator[]( unsigned int a_uiFrameNumber ) const;

    // Frame increment/decrement operators
    Sprite& operator++();   // ++Sprite - returns incremented sprite
    Sprite operator++(int); // Sprite++ - returns copy of pre-increment sprite
    Sprite& operator--();   // --Sprite - returns decremented sprite
    Sprite operator--(int); // Sprite-- - returns copy of pre-decrement sprite

    // Sprite properties
    unsigned int FrameNumber() const { return m_uiFrameNumber; }
    unsigned int FrameCount() const;
    Frame& CurrentFrame();
    const Frame& CurrentFrame() const;
    Sprite& SetFrameNumber( unsigned int a_uiFrameNumber );

    // Current frame properties
    const IntPoint2D& SpritePixels() const
    { return CurrentFrame().spritePixels; }
    const IntPoint2D& CenterOffset() const
    { return CurrentFrame().centerOffset; }
    const IntPoint2D& SlicePixels() const
    { return CurrentFrame().slicePixels; }
    const IntPoint2D& SliceLocation() const
    { return CurrentFrame().sliceLocation; }
    const IntPoint2D& SliceOffset() const
    { return CurrentFrame().sliceOffset; }
    Cropping Cropping() const { return CurrentFrame().cropping; }
    // TODO get texture

    // Get the cached model view transformation resulting from this object's
    // scale/rotation/position/pixel dimensions/etc.  If any of those properties
    // have changed since the last time said transformation was calculated,
    // recalculate it.
    virtual const Transform3D& GetModelMatrix() const override;

    // TODO set properties

    static const Frame ZERO_FRAME;

protected:

    // Default constructor creates one frame
    const FrameArray* m_poFrames; // pointer to const, not const pointer
    unsigned int m_uiFrameNumber;

};  // class Sprite

}   // namespace MyFirstEngine

#endif  // SPRITE__H
