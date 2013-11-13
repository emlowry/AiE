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

//#include "EventHandler.h"

// Base class defines the call - handle events, then update components and draw.
inline void GameState::operator()()
{
    //EventHandler::Run();
    Update();
    Draw();
}

// Instantiate singleton and singleton caller instances
template< typename Derived >
Derived GameState::Singleton< Derived >::sm_oInstance = Derived();
template< typename Derived >
const typename GameState::Singleton< Derived >::Caller
    GameState::Singleton< Derived >::State =
        GameState::Singleton< Derived >::Caller();

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

// The singleton caller can be cloned normally
template< typename Derived >
inline typename GameState::Singleton< Derived >::Caller*
    GameState::Singleton< Derived >::Caller::Clone() const
{
    return new Caller();
}

// Singleton caller calls on singleton
template< typename Derived >
inline void GameState::Singleton< Derived >::Caller::Draw() const
{
    sm_oInstance.Draw();
}
template< typename Derived >
inline void GameState::Singleton< Derived >::Caller::HandleInput()
{
    sm_oInstance.HandleInput();
}
template< typename Derived >
inline void GameState::Singleton< Derived >::Caller::OnEnter()
{
    sm_oInstance.OnEnter();
}
template< typename Derived >
inline void GameState::Singleton< Derived >::Caller::OnExit()
{
    sm_oInstance.OnExit();
}
template< typename Derived >
inline void GameState::Singleton< Derived >::Caller::OnResume()
{
    sm_oInstance.OnResume();
}
template< typename Derived >
inline void GameState::Singleton< Derived >::Caller::OnSuspend()
{
    sm_oInstance.OnSuspend();
}
template< typename Derived >
inline void GameState::Singleton< Derived >::Caller::Update()
{
    sm_oInstance.Update();
}

#endif  // _GAME_STATE_INL_
