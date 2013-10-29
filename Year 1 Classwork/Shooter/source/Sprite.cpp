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

// Constructor does all its work in initializer list
Sprite::Sprite( const char* const ac_cpcTextureName,
                const IntXY& ac_roSize,
                const FloatXY& ac_roPosition,
                const float ac_fRotation,
                const FloatXY& ac_roScale )
  : m_cuiSpriteID( CreateSprite( ac_cpcTextureName, ac_roSize.x, ac_roSize.y ) ),
    m_oPosition( ac_roPosition ),
    m_fRotation( ac_fRotation ),
    m_oScale( ac_roScale ),
    m_bDestroyed( false ),
    m_bUpToDate( false ),
    m_bVisible( true )
{
}

// Destructor
Sprite::~Sprite()
{
    Destroy();
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
    if( !m_bUpToDate )
    {
        MoveSprite( m_cuiSpriteID, m_oPosition.x, m_oPosition.y );
        RotateSprite( m_cuiSpriteID, m_fRotation );
        FloatXY oScaleCopy = m_oScale;  // to prevent compiler error
        SetSpriteScale( m_cuiSpriteID, oScaleCopy.x, oScaleCopy.y );
    }
    DrawSprite( m_cuiSpriteID );
}

// This should be overridden in child classes
void Sprite::Update( const float ac_fDeltaT )
{
    // This is where you'd update the position, rotation, scale, etc.
}
