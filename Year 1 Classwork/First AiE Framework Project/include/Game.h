/******************************************************************************
 * File:               Game.h
 * Author:             Elizabeth Lowry
 * Date Created:       September 17, 2013
 * Description:        Definitions for the class that handles the game as a
						 whole.
 * Last Modified:      September 23, 2013
 * Last Modification:  Added pause state.
 ******************************************************************************/

#ifndef _GAME_H_
#define _GAME_H_

#include "Sprite.h"
#include "Ball.h"
#include "Player.h"
#include "StopWatch.h"

// Handles the game as a whole.
class Game
{
public:

	// It would be better to use enum classes here so we won't have to worry
	// about the names of enum constants, but Visual Studio 2010 doesn't support
	// that feature of C++11.  >:-(
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
	enum HumanPlayers
	{
		LEFT,
		RIGHT,
		BOTH
	};
	enum Speed
	{
		SLOW = 200,
		MEDIUM = 400,
		FAST = 600
	};

	Game();
	bool Run();
	void Shutdown();
	
	// GAME_TITLE = "Pong, starring Venus and Serena Williams!"
	static const char* const GAME_TITLE;
	static const int SCREEN_WIDTH = 1200;
	static const int SCREEN_HEIGHT = 801;

private:
	
	void CheckCollisions();
	GameState CheckForWinners( bool a_bBackgroundMatch );
	void DrawPauseScreen();
	void DrawScores( bool a_bDrawTime = true );
	void EnterMenu();
	static bool IsOneOfTheseKeysDown( const int* const ac_pciKeys,
									  const unsigned int ac_uiKeyCount );
	bool MatchOver() const;
	GameState Menu();
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
	static const int LEFT_PLAYER_LOSES_X = 200;
	static const Sprite::XYPair LEFT_PLAYER_START_POSITION;	// {240,396}
	static const int LEFT_SCORE_X = 100;
	static const int MAX_Y = 645;
	static const unsigned int MENU_KEY_COUNT = 4;
	// KEY_ESC, KEY_HOME, KEY_END, KEY_BACKSPACE
	static const int MENU_KEYS[MENU_KEY_COUNT];
	static const int MIN_Y = 147;
	static const unsigned int PAUSE_KEY_COUNT = 7;
	// KEY_PAUSE, KEY_ESC, KEY_HOME, KEY_END, KEY_BACKSPACE, KEY_SPACE, KEY_ENTER
	static const int PAUSE_KEYS[PAUSE_KEY_COUNT];
	static const unsigned int RESUME_KEY_COUNT = 3;
	// KEY_PAUSE, KEY_SPACE, KEY_ENTER
	static const int RESUME_KEYS[RESUME_KEY_COUNT];
	static const int RIGHT_PLAYER_LOSES_X = 1000;
	static const Sprite::XYPair RIGHT_PLAYER_START_POSITION;	// {960,396}
	static const int RIGHT_SCORE_X = 1000;
	static const int SCORE_Y = 700;
	static const int TIME_Y = 80;
	static const int TIME_X = 550;
	
	Sprite m_oBackgroundSprite;
	Ball m_oBall;
	Speed m_eGameSpeed;
	HumanPlayers m_eHumanPlayers;
	Player m_oLeftPlayer;
	bool m_bKeyPressed;	// Is it still the initial pause/unpause keypress?
	StopWatch m_oPlayTime;	// How long has the current match been in progress?
	Player m_oRightPlayer;
	Player* m_poServingPlayer;	// Which player will serve the ball?
	GameState m_eState;

};

#endif	// _GAME_H_