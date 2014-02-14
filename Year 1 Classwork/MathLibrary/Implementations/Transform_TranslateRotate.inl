/******************************************************************************
 * File:               Transform_TranslateRotate.h
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        Inline function implementations for translation and
 *                      rotation transformations.  Remember that this library
 *                      uses row vectors, not column.
 * Last Modified:      February 10, 2014
 * Last Modification:  Templatizing PointVector.
 ******************************************************************************/

#ifndef TRANSFORM__TRANSLATE_ROTATE__INL
#define TRANSFORM__TRANSLATE_ROTATE__INL

#include "../Declarations/Transform.h"
#include "../Declarations/ImExportMacro.h"

namespace Plane
{

// Translate
INLINE Transform Translation( double a_dX, double a_dY )
{
    double adTranslate[3][3] = { { 1.0,  0.0,  0.0 },
                                 { 0.0,  1.0,  0.0 },
                                 { a_dX, a_dY, 1.0 } };
    return Transform( adTranslate );
}
INLINE Transform Translation( const Point& ac_roTranslation )
{
    double adTranslate[3][3] =
    { { 1.0,                0.0,                0.0 },
      { 0.0,                1.0,                0.0 },
      { ac_roTranslation.x, ac_roTranslation.y, 1.0 } };
    return Transform( adTranslate );
}
INLINE Transform Translation( double a_dTime,
                              const Point& ac_roVelocity )
{
    Point oDistance = ac_roVelocity * a_dTime;
    return Translation( oDistance );
}

// Rotate
INLINE PointTransform
    PointRotation( double a_dRadians, bool a_bClockwise )
{
    a_dRadians *= ( a_bClockwise ? -1 : 1 );
    double dCos = std::cos( a_dRadians );
    double dSin = ( dCos == -1 || dCos == 1 ? 0 : std::sin( a_dRadians ) );
    dCos = ( dSin == -1 || dSin == 1 ? 0 : dCos );
    double adRotate[2][2] = { { dCos, dSin }, { dSin * -1, dCos } };
    return PointTransform( adRotate );
}
INLINE Transform Rotation( double a_dRadians, bool a_bClockwise,
                           const Point& ac_roOrigin )
{
    return Rotation( a_dRadians, ac_roOrigin, a_bClockwise );
}
INLINE Transform Rotation( double a_dRadians,
                           const Point& ac_roOrigin,
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
INLINE PointTransform PointDegreeRotation( double a_dDegrees,
                                           bool a_bClockwise )
{
    return PointRotation( Radians( a_dDegrees ),
                          a_bClockwise );
}
INLINE Transform DegreeRotation( double a_dDegrees, bool a_bClockwise,
                                 const Point& ac_roOrigin )
{
    return Rotation( Radians( a_dDegrees ), ac_roOrigin, a_bClockwise );
}
INLINE Transform DegreeRotation( double a_dDegrees,
                                 const Point& ac_roOrigin,
                                 bool a_bClockwise )
{
    return Rotation( Radians( a_dDegrees ), ac_roOrigin, a_bClockwise );
}

}   // namespace Plane

namespace Space
{

// Translate
INLINE Transform Translation( double a_dX, double a_dY, double a_dZ )
{
    double adTranslate[4][4] = { { 1.0,  0.0,  0.0,  0.0 },
                                 { 0.0,  1.0,  0.0,  0.0 },
                                 { 0.0,  0.0,  1.0,  0.0 },
                                 { a_dX, a_dY, a_dZ, 1.0 } };
    return Transform( adTranslate );
}
INLINE Transform Translation( const Point& ac_roTranslation )
{
    double adTranslate[4][4] =
    { { 1.0,                0.0,                0.0,                0.0 },
      { 0.0,                1.0,                0.0,                0.0 },
      { 0.0,                0.0,                1.0,                0.0 },
      { ac_roTranslation.x, ac_roTranslation.y, ac_roTranslation.z, 1.0 } };
    return Transform( adTranslate );
}
INLINE Transform Translation( double a_dTime,
                              const Point& ac_roVelocity )
{
    Point oDistance = ac_roVelocity * a_dTime;
    return Translation( oDistance );
}

// Rotate
INLINE PointTransform
    PointRotation( double a_dRadians, bool a_bClockwise,
                   const Point& ac_roAxis )
{
    return PointRotation( a_dRadians, ac_roAxis, a_bClockwise );
}
INLINE PointTransform
    PointRotation( double a_dRadians,
                   const Point& ac_roAxis,
                   bool a_bClockwise )
{
    a_dRadians *= ( a_bClockwise ? -1 : 1 );
    Point oN = ac_roAxis.Normal();
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
INLINE Transform Rotation( double a_dRadians, bool a_bClockwise,
                           const Point& ac_roAxis,
                           const Point& ac_roOrigin )
{
    return Rotation( a_dRadians, ac_roAxis, ac_roOrigin, a_bClockwise );
}
INLINE Transform Rotation( double a_dRadians,
                           const Point& ac_roAxis,
                           bool a_bClockwise,
                           const Point& ac_roOrigin )
{
    return Rotation( a_dRadians, ac_roAxis, ac_roOrigin, a_bClockwise );
}
INLINE Transform Rotation( double a_dRadians,
                           const Point& ac_roAxis,
                           const Point& ac_roOrigin,
                           bool a_bClockwise )
{
    a_dRadians *= ( a_bClockwise ? -1 : 1 );
    Point oN = ac_roAxis.Normal();
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
INLINE PointTransform PointDegreeRotation( double a_dDegrees,
                                           bool a_bClockwise,
                                           const Point& ac_roAxis )
{
    return PointRotation( Radians( a_dDegrees ), ac_roAxis, a_bClockwise );
}
INLINE PointTransform PointDegreeRotation( double a_dDegrees,
                                           const Point& ac_roAxis,
                                           bool a_bClockwise )
{
    return PointRotation( Radians( a_dDegrees ), ac_roAxis, a_bClockwise );
}
INLINE Transform DegreeRotation( double a_dDegrees, bool a_bClockwise,
                                 const Point& ac_roAxis,
                                 const Point& ac_roOrigin )
{
    return Rotation( Radians( a_dDegrees ),
                     ac_roAxis, ac_roOrigin, a_bClockwise );
}
INLINE Transform DegreeRotation( double a_dDegrees,
                                 const Point& ac_roAxis,
                                 bool a_bClockwise,
                                 const Point& ac_roOrigin )
{
    return Rotation( Radians( a_dDegrees ),
                     ac_roAxis, ac_roOrigin, a_bClockwise );
}
INLINE Transform DegreeRotation( double a_dDegrees,
                                 const Point& ac_roAxis,
                                 const Point& ac_roOrigin,
                                 bool a_bClockwise )
{
    return Rotation( Radians( a_dDegrees ),
                     ac_roAxis, ac_roOrigin, a_bClockwise );
}

}   // namespace Space

#endif  // TRANSFORM__TRANSLATE_ROTATE__INL
