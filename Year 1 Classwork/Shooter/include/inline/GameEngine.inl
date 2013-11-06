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

// Get the current state
inline GameState* GameEngine::GetState()
{
    return sm_oStates.empty() ? GameState::END : sm_oStates.top();
}

// Remove the topmost state from the stack
inline void GameEngine::PopState()
{
    sm_oStates.pop();
}

// Add the given state to the top of the stack
inline void GameEngine::PushState( const GameState&& ac_rroState )
{
    sm_oStates.push( ac_rroState.Clone() );
}
inline void GameEngine::PushState( const GameState* const ac_cpoState )
{
    sm_oStates.push( ac_cpoState->Clone() );
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
    while( !sm_oStates.empty() )
    {
        sm_oStates.pop();
    }
    sm_oStates.push( ac_rroState.Clone() );
}
inline void GameEngine::SetState( const GameState* const ac_cpoState )
{
    while( !sm_oStates.empty() )
    {
        sm_oStates.pop();
    }
    sm_oStates.push( ac_cpoState->Clone() );
}

#endif  // _GAME_ENGINE_INL_
