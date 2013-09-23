/******************************************************************************
 * File:               Game.h
 * Author:             Elizabeth Lowry
 * Date Created:       September 17, 2013
 * Description:        Definitions for the class that handles the game as a
						 whole.
 * Last Modified:      September 18, 2013
 * Last Modification:  Added comments.
 ******************************************************************************/

#ifndef _GAME_H_
#define _GAME_H_

#include "Sprite.h"
#include "Ball.h"
#include "Player.h"

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
	void DrawScores( bool a_bBackgroundMatch );
	void EnterMenu();
	static void FormatPlayTime( char* a_pcBuffer,
								unsigned int a_uiBufferSize,
								float a_fPlayTime );
	bool MatchOver() const;
	GameState Menu();
	GameState PlayGame( bool a_bBackgroundMatch = false );
	// updates score and serving player and returns true if a player scores
	bool PlayerScores();
	// Pick one of the players at random
	Player* RandomPlayer();
	void StartMatch();
	void StartRound();
	void UpdateAndDrawSprites();

	// BACKGROUND_TEXTURE_NAME = "./images/tennis_court.png"
	static const char* const BACKGROUND_TEXTURE_NAME;
	static const int LEFT_PLAYER_LOSES_X = 200;
	static const Sprite::XYPair LEFT_PLAYER_START_POSITION;	// {240,396}
	static const int LEFT_SCORE_X = 100;
	static const int MAX_Y = 645;
	static const int MIN_Y = 147;
	static const int RIGHT_PLAYER_LOSES_X = 1000;
	static const Sprite::XYPair RIGHT_PLAYER_START_POSITION;	// {960,396}
	static const int RIGHT_SCORE_X = 1000;
	static const char* const SCORE_FORMAT;	// "%s: %d"
	static const int SCORE_Y = 700;
	static const char* const TIME_FORMAT;	// "%d:%02d:%03d"
	static const int TIME_Y = 80;
	static const int TIME_X = 550;
	
	Sprite m_oBackgroundSprite;
	Ball m_oBall;
	Speed m_eGameSpeed;
	HumanPlayers m_eHumanPlayers;
	Player m_oLeftPlayer;
	float m_fPlayTime;	// How long has the current match been in progress?
	Player m_oRightPlayer;
	Player* m_poServingPlayer;	// Which player will serve the ball?
	GameState m_eState;

};

#endif	// _GAME_H_