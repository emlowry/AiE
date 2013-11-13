/******************************************************************************
 * File:               GameState.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       November 12, 2013
 * Description:        Instantiation of non-integer static member variable.
 * Last Modified:      November 12, 2013
 * Last Modification:  Moving out of GameState.inl.
 ******************************************************************************/

#include "GameState.h"

// State that shuts down the game
GameState* const GameState::END = nullptr;
