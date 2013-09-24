/******************************************************************************
 * File:               Game.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       September 17, 2013
 * Description:        Implementations for methods of the Game class.
 * Last Modified:      September 23, 2013
 * Last Modification:  Added pause state.
 ******************************************************************************/

#include "Game.h"
#include "EnumsAndStructs.h"
#include "Sprite.h"
#include "Ball.h"
#include "Player.h"
#include "AIE.h"
#include "StopWatch.h"
#include "HighScores.h"
#include <algorithm>	// for std::max(int a, int b)
#include <cstdlib>	// for rand and abs

const char* const Game::BACKGROUND_TEXTURE_NAME = "./images/tennis_court.png";
const char* const Game::GAME_TITLE = "Pong, starring Venus and Serena Williams!";
const XYPair Game::LEFT_PLAYER_START_POSITION = {240,396};
const int Game::MENU_KEYS[MENU_KEY_COUNT] =
{
	KEY_ESC,
	KEY_HOME,
	KEY_END,
	KEY_BACKSPACE
};
const char* const Game::OVERTIME_STRING =
	"Time: It's over NINE-THOUSAAAND!!! (seconds)";
const double Game::OVERTIME_SECONDS = 9000.0;	// What? Nine-thousand?!
const int Game::PAUSE_KEYS[PAUSE_KEY_COUNT] =
{
	KEY_PAUSE,
	KEY_ESC,
	KEY_HOME,
	KEY_END,
	KEY_BACKSPACE,
	KEY_SPACE,
	KEY_ENTER
};
const char* const Game::PAUSE_TEXTURE_NAME = "./images/shade.png";
const int Game::RESUME_KEYS[RESUME_KEY_COUNT] =
{
	KEY_PAUSE,
	KEY_SPACE,
	KEY_ENTER
};
const XYPair Game::RIGHT_PLAYER_START_POSITION = {960,396};
const char* const Game::SHADE_TEXTURE_NAME = "./images/shade.png";

// Constructor
Game::Game()
	: m_oBackgroundSprite( BACKGROUND_TEXTURE_NAME,
						   SCREEN_WIDTH,
						   SCREEN_HEIGHT,
						   DEFAULT_X_Y_PAIR,
						   false ),
	  m_oLeftPlayer( m_oBall,
					 Player::LEFT,
					 LEFT_PLAYER_START_POSITION,
					 MIN_Y,
					 MAX_Y ),
	  m_bKeyPressed( false ),
	  m_oRightPlayer( m_oBall,
					  Player::RIGHT,
					  RIGHT_PLAYER_START_POSITION,
					  MIN_Y,
					  MAX_Y ),
	  m_oScreenShadeSprite( SHADE_TEXTURE_NAME,
							SCREEN_WIDTH,
							SCREEN_HEIGHT,
							DEFAULT_X_Y_PAIR,
							false ),
	  m_poServingPlayer( RandomPlayer() ),
	  m_eGameSpeed( MEDIUM ),
	  m_eHumanPlayers( BOTH ),
	  m_eState( START_MATCH )	// TODO: change this to ENTER_MENU once the menu has been implemented
{
	// Nothing else to do here, since all members either have a default
	//   constructor or have been instantiated in the initializer list.
}

// Find and react to collisions
void Game::CheckCollisions()
{
	if ( m_oBall.CanRebound( MIN_Y, MAX_Y ) )
	{
		m_oBall.BounceY();
	}
	if ( m_oLeftPlayer.CanHit() )
	{
		m_oLeftPlayer.Hit();
	}
	if ( m_oRightPlayer.CanHit() )
	{
		m_oRightPlayer.Hit();
	}
}

// return the next game state
GameState Game::CheckForWinners( bool a_bBackgroundMatch )
{
	if ( PlayerScores() )
	{
		if ( MatchOver() )
		{
			if ( !a_bBackgroundMatch )
			{
				m_oHighScores.RecordScore();
			}
			return START_MATCH;	// TODO: change to ENTER_MENU once menu is implemented
		}
		return START_ROUND;
	}
	return PLAY_GAME;
}

// Draw the pause screen.
void Game::DrawPauseScreen()
{
	// Clear the screen
	ClearScreen();

	// Draw the game sprites...
	Sprite* apoGameSprites[] =
	{
		&m_oBackgroundSprite,
		&m_oLeftPlayer,
		&m_oRightPlayer,
		&m_oBall,
		&m_oScreenShadeSprite
	};
	for each ( Sprite* poSprite in apoGameSprites )
	{
		poSprite->Draw();
	}

	// Draw scores and time
	DrawScores();

	// TODO: draw pause message
}

// Draw scores and time
void Game::DrawScores()
{
	// create a buffer to hold text
	const unsigned int cuiBufferSize = 20;
	char acBuffer[cuiBufferSize];

	// Draw the left player's score
	m_oLeftPlayer.PrintScore( acBuffer, cuiBufferSize );
	DrawString( acBuffer, LEFT_SCORE_X, SCORE_Y );

	// Draw the right player's score
	m_oRightPlayer.PrintScore( acBuffer, cuiBufferSize );
	DrawString( acBuffer, RIGHT_SCORE_X, SCORE_Y );

	// Draw the match time
	if( m_oPlayTime.GetSeconds() > OVERTIME_SECONDS )
	{
		DrawString( OVERTIME_STRING, OVERTIME_X, TIME_Y );
	}
	else
	{
		m_oPlayTime.PrintTime( acBuffer, cuiBufferSize );
		DrawString( acBuffer, TIME_X, TIME_Y );
	}
}

// Set up the components of the menu
void Game::EnterMenu()
{
	// Set up the AI-only game playing in the background
	m_oLeftPlayer.Reset();
	m_oRightPlayer.Reset();
	m_oLeftPlayer.SetMode( Player::AI );
	m_oRightPlayer.SetMode( Player::AI );
	m_poServingPlayer = RandomPlayer();

	// TODO: other menu startup tasks
}

// If at least one of the given keys is pressed, return true
bool Game::IsOneOfTheseKeysDown( const int* const ac_pciKeys,
								 const unsigned int ac_uiKeyCount )
{
	const int* pciKey = ac_pciKeys;
	for( unsigned int ui = 0; ui < ac_uiKeyCount; ++ui )
	{
		if( IsKeyDown( *pciKey++ ) )
		{
			return true;
		}
	}
	return false;
}

// Is the match over?  It's over when one player has at least 4 points and is
//   ahead of the other by at least 2.
bool Game::MatchOver() const
{
	unsigned int uiLeftScore = m_oLeftPlayer.GetScore();
	unsigned int uiRightScore = m_oRightPlayer.GetScore();
	return ( ( std::max( uiLeftScore, uiRightScore ) >= 4 ) &&
			 ( abs( (int)uiLeftScore - (int)uiRightScore ) >= 2 ) );
}

// Run the program while in the menu
GameState Game::Menu()
{
	// Run the AI vs. AI match in the background. Don't show the time.
	GameState eState = PlayGame( true );
	if ( eState != PLAY_GAME )
	{
		if( eState != START_ROUND )
		{
			m_oLeftPlayer.Reset();
			m_oRightPlayer.Reset();
		}
		m_poServingPlayer->Serve();
	}

	// Shade the background match, since it's not the focus here.
	m_oScreenShadeSprite.Draw();

	// TODO: draw actual menu, return START_MATCH or END if appropriate.
	m_bKeyPressed = false;

	return MENU;
}

// Update ball and player positions, draw everything, detect and react to
//   collisions, and return the next game state.
GameState Game::PlayGame( bool a_bBackgroundMatch )
{
	bool bPaused = IsOneOfTheseKeysDown( PAUSE_KEYS, PAUSE_KEY_COUNT );
	if( !m_bKeyPressed && bPaused )
	{
		m_bKeyPressed = true;
		return ENTER_PAUSE;
	}
	if( m_bKeyPressed && !bPaused)
	{
		m_bKeyPressed = false;
	}
	UpdateAndDrawSprites();
	DrawScores();
	CheckCollisions();
	return CheckForWinners( a_bBackgroundMatch );
}

// Checks to see if the ball is out of bounds.  if it is, updates winning
//   player's score and sets said player as the player to serve at the start of
//   the next round, then returns true.
bool Game::PlayerScores()
{
	float fBallX = m_oBall.GetPosition().x;
	if ( ( fBallX < LEFT_PLAYER_LOSES_X ) || ( RIGHT_PLAYER_LOSES_X < fBallX ) )
	{
		if ( fBallX < LEFT_PLAYER_LOSES_X )
		{
			m_poServingPlayer = &m_oRightPlayer;
		}
		else
		{
			m_poServingPlayer = &m_oLeftPlayer;
		}
		m_poServingPlayer->IncrementScore();
		m_oBall.Hide();
		return true;
	}
	return false;
}

// Pick one of the players at random
Player* Game::RandomPlayer()
{
	return ( rand()%2 == 0 ) ? &m_oLeftPlayer : &m_oRightPlayer;
}

// Run the game as a whole, calling functions according to game state and
//   changing states
bool Game::Run()
{
	switch ( m_eState )
	{
	// Set up the menu...
	case ENTER_MENU:
		{
			EnterMenu();
			m_eState = MENU;	// ... then fall through to the menu
		}

	// Run the menu
	case MENU:
		{
			// either stay in MENU or go to END or START_MATCH
			m_eState = Menu();
			break;
		}

	// Set up a match...
	case START_MATCH:
		{
			StartMatch();
			m_eState = START_ROUND;	// ... then fall through to start a round
		}

	// Set up a round...
	case START_ROUND:
		{
			StartRound();
			m_eState = PLAY_GAME;	// ... then fall through to start playing
		}
		
	// Play the game
	case PLAY_GAME:
		{
			// either stay in PLAY_GAME or go to START_ROUND or ENTER_MENU
			m_eState = PlayGame();
			break;
		}

	// Draw the Pause screen...
	case ENTER_PAUSE:
		{
			m_oPlayTime.Stop();
			m_eState = PAUSED;	// ... then fall through to the pause state proper
		}

	// Game is paused until the player presses ESC, SPACE, or ENTER
	case PAUSED:
		{
			DrawPauseScreen();
			m_eState = WaitForUnpause();
			break;
		}

	// If the state isn't one of the defined ones, quit
	default:
		{
			m_eState = END;
			break;
		}
	}	// end of switch statement

	// Return true as long as the user hasn't chosen to exit the program
	return m_eState != END;
}

// Destroy all the sprites, perform any other cleanup tasks that have to be done
//   before the framework shuts down.
void Game::Shutdown()
{
	Sprite* apoSprites[] =
	{
		&m_oBackgroundSprite,
		&m_oLeftPlayer,
		&m_oRightPlayer,
		&m_oBall,
		&m_oScreenShadeSprite
	};
	for each ( Sprite* poSprite in apoSprites )
	{
		poSprite->Destroy();
	}
	m_oHighScores.Shutdown();
}

// Set everything up for a new match
void Game::StartMatch()
{
	// Set left player
	m_oLeftPlayer.Reset();
	if ( m_eHumanPlayers != RIGHT )
	{
		m_oLeftPlayer.SetMode( Player::HUMAN );
	}
	else
	{
		m_oLeftPlayer.SetMode( Player::AI );
	}
	
	// Set right player
	m_oRightPlayer.Reset();
	if ( m_eHumanPlayers != LEFT )
	{
		m_oRightPlayer.SetMode( Player::HUMAN );
	}
	else
	{
		m_oRightPlayer.SetMode( Player::AI );
	}

	// Choose which player should serve
	switch(m_eHumanPlayers)
	{
	case LEFT: m_poServingPlayer = &m_oRightPlayer; break;
	case RIGHT: m_poServingPlayer = &m_oLeftPlayer; break;
	case BOTH:	// fall through
	default: m_poServingPlayer = RandomPlayer(); break;
	}

	// Set the match time to zero
	m_oPlayTime.Clear();
	m_oPlayTime.Start();
}

// Perform all start-of-round tasks
void Game::StartRound()
{
	m_poServingPlayer->Serve();
}

// Update sprite positions and draw them
void Game::UpdateAndDrawSprites()
{
	// Clear the screen
	ClearScreen();

	// Put all the sprites to draw into an array...
	Sprite* apoGameSprites[] =
	{
		&m_oBackgroundSprite,
		&m_oLeftPlayer,
		&m_oRightPlayer,
		&m_oBall
	};

	// ... and loop through them to update and draw
	float fDeltaT = GetDeltaTime();
	for each ( Sprite* poSprite in apoGameSprites )
	{
		poSprite->Update( fDeltaT * m_eGameSpeed );
		poSprite->Draw();
	}
}

// Check for one of the key presses signalling the end of the paused state and
// return the appropriate next game state.
GameState Game::WaitForUnpause()
{
	bool bMenu = IsOneOfTheseKeysDown( MENU_KEYS, MENU_KEY_COUNT );
	bool bPlay = IsOneOfTheseKeysDown( RESUME_KEYS, RESUME_KEY_COUNT );

	// If the initial keypress isn't over, stay paused
	if( m_bKeyPressed )
	{
		// Check to see if it should be over
		if( !bMenu && !bPlay )
		{
			m_bKeyPressed = false;
		}
		return PAUSED;
	}

	// If either a menu key or a resume key, but not one of both, is pressed...
	if( bMenu != bPlay )
	{
		m_bKeyPressed = true;

		// If any of the keys for ending the game and returning to the menu are
		// pressed, go to the menu without entering any scores.
		if( bMenu )
		{
			return ENTER_MENU;
		}

		// If any of the keys for resuming the game are pressed, go back to the
		// game.
		m_oPlayTime.Start();
		return PLAY_GAME;
	}

	// Otherwise, remain paused.
	return PAUSED;
}
