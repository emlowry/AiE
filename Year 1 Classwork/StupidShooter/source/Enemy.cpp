/******************************************************************************
 * File:               Enemy.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       November 13, 2013
 * Description:        Class for handling enemies.
 * Last Modified:      November 13, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#include "Enemy.h"

const char* const Enemy::ENEMY_FILE = "./images/enemy.png";
const IntXY Enemy::ENEMY_SIZE( 70, 70 );
const IntXY Enemy::ENEMY_VELOCITY( -400, 0 );
const IntXY Enemy::SCREEN_SIZE( 1280, 720 );

std::set<Enemy*> Enemy::sm_oLive = std::set<Enemy*>();
std::set<Enemy*> Enemy::sm_oDead = std::set<Enemy*>();

// insert new bullets into live list
Enemy::Enemy( const IntXY& ac_roPosition )
    : Sprite( ENEMY_FILE, ENEMY_SIZE, ac_roPosition )
{
    sm_oLive.insert( this );
}

// Destructor deallocates all bullets
Enemy::~Enemy()
{
    Enemy* poEnemy;
    while( !sm_oLive.empty() )
    {
        poEnemy = *(sm_oLive.begin());
        sm_oLive.erase(sm_oLive.begin());
        delete poEnemy;
    }
    while( !sm_oDead.empty() )
    {
        poEnemy = *(sm_oDead.begin());
        sm_oDead.erase(sm_oDead.begin());
        delete poEnemy;
    }
}

// recycle a dead bullet if available, otherwise make a new one
void Enemy::Deploy()
{
    IntXY oPosition( 1280, ( rand() % 660 ) + 30 );
    if( sm_oDead.empty() )
    {
        new Enemy( oPosition );
    }
    else
    {
        Enemy* poEnemy = *(sm_oDead.begin());
        poEnemy->Spawn( oPosition );
    }
}

// static functions
std::set< Enemy* > Enemy::GetLive()
{
    return sm_oLive;
}
void Enemy::UpdateAll( const float ac_fDeltaT )
{
    for each( Enemy* poEnemy in sm_oLive )
    {
        poEnemy->Update( ac_fDeltaT );
    }
}
void Enemy::DrawAll()
{
    for each( Enemy* poEnemy in sm_oLive )
    {
        poEnemy->Draw();
    }
}

// move enemy, die if out of bounds
void Enemy::Update( const float ac_fDeltaT )
{
    m_oPosition.x += ENEMY_VELOCITY.x * ac_fDeltaT;
    m_oPosition.y += ENEMY_VELOCITY.y * ac_fDeltaT;

    if( m_oPosition.x < 0 || m_oPosition.x > SCREEN_SIZE.x ||
        m_oPosition.y < 0 || m_oPosition.y > SCREEN_SIZE.y )
    {
        Die();
    }
}

// recycle enemies
void Enemy::Die()
{
    sm_oLive.erase( this );
    sm_oDead.insert( this );
}
void Enemy::Spawn( const IntXY& ac_roPosition )
{
    sm_oDead.erase( this );
    m_oPosition = ac_roPosition;
    sm_oLive.insert( this );
}