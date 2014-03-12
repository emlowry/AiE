/******************************************************************************
 * File:               Frame.h
 * Author:             Elizabeth Lowry
 * Date Created:       March 11, 2014
 * Description:        Class representing a frame within a texture.
 * Last Modified:      March 11, 2014
 * Last Modification:  Moving code out of Sprite.h.
 ******************************************************************************/

#ifndef FRAME__H
#define FRAME__H

#include "MathLibrary.h"

namespace MyFirstEngine
{

// Holds attributes for a single frame
struct Frame
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
           const IntPoint2D& ac_roCenterOffset = IntPoint2D::Zero() )
        : framePixels( ac_roFramePixels ), centerOffset( ac_roCenterOffset ),
          sliceLocation( ac_roSliceLocation ), slicePixels( ac_roFramePixels ),
          sliceOffset( IntPoint2D::Zero() ), cropping( CROP_TO_SLICE ) {}

    // constructors for frames with slice and frame differing
    Frame( const IntPoint2D& ac_roFramePixels,
           const IntPoint2D& ac_roSliceLocation,
           const IntPoint2D& ac_roCenterOffset,
           const IntPoint2D& ac_roSlicePixels,
           Cropping a_eCropping = CROP_TO_SLICE )
        : framePixels( ac_roFramePixels ), centerOffset( ac_roCenterOffset ),
          sliceLocation( ac_roSliceLocation ), slicePixels( ac_roSlicePixels ),
          sliceOffset( ( framePixels - slicePixels ) / 2 ),
          cropping( a_eCropping ) {}
    Frame( const IntPoint2D& ac_roFramePixels,
           const IntPoint2D& ac_roSliceLocation,
           const IntPoint2D& ac_roCenterOffset,
           const IntPoint2D& ac_roSlicePixels,
           const IntPoint2D& ac_roSliceOffset,
           Cropping a_eCropping = CROP_TO_SLICE )
        : framePixels( ac_roFramePixels ), centerOffset( ac_roCenterOffset ),
          sliceLocation( ac_roSliceLocation ), slicePixels( ac_roSlicePixels ),
          sliceOffset( ac_roSliceOffset ), cropping( a_eCropping ) {}

    // copy constructor
    Frame( const Frame& ac_roFrame )
        : framePixels( ac_roFrame.framePixels ),
          centerOffset( ac_roFrame.centerOffset ),
          sliceLocation( ac_roFrame.sliceLocation ),
          slicePixels( ac_roFrame.slicePixels ),
          sliceOffset( ac_roFrame.sliceOffset ),
          cropping( ac_roFrame.cropping ) {}

    // assignment operator
    Frame& operator=( const Frame& ac_roFrame )
    {
        framePixels = ac_roFrame.framePixels;
        centerOffset = ac_roFrame.centerOffset;
        sliceLocation = ac_roFrame.sliceLocation;
        slicePixels = ac_roFrame.slicePixels;
        sliceOffset = ac_roFrame.sliceOffset;
        cropping = ac_roFrame.cropping;
    }

    // Compare dimensions
    bool operator==( const Frame& ac_roFrame ) const
    {
        return ( SameSize( ac_roFrame ) &&
                 ac_roFrame.sliceLocation == sliceLocation );
    }
    bool operator!=( const Frame& ac_roFrame ) const
    {
        return ( !SameSize( ac_roFrame ) ||
                 ac_roFrame.sliceLocation != sliceLocation );
    }
    bool SameSize( const Frame& ac_roFrame ) const
    {
        return ( ac_roFrame.sliceOffset == sliceOffset &&
                 ac_roFrame.slicePixels == slicePixels &&
                 ac_roFrame.centerOffset == centerOffset &&
                 ac_roFrame.framePixels == framePixels &&
                 ac_roFrame.cropping == cropping );
    }

    // compute pixel coordinates of corners of union of frame and slice areas
    // relative to the main position, what would be the center if centerOffset
    // and sliceOffset were both zero and framePixels and slicePixels were equal
    // ( +x = down, +y = right )
    void UnionCorners( IntPoint2D& a_roTopLeft,
                       IntPoint2D& a_roBottomRight ) const
    {
        IntPoint2D oSliceBottomRight = slicePixels + sliceOffset;
        a_roTopLeft.x = ( 0 <= sliceOffset.x ? 0 : sliceOffset.x );
        a_roTopLeft.y = ( 0 <= sliceOffset.y ? 0 : sliceOffset.y );
        a_roTopLeft += centerOffset;
        a_roBottomRight.x = ( framePixels.x >= oSliceBottomRight.x
                              ? framePixels.x : oSliceBottomRight.x );
        a_roBottomRight.y = ( framePixels.y >= oSliceBottomRight.y
                              ? framePixels.y : oSliceBottomRight.y );
        a_roBottomRight += centerOffset;
    }

    // compute pixel coordinates of corners of intersection of frame and slice
    // areas relative to the main position, what would be the center if
    // centerOffset and sliceOffset were both zero and framePixels and
    // slicePixels were equal ( +x = down, +y = right )
    void IntersectionCorners( IntPoint2D& a_roTopLeft,
                              IntPoint2D& a_roBottomRight ) const
    {
        // If areas do not intersect, there is no display area
        IntPoint2D oSliceBottomRight = slicePixels + sliceOffset;
        if( oSliceBottomRight.x <= 0 || oSliceBottomRight.y <= 0 ||
            sliceOffset.x >= framePixels.x ||
            sliceOffset.y >= framePixels.y )
        {
            a_roTopLeft = IntPoint2D::Zero();
            a_roBottomRight = IntPoint2D::Zero();
            return;
        }

        // Otherwise, compute corners
        a_roTopLeft.x = ( 0 >= sliceOffset.x ? 0 : sliceOffset.x );
        a_roTopLeft.y = ( 0 >= sliceOffset.y ? 0 : sliceOffset.y );
        a_roTopLeft += centerOffset;
        a_roBottomRight.x = ( framePixels.x <= oSliceBottomRight.x
                              ? framePixels.x : oSliceBottomRight.x );
        a_roBottomRight.y = ( framePixels.y <= oSliceBottomRight.y
                              ? framePixels.y : oSliceBottomRight.y );
        a_roBottomRight += centerOffset;
    }

    // How many pixels are actually displayed for this frame
    IntPoint2D DisplayAreaPixels() const
    {
        IntPoint2D oResult;
        switch( cropping )
        {

        // display pixels within either bound
        case CROP_TO_UNION:
        {
            IntPoint2D oTopLeft, oBottomRight;
            UnionCorners( oTopLeft, oBottomRight );
            oResult = oBottomRight - oTopLeft;
            break;
        }

        // display pixels within both bounds
        case CROP_TO_INTERSECTION:
        {
            IntPoint2D oTopLeft, oBottomRight;
            IntersectionCorners( oTopLeft, oBottomRight );
            oResult = oBottomRight - oTopLeft;
            break;
        }

        // display pixels within slice bounds
        case CROP_TO_SLICE:
        {
            oResult = slicePixels;
            break;
        }

        // display pixels within frame bounds
        case CROP_TO_FRAME:
        {
            oResult = framePixels;
            break;
        }
    
        // display nothing
        default:
        {
            oResult = IntPoint2D::Zero();
            break;
        }

        }   // switch( cropping )
        return oResult;
    }

    // Position of the center of the display area relative to the main position,
    // what would be the center if centerOffset and sliceOffset were both zero
    // and framePixels and slicePixels were equal
    IntPoint2D DisplayAreaOffset() const
    {
        IntPoint2D oResult;
        // TODO
        return oResult;
    }

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
const Frame Frame::ZERO = Frame();

}   // namespace MyFirstEngine

#endif  // FRAME__H
