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

#include "Declarations\GameEngine.h"
#include "Declarations\GameState.h"
#include "Declarations\GameWindow.h"
#include "Declarations\GLFW.h"
#include "Declarations\MyFirstEngineMacros.h"
#include <iostream>

namespace MyFirstEngine
{

// Destructor doesn't need to do anything
INLINE GameEngine::~GameEngine() {}

// Private default constructor called only to initialize singleton
INLINE GameEngine::GameEngine() : m_bInitialized( false ) {}

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
        // TODO call other initialization/initialization failure functions
    }
    return IsInitialized();
}
INLINE bool GameEngine::IsInitialized() { return Instance().m_bInitialized; }

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

// Run the game.  This function won't return until the current state is
// GameState::End().
INLINE void GameEngine::Run()
{
    while( GameState::End() != CurrentState() )
    {
        CurrentState().OnUpdate();
        glfwWaitEvents();
    }
}

// get a reference to a static stack object, the top of which contains the
// current state.
INLINE GameEngine::StateStack& GameEngine::States()
{
    static StateStack s_oStates;
    return s_oStates;
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

}   // namespace MyFirstEngine

#endif  // GAME_ENGINE__INL