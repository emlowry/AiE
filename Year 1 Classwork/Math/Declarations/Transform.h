/******************************************************************************
 * File:               Transform.h
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        Functions for creating transform matrices.
 * Last Modified:      January 5, 2014
 * Last Modification:  Creation.
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
IMEXPORT PointTransform
    PointScaling( double a_dFactor );
IMEXPORT Transform Scaling( double a_dFactor,
                            const PointVector& ac_roOrigin
                                                      = PointVector::Origin() );
IMEXPORT PointTransform PointScaling( double a_dX, double a_dY );
IMEXPORT Transform Scaling( double a_dX, double a_dY,
                            const PointVector& ac_roOrigin
                                                      = PointVector::Origin() );
IMEXPORT PointTransform PointScaling( const PointVector& ac_roFactor );
IMEXPORT Transform Scaling( const PointVector& ac_roFactor,
                            const PointVector& ac_roOrigin
                                                      = PointVector::Origin() );

// Translate
IMEXPORT Transform Translation( double a_dX, double a_dY );
IMEXPORT Transform Translation( const PointVector& ac_roTranslation );
IMEXPORT Transform
    Translation( double a_dDistance,
                 const PointVector& ac_roDirection = PointVector::Unit(0) );

// Rotate
IMEXPORT PointTransform
    PointRotation( double a_dRadians );
IMEXPORT Transform Rotation( double a_dRadians,
                             const PointVector& ac_roOrigin
                                                      = PointVector::Origin() );

}   // namespace Plane

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
IMEXPORT Transform Scaling( double a_dFactor,
                            const PointVector& ac_roOrigin
                                                      = PointVector::Origin() );
IMEXPORT PointTransform PointScaling( double a_dX, double a_dY, double a_dZ );
IMEXPORT Transform Scaling( double a_dX, double a_dY, double a_dZ,
                            const PointVector& ac_roOrigin
                                                      = PointVector::Origin() );
IMEXPORT PointTransform PointScaling( const PointVector& ac_roFactor );
IMEXPORT Transform Scaling( const PointVector& ac_roFactor,
                            const PointVector& ac_roOrigin
                                                      = PointVector::Origin() );

// Translate
IMEXPORT Transform Translation( double a_dX, double a_dY, double a_dZ );
IMEXPORT Transform Translation( const PointVector& ac_roTranslation );
IMEXPORT Transform
    Translation( double a_dDistance,
                 const PointVector& ac_roDirection = PointVector::Unit(0) );

// Rotate
IMEXPORT PointTransform
    PointRotation( double a_dRadians,
                   const PointVector& ac_roAxis = PointVector::Unit(2) );
IMEXPORT Transform Rotation( double a_dRadians,
                             const PointVector& ac_roAxis = PointVector::Unit(2),
                             const PointVector& ac_roOrigin
                                                      = PointVector::Origin() );

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

#endif  // TRANSFORM__H