/******************************************************************************
 * File:               Play.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       November 13, 2013
 * Description:        Play state function implementation.
 * Last Modified:      November 13, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#include "GameEngine.h"
#include "Play.h"

Play::Play()
    : m_poPlayer( nullptr ), m_poBackground( nullptr ), m_uiPoints( 0 ), m_uiLives( 3 ) {}
Play::~Play()
{
    if( nullptr != m_poPlayer )
    {
        delete m_poPlayer;
        m_poPlayer = nullptr;
    }
    if( nullptr != m_poBackground )
    {
        delete m_poBackground;
        m_poBackground = nullptr;
    }
}

void Play::Draw() const
{
    m_poBackground->Draw();

    // TODO: draw bullets
    // TODO: draw enemies

    m_poPlayer->Draw();
}

void Play::HandleInput()
{
    m_poPlayer->HandleInput();
}

void Play::LoadState()
{
    sm_oInstance.Load();
}

void Play::Load()
{
    m_poPlayer = new Player();
    m_poBackground = new Sprite( "images/background.png", IntXY( 1280, 720 ), IntXY( 640, 360 ) );
}

void Play::OnEnter()
{
    // if the main menu was implemented, this is where you'd reset the score and lives
}

void Play::Update()
{
    // TODO update bullets
    // TODO update enemies
    // TODO check for collisions

    if( m_uiLives == 0 )
    {
        GameEngine::SetState( GameState::END );
    }
}
