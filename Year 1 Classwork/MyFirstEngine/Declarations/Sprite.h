/******************************************************************************
 * File:               Sprite.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 27, 2014
 * Description:        Class representing an textured rectangle, or sprite.
 * Last Modified:      February 27, 2014
 * Last Modification:  Adding copy constructor/operator.
 ******************************************************************************/

#ifndef SPRITE__H
#define SPRITE__H

#include "Quad.h"
#include "MyFirstEngineMacros.h"

namespace MyFirstEngine
{

class IMEXPORT_CLASS Sprite : public Quad
{
public:

    // How to handle the sprite area and slice area not matching.  Options other
    // than CROP_TO_SLICE will draw uncropped pixels not within the slice based
    // on the current OpenGL clamping options.
    enum Cropping
    {
        CROP_TO_SLICE = 0,          // draw pixels if and only if inside slice area
        CROP_TO_SPRITE = 1,         // draw pixels if and only if inside sprite area
        CROP_TO_INTERSECTION = 2,   // draw only where sprite and slice overlap
        CROP_TO_UNION = 3,          // draw area that contains both sprite and slice

        CROP_OPTION_COUNT = 4
    };

    // TODO constructor

    virtual ~Sprite() {}

    // Get properties
    const Point2D& GetPixels() const { return m_oPixels; }
    const Point2D& GetSlicePixels() const { return m_oSlicePixels; }
    const Point2D& GetPixelLocation() const { return m_oPixelLocation; }
    const Point2D& GetPixelOffset() const { return m_oPixelOffset; }
    Cropping GetCropping() const { return m_eCropping; }
    // TODO get texture

    // TODO set properties

private:

    Point2D m_oPixels;          // size of the sprite in texture pixels
    Point2D m_oSlicePixels;     // size of the slice in texture pixels
    Point2D m_oPixelLocation;   // pixel location of the top-left pixel in slice
    Point2D m_oPixelOffset;     // pixel location of the top-left pixel in slice
                                // relative to the top-left corner of the sprite
                                // ( +x = down, +y = right )
    Cropping m_eCropping;

    // TODO indicate texture

};  // class Sprite

}   // namespace MyFirstEngine

#endif  // SPRITE__H
