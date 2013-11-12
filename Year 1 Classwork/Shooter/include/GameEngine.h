/******************************************************************************
 * File:               GameEngine.h
 * Author:             Elizabeth Lowry
 * Date Created:       October 29, 2013
 * Description:        Manages game states.
 * Last Modified:      October 29, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef _GAME_ENGINE_H_
#define _GAME_ENGINE_H_

#include "GameState.h"
#include "XY.h"
#include <stack>

// manages game states
class GameEngine
{
public:

    // Get the current state
    static GameState* GetState();

    // Remove all states from the stack.  The same effect can be accomplished by
    // setting or pushing GameState::END.
    static void ClearStates();

    // Create window, set initial state, etc.
    static void Initialize( const char* ac_pcWindowTitle = nullptr,
                            const IntXY& ac_roScreenSize = IntXY( 1280, 720 ),
                            bool a_bFullscreen = false );

    // Remove the topmost state from the stack
    static void PopState();

    // Add the given state to the top of the stack
    static void PushState( const GameState&& ac_rroState );
    static void PushState( const GameState* const ac_cpoState );

    // Run the game
    static void Run();

    // Set the given state as the only state
    static void SetState( const GameState&& ac_rroState );
    static void SetState( const GameState* const ac_cpoState );

    // Shut down the game and perform cleanup tasks
    static void Shutdown();

private:

    GameEngine();   // static methods only

    // Call corresponding functions in current state, if there is a current state.
    static void OnEnter();
    static void OnExit();
    static void OnResume();
    static void OnSuspend();

    // Current game state is at the top of the stack
    static std::stack< GameState* > sm_oStates;

};

#include "inline/GameEngine.inl"

#endif  // _GAME_ENGINE_H_