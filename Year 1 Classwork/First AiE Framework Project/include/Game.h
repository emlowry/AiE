/**************************************************************************************************
 * File:               Game.h
 * Author:             Elizabeth Lowry
 * Date Created:       September 17, 2013
 * Description:        Definitions for the class that handles the game as a whole.
 * Last Modified:      September 17, 2013
 * Last Modification:  Moving code in from main.cpp.
 **************************************************************************************************/

#ifndef _GAME_H_
#define _GAME_H_

#include "Sprite.h"
#include "Ball.h"
#include "Player.h"

class Game
{
public:
	
	static const char* const GAME_TITLE;	// "Pong, starring Venus and Serena Williams!"
	static const int SCREEN_WIDTH = 1200;
	static const int SCREEN_HEIGHT = 801;

	Game();
	bool Run();
	void Shutdown();

private:

	static const char* const BACKGROUND_TEXTURE_NAME;	// "./images/tennis_court.png"
	static const int FAST_SPEED = 600;
	static const int LEFT_PLAYER_LOSES_X = 200;
	static const Sprite::Vector LEFT_PLAYER_START_POSITION;	// {240,396}
	static const int LEFT_SCORE_X = 100;
	static const int MAX_Y = 645;
	static const int MEDIUM_SPEED = 400;
	static const int MIN_Y = 147;
	static const int RIGHT_PLAYER_LOSES_X = 1000;
	static const Sprite::Vector RIGHT_PLAYER_START_POSITION;	// {960,396}
	static const int RIGHT_SCORE_X = 1000;
	static const char* const SCORE_FORMAT;	// "%s: %d"
	static const int SCORE_Y = 700;
	static const int SLOW_SPEED = 200;
	static const char* const TIME_FORMAT;	// "%d:%02d:%03d"
	static const int TIME_Y = 80;
	static const int TIME_X = 550;

	enum GameState { ENTER_MENU, MENU, START_MATCH, START_ROUND, GAME_STATE, END };
	enum HumanPlayers { LEFT, RIGHT, BOTH };
	enum MenuPage { PLAY, SCORES, QUIT };
	enum Speed { SLOW, MEDIUM, FAST };

	static void FormatPlayTime(char* a_pcBuffer, unsigned int a_uiBufferSize, float a_fPlayTime);
	static float GetSpeed(const Speed ac_eSpeed);

	Sprite m_oBackgroundSprite;
	Ball m_oBall;
	Speed m_eGameSpeed;
	HumanPlayers m_eHumanPlayers;
	Player m_oLeftPlayer;
	float m_fPlayTime;
	Player m_oRightPlayer;
	Player* m_poServingPlayer;
	GameState m_eState;
	
	void EnterMenu();
	void PlayGame();
	bool PlayerScores();
	bool PlayerWon();
	Player* RandomPlayer();
	GameState RunMenu();
	void StartMatch();
	void StartRound();
};

#endif	// _GAME_H_