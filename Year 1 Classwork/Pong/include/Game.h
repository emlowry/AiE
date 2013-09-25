/******************************************************************************
 * File:               Game.h
 * Author:             Elizabeth Lowry
 * Date Created:       September 17, 2013
 * Description:        Definitions for the class that handles the game as a
 *						 whole.
 * Last Modified:      September 24, 2013
 * Last Modification:  Added menu.
 ******************************************************************************/

#ifndef _GAME_H_
#define _GAME_H_

#include "Ball.h"
#include "Globals.h"
#include "HighScores.h"
#include "Menu.h"
#include "Player.h"
#include "Sprite.h"
#include "StopWatch.h"

// Handles the game as a whole.
class Game
{
public:

	Game();
	bool Run();
	void Shutdown();
	
	// GAME_TITLE = "PONG: Starring Venus and Serena Williams!"
	static const char* const GAME_TITLE;
	static const int SCREEN_HEIGHT = 801;
	static const int SCREEN_WIDTH = 1200;

private:
	
	void CheckCollisions();
	GameState CheckForWinners( bool a_bBackgroundMatch );
	void DrawPauseScreen();
	void DrawScores();
	void EnterMenu();
	bool MatchOver() const;
	GameState MenuState();
	GameState PlayGame( bool a_bBackgroundMatch = false );
	// updates score and serving player and returns true if a player scores
	bool PlayerScores();
	Player* RandomPlayer();	// Pick one of the players at random
	void StartMatch();
	void StartRound();
	void UpdateAndDrawSprites();
	GameState WaitForUnpause();

	// BACKGROUND_TEXTURE_NAME = "./images/tennis_court.png"
	static const char* const BACKGROUND_TEXTURE_NAME;
	static const char* const OVERTIME_STRING;
	static const char* const PAUSE_MESSAGE;	// long-ass message - see .cpp
	// SHADE_TEXTURE_NAME = "./images/shade.png"
	static const char* const SHADE_TEXTURE_NAME;
	static const char* const TIME_PREFIX;	// "Time: "

	static const double OVERTIME_SECONDS;   // 2.5 hours

	static const XYPair LEFT_PLAYER_START_POSITION;	// {240,396}
	static const XYPair PAUSE_MESSAGE_POSITION;	// {225,150}
	static const XYPair OVERTIME_POSITION;	// {300,80}
	static const XYPair RIGHT_PLAYER_START_POSITION;	// {960,396}
	static const XYPair TIME_POSITION;	// {485,80}

	static const int LEFT_PLAYER_LOSES_X = 200;
	static const int LEFT_SCORE_X = 100;
	static const int MIN_Y = 147;
	static const int MAX_Y = 645;
	static const int RIGHT_PLAYER_LOSES_X = 1000;
	static const int RIGHT_SCORE_X = 1000;
	static const int SCORE_Y = 700;

    static const unsigned int SPEED_FACTORS[NUMBER_OF_SPEEDS];

	static const unsigned int MENU_KEY_COUNT = 4;
	static const unsigned int PAUSE_KEY_COUNT = 7;
	static const unsigned int RESUME_KEY_COUNT = 3;

	//KEY_ESC, KEY_HOME, KEY_END, KEY_BACKSPACE
	static const int MENU_KEYS[MENU_KEY_COUNT];
	// KEY_PAUSE, KEY_ESC, KEY_HOME, KEY_END, KEY_BACKSPACE, KEY_SPACE, KEY_ENTER
	static const int PAUSE_KEYS[PAUSE_KEY_COUNT];
	// KEY_PAUSE, KEY_SPACE, KEY_ENTER
	static const int RESUME_KEYS[RESUME_KEY_COUNT];
	
	Sprite m_oBackgroundSprite;
	Ball m_oBall;
	Player m_oLeftPlayer;
	Player m_oRightPlayer;
	Sprite m_oScreenShadeSprite;	// dims the screen during pause and menu
	Player* m_poServingPlayer;	// Which player will serve the ball?

	HighScores m_oHighScores;
    Menu m_oMenu;
	StopWatch m_oPlayTime;	// How long has the current match been in progress?

	ScoreListType m_eDisplayScoreListType;	// Which high score list to display?
	Speed m_eGameSpeed;
	HumanPlayers m_eHumanPlayers;
	GameState m_eState;

	bool m_bKeyPressed;	// Is it still the initial pause/unpause keypress?

};

#endif	// _GAME_H_