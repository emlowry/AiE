/**************************************************************************************************
 * File:               Player.h
 * Author:             Elizabeth Lowry
 * Date Created:       September 11, 2013
 * Description:        Definitions for the class that handles a player sprite.
 * Last Modified:      September 18, 2013
 * Last Modification:  Added comments.
 **************************************************************************************************/

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Sprite.h"
#include "Ball.h"
#include "AIE.h"

class Player : public Sprite
{
public:

	// Publicly-available enums
	enum Side { LEFT, RIGHT };	// Side of the screen the player should be on
	enum Mode { FROZEN, AI, HUMAN };	// Is the player motionless, or controlled by a human or AI?

	// Constructor
	Player(Ball& a_roBall,		// Save a reference to the Ball so an AI player can update by itself
		   const Side ac_eSide,
		   const XYPair& a_oPosition,
		   const int ac_iMinY,
		   const int ac_iMaxY);

	// Public methods
	bool CanHit() const;	// Can this player hit the ball?
	const char* const GetPlayerName() const;	// Name accessor
	unsigned int GetScore() const;	// Score accessor
	void Hit() const;	// Make the ball rebound off the player
	void IncrementScore();	// Increase the player's score
	void Reset();	// Move the player back to its starting position and clear its score
	void Serve() const;	// Serve the ball
	void SetMode(Mode a_eMode);	// Mode mutator
	void Update(float a_fDeltaT);	// Update the player's position based on its mode

private:

	// Which way should the paddle go?
	enum MotionDirection { NONE, UP, DOWN };

	// Class-level constants
	static const unsigned int LEFT_DOWN_KEY = 'S';
	static const char* const LEFT_PLAYER_NAME;	// "Serena"
	static const char* const LEFT_TEXTURE_NAME;	// "./images/serena_williams.png"
	static const unsigned int LEFT_UP_KEY = 'W';
	static const unsigned int PADDLE_HEIGHT = 100;
	static const unsigned int PADDLE_WIDTH = 50;
	static const unsigned int PLAYER_HEIGHT = 130;	// due to the art used, the sprite is a bit
	static const unsigned int PLAYER_WIDTH = 70;	// larger than the actual paddle area
	static const unsigned int RIGHT_DOWN_KEY = KEY_DOWN;
	static const char* const RIGHT_PLAYER_NAME;	// "Venus"
	static const char* const RIGHT_TEXTURE_NAME;	// "./images/venus_williams.png"
	static const unsigned int RIGHT_UP_KEY = KEY_UP;

	// Constants set at instantiation
	const int mc_iMaxY;
	const int mc_iMinY;
	const Side mc_eSide;
	const XYPair mc_oStartPosition;

	// Members
	Ball& m_roBall;	// Keep a reference to the ball so the AI knows where it is
	Mode m_eMode;
	XYPair m_oPosition;
	unsigned int m_uiScore;

	// Private methods
	bool BallIsIncoming() const;	// Is the ball heading towards the player?
	void DrawTasks() const;	// Do the actual work of drawing the player sprite
	MotionDirection GetDirection() const;	// Which way should the player move?
	MotionDirection GetAIDirection() const;	// Which way does the AI say the player should move?
	MotionDirection GetHumanDirection() const;	// Which way is a human telling the player to move?

};

#endif // _PLAYER_H_
