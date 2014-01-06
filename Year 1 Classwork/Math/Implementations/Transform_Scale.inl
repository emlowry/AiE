/******************************************************************************
 * File:               Transform_Scale.h
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        Inline function implementations for making scale
 *                      transformations.
 * Last Modified:      January 5, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef TRANSFORM__SCALE__INL
#define TRANSFORM__SCALE__INL

#include "Declarations/Transform.h"

namespace Plane
{

// Scale by a given factor
inline PointTransform PointScaling( double a_dFactor )
{
    return PointTransform::Identity() * a_dFactor;
}
inline Transform Scaling( double a_dFactor, const PointVector& ac_roOrigin )
{
    Transform oScale = PointTransform::Identity() * a_dFactor;
    oScale[2][2] = 1.0;
    return TransformationAbout( oScale, ac_roOrigin );
}

// Scale by the given factors along each axis
inline PointTransform PointScaling( double a_dX, double a_dY )
{
    double adScale[2][2] = { { a_dX, 0.0 }, { 0.0, a_dY } };
    return PointTransform( adScale );
}
inline Transform Scaling( double a_dX, double a_dY,
                          const PointVector& ac_roOrigin )
{
    double adScale[3][3] = { { a_dX, 0.0,  0.0 },
                             { 0.0,  a_dY, 0.0 },
                             { 0.0,  0.0,  1.0 } };
    return TransformationAbout( Transform( adScale ), ac_roOrigin );
}

// Scale by the factors given by a point along each axis
inline PointTransform PointScaling( const PointVector& ac_roFactor )
{
    double adScale[2][2] = { { ac_roFactor[0], 0.0 },
                             { 0.0,            ac_roFactor[1] } };
    return PointTransform( adScale );
}
inline Transform Scaling( const PointVector& ac_roFactor,
                          const PointVector& ac_roOrigin )
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
inline PointTransform PointScaling( double a_dFactor )
{
    return PointTransform::Identity() * a_dFactor;
}
inline Transform Scaling( double a_dFactor, const PointVector& ac_roOrigin )
{
    Transform oScale = PointScaling( a_dFactor );
    oScale[3][3] = 1.0;
    return oScale;
}

// Scale by the given factors along each axis
inline PointTransform PointScaling( double a_dX, double a_dY, double a_dZ )
{
    double adScale[3][3] = { { a_dX, 0.0,  0.0 },
                             { 0.0,  a_dY, 0.0 },
                             { 0.0,  0.0,  a_dZ } };
    return PointTransform( adScale );
}
inline Transform Scaling( double a_dX, double a_dY, double a_dZ,
                          const PointVector& ac_roOrigin )
{
    double adScale[4][4] = { { a_dX, 0.0,  0.0,  0.0 },
                             { 0.0,  a_dY, 0.0,  0.0 },
                             { 0.0,  0.0,  a_dZ, 0.0 },
                             { 0.0,  0.0,  0.0,  1.0 } };
    return TransformationAbout( Transform( adScale ), ac_roOrigin );
}

// Scale by the factors given by a point along each axis
inline PointTransform PointScaling( const PointVector& ac_roFactor )
{
    double adScale[3][3] =
    { { ac_roFactor[0], 0.0,            0.0 },
      { 0.0,            ac_roFactor[1], 0.0 },
      { 0.0,            0.0,            ac_roFactor[2] } };
    return PointTransform( adScale );
}
inline Transform Scaling( const PointVector& ac_roFactor,
                          const PointVector& ac_roOrigin )
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
