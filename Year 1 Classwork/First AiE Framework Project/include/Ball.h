/**************************************************************************************************
 * File:               Ball.h
 * Author:             Elizabeth Lowry
 * Date Created:       September 11, 2013
 * Description:        Definitions for the class that handles the ball sprite.
 * Last Modified:      September 18, 2013
 * Last Modification:  Added comments.
 **************************************************************************************************/

#ifndef _BALL_H_
#define _BALL_H_

#include "Sprite.h"

class Ball : public Sprite
{
public:

	Ball();	// Constructor

	// Public functions related to rebounding off surfaces
	void BounceX();
	void BounceY();
	bool CanRebound(const int ac_iMinY, const int ac_iMaxY) const;

	// Accessors
	unsigned int GetDiameter() const;
	XYPair GetPosition() const;
	XYPair GetVelocity() const;

	// Other functions
	void Hide();
	void Serve(XYPair& a_oPosition, XYPair& a_oVelocity);
	void Update(float a_fDeltaT);

private:

	// class-level constants
	static const unsigned int DEFAULT_BALL_DIAMETER = 20;
	static const char* const BALL_TEXTURE_NAME;	// "./images/tennis_ball.png"

	// members
	XYPair m_oPosition;
	float m_fRotation;
	XYPair m_oVelocity;
	bool m_bVisible;

	// Do the work of drawing the ball, overridden from parent class
	void DrawTasks() const;

};

#endif // _BALL_H_
