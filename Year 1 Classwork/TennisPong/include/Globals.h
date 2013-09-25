/******************************************************************************
 * File:               Globals.h
 * Author:             Elizabeth Lowry
 * Date Created:       September 23, 2013
 * Description:        Definitions for global enums, structs, and functions.
 * Last Modified:      September 24, 2013
 * Last Modification:  Added constant for distance between drawn lines of text.
 ******************************************************************************/

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include "AIE.h"

// Draw a string with newline ('\n') characters in it
void DrawMultilineString( const char* a_pText,
						  int a_iXPos,
						  int a_iYPos,
						  SColour a_sColour = SColour(0xFF,0xFF,0xFF,0xFF) );

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
	BOTH,

	NUMBER_OF_HUMAN_PLAYER_OPTIONS
};
const char* const HUMAN_PLAYER_STRINGS[NUMBER_OF_HUMAN_PLAYER_OPTIONS] =
{
	"Human Serena vs. AI Venus",
	"AI Serena vs. Human Venus",
	"Human Serena vs. Human Venus",
};

// If at least one of the given keys is pressed, return true.  Game and Menu
// both need this.
bool IsOneOfTheseKeysDown( const int* const ac_pciKeys,
						   const unsigned int ac_uiKeyCount );

// How far between lines of text printed on the screen?
const unsigned int LINE_SEPARATION = 40;

// Which list are you looking at on the high score list?  Game, Menu, and
// HighScores all need this.
enum ScoreListType
{
	HIGH_SCORES,
	FAST_WINS,
	SLOW_LOSSES,

	NUMBER_OF_SCORE_LIST_TYPES
};

// How fast does the game run?  Game, Menu, and HighScores all need this.
enum Speed
{
	SLOW,
	MEDIUM,
	FAST,

	NUMBER_OF_SPEEDS
};

// Struct for storing coordinates or direction vectors on a 2D plane.  Sprite,
// Ball, Player, and Game all use this.
struct XYPair
{
	float x;
	float y;
};
const XYPair DEFAULT_X_Y_PAIR = {0.0,0.0};

#endif	// _GLOBALS_H_
