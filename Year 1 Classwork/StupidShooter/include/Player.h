/******************************************************************************
 * File:               Player.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 13, 2013
 * Description:        Class for handling the player sprite.
 * Last Modified:      November 13, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Sprite.h"

class Player : public Sprite
{
public:

    Player();
    virtual ~Player() {};
    virtual void HandleInput();

    static const char* const PLAYER_FILE;

    bool m_bClickStarted;

};

#endif  // _PLAYER_H_