/******************************************************************************
 * File:               GameEngine.inl
 * Author:             Elizabeth Lowry
 * Date Created:       October 29, 2013
 * Description:        Inline function implementations for GameEngine.h.
 * Last Modified:      October 29, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef _GAME_ENGINE_INL_
#define _GAME_ENGINE_INL_

#include "AIE.h"
#include "GameState.h"

// Remove all states from the stack
inline void GameEngine::ClearStates()
{
    while( !sm_oStates.empty() )
    {
        OnExit();
        sm_oStates.pop();
    }
}

// Get the current state
inline GameState* GameEngine::GetState()
{
    return sm_oStates.empty() ? GameState::END : sm_oStates.top();
}

// Call corresponding functions in current state, if there is a current state
inline void GameEngine::OnEnter()
{
    if( GetState() != GameState::END )
    {
        GetState()->OnEnter();
    }
}
inline void GameEngine::OnExit()
{
    if( GetState() != GameState::END )
    {
        GetState()->OnExit();
    }
}
inline void GameEngine::OnResume()
{
    if( GetState() != GameState::END )
    {
        GetState()->OnResume();
    }
}
inline void GameEngine::OnSuspend()
{
    if( GetState() != GameState::END )
    {
        GetState()->OnSuspend();
    }
}

// Remove the topmost state from the stack
inline void GameEngine::PopState()
{
    OnExit();
    sm_oStates.pop();
    OnResume();
}

// Add the given state to the top of the stack
inline void GameEngine::PushState( const GameState&& ac_rroState )
{
    OnSuspend();
    sm_oStates.push( ac_rroState.Clone() );
    OnEnter();
}
inline void GameEngine::PushState( const GameState* const ac_cpoState )
{
    OnSuspend();
    if( GameState::END != ac_cpoState )
    {
        sm_oStates.push( ac_cpoState->Clone() );
        OnEnter();
    }
}

// Run the game
inline void GameEngine::Run()
{
    while( FrameworkUpdate() && GetState() != GameState::END )
    {
        (*GetState())();
    }
}

// Set the given state as the only state
inline void GameEngine::SetState( const GameState&& ac_rroState )
{
    ClearStates();
    sm_oStates.push( ac_rroState.Clone() );
    OnEnter();
}
inline void GameEngine::SetState( const GameState* const ac_cpoState )
{
    ClearStates();
    if( GameState::END != ac_cpoState )
    {
        sm_oStates.push( ac_cpoState->Clone() );
        OnEnter();
    }
}

#endif  // _GAME_ENGINE_INL_
