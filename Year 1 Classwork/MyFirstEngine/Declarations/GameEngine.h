/******************************************************************************
 * File:               GameEngine.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 5, 2014
 * Description:        Singleton class representing the game engine as a whole.
 * Last Modified:      February 25, 2014
 * Last Modification:  Adding a main window for the game engine.
 ******************************************************************************/

#ifndef GAME_ENGINE__H
#define GAME_ENGINE__H

#include "GameWindow.h"
#include "MathLibrary.h"
#include <stack>

#include "MyFirstEngineMacros.h"

namespace MyFirstEngine
{

using namespace Utility;

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
    static bool Initialize( const IntPoint2D& ac_roSize = IntPoint2D( 800, 600 ),
                            const char* ac_pcTitle = "",
                            const ColorVector& ac_roColor = Color::BLACK );
    static bool Initialize( unsigned int a_uiWidth, unsigned int a_uiHeight,
                            const char* ac_pcTitle = "",
                            const ColorVector& ac_roColor = Color::BLACK );
    static bool IsInitialized() { return Instance().m_bInitialized; }
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

    // Get the main game window
    static GameWindow& MainWindow() { return Instance().m_oMainWindow; }

private:

    // PIMPLE idiom - this class is only defined in the cpp, so inheritance from
    // an stl container won't result in warnings.
    class StateStack;

    // Default constructor is only used by the base Singleton class's Instance()
    // function.  The user never instantiates a GameEngine object directly.
    GameEngine();

    // Returns the time since this function was last called.
    double DeltaTime();

    // get a reference to a static stack object, the top of which contains the
    // current state.
    static StateStack& States() { return *( Instance().m_poStates ); }

    // Is the engine initialized?
    bool m_bInitialized;

    // result of previous DeltaTime() call
    double m_dLastDeltaTime;

    // time of previous DeltaTime() call
    double m_dLastTime;

    // store a stack of state objects, the top of which is the current state
    // the stack is hidden in a struct to avaoid a compiler warning
    StateStack* m_poStates;

    // Main game window
    GameWindow m_oMainWindow;

};  // class GameEngine

}   // namespace MyFirstEngine

#include "GameState.h"

#endif  // GAME_ENGINE__H