/******************************************************************************
 * File:               Player.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       November 13, 2013
 * Description:        Class for handling the player sprite.
 * Last Modified:      November 13, 2013
 * Last Modification:  Creation.
 ******************************************************************************/


#include "AIE.h"
#include "Player.h"
#include "Bullet.h"
#include "XY.h"

const char* const Player::PLAYER_FILE = "./images/ship.png";

Player::Player()
    : Sprite( PLAYER_FILE, IntXY( 70, 70 ) ), m_bClickStarted( false )
{
}

void Player::HandleInput()
{
    // Move
    IntXY oNewPosition(0);
    GetMouseLocation( oNewPosition.x, oNewPosition.y );
    if( oNewPosition.x > 1240 )
    {
        oNewPosition.x = 1240;
    }
    else if( oNewPosition.x < 40 )
    {
        oNewPosition.x = 40;
    }
    if( oNewPosition.y > 680 )
    {
        oNewPosition.x = 680;
    }
    else if( oNewPosition.y < 40 )
    {
        oNewPosition.y = 40;
    }
    m_oPosition = oNewPosition;

    // Fire
    if( GetMouseButtonDown( MOUSE_BUTTON_1 ) )
    {
        if( !m_bClickStarted )
        {
            Bullet::Fire( m_oPosition );
            m_bClickStarted = true;
        }
    }
    else
    {
        m_bClickStarted = false;
    }
}