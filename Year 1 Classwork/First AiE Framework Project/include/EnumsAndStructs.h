/******************************************************************************
 * File:               Enums.h
 * Author:             Elizabeth Lowry
 * Date Created:       September 23, 2013
 * Description:        Definitions for enums and structs used in many classes.
 * Last Modified:      September 23, 2013
 * Last Modification:  Moved enums out of Game.h.
 ******************************************************************************/

#ifndef _ENUMS_AND_STRUCTS_H_
#define _ENUMS_AND_STRUCTS_H_

// Struct for storing coordinates or direction vectors on a 2D plane.  Sprite,
// Ball, Player, and Game all use this.
struct XYPair
{
	float x;
	float y;
};
const XYPair DEFAULT_X_Y_PAIR = {0.0,0.0};

// It would be better to use enum classes here so we won't have to worry
// about the names of enum constants, but Visual Studio 2010 doesn't support
// that feature of C++11.  >:-(

// What state is the game in?  Both Game and Menu need this.
enum GameState
{
	ENTER_MENU,
	MENU,
	START_MATCH,
	START_ROUND,
	PLAY_GAME,
	ENTER_PAUSE,
	PAUSED,
	END
};

// Which players are controlled by humans?  Game, Menu, and HighScores all need
// this.
enum HumanPlayers
{
	LEFT,
	RIGHT,
	BOTH
};

// How fast does the game run?  Game, Menu, and HighScores all need this.
enum Speed
{
	SLOW = 200,
	MEDIUM = 400,
	FAST = 600
};

#endif	// _ENUMS_AND_STRUCTS_H_
