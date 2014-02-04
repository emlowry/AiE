/******************************************************************************
 * File:               Transform_TranslateRotate.h
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        Inline function implementations for translation and
 *                      rotation transformations.  Remember that this library
 *                      uses row vectors, not column.
 * Last Modified:      January 5, 2014
 * Last Modification:  Debugging.
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
inline Transform Translation( double a_dTime,
                              const PointVector& ac_roVelocity )
{
    PointVector oDistance = ac_roVelocity * a_dTime;
    return Translation( oDistance );
}

// Rotate
inline PointTransform
    PointRotation( double a_dRadians, bool a_bClockwise )
{
    a_dRadians *= ( a_bClockwise ? -1 : 1 );
    double dCos = std::cos( a_dRadians );
    double dSin = ( dCos == -1 || dCos == 1 ? 0 : std::sin( a_dRadians ) );
    dCos = ( dSin == -1 || dSin == 1 ? 0 : dCos );
    double adRotate[2][2] = { { dCos, dSin }, { dSin * -1, dCos } };
    return PointTransform( adRotate );
}
inline Transform Rotation( double a_dRadians, bool a_bClockwise,
                           const PointVector& ac_roOrigin )
{
    return Rotation( a_dRadians, ac_roOrigin, a_bClockwise );
}
inline Transform Rotation( double a_dRadians,
                           const PointVector& ac_roOrigin,
                           bool a_bClockwise )
{
    a_dRadians *= ( a_bClockwise ? -1 : 1 );
    double dCos = std::cos( a_dRadians );
    double dSin = ( dCos == -1 || dCos == 1 ? 0 : std::sin( a_dRadians ) );
    dCos = ( dSin == -1 || dSin == 1 ? 0 : dCos );
    double adRotate[3][3] = { { dCos,      dSin, 0.0 },
                              { dSin * -1, dCos, 0.0 },
                              { 0.0,       0.0,  1.0 } };
    return TransformationAbout( Transform( adRotate ), ac_roOrigin );
}
inline PointTransform PointDegreeRotation( double a_dDegrees,
                                           bool a_bClockwise )
{
    return PointRotation( Math::Radians( a_dDegrees ),
                          a_bClockwise );
}
inline Transform DegreeRotation( double a_dDegrees, bool a_bClockwise,
                                 const PointVector& ac_roOrigin )
{
    return Rotation( Math::Radians( a_dDegrees ), ac_roOrigin, a_bClockwise );
}
inline Transform DegreeRotation( double a_dDegrees,
                                 const PointVector& ac_roOrigin,
                                 bool a_bClockwise )
{
    return Rotation( Math::Radians( a_dDegrees ), ac_roOrigin, a_bClockwise );
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
      { ac_roTranslation.x, ac_roTranslation.y, ac_roTranslation.z, 1.0 } };
    return Transform( adTranslate );
}
inline Transform Translation( double a_dTime,
                              const PointVector& ac_roVelocity )
{
    PointVector oDistance = ac_roVelocity * a_dTime;
    return Translation( oDistance );
}

// Rotate
inline PointTransform
    PointRotation( double a_dRadians, bool a_bClockwise,
                   const PointVector& ac_roAxis )
{
    return PointRotation( a_dRadians, ac_roAxis, a_bClockwise );
}
inline PointTransform
    PointRotation( double a_dRadians,
                   const PointVector& ac_roAxis,
                   bool a_bClockwise )
{
    a_dRadians *= ( a_bClockwise ? -1 : 1 );
    PointVector oN = ac_roAxis.Normal();
    double dCos = std::cos( a_dRadians );
    double dSin = ( dCos == -1 || dCos == 1 ? 0 : std::sin( a_dRadians ) );
    dCos = ( dSin == -1 || dSin == 1 ? 0 : dCos );
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
inline Transform Rotation( double a_dRadians, bool a_bClockwise,
                           const PointVector& ac_roAxis,
                           const PointVector& ac_roOrigin )
{
    return Rotation( a_dRadians, ac_roAxis, ac_roOrigin, a_bClockwise );
}
inline Transform Rotation( double a_dRadians,
                           const PointVector& ac_roAxis,
                           bool a_bClockwise,
                           const PointVector& ac_roOrigin )
{
    return Rotation( a_dRadians, ac_roAxis, ac_roOrigin, a_bClockwise );
}
inline Transform Rotation( double a_dRadians,
                           const PointVector& ac_roAxis,
                           const PointVector& ac_roOrigin,
                           bool a_bClockwise )
{
    a_dRadians *= ( a_bClockwise ? -1 : 1 );
    PointVector oN = ac_roAxis.Normal();
    double dCos = std::cos( a_dRadians );
    double dSin = ( dCos == -1 || dCos == 1 ? 0 : std::sin( a_dRadians ) );
    dCos = ( dSin == -1 || dSin == 1 ? 0 : dCos );
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
inline PointTransform PointDegreeRotation( double a_dDegrees,
                                           bool a_bClockwise,
                                           const PointVector& ac_roAxis )
{
    return PointRotation( Math::Radians( a_dDegrees ), ac_roAxis, a_bClockwise );
}
inline PointTransform PointDegreeRotation( double a_dDegrees,
                                           const PointVector& ac_roAxis,
                                           bool a_bClockwise )
{
    return PointRotation( Math::Radians( a_dDegrees ), ac_roAxis, a_bClockwise );
}
inline Transform DegreeRotation( double a_dDegrees, bool a_bClockwise,
                                 const PointVector& ac_roAxis,
                                 const PointVector& ac_roOrigin )
{
    return Rotation( Math::Radians( a_dDegrees ),
                     ac_roAxis, ac_roOrigin, a_bClockwise );
}
inline Transform DegreeRotation( double a_dDegrees,
                                 const PointVector& ac_roAxis,
                                 bool a_bClockwise,
                                 const PointVector& ac_roOrigin )
{
    return Rotation( Math::Radians( a_dDegrees ),
                     ac_roAxis, ac_roOrigin, a_bClockwise );
}
inline Transform DegreeRotation( double a_dDegrees,
                                 const PointVector& ac_roAxis,
                                 const PointVector& ac_roOrigin,
                                 bool a_bClockwise )
{
    return Rotation( Math::Radians( a_dDegrees ),
                     ac_roAxis, ac_roOrigin, a_bClockwise );
}

}   // namespace Space

#endif  // TRANSFORM__TRANSLATE_ROTATE__INL
