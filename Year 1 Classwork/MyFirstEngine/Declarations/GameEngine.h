/******************************************************************************
 * File:               GameEngine.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 5, 2014
 * Description:        Singleton class representing the game engine as a whole.
 * Last Modified:      February 5, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef GAME_ENGINE__H
#define GAME_ENGINE__H

#include "Declarations\Singleton.h"
#include "Declarations\MyFirstEngineMacros.h"

namespace MyFirstEngine
{

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

private:

    // Default constructor is only used by the base Singleton class's Instance()
    // function.  The user never instantiates a GmaeEngine object directly.
    GameEngine();

    // Print error messages to standard error stream.
    static void PrintError( int a_iCode, const char* ac_pcDescription );

    // Is the engine initialized?
    bool m_bInitialized;

};  // class GameEngine

}   // namespace MyFirstEngine

#ifdef INLINE_IMPLEMENTATION
#include "Implementations\GameEngine.inl"
#endif;

#endif  // GAME_ENGINE__H