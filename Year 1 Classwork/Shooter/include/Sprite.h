/******************************************************************************
 * File:               Sprite.h
 * Author:             Elizabeth Lowry
 * Date Created:       September 30, 2013
 * Description:        Class for handling a drawable object.
 * Last Modified:      September 30, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "XY.h"

// Handles a single drawable object.
class Sprite
{
public:

    Sprite( const char* const ac_cpcTextureName,
            const IntXY& ac_roSize,
            const FloatXY& ac_roPosition = XY_ZERO,
            const float ac_fRotation = 0,
            const FloatXY& ac_roScale = XY_ONE );
    virtual ~Sprite();

    void Destroy();
    void Draw() const;  // if visible and not destroyed, call DrawThis
    virtual void Update( const float ac_fDeltaT );  // implement in child class

protected:

    virtual void DrawThis() const;

    bool m_bDestroyed;
    FloatXY m_oPosition;
    float m_fRotation;
    FloatXY m_oScale;
    const unsigned int m_cuiSpriteID;
    bool m_bUpToDate;
    bool m_bVisible;

private:

    // leave copy/assignment constructors uncallable and unimplemented
    Sprite( const Sprite& a_roSprite );
    Sprite operator=( const Sprite& a_roSprite );

};

#endif  // _SPRITE_H_