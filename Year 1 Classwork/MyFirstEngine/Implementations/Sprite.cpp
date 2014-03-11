/******************************************************************************
 * File:               Sprite.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       March 5, 2014
 * Description:        Implementations for Sprite functions.
 * Last Modified:      March 6, 2014
 * Last Modification:  Refactoring.
 ******************************************************************************/

#include "../Declarations/Sprite.h"
#include <stdexcept>
#include <vector>

namespace MyFirstEngine
{

// Default frame
const Sprite::Frame Sprite::Frame::ZERO = Frame();

// Default frame constructor
Sprite::Frame::Frame()
    : spritePixels( IntPoint2D::Zero() ), centerOffset( IntPoint2D::Zero() ),
      sliceLocation( IntPoint2D::Zero() ), slicePixels( IntPoint2D::Zero() ),
      sliceOffset( IntPoint2D::Zero() ), cropping( Sprite::CROP_TO_SLICE ) {}

// Compare dimensions
bool Sprite::Frame::operator==( const Sprite::Frame& ac_roFrame ) const
{
    return ( SameSize( ac_roFrame ) &&
             ac_roFrame.sliceLocation == sliceLocation );
}
bool Sprite::Frame::operator!=( const Sprite::Frame& ac_roFrame ) const
{
    return ( !SameSize( ac_roFrame ) ||
             ac_roFrame.sliceLocation != sliceLocation );
}
bool Sprite::Frame::SameSize( const Sprite::Frame& ac_roFrame ) const
{
    return ( ac_roFrame.sliceOffset == sliceOffset &&
             ac_roFrame.slicePixels == slicePixels &&
             ac_roFrame.centerOffset == centerOffset &&
             ac_roFrame.spritePixels == spritePixels &&
             ac_roFrame.cropping == cropping );
}

// Copy constructor/operator
// TODO initialize members not added yet
Sprite::Sprite( const Sprite& ac_roSprite )
    : Quad( ac_roSprite ),
      m_uiFrameCount( nullptr == ac_roSprite.m_paoFrames
                        ? 0 : ac_roSprite.m_uiFrameCount ),
      m_uiFrameNumber( 0 == m_uiFrameCount
                        ? 0 : ac_roSprite.m_uiFrameNumber % m_uiFrameCount ),
      m_paoFrames( 0 == m_uiFrameCount ? nullptr : new Frame[ m_uiFrameCount ] )
{
    if( 0 != m_uiFrameCount )
    {
        memcpy( m_paoFrames, ac_roSprite.m_paoFrames,
                m_uiFrameCount * sizeof( Frame ) );
    }
}
Sprite& Sprite::operator=( const Sprite& ac_roSprite )
{
    if( &m_paoFrames != &(ac_roSprite.m_paoFrames) )
    {
        if( m_uiFrameCount != ac_roSprite.m_uiFrameCount )
        {
            m_uiFrameCount = ( nullptr == ac_roSprite.m_paoFrames
                                ? 0 : ac_roSprite.m_uiFrameCount );
            Frame* paoFrames = m_paoFrames;
            m_paoFrames = ( 0 == m_uiFrameCount
                            ? nullptr : new Frame[ m_uiFrameCount ] );
            delete paoFrames;
        }
        if( 0 != m_uiFrameCount )
        {
            memcpy( m_paoFrames, ac_roSprite.m_paoFrames,
                    m_uiFrameCount * sizeof( Frame ) );
        }
        m_uiFrameNumber = ( 0 == m_uiFrameCount
                            ? 0 : ac_roSprite.m_uiFrameNumber % m_uiFrameCount );
    }
    return *this;
}

// Destructor actually does something
Sprite::~Sprite()
{
    Frame* paoFrames = m_paoFrames;
    m_paoFrames = nullptr;
    if( nullptr != paoFrames )
    {
        delete[] paoFrames;
    }
}

// Frame access operators
Sprite::Frame&
    Sprite::GetFrame( unsigned int a_uiFrameNumber )
{
    if( nullptr == m_paoFrames || 0 == m_uiFrameCount )
    {
        throw std::out_of_range( "Sprite has no frames" );
    }
    return m_paoFrames[ a_uiFrameNumber % m_uiFrameCount ];
}
const Sprite::Frame&
    Sprite::GetFrame( unsigned int a_uiFrameNumber ) const
{
    if( nullptr == m_paoFrames || 0 == m_uiFrameCount )
    {
        throw std::out_of_range( "Sprite has no frames" );
    }
    return m_paoFrames[ a_uiFrameNumber % m_uiFrameCount ];
}
Sprite::Frame&
    Sprite::operator[]( unsigned int a_uiFrameNumber )
{
    if( nullptr == m_paoFrames || 0 == m_uiFrameCount )
    {
        throw std::out_of_range( "Sprite has no frames" );
    }
    return m_paoFrames[ a_uiFrameNumber % m_uiFrameCount ];
}
const Sprite::Frame&
    Sprite::operator[]( unsigned int a_uiFrameNumber ) const
{
    if( nullptr == m_paoFrames || 0 == m_uiFrameCount )
    {
        throw std::out_of_range( "Sprite has no frames" );
    }
    return m_paoFrames[ a_uiFrameNumber % m_uiFrameCount ];
}

// Frame increment/decrement operators
Sprite& Sprite::operator++()
{
    unsigned int uiOldFrame = m_uiFrameNumber;
    m_uiFrameNumber = ( m_uiFrameNumber + 1 ) % m_uiFrameCount;
    if( !m_paoFrames[ m_uiFrameNumber ].SameSize( m_paoFrames[ uiOldFrame ] ) )
    {
        UpdateModelMatrix();
    }
    return *this;
}
Sprite Sprite::operator++(int)
{
    Sprite oCopy( *this );
    m_uiFrameNumber = ( m_uiFrameNumber + 1 ) % m_uiFrameCount;
    if( !m_paoFrames[ m_uiFrameNumber ].SameSize( oCopy.CurrentFrame() ) )
    {
        UpdateModelMatrix();
    }
    return oCopy;
}
Sprite& Sprite::operator--()
{
    unsigned int uiOldFrame = m_uiFrameNumber;
    m_uiFrameNumber = ( m_uiFrameNumber - 1 ) % m_uiFrameCount;
    if( !m_paoFrames[ m_uiFrameNumber ].SameSize( m_paoFrames[ uiOldFrame ] ) )
    {
        UpdateModelMatrix();
    }
    return *this;
}
Sprite Sprite::operator--(int)
{
    Sprite oCopy( *this );
    m_uiFrameNumber = ( m_uiFrameNumber - 1 ) % m_uiFrameCount;
    if( !m_paoFrames[ m_uiFrameNumber ].SameSize( oCopy.CurrentFrame() ) )
    {
        UpdateModelMatrix();
    }
    return oCopy;
}

// Sprite properties
Sprite::Frame& Sprite::CurrentFrame()
{
    if( nullptr == m_paoFrames || 0 == m_uiFrameCount )
    {
        throw std::out_of_range( "Sprite has no frames" );
    }
    return m_paoFrames[ m_uiFrameNumber ];
}
const Sprite::Frame& Sprite::CurrentFrame() const
{
    if( nullptr == m_paoFrames || 0 == m_uiFrameCount )
    {
        throw std::out_of_range( "Sprite has no frames" );
    }
    return m_paoFrames[ m_uiFrameNumber ];
}
Sprite& Sprite::SetFrameNumber( unsigned int a_uiFrameNumber )
{
    if( nullptr == m_paoFrames || 0 == m_uiFrameCount )
    {
        throw std::out_of_range( "Sprite has no frames" );
    }
    m_uiFrameNumber = a_uiFrameNumber % m_uiFrameCount;
    return *this;
}

}   // namespace MyFirstEngine
