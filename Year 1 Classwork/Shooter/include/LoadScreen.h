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
#include "StopWatch.h"

SINGLETON_STATE_CLASS( LoadScreen )
{
SINGLETON_STATE_PRIVATE( LoadScreen )

    void Draw() const override;
    bool IsFinished();
    void WhenFinished();
    void Update() override;

    static const unsigned int MIN_LOAD_SECONDS = 5;
    StopWatch m_oLoadTime;
};

#endif  // _LOAD_SCREEN_H_