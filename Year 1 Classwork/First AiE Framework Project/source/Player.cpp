/******************************************************************************
 * File:               Player.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       September 11, 2013
 * Description:        Implementation for methods of the Player class.
 * Last Modified:      September 23, 2013
 * Last Modification:  Formatting to meet coding standards.
 ******************************************************************************/

#include "Player.h"
#include "AIE.h"
#include <cstdio>	// for sprintf_s
#include <cstdlib>	// for rand

const char* const Player::LEFT_PLAYER_NAME = "Serena";
const char* const Player::LEFT_TEXTURE_NAME = "./images/serena_williams.png";
const char* const Player::RIGHT_PLAYER_NAME = "Venus";
const char* const Player::RIGHT_TEXTURE_NAME = "./images/venus_williams.png";
const char* const Player::SCORE_FORMAT = "%s: %d";

// Constructor instantiates all the members in the initializer list.
Player::Player( Ball& a_roBall,
				const Side ac_eSide,
				const XYPair& a_oPosition,
				const int ac_iMinY,
				const int ac_iMaxY )
	: Sprite( ac_eSide == LEFT ? LEFT_TEXTURE_NAME : RIGHT_TEXTURE_NAME,
			  PLAYER_WIDTH,
			  PLAYER_HEIGHT,
			  a_oPosition ),
	  m_roBall( a_roBall ),
	  mc_iMaxY( ac_iMaxY ),
	  mc_iMinY( ac_iMinY ),
	  m_eMode( FROZEN ),
	  m_oPosition( a_oPosition ),
	  m_uiScore( 0 ),
	  mc_oStartPosition( a_oPosition ),
	  mc_eSide( ac_eSide )
{
}

// Is the ball heading towards the player?
bool Player::BallIsIncoming() const
{
	// Get the ball's horizontal position and velocity.
	float fBallPositionX = m_roBall.GetPosition().x;
	float fBallVelocityX = m_roBall.GetVelocity().x;

	// Get the distance between the center of the player and the center of the
	// ball when in contact.
	float fOffsetX = (float) (PADDLE_WIDTH + m_roBall.GetDiameter() ) / 2;

	// If the player is on the left and the ball is moving left, return false if
	// the ball has moved past the player and true if it hasn't yet.
	if ( mc_eSide == LEFT && fBallVelocityX < 0 )
	{
		return ( fBallPositionX > ( m_oPosition.x - fOffsetX ) );
	}

	// If the player is on the right and the ball is moving right, return false
	// if the ball has moved past the player and true if it hasn't yet.
	if ( mc_eSide == RIGHT && fBallVelocityX > 0 )
	{
		return ( fBallPositionX < ( m_oPosition.x + fOffsetX ) );
	}

	// Otherwise, return false.
	return false;
}

// Can the player hit the ball?
bool Player::CanHit() const
{
	// If the ball isn't heading toward the player, the answer is obviously no.
	if ( !BallIsIncoming() )
	{
		return false;
	}

	// Get the ball's position
	XYPair oBallPosition = m_roBall.GetPosition();

	// Get the horizontal and vertical distances between the center of the
	// player and the center of the ball when the two are touching.
	float fOffsetX = (float)( PADDLE_WIDTH + m_roBall.GetDiameter() ) / 2;
	float fOffsetY = (float)( PADDLE_HEIGHT + m_roBall.GetDiameter() ) / 2;

	// Get the boundaries within which the ball can be hit by the player.
	float fMinX = m_oPosition.x - fOffsetX;
	float fMaxX = m_oPosition.x + fOffsetX;
	float fMinY = m_oPosition.y - fOffsetY;
	float fMaxY = m_oPosition.y + fOffsetY;

	// Is the ball within said boundaries?
	return ( fMinX <= oBallPosition.x && oBallPosition.x <= fMaxX &&
			 fMinY <= oBallPosition.y && oBallPosition.y <= fMaxY );
}

// Clear the player's score and move it back to its starting position.
void Player::Reset()
{
	m_uiScore = 0;
	m_oPosition = mc_oStartPosition;
}

// Do the actual work of drawing the player sprite.
void Player::DrawTasks() const
{
	MoveSprite( m_cuiSpriteID, m_oPosition.x, m_oPosition.y );
	DrawSprite( m_cuiSpriteID );
}

// Name accessor
const char* const Player::GetPlayerName() const
{
	return mc_eSide == LEFT ? LEFT_PLAYER_NAME : RIGHT_PLAYER_NAME;
}

// Score accessor
unsigned int Player::GetScore() const
{
	return m_uiScore;
}

// Have the player hit the ball.
void Player::Hit() const
{
	// The ball bounces horizontally, heading towards the other player.
	m_roBall.BounceX();

	// If the ball is outside these bounds, then it is hitting the edge of the
	// player.
	float fMinY = m_oPosition.y - ( (float)PADDLE_HEIGHT / 2 );
	float fMaxY = m_oPosition.y + ( (float)PADDLE_HEIGHT / 2 );

	// Get the ball's vertical position and velocity.
	float fBallPosY = m_roBall.GetPosition().y;
	float fBallVelY = m_roBall.GetVelocity().y;

	// If the ball hits one of the player's horizontal edges directly, then its
	// entire velocity is reversed, not just the horizontal component.
	if ( ( 0 < fBallVelY && fBallPosY < fMinY ) ||
		 ( fMaxY < fBallPosY && fBallVelY < 0 ) )
	{
		m_roBall.BounceY();
	}
}

// Increase the player's score
void Player::IncrementScore()
{
	m_uiScore++;
}

// Write the player's score to a char array in "PlayerName: Score" format
void Player::PrintScore( char* a_pcBuffer, unsigned int a_uiBufferSize )
{
	sprintf_s( a_pcBuffer,
			   a_uiBufferSize,
			   SCORE_FORMAT,
			   GetPlayerName(),
			   GetScore() );
}

// Serve the ball
void Player::Serve() const
{
	XYPair oServePosition = m_oPosition;
	unsigned int uiBallDiameter = m_roBall.GetDiameter();

	// Serve from the edge of the player facing the field, not from the center
	// of the player.
	if ( mc_eSide == LEFT )
	{
		oServePosition.x += (float)( PADDLE_WIDTH + uiBallDiameter ) / 2;
	}
	else
	{
		oServePosition.x -= (float)( PADDLE_WIDTH + uiBallDiameter ) / 2;
	}

	// Serve towards the other player, angled up or down by random chance.
	XYPair oServeVelocity =
	{
		mc_eSide == LEFT ? 1.0f : -1.0f,
		rand()%2 == 0 ? 1.0f : -1.0f
	};
	m_roBall.Serve( oServePosition, oServeVelocity );
}

// Mode mutator
void Player::SetMode( Mode a_eMode )
{
	m_eMode = a_eMode;
}

// Update the player's position based on the elapsed time and the human or AI
// controller's input.
void Player::Update( float a_fDeltaT )
{
	switch( GetDirection() )
	{
	case UP: m_oPosition.y -= a_fDeltaT; break;
	case DOWN: m_oPosition.y += a_fDeltaT; break;
	default: break;
	}
}

// Get the human or AI controller's input, depending on the player mode.
Player::MotionDirection Player::GetDirection() const
{
	MotionDirection eMotion = NONE;
	switch( m_eMode )
	{
	case AI: eMotion = GetAIDirection(); break;
	case HUMAN: eMotion = GetHumanDirection(); break;
	default: break;
	}
	return eMotion;
}

// Get the AI controller's input
Player::MotionDirection Player::GetAIDirection() const
{
	// Don't move if the ball is moving away.
	if( !BallIsIncoming() )
	{
		return NONE;
	}

	// Get the ball's vertical position
	float fBallPositionY = m_roBall.GetPosition().y;

	// If the center of the ball is above the center of the player, move up
	// unless the player is already as far up as it can go.
	float fMinY = mc_iMinY + ( (float)PADDLE_HEIGHT / 2 );
	if( ( fBallPositionY < m_oPosition.y ) && ( m_oPosition.y > fMinY ) )
	{
		return UP;
	}

	// If the center of the ball is below the center of the player, move down
	// unless the player is already as far down as it can go.
	float fMaxY = mc_iMaxY - ( (float)PADDLE_HEIGHT / 2 );
	if( ( fBallPositionY > m_oPosition.y ) && ( m_oPosition.y < fMaxY ) )
	{
		return DOWN;
	}

	// Otherwise, don't move.
	return NONE;
}

// Get a human controller's input
Player::MotionDirection Player::GetHumanDirection() const
{
	// Is the key indicating "down" for this side pressed?
	bool bDown = IsKeyDown( mc_eSide == LEFT ? LEFT_DOWN_KEY : RIGHT_DOWN_KEY );
	
	// Is the key indicating "up" for this side pressed?
	bool bUp = IsKeyDown( mc_eSide == LEFT ? LEFT_UP_KEY : RIGHT_UP_KEY );

	// If one or the other is pressed, but not both...
	if ( bUp != bDown )
	{
		// If only the "up" key for this side is pressed, move up unless the
		// player is already as far up as it can go.
		float fMinY = mc_iMinY + ( (float)PADDLE_HEIGHT / 2 );
		if (bUp && ( m_oPosition.y > fMinY ) )
		{
			return UP;
		}

		// If only the "down" key for this side is pressed, move down unless the
		// player is already as far up as it can go.
		float fMaxY = mc_iMaxY - ( (float)PADDLE_HEIGHT / 2 );
		if (bDown && ( m_oPosition.y < fMaxY) )
		{
			return DOWN;
		}
	}

	// Otherwise, don't move.
	return NONE;
}
