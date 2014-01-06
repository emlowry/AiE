/******************************************************************************
 * File:               Transform_TranslateRotate.h
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        Inline function implementations for translation and
 *                      rotation transformations.  Remember that this library
 *                      uses row vectors, not column.
 * Last Modified:      January 5, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef TRANSFORM__TRANSLATE_ROTATE__INL
#define TRANSFORM__TRANSLATE_ROTATE__INL

#include "Declarations/Transform.h"

namespace Plane
{

// Translate
inline Transform Translation( double a_dX, double a_dY )
{
    double adTranslate[3][3] = { { 1.0,  0.0,  0.0 },
                                 { 0.0,  1.0,  0.0 },
                                 { a_dX, a_dY, 1.0 } };
    return Transform( adTranslate );
}
inline Transform Translation( const PointVector& ac_roTranslation )
{
    double adTranslate[3][3] =
    { { 1.0,                0.0,                0.0 },
      { 0.0,                1.0,                0.0 },
      { ac_roTranslation.x, ac_roTranslation.y, 1.0 } };
    return Transform( adTranslate );
}
inline Transform Translation( double a_dDistance,
                              const PointVector& ac_roDirection )
{
    PointVector oDistance = ac_roDirection.Normal() * a_dDistance;
    double adTranslate[3][3] = { { 1.0,         0.0,         0.0 },
                                 { 0.0,         1.0,         0.0 },
                                 { oDistance.x, oDistance.y, 1.0 } };
    return Transform( adTranslate );
}

// Rotate
inline PointTransform
    PointRotation( double a_dRadians )
{
    double dCos = std::cos( a_dRadians );
    double dSin = std::sin( a_dRadians );
    double adRotate[2][2] = { { dCos, dSin }, { dSin * -1, dCos } };
    return PointTransform( adRotate );
}
inline HomogeneousTransform
    HomogeneousRotation( double a_dRadians, const PointVector& ac_roOrigin )
{
    double dCos = std::cos( a_dRadians );
    double dSin = std::sin( a_dRadians );
    double adRotate[3][3] = { { dCos,      dSin, 0.0 },
                              { dSin * -1, dCos, 0.0 },
                              { 0.0,       0.0,  1.0 } };
    return TransformationAbout( Transform( adRotate ), ac_roOrigin );
}

}   // namespace Plane

namespace Space
{

// Translate
inline Transform Translation( double a_dX, double a_dY, double a_dZ )
{
    double adTranslate[4][4] = { { 1.0,  0.0,  0.0,  0.0 },
                                 { 0.0,  1.0,  0.0,  0.0 },
                                 { 0.0,  0.0,  1.0,  0.0 },
                                 { a_dX, a_dY, a_dZ, 1.0 } };
    return Transform( adTranslate );
}
inline Transform Translation( const PointVector& ac_roTranslation )
{
    double adTranslate[4][4] =
    { { 1.0,                0.0,                0.0,                0.0 },
      { 0.0,                1.0,                0.0,                0.0 },
      { 0.0,                0.0,                1.0,                0.0 },
      { ac_roTranslation.x, ac_roTranslation.y, ac_roTranslation.y, 1.0 } };
    return Transform( adTranslate );
}
inline Transform Translation( double a_dDistance,
                              const PointVector& ac_roDirection )
{
    PointVector oDistance = ac_roDirection.Normal() * a_dDistance;
    double adTranslate[4][4] =
    { { 1.0,         0.0,         0.0,         0.0 },
      { 0.0,         1.0,         0.0,         0.0 },
      { 0.0,         0.0,         1.0,         0.0 },
      { oDistance.x, oDistance.y, oDistance.z, 1.0 } };
    return Transform( adTranslate );
}

// Rotate
inline PointTransform
    PointRotation( double a_dRadians,
                   const PointVector& ac_roAxis )
{
    PointVector oN = ac_roAxis.Normal();
    double dCos = std::cos( a_dRadians );
    double dSin = std::sin( a_dRadians );
    double adRotate[3][3] =
    { { dCos + ( oN.x * oN.x * ( 1.0 - dCos ) ),
        ( oN.y * oN.x * ( 1.0 - dCos ) ) + ( oN.z * dSin ),
        ( oN.z * oN.x * ( 1.0 - dCos ) ) - ( oN.y * dSin ) },
      { ( oN.x * oN.y * ( 1.0 - dCos ) ) - ( oN.z * dSin ),
        dCos + ( oN.y * oN.y * ( 1.0 - dCos ) ),
        ( oN.z * oN.y * ( 1.0 - dCos ) ) + ( oN.x * dSin ) },
      { ( oN.x * oN.z * ( 1.0 - dCos ) ) + ( oN.y * dSin ),
        ( oN.y * oN.z * ( 1.0 - dCos ) ) - ( oN.x * dSin ),
        dCos + ( oN.z * oN.z * ( 1.0 - dCos ) ) } };
    return PointTransform( adRotate );
}
inline Transform Rotation( double a_dRadians,
                           const PointVector& ac_roAxis,
                           const PointVector& ac_roOrigin )
{
    PointVector oN = ac_roAxis.Normal();
    double dCos = std::cos( a_dRadians );
    double dSin = std::sin( a_dRadians );
    double adRotate[4][4] =
    { { dCos + ( oN.x * oN.x * ( 1.0 - dCos ) ),
        ( oN.y * oN.x * ( 1.0 - dCos ) ) + ( oN.z * dSin ),
        ( oN.z * oN.x * ( 1.0 - dCos ) ) - ( oN.y * dSin ),
        0.0 },
      { ( oN.x * oN.y * ( 1.0 - dCos ) ) - ( oN.z * dSin ),
        dCos + ( oN.y * oN.y * ( 1.0 - dCos ) ),
        ( oN.z * oN.y * ( 1.0 - dCos ) ) + ( oN.x * dSin ),
        0.0 },
      { ( oN.x * oN.z * ( 1.0 - dCos ) ) + ( oN.y * dSin ),
        ( oN.y * oN.z * ( 1.0 - dCos ) ) - ( oN.x * dSin ),
        dCos + ( oN.z * oN.z * ( 1.0 - dCos ) ),
        0.0 },
      { 0.0, 0.0, 0.0, 1.0 } };
    return TransformationAbout( Transform( adRotate ), ac_roOrigin );
}

}   // namespace Space

#endif  // TRANSFORM__TRANSLATE_ROTATE__INL
