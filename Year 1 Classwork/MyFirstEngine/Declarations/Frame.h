/******************************************************************************
 * File:               Frame.h
 * Author:             Elizabeth Lowry
 * Date Created:       March 11, 2014
 * Description:        Class representing a frame within a texture.
 * Last Modified:      March 12, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

#ifndef FRAME__H
#define FRAME__H

#include "MathLibrary.h"
#include "MyFirstEngineMacros.h"

namespace MyFirstEngine
{
    
// Holds attributes for a single frame
struct IMEXPORT_CLASS Frame
{
    // save typing elsewhere
    typedef Utility::DynamicArray< Frame > Array;
    
    // How to handle the frame area and slice area not matching.  Options other
    // than CROP_TO_SLICE will draw uncropped pixels not within the slice based
    // on the current OpenGL clamping options.
    enum Cropping
    {
        CROP_TO_SLICE = 0,      // draw pixels if and only if inside slice area
        CROP_TO_FRAME = 1,      // draw pixels if and only if inside frame area
        CROP_TO_INTERSECTION = 2,   // draw only where frame and slice overlap
        CROP_TO_UNION = 3,      // draw area that contains both frame and slice

        CROP_OPTION_COUNT = 4
    };

    // default constructor
    Frame( const IntPoint2D& ac_roFramePixels = IntPoint2D::Zero(),
           const IntPoint2D& ac_roSliceLocation = IntPoint2D::Zero(),
           const IntPoint2D& ac_roCenterOffset = IntPoint2D::Zero() );

    // constructors for frames with slice and frame differing
    Frame( const IntPoint2D& ac_roFramePixels,
           const IntPoint2D& ac_roSliceLocation,
           const IntPoint2D& ac_roCenterOffset,
           const IntPoint2D& ac_roSlicePixels,
           Cropping a_eCropping = CROP_TO_SLICE );
    Frame( const IntPoint2D& ac_roFramePixels,
           const IntPoint2D& ac_roSliceLocation,
           const IntPoint2D& ac_roCenterOffset,
           const IntPoint2D& ac_roSlicePixels,
           const IntPoint2D& ac_roSliceOffset,
           Cropping a_eCropping = CROP_TO_SLICE );

    // copy constructor
    Frame( const Frame& ac_roFrame );

    // assignment operator
    Frame& operator=( const Frame& ac_roFrame );

    // Compare dimensions
    bool operator==( const Frame& ac_roFrame ) const;
    bool operator!=( const Frame& ac_roFrame ) const;
    bool SameSize( const Frame& ac_roFrame ) const;

    // How many pixels are actually displayed for this frame
    IntPoint2D DisplayAreaPixels() const;

    // Position of the center of the display area relative to the main position,
    // what would be the center if centerOffset and sliceOffset were both zero
    // and framePixels and slicePixels were equal
    IntPoint2D DisplayAreaOffset() const;

    // Location of the top left corner of the slice relative to the top left
    // corner of the display area
    IntPoint2D DisplayAreaSliceOffset() const;

    // Create a transformation matrix for transforming texture coordinates of a
    // quad into the corresponding texture coordinates of the frame display area
    Transform2D DisplayAreaTextureTransform() const
    { Transform2D oResult; return DisplayAreaTextureTransform( oResult ); }
    Transform2D& DisplayAreaTextureTransform( Transform2D& a_roTransform ) const;

    // Create a transformation matrix for transforming a default quad (1x1
    // centered on origin) into a quad of the size and dimensions of the display
    // area
    Transform3D DisplayAreaVertexTransform() const
    { Transform3D oResult; return DisplayAreaVertexTransform( oResult ); }
    Transform3D& DisplayAreaVertexTransform( Transform3D& a_roTransform ) const;

    // Does this frame contain any drawable pixels?
    bool HasDisplayArea() const;

    // Get UV dimensions for the current frame's slice on a texture of the given
    // size.
    Point2D SliceOffsetUV( int a_iTextureWidth, int a_iTextureHeight ) const;
    Point2D SliceSizeUV( int a_iTextureWidth, int a_iTextureHeight ) const;
    Point2D SliceOffsetUV( const IntPoint2D& ac_roTextureSize ) const
    { return SliceOffsetUV( ac_roTextureSize.x, ac_roTextureSize.y ); }
    Point2D SliceSizeUV( const IntPoint2D& ac_roTextureSize ) const
    { return SliceSizeUV( ac_roTextureSize.x, ac_roTextureSize.y ); }

    IntPoint2D framePixels;     // size of the frame in texture pixels
    IntPoint2D centerOffset;    // pixel location of the center of the
                                //  frame relative to framePixels / 2
                                //  ( +x = down, +y = right )
    IntPoint2D sliceLocation;   // pixel location of the top-left pixel in
                                //  slice relative to the top-left corner of
                                //  the texture ( +x = down, +y = right )
    IntPoint2D slicePixels;     // size of the slice in texture pixels
    IntPoint2D sliceOffset;     // pixel location of the top-left pixel in
                                //  slice relative to the top-left corner of
                                //  the frame ( +x = down, +y = right )
    Cropping cropping;

    static const Frame ZERO;
};

}   // namespace MyFirstEngine

// When compiling the Frame class, compile DynamicArray< Frame >
#ifdef FRAME__CPP

// Explicit instantiation
template class DLL_EXPORT Utility::DynamicArray< MyFirstEngine::Frame >;

// When compiling other classes, just use extern explicit template instantiation
#else

// disable warnings on extern before template instantiation
#pragma warning(push)
#pragma warning (disable : 4231)

// Extern explicit instantiation
extern template class DLL_IMPORT Utility::DynamicArray< MyFirstEngine::Frame >;

// reenable warnings
#pragma warning(pop)

#endif  // DynamicArray< Frame > explicit instantiation

#endif  // FRAME__H
