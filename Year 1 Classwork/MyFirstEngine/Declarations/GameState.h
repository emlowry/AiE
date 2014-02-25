/******************************************************************************
 * File:               GameState.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 11, 2014
 * Description:        Class representing a game state (load, menu, play, etc).
 * Last Modified:      February 24, 2014
 * Last Modification:  Moved base classes to Utility namespace in MathLibrary.
 ******************************************************************************/

#ifndef GAME_STATE__H
#define GAME_STATE__H

#include "GameEngine.h"
#include "GameWindow.h"
#include "MathLibrary.h"

#include "MyFirstEngineMacros.h"

namespace MyFirstEngine
{

using namespace Utility;

// Represents a state in the game, such as showing the splash screen or the menu
// or actually playing the game.
class IMEXPORT_CLASS GameState : public NotCopyable, public MostDerivedAddress
{
    // these classes are the only ones to call the protected event handlers
    friend class GameEngine;
    friend class GameWindow;

public:

    // (In)Equality checks are identity checks
    virtual bool operator==( const GameState& ac_roState ) const
    { return Address() == ac_roState.Address(); }
    virtual bool operator!=( const GameState& ac_roState ) const
    { return Address() != ac_roState.Address(); }

    // Draw to the screen after each update.  Don't update anything - that's for
    // OnUpdate and other event handlers.  Default behavior is to swap frame
    // buffers for all windows.  If you actually draw things, remember to call
    // ShaderProgram::Stop() when finished.
    virtual void Draw() const { GameWindow::SwapAllBuffers(); }

    // Return a reference to the current game state
    bool IsCurrent() const { return GameEngine::CurrentState() == *this; }

    // Add a state to the stack, above the current stack
    GameState& Push() { return GameEngine::PushState( *this ); }

    // Add a state to the stack, replacing the current stack
    GameState& ReplaceCurrent()
    { return GameEngine::ReplaceCurrentState( *this ); }

    // Return a reference to a special game state representing no state
    static GameState& End();

protected:

    // Constructor/destructor are protected so you can't just instantiate a
    // default GameState object.  What would be the point?  This is a base class
    // - users should implement derived classes that actually do something.
    GameState() {}
    virtual ~GameState() {}

    // These functions are called in response to different events.  For
    // non-default behavior, redefine these in child classes.

    // Called by GameWindow::OnCloseWindow when a window's close button is
    // pressed.  Unless your derived class redefines this, the default behavior
    // is to clear out all the game states if any window is closed.
    virtual void OnCloseWindow( GameWindow& a_roWindow )
    { GameEngine::ClearStates(); }

    // Called by GameEngine::Run() before calling on GLFW to update.  Default
    // behavior is to do nothing.
    virtual void OnUpdate( double a_dDeltaTime ) {}

    // Called by Clear, Pop, Push, and ReplaceCurrent as states are added to,
    // removed from, or covered or uncovered on the stack.  Default behavior is
    // to do nothing.
    virtual void OnEnter() {}   // When added to the stack
    virtual void OnSuspend() {} // When another state is pushed on top of this
    virtual void OnResume() {}  // When a pop uncovers this as the new current
    virtual void OnExit() {}    // When removed from the stack

private:

    // special gamestate type representing no state
    class EndState;

};  // class GameState

// special gamestate type representing no state
class IMEXPORT_CLASS GameState::EndState
    : public GameState, public Singleton< EndState >
{
    friend class Singleton< EndState >;
public:
    virtual ~EndState() {}
private:
    EndState() {}
};

// Return a reference to a special game state representing no state
inline GameState& GameState::End() { return EndState::Instance(); }

}   // namespace MyFirstEngine

#endif  // GAME_STATE__H
