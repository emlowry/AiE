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
#include <stack>

// manages game states
class GameEngine
{
public:

    // Get the current state
    static GameState* GetState();

    // Create window, set initial state, etc.
    static void Initialize();

    // Remove the topmost state from the stack
    static void PopState();

    // Add the given state to the top of the stack
    static void PushState( GameState* a_poState );

    // Run the game
    static void Run();

    // Set the given state as the only state
    static void SetState( GameState* a_poState );

    // Shut down the game and perform cleanup tasks
    static void Shutdown();

private:

    GameEngine();   // static methods only

    // Current game state is at the top of the stack
    static stack< GameState* > sm_oStates;

};

#include "inline/GameEngine.inl"

#endif  // _GAME_ENGINE_H_