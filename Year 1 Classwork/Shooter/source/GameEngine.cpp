/******************************************************************************
 * File:               GameEngine.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       October 29, 2013
 * Description:        Implementation for non-inlined GameEngine functions.
 * Last Modified:      October 29, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#include "GameEngine.h"
#include <stack>

// instantiate static stack
std::stack< GameState* > GameEngine::sm_oStates = std::stack< GameState* >();

// Set up window, load things, etc.
void GameEngine::Initialize( const char* ac_pcWindowTitle,
                             const IntXY& ac_roScreenSize, bool a_bFullscreen )
{
    // TODO
}

// Cleanup tasks
void GameEngine::Shutdown()
{
    // Exit any remaining states, in case there are any left.
    ClearStates();

    // TODO
}