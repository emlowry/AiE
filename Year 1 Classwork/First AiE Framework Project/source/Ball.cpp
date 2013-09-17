/******************************************************************************
 * File:              Ball.cpp
 * Author:            Elizabeth Lowry
 * Date Created:      September 16, 2013
 * Description:       Implementations for methods of the Ball class.
 * Last Modified:     September 16, 2013
 * Last Modification: Creation.
 ******************************************************************************/

#include "Ball.h"
#include "AIE.h"

const char* const Ball::BALL_TEXTURE_NAME = "./images/tennis_ball.png";

Ball::Ball()
	: Sprite(BALL_TEXTURE_NAME, DEFAULT_BALL_DIAMETER, DEFAULT_BALL_DIAMETER),
	  m_fRotation(0.0),
	  m_bVisible(false)
{
	// nothing else to do here
}

void Ball::BounceX()
{
	m_oVelocity.x *= -1;
}

void Ball::BounceY()
{
	m_oVelocity.y *= -1;
}

bool Ball::CanRebound(const int ac_iMinY, const int ac_iMaxY) const
{
	float fMinY = ac_iMinY + ((float)GetDiameter() / 2);
	float fMaxY = ac_iMaxY - ((float)GetDiameter() / 2);
	if ((m_oVelocity.y < 0) && (m_oPosition.y <= fMinY))
		return true;
	if ((m_oVelocity.y > 0) && (m_oPosition.y >= fMaxY))
		return true;
	return false;
}

void Ball::Draw() const {
	if (m_bVisible && !m_bDestroyed)
	{
		RotateSprite(m_cuiSpriteID, m_fRotation);
		MoveSprite(m_cuiSpriteID, m_oPosition.x, m_oPosition.y);
		DrawSprite(m_cuiSpriteID);
	}
}

unsigned int Ball::GetDiameter() const
{
	return DEFAULT_BALL_DIAMETER;
}

Sprite::Vector Ball::GetPosition() const
{
	return m_oPosition;
}

Sprite::Vector Ball::GetVelocity() const
{
	return m_oVelocity;
}

void Ball::Hide()
{
	m_bVisible = false;
}

void Ball::Serve(Vector a_oPosition, Vector a_oVelocity)
{
	m_oPosition = a_oPosition;
	m_oVelocity = a_oVelocity;
	m_bVisible = true;
}

void Ball::Update(float a_fDeltaT)
{
	m_oPosition.x += m_oVelocity.x * a_fDeltaT;
	m_oPosition.y += m_oVelocity.y * a_fDeltaT;
	m_fRotation += a_fDeltaT;
	if (m_fRotation > 360.0)
		m_fRotation -= 360.0;
}
