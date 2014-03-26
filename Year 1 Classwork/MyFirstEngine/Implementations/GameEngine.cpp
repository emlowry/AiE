/******************************************************************************
 * File:               GameEngine.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       February 5, 2014
 * Description:        Implementations of GameEngine functions.
 * Last Modified:      March 25, 2014
 * Last Modification:  Hooking up mouse and keyboard event handling.
 ******************************************************************************/

#include "..\Declarations\Camera.h"
#include "..\Declarations\GameEngine.h"
#include "..\Declarations\GameState.h"
#include "..\Declarations\GameWindow.h"
#include "..\Declarations\GLFW.h"
#include "..\Declarations\Keyboard.h"
#include "..\Declarations\Mouse.h"
#include "..\Declarations\QuadShaderProgram.h"
#include "..\Declarations\Shader.h"
#include "..\Declarations\ShaderProgram.h"
#include "..\Declarations\SpriteShaderProgram.h"
#include <iostream>

namespace MyFirstEngine
{

// declare classes instead of typedefs to avoid compiler warnings
// definition is only in cpp
class GameEngine::StateStack : public std::stack< GameState* >
{
public:
    virtual ~StateStack() {}
};
class GameEngine::TransformStack : public std::stack< Transform3D >
{
public:
    virtual ~TransformStack() {}
};

// Default constructor is only used by the base Singleton class's Instance()
// function.  The user never instantiates a GameEngine object directly.
GameEngine::GameEngine()
    : m_bInitialized( false ), m_dLastTime( 0.0 ),
      m_poModelView( new TransformStack ),
      m_poProjection( new TransformStack ),
      m_poStates( new StateStack ) {}

// Destructor is virtual, since inheritance is involved.
GameEngine::~GameEngine()
{
    delete m_poStates;
    delete m_poModelView;
    delete m_poProjection;
}

// Returns the time since this function was last called.
double GameEngine::DeltaTime()
{
    double dThen = m_dLastTime;
    m_dLastTime = Time();
    m_dLastDeltaTime = m_dLastTime - dThen;
    return m_dLastTime - dThen;
}

//
// STATIC FUNCTIONS
//

// Replaces the now-deprecated OpenGL matrix stack
Transform3D GameEngine::ModelViewProjection()
{
    return ModelView() * Projection();
}
Transform3D& GameEngine::ModelView()
{
    if( Instance().m_poModelView->empty() )
    {
        Instance().m_poModelView->push( Transform3D::Identity() );
    }
    return Instance().m_poModelView->top();
}
Transform3D& GameEngine::Projection()
{
    if( Instance().m_poProjection->empty() )
    {
        Instance().m_poProjection->push( Transform3D::Identity() );
    }
    return Instance().m_poProjection->top();
}
Transform3D& GameEngine::SetModelView( const Transform3D& ac_roMatrix )
{
    ModelView() = ac_roMatrix;
    return ModelView();
}
Transform3D& GameEngine::SetProjection( const Transform3D& ac_roMatrix )
{
    Projection() = ac_roMatrix;
    return Projection();
}
Transform3D& GameEngine::ApplyAfterModelView( const Transform3D& ac_roMatrix )
{
    ModelView() *= ac_roMatrix;
    return ModelView();
}
Transform3D& GameEngine::ApplyAfterProjection( const Transform3D& ac_roMatrix )
{
    Projection() *= ac_roMatrix;
    return Projection();
}
Transform3D& GameEngine::ApplyBeforeModelView( const Transform3D& ac_roMatrix )
{
    ModelView() = ac_roMatrix * ModelView();
    return ModelView();
}
Transform3D& GameEngine::ApplyBeforeProjection( const Transform3D& ac_roMatrix )
{
    Projection() = ac_roMatrix * Projection();
    return Projection();
}
void GameEngine::ClearModelView()
{
    while( !Instance().m_poModelView->empty() )
    {
        Instance().m_poModelView->pop();
    }
}
void GameEngine::ClearProjection()
{
    while( !Instance().m_poProjection->empty() )
    {
        Instance().m_poProjection->pop();
    }
}
Transform3D GameEngine::PopModelView()  // returns copy of now-removed top matrix
{
    Transform3D oCopy( ModelView() );
    Instance().m_poModelView->pop();
    return oCopy;
}
Transform3D GameEngine::PopProjection()  // returns copy of now-removed top matrix
{
    Transform3D oCopy( Projection() );
    Instance().m_poProjection->pop();
    return oCopy;
}
Transform3D& GameEngine::PushModelView( const Transform3D& ac_roMatrix )
{
    Instance().m_poModelView->push( ac_roMatrix );
    return ModelView();
}
Transform3D& GameEngine::PushProjection( const Transform3D& ac_roMatrix )
{
    Instance().m_poProjection->push( ac_roMatrix );
    return Projection();
}

// Return a reference to the current game state
GameState& GameEngine::CurrentState()
{
    if( States().empty() || nullptr == States().top() )
    {
        return GameState::End();
    }
    return *( States().top() );
}

// Initialize the game engine
bool GameEngine::Initialize( const IntPoint2D& ac_roSize,
                             const char* ac_pcTitle,
                             const ColorVector& ac_roColor )
{
    if( !IsInitialized() )
    {
        // Initialize GLFW
        glfwSetErrorCallback( PrintError );
        Instance().m_bInitialized = ( GL_TRUE == glfwInit() );
        
        // If GLFW failed to initialize, just return false
        if( !IsInitialized() )
        {
            return false;
        }

        // Otherwise, attempt to create an OpenGL context and call glewInit()
        Mouse::Initialize();
        Keyboard::Initialize();
        MainWindow().SetClearColor( ac_roColor );
        MainWindow().SetSize( ac_roSize );
        MainWindow().SetTitle( ac_pcTitle );
        MainWindow().MakeCurrent();
        glewExperimental = GL_TRUE;
        Instance().m_bInitialized = ( MainWindow().IsCurrent() &&
                                      GLEW_OK == glewInit() );

        // If context and GLEW initialization succeeded, initialize the rest
        if( IsInitialized() )
        {
            glEnable (GL_BLEND);
            glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            QuadShaderProgram::Initialize();
            SpriteShaderProgram::Initialize();
            Instance().m_dLastTime = Time();
        }
        else    // otherwise, terminate GLFW
        {
            GameWindow::DestroyAll();
            glfwTerminate();
        }

    }   // if( !IsInitialized() )
    return IsInitialized();
}
bool GameEngine::Initialize( unsigned int a_uiWidth, unsigned int a_uiHeight,
                             const char* ac_pcTitle,
                             const ColorVector& ac_roColor )
{
    return Initialize( IntPoint2D( a_uiWidth, a_uiHeight ),
                       ac_pcTitle, ac_roColor );
}

// Remove states
void GameEngine::PopState()
{
    if( !States().empty() )
    {
        CurrentState().OnExit();
        States().pop();
        CurrentState().OnResume();
    }
}
void GameEngine::ClearStates()
{
    while( !States().empty() )
    {
        CurrentState().OnExit();
        States().pop();
    }
}

// Print error messages to standard error stream.
void GameEngine::PrintError( int a_iCode, const char* ac_pcDescription )
{
    std::cerr << "ERROR " << a_iCode << ": " << ac_pcDescription << std::endl;
}
void GameEngine::PrintError( const char* ac_pcDescription )
{
    std::cerr << "ERROR: " << ac_pcDescription << std::endl;
}

// Add a state to the stack, above the current stack
GameState& GameEngine::PushState( GameState& a_roState )
{
    CurrentState().OnSuspend();
    States().push( &a_roState );
    CurrentState().OnEnter();
    return CurrentState();
}

// Add a state to the stack, replacing the current stack
GameState& GameEngine::ReplaceCurrentState( GameState& a_roState )
{
    if( !States().empty() )
    {
        CurrentState().OnExit();
        States().pop();
    }
    States().push( &a_roState );
    CurrentState().OnEnter();
    return CurrentState();
}

// Run the game.  This function won't return until the current state is
// GameState::End().
void GameEngine::Run()
{
    if( !IsInitialized() )
    {
        throw std::runtime_error( "Game engine not initialized" );
    }
    while( GameState::End() != CurrentState() )
    {
        Instance().DeltaTime();
        glfwPollEvents();
        if( GameState::End() == CurrentState() ) { break; }
        CurrentState().OnUpdate( LastDeltaTime() );
        if( GameState::End() == CurrentState() ) { break; }
        glfwPollEvents();   // in case OnUpdate triggered anything
        if( GameState::End() == CurrentState() ) { break; }
        Camera::Refresh();
        CurrentState().Draw();
    }
}

// Terminate the game engine
void GameEngine::Terminate()
{
    if( IsInitialized() )
    {
        SpriteShaderProgram::Terminate();
        QuadShaderProgram::Terminate();
        Texture::DestroyAll();
        ShaderProgram::DestroyAll();
        Shader::DestroyAll();
        GameWindow::DestroyAll();
        Keyboard::Terminate();
        Mouse::Terminate();
        glfwTerminate();
        Instance().m_bInitialized = false;
    }
}

// Time since initialization
double GameEngine::Time()
{
    return IsInitialized() ? glfwGetTime() : 0.0;
}

}   // namespace MyFirstEngine
