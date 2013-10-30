/******************************************************************************
 * File:               LoadScreen.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       October 29, 2013
 * Description:        Implementation for LoadScreen functions.
 * Last Modified:      October 29, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#include "GameEngine.h"
#include "GameState.h"
#include "LoadScreen.h"

// Start timer
LoadScreen::LoadScreen()
{
    m_oLoadTime.Start();
}

void LoadScreen::Draw() const
{
    // TODO
}

inline bool LoadScreen::IsFinished()
{
    return ( (unsigned int)m_oLoadTime.GetSeconds() < MIN_LOAD_SECONDS );
}

void LoadScreen::WhenFinished()
{
    GameEngine::SetState(GameState::END);//MainMenu::State
}

void LoadScreen::Update()
{
    // TODO
}
