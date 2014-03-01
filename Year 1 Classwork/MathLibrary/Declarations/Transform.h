/******************************************************************************
 * File:               Transform.h
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        Functions for creating transform matrices.
 * Last Modified:      February 10, 2014
 * Last Modification:  Templatizing PointVector.
 ******************************************************************************/

#ifndef TRANSFORM__H
#define TRANSFORM__H

#include "PointVector.h"
#include "Matrix.h"
#include "ImExportMacro.h"

// explicit instantiations
EXTERN_T_INST template class IMEXPORT_T_INST Math::Matrix< double, 2 >;
EXTERN_T_INST template class IMEXPORT_T_INST Math::Matrix< double, 3 >;
EXTERN_T_INST template class IMEXPORT_T_INST Math::Matrix< double, 4 >;

namespace Plane
{

using namespace Math;
    
// simplify typing
typedef Matrix< double, 2 > PointTransform;
typedef Matrix< double, 3 > Transform;
typedef Transform HomogeneousTransform;
typedef Transform HVectorTransform;

// Make a transformation that performs the given transformation about a point
IMEXPORT Transform
   TransformationAbout( const Transform& ac_roTransform,
                        const Point& ac_roOrigin = Point::Origin() );

// Scale
IMEXPORT PointTransform PointScaling( double a_dFactor );
IMEXPORT Transform
    Scaling( double a_dFactor, const Point& ac_roOrigin = Point::Origin() );
IMEXPORT PointTransform PointScaling( double a_dX, double a_dY );
IMEXPORT Transform
    Scaling( double a_dX, double a_dY,
             const Point& ac_roOrigin = Point::Origin() );
IMEXPORT PointTransform PointScaling( const Point& ac_roFactor );
IMEXPORT Transform
    Scaling( const Point& ac_roFactor,
             const Point& ac_roOrigin = Point::Origin() );

// Translate
IMEXPORT Transform Translation( double a_dX, double a_dY );
IMEXPORT Transform Translation( const Point& ac_roTranslation );
IMEXPORT Transform
    Translation( double a_dTime, const Point& ac_roVelocity = Point::Unit(0) );

// Rotate
IMEXPORT PointTransform PointRotation( double a_dRadians,
                                       bool a_bClockwise = false );
IMEXPORT Transform
    Rotation( double a_dRadians, bool a_bClockwise,
              const Point& ac_roOrigin = Point::Origin() );
IMEXPORT Transform
    Rotation( double a_dRadians,
              const Point& ac_roOrigin = Point::Origin(),
              bool a_bClockwise = false );
IMEXPORT PointTransform PointDegreeRotation( double a_dDegrees,
                                             bool a_bClockwise = false );
IMEXPORT Transform
    DegreeRotation( double a_dDegrees, bool a_bClockwise,
                    const Point& ac_roOrigin = Point::Origin() );
IMEXPORT Transform
    DegreeRotation( double a_dDegrees,
                    const Point& ac_roOrigin = Point::Origin(),
                    bool a_bClockwise = false );

}   // namespace Plane
typedef Plane::PointTransform PointTransform2D;
typedef Plane::Transform Transform2D;
typedef Transform2D HomogeneousTransform2D;
typedef Transform2D HVectorTransform2D;

namespace Space
{

using namespace Math;

// simplify typing
typedef Matrix< double, 3 > PointTransform;
typedef Matrix< double, 4 > Transform;
typedef Transform HomogeneousTransform;
typedef Transform HVectorTransform;

// Make a transformation that performs the given transformation about a point
IMEXPORT Transform
   TransformationAbout( const Transform& ac_roTransform,
                        const Point& ac_roOrigin = Point::Origin() );

// Scale
IMEXPORT PointTransform PointScaling( double a_dFactor );
IMEXPORT Transform
    Scaling( double a_dFactor, const Point& ac_roOrigin = Point::Origin() );
IMEXPORT PointTransform PointScaling( double a_dX, double a_dY, double a_dZ );
IMEXPORT Transform
    Scaling( double a_dX, double a_dY, double a_dZ,
             const Point& ac_roOrigin = Point::Origin() );
IMEXPORT PointTransform PointScaling( const Point& ac_roFactor );
IMEXPORT Transform
    Scaling( const Point& ac_roFactor,
             const Point& ac_roOrigin = Point::Origin() );

// Translate
IMEXPORT Transform Translation( double a_dX, double a_dY, double a_dZ );
IMEXPORT Transform Translation( const Point& ac_roTranslation );
IMEXPORT Transform
    Translation( double a_dTime, const Point& ac_roVelocity = Point::Unit(0) );

// Rotate
IMEXPORT PointTransform
    PointRotation( double a_dRadians, bool a_bClockwise,
                   const Point& ac_roAxis = Point::Unit(2) );
IMEXPORT PointTransform
    PointRotation( double a_dRadians,
                   const Point& ac_roAxis = Point::Unit(2),
                   bool a_bClockwise = false );
IMEXPORT PointTransform
    PointRotation( double a_dYaw, double a_dPitch, double a_dRoll,
                   bool a_bClockwise = false );
IMEXPORT Transform
    Rotation( double a_dRadians, bool a_bClockwise,
              const Point& ac_roAxis = Point::Unit(2),
              const Point& ac_roOrigin = Point::Origin() );
IMEXPORT Transform
    Rotation( double a_dRadians,
              const Point& ac_roAxis, bool a_bClockwise,
              const Point& ac_roOrigin = Point::Origin() );
IMEXPORT Transform
    Rotation( double a_dRadians,
              const Point& ac_roAxis = Point::Unit(2),
              const Point& ac_roOrigin = Point::Origin(),
              bool a_bClockwise = false );
IMEXPORT Transform
    Rotation( double a_dYaw, double a_dPitch, double a_dRoll, bool a_bClockwise,
              const Point& ac_roOrigin = Point::Origin() );
IMEXPORT Transform
    Rotation( double a_dYaw, double a_dPitch, double a_dRoll,
              const Point& ac_roOrigin = Point::Origin(),
              bool a_bClockwise = false );
IMEXPORT PointTransform
    PointDegreeRotation( double a_dDegrees, bool a_bClockwise,
                         const Point& ac_roAxis = Point::Unit(2) );
IMEXPORT PointTransform
    PointDegreeRotation( double a_dDegrees,
                         const Point& ac_roAxis = Point::Unit(2),
                         bool a_bClockwise = false );
IMEXPORT PointTransform
    PointDegreeRotation( double a_dYaw, double a_dPitch, double a_dRoll,
                         bool a_bClockwise = false );
IMEXPORT Transform
    DegreeRotation( double a_dDegrees, bool a_bClockwise,
                    const Point& ac_roAxis = Point::Unit(2),
                    const Point& ac_roOrigin = Point::Origin() );
IMEXPORT Transform
    DegreeRotation( double a_dDegrees,
                    const Point& ac_roAxis, bool a_bClockwise,
                    const Point& ac_roOrigin = Point::Origin() );
IMEXPORT Transform
    DegreeRotation( double a_dDegrees,
                    const Point& ac_roAxis = Point::Unit(2),
                    const Point& ac_roOrigin = Point::Origin(),
                    bool a_bClockwise = false );
IMEXPORT Transform
    DegreeRotation( double a_dYaw, double a_dPitch, double a_dRoll,
                    bool a_bClockwise,
                    const Point& ac_roOrigin = Point::Origin() );
IMEXPORT Transform
    DegreeRotation( double a_dYaw, double a_dPitch, double a_dRoll,
                    const Point& ac_roOrigin = Point::Origin(),
                    bool a_bClockwise = false );

// Perspective project onto plane z = -nearDistance.  Remap coordinates from
//  x = [-screenSizeX/2, screenSizeX/2], y = [-screenSizeY/2, screenSizeY/2],
//  z = [-near, -far] to x' = [ -screenCenterX - 0.5, -screenCenterX + 0.5],
//  y' = [ -screenCenterY - 0.5, -screenCenterY + 0.5], z' = [0, 1].
IMEXPORT Transform
    PerspectiveProjection( double a_dNearDistance, double a_dFarDistance,
                           const Plane::Point& ac_roScreenSize,
                           const Plane::Point& ac_roScreenCenter
                                                            = Point::Origin() );

// Parallel project onto plane z = -nearDistance.  Remap coordinates from
//  x = [-screenSizeX/2, screenSizeX/2], y = [-screenSizeY/2, screenSizeY/2],
//  z = [-near, -far] to x' = [ -screenCenterX - 0.5, -screenCenterX + 0.5],
//  y' = [ -screenCenterY - 0.5, -screenCenterY + 0.5], z' = [0, 1].
IMEXPORT Transform
    ParallelProjection( double a_dNearDistance, double a_dFarDistance,
                        const Plane::Point& ac_roScreenSize,
                        const Plane::Point& ac_roScreenCenter
                                                            = Point::Origin() );

}   // namespace Space
typedef Space::PointTransform PointTransform3D;
typedef Space::Transform Transform3D;
typedef Transform2D HomogeneousTransform3D;
typedef Transform2D HVectorTransform3D;

#ifdef INLINE_IMPLEMENTATION
#include "../Implementations/Transform.inl"
#endif

#endif  // TRANSFORM__H