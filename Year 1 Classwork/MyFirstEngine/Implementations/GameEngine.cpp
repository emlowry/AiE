/******************************************************************************
 * File:               GameEngine.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       February 5, 2014
 * Description:        Implementations of GameEngine functions.
 * Last Modified:      February 27, 2014
 * Last Modification:  Refactoring.
 ******************************************************************************/

#include "..\Declarations\GameEngine.h"
#include "..\Declarations\GameState.h"
#include "..\Declarations\GameWindow.h"
#include "..\Declarations\GLFW.h"
#include "..\Declarations\Quad.h"
#include "..\Declarations\Shader.h"
#include "..\Declarations\ShaderProgram.h"
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

// Default constructor is only used by the base Singleton class's Instance()
// function.  The user never instantiates a GameEngine object directly.
GameEngine::GameEngine()
    : m_bInitialized( false ), m_dLastTime( 0.0 ),
      m_poStates( new StateStack ) {}

// Destructor is virtual, since inheritance is involved.
GameEngine::~GameEngine()
{
    delete m_poStates;
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
            QuadShaderProgram::Initialize();
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
    while( GameState::End() != CurrentState() )
    {
        CurrentState().OnUpdate( Instance().DeltaTime() );
        glfwPollEvents();
        CurrentState().Draw();
    }
}

// Terminate the game engine
void GameEngine::Terminate()
{
    if( IsInitialized() )
    {
        QuadShaderProgram::Terminate();
        ShaderProgram::DestroyAll();
        Shader::DestroyAll();
        GameWindow::DestroyAll();
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