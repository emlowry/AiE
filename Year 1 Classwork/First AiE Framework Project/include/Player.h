/******************************************************************************
 * File:              Player.h
 * Author:            Elizabeth Lowry
 * Date Created:      September 11, 2013
 * Description:       Definitions for the class that handles a player sprite.
 * Last Modified:     September 16, 2013
 * Last Modification: Added Hit and SetDirectionProvider functions.
 ******************************************************************************/

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Sprite.h"
#include "Ball.h"
#include "AIE.h"
#include <functional>

using namespace std;

class Player : public Sprite
{
public:

	enum Side
	{
		LEFT,
		RIGHT
	};

	enum Mode
	{
		FROZEN,
		AI,
		HUMAN
	};

	Player(Ball& a_roBall, const Side ac_eSide, Vector a_oPosition, const int ac_iMinY, const int ac_iMaxY);

	bool CanHit() const;
	void Reset();
	void Draw() const;
	const char* const GetPlayerName() const;
	unsigned int GetScore() const;
	void Hit() const;
	void IncrementScore();
	void Serve() const;
	void SetMode(Mode a_eMode);
	void Update(float a_fDeltaT);

private:

	enum MotionDirection
	{
		NONE,
		UP,
		DOWN
	};

	// due to the art used, the sprite is a bit larger than the actual paddle area
	static const unsigned int LEFT_DOWN_KEY = 'S';
	static const char* const LEFT_PLAYER_NAME;
	static const char* const LEFT_TEXTURE_NAME;
	static const unsigned int LEFT_UP_KEY = 'W';
	static const unsigned int PADDLE_HEIGHT = 100;
	static const unsigned int PADDLE_WIDTH = 50;
	static const unsigned int PLAYER_HEIGHT = 130;
	static const unsigned int PLAYER_WIDTH = 70;
	static const unsigned int RIGHT_DOWN_KEY = KEY_DOWN;
	static const char* const RIGHT_PLAYER_NAME;
	static const char* const RIGHT_TEXTURE_NAME;
	static const unsigned int RIGHT_UP_KEY = KEY_UP;

	const int mc_iMaxY;
	const int mc_iMinY;
	const Side mc_eSide;

	Ball& m_roBall;
	Mode m_eMode;
	Vector m_oPosition;
	unsigned int m_uiScore;
	const Vector mc_oStartPosition;

	bool BallIsIncoming() const;
	MotionDirection GetDirection() const;
	MotionDirection GetAIDirection() const;
	MotionDirection GetHumanDirection() const;
};

#endif // _PLAYER_H_
