/******************************************************************************
 * File:               Play.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       November 13, 2013
 * Description:        Play state function implementation.
 * Last Modified:      November 13, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#include "Bullet.h"
#include "Enemy.h"
#include "GameEngine.h"
#include "Play.h"

const char* const Play::BACKGROUND_FILE = "./images/background.png";
const IntXY Play::SCREEN_SIZE( 1280, 720 );
const IntXY Play::SCREEN_CENTER( 640, 360 );
const IntXY Play::SHIP_SIZE( 70, 70 );
const char* const Play::STRING_FORMAT = "Lives: %d               Score: %d";
const IntXY Play::STRING_POSITION( 10, 10 );

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
    ClearScreen();
    m_poBackground->Draw();

    Bullet::DrawAll();
    Enemy::DrawAll();

    m_poPlayer->Draw();

    char acBuffer[ STRING_LENGTH ];
    std::sprintf( acBuffer, STRING_FORMAT, m_uiLives, m_uiPoints );
    DrawString( acBuffer, STRING_POSITION.x, STRING_POSITION.y );
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
    m_poBackground = new Sprite( BACKGROUND_FILE, SCREEN_SIZE, SCREEN_CENTER );
}

void Play::OnEnter()
{
    m_oAttackTimer.Start();
    // if the main menu was implemented, this is where you'd reset the score and lives
}

void Play::Update()
{
    float fDeltaT = GetDeltaTime();

    // Update bullets and get list of live ones
    Bullet::UpdateAll(fDeltaT);
    std::set< Bullet* > oBullets = Bullet::GetLive();

    // Update enemies and get list of live ones
    Enemy::UpdateAll(fDeltaT);
    if( m_oAttackTimer.GetMilliseconds() > (double)ATTACK_INTERVAL_MS )
    {
        m_oAttackTimer.Clear();
        Enemy::Deploy();
    }
    std::set<Enemy*> oEnemies = Enemy::GetLive();

    // check for bullets colliding with enemies
    std::set<Enemy*> oKills;
    while( !oBullets.empty() )
    {
        Bullet* poCurrentBullet = *(oBullets.begin());
        for( std::set<Enemy*>::iterator it = oEnemies.begin(); it != oEnemies.end(); ++it )
        {
            if( poCurrentBullet->CollidingWith(**it) )
            {
                poCurrentBullet->Die();
                (*it)->Die();
                oKills.insert(*it);
                oEnemies.erase(*it);
                break;
            }
        }
        oBullets.erase(poCurrentBullet);
    }

    // update score
    m_uiPoints += oKills.size();

    // check for enemies colliding with player
    bool bHit = false;
    while( !oEnemies.empty() )
    {
        Enemy* poCurrentEnemy = *(oEnemies.begin());
        if( poCurrentEnemy->CollidingWith(*m_poPlayer) )
        {
            poCurrentEnemy->Die();
            bHit = true;
        }
        oEnemies.erase( poCurrentEnemy );
    }

    // if player was hit, decrement lives
    if( bHit )
    {
        --m_uiLives;
    }

    // If out of lives, end game
    if( m_uiLives == 0 )
    {
        GameEngine::SetState( GameState::END );//Scores::State );
    }
}
