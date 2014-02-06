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

    // Initialization and termination
    static bool Initialize();   // returns true if initialization was successful
    static bool IsInitialized();
    static void Terminate();

private:

    GameEngine();
    GameEngine( const GameEngine& ac_roToCopy );
    GameEngine& operator=( const GameEngine& ac_roToCopy );

    // Is the engine initialized?
    bool m_bInitialized;

};  // class GameEngine

}   // namespace MyFirstEngine

#ifdef INLINE_IMPLEMENTATION
#include "Implementations\GameEngine.inl"
#endif;

#endif  // GAME_ENGINE__H