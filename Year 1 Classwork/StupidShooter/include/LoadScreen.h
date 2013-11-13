/******************************************************************************
 * File:               LoadScreen.h
 * Author:             Elizabeth Lowry
 * Date Created:       October 29, 2013
 * Description:        GameState representing the initial splash screen shown
 *                      when the game starts.
 * Last Modified:      October 29, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef _LOAD_SCREEN_H_
#define _LOAD_SCREEN_H_

#include "GameState.h"
#include "Sprite.h"
#include "StopWatch.h"

SINGLETON_STATE_CLASS( LoadScreen )
{
SINGLETON_STATE_PRIVATE( LoadScreen )

    void Draw() const override;
    void HandleInput() override {}
    void Load();
    bool IsFinished();
    void OnEnter() override;
    void WhenFinished();
    void Update() override;

    static const char* const SPLASH_FILE;
    static const unsigned int MIN_LOAD_SECONDS = 2;
    static const IntXY SCREEN_SIZE;
    static const IntXY SCREEN_CENTER;

    StopWatch m_oLoadTime;
    bool m_bSplashDrawn;
    bool m_bLoadingComplete;

    Sprite* m_poSplashScreen;
};

#endif  // _LOAD_SCREEN_H_