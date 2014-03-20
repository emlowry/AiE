/******************************************************************************
 * File:               AnimatedSprite.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       March 17, 2014
 * Description:        Function implementations for the AnimatedSprite class.
 * Last Modified:      March 18, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

#include "../Declarations/AnimatedSprite.h"
#include "../Declarations/GameEngine.h"

namespace MyFirstEngine
{
    
// Main constructors
AnimatedSprite::AnimatedSprite( Texture& a_roTexture,
                                const Frame::Array& ac_roFrameList,
                                double a_dFPS, unsigned int a_uiLoops,
                                const Point2D& ac_roScale,
                                const Point3D& ac_roPosition,
                                const Rotation3D& ac_roRotation,
                                const Color::ColorVector& ac_roColor )
    : Sprite( a_roTexture, ac_roFrameList, ac_roScale,
              ac_roPosition, ac_roRotation, ac_roColor ),
      m_dFPS( a_dFPS ), m_uiLoops( a_uiLoops ), m_pOnComplete( nullptr ),
      m_uiCompletedLoops( 0 ), m_dSeconds( 0 ), m_dUnpauseTime( 0 ),
      m_bPaused( true ) {}
AnimatedSprite::AnimatedSprite( Texture& a_roTexture,
                                const Frame::Array& ac_roFrameList,
                                double a_dFPS, unsigned int a_uiLoops,
                                const Point2D& ac_roScale,
                                const Point3D& ac_roPosition,
                                const Point3D& ac_roForward,
                                const Point3D& ac_roUp,
                                const Color::ColorVector& ac_roColor )
    : Sprite( a_roTexture, ac_roFrameList, ac_roScale,
              ac_roPosition, ac_roForward, ac_roUp, ac_roColor ),
      m_dFPS( a_dFPS ), m_uiLoops( a_uiLoops ), m_pOnComplete( nullptr ),
      m_uiCompletedLoops( 0 ), m_dSeconds( 0 ), m_dUnpauseTime( 0 ),
      m_bPaused( true ) {}
AnimatedSprite::AnimatedSprite( Texture& a_roTexture,
                                const Frame::Array& ac_roFrameList,
                                double a_dFPS, unsigned int a_uiLoops,
                                const Point3D& ac_roLowerLeftCorner,
                                const Point3D& ac_roUpperRightCorner,
                                const Point3D& ac_roForward,
                                const Color::ColorVector& ac_roColor )
    : Sprite( a_roTexture, ac_roFrameList, ac_roLowerLeftCorner,
              ac_roUpperRightCorner, ac_roForward, ac_roColor ),
      m_dFPS( a_dFPS ), m_uiLoops( a_uiLoops ), m_pOnComplete( nullptr ),
      m_uiCompletedLoops( 0 ), m_dSeconds( 0 ), m_dUnpauseTime( 0 ),
      m_bPaused( true ) {}
AnimatedSprite::AnimatedSprite( Texture& a_roTexture,
                                const Frame::Array& ac_roFrameList,
                                double a_dFPS, unsigned int a_uiLoops,
                                Callback a_pOnComplete,
                                const Point2D& ac_roScale,
                                const Point3D& ac_roPosition,
                                const Rotation3D& ac_roRotation,
                                const Color::ColorVector& ac_roColor )
    : Sprite( a_roTexture, ac_roFrameList, ac_roScale,
              ac_roPosition, ac_roRotation, ac_roColor ),
      m_dFPS( a_dFPS ), m_uiLoops( a_uiLoops ), m_pOnComplete( a_pOnComplete ),
      m_uiCompletedLoops( 0 ), m_dSeconds( 0 ), m_dUnpauseTime( 0 ),
      m_bPaused( true ) {}
AnimatedSprite::AnimatedSprite( Texture& a_roTexture,
                                const Frame::Array& ac_roFrameList,
                                double a_dFPS, unsigned int a_uiLoops,
                                Callback a_pOnComplete,
                                const Point2D& ac_roScale,
                                const Point3D& ac_roPosition,
                                const Point3D& ac_roForward,
                                const Point3D& ac_roUp,
                                const Color::ColorVector& ac_roColor )
    : Sprite( a_roTexture, ac_roFrameList, ac_roScale,
              ac_roPosition, ac_roForward, ac_roUp, ac_roColor ),
      m_dFPS( a_dFPS ), m_uiLoops( a_uiLoops ), m_pOnComplete( a_pOnComplete ),
      m_uiCompletedLoops( 0 ), m_dSeconds( 0 ), m_dUnpauseTime( 0 ),
      m_bPaused( true ) {}
AnimatedSprite::AnimatedSprite( Texture& a_roTexture,
                                const Frame::Array& ac_roFrameList,
                                double a_dFPS, unsigned int a_uiLoops,
                                Callback a_pOnComplete,
                                const Point3D& ac_roLowerLeftCorner,
                                const Point3D& ac_roUpperRightCorner,
                                const Point3D& ac_roForward,
                                const Color::ColorVector& ac_roColor )
    : Sprite( a_roTexture, ac_roFrameList, ac_roLowerLeftCorner,
              ac_roUpperRightCorner, ac_roForward, ac_roColor ),
      m_dFPS( a_dFPS ), m_uiLoops( a_uiLoops ), m_pOnComplete( a_pOnComplete ),
      m_uiCompletedLoops( 0 ), m_dSeconds( 0 ), m_dUnpauseTime( 0 ),
      m_bPaused( true ) {}

// Copy constructor/operator
AnimatedSprite::AnimatedSprite( const AnimatedSprite& ac_roSprite )
    : Sprite( ac_roSprite ),
      m_dFPS( ac_roSprite.m_dFPS ),
      m_uiLoops( ac_roSprite.m_uiLoops ),
      m_pOnComplete( ac_roSprite.m_pOnComplete ),
      m_uiCompletedLoops( ac_roSprite.m_uiCompletedLoops ),
      m_dSeconds( ac_roSprite.m_dSeconds ),
      m_dUnpauseTime( ac_roSprite.m_dUnpauseTime ),
      m_bPaused( ac_roSprite.m_bPaused ) {}
AnimatedSprite& AnimatedSprite::operator=( const AnimatedSprite& ac_roSprite )
{
    Sprite::operator=( ac_roSprite );
    m_dFPS = ac_roSprite.m_dFPS;
    m_uiLoops = ac_roSprite.m_uiLoops;
    m_pOnComplete = ac_roSprite.m_pOnComplete;
    m_uiCompletedLoops = ac_roSprite.m_uiCompletedLoops;
    m_dSeconds = ac_roSprite.m_dSeconds;
    m_dUnpauseTime = ac_roSprite.m_dUnpauseTime;
    m_bPaused = ac_roSprite.m_bPaused;
    return *this;
}
AnimatedSprite::AnimatedSprite( const Sprite& ac_roSprite )
    : Sprite( ac_roSprite ), m_dFPS( 0 ), m_uiLoops( 0 ),
      m_pOnComplete( nullptr ), m_uiCompletedLoops( 0 ), m_dSeconds( 0 ),
      m_dUnpauseTime( 0 ), m_bPaused( true ) {}
AnimatedSprite& AnimatedSprite::operator=( const Sprite& ac_roSprite )
{
    Sprite::operator=( ac_roSprite );
    return *this;
}

// increment frame if appropriate
AnimatedSprite& AnimatedSprite::Update( double a_dDeltaTime )
{
    if( !IsPaused() && !IsCompleted() )
    {
        if( 0.0 == m_dFPS )
        {
            IncrementFrame();
        }
        else
        {
            CalculateFrame();
        }
        if( IsCompleted() && nullptr != m_pOnComplete )
        {
            OnComplete();
        }
    }
    return *this;
}

// adjust frame based on elapsed time (does nothing if m_dFPS is zero)
AnimatedSprite& AnimatedSprite::CalculateFrame()
{
    if( 0.0 != m_dFPS )
    {
        m_uiCompletedLoops = 0;
        double dElapsedSeconds = ElapsedSeconds();
        m_uiCompletedLoops = (unsigned int)( dElapsedSeconds /
                                             LengthInSeconds() );
        SetFrameNumber( IsCompleted() ? FrameCount() - 1 :
                        (unsigned int)( dElapsedSeconds * m_dFPS ) );
    }
    return *this;
}

// increment frame and, if neccessary, completed loop count
AnimatedSprite& AnimatedSprite::IncrementFrame()
{
    if( IsCompleted() )
    {
        SetFrameNumber( FrameCount() - 1 );
    }
    else
    {
        if( FrameCount() - 1 == FrameNumber() )
        {
            ++m_uiCompletedLoops;
        }
        if( !IsCompleted() )
        {
            SetFrameNumber( FrameNumber() + 1 );
        }
    }
    return *this;
}

// control progress
AnimatedSprite& AnimatedSprite::Play()
{
    if( m_bPaused )
    {
        m_dUnpauseTime = GameEngine::LastTime();
        m_bPaused = false;
    }
    return *this;
}
AnimatedSprite& AnimatedSprite::Pause()
{
    if( !m_bPaused )
    {
        m_dSeconds = ElapsedSeconds();
        m_bPaused = true;
    }
    return *this;
}
AnimatedSprite& AnimatedSprite::Rewind()
{
    Seek( 0.0 );
    SetFrameNumber( 0 );
    m_uiCompletedLoops = 0;
    return *this;
}
AnimatedSprite& AnimatedSprite::Complete()
{
    if( 0 != m_uiLoops )
    {
        m_uiLoops = m_uiCompletedLoops + 1;
    }
    Seek( LengthInSeconds() );
    m_uiCompletedLoops = m_uiLoops;
    SetFrameNumber( FrameCount() - 1 );
    OnComplete();
    return *this;
}
AnimatedSprite& AnimatedSprite::Seek( unsigned int a_uiFrame )
{
    if( 0 != LengthInFrames() && LengthInFrames() <= a_uiFrame )
    {
        return Complete();
    }
    if( 0.0 != m_dFPS )
    {
        Seek( a_uiFrame / m_dFPS );
    }
    else
    {
        if( 0 != FrameCount() )
        {
            m_uiCompletedLoops = a_uiFrame / FrameCount();
            if( m_uiLoops < m_uiCompletedLoops )
            {
                m_uiCompletedLoops = m_uiLoops;
            }
        }
        SetFrameNumber( IsCompleted() ? FrameCount() - 1 : a_uiFrame );
    }
    return *this;
}
AnimatedSprite& AnimatedSprite::Seek( double a_dSeconds )
{
    m_dSeconds = ( 0.0 > a_dSeconds ? 0.0 : a_dSeconds );
    if( !m_bPaused )
    {
        m_dUnpauseTime = GameEngine::LastTime();
    }
    if( 0.0 != m_dFPS )
    {
        if( 0 != m_uiLoops && LengthInSeconds() < a_dSeconds )
        {
            m_dSeconds = LengthInSeconds();
        }
        return CalculateFrame();
    }
    return *this;
}
AnimatedSprite& AnimatedSprite::Add( int a_iFrames )
{
    if( 0 > a_iFrames && ElapsedFrames() <= (unsigned int)( -a_iFrames ) )
    {
        Rewind();
    }
    return Seek( ElapsedFrames() + a_iFrames );
}
AnimatedSprite& AnimatedSprite::Add( double a_dSeconds )
{
    return Seek( ElapsedSeconds() + a_dSeconds );
}

// Get properties
bool AnimatedSprite::IsCompleted() const
{
    return ( 0 == FrameCount() ? true :
             0 == m_uiLoops ? false :
             m_uiLoops <= m_uiCompletedLoops );
}
unsigned int AnimatedSprite::ElapsedFrames() const
{
    return ( IsCompleted() ? LengthInFrames() :
             FrameNumber() + m_uiCompletedLoops * FrameCount() );
}
double AnimatedSprite::ElapsedSeconds() const
{
    return ( IsCompleted() ? LengthInSeconds() :
             m_dSeconds + ( m_bPaused ? 0 :
                            GameEngine::LastTime() - m_dUnpauseTime ) );
}

// Set properties
AnimatedSprite& AnimatedSprite::SetLoops( unsigned int a_uiLoops )
{
    m_uiLoops = a_uiLoops;
    if( m_uiCompletedLoops > m_uiLoops )
    {
        m_uiCompletedLoops = m_uiLoops;
    }
    return *this;
}
AnimatedSprite& AnimatedSprite::SetLengthInSeconds( double a_dSeconds )
{
    unsigned int uiFrames = LengthInFrames();
    if( 0.0 != a_dSeconds )
    {
        SetFPS( uiFrames / a_dSeconds );
    }
    return *this;
}

}   // namespace MyFirstEngine
