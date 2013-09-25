/******************************************************************************
 * File:               Menu.h
 * Author:             Elizabeth Lowry
 * Date Created:       September 24, 2013
 * Description:        Definitions for the class that handles the game menu.
 * Last Modified:      September 24, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef _MENU_H_
#define _MENU_H_

#include "Globals.h"
#include "HighScores.h"

// Handles the game menu.
class Menu
{
public:

	Menu( Speed& a_reGameSpeed,
		  HighScores& a_roHighScores,
		  HumanPlayers& a_reHumanPlayers,
		  bool& a_rbKeyPressed );

	void Enter( bool a_bProgramStartup );
	GameState Run();

private:

	enum MenuState
	{
		PLAY,
		SCORES,
		EXIT,

		NUMBER_OF_MENU_STATES
	};
	enum PlaySetting
	{
		PLAY_MAIN,
		PLAY_SPEED,
		PLAY_HUMANS,

		NUMBER_OF_PLAY_SETTINGS
	};
	enum ScoreSetting
	{
		SCORE_MAIN,
		SCORE_SPEED,
		SCORE_TYPE,

		NUMBER_OF_SCORE_SETTINGS
	};

	void DrawExitMenu();
	void DrawPlayMenu();
	void DrawScoresMenu();

	GameState UpdateExitMenu();
	GameState UpdatePlayMenu();
	void UpdateScoresMenu();

	static const char* const LEFT_PLAYER_HINT;
	static const char* const MENU_STATE_STRINGS[NUMBER_OF_MENU_STATES * 2];
	static const char* const PLAY_MESSAGE;
	static const char* const PLAY_SETTING_STRINGS[NUMBER_OF_PLAY_SETTINGS];
	static const char* const RIGHT_PLAYER_HINT;
	static const char* const SCORE_SETTING_STRINGS[NUMBER_OF_SCORE_SETTINGS];
	
	Speed& m_reGameSpeed;
	HighScores& m_roHighScores;
	HumanPlayers& m_reHumanPlayers;
	bool& m_rbKeyPressed;
	MenuState m_eMenuState;
	PlaySetting m_ePlaySetting;
	ScoreSetting m_eScoreSetting;
}

#endif	// _MENU_H_
