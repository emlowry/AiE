/******************************************************************************
 * File:               GameWindow.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       February 10, 2014
 * Description:        Inline function implementations for the GameWindow class.
 * Last Modified:      February 18, 2014
 * Last Modification:  Changing from inl to cpp.
 ******************************************************************************/

#include "..\Declarations\GLFW.h"
#include "..\Declarations\GameEngine.h"
#include "..\Declarations\GameState.h"
#include "..\Declarations\GameWindow.h"
#include "MathLibrary.h"
#include <stdexcept>
#include <string>
#include <vector>
#include <unordered_map>

namespace MyFirstEngine
{

// declare classes instead of typedefs to avoid compiler warnings
// definition is only in cpp
class GameWindow::WindowList : public std::vector< GameWindow* >
{
public:
    virtual ~WindowList() {}
};
class GameWindow::WindowLookup
    : std::unordered_map< GLFWwindow*, unsigned int >
{
public:
    virtual ~WindowLookup() {}
};

// Initialize static containers
GameWindow::WindowList* GameWindow::sm_poList = new GameWindow::WindowList();
GameWindow::WindowLookup* GameWindow::sm_poLookup = new GameWindow::WindowLookup();

// Constructors
GameWindow::GameWindow( const IntPoint2D& ac_roSize, const char* ac_pcTitle )
    : m_oSize( ac_roSize ), m_oFramePadding( 0 ),
      m_oTitle( ac_pcTitle ), m_poWindow( nullptr ),
      m_uiIndex( sm_poList->size() )
{
    sm_poList->push_back( this );
}
GameWindow::GameWindow( unsigned int a_uiWidth, unsigned int a_uiHeight,
                        const char* ac_pcTitle )
    : m_oSize( a_uiWidth, a_uiHeight ), m_oFramePadding( 0 ),
      m_oTitle( ac_pcTitle ), m_poWindow( nullptr ),
      m_uiIndex( sm_poList->size() )
{
    sm_poList->push_back( this );
}
// Destructor actually does something in this class
GameWindow::~GameWindow()
{
    Destroy();
    (*sm_poList)[ m_uiIndex ] = nullptr;
}

// Set window properties
GameWindow& GameWindow::SetSize( unsigned int a_uiWidth,
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
GameWindow& GameWindow::SetSize( const IntPoint2D& ac_roSize )
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
GameWindow& GameWindow::SetTitle( const char* ac_pcTitle )
{
    m_oTitle = ac_pcTitle;
    if( IsOpen() )
    {
        glfwSetWindowTitle( m_poWindow, ac_pcTitle );
    }
    return *this;
}

// Set the close flag for this window to false
void GameWindow::CancelClose()
{
    glfwSetWindowShouldClose( m_poWindow, GL_FALSE );
}

// Set the close flag for this window to true
void GameWindow::Close()
{
    glfwSetWindowShouldClose( m_poWindow, GL_TRUE );
}

// Is this window object flagged for closing?
bool GameWindow::IsClosing() const
{
    IsOpen() ? ( GL_TRUE == glfwWindowShouldClose( m_poWindow ) ) : false;
}

// destroy the GLFW window object
void GameWindow::Destroy()
{
    if( IsOpen() )
    {
        sm_poLookup->erase( m_poWindow );
        glfwDestroyWindow( m_poWindow );
        m_poWindow = nullptr;
    }
}

// called when this window is closed
void GameWindow::DoClose()
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

// actually create the window with GLFW
bool GameWindow::Open()
{
    if( !IsOpen() )
    {
        CreateWindow();
        AdjustFramePadding();
    }
    return IsOpen();
}
void GameWindow::CreateWindow()
{
    m_poWindow = glfwCreateWindow( m_oSize.x + m_oFramePadding.x,
                                    m_oSize.y + m_oFramePadding.y,
                                    m_oTitle.CString(), nullptr, nullptr );
    if( nullptr != m_poWindow )
    {
        (*sm_poLookup)[ m_poWindow ] = m_uiIndex;
        glfwSetWindowCloseCallback( m_poWindow, OnCloseWindow );
    }
}
void GameWindow::AdjustFramePadding()
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
bool GameWindow::IsCurrent()
{
    return IsOpen() ? glfwGetCurrentContext() == m_poWindow : false;
}
GameWindow& GameWindow::MakeCurrent()
{
    Open();
    glfwMakeContextCurrent( m_poWindow );
    return *this;
}

// advance by frame
void GameWindow::SwapBuffers()
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
void GameWindow::DestroyAll()
{
    for each( GameWindow* poWindow in sm_oList )
    {
        if( nullptr != poWindow )
        {
            poWindow->Destroy();
        }
    }
}

// Get a specific window
// if there is no window at the given index, throw exception
GameWindow& GameWindow::Get( unsigned int a_uiIndex )
{
    if( a_uiIndex >= sm_poList->size() || nullptr == (*sm_poList)[ a_uiIndex ] )
    {
        throw std::out_of_range( "No window with that index" );
    }
    return *( (*sm_poList)[ a_uiIndex ] );
}

// GLFW callback for window close
void GameWindow::OnCloseWindow( GLFWwindow* a_poWindow )
{
    if( sm_poLookup->count( a_poWindow ) != 0 &&
        nullptr != (*sm_poList)[ (*sm_poLookup)[ a_poWindow ] ] )
    {
        GameWindow& roWindow = *( (*sm_poList)[ (*sm_poLookup)[ a_poWindow ] ] );
        GameEngine::CurrentState().OnCloseWindow( roWindow );
        if( roWindow.IsClosing() )
        {
            roWindow.DoClose();
        }
    }
}

// Swap frame buffers of all open windows
void GameWindow::SwapAllBuffers()
{
    for each( GameWindow* poWindow in sm_oList )
    {
        if( nullptr != poWindow )
        {
            poWindow->SwapBuffers();
        }
    }
}

}   // namespace MyFirstEngine
