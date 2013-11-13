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
#include <set>

// Handles a single drawable object.
class Sprite
{
public:

    Sprite( const char* const ac_cpcTextureName,
            const IntXY& ac_roSize,
            const FloatXY& ac_roPosition = XY_ZERO );
    virtual ~Sprite();

    void Destroy();
    virtual void Draw() const;  // if visible and not destroyed, call DrawThis
    virtual void Update( const float ac_fDeltaT );  // implement in child class
    bool CollidingWith( const Sprite& ac_roSprite );

    static void DestroyAll();

protected:

    virtual void DrawThis() const;

    bool m_bDestroyed;
    FloatXY m_oPosition;
    unsigned int m_uiRadius;
    const unsigned int m_cuiSpriteID;
    bool m_bVisible;

private:

    // leave copy/assignment constructors uncallable and unimplemented
    Sprite( const Sprite& a_roSprite );
    Sprite operator=( const Sprite& a_roSprite );

    // keep track of all sprites.  this set does not own the sprite objects.
    static std::set< Sprite* > sm_oAllSprites;

};

#endif  // _SPRITE_H_