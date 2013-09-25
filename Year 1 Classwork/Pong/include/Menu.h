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

	Menu( ScoreListType& a_reDisplayListType,
		  Speed& a_reGameSpeed,
	      HighScores& a_roHighScores,
		  HumanPlayers& a_reHumanPlayers,
		  bool& a_rbKeyPressed );

	void Enter();
	GameState Run();

private:
    
	// It would be better to use enum classes here so we won't have to worry
	// about the names of enum constants, but Visual Studio 2010 doesn't support
	// that feature of C++11.  >:-(
	enum MenuState
	{
		PLAY,
		SCORES,
		EXIT,

		NUMBER_OF_MENU_STATES
	};
    enum KeyPressAction
    {
        NONE,
        CONFIRM,
        GO_DOWN,
        GO_LEFT,
        GO_RIGHT,
        GO_UP,
        GO_TO_EXIT,
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
    void DrawMenuStateString( bool a_bFocusOnMainMenu );
	void DrawPlayMenu();
	void DrawScoresMenu();
    KeyPressAction GetKeyPressAction();
    static unsigned int Rollover( const unsigned int a_uiPlace,
                                  const unsigned int a_uiSize,
                                  const bool a_bForward );
    void SideScrollPlayMenu( bool a_bForward );
    void SideScrollScoresMenu( bool a_bForward );
	GameState UpdateExitMenu();
	GameState UpdatePlayMenu();
	void UpdateScoresMenu();

    
    static const char* const EXIT_MESSAGE;
	static const char* const LEFT_PLAYER_HINT;
    static const char* const PLAYER_HINT;
	static const char* const PLAY_MESSAGE;
	static const char* const RIGHT_PLAYER_HINT;

	static const char* const MENU_STATE_STRINGS[NUMBER_OF_MENU_STATES * 2];
	static const char* const PLAY_SETTING_STRINGS[NUMBER_OF_PLAY_SETTINGS];
    static const char* const SCORE_LIST_TYPE_STRINGS[NUMBER_OF_SCORE_LIST_TYPES];
	static const char* const SCORE_SETTING_STRINGS[NUMBER_OF_SCORE_SETTINGS];
    static const char* const SPEED_STRINGS[NUMBER_OF_SPEEDS];

    static const int FIRST_LINE_Y = 155;

    static const XYPair EXIT_MESSAGE_LOCATION;
    static const XYPair MENU_STATE_STRING_LOCATION;
    static const XYPair PLAYER_HINT_LOCATION;
    static const XYPair PLAY_MESSAGE_LOCATION;
    static const XYPair PLAY_SETTINGS_LOCATION;
    static const XYPair SCORE_SETTINGS_LOCATION;

    static const unsigned int CONFIRM_KEY_COUNT = 2;
    static const unsigned int DOWN_KEY_COUNT = 2;
	static const unsigned int EXIT_KEY_COUNT = 2;
    static const unsigned int LEFT_KEY_COUNT = 2;
	static const unsigned int PRESSABLE_KEY_COUNT = 12;
    static const unsigned int PLAY_SETTINGS_BUFFER_SIZE = 128;
    static const unsigned int RIGHT_KEY_COUNT = 2;
    static const unsigned int SCORE_SETTINGS_BUFFER_SIZE = 42;
    static const unsigned int UP_KEY_COUNT = 2;


    static const int CONFIRM_KEYS[CONFIRM_KEY_COUNT];    // KEY_SPACE, KEY_ENTER
    static const int DOWN_KEYS[DOWN_KEY_COUNT];    // KEY_DOWN, KEY_PAGEDOWN
	static const int EXIT_KEYS[EXIT_KEY_COUNT];	// KEY_ESC, KEY_END
	static const int LEFT_KEYS[LEFT_KEY_COUNT];	// KEY_LEFT, KEY_BACKSPACE
	// KEY_ENTER, KEY_SPACE, KEY_ESC, KEY_END, KEY_LEFT, KEY_BACKSPACE,
    // KEY_RIGHT, KEY_TAB, KEY_UP, KEY_PAGEUP, KEY_DOWN, KEY_PAGEDOWN
	static const int PRESSABLE_KEYS[PRESSABLE_KEY_COUNT];
	static const int RIGHT_KEYS[RIGHT_KEY_COUNT];	// KEY_RIGHT, KEY_TAB
	static const int UP_KEYS[UP_KEY_COUNT];	// KEY_UP, KEY_PAGEUP
	
    ScoreListType& m_reDisplayListType;
	Speed& m_reGameSpeed;
	HighScores& m_roHighScores;
	HumanPlayers& m_reHumanPlayers;
	bool& m_rbKeyPressed;
	MenuState m_eMenuState;
	PlaySetting m_ePlaySetting;
    bool m_bProgramStartup;
	ScoreSetting m_eScoreSetting;
};

#endif	// _MENU_H_
