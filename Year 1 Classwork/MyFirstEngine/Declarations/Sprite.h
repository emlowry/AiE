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
    const IntPoint2D& GetPixels() const { return m_oPixels; }
    const IntPoint2D& GetCenterOffset() const { return m_oCenterOffset; }
    const IntPoint2D& GetSlicePixels() const { return m_oSlicePixels; }
    const IntPoint2D& GetSliceLocation() const { return m_oSliceLocation; }
    const IntPoint2D& GetSliceOffset() const { return m_oSliceOffset; }
    Cropping GetCropping() const { return m_eCropping; }
    // TODO get texture

    // Get the cached model view transformation resulting from this object's
    // scale/rotation/position/pixel dimensions/etc.  If any of those properties
    // have changed since the last time said transformation was calculated,
    // recalculate it.
    virtual const Transform3D& GetModelMatrix() const override;

    // Add to pixel dimensions
    const Sprite& AddPixels( const IntPoint2D& ac_roPixels );
    const Sprite& AddPixels( int a_iX, int a_iY );
    const Sprite& AddCenterOffset( const IntPoint2D& ac_roPixels );
    const Sprite& AddCenterOffset( int a_iX, int a_iY );
    const Sprite& AddSlicePixels( const IntPoint2D& ac_roPixels );
    const Sprite& AddSlicePixels( int a_iX, int a_iY );
    const Sprite& AddSliceLocation( const IntPoint2D& ac_roPixels );
    const Sprite& AddSliceLocation( int a_iX, int a_iY );
    const Sprite& AddSliceOffset( const IntPoint2D& ac_roPixels );
    const Sprite& AddSliceOffset( int a_iX, int a_iY );
    const Sprite& AddSliceDimensions( const IntPoint2D& ac_roPixels,
        const IntPoint2D& ac_roCenterOffset = IntPoint2D::Zero(),
        const IntPoint2D& ac_roSlicePixels = IntPoint2D::Zero(),
        const IntPoint2D& ac_roSliceLocation = IntPoint2D::Zero(),
        const IntPoint2D& ac_roSliceOffset = IntPoint2D::Zero() );

    // TODO set properties

protected:

    IntPoint2D m_oPixels;       // size of the sprite in texture pixels
    IntPoint2D m_oCenterOffset; // pixel location of the center of the sprite
                                // relative to m_oPixels / 2
    IntPoint2D m_oSlicePixels;  // size of the slice in texture pixels
    IntPoint2D m_oSliceLocation;// pixel location of the top-left pixel in slice
                                // relative to the top-left corner of the
                                // texture ( +x = down, +y = right )
    IntPoint2D m_oSliceOffset;  // pixel location of the top-left pixel in slice
                                // relative to the top-left corner of the sprite
                                // ( +x = down, +y = right )
    Cropping m_eCropping;

    // TODO indicate texture

};  // class Sprite

}   // namespace MyFirstEngine

#endif  // SPRITE__H
