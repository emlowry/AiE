/******************************************************************************
 * File:               GameEngine.inl
 * Author:             Elizabeth Lowry
 * Date Created:       February 5, 2014
 * Description:        Inline implementations of GameEngine functions.
 * Last Modified:      February 11, 2014
 * Last Modification:  Adding GameState.
 ******************************************************************************/

#ifndef GAME_ENGINE__INL
#define GAME_ENGINE__INL

#include "..\Declarations\GameEngine.h"
#include "..\Declarations\GameState.h"
#include "..\Declarations\GameWindow.h"
#include "..\Declarations\GLFW.h"
#include "..\Declarations\MyFirstEngineMacros.h"
#include <iostream>

namespace MyFirstEngine
{

// Destructor doesn't need to do anything
INLINE GameEngine::~GameEngine() {}

// Private default constructor called only to initialize singleton
INLINE GameEngine::GameEngine() : m_bInitialized( false ), m_dLastTime( 0.0 ) {}

// Returns the time since this function was last called.
INLINE double GameEngine::DeltaTime()
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
INLINE GameState& GameEngine::CurrentState()
{
    if( States().empty() || nullptr == States().top() )
    {
        return GameState::End();
    }
    return *( States().top() );
}

// Initialize the game engine
INLINE bool GameEngine::Initialize()
{
    if( !IsInitialized() )
    {
        glfwSetErrorCallback( PrintError );
        Instance().m_bInitialized = ( GL_TRUE == glfwInit() );
        Instance().m_dLastTime = Time();
    }
    return IsInitialized();
}
INLINE bool GameEngine::IsInitialized()
{
    return Instance().m_bInitialized;
}

// Remove states
INLINE void GameEngine::PopState()
{
    if( !States().empty() )
    {
        CurrentState().OnExit();
        States().pop();
        CurrentState().OnResume();
    }
}
INLINE void GameEngine::ClearStates()
{
    while( !States().empty() )
    {
        CurrentState().OnExit();
        States().pop();
    }
}

// Print error messages to standard error stream.
INLINE void GameEngine::PrintError( int a_iCode, const char* ac_pcDescription )
{
    std::cerr << "ERROR " << a_iCode << ": " << ac_pcDescription << std::endl;
}
INLINE void GameEngine::PrintError( const char* ac_pcDescription )
{
    std::cerr << "ERROR: " << ac_pcDescription << std::endl;
}

// Add a state to the stack, above the current stack
INLINE GameState& GameEngine::PushState( GameState& a_roState )
{
    CurrentState().OnSuspend();
    States().push( &a_roState );
    CurrentState().OnEnter();
    return CurrentState();
}

// Add a state to the stack, replacing the current stack
INLINE GameState& GameEngine::ReplaceCurrentState( GameState& a_roState )
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

// get a reference to a static stack object, the top of which contains the
// current state.
INLINE GameEngine::StateStack& GameEngine::States()
{
    return Instance().m_oStates.stack;
}

// Run the game.  This function won't return until the current state is
// GameState::End().
INLINE void GameEngine::Run()
{
    while( GameState::End() != CurrentState() )
    {
        CurrentState().OnUpdate( Instance().DeltaTime() );
        glfwPollEvents();
        CurrentState().Draw();
    }
}

// Terminate the game engine
INLINE void GameEngine::Terminate()
{
    if( IsInitialized() )
    {
        GameWindow::DestroyAll();
        glfwTerminate();
        Instance().m_bInitialized = false;
    }
}

// Time since initialization
INLINE double GameEngine::Time()
{
    return IsInitialized() ? glfwGetTime() : 0.0;
}

}   // namespace MyFirstEngine

#endif  // GAME_ENGINE__INL