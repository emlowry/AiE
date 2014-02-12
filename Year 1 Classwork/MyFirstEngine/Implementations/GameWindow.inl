/******************************************************************************
 * File:               GameWindow.inl
 * Author:             Elizabeth Lowry
 * Date Created:       February 10, 2014
 * Description:        Inline function implementations for the GameWindow class.
 * Last Modified:      February 11, 2014
 * Last Modification:  Adding GameState.
 ******************************************************************************/

#ifndef GAME_WINDOW__INL
#define GAME_WINDOW__INL

#include "Declarations\GLFW.h"
#include "Declarations\GameEngine.h"
#include "Declarations\GameState.h"
#include "Declarations\GameWindow.h"
#include "MathLibrary.h"
#include <stdexcept>
#include <string>
#include <vector>

#include "Declarations\MyFirstEngineMacros.h"

namespace MyFirstEngine
{

// Constructors
INLINE GameWindow::GameWindow( const IntPoint2D& ac_roSize,
                               const char* ac_pcTitle )
    : m_oSize( ac_roSize ), m_oFramePadding( 0 ),
      m_oTitle( ac_pcTitle ), m_poWindow( nullptr )
{
    SetUp();
}
INLINE GameWindow::GameWindow( unsigned int a_uiWidth, unsigned int a_uiHeight,
                               const char* ac_pcTitle )
    : m_oSize( a_uiWidth, a_uiHeight ), m_oFramePadding( 0 ),
      m_oTitle( ac_pcTitle ), m_poWindow( nullptr )
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
INLINE GameWindow& GameWindow::SetSize( unsigned int a_uiWidth,
                                        unsigned int a_uiHeight )
{
    m_oSize.x = a_uiWidth;
    m_oSize.y = a_uiHeight;
    if( IsOpen() )
    {
        glfwSetWindowSize( m_poWindow,
                           a_uiWidth + m_oFramePadding.x,
                           a_uiHeight + m_oFramePadding.y );
    }
    return *this;
}
INLINE GameWindow& GameWindow::SetSize( const IntPoint2D& ac_roSize )
{
    m_oSize = ac_roSize;
    if( IsOpen() )
    {
        glfwSetWindowSize( m_poWindow,
                           ac_roSize.x + m_oFramePadding.x,
                           ac_roSize.y + m_oFramePadding.y );
    }
    return *this;
}
INLINE GameWindow& GameWindow::SetTitle( const char* ac_pcTitle )
{
    m_oTitle = ac_pcTitle;
    if( IsOpen() )
    {
        glfwSetWindowTitle( m_poWindow, ac_pcTitle );
    }
    return *this;
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
        m_poWindow = nullptr;
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
        CreateWindow();
        AdjustFramePadding();
    }
    return IsOpen();
}
INLINE void GameWindow::CreateWindow()
{
    m_poWindow = glfwCreateWindow( m_oSize.x + m_oFramePadding.x,
                                    m_oSize.y + m_oFramePadding.y,
                                    m_oTitle.CString(), nullptr, nullptr );
    if( nullptr != m_poWindow )
    {
        Lookup()[ m_poWindow ] = m_uiIndex;
        glfwSetWindowCloseCallback( m_poWindow, OnCloseWindow );
    }
}
INLINE void GameWindow::AdjustFramePadding()
{
    IntPoint2D oBufferSize;
    glfwGetFramebufferSize( m_poWindow, &( oBufferSize.x ), &( oBufferSize.y ) );
    if( m_oSize != oBufferSize )
    {
        m_oFramePadding = m_oSize - oBufferSize;
        glfwSetWindowSize( m_poWindow,
                           m_oSize.x + m_oFramePadding.x,
                           m_oSize.y + m_oFramePadding.y );
    }
}

// make/check if current context window
INLINE bool GameWindow::IsCurrent()
{
    return IsOpen() ? glfwGetCurrentContext() == m_poWindow : false;
}
INLINE GameWindow& GameWindow::MakeCurrent()
{
    Open();
    glfwMakeContextCurrent( m_poWindow );
    return *this;
}

// advance by frame
INLINE void GameWindow::SwapBuffers()
{
    if( IsOpen() )
    {
        glfwSwapBuffers( m_poWindow );
    }
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
INLINE GameWindow& GameWindow::Get( Index a_uiIndex )
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
    if( Lookup().count( a_poWindow ) != 0 &&
        nullptr != Windows()[ Lookup()[ a_poWindow ] ] )
    {
        GameWindow& roWindow = *( Windows()[ Lookup()[ a_poWindow ] ] );
        GameEngine::CurrentState().OnCloseWindow( roWindow );
        if( roWindow.IsClosing() )
        {
            roWindow.DoClose();
        }
    }
}

// Swap frame buffers of all open windows
INLINE void GameWindow::SwapAllBuffers()
{
    for each( GameWindow* poWindow in Windows() )
    {
        if( nullptr != poWindow )
        {
            poWindow->SwapBuffers();
        }
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
