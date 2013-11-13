/******************************************************************************
 * File:               Play.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 13, 2013
 * Description:        GameState representing the shooter gameplay.
 * Last Modified:      November 13, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef _PLAY_H_
#define _PLAY_H_

#include "GameState.h"
#include "Player.h"
#include "Sprite.h"
#include "StopWatch.h"

SINGLETON_STATE_CLASS( Play )
{
    friend class LoadScreen;

SINGLETON_STATE_PRIVATE( Play )

    void Draw() const override;
    void HandleInput() override;
    static void LoadState();
    void Load();
    void OnEnter() override;
    void Update() override;

    static const char* const BACKGROUND_FILE;
    static const IntXY SCREEN_SIZE;
    static const IntXY SCREEN_CENTER;
    static const IntXY SHIP_SIZE;
    static const int ATTACK_INTERVAL_MS = 500;
    static const char* const STRING_FORMAT;
    static const unsigned int STRING_LENGTH = 100;
    static const IntXY STRING_POSITION;

    Player* m_poPlayer;
    Sprite* m_poBackground;

    StopWatch m_oAttackTimer;

    unsigned int m_uiPoints;
    unsigned int m_uiLives;
};

#endif  // _PLAY_H_