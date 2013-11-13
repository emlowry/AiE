/******************************************************************************
 * File:               Enemy.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 13, 2013
 * Description:        Class for handling enemies.
 * Last Modified:      November 13, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Sprite.h"
#include <set>

class Enemy : public Sprite
{
public:

    Enemy( const IntXY& ac_roPosition );
    virtual ~Enemy();

    static void Deploy();
    static std::set< Enemy* > GetLive();
    static void UpdateAll( const float ac_fDeltaT );
    static void DrawAll();

    virtual void Update( const float ac_fDeltaT ) override;
    void Die();
    void Spawn( const IntXY& ac_roPosition );

private:

    static std::set< Enemy* > sm_oDead;
    static std::set< Enemy* > sm_oLive;

    static const char* const ENEMY_FILE;
    static const IntXY ENEMY_SIZE;
    static const IntXY ENEMY_VELOCITY;
    static const IntXY SCREEN_SIZE;

};

#endif  // _ENEMY_H_
