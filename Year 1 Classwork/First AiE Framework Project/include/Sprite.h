/******************************************************************************
 * File:               Sprite.h
 * Author:             Elizabeth Lowry
 * Date Created:       September 11, 2013
 * Description:        Definitions for the class that handles a drawable object.
 * Last Modified:      September 18, 2013
 * Last Modification:  Moved XYPair to a separate header.
 ******************************************************************************/

#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "EnumsAndStructs.h"

// Handles a drawable object.
class Sprite
{
public:

	Sprite( const char* const ac_pcName,
			const unsigned int ac_uiWidth,
			const unsigned int ac_uiHeight,
			const XYPair& a_oPosition = DEFAULT_X_Y_PAIR,
			const bool ac_bDrawFromCenter = true );
	Sprite( const Sprite& ac_roSprite );
	virtual ~Sprite();

	void Destroy();
	void Draw() const;	// if the sprite hasn't been destroyed, call DrawTasks()
	virtual void Update( float a_fDeltaT );

protected:

	virtual void DrawTasks() const;	// Do the actual work of drawing the sprite

	const unsigned int m_cuiSpriteID;	// ID of the OpenGL sprite

private:

	// Don't implement this!  You can't copy Sprites with an assignment operator
	//   because you won't be able to change an existing Sprite's m_cuiSpriteID.
	//   Leave it as a private prototype only - that way, it can't be called.
	Sprite& operator=( const Sprite& a_roSprite );
	
	bool m_bDestroyed;	// has the sprite been destroyed?

};

#endif // _SPRITE_H_