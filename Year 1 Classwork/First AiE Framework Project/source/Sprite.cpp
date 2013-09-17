/******************************************************************************
 * File:              Sprite.cpp
 * Author:            Elizabeth Lowry
 * Date Created:      September 11, 2013
 * Description:       Implementations for methods of the Sprite class.
 * Last Modified:     September 11, 2013
 * Last Modification: Creation.
 ******************************************************************************/

#include "Sprite.h"
#include "AIE.h"

const Sprite::Vector Sprite::DEFAULT_POSITION = {0.0, 0.0};

Sprite::Sprite(const char* ac_pcName,
		       const unsigned int ac_uiWidth,
		       const unsigned int ac_uiHeight,
		       const Vector a_oPosition,
		       const bool ac_bDrawFromCenter)
	: m_cuiSpriteID(CreateSprite(ac_pcName, ac_uiWidth, ac_uiHeight, ac_bDrawFromCenter)),
	  m_bDestroyed(false)
{
	MoveSprite(m_cuiSpriteID, a_oPosition.x, a_oPosition.y);
}

Sprite::Sprite(const Sprite& ac_roSprite)
	: m_cuiSpriteID(ac_roSprite.m_bDestroyed
					? ac_roSprite.m_cuiSpriteID	// I don't know if destroyed sprites can be duplicated
					: DuplicateSprite(ac_roSprite.m_cuiSpriteID)),
	  m_bDestroyed(ac_roSprite.m_bDestroyed)
{
	// Don't need to do anything here, since the duplicated sprite will be in the
	// same position as the original was at the time of the copying.
}

Sprite::~Sprite()
{
	this->Destroy();
}

void Sprite::Destroy()
{
	if (!m_bDestroyed)
	{
		DestroySprite(m_cuiSpriteID);
		m_bDestroyed = true;
	}
}

void Sprite::Draw() const
{
	if (!m_bDestroyed)
		DrawSprite(m_cuiSpriteID);
}

void Sprite::Update(float a_fDeltaT)
{
	// this is where position, velocity, visibility, etc. would be updated in a
	// child class.
}
