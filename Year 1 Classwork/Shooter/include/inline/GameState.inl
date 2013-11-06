/******************************************************************************
 * File:               GameState.inl
 * Author:             Elizabeth Lowry
 * Date Created:       November 5, 2013
 * Description:        Inline function implementations for GameState.h.
 * Last Modified:      November 5, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef _GAME_STATE_INL_
#define _GAME_STATE_INL_

#include "EventHandler.h"

// State that shuts down the game
GameState* const GameState::END = nullptr;

// Base class defines the call - handle events, then update components and draw.
inline void GameState::operator()()
{
    EventHandler::Run();
    Update();
    Draw();
}

// Attempting to clone a singleton only returns a pointer to the singleton.
// That said, you should never ever have a pointer to the singleton itself, only
// to a disposable caller object - otherwise, some idiot might try to deallocate
// the singleton instance.
template< typename Derived >
inline GameState::Singleton< Derived >*
    GameState::Singleton< Derived >::Clone() const
{
    return const_cast< GameState::Singleton< Derived >* >( this );
}

// The singleton wrapper can be cloned normally
template< typename Derived >
inline typename GameState::Singleton< Derived >::Caller*
    GameState::Singleton< Derived >::Caller::Clone() const
{
    return new Caller();
}

// Singleton wrapper calls on wrapped singleton
template< typename Derived >
void GameState::Singleton< Derived >::Caller::Update()
{
    sm_oInstance.Update();
}
template< typename Derived >
void GameState::Singleton< Derived >::Caller::Draw() const
{
    sm_oInstance.Draw();
}

#endif  // _GAME_STATE_INL_
