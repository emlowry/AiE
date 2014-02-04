/******************************************************************************
 * File:               Transform.h
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        Functions for creating transform matrices.
 * Last Modified:      January 5, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

#ifndef TRANSFORM__H
#define TRANSFORM__H

#include "ImExportMacro.h"
#include "PointVector.h"
#include "Matrix.h"

namespace Plane
{
    
// simplify typing
typedef Math::Matrix< double, 2 > PointTransform;
typedef Math::Matrix< double, 3 > Transform;
typedef Transform HomogeneousTransform;
typedef Transform HVectorTransform;

// Make a transformation that performs the given transformation about a point
IMEXPORT Transform
   TransformationAbout( const Transform& ac_roTransform,
                        const PointVector& ac_roOrigin = PointVector::Origin() );

// Scale
IMEXPORT PointTransform PointScaling( double a_dFactor );
IMEXPORT Transform
    Scaling( double a_dFactor,
             const PointVector& ac_roOrigin = PointVector::Origin() );
IMEXPORT PointTransform PointScaling( double a_dX, double a_dY );
IMEXPORT Transform
    Scaling( double a_dX, double a_dY,
             const PointVector& ac_roOrigin = PointVector::Origin() );
IMEXPORT PointTransform PointScaling( const PointVector& ac_roFactor );
IMEXPORT Transform
    Scaling( const PointVector& ac_roFactor,
             const PointVector& ac_roOrigin = PointVector::Origin() );

// Translate
IMEXPORT Transform Translation( double a_dX, double a_dY );
IMEXPORT Transform Translation( const PointVector& ac_roTranslation );
IMEXPORT Transform
    Translation( double a_dTime,
                 const PointVector& ac_roVelocity = PointVector::Unit(0) );

// Rotate
IMEXPORT PointTransform PointRotation( double a_dRadians,
                                       bool a_bClockwise = false );
IMEXPORT Transform
    Rotation( double a_dRadians, bool a_bClockwise,
              const PointVector& ac_roOrigin = PointVector::Origin() );
IMEXPORT Transform
    Rotation( double a_dRadians,
              const PointVector& ac_roOrigin = PointVector::Origin(),
              bool a_bClockwise = false );
IMEXPORT PointTransform PointDegreeRotation( double a_dDegrees,
                                             bool a_bClockwise = false );
IMEXPORT Transform
    DegreeRotation( double a_dDegrees, bool a_bClockwise,
                    const PointVector& ac_roOrigin = PointVector::Origin() );
IMEXPORT Transform
    DegreeRotation( double a_dDegrees,
                    const PointVector& ac_roOrigin = PointVector::Origin(),
                    bool a_bClockwise = false );

}   // namespace Plane
typedef Plane::PointTransform PointTransform2D;
typedef Plane::Transform Transform2D;
typedef Transform2D HomogeneousTransform2D;
typedef Transform2D HVectorTransform2D;

namespace Space
{

// simplify typing
typedef Math::Matrix< double, 3 > PointTransform;
typedef Math::Matrix< double, 4 > Transform;
typedef Transform HomogeneousTransform;
typedef Transform HVectorTransform;

// Make a transformation that performs the given transformation about a point
IMEXPORT Transform
   TransformationAbout( const Transform& ac_roTransform,
                        const PointVector& ac_roOrigin = PointVector::Origin() );

// Scale
IMEXPORT PointTransform PointScaling( double a_dFactor );
IMEXPORT Transform
    Scaling( double a_dFactor,
             const PointVector& ac_roOrigin = PointVector::Origin() );
IMEXPORT PointTransform PointScaling( double a_dX, double a_dY, double a_dZ );
IMEXPORT Transform
    Scaling( double a_dX, double a_dY, double a_dZ,
             const PointVector& ac_roOrigin = PointVector::Origin() );
IMEXPORT PointTransform PointScaling( const PointVector& ac_roFactor );
IMEXPORT Transform
    Scaling( const PointVector& ac_roFactor,
             const PointVector& ac_roOrigin = PointVector::Origin() );

// Translate
IMEXPORT Transform Translation( double a_dX, double a_dY, double a_dZ );
IMEXPORT Transform Translation( const PointVector& ac_roTranslation );
IMEXPORT Transform
    Translation( double a_dTime,
                 const PointVector& ac_roVelocity = PointVector::Unit(0) );

// Rotate
IMEXPORT PointTransform
    PointRotation( double a_dRadians, bool a_bClockwise,
                   const PointVector& ac_roAxis = PointVector::Unit(2) );
IMEXPORT PointTransform
    PointRotation( double a_dRadians,
                   const PointVector& ac_roAxis = PointVector::Unit(2),
                   bool a_bClockwise = false );
IMEXPORT Transform
    Rotation( double a_dRadians, bool a_bClockwise,
              const PointVector& ac_roAxis = PointVector::Unit(2),
              const PointVector& ac_roOrigin = PointVector::Origin() );
IMEXPORT Transform
    Rotation( double a_dRadians,
              const PointVector& ac_roAxis, bool a_bClockwise,
              const PointVector& ac_roOrigin = PointVector::Origin() );
IMEXPORT Transform
    Rotation( double a_dRadians,
              const PointVector& ac_roAxis = PointVector::Unit(2),
              const PointVector& ac_roOrigin = PointVector::Origin(),
              bool a_bClockwise = false );
IMEXPORT PointTransform
    PointDegreeRotation( double a_dDegrees, bool a_bClockwise,
                         const PointVector& ac_roAxis = PointVector::Unit(2) );
IMEXPORT PointTransform
    PointDegreeRotation( double a_dDegrees,
                         const PointVector& ac_roAxis = PointVector::Unit(2),
                         bool a_bClockwise = false );
IMEXPORT Transform
    DegreeRotation( double a_dDegrees, bool a_bClockwise,
                    const PointVector& ac_roAxis = PointVector::Unit(2),
                    const PointVector& ac_roOrigin = PointVector::Origin() );
IMEXPORT Transform
    DegreeRotation( double a_dDegrees,
                    const PointVector& ac_roAxis, bool a_bClockwise,
                    const PointVector& ac_roOrigin = PointVector::Origin() );
IMEXPORT Transform
    DegreeRotation( double a_dDegrees,
                    const PointVector& ac_roAxis = PointVector::Unit(2),
                    const PointVector& ac_roOrigin = PointVector::Origin(),
                    bool a_bClockwise = false );

// Perspective project onto plane z = -nearDistance.  Remap coordinates from
//  x = [-screenSizeX/2, screenSizeX/2], y = [-screenSizeY/2, screenSizeY/2],
//  z = [-near, -far] to x' = [ -screenCenterX - 0.5, -screenCenterX + 0.5],
//  y' = [ -screenCenterY - 0.5, -screenCenterY + 0.5], z' = [0, 1].
IMEXPORT Transform
    PerspectiveProjection( double a_dNearDistance, double a_dFarDistance,
                           const Plane::PointVector& ac_roScreenSize,
                           const Plane::PointVector& ac_roScreenCenter
                                                      = PointVector::Origin() );

// Parallel project onto plane z = -nearDistance.  Remap coordinates from
//  x = [-screenSizeX/2, screenSizeX/2], y = [-screenSizeY/2, screenSizeY/2],
//  z = [-near, -far] to x' = [ -screenCenterX - 0.5, -screenCenterX + 0.5],
//  y' = [ -screenCenterY - 0.5, -screenCenterY + 0.5], z' = [0, 1].
IMEXPORT Transform
    ParallelProjection( double a_dNearDistance, double a_dFarDistance,
                        const Plane::PointVector& ac_roScreenSize,
                        const Plane::PointVector& ac_roScreenCenter
                                                      = PointVector::Origin() );

}   // namespace Space
typedef Space::PointTransform PointTransform3D;
typedef Space::Transform Transform3D;
typedef Transform2D HomogeneousTransform3D;
typedef Transform2D HVectorTransform3D;

#endif  // TRANSFORM__H