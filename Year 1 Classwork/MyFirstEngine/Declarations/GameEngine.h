/******************************************************************************
 * File:               GameEngine.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 5, 2014
 * Description:        Singleton class representing the game engine as a whole.
 * Last Modified:      February 11, 2014
 * Last Modification:  Adding GameState.
 ******************************************************************************/

#ifndef GAME_ENGINE__H
#define GAME_ENGINE__H

#include "Declarations\Singleton.h"
#include <stack>

#include "Declarations\MyFirstEngineMacros.h"

namespace MyFirstEngine
{

// forward declare GameState
class GameState;

// Represents the game engine as a whole - handles intialization, termination,
// state management, etc.
class IMEXPORT_CLASS GameEngine : private Singleton< GameEngine >
{
    friend Singleton< GameEngine >;

public:

    // Destructor is virtual, since inheritance is involved.
    virtual ~GameEngine();

    // Initialization and termination
    static bool Initialize();   // returns true if initialization was successful
    static bool IsInitialized();
    static void Terminate();

    // Return a reference to the current game state
    static GameState& CurrentState();

    // Remove states
    static void PopState();  // remove current
    static void ClearStates();    // remove all

    // Add a state to the stack, above the current stack
    static GameState& PushState( GameState& a_roState );

    // Add a state to the stack, replacing the current stack
    static GameState& ReplaceCurrentState( GameState& a_roState );

    // Run the game.  This function won't return until the current state is
    // GameState::End().
    static void Run();

private:

    // prevent typing errors
    typedef std::stack< GameState* > StateStack;

    // Default constructor is only used by the base Singleton class's Instance()
    // function.  The user never instantiates a GmaeEngine object directly.
    GameEngine();

    // Print error messages to standard error stream.
    static void PrintError( int a_iCode, const char* ac_pcDescription );

    // get a reference to a static stack object, the top of which contains the
    // current state.
    static StateStack& States();

    // Is the engine initialized?
    bool m_bInitialized;

};  // class GameEngine

}   // namespace MyFirstEngine

#include "Declarations\GameState.h"
#ifdef INLINE_IMPLEMENTATION
#include "Implementations\GameEngine.inl"
#endif;

#endif  // GAME_ENGINE__H