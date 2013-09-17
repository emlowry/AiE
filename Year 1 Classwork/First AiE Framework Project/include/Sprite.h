/******************************************************************************
 * File:              Sprite.h
 * Author:            Elizabeth Lowry
 * Date Created:      September 11, 2013
 * Description:       Definitions for the class that handles a drawable object.
 * Last Modified:     September 11, 2013
 * Last Modification: Moved code in from main.cpp.
 ******************************************************************************/

#ifndef _SPRITE_H_
#define _SPRITE_H_

class Sprite
{
public:

	struct Vector
	{
		float x;
		float y;
	};

	static const Vector DEFAULT_POSITION;

	Sprite(const char* ac_pcName,
		   const unsigned int ac_uiWidth,
		   const unsigned int ac_uiHeight,
		   const Vector a_oPosition = DEFAULT_POSITION,
		   const bool ac_bDrawFromCenter = true);
	Sprite(const Sprite& ac_roSprite);
	~Sprite();

	void Destroy();
	virtual void Draw() const;
	virtual void Update(float a_fDeltaT);

protected:

	const unsigned int m_cuiSpriteID;
	bool m_bDestroyed;
};

#endif // _SPRITE_H_