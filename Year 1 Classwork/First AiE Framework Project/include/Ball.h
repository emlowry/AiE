/******************************************************************************
 * File:               Ball.h
 * Author:             Elizabeth Lowry
 * Date Created:       September 11, 2013
 * Description:        Definitions for the class that handles the ball sprite.
 * Last Modified:      September 23, 2013
 * Last Modification:  Formatting according to coding standards.
 ******************************************************************************/

#ifndef _BALL_H_
#define _BALL_H_

#include "Sprite.h"

// Handles the ball in the game
class Ball : public Sprite
{
public:

	Ball();

	void BounceX();
	void BounceY();
	bool CanRebound( const int ac_iMinY, const int ac_iMaxY ) const;
	unsigned int GetDiameter() const;
	XYPair GetPosition() const;
	XYPair GetVelocity() const;
	void Hide();
	void Serve( XYPair& a_oPosition, XYPair& a_oVelocity );
	void Update(float a_fDeltaT);

private:

	virtual void DrawTasks() const;

	static const unsigned int DEFAULT_BALL_DIAMETER = 20;
	static const char* const BALL_TEXTURE_NAME;	// "./images/tennis_ball.png"

	XYPair m_oPosition;
	float m_fRotation;
	XYPair m_oVelocity;
	bool m_bVisible;

};

#endif // _BALL_H_
