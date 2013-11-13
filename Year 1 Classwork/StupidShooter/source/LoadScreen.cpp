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
#include "Play.h"
#include "Sprite.h"

const char* const LoadScreen::SPLASH_FILE = "./images/splash.png";
const IntXY LoadScreen::SCREEN_SIZE( 1280, 720 );
const IntXY LoadScreen::SCREEN_CENTER( 640, 360 );

LoadScreen::LoadScreen()
    : m_bLoadingComplete( false ), m_bSplashDrawn( false ), m_poSplashScreen( nullptr ) {}

LoadScreen::~LoadScreen()
{
    if( nullptr != m_poSplashScreen )
    {
        delete m_poSplashScreen;
        m_poSplashScreen = nullptr;
    }
}

void LoadScreen::Draw() const
{
    if( m_poSplashScreen != nullptr )
    {
        ClearScreen();
        m_poSplashScreen->Draw();
    }
}

bool LoadScreen::IsFinished()
{
    return ( m_bSplashDrawn && m_bLoadingComplete &&
             (unsigned int)m_oLoadTime.GetSeconds() > MIN_LOAD_SECONDS );
}

void LoadScreen::Load()
{
    Play::LoadState();
    // TODO Load art for other game states

    m_bLoadingComplete = true;
}

// Start timer
void LoadScreen::OnEnter()
{
    m_oLoadTime.Start();
}

void LoadScreen::WhenFinished()
{
    GameEngine::SetState(Play::State);//MainMenu::State
}

void LoadScreen::Update()
{
    if( !m_bSplashDrawn )
    {
        m_poSplashScreen = new Sprite( SPLASH_FILE, SCREEN_SIZE, SCREEN_CENTER );
        m_bSplashDrawn = true;
        return;
    }

    if( !m_bLoadingComplete )
    {
        Load();
        return;
    }

    if( IsFinished() )
    {
        WhenFinished();
    }
}
