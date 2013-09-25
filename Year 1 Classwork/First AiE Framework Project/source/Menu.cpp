/******************************************************************************
 * File:               Menu.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       September 24, 2013
 * Description:        Implementations for methods of the Menu class.
 * Last Modified:      September 24, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#include "Menu.h"
#include "Globals.h"
#include "HighScores.h"

const char* const Menu::LEFT_PLAYER_HINT = "";
const char* const Menu::MENU_STATE_STRINGS[NUMBER_OF_MENU_STATES * 2] =
{
	"  PLAY GAME    Scoreboard    Quit",
	"[ PLAY GAME ]  Scoreboard    Quit",
	"  Play Game    SCOREBOARD    Quit",
	"  Play Game  [ SCOREBOARD ]  Quit",
	"  Play Game    Scoreboard  [ QUIT ]",
	"  Play Game    Scoreboard  [ QUIT ]",
};
const char* const Menu::PLAY_MESSAGE = "Press ENTER or SPACE to start a match!";
const char* const Menu::PLAY_SETTING_STRINGS[NUMBER_OF_PLAY_SETTINGS] =
{
	"Difficulty:     %s\n \n"
	"      Players:     %s\n \n"
	"      %s\n"
	"      %s",

	"Difficulty:  <- %s ->\n \n"
	"      Players:     %s\n \n"
	"      %s\n"
	"      %s",

	"Difficulty:     %s\n \n"
	"      Players:  <- %s ->\n \n"
	"      %s\n"
	"      %s",
}
const char* const Menu::RIGHT_PLAYER_HINT = "";
const char* const Menu::SCORE_SETTING_STRINGS[NUMBER_OF_SCORE_SETTINGS] =
{
	"",
	"",
	"",
}

// Constructor instantiates members in initializer list
Menu::Menu( Speed& a_reGameSpeed,
		  HighScores& a_roHighScores,
		  HumanPlayers& a_reHumanPlayers,
		  bool& a_rbKeyPressed )
	: m_reGameSpeed( a_reGameSpeed ),
	  m_roHighScores( a_roHighScores ),
	  m_reHumanPlayers( a_reHumanPlayers ),
	  m_rbKeyPressed( a_rbKeyPressed ),
	  m_eMenuState( PLAY ),
	  m_ePlaySetting( PLAY_SPEED ),
	  m_eScoreSetting( SCORE_SPEED )
{
}

// Set the menu state (when entering the menu) to either PLAY or SCORES,
// depending on whether this is program startup or just the menu displayed after
// a match.
void Menu::Enter( bool a_bProgramStartup )
{
	if( !a_bProgramStartup )
	{
		// If this isn't the first time we've entered the menu (that is, any
		// time other than program startup), set the menu to show scores.
		m_eMenuState = SCORES;
	}
	// Otherwise, leave it in its initial state of PLAY.
}

// Draw the quit confirmation screen.
void Menu::DrawExitMenu()
{
}

// Draw the play settings menu.
void Menu::DrawPlayMenu()
{
}

// Draw the . 
void Menu::DrawScoresMenu()
{
}

// Draw the menu text, keep track of user input, and return MENU, START_MATCH,
// or END as appropriate.
GameState Menu::Run()
{
	GameState eNextGameState = MENU;
	switch( m_eMenuState )
	{
	case PLAY:
		{
			eNextGameState = UpdatePlayMenu();
			DrawPlayMenu();
			break;
		}
	case EXIT:
		{
			eNextGameState = UpdateExitMenu();
			DrawExitMenu();
			break;
		}
	case SCORES:
	default:
		{
			UpdateScoresMenu();
			DrawScoresMenu();
			break;
		}
	}	// end of switch statement
	return eNextGameState;
}

// Keep track of user input and return MENU or END, as appropriate.
GameState Menu::UpdateExitMenu()
{
}

// Keep track of user input and return MENU or START_MATCH as appropriate.
GameState Menu::UpdatePlayMenu()
{
}

// Keep track of user input. 
void Menu::UpdateScoresMenu()
{
}
