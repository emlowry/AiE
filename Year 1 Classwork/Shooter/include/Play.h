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

    Player* m_poPlayer;
    Sprite* m_poBackground;

    unsigned int m_uiPoints;
    unsigned int m_uiLives;
};

#endif  // _PLAY_H_