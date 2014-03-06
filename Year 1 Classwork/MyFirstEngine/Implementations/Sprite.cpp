/******************************************************************************
 * File:               Sprite.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       March 5, 2014
 * Description:        Implementations for Sprite functions.
 * Last Modified:      March 5, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#include "../Declarations/Sprite.h"
#include <stdexcept>
#include "../Declarations/MyFirstEngineMacros.h"

namespace MyFirstEngine
{

// Default frame
const Sprite::PixelDimensions Sprite::ZERO_FRAME = { IntPoint2D::Zero(),
                                                     IntPoint2D::Zero(),
                                                     IntPoint2D::Zero(),
                                                     IntPoint2D::Zero(),
                                                     IntPoint2D::Zero(),
                                                     Sprite::CROP_TO_SLICE };

// Copy constructor/operator
INLINE Sprite::Sprite( const Sprite& ac_roSprite )
    : Quad( ac_roSprite ), m_uiFrameCount( ac_roSprite.m_uiFrameCount ),
      m_paoFrames( 0 == m_uiFrameCount
                    ? nullptr : new PixelDimensions[ m_uiFrameCount ] ),
      m_uiFrameNumber( ac_roSprite.m_uiFrameNumber % m_uiFrameCount )
{
    if( 0 < m_uiFrameCount )
    {
        memcpy( m_paoFrames, ac_roSprite.m_paoFrames,
                sizeof( ZERO_FRAME ) * m_uiFrameCount );
    }
}
INLINE Sprite& Sprite::operator=( const Sprite& ac_roSprite )
{
    if( &m_paoFrames != &(ac_roSprite.m_paoFrames) )
    {
        m_uiFrameCount = ac_roSprite.m_uiFrameCount;
        m_uiFrameNumber = ac_roSprite.m_uiFrameNumber % m_uiFrameCount;
        PixelDimensions* paoFrames = m_paoFrames;
        m_paoFrames = ( 0 == ac_roSprite.m_uiFrameCount
                        ? nullptr : new PixelDimensions[ m_uiFrameCount ] );
        if( nullptr != paoFrames )
        {
            delete[] paoFrames;
        }
    }
    return *this;
}

// Destructor actually does something
INLINE Sprite::~Sprite()
{
    PixelDimensions* paoFrames = m_paoFrames;
    m_paoFrames = nullptr;
    if( nullptr != paoFrames )
    {
        delete[] paoFrames;
    }
}

// Frame access operators
INLINE Sprite::PixelDimensions&
    Sprite::Frame( unsigned int a_uiFrameNumber )
{
    if( nullptr == m_paoFrames || 0 == m_uiFrameCount )
    {
        throw std::out_of_range( "Sprite has no frames" );
    }
    return m_paoFrames[ a_uiFrameNumber % m_uiFrameCount ];
}
INLINE const Sprite::PixelDimensions&
    Sprite::Frame( unsigned int a_uiFrameNumber ) const
{
    if( nullptr == m_paoFrames || 0 == m_uiFrameCount )
    {
        throw std::out_of_range( "Sprite has no frames" );
    }
    return m_paoFrames[ a_uiFrameNumber % m_uiFrameCount ];
}
INLINE Sprite::PixelDimensions&
    Sprite::operator[]( unsigned int a_uiFrameNumber )
{
    if( nullptr == m_paoFrames || 0 == m_uiFrameCount )
    {
        throw std::out_of_range( "Sprite has no frames" );
    }
    return m_paoFrames[ a_uiFrameNumber % m_uiFrameCount ];
}
INLINE const Sprite::PixelDimensions&
    Sprite::operator[]( unsigned int a_uiFrameNumber ) const
{
    if( nullptr == m_paoFrames || 0 == m_uiFrameCount )
    {
        throw std::out_of_range( "Sprite has no frames" );
    }
    return m_paoFrames[ a_uiFrameNumber % m_uiFrameCount ];
}

// Sprite properties
PixelDimensions& CurrentFrame()
{
    if( nullptr == m_paoFrames || 0 == m_uiFrameCount )
    {
        throw std::out_of_range( "Sprite has no frames" );
    }
    return m_paoFrames[ m_uiFrameNumber ];
}
const PixelDimensions& CurrentFrame() const
{
    if( nullptr == m_paoFrames || 0 == m_uiFrameCount )
    {
        throw std::out_of_range( "Sprite has no frames" );
    }
    return m_paoFrames[ m_uiFrameNumber ];
}
Sprite& SetFrame( unsigned int a_uiFrameNumber )
{
    if( nullptr == m_paoFrames || 0 == m_uiFrameCount )
    {
        throw std::out_of_range( "Sprite has no frames" );
    }
    m_uiFrameNumber = a_uiFrameNumber % m_uiFrameCount;
    return *this;
}

}   // namespace MyFirstEngine
