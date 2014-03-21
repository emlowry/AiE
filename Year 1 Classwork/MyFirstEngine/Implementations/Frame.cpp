/******************************************************************************
 * File:               Frame.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       March 12, 2014
 * Description:        Function implementations for Frame functions.
 * Last Modified:      March 12, 2014
 * Last Modification:  Moving code out of Frame.h.
 ******************************************************************************/

#define FRAME__CPP
#include "../Declarations/Frame.h"

//
// File-local helper functions
//

// compute pixel coordinates of corners of intersection of frame and slice
// areas relative to the upper left corner of the frame ( +x = down,
// +y = right )
static void IntersectionCorners( const MyFirstEngine::Frame& ac_roFrame,
                                 IntPoint2D& a_roTopLeft,
                                 IntPoint2D& a_roBottomRight )
{
    // If areas do not intersect, there is no display area
    IntPoint2D oSliceBottomRight = ac_roFrame.slicePixels
                                   + ac_roFrame.sliceOffset;
    if( oSliceBottomRight.x <= 0 || oSliceBottomRight.y <= 0 ||
        ac_roFrame.sliceOffset.x >= ac_roFrame.framePixels.x ||
        ac_roFrame.sliceOffset.y >= ac_roFrame.framePixels.y )
    {
        a_roTopLeft = IntPoint2D::Zero();
        a_roBottomRight = IntPoint2D::Zero();
        return;
    }

    // Otherwise, compute corners
    a_roTopLeft.x = ( 0 >= ac_roFrame.sliceOffset.x
                      ? 0 : ac_roFrame.sliceOffset.x );
    a_roTopLeft.y = ( 0 >= ac_roFrame.sliceOffset.y
                      ? 0 : ac_roFrame.sliceOffset.y );
    a_roBottomRight.x = ( ac_roFrame.framePixels.x <= oSliceBottomRight.x
                          ? ac_roFrame.framePixels.x : oSliceBottomRight.x );
    a_roBottomRight.y = ( ac_roFrame.framePixels.y <= oSliceBottomRight.y
                          ? ac_roFrame.framePixels.y : oSliceBottomRight.y );
}

// compute pixel coordinates of corners of union of frame and slice areas
// relative to the upper left corner of the frame ( +x = down, +y = right )
static void UnionCorners( const MyFirstEngine::Frame& ac_roFrame,
                          IntPoint2D& a_roTopLeft,
                          IntPoint2D& a_roBottomRight )
{
    IntPoint2D oSliceBottomRight = ac_roFrame.slicePixels
                                   + ac_roFrame.sliceOffset;
    a_roTopLeft.x = ( 0 <= ac_roFrame.sliceOffset.x
                      ? 0 : ac_roFrame.sliceOffset.x );
    a_roTopLeft.y = ( 0 <= ac_roFrame.sliceOffset.y
                      ? 0 : ac_roFrame.sliceOffset.y );
    a_roBottomRight.x = ( ac_roFrame.framePixels.x >= oSliceBottomRight.x
                          ? ac_roFrame.framePixels.x : oSliceBottomRight.x );
    a_roBottomRight.y = ( ac_roFrame.framePixels.y >= oSliceBottomRight.y
                          ? ac_roFrame.framePixels.y : oSliceBottomRight.y );
}

namespace MyFirstEngine
{

//
// Class member functions
//

// all-zero frame
const Frame Frame::ZERO = Frame();

// default constructor
Frame::Frame( const IntPoint2D& ac_roFramePixels,
              const IntPoint2D& ac_roSliceLocation,
              const IntPoint2D& ac_roCenterOffset )
    : framePixels( ac_roFramePixels ), centerOffset( ac_roCenterOffset ),
      sliceLocation( ac_roSliceLocation ), slicePixels( ac_roFramePixels ),
      sliceOffset( IntPoint2D::Zero() ), cropping( CROP_TO_SLICE ) {}

// constructors for frames with slice and frame differing
Frame::Frame( const IntPoint2D& ac_roFramePixels,
              const IntPoint2D& ac_roSliceLocation,
              const IntPoint2D& ac_roCenterOffset,
              const IntPoint2D& ac_roSlicePixels,
              Cropping a_eCropping )
    : framePixels( ac_roFramePixels ), centerOffset( ac_roCenterOffset ),
      sliceLocation( ac_roSliceLocation ), slicePixels( ac_roSlicePixels ),
      sliceOffset( ( framePixels - slicePixels ) / 2 ),
      cropping( a_eCropping ) {}
Frame::Frame( const IntPoint2D& ac_roFramePixels,
              const IntPoint2D& ac_roSliceLocation,
              const IntPoint2D& ac_roCenterOffset,
              const IntPoint2D& ac_roSlicePixels,
              const IntPoint2D& ac_roSliceOffset,
              Cropping a_eCropping )
    : framePixels( ac_roFramePixels ), centerOffset( ac_roCenterOffset ),
      sliceLocation( ac_roSliceLocation ), slicePixels( ac_roSlicePixels ),
      sliceOffset( ac_roSliceOffset ), cropping( a_eCropping ) {}

// copy constructor
Frame::Frame( const Frame& ac_roFrame )
    : framePixels( ac_roFrame.framePixels ),
      centerOffset( ac_roFrame.centerOffset ),
      sliceLocation( ac_roFrame.sliceLocation ),
      slicePixels( ac_roFrame.slicePixels ),
      sliceOffset( ac_roFrame.sliceOffset ),
      cropping( ac_roFrame.cropping ) {}

// assignment operator
Frame& Frame::operator=( const Frame& ac_roFrame )
{
    framePixels = ac_roFrame.framePixels;
    centerOffset = ac_roFrame.centerOffset;
    sliceLocation = ac_roFrame.sliceLocation;
    slicePixels = ac_roFrame.slicePixels;
    sliceOffset = ac_roFrame.sliceOffset;
    cropping = ac_roFrame.cropping;
    return *this;
}

// Compare dimensions
bool Frame::operator==( const Frame& ac_roFrame ) const
{
    return ( SameSize( ac_roFrame ) &&
             ac_roFrame.sliceLocation == sliceLocation );
}
bool Frame::operator!=( const Frame& ac_roFrame ) const
{
    return ( !SameSize( ac_roFrame ) ||
             ac_roFrame.sliceLocation != sliceLocation );
}
bool Frame::SameSize( const Frame& ac_roFrame ) const
{
    return ( ac_roFrame.sliceOffset == sliceOffset &&
             ac_roFrame.slicePixels == slicePixels &&
             ac_roFrame.centerOffset == centerOffset &&
             ac_roFrame.framePixels == framePixels &&
             ac_roFrame.cropping == cropping );
}

// How many pixels are actually displayed for this frame
IntPoint2D Frame::DisplayAreaPixels() const
{
    IntPoint2D oResult;
    switch( cropping )
    {

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
    
    // display pixels within both bounds
    case CROP_TO_INTERSECTION:
    {
        IntPoint2D oTopLeft, oBottomRight;
        IntersectionCorners( *this, oTopLeft, oBottomRight );
        oResult = oBottomRight - oTopLeft;
        break;
    }

    // display pixels within either bound
    case CROP_TO_UNION:
    {
        IntPoint2D oTopLeft, oBottomRight;
        UnionCorners( *this, oTopLeft, oBottomRight );
        oResult = oBottomRight - oTopLeft;
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
IntPoint2D Frame::DisplayAreaOffset() const
{
    IntPoint2D oResult;
    switch( cropping )
    {

    // display pixels within slice bounds
    case CROP_TO_SLICE:
    {
        oResult = ( slicePixels - framePixels ) / 2
                    + sliceOffset + centerOffset;
        break;
    }

    // display pixels within frame bounds
    case CROP_TO_FRAME:
    {
        oResult = centerOffset;
        break;
    }
    
    // display pixels within both bounds
    case CROP_TO_INTERSECTION:
    {
        IntPoint2D oTopLeft, oBottomRight;
        IntersectionCorners( *this, oTopLeft, oBottomRight );
        oResult = ( oTopLeft + oBottomRight ) / 2 + centerOffset;
        break;
    }

    // display pixels within either bound
    case CROP_TO_UNION:
    {
        IntPoint2D oTopLeft, oBottomRight;
        UnionCorners( *this, oTopLeft, oBottomRight );
        oResult = ( oTopLeft + oBottomRight ) / 2 + centerOffset;
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

// Location of the top left corner of the slice relative to the top left
// corner of the display area
IntPoint2D Frame::DisplayAreaSliceOffset() const
{
    IntPoint2D oResult;
    switch( cropping )
    {
        
    case CROP_TO_FRAME:
    {
        oResult = sliceOffset;
        break;
    }

    case CROP_TO_INTERSECTION:
    {
        IntPoint2D oTopLeft, oBottomRight;
        IntersectionCorners( *this, oTopLeft, oBottomRight );
        oResult = sliceOffset - oTopLeft;
        break;
    }

    case CROP_TO_UNION:
    {
        IntPoint2D oTopLeft, oBottomRight;
        UnionCorners( *this, oTopLeft, oBottomRight );
        oResult = sliceOffset - oTopLeft;
        break;
    }

    case CROP_TO_SLICE:
    default:
    {
        oResult = IntPoint2D::Zero();
        break;
    }

    }   // switch( cropping )
    return oResult;
}

// Does this frame contain any drawable pixels?
bool Frame::HasDisplayArea() const
{
    bool bResult;
    switch( cropping )
    {

    case CROP_TO_SLICE:
    {
        bResult = ( 0 != slicePixels.x && 0 != slicePixels.y );
        break;
    }
    
    case CROP_TO_FRAME:
    {
        bResult = ( 0 != framePixels.x && 0 != framePixels.y );
        break;
    }

    case CROP_TO_INTERSECTION:
    {
        IntPoint2D oTopLeft, oBottomRight;
        IntersectionCorners( *this, oTopLeft, oBottomRight );
        bResult = ( oTopLeft.x != oBottomRight.x &&
                    oTopLeft.y != oBottomRight.y );
        break;
    }

    case CROP_TO_UNION:
    {
        IntPoint2D oTopLeft, oBottomRight;
        UnionCorners( *this, oTopLeft, oBottomRight );
        bResult = ( oTopLeft.x != oBottomRight.x &&
                    oTopLeft.y != oBottomRight.y );
        break;
    }

    default:
    {
    }

    }   // switch( cropping )
    return bResult;
}

// Create a transformation matrix for transforming texture coordinates of a
// quad into the corresponding texture coordinates of the frame display area
Transform2D& Frame::
    DisplayAreaTextureTransform( Transform2D& a_roTransform ) const
{
    Point2D oDisplayArea = DisplayAreaPixels();
    Point2D oSliceArea = slicePixels;
    Point2D oOffset = DisplayAreaSliceOffset();
    a_roTransform = Plane::Scaling( 0 == oSliceArea.x
                                    ? 0 : oDisplayArea.x / oSliceArea.x,
                                    0 == oSliceArea.y
                                    ? 0 : oDisplayArea.y / oSliceArea.y ) *
                    Plane::Translation( 0 == oSliceArea.x
                                        ? 0 : -oOffset.x / oSliceArea.x,
                                        0 == oSliceArea.y
                                        ? 0 : -oOffset.y / oSliceArea.y );
    return a_roTransform;
}

// Create a transformation matrix for transforming a default quad (1x1
// centered on origin) into a quad of the size and dimensions of the display
// area
Transform3D& Frame::
    DisplayAreaVertexTransform( Transform3D& a_roTransform ) const
{
    Point3D oDisplayArea = DisplayAreaPixels();
    Point3D oOffset = DisplayAreaOffset();
    a_roTransform = Space::Scaling( oDisplayArea ) *
                    Space::Translation( oOffset.x, -oOffset.y );
    return a_roTransform;
}

// Get UV dimensions for the current frame's slice on a texture of the given
// size.
Point2D Frame::SliceOffsetUV( int a_iTextureWidth, int a_iTextureHeight ) const
{
    return ( ( 0 == a_iTextureWidth || 0 == a_iTextureHeight )
             ? Point2D::Zero()
             : Point2D( (double)( sliceLocation.x ) / a_iTextureWidth,
                        (double)( sliceLocation.y ) / a_iTextureHeight ) );
}
Point2D Frame::SliceSizeUV( int a_iTextureWidth, int a_iTextureHeight ) const
{
    return ( ( 0 == a_iTextureWidth || 0 == a_iTextureHeight )
             ? Point2D::Zero()
             : Point2D( (double)( slicePixels.x ) / a_iTextureWidth,
                        (double)( slicePixels.y ) / a_iTextureHeight ) );
}

}   // namespace MyFirstEngine
