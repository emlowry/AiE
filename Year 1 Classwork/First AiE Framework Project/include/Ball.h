/**************************************************************************************************
 * File:               Ball.h
 * Author:             Elizabeth Lowry
 * Date Created:       September 11, 2013
 * Description:        Definitions for the class that handles the ball sprite.
 * Last Modified:      September 16, 2013
 * Last Modification:  Added GetDiameter function.
 **************************************************************************************************/

#ifndef _BALL_H_
#define _BALL_H_

#include "Sprite.h"

class Ball : public Sprite
{
public:
	Ball();

	void BounceX();
	void BounceY();
	bool CanRebound(const int ac_iMinY, const int ac_iMaxY) const;
	void Draw() const;
	unsigned int GetDiameter() const;
	Vector GetPosition() const;
	Vector GetVelocity() const;
	void Hide();
	void Serve(Vector a_oPosition, Vector a_oVelocity);
	void Update(float a_fDeltaT);

private:
	static const unsigned int DEFAULT_BALL_DIAMETER = 20;
	static const char* const BALL_TEXTURE_NAME;	// "./images/tennis_ball.png"

	Vector m_oPosition;
	float m_fRotation;
	Vector m_oVelocity;
	bool m_bVisible;
};

#endif // _BALL_H_
