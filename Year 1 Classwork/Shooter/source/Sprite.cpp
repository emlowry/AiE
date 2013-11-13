/******************************************************************************
 * File:               Sprite.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       September 30, 2013
 * Description:        Implementations for methods of the Sprite class.
 * Last Modified:      September 30, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#include "AIE.h"
#include "Sprite.h"

std::set< Sprite* > Sprite::sm_oAllSprites = std::set< Sprite* >();

// Constructor does all its work in initializer list
Sprite::Sprite( const char* const ac_cpcTextureName,
                const IntXY& ac_roSize,
                const FloatXY& ac_roPosition )
  : m_cuiSpriteID( CreateSprite( ac_cpcTextureName, ac_roSize.x, ac_roSize.y ) ),
    m_oPosition( ac_roPosition ),
    m_bDestroyed( false ),
    m_bVisible( true ),
    m_uiRadius( ( ac_roSize.x + ac_roSize.y ) / 4 )
{
    sm_oAllSprites.insert( this );
}

// Destructor
Sprite::~Sprite()
{
    Destroy();
    sm_oAllSprites.erase( this );
}

// Is this sprite colliding with the given sprite?
bool Sprite::CollidingWith( const Sprite& ac_roSprite )
{
    return Hypotenuse( m_oPosition, ac_roSprite.m_oPosition )
            < ( m_uiRadius + ac_roSprite.m_uiRadius );
}

// Destroy the OpenGL sprite
void Sprite::Destroy()
{
    if( !m_bDestroyed )
    {
        m_bDestroyed = true;
        DestroySprite( m_cuiSpriteID );
    }
}

void Sprite::DestroyAll()
{
    for each( Sprite* poSprite in sm_oAllSprites )
    {
        poSprite->Destroy();
    }
}

// If visible and not destroyed, call DrawSprite to do the work
void Sprite::Draw() const
{
    if( m_bVisible && !m_bDestroyed )
    {
        DrawThis();
    }
}

// Do the work of drawing the sprite
void Sprite::DrawThis() const
{
    MoveSprite( m_cuiSpriteID, m_oPosition.x, m_oPosition.y );
    DrawSprite( m_cuiSpriteID );
}

// This should be overridden in child classes
void Sprite::Update( const float ac_fDeltaT )
{
    // This is where you'd update the position, rotation, scale, etc.
}
