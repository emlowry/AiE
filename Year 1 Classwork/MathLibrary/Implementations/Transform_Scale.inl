/******************************************************************************
 * File:               Transform_Scale.h
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        Inline function implementations for making scale
 *                      transformations.
 * Last Modified:      February 10, 2014
 * Last Modification:  Templatizing PointVector.
 ******************************************************************************/

#ifndef TRANSFORM__SCALE__INL
#define TRANSFORM__SCALE__INL

#include "../Declarations/Transform.h"
#include "../Declarations/ImExportMacro.h"

namespace Plane
{

// Scale by a given factor
INLINE PointTransform PointScaling( double a_dFactor )
{
    return PointTransform::Identity() * a_dFactor;
}
INLINE Transform Scaling( double a_dFactor, const Point& ac_roOrigin )
{
    Transform oScale = PointTransform::Identity() * a_dFactor;
    oScale[2][2] = 1.0;
    return TransformationAbout( oScale, ac_roOrigin );
}

// Scale by the given factors along each axis
INLINE PointTransform PointScaling( double a_dX, double a_dY )
{
    double adScale[2][2] = { { a_dX, 0.0 }, { 0.0, a_dY } };
    return PointTransform( adScale );
}
INLINE Transform Scaling( double a_dX, double a_dY,
                          const Point& ac_roOrigin )
{
    double adScale[3][3] = { { a_dX, 0.0,  0.0 },
                             { 0.0,  a_dY, 0.0 },
                             { 0.0,  0.0,  1.0 } };
    return TransformationAbout( Transform( adScale ), ac_roOrigin );
}

// Scale by the factors given by a point along each axis
INLINE PointTransform PointScaling( const Point& ac_roFactor )
{
    double adScale[2][2] = { { ac_roFactor[0], 0.0 },
                             { 0.0,            ac_roFactor[1] } };
    return PointTransform( adScale );
}
INLINE Transform Scaling( const Point& ac_roFactor,
                          const Point& ac_roOrigin )
{
    double adScale[3][3] = { { ac_roFactor[0], 0.0,            0.0 },
                             { 0.0,            ac_roFactor[1], 0.0 },
                             { 0.0,            0.0,            1.0 } };
    return TransformationAbout( Transform( adScale ), ac_roOrigin );
}

}   // namespace Plane

namespace Space
{

// Scale by a given factor
INLINE PointTransform PointScaling( double a_dFactor )
{
    return PointTransform::Identity() * a_dFactor;
}
INLINE Transform Scaling( double a_dFactor, const Point& ac_roOrigin )
{
    Transform oScale = PointScaling( a_dFactor );
    oScale[3][3] = 1.0;
    return TransformationAbout( oScale, ac_roOrigin );
}

// Scale by the given factors along each axis
INLINE PointTransform PointScaling( double a_dX, double a_dY, double a_dZ )
{
    double adScale[3][3] = { { a_dX, 0.0,  0.0 },
                             { 0.0,  a_dY, 0.0 },
                             { 0.0,  0.0,  a_dZ } };
    return PointTransform( adScale );
}
INLINE Transform Scaling( double a_dX, double a_dY, double a_dZ,
                          const Point& ac_roOrigin )
{
    double adScale[4][4] = { { a_dX, 0.0,  0.0,  0.0 },
                             { 0.0,  a_dY, 0.0,  0.0 },
                             { 0.0,  0.0,  a_dZ, 0.0 },
                             { 0.0,  0.0,  0.0,  1.0 } };
    return TransformationAbout( Transform( adScale ), ac_roOrigin );
}

// Scale by the factors given by a point along each axis
INLINE PointTransform PointScaling( const Point& ac_roFactor )
{
    double adScale[3][3] =
    { { ac_roFactor[0], 0.0,            0.0 },
      { 0.0,            ac_roFactor[1], 0.0 },
      { 0.0,            0.0,            ac_roFactor[2] } };
    return PointTransform( adScale );
}
INLINE Transform Scaling( const Point& ac_roFactor,
                          const Point& ac_roOrigin )
{
    double adScale[4][4] =
    { { ac_roFactor[0], 0.0,            0.0,            0.0 },
      { 0.0,            ac_roFactor[1], 0.0,            0.0 },
      { 0.0,            0.0,            ac_roFactor[2], 0.0 },
      { 0.0,            0.0,            0.0,            1.0 } };
    return TransformationAbout( Transform( adScale ), ac_roOrigin );
}

}   // namespace Space

#endif  // TRANSFORM__SCALE__INL
