/******************************************************************************
 * File:               Camera.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       March 22, 2014
 * Description:        Class for managing the projection matrix.
 * Last Modified:      June 26, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

#include "../Declarations/Camera.h"
#include "../Declarations/GameEngine.h"
#include "../Declarations/GameWindow.h"
#include "MathLibrary.h"

namespace MyFirstEngine
{

const Rotation3D Camera::FACING_NEGY_Z_PLANE = Rotation3D::None();
const Rotation3D Camera::FACING_XY_PLANE = Rotation3D( Math::PI / 2, -Math::PI / 2 );

// Constructor
Camera::Camera()
    : m_dDepthOfView( 1 ), m_dFocalLength( 0 ), m_oPosition( Point3D::Origin() ),
      m_oRotation( FACING_XY_PLANE ), m_oScreenSize( 2, 2 ),
      m_bUpdateProjectionMatrix( true ), m_bUseCamera( false ) {}

// Control whether or not the camera is used - if disabled, projection
// matrix is identity.
void Camera::Enable()
{
    if( !IsEnabled() )
    {
        Instance().m_bUpdateProjectionMatrix = true;
    }
    Instance().m_bUseCamera = true;
}
void Camera::Disable()
{
    if( IsEnabled() )
    {
        Instance().m_bUpdateProjectionMatrix = true;
    }
    Instance().m_bUseCamera = false;
}
    
// Reset to default settings for 2D or 3D cameras.
void Camera::UseDefault2D()
{
    SetPosition( Point3D::Origin() );
    SetRotation( FACING_XY_PLANE );
    SetFocalLength( 0 );
    SetDepthOfView( 1 );
    UseWindowPixelScreenSize();
}
void Camera::UseDefault3D()
{
    SetPosition( Point3D::Origin() );
    SetRotation( FACING_NEGY_Z_PLANE );
    SetFocalLength( 1 );
    SetDepthOfView( 2 );
    UseDefaultScreenSize();
}

// Control what coordinates on the camera's zero plane become on the screen
void Camera::UseWindowPixelScreenSize()  // Use window pixel sized screen
{
    SetScreenSize( GameWindow::Current().GetSize() / 2 );
}
void Camera::UseDefaultScreenSize()  // Use default 2x2 screen
{
    SetScreenSize( 2, 2 );
}
void Camera::SetScreenSize( double a_dWidth, double a_dHeight )
{
    Point2D oSize( a_dWidth, a_dHeight );
    SetScreenSize( oSize );
}
void Camera::SetScreenSize( const Point2D& ac_roSize )
{
    if( ac_roSize / 2 != Instance().m_oScreenSize )
    {
        Instance().m_oScreenSize = ac_roSize;
        Instance().m_bUpdateProjectionMatrix = true;
    }
}
void Camera::SetAspectRatio( double a_dRatio, double a_dHeight )
{
    SetScreenSize( a_dRatio * a_dHeight, a_dHeight );
}

// Control perspective (<0 = parallel projection)
void Camera::SetFocalLength( double a_dLength )
{
    if( a_dLength != Instance().m_dFocalLength )
    {
        Instance().m_dFocalLength = a_dLength;
        Instance().m_bUpdateProjectionMatrix = true;
    }
}
void Camera::SetAngleOfView( double a_dRadians )
{
    a_dRadians = Math::ScrollRadians( a_dRadians );
    if( 0 == std::sin( a_dRadians / 2 ) )
    {
        SetFocalLength( 0 );
    }
    SetFocalLength( Instance().m_oScreenSize.x *
                    std::cos( a_dRadians / 2 ) / std::sin( a_dRadians / 2 ) );
}
void Camera::SetDepthOfView( double a_dDepth )   // far plane (near is zero)
{
    if( a_dDepth != Instance().m_dDepthOfView )
    {
        Instance().m_dDepthOfView = a_dDepth;
        Instance().m_bUpdateProjectionMatrix = true;
    }
}

// Control position and rotation of camera
void Camera::SetPosition( const Point3D& ac_roPosition )
{
    if( ac_roPosition != Instance().m_oPosition )
    {
        Instance().m_oPosition = ac_roPosition;
        Instance().m_bUpdateProjectionMatrix = true;
    }
}
void Camera::SetPosition( double a_dX, double a_dY, double a_dZ )
{
    Point3D oPosition( a_dX, a_dY, a_dZ );
    SetPosition( oPosition );
}
void Camera::SetRotation( double a_dYaw, double a_dPitch, double a_dRoll )
{
    Rotation3D oRotation( a_dYaw, a_dPitch, a_dRoll );
    SetRotation( oRotation );
}
void Camera::SetRotation( const Rotation3D& ac_roRotation )
{
    if( ac_roRotation != Instance().m_oRotation )
    {
        Instance().m_oRotation = ac_roRotation;
        Instance().m_bUpdateProjectionMatrix = true;
    }
}

// Push and Pop cameras - if you call push, then the projection will be the
// previous projection matrix times this - a camera view of another camera's
// view.
void Camera::Push() { GameEngine::PushProjection(); }
void Camera::Pop() { GameEngine::PopProjection(); }

// Recalculate the projection matrix, if neccessary
void Camera::Refresh()
{
    if( Instance().m_bUpdateProjectionMatrix )
    {
        // Get rid of stale projection matrix
        Pop();
        Push();

        if( !Instance().m_bUseCamera )
        {
            GameEngine::Projection() = Transform3D::Identity();
            Instance().m_bUpdateProjectionMatrix = false;
            return;
        }

        // move and rotate the world
        GameEngine::Projection() *=
            Space::Translation( -Instance().m_oPosition );
        GameEngine::Projection() *=
            ( Instance().m_oRotation ^ -1 ).MakeTransform();
        Transform3D oProjection = GameEngine::Projection();

        // The projection matrices assume that the z-axis points towards the
        // camera.  Since normally the z-axis is up and the x-axis forward,
        // rotate the world again.
        GameEngine::Projection() *= FACING_XY_PLANE.MakeTransform();
        oProjection = GameEngine::Projection();
        
        // apply the appropriate projection matrix
        if( 0.0 >= Instance().m_dFocalLength )
        {
            GameEngine::Projection() *=
                Space::ParallelProjection( 0, Instance().m_dDepthOfView,
                                           Instance().m_oScreenSize );
        }
        else
        {
            GameEngine::Projection() *=
                Space::Translation( 0, 0, -Instance().m_dFocalLength );
            GameEngine::Projection() *=
                Space::PerspectiveProjection( Instance().m_dFocalLength,
                                              Instance().m_dDepthOfView +
                                                Instance().m_dFocalLength,
                                              Instance().m_oScreenSize /
                                                Instance().m_dFocalLength );
        }/**/
        oProjection = GameEngine::Projection();
        /**/
        // now that the projection matrix is updated, it won't need to be
        // recalculated again until something changes.
        Instance().m_bUpdateProjectionMatrix = false;
    }
}

}   // namespace MyFirstEngine
