/******************************************************************************
 * File:               Camera.h
 * Author:             Elizabeth Lowry
 * Date Created:       March 22, 2014
 * Description:        Class for managing the projection matrix.
 *                      TODO: switch to non-singleton implementation so there
 *                      can be multiple cameras
 * Last Modified:      March 22, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef CAMERA__H
#define CAMERA__H

#include "MathLibrary.h"
#include "MyFirstEngineMacros.h"

namespace MyFirstEngine
{

class IMEXPORT_CLASS Camera : Utility::Singleton< Camera >
{
    friend Utility::Singleton< Camera >;
public:

    // Control whether or not the camera is used - if disabled, projection
    // matrix is identity.
    static void Enable();
    static void Disable();
    static bool IsEnabled() { return Instance().m_bUseCamera; }

    // Reset to default settings for 2D or 3D cameras.
    static void UseDefault2D();
    static void UseDefault3D();

    // Control what coordinates on the camera's zero plane become on the screen
    static void UseWindowPixelScreenSize(); // Use window pixel sized screen
    static void UseDefaultScreenSize(); // Use default 2x2 screen
    static void SetScreenSize( double a_dWidth, double a_dHeight );
    static void SetScreenSize( const Point2D& ac_roSize );
    static void SetAspectRatio( double a_dRatio, double a_dHeight = 2.0 );

    // Control perspective (<0 = parallel projection)
    static void SetFocalLength( double a_dLength );
    static void SetAngleOfView( double a_dRadians );
    static void SetDepthOfView( double a_dDepth );  // far plane (near is zero)

    // Control position and rotation of camera
    static void SetPosition( const Point3D& ac_roPosition );
    static void SetPosition( double a_dX, double a_dY, double a_dZ = 0.0 );
    static void SetRotation( double a_dYaw, double a_dPitch,
                             double a_dRoll = 0.0 );
    static void SetRotation( const Rotation3D& ac_roRotation );

    // Push and Pop cameras - if you call push, then the projection will be the
    // previous projection matrix times this - a camera view of another camera's
    // view.
    static void Push();
    static void Pop();

    // Recalculate the projection matrix, if neccessary
    static void Refresh();

    static const Rotation3D FACING_NEGY_Z_PLANE;    // z = up, x = forward
    static const Rotation3D FACING_XY_PLANE;    // z = backward, y = up, x = right

private:

    // Constructor
    Camera();

    double m_dDepthOfView;
    double m_dFocalLength;
    Point3D m_oPosition;
    Rotation3D m_oRotation;
    Point2D m_oScreenSize;
    bool m_bUpdateProjectionMatrix;
    bool m_bUseCamera;

};  // class Camera

}   // namespace MyFirstEngine

#endif  // CAMERA__H
