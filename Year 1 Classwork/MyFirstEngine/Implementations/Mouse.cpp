/******************************************************************************
 * File:               Mouse.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       March 25, 2014
 * Description:        Class for managing mouse input
 * Last Modified:      March 25, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#include "../Declarations/Mouse.h"
#include "../Declarations/GameEngine.h"
#include "../Declarations/GLFW.h"
#include <stdexcept>

//
// File-only helper functions and classes
//
namespace
{

    // Store data about when mouse buttons were pressed or released and which
    // window, if any, the cursor is in.
    static double sg_adPressTimes[ MyFirstEngine::Mouse::BUTTON_COUNT ];
    static double sg_adReleaseTimes[ MyFirstEngine::Mouse::BUTTON_COUNT ];
    static MyFirstEngine::GameWindow* sg_poMouseWindow = nullptr;
    static double sg_dMouseWindowChangeTime = 0.0;

    // Called if the mouse enters or exits a game window
    static void CursorEnterCallback( GLFWwindow* a_poWindow, int a_iEntered )
    {
        MyFirstEngine::GameWindow* poWindow =
            MyFirstEngine::GameWindow::Get( a_poWindow );
        if( GL_FALSE == a_iEntered && poWindow == sg_poMouseWindow )
        {
            sg_dMouseWindowChangeTime = MyFirstEngine::GameEngine::LastTime();
            sg_poMouseWindow = nullptr;
        }
        else if( GL_TRUE == a_iEntered )
        {
            if( poWindow != sg_poMouseWindow )
            {
                sg_dMouseWindowChangeTime =
                    MyFirstEngine::GameEngine::LastTime();
            }
            sg_poMouseWindow = poWindow;
        }
    }

    // Called if a mouse button is pressed
    static void MouseButtonCallback( GLFWwindow* a_poWindow, int a_iButton,
                                     int a_iAction, int a_iMods )
    {
        if( 0 <= a_iButton && MyFirstEngine::Mouse::BUTTON_COUNT > a_iButton )
        {
            if( GLFW_PRESS == a_iAction &&
                sg_adPressTimes[ a_iButton ] <= sg_adReleaseTimes[ a_iButton ] )
            {
                sg_adPressTimes[ a_iButton ] =
                    MyFirstEngine::GameEngine::LastTime();
            }
            else if( GLFW_RELEASE == a_iAction &&
                sg_adPressTimes[ a_iButton ] >= sg_adReleaseTimes[ a_iButton ] )
            {
                sg_adReleaseTimes[ a_iButton ] =
                    MyFirstEngine::GameEngine::LastTime();
            }
        }
    }

}   // namespace

//
// Class functions
//
namespace MyFirstEngine
{

// Set up or clean up data
void Mouse::InitializeInstance()
{
    for( unsigned int ui = 0; ui < BUTTON_COUNT; ++ui )
    {
        sg_adPressTimes[ ui ] = 0.0;
        sg_adReleaseTimes[ ui ] = 0.0;
    }
}
void Mouse::TerminateInstance()
{
    sg_dMouseWindowChangeTime = 0.0;
    sg_poMouseWindow = nullptr;
}

//
// Static functions
//

// When was a button last released or when did it last start being pressed?
bool Mouse::ButtonIsPressed( Button a_eButton )
{
    if( 0 > a_eButton || BUTTON_COUNT <= a_eButton )
    {
        throw std::runtime_error( "Invalid mouse button" );
    }
    return ( IsInitialized() &&
             sg_adPressTimes[ a_eButton ] > sg_adReleaseTimes[ a_eButton ] );
}
double Mouse::ButtonTime( Button a_eButton )
{
    if( 0 > a_eButton || BUTTON_COUNT <= a_eButton )
    {
        throw std::runtime_error( "Invalid mouse button" );
    }
    return  GameEngine::LastTime() -
                std::max( sg_adPressTimes[ a_eButton ],
                          sg_adReleaseTimes[ a_eButton ] );
}

// Where is the cursor's last reported position, in pixels, relative to the
// center of the given window (+y = up) and is it even in said window?  If
// no window is given, use main window. If window isn't valid GLFW window,
// return origin.
Point2D Mouse::Position( GameWindow* a_poWindow )
{
    if( nullptr == a_poWindow )
    {
        a_poWindow = &GameEngine::MainWindow();
    }
    if( !a_poWindow->IsOpen() )
    {
        return Point2D::Origin();
    }
    Point2D oResult;
    glfwGetCursorPos( a_poWindow->m_poWindow, &oResult.x, &oResult.y );
    oResult.x -= a_poWindow->GetSize().x / 2;
    oResult.y = a_poWindow->GetSize().y / 2 - oResult.y;
    return oResult;
}

// Hook up the mouse event handlers for the given window
void Mouse::Register( GameWindow& a_roWindow )
{
    if( nullptr != a_roWindow.m_poWindow )
    {
        glfwSetCursorEnterCallback( a_roWindow.m_poWindow, CursorEnterCallback );
        glfwSetMouseButtonCallback( a_roWindow.m_poWindow, MouseButtonCallback );
    }
}
void Mouse::Deregister( GameWindow& a_roWindow )
{
    if( nullptr != a_roWindow.m_poWindow )
    {
        glfwSetCursorEnterCallback( a_roWindow.m_poWindow, nullptr );
        glfwSetMouseButtonCallback( a_roWindow.m_poWindow, nullptr );
        if( sg_poMouseWindow == &a_roWindow )
        {
            sg_poMouseWindow = nullptr;
            sg_dMouseWindowChangeTime = GameEngine::LastTime();
        }
    }
}

// What game window, if any, is the cursor currently in?
GameWindow* Mouse::Window()
{
    return sg_poMouseWindow;
}

// When did the window the cursor is in (if any) last change"
static double WindowChangeTime()
{
    return sg_dMouseWindowChangeTime;
}

}   // namespace MyFirstEngine