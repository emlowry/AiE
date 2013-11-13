/******************************************************************************
 * File:               Bullet.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 13, 2013
 * Description:        Class for handling bullets fired by the player.
 * Last Modified:      November 13, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef _BULLET_H_
#define _BULLET_H_

#include "Sprite.h"
#include <set>

class Bullet : public Sprite
{
public:

    Bullet( const IntXY& ac_roPosition );
    virtual ~Bullet();

    static void Fire( const IntXY& ac_roPosition );
    static std::set< Bullet* > GetLive();
    static void UpdateAll( const float ac_fDeltaT );
    static void DrawAll();

    virtual void Update( const float ac_fDeltaT ) override;
    void Die();
    void Spawn( const IntXY& ac_roPosition );

private:

    static std::set< Bullet* > sm_oDead;
    static std::set< Bullet* > sm_oLive;

    static const char* const BULLET_FILE;
    static const IntXY BULLET_SIZE;
    static const IntXY BULLET_VELOCITY;
    static const IntXY SCREEN_SIZE;

};

#endif  // _BULLET_H_
