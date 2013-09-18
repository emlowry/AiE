/******************************************************************************
 * File:               Sprite.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       September 11, 2013
 * Description:        Implementations for methods of the Sprite class.
 * Last Modified:      September 18, 2013
 * Last Modification:  Added comments.
 ******************************************************************************/

#include "Sprite.h"
#include "AIE.h"

const Sprite::XYPair Sprite::DEFAULT_POSITION = {0.0, 0.0};

// Constructor
Sprite::Sprite( const char* const ac_pcName,
				const unsigned int ac_uiWidth,
				const unsigned int ac_uiHeight,
				const XYPair& a_oPosition,
				const bool ac_bDrawFromCenter )
	: m_cuiSpriteID( CreateSprite(ac_pcName,
								  ac_uiWidth,
								  ac_uiHeight,
								  ac_bDrawFromCenter ) ),
	  m_bDestroyed( false )
{
	// In case neither the Update nor the Draw function move the sprite
	//   position, put it in the provided start position.
	MoveSprite( m_cuiSpriteID, a_oPosition.x, a_oPosition.y );
}

// Copy constructor duplicates the given OpenGL sprite instead of reusing it.
Sprite::Sprite(const Sprite& ac_roSprite)
	: m_cuiSpriteID( ac_roSprite.m_bDestroyed
					 ? ac_roSprite.m_cuiSpriteID
					 : DuplicateSprite( ac_roSprite.m_cuiSpriteID ) ),
	  m_bDestroyed( ac_roSprite.m_bDestroyed )
{
	// Don't need to do anything here, since the duplicated sprite will be in
	//   the same position as the original was at the time of the copying.
}

// Make sure the OpenGL sprite has been destroyed before this object is.
Sprite::~Sprite()
{
	this->Destroy();
}

// If it hasn't been destroyed already, destroy the OpenGL sprite
void Sprite::Destroy()
{
	if ( !m_bDestroyed )
	{
		DestroySprite( m_cuiSpriteID );
		m_bDestroyed = true;
	}
}

// If the sprite hasn't been destroyed, draw it.
void Sprite::Draw() const
{
	if ( !m_bDestroyed )
	{
		DrawTasks();
	}
}

// Internal function, overridden by child classes, that does the actual work of
//   drawing the sprite.
void Sprite::DrawTasks() const
{
	DrawSprite( m_cuiSpriteID );
}

// This is where position, velocity, visibility, etc. would be updated in a
//   child class.
void Sprite::Update( float a_fDeltaT )
{
	// Just leave the sprite in its starting position for the default
	//   implementation.
}
