/******************************************************************************
 * File:               GameState.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 11, 2014
 * Description:        Class representing a game state (load, menu, play, etc).
 * Last Modified:      February 11, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef GAME_STATE__H
#define GAME_STATE__H

#include "MathLibrary.h"
#include "NotCopyable.h"
#include "Singleton.h"

#include "MyFirstEngineMacros.h"

namespace MyFirstEngine
{

// Forward declare GameEngine and GameWindow
class GameEngine;
class GameWindow;

// Represents a state in the game, such as showing the splash screen or the menu
// or actually playing the game.
class IMEXPORT_CLASS GameState : public NotCopyable, public MostDerivedAddress
{
    // these classes are the only ones to call the protected event handlers
    friend class GameEngine;
    friend class GameWindow;

public:

    // (In)Equality checks are identity checks
    virtual bool operator==( const GameState& ac_roState ) const;
    virtual bool operator!=( const GameState& ac_roState ) const;

    // Draw to the screen after each update.  Don't update anything - that's for
    // OnUpdate and other event handlers.  Default behavior is to swap frame
    // buffers for all windows.
    virtual void Draw() const;

    // Return a reference to the current game state
    bool IsCurrent() const;

    // Add a state to the stack, above the current stack
    GameState& Push();

    // Add a state to the stack, replacing the current stack
    GameState& ReplaceCurrent();

    // Return a reference to a special game state representing no state
    static GameState& End();

protected:

    // Constructor/destructor are protected so you can't just instantiate a
    // default GameState object.  What would be the point?  This is a base class
    // - users should implement derived classes that actually do something.
    GameState();
    virtual ~GameState();

    // These functions are called in response to different events.  For
    // non-default behavior, redefine these in child classes.

    // Called by GameWindow::OnCloseWindow when a window's close button is
    // pressed.  Unless your derived class redefines this, the default behavior
    // is to clear out all the game states if any window is closed.
    virtual void OnCloseWindow( GameWindow& a_roWindow );

    // Called by GameEngine::Run() before calling on GLFW to update.  Default
    // behavior is to do nothing.
    virtual void OnUpdate( double a_dDeltaTime );

    // Called by Clear, Pop, Push, and ReplaceCurrent as states are added to,
    // removed from, or covered or uncovered on the stack.  Default behavior is
    // to do nothing.
    virtual void OnEnter();  // When added to the stack
    virtual void OnSuspend();// When another state is pushed on top of this
    virtual void OnResume(); // When a pop uncovers this as the new current
    virtual void OnExit();   // When removed from the stack

};  // class GameState

}   // namespace MyFirstEngine

#include "GameEngine.h"
#include "GameWindow.h"
#ifdef INLINE_IMPLEMENTATION
#include "..\Implementations\GameState.inl"
#endif

#endif  // GAME_STATE__H
