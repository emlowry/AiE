/******************************************************************************
 * File:               Player.h
 * Author:             Elizabeth Lowry
 * Date Created:       September 11, 2013
 * Description:        Definitions for the class that handles a player sprite.
 * Last Modified:      September 23, 2013
 * Last Modification:  Updated formatting to follow coding standards.
 ******************************************************************************/

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "AIE.h"
#include "Ball.h"
#include "Sprite.h"

class Player : public Sprite
{
public:
	
	// It would be better to use enum classes here so we won't have to worry
	// about the names of enum constants, but Visual Studio 2010 doesn't support
	// that feature of C++11.  >:-(
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

	Player( Ball& a_roBall,		// Save a reference to the Ball for the AI
			const Side ac_eSide,
			const XYPair& a_oPosition,
			const int ac_iMinY,
			const int ac_iMaxY );

	bool CanHit() const;
	const char* const GetPlayerName() const;
	unsigned int GetScore() const;
	void Hit() const;
	void IncrementScore();
	void PrintScore( char* a_pcBuffer, unsigned int a_uiBufferSize );
	void Reset();
	void Serve() const;
	void SetMode( Mode a_eMode );
	void Update( float a_fDeltaT );

private:
	
	// It would be better to use enum classes here so we won't have to worry
	// about the names of enum constants, but Visual Studio 2010 doesn't support
	// that feature of C++11.  >:-(
	enum MotionDirection {
		NONE,
		UP,
		DOWN
	};

	bool BallIsIncoming() const;
	virtual void DrawTasks() const;
	MotionDirection GetDirection() const;	// Which way should the player move?
	MotionDirection GetAIDirection() const;
	MotionDirection GetHumanDirection() const;

	static const int LEFT_DOWN_KEY = 'S';
	static const char* const LEFT_PLAYER_NAME;	// "Serena"
	static const char* const LEFT_TEXTURE_NAME;	// "./images/serena_williams.png"
	static const int LEFT_UP_KEY = 'W';
	static const unsigned int PADDLE_HEIGHT = 100;	// due to the art used, the
	static const unsigned int PADDLE_WIDTH = 50;	// sprite is a bit larger
	static const unsigned int PLAYER_HEIGHT = 130;	// than the actual paddle
	static const unsigned int PLAYER_WIDTH = 70;	// area.
	static const int RIGHT_DOWN_KEY = KEY_DOWN;
	static const char* const RIGHT_PLAYER_NAME;	// "Venus"
	static const char* const RIGHT_TEXTURE_NAME;	// "./images/venus_williams.png"
	static const int RIGHT_UP_KEY = KEY_UP;
	static const char* const SCORE_FORMAT;	// "%s: %d"

	const int mc_iMaxY;
	const int mc_iMinY;
	const Side mc_eSide;
	const XYPair mc_oStartPosition;

	Ball& m_roBall;	// Keep a reference to the ball so the AI knows where it is
	Mode m_eMode;
	XYPair m_oPosition;
	unsigned int m_uiScore;

};

#endif // _PLAYER_H_
