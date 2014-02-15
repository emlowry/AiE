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

    // State management
    static GameState& CurrentState();
    static void PopState();
    static void ClearStates();
    static GameState& PushState( GameState& a_roState );
    static GameState& ReplaceCurrentState( GameState& a_roState );

    // Print error messages to standard error stream.
    static void PrintError( int a_iCode, const char* ac_pcDescription );
    static void PrintError( const char* ac_pcDescription );

    // Run the game.  This function won't return until the current state is
    // GameState::End().
    static void Run();

    // Time-related functions
    static double Time();   // time since initialization
    static double LastDeltaTime() { return Instance().m_dLastDeltaTime; }
    static double LastTime() { return Instance().m_dLastTime; }

private:

    // prevent typing errors
    typedef std::stack< GameState* > StateStack;

    // Default constructor is only used by the base Singleton class's Instance()
    // function.  The user never instantiates a GameEngine object directly.
    GameEngine();

    // Returns the time since this function was last called.
    double DeltaTime();

    // get a reference to a static stack object, the top of which contains the
    // current state.
    static StateStack& States();

    // Is the engine initialized?
    bool m_bInitialized;

    // result of previous DeltaTime() call
    double m_dLastDeltaTime;

    // time of previous DeltaTime() call
    double m_dLastTime;

    // store a stack of state objects, the top of which is the current state
    // the stack is hidden in a struct to avaoid a compiler warning
    struct
    {
        StateStack stack;
    } m_oStates;

};  // class GameEngine

}   // namespace MyFirstEngine

#include "Declarations\GameState.h"
#ifdef INLINE_IMPLEMENTATION
#include "..\Implementations\GameEngine.inl"
#endif;

#endif  // GAME_ENGINE__H