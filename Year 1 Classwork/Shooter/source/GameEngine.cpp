/******************************************************************************
 * File:               GameEngine.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       October 29, 2013
 * Description:        Implementation for non-inlined GameEngine functions.
 * Last Modified:      October 29, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#include "AIE.h"
#include "GameEngine.h"
#include "Sprite.h"
#include <stack>

// instantiate static stack
std::stack< GameState* > GameEngine::sm_oStates = std::stack< GameState* >();

// Set up window, load things, etc.
void GameEngine::Initialize( const char* ac_pcWindowTitle,
                             const IntXY& ac_roScreenSize, bool a_bFullscreen )
{
    Initialise( ac_roScreenSize.x, ac_roScreenSize.y, a_bFullscreen, ac_pcWindowTitle );
}

// Cleanup tasks
void GameEngine::Shutdown()
{
    // Exit any remaining states, in case there are any left.
    ClearStates();

    // destroy all sprites
    Sprite::DestroyAll();

    // TODO
}