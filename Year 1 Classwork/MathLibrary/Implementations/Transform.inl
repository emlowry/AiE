/******************************************************************************
 * File:               Transform.h
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        Inline function implementations for Transform.h.
 *                      Remember that this library uses row vectors, not column.
 * Last Modified:      June 26, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

#ifndef TRANSFORM__INL
#define TRANSFORM__INL

#include "../Declarations/Transform.h"
#include "../Declarations/ImExportMacro.h"

// Separate files to keep file size down
#include "Transform_Scale.inl"
#include "Transform_TranslateRotate.inl"

namespace Plane
{

// Make a transformation that performs the given transformation about a point
INLINE Transform
   TransformationAbout( const Transform& ac_roTransform,
                        const Point& ac_roOrigin )
{
    if( ac_roOrigin == Point::Origin() )
    {
        return ac_roTransform;
    }
    return Translation( -ac_roOrigin ) * ac_roTransform * Translation( ac_roOrigin );
}

}   // namespace Plane

namespace Space
{

// Make a transformation that performs the given transformation about a point
INLINE Transform
   TransformationAbout( const Transform& ac_roTransform,
                        const Point& ac_roOrigin )
{
    if( ac_roOrigin == Point::Origin() )
    {
        return ac_roTransform;
    }
    return Translation( -ac_roOrigin ) * ac_roTransform * Translation( ac_roOrigin );
}

// Perspective project onto plane z = -nearDistance.  Remap coordinates from
//  x = [-screenSizeX/2, screenSizeX/2], y = [-screenSizeY/2, screenSizeY/2],
//  z = [-near, -far] to x' = [ -screenCenterX - 0.5, -screenCenterX + 0.5],
//  y' = [ -screenCenterY - 0.5, -screenCenterY + 0.5], z' = [0, 1].
INLINE Transform
    PerspectiveProjection( double a_dNearDistance, double a_dFarDistance,
                           const Point2D& ac_roScreenSize,
                           const Point2D& ac_roScreenCenter)
{
    const Point2D& roSize = ac_roScreenSize / a_dNearDistance;
    const Point2D& roCenter = ac_roScreenCenter;
    // x' = x/sizeX + centerX*z
    // y' = y/sizeY + centerY*z
    // z' = -far*(z + near)/(far - near)
    // w' = -z
    // x'/w' = x/(-z*sizeX) - centerX
    // y'/w' = y/(-z*sizeY) - centerY
    // z'/w' = far*(1 + near/z)/(far - near)
    double dDepth = a_dFarDistance - a_dNearDistance;
    double adProject[4][4] =
    { { 1.0 / roSize.x, 0.0,            0.0,                        0.0 },
      { 0.0,            1.0 / roSize.y, 0.0,                        0.0 },
      { roCenter.x,     roCenter.y,     -a_dFarDistance / dDepth,   -1.0 },
      { 0.0,            0.0,        -a_dFarDistance * a_dNearDistance / dDepth,
                                                                    0.0 } };
    return Transform( adProject );

}

// Parallel project onto plane z = -nearDistance.  Remap coordinates from
//  x = [-screenSizeX/2, screenSizeX/2], y = [-screenSizeY/2, screenSizeY/2],
//  z = [-near, -far] to x' = [ -screenCenterX - 0.5, -screenCenterX + 0.5],
//  y' = [ -screenCenterY - 0.5, -screenCenterY + 0.5], z' = [0, 1].
INLINE Transform
    ParallelProjection( double a_dNearDistance, double a_dFarDistance,
                        const Point2D& ac_roScreenSize,
                        const Point2D& ac_roScreenCenter)
{
    const Point2D& roSize = ac_roScreenSize;
    const Point2D& roCenter = ac_roScreenCenter;
    // x' = x'/w' = x/sizeX - centerX
    // y' = y'/w' = y/sizeY - centerY
    // z' = z'/w' = (-z - near)/(far - near)
    double dDepth = a_dFarDistance - a_dNearDistance;
    double adProject[4][4] =
    { { 1.0 / roSize.x, 0.0,            0.0,                        0.0 },
      { 0.0,            1.0 / roSize.y, 0.0,                        0.0 },
      { 0.0,            0.0,            -1.0 / dDepth,              0.0 },
      { -roCenter.x,    -roCenter.y,    -a_dNearDistance / dDepth,  1.0 } };
    return Transform( adProject );
}

}   // namespace Space

#endif  // TRANSFORM__INL