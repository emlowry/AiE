/******************************************************************************
 * File:               Sprite.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       March 5, 2014
 * Description:        Implementations for Sprite functions.
 * Last Modified:      March 11, 2014
 * Last Modification:  Moving Frame code to Frame.h.
 ******************************************************************************/

#include "../Declarations/Sprite.h"
#include <stdexcept>
#include <vector>

namespace MyFirstEngine
{

// Copy constructor/operator
// TODO initialize members not added yet
Sprite::Sprite( const Sprite& ac_roSprite )
    : Quad( ac_roSprite ),
      m_pcoFrameList( ac_roSprite.m_pcoFrameList ),
      m_uiFrameNumber( ac_roSprite.m_uiFrameNumber ),
      m_pcoTexture( ac_roSprite.m_pcoTexture ),
      m_pbUpdateTextureMatrix( new bool ), m_poTextureMatrix( new Transform3D )
{
    UpdateTextureMatrix();
}
Sprite& Sprite::operator=( const Sprite& ac_roSprite )
{
    // if this is this, don't do anything
    if( &m_uiFrameNumber == &(ac_roSprite.m_uiFrameNumber) )
    {
        return *this;
    }

    // Remember the old frame size
    Frame oFrame = CurrentFrame();

    // Copy properties
    Quad::operator=( ac_roSprite );
    m_pcoFrameList = ac_roSprite.m_pcoFrameList;
    m_uiFrameNumber = ac_roSprite.m_uiFrameNumber;
    m_pcoTexture = ac_roSprite.m_pcoTexture;

    // If frame size changed, update matrix
    if( !CurrentFrame().SameSize( oFrame ) )
    {
        UpdateModelMatrix();
        UpdateTextureMatrix();
    }

    return *this;
}

// Frame access operators
const Frame& Sprite::GetFrame( unsigned int a_uiFrameNumber ) const
{
    if( 0 == FrameCount() )
    {
        return ( nullptr == m_pcoTexture ? Frame::ZERO
                                         : m_pcoTexture->TextureFrame() );
    }
    return (*m_pcoFrameList)[ a_uiFrameNumber % FrameCount() ];
}
const Frame& Sprite::operator[]( unsigned int a_uiFrameNumber ) const
{
    if( 0 == FrameCount() )
    {
        return ( nullptr == m_pcoTexture ? Frame::ZERO
                                         : m_pcoTexture->TextureFrame() );
    }
    return (*m_pcoFrameList)[ a_uiFrameNumber % FrameCount() ];
}

// Frame increment/decrement operators
Sprite& Sprite::operator++()
{
    if( 0 == FrameCount() )
    {
        return *this;
    }
    unsigned int uiOldFrame = m_uiFrameNumber;
    m_uiFrameNumber = ( m_uiFrameNumber + 1 ) % FrameCount();
    if( !CurrentFrame().SameSize( GetFrame( uiOldFrame ) ) )
    {
        UpdateModelMatrix();
        UpdateTextureMatrix();
    }
    return *this;
}
Sprite Sprite::operator++(int)
{
    if( 0 == FrameCount() )
    {
        return *this;
    }
    Sprite oCopy( *this );
    m_uiFrameNumber = ( m_uiFrameNumber + 1 ) % FrameCount();
    if( !CurrentFrame().SameSize( oCopy.CurrentFrame() ) )
    {
        UpdateModelMatrix();
        UpdateTextureMatrix();
    }
    return oCopy;
}
Sprite& Sprite::operator--()
{
    if( 0 == FrameCount() )
    {
        return *this;
    }
    unsigned int uiOldFrame = m_uiFrameNumber;
    m_uiFrameNumber = ( 0 == m_uiFrameNumber
                        ? FrameCount() - 1
                        : ( m_uiFrameNumber - 1 ) % FrameCount() );
    if( !CurrentFrame().SameSize( GetFrame( uiOldFrame ) ) )
    {
        UpdateModelMatrix();
        UpdateTextureMatrix();
    }
    return *this;
}
Sprite Sprite::operator--(int)
{
    if( 0 == FrameCount() )
    {
        return *this;
    }
    Sprite oCopy( *this );
    m_uiFrameNumber = ( 0 == m_uiFrameNumber
                        ? FrameCount() - 1
                        : ( m_uiFrameNumber - 1 ) % FrameCount() );
    if( !CurrentFrame().SameSize( oCopy.CurrentFrame() ) )
    {
        UpdateModelMatrix();
        UpdateTextureMatrix();
    }
    return oCopy;
}

// Sprite properties
const Frame& Sprite::CurrentFrame() const
{
    return GetFrame( m_uiFrameNumber );
}
Sprite& Sprite::SetFrameNumber( unsigned int a_uiFrameNumber )
{
    if( 0 == FrameCount() )
    {
        return *this;
    }
    if( !CurrentFrame().SameSize( GetFrame( a_uiFrameNumber ) ) )
    {
        UpdateModelMatrix();
        UpdateTextureMatrix();
    }
    m_uiFrameNumber = a_uiFrameNumber % FrameCount();
    return *this;
}
Sprite& Sprite::SetFrameList( const Frame::Array* a_pcoFrameList )
{
    // save current frame
    Frame oFrame = CurrentFrame();

    // set frame list
    m_pcoFrameList = a_pcoFrameList;
    m_uiFrameNumber = ( nullptr == m_pcoFrameList
                        ? 0 : m_uiFrameNumber % FrameCount() );

    // check for change in frame size
    if( !oFrame.SameSize( CurrentFrame() ) )
    {
        UpdateModelMatrix();
        UpdateTextureMatrix();
    }
    return *this;
}
Sprite& Sprite::SetTexture( const Texture& ac_roTexture )
{
    if( &ac_roTexture != m_pcoTexture )
    {
        Frame oFrame = CurrentFrame();
        m_pcoTexture = &ac_roTexture;
        if( !oFrame.SameSize( CurrentFrame() ) )
        {
            UpdateModelMatrix();
            UpdateTextureMatrix();
        }
    }
    return *this;
}
// sets texture pointer to null.  This way, lvalue references to const textures
// can be used, but passing in an rvalue reference to a temporary texture won't
// lead to the sprite having an invalid texture pointer.
Sprite& Sprite::SetTexture( Texture&& a_rroTexture )
{
    Frame oFrame = CurrentFrame();
    m_pcoTexture = nullptr;
    if( !oFrame.SameSize( CurrentFrame() ) )
    {
        UpdateModelMatrix();
        UpdateTextureMatrix();
    }
    return *this;
}

// Get the cached model view transformation resulting from this object's
// scale/rotation/position/pixel dimensions/etc.  If any of those properties
// have changed since the last time said transformation was calculated,
// recalculate it.
const Transform3D& Sprite::GetModelMatrix() const
{
    if( *m_pbUpdateModelMatrix )
    {
        // TODO
        *m_pbUpdateModelMatrix = false;
    }
    return *m_poModelMatrix;
}

// Get the cached texture coordinate transformation resulting from the
// current frame's dimensions and cropping.  If any of those properties have
// changed since the last time said transformation was calculated,
// recalculate it.
const Transform3D& Sprite::GetTextureMatrix() const
{
    if( *m_pbUpdateTextureMatrix )
    {
        // TODO
        *m_pbUpdateTextureMatrix = false;
    }
    return *m_poTextureMatrix;
}

}   // namespace MyFirstEngine
