/******************************************************************************
 * File:               Game.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       September 17, 2013
 * Description:        Implementations for methods of the Game class.
 * Last Modified:      September 23, 2013
 * Last Modification:  Added pause state.
 ******************************************************************************/

#include "Game.h"
#include "Sprite.h"
#include "Ball.h"
#include "Player.h"
#include "AIE.h"
#include <algorithm>	// for std::max(int a, int b)
#include <cstdio>	// for sprintf_s
#include <cstdlib>	// for rand and abs

const char* const Game::BACKGROUND_TEXTURE_NAME = "./images/tennis_court.png";
const char* const Game::GAME_TITLE = "Pong, starring Venus and Serena Williams!";
const Sprite::XYPair Game::LEFT_PLAYER_START_POSITION = {240,396};
const int Game::MENU_KEYS[MENU_KEY_COUNT] =
{
	KEY_ESC,
	KEY_HOME,
	KEY_END,
	KEY_BACKSPACE
};
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
const int Game::RESUME_KEYS[RESUME_KEY_COUNT] =
{
	KEY_PAUSE,
	KEY_SPACE,
	KEY_ENTER
};
const Sprite::XYPair Game::RIGHT_PLAYER_START_POSITION = {960,396};
const char* const Game::SCORE_FORMAT = "%s: %d";
const char* const Game::TIME_FORMAT = "%d:%02d:%03d";

// Constructor
Game::Game()
	: m_oBackgroundSprite( BACKGROUND_TEXTURE_NAME,
						   SCREEN_WIDTH,
						   SCREEN_HEIGHT,
						   Sprite::DEFAULT_POSITION,
						   false ),
	  m_oLeftPlayer( m_oBall,
					 Player::LEFT,
					 LEFT_PLAYER_START_POSITION,
					 MIN_Y,
					 MAX_Y ),
	  m_oRightPlayer( m_oBall,
					  Player::RIGHT,
					  RIGHT_PLAYER_START_POSITION,
					  MIN_Y,
					  MAX_Y ),
	  m_poServingPlayer( RandomPlayer() ),
	  m_eGameSpeed( MEDIUM ),
	  m_eHumanPlayers( BOTH ),
	  m_fPlayTime( 0.0f ),
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
Game::GameState Game::CheckForWinners( bool a_bBackgroundMatch )
{
	if ( PlayerScores() )
	{
		if ( MatchOver() )
		{
			if ( !a_bBackgroundMatch )
			{
				// TODO: submit scores
			}
			return START_MATCH;	// TODO: change to ENTER_MENU once menu is implemented
		}
		return START_ROUND;
	}
	return PLAY_GAME;
}

// Draw the pause screen.  This only needs to be done once, since nothing on
// screen is updated while paused.
void Game::DrawPauseScreen()
{
	// TODO
}

// Draw scores and time
void Game::DrawScores( bool a_bBackgroundMatch )
{
	// create a buffer to hold text
	char acBuffer[15];

	// Draw the left player's score
	sprintf_s( acBuffer,
			   15,
			   SCORE_FORMAT,
			   m_oLeftPlayer.GetPlayerName(),
			   m_oLeftPlayer.GetScore() );
	DrawString( acBuffer, LEFT_SCORE_X, SCORE_Y );

	// Draw the right player's score
	sprintf_s( acBuffer,
			   15,
			   SCORE_FORMAT,
			   m_oRightPlayer.GetPlayerName(),
			   m_oRightPlayer.GetScore() );
	DrawString( acBuffer, RIGHT_SCORE_X, SCORE_Y );

	// If this is an actual game and not menu background, draw the match time
	if ( !a_bBackgroundMatch )
	{
		FormatPlayTime( acBuffer, 15, m_fPlayTime );
		DrawString( acBuffer, TIME_X, TIME_Y );
	}
}

// Set up the components of the menu
void Game::EnterMenu()
{
	// Set up the AI-only game playing in the background
	m_fPlayTime = 0.0f;
	m_oLeftPlayer.Reset();
	m_oRightPlayer.Reset();
	m_oLeftPlayer.SetMode( Player::AI );
	m_oRightPlayer.SetMode( Player::AI );
	m_poServingPlayer = RandomPlayer();

	// TODO: other menu startup tasks
}

// Write the time given in the float to the given char* string in
//   "minute:second.millisecond" format
void Game::FormatPlayTime( char* a_pcBuffer,
						   unsigned int a_uiBufferSize,
						   float a_fPlayTime )
{
	unsigned int uiMilliseconds = (unsigned int)( a_fPlayTime * 1000 );
	unsigned int uiSeconds = uiMilliseconds / 1000;
	uiMilliseconds %= 1000;
	unsigned int uiMinutes = uiSeconds / 60;
	uiSeconds %= 60;
	sprintf_s( a_pcBuffer,
			   a_uiBufferSize,
			   TIME_FORMAT,
			   uiMinutes,
			   uiSeconds,
			   uiMilliseconds );
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
Game::GameState Game::Menu()
{
	// Run the AI vs. AI match in the background. Don't show the time.
	GameState eState = PlayGame( false );
	if ( eState != PLAY_GAME )
	{
		if( eState != START_ROUND )
		{
			m_oLeftPlayer.Reset();
			m_oRightPlayer.Reset();
		}
		m_poServingPlayer->Serve();
	}

	// TODO: draw actual menu, return START_MATCH or END if appropriate.

	return MENU;
}

// Update ball and player positions, draw everything, detect and react to
//   collisions, and return the next game state.
Game::GameState Game::PlayGame( bool a_bBackgroundMatch )
{
	if( IsOneOfTheseKeysDown( PAUSE_KEYS, PAUSE_KEY_COUNT ) )
	{
		return ENTER_PAUSE;
	}
	UpdateAndDrawSprites();
	DrawScores( a_bBackgroundMatch );
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
			DrawPauseScreen();
			m_eState = PAUSED;	// ... then fall through to the pause state proper
		}

	// Game is paused until the player presses ESC, SPACE, or ENTER
	case PAUSED:
		{
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
	Sprite* apoSprites[4] =
	{
		&m_oBackgroundSprite,
		&m_oLeftPlayer,
		&m_oRightPlayer,
		&m_oBall
	};
	for each ( Sprite* poSprite in apoSprites )
	{
		poSprite->Destroy();
	}
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
	m_fPlayTime = 0.0f;
}

// Perform all start-of-round tasks
void Game::StartRound()
{
	m_poServingPlayer->Serve();
}

// Update sprite positions and draw them
void Game::UpdateAndDrawSprites()
{
	// keep track of total time for the match
	float fDeltaT = GetDeltaTime();
	m_fPlayTime += fDeltaT;

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
	for each ( Sprite* poSprite in apoGameSprites )
	{
		poSprite->Update( fDeltaT * m_eGameSpeed );
		poSprite->Draw();
	}
}

// Check for one of the key presses signalling the end of the paused state and
// return the appropriate next game state.
Game::GameState Game::WaitForUnpause()
{
	// If any of the keys for ending the game and returning to the menu are
	// pressed, go to the menu without entering any scores.
	if( IsOneOfTheseKeysDown( MENU_KEYS, MENU_KEY_COUNT ) )
	{
		return ENTER_MENU;
	}
	
	// If any of the keys for resuming the game are pressed, go back to the game.
	if( IsOneOfTheseKeysDown( RESUME_KEYS, RESUME_KEY_COUNT ) )
	{
		return PLAY_GAME;
	}

	// If none of those keys were pressed, remain paused.
	return PAUSED;
}
