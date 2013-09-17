/******************************************************************************
 * File:              Player.cpp
 * Author:            Elizabeth Lowry
 * Date Created:      September 11, 2013
 * Description:       Implementation for methods of the Player class.
 * Last Modified:     September 17, 2013
 * Last Modification: Adjusted BallIsIncoming function.
 ******************************************************************************/

#include "Player.h"
#include "AIE.h"

const char* const Player::LEFT_PLAYER_NAME = "Serena";
const char* const Player::LEFT_TEXTURE_NAME = "./images/serena_williams.png";
const char* const Player::RIGHT_PLAYER_NAME = "Venus";
const char* const Player::RIGHT_TEXTURE_NAME = "./images/venus_williams.png";

Player::Player(Ball& a_roBall, const Side ac_eSide, Vector a_oPosition, const int ac_iMinY, const int ac_iMaxY)
	: Sprite(ac_eSide == LEFT ? LEFT_TEXTURE_NAME : RIGHT_TEXTURE_NAME,
			 PLAYER_WIDTH, PLAYER_HEIGHT, a_oPosition),
	  m_roBall(a_roBall),
	  mc_iMaxY(ac_iMaxY),
	  mc_iMinY(ac_iMinY),
	  m_eMode(FROZEN),
	  m_oPosition(a_oPosition),
	  m_uiScore(0),
	  mc_oStartPosition(a_oPosition),
	  mc_eSide(ac_eSide)
{
	// nothing left to do here
}

bool Player::BallIsIncoming() const
{
	float fBallPositionX = m_roBall.GetPosition().x;
	float fBallVelocityX = m_roBall.GetVelocity().x;
	float fOffsetX = (float)(PADDLE_WIDTH + m_roBall.GetDiameter()) / 2;
	if (mc_eSide == LEFT && fBallVelocityX < 0)
		return (fBallPositionX > (m_oPosition.x - fOffsetX));
	if (mc_eSide == RIGHT && fBallVelocityX > 0)
		return (fBallPositionX < (m_oPosition.x + fOffsetX));
	return false;
}

bool Player::CanHit() const
{
	if (!BallIsIncoming())
		return false;
	Vector oBallPosition = m_roBall.GetPosition();
	float fOffsetX = (float)(PADDLE_WIDTH + m_roBall.GetDiameter()) / 2;
	float fOffsetY = (float)(PADDLE_HEIGHT + m_roBall.GetDiameter()) / 2;
	float fMinX = m_oPosition.x - fOffsetX;
	float fMaxX = m_oPosition.x + fOffsetX;
	float fMinY = m_oPosition.y - fOffsetY;
	float fMaxY = m_oPosition.y + fOffsetY;
	return (fMinX <= oBallPosition.x && oBallPosition.x <= fMaxX &&
			fMinY <= oBallPosition.y && oBallPosition.y <= fMaxY);
}

void Player::Reset()
{
	m_uiScore = 0;
	m_oPosition = mc_oStartPosition;
}

void Player::Draw() const
{
	if (!m_bDestroyed)
	{
		MoveSprite(m_cuiSpriteID, m_oPosition.x, m_oPosition.y);
		DrawSprite(m_cuiSpriteID);
	}
}

const char* const Player::GetPlayerName() const
{
	return mc_eSide == LEFT ? LEFT_PLAYER_NAME : RIGHT_PLAYER_NAME;
}

unsigned int Player::GetScore() const
{
	return m_uiScore;
}

void Player::Hit() const
{
	// if the ball is outside these bounds, then it must be hitting the edge of the player
	float fMinY = m_oPosition.y - ((float)PADDLE_HEIGHT / 2);
	float fMaxY = m_oPosition.y + ((float)PADDLE_HEIGHT / 2);
	float fBallPosY = m_roBall.GetPosition().y;
	float fBallVelY = m_roBall.GetVelocity().y;

	m_roBall.BounceX();
	if ((0 < fBallVelY && fBallPosY < fMinY) || (fMaxY < fBallPosY && fBallVelY < 0))
		m_roBall.BounceY();
}

void Player::IncrementScore()
{
	m_uiScore++;
}


void Player::Serve() const
{
	Vector oServePosition = m_oPosition;
	unsigned int uiBallDiameter = m_roBall.GetDiameter();
	if (mc_eSide == LEFT)
		oServePosition.x += (float)(PADDLE_WIDTH + uiBallDiameter) / 2;
	else
		oServePosition.x -= (float)(PADDLE_WIDTH + uiBallDiameter) / 2;
	Vector oServeVelocity = {mc_eSide == LEFT ? 1.0f : -1.0f, -1.0f};
	m_roBall.Serve(oServePosition, oServeVelocity);
}

void Player::SetMode(Mode a_eMode)
{
	m_eMode = a_eMode;
}

void Player::Update(float a_fDeltaT)
{
	switch(GetDirection())
	{
	case UP:
		m_oPosition.y -= a_fDeltaT;
		break;
	case DOWN:
		m_oPosition.y += a_fDeltaT;
		break;
	default:
		break;
	}
}

Player::MotionDirection Player::GetDirection() const
{
	MotionDirection eMotion = NONE;
	switch(m_eMode)
	{
	case AI:
		eMotion = GetAIDirection();
		break;
	case HUMAN:
		eMotion = GetHumanDirection();
		break;
	default:
		break;
	}
	return eMotion;
}

Player::MotionDirection Player::GetAIDirection() const
{
	if(!BallIsIncoming())
		return NONE;
	float fBallPositionY = m_roBall.GetPosition().y;
	float fMinY = mc_iMinY + ((float)PADDLE_HEIGHT / 2);
	if((fBallPositionY < m_oPosition.y) && (m_oPosition.y > fMinY))
		return UP;
	float fMaxY = mc_iMaxY - ((float)PADDLE_HEIGHT / 2);
	if((fBallPositionY > m_oPosition.y) && (m_oPosition.y < fMaxY))
		return DOWN;
	return NONE;
}

Player::MotionDirection Player::GetHumanDirection() const
{
	bool bDown = IsKeyDown(mc_eSide == LEFT ? LEFT_DOWN_KEY : RIGHT_DOWN_KEY);
	bool bUp = IsKeyDown(mc_eSide == LEFT ? LEFT_UP_KEY : RIGHT_UP_KEY);
	if (bUp == bDown)
		return NONE;
	float fMinY = mc_iMinY + ((float)PADDLE_HEIGHT / 2);
	if (bUp && (this->m_oPosition.y > fMinY))
		return UP;
	float fMaxY = mc_iMaxY - ((float)PADDLE_HEIGHT / 2);
	if (bDown && (this->m_oPosition.y < fMaxY))
		return DOWN;
	return NONE;
}

