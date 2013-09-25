/******************************************************************************
 * File:               Menu.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       September 24, 2013
 * Description:        Implementations for methods of the Menu class.
 * Last Modified:      September 24, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#include "AIE.h"
#include "Globals.h"
#include "HighScores.h"
#include "Menu.h"
#include <cstdio>   // for sprintf_s

// String constants
const char* const Menu::EXIT_MESSAGE = "Are you sure you want to quit?\n \n"
                                       "Press ENTER, SPACE, ESC, or END\n"
                                       "     to exit the program.";
const char* const Menu::LEFT_PLAYER_HINT =
    "Move Serena up with the W key and down with the S key.";
const char* const Menu::PLAYER_HINT = "%s\n%s";
const char* const Menu::PLAY_MESSAGE =
    "          Press ENTER or SPACE to start a match!\n"
    "     You win when you have at least four points and\n"
    "are ahead of the other player by at least two points.";
const char* const Menu::RIGHT_PLAYER_HINT =
    "Move Venus up with the UP key and down with the DOWN key.";

// String array constants
const char* const Menu::MENU_STATE_STRINGS[NUMBER_OF_MENU_STATES * 2] =
{
	" PLAY GAME   Scoreboard   Quit",
	"[PLAY GAME]  Scoreboard   Quit",
	" Play Game   SCOREBOARD   Quit",
	" Play Game  [SCOREBOARD]  Quit",
	" Play Game   Scoreboard   QUIT",
	" Play Game   Scoreboard  [QUIT]",
};
const char* const Menu::PLAY_SETTING_STRINGS[NUMBER_OF_PLAY_SETTINGS] =
{
	"Difficulty:    %s\n \n"
	"      Players:    %s",

	"Difficulty:  <-%s->\n \n"
	"      Players:    %s",

	"Difficulty:    %s\n \n"
	"      Players:  <-%s->",
};
const char* const Menu::SCORE_LIST_TYPE_STRINGS[NUMBER_OF_SCORE_LIST_TYPES] =
{
    "Highest Scores",
    "Fastest Wins",
    "Slowest Losses",
};
const char* const Menu::SCORE_SETTING_STRINGS[NUMBER_OF_SCORE_SETTINGS] =
{
	"Difficulty:    %s\n \n"
	"Score Type:    %s",
    "Difficulty:  <-%s->\n \n"
	"Score Type:    %s",
	"Difficulty:    %s\n \n"
	"Score Type:  <-%s->",
};
const char* const Menu::SPEED_STRINGS[NUMBER_OF_SPEEDS] =
{
	"Easy",
	"Average",
	"Hard",
};

// 2D Coordinate constants
const XYPair Menu::EXIT_MESSAGE_LOCATION =
{
    350,
    FIRST_LINE_Y + ( LINE_SEPARATION * 4 )
};
const XYPair Menu::MENU_STATE_STRING_LOCATION = { 480, FIRST_LINE_Y };
const XYPair Menu::PLAYER_HINT_LOCATION =
{
    240,
    FIRST_LINE_Y + ( LINE_SEPARATION * 10 )
};
const XYPair Menu::PLAY_MESSAGE_LOCATION =
{
    300,
    FIRST_LINE_Y + ( LINE_SEPARATION * 2 )
};
const XYPair Menu::PLAY_SETTINGS_LOCATION =
{
    325,
    FIRST_LINE_Y + ( LINE_SEPARATION * 6 )
};
const XYPair Menu::SCORE_SETTINGS_LOCATION =
{
    500,
    FIRST_LINE_Y + ( LINE_SEPARATION * 2 )
};

// Keyboard key array constants
const int Menu::CONFIRM_KEYS[CONFIRM_KEY_COUNT] =
{
    KEY_SPACE,
    KEY_ENTER,
};
const int Menu::DOWN_KEYS[DOWN_KEY_COUNT] =
{
    KEY_DOWN,
    KEY_PAGEDOWN,
};
const int Menu::EXIT_KEYS[EXIT_KEY_COUNT] =
{
    KEY_ESC,
    KEY_END,
};
const int Menu::LEFT_KEYS[LEFT_KEY_COUNT] =
{
    KEY_LEFT,
    KEY_BACKSPACE,
};
const int Menu::PRESSABLE_KEYS[PRESSABLE_KEY_COUNT] =
{
	KEY_ENTER,
    KEY_SPACE,
    KEY_ESC,
    KEY_END,
    KEY_LEFT,
    KEY_BACKSPACE,
    KEY_RIGHT,
    KEY_TAB,
    KEY_UP,
    KEY_PAGEUP,
    KEY_DOWN,
    KEY_PAGEDOWN,
};
const int Menu::RIGHT_KEYS[RIGHT_KEY_COUNT] =
{
    KEY_RIGHT,
    KEY_TAB,
};
const int Menu::UP_KEYS[UP_KEY_COUNT] =
{
    KEY_UP,
    KEY_PAGEUP,
};

// Constructor instantiates members in initializer list
Menu::Menu( ScoreListType& a_reDisplayListType,
		    Speed& a_reGameSpeed,
		    HighScores& a_roHighScores,
		    HumanPlayers& a_reHumanPlayers,
		    bool& a_rbKeyPressed )
	: m_reDisplayListType( a_reDisplayListType ),
      m_reGameSpeed( a_reGameSpeed ),
	  m_roHighScores( a_roHighScores ),
	  m_reHumanPlayers( a_reHumanPlayers ),
	  m_rbKeyPressed( a_rbKeyPressed ),
	  m_eMenuState( PLAY ),
	  m_ePlaySetting( PLAY_MAIN ),
      m_bProgramStartup( true ),
	  m_eScoreSetting( SCORE_MAIN )
{
}

// Draw the quit confirmation screen.
void Menu::DrawExitMenu()
{
    DrawMenuStateString( true );
    DrawMultilineString( EXIT_MESSAGE,
                         (int)EXIT_MESSAGE_LOCATION.x,
                         (int)EXIT_MESSAGE_LOCATION.y );
}

// Draw the main menu tabs
void Menu::DrawMenuStateString( bool a_bFocusOnMainMenu )
{
    unsigned int uiIndex = m_eMenuState * 2;
    if( a_bFocusOnMainMenu )
    {
        uiIndex++;
    }
    DrawString( MENU_STATE_STRINGS[uiIndex],
                (int)MENU_STATE_STRING_LOCATION.x,
                (int)MENU_STATE_STRING_LOCATION.y );
}

// Draw the play settings menu.
void Menu::DrawPlayMenu()
{
    // Draw main menu and basic "press ENTER or SPACE to play" message
    DrawMenuStateString( m_ePlaySetting == PLAY_MAIN );
    DrawMultilineString( PLAY_MESSAGE,
                         (int)PLAY_MESSAGE_LOCATION.x,
                         (int)PLAY_MESSAGE_LOCATION.y );

    // Draw settings
    const unsigned int uiBufferSize = PLAY_SETTINGS_BUFFER_SIZE;
    char acBuffer[uiBufferSize];
    sprintf_s( acBuffer,
               uiBufferSize,
               PLAY_SETTING_STRINGS[m_ePlaySetting],
               SPEED_STRINGS[m_reGameSpeed],
               HUMAN_PLAYER_STRINGS[m_reHumanPlayers] );
    DrawMultilineString( acBuffer,
                         (int)PLAY_SETTINGS_LOCATION.x,
                         (int)PLAY_SETTINGS_LOCATION.y );

    // Draw player control instructions
    sprintf_s( acBuffer,
               uiBufferSize,
               PLAYER_HINT,
               m_reHumanPlayers != RIGHT ? LEFT_PLAYER_HINT : "",
               m_reHumanPlayers != LEFT ? RIGHT_PLAYER_HINT : "" );
    DrawMultilineString( acBuffer,
                         (int)PLAYER_HINT_LOCATION.x,
                         (int)PLAYER_HINT_LOCATION.y );
}

// Draw the . 
void Menu::DrawScoresMenu()
{
    // Draw main menu
    DrawMenuStateString( m_eScoreSetting == SCORE_MAIN );

    // Draw settings
    const unsigned int uiBufferSize = SCORE_SETTINGS_BUFFER_SIZE;
    char acBuffer[uiBufferSize];
    sprintf_s( acBuffer,
               uiBufferSize,
               SCORE_SETTING_STRINGS[m_ePlaySetting],
               SPEED_STRINGS[m_reGameSpeed],
               SCORE_LIST_TYPE_STRINGS[m_reDisplayListType] );
    DrawMultilineString( acBuffer,
                         (int)SCORE_SETTINGS_LOCATION.x,
                         (int)SCORE_SETTINGS_LOCATION.y );

    // Draw scores
    m_roHighScores.Draw();
}

// Set the menu state (when entering the menu) to either PLAY or SCORES,
// depending on whether this is program startup or just the menu displayed after
// a match.
void Menu::Enter()
{
	if( !m_bProgramStartup )
	{
		// If this isn't the first time we've entered the menu (that is, any
		// time other than program startup), set the menu to show scores.
		m_eMenuState = SCORES;
	}
    else
    {
    	// Otherwise, leave it in its initial state of PLAY and turn off the
        // program startup flag.
        m_bProgramStartup = false;
    }

    // Make sure the main menu is the initial focus.
    m_ePlaySetting = PLAY_MAIN;
    m_eScoreSetting = SCORE_MAIN;
}

// Are any of the keys that interact with the menu pressed?
Menu::KeyPressAction Menu::GetKeyPressAction()
{
    // Are any of the keys physically down?
    bool bKeyDown = IsOneOfTheseKeysDown(PRESSABLE_KEYS, PRESSABLE_KEY_COUNT);

    // Is this just the continuation of a prior keypress?
    if( m_rbKeyPressed && !bKeyDown )
    {
        m_rbKeyPressed = false;
    }
    // Or is it a new keypress?
    else if( !m_rbKeyPressed && bKeyDown )
    {
        // Should we go to the exit screen?
        if( IsOneOfTheseKeysDown( EXIT_KEYS, EXIT_KEY_COUNT ) )
        {
            return GO_TO_EXIT;
        }

        // Should we confirm playing a game or exiting?
        if( IsOneOfTheseKeysDown( CONFIRM_KEYS, CONFIRM_KEY_COUNT ) )
        {
            return CONFIRM;
        }

        // Which directions have their corresponding keys pressed?
        bool bDown = IsOneOfTheseKeysDown( DOWN_KEYS, DOWN_KEY_COUNT );
        bool bLeft = IsOneOfTheseKeysDown( LEFT_KEYS, LEFT_KEY_COUNT );
        bool bRight = IsOneOfTheseKeysDown( RIGHT_KEYS, RIGHT_KEY_COUNT );
        bool bUp = IsOneOfTheseKeysDown( UP_KEYS, UP_KEY_COUNT );

        // Do any of the directional actions cancel each other?
        if( bDown && bUp )
        {
            bDown = false;
            bUp = false;
        }
        if( ( bLeft && bRight ) || bDown || bUp )
        {
            bLeft = false;
            bRight = false;
        }

        // return directional action, if any are selected
        if( bDown )
        {
            return GO_DOWN;
        }
        if( bLeft )
        {
            return GO_LEFT;
        }
        if( bRight )
        {
            return GO_RIGHT;
        }
        if( bUp )
        {
            return GO_UP;
        }
    }

    // Or are there no keys pressed at all?
    return NONE;
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
			DrawPlayMenu();
			eNextGameState = UpdatePlayMenu();
			break;
		}
	case EXIT:
		{
			DrawExitMenu();
			eNextGameState = UpdateExitMenu();
			break;
		}
	case SCORES:
	default:
		{
			DrawScoresMenu();
			UpdateScoresMenu();
			break;
		}
	}	// end of switch statement
	return eNextGameState;
}

// Given a number between zero and a given maximum, add or subtract one, then
// add or subtract the maximum to put the result back between zero and the
// maximum.
unsigned int Menu::Rollover( const unsigned int a_uiPlace,
                             const unsigned int a_uiSize,
                             const bool a_bForward )
{
    unsigned int uiResult = a_uiPlace;
    uiResult += a_bForward ? 1 : ( a_uiSize - 1 );
    uiResult %= a_uiSize;
    return uiResult;
}

// Process left or right change on play menu
void Menu::SideScrollPlayMenu( bool a_bForward )
{
    switch( m_ePlaySetting )
    {
    case PLAY_MAIN: m_eMenuState = a_bForward ? SCORES : EXIT; break;
    case PLAY_SPEED:
        {
            m_reGameSpeed = (Speed)Rollover( m_reGameSpeed,
                                             NUMBER_OF_SPEEDS,
                                             a_bForward );
            break;
        }
    case PLAY_HUMANS:
        {
            m_reHumanPlayers =
                (HumanPlayers)Rollover( m_reHumanPlayers,
                                        NUMBER_OF_HUMAN_PLAYER_OPTIONS,
                                        a_bForward );
            break;
        }
    default: break;
    }
}

// Process left or right change on scores menu
void Menu::SideScrollScoresMenu( bool a_bForward )
{
    switch( m_eScoreSetting )
    {
    case SCORE_MAIN: m_eMenuState = a_bForward ? EXIT : PLAY; break;
    case SCORE_SPEED:
        {
            m_reGameSpeed = (Speed)Rollover( m_reGameSpeed,
                                             NUMBER_OF_SPEEDS,
                                             a_bForward );
            break;
        }
    case SCORE_TYPE:
        {
            m_reDisplayListType =
                (ScoreListType)Rollover( m_reDisplayListType,
                                         NUMBER_OF_SCORE_LIST_TYPES,
                                         a_bForward );
            break;
        }
    default: break;
    }
}

// Keep track of user input and return MENU or END, as appropriate.
GameState Menu::UpdateExitMenu()
{
    switch( GetKeyPressAction() )
    {
    case CONFIRM:
    case GO_TO_EXIT: return END; break;  // break in case the code changes.
    case GO_LEFT: m_eMenuState = SCORES; break;
    case GO_RIGHT: m_eMenuState = PLAY; break;
    case GO_UP:
    case GO_DOWN:
    case NONE:
    default: break;
    }
    return MENU;
}

// Keep track of user input and return MENU or START_MATCH as appropriate.
GameState Menu::UpdatePlayMenu()
{
    switch( GetKeyPressAction() )
    {
    case CONFIRM: return START_MATCH; break;  // break in case the code changes.
    case GO_TO_EXIT: m_eMenuState = EXIT; break;
    case GO_LEFT: SideScrollPlayMenu( false ); break;
    case GO_RIGHT: SideScrollPlayMenu( true ); break;
    case GO_UP:
        {
            m_ePlaySetting = (PlaySetting)Rollover( m_ePlaySetting,
                                                    NUMBER_OF_PLAY_SETTINGS,
                                                    false );
            break;
        }
    case GO_DOWN:
        {
            m_ePlaySetting = (PlaySetting)Rollover( m_ePlaySetting,
                                                    NUMBER_OF_PLAY_SETTINGS,
                                                    true );
            break;
        }
    case NONE:
    default: break;
    }
    return MENU;
}

// Keep track of user input. 
void Menu::UpdateScoresMenu()
{
    switch( GetKeyPressAction() )
    {
    case GO_TO_EXIT: m_eMenuState = EXIT; break;
    case GO_LEFT: SideScrollScoresMenu( false ); break;
    case GO_RIGHT: SideScrollScoresMenu( true ); break;
    case GO_UP:
        {
            m_eScoreSetting = (ScoreSetting)Rollover( m_eScoreSetting,
                                                      NUMBER_OF_SCORE_SETTINGS,
                                                      false );
            break;
        }
    case GO_DOWN:
        {
            m_eScoreSetting = (ScoreSetting)Rollover( m_eScoreSetting,
                                                      NUMBER_OF_SCORE_SETTINGS,
                                                      true );
            break;
        }
    case CONFIRM:
    case NONE:
    default: break;
    }
}
