/******************************************************************************
 * File:               GameState.inl
 * Author:             Elizabeth Lowry
 * Date Created:       February 11, 2014
 * Description:        Inline implementations for GameState class.
 * Last Modified:      February 11, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef GAME_STATE__INL
#define GAME_STATE__INL

#include "Declarations\GameState.h"
#include "Declarations\GameEngine.h"
#include "Declarations\MyFirstEngineMacros.h"

namespace MyFirstEngine
{

// Constructor/destructor are protected so you can't just instantiate a
// default GameState object.  What would be the point?  This is a base class
// - users should implement derived classes that actually do something.
INLINE GameState::GameState() {}
INLINE GameState::~GameState() {}

// (In)Equality checks are identity checks
INLINE bool GameState::operator==( const GameState& ac_roState ) const
{
    return Address() == ac_roState.Address();
}
INLINE bool GameState::operator!=( const GameState& ac_roState ) const
{
    return Address() != ac_roState.Address();
}

// Draw to the screen after each update.  Don't update anything - that's for
// OnUpdate and other event handlers.  Default behavior is to swap frame buffers
// for all windows.
INLINE void GameState::Draw() const
{
    GameWindow::SwapAllBuffers();
}

// Return a reference to the current game state
INLINE bool GameState::IsCurrent() const
{
    return GameEngine::CurrentState() == *this;
}

// Add a state to the stack, above the current stack
INLINE GameState& GameState::Push()
{
    return GameEngine::PushState( *this );
}

// Add a state to the stack, replacing the current stack
INLINE GameState& GameState::ReplaceCurrent()
{
    return GameEngine::ReplaceCurrentState( *this );
}

// Default event handlers
INLINE void GameState::OnCloseWindow( GameWindow& a_roWindow )
{
    GameEngine::ClearStates();
}
INLINE void GameState::OnUpdate() {}
INLINE void GameState::OnEnter() {}
INLINE void GameState::OnSuspend() {}
INLINE void GameState::OnResume() {}
INLINE void GameState::OnExit() {}

//
// Static functions
//

// special gamestate type representing no state
class IMEXPORT_CLASS EndState : public GameState, public Singleton< EndState >
{
    friend class Singleton< EndState >;
public:
    virtual ~EndState() {}
private:
    EndState() {}
};
INLINE GameState& GameState::End()
{
    return EndState::Instance();
}

}   // namespace MyFirstEngine

#endif  // GAME_STATE__INL
