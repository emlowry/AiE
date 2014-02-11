/******************************************************************************
 * File:               GameWindow.inl
 * Author:             Elizabeth Lowry
 * Date Created:       February 10, 2014
 * Description:        Inline function implementations for the GameWindow class.
 * Last Modified:      February 10, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef GAME_WINDOW__INL
#define GAME_WINDOW__INL

#include "Declarations\GLFW.h"
#include "Declarations\GameWindow.h"
#include "MathLibrary.h"
#include <stdexcept>
#include <string>
#include <vector>

#include "Declarations\MyFirstEngineMacros.h"

namespace MyFirstEngine
{

// Constructors
INLINE GameWindow::GameWindow( const IntPoint2D& ac_roSize, const char* ac_pcTitle )
    : m_oSize( ac_roSize ), m_oTitle( ac_pcTitle )
{
    SetUp();
}
INLINE GameWindow::GameWindow( unsigned int a_uiWidth, unsigned int a_uiHeight,
                               const char* ac_pcTitle )
    : m_oSize( a_uiWidth, a_uiHeight ), m_oTitle( ac_pcTitle )
{
    SetUp();
}
INLINE void GameWindow::SetUp()
{
    m_uiIndex = Windows().size();
    Windows().push_back( this );
}

// Destructor actually does something in this class
INLINE GameWindow::~GameWindow()
{
    Destroy();
    Windows()[ m_uiIndex ] = nullptr;
}

// Set window properties
INLINE void GameWindow::SetSize( unsigned int a_uiWidth, unsigned int a_uiHeight )
{
    m_oSize.x = a_uiWidth;
    m_oSize.y = a_uiHeight;
    if( IsOpen() )
    {
        glfwSetWindowSize( m_poWindow, a_uiWidth, a_uiHeight );
    }
}
INLINE void GameWindow::SetSize( const IntPoint2D& ac_roSize )
{
    m_oSize = ac_roSize;
    if( IsOpen() )
    {
        glfwSetWindowSize( m_poWindow, ac_roSize.x, ac_roSize.y );
    }
}
INLINE void GameWindow::SetTitle( const char* ac_pcTitle )
{
    m_oTitle = ac_pcTitle;
    if( IsOpen() )
    {
        glfwSetWindowTitle( m_poWindow, ac_pcTitle );
    }
}

// set flag indicating window shouldn't close
INLINE void GameWindow::CancelClose()
{
    glfwSetWindowShouldClose( m_poWindow, GL_FALSE );
}

// set flag indicating window should close
INLINE void GameWindow::Close()
{
    glfwSetWindowShouldClose( m_poWindow, GL_TRUE );
}

// destroy the GLFW window object
INLINE void GameWindow::Destroy()
{
    if( IsOpen() )
    {
        Lookup().erase( m_poWindow );
        glfwDestroyWindow( m_poWindow );
    }
}

// called when this window is closed
INLINE void GameWindow::DoClose()
{
    if( IsOpen() )
    {
        OnClose();
        if( IsClosing() )
        {
            Destroy();
        }
    }
}

// does GLFW flag indicate window should be closed?
INLINE bool GameWindow::IsClosing() const
{
    return IsOpen() ? ( GL_TRUE == glfwWindowShouldClose( m_poWindow ) ) : false;
}

// does a GLFW object for this window exist?
INLINE bool GameWindow::IsOpen() const
{
    return ( nullptr != m_poWindow );
}

// actually create the window with GLFW
INLINE bool GameWindow::Open()
{
    if( !IsOpen() )
    {
        m_poWindow = glfwCreateWindow( m_oSize.x, m_oSize.y, m_oTitle.CString(),
                                       nullptr, nullptr );
        if( nullptr != m_poWindow )
        {
            Lookup()[ m_poWindow ] = m_uiIndex;
            glfwSetWindowCloseCallback( m_poWindow, OnCloseWindow );
        }
    }
    return IsOpen();
}

//
// Static functions
//

// Destroy all windows
INLINE void GameWindow::DestroyAll()
{
    for each( GameWindow* poWindow in Windows() )
    {
        if( nullptr != poWindow )
        {
            poWindow->Destroy();
        }
    }
}

// Get a specific window
// if there is no window at the given index, throw exception
INLINE GameWindow& GameWindow::Get( WindowIndex a_uiIndex )
{
    if( a_uiIndex >= Windows().size() || nullptr == Windows()[ a_uiIndex ] )
    {
        throw std::out_of_range( "No window with that index" );
    }
    return *( Windows()[ a_uiIndex ] );
}

// Get a reference to the static map linking GLFWwindow pointers to GameWindows
INLINE GameWindow::WindowLookup& GameWindow::Lookup()
{
    static WindowLookup s_oLookup;
    return s_oLookup;
}

// GLFW callback for window close
INLINE void GameWindow::OnCloseWindow( GLFWwindow* a_poWindow )
{
    if( Lookup().count( a_poWindow ) != 0 )
    {
        Windows()[ Lookup()[ a_poWindow ] ]->DoClose();
    }
}

// Get a reference to the static list of windows
INLINE GameWindow::WindowSet& GameWindow::Windows()
{
    static WindowSet s_oWindows;
    return s_oWindows;
}

}   // namespace MyFirstEngine

#endif  // GAME_WINDOW__INL
