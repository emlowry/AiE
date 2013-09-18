/******************************************************************************
 * File:               Ball.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       September 16, 2013
 * Description:        Implementations for methods of the Ball class.
 * Last Modified:      September 18, 2013
 * Last Modification:  Added comments.
 ******************************************************************************/

#include "Ball.h"
#include "AIE.h"

const char* const Ball::BALL_TEXTURE_NAME = "./images/tennis_ball.png";

// Default constructor creates a default ball sprite
Ball::Ball()
	: Sprite( BALL_TEXTURE_NAME, DEFAULT_BALL_DIAMETER, DEFAULT_BALL_DIAMETER ),
	  m_fRotation( 0.0 ),
	  m_bVisible( false )
{
	// nothing else to do here
}

// Rebound off a horizontal surface
void Ball::BounceX()
{
	m_oVelocity.x *= -1;
}

// Rebound off a vertical surface
void Ball::BounceY()
{
	m_oVelocity.y *= -1;
}

// Can the ball rebound off the given horizontal boundaries?
bool Ball::CanRebound( const int ac_iMinY, const int ac_iMaxY ) const
{
	float fMinY = ac_iMinY + ( (float)GetDiameter() / 2 );
	float fMaxY = ac_iMaxY - ( (float)GetDiameter() / 2 );
	return ( ( ( m_oVelocity.y < 0 ) && ( m_oPosition.y <= fMinY ) ) ||
			 ( ( m_oVelocity.y > 0 ) && ( m_oPosition.y >= fMaxY ) ) );
}

// If the ball is visible, rotate it
void Ball::DrawTasks() const {
	if ( m_bVisible )
	{
		RotateSprite( m_cuiSpriteID, m_fRotation );
		MoveSprite( m_cuiSpriteID, m_oPosition.x, m_oPosition.y );
		DrawSprite( m_cuiSpriteID );
	}
}

// Diameter accessor
unsigned int Ball::GetDiameter() const
{
	return DEFAULT_BALL_DIAMETER;
}

// Position accessor
Sprite::XYPair Ball::GetPosition() const
{
	return m_oPosition;
}

// Velocity accessor
Sprite::XYPair Ball::GetVelocity() const
{
	return m_oVelocity;
}

// Keep the ball from being drawn
void Ball::Hide()
{
	m_bVisible = false;
}

// Apply the given initial position and velocity to the ball and make sure it
//   will be drawn.
void Ball::Serve( XYPair& a_oPosition, XYPair& a_oVelocity )
{
	m_oPosition = a_oPosition;
	m_oVelocity = a_oVelocity;
	m_bVisible = true;
}

// Given the elapsed time, update the ball's position (based on its velocity)
//   and rotation.
void Ball::Update( float a_fDeltaT )
{
	m_oPosition.x += m_oVelocity.x * a_fDeltaT;
	m_oPosition.y += m_oVelocity.y * a_fDeltaT;
	m_fRotation += a_fDeltaT;

	// Keep the rotation from ballooning over time.
	if (m_fRotation > 360.0)
	{
		m_fRotation -= 360.0;
	}
}
