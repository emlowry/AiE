/******************************************************************************
 * File:               Bullet.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       November 13, 2013
 * Description:        Class for handling bullets fired by the player.
 * Last Modified:      November 13, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#include "Bullet.h"

const char* const Bullet::BULLET_FILE = "./images/bullet.png";
const IntXY Bullet::BULLET_SIZE( 15, 15 );
const IntXY Bullet::BULLET_VELOCITY( 400, 0 );
const IntXY Bullet::SCREEN_SIZE( 1280, 720 );

std::set<Bullet*> Bullet::sm_oLive = std::set<Bullet*>();
std::set<Bullet*> Bullet::sm_oDead = std::set<Bullet*>();

// insert new bullets into live list
Bullet::Bullet( const IntXY& ac_roPosition )
    : Sprite( BULLET_FILE, BULLET_SIZE, ac_roPosition )
{
    sm_oLive.insert( this );
}

// Destructor deallocates all bullets
Bullet::~Bullet()
{
    Bullet* poBullet;
    while( !sm_oLive.empty() )
    {
        poBullet = *(sm_oLive.begin());
        sm_oLive.erase(sm_oLive.begin());
        delete poBullet;
    }
    while( !sm_oDead.empty() )
    {
        poBullet = *(sm_oDead.begin());
        sm_oDead.erase(sm_oDead.begin());
        delete poBullet;
    }
}

// recycle a dead bullet if available, otherwise make a new one
void Bullet::Fire( const IntXY& ac_roPosition )
{
    if( sm_oDead.empty() )
    {
        new Bullet( ac_roPosition );
    }
    else
    {
        Bullet* poBullet = *(sm_oDead.begin());
        poBullet->Spawn( ac_roPosition );
    }
}

// static functions
std::set< Bullet* > Bullet::GetLive()
{
    return sm_oLive;
}
void Bullet::UpdateAll( const float ac_fDeltaT )
{
    std::set<Bullet*> oBullets = sm_oLive;
    for each( Bullet* poBullet in oBullets )
    {
        poBullet->Update( ac_fDeltaT );
    }
}
void Bullet::DrawAll()
{
    for each( Bullet* poBullet in sm_oLive )
    {
        poBullet->Draw();
    }
}

// move bullet, die if out of bounds
void Bullet::Update( const float ac_fDeltaT )
{
    m_oPosition.x += BULLET_VELOCITY.x * ac_fDeltaT;
    m_oPosition.y += BULLET_VELOCITY.y * ac_fDeltaT;

    if( m_oPosition.x < 0 || m_oPosition.x > SCREEN_SIZE.x ||
        m_oPosition.y < 0 || m_oPosition.y > SCREEN_SIZE.y )
    {
        Die();
    }
}

// recycle bullets
void Bullet::Die()
{
    sm_oLive.erase( this );
    sm_oDead.insert( this );
}
void Bullet::Spawn( const IntXY& ac_roPosition )
{
    sm_oDead.erase( this );
    m_oPosition = ac_roPosition;
    sm_oLive.insert( this );
}