/******************************************************************************
 * File:               AnimatedSprite.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       March 17, 2014
 * Description:        Function implementations for the AnimatedSprite class.
 * Last Modified:      March 17, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#include "../Declarations/AnimatedSprite.h"
#include "../Declarations/GameEngine.h"

namespace MyFirstEngine
{
    
// Main constructors
AnimatedSprite::AnimatedSprite( Texture* a_poTexture,
                                const Point2D& ac_roScale,
                                const Point3D& ac_roPosition,
                                const Rotation3D& ac_roRotation,
                                double a_dFPS, unsigned int a_uiLoops,
                                CompletionCallback a_pOnComplete,
                                const Color::ColorVector& ac_roColor )
    : Sprite( a_poTexture, ac_roScale, ac_roPosition,
              ac_roRotation, ac_roColor ),
      m_dFPS( a_dFPS ), m_uiLoops( a_uiLoops ), m_pOnComplete( a_pOnComplete ),
      m_uiCompletedLoops( 0 ), m_dSeconds( 0 ), m_dUnpauseTime( 0 ),
      m_bPaused( true ) {}
AnimatedSprite::AnimatedSprite( Texture* a_poTexture,
                                const Point2D& ac_roScale,
                                const Point3D& ac_roPosition,
                                const Point3D& ac_roForward,
                                const Point3D& ac_roUp,
                                double a_dFPS, unsigned int a_uiLoops,
                                CompletionCallback a_pOnComplete,
                                const Color::ColorVector& ac_roColor )
    : Sprite( a_poTexture, ac_roScale, ac_roPosition,
              ac_roForward, ac_roUp, ac_roColor ),
      m_dFPS( a_dFPS ), m_uiLoops( a_uiLoops ), m_pOnComplete( a_pOnComplete ),
      m_uiCompletedLoops( 0 ), m_dSeconds( 0 ), m_dUnpauseTime( 0 ),
      m_bPaused( true ) {}
AnimatedSprite::AnimatedSprite( Texture* a_poTexture,
                                const Point3D& ac_roLowerLeftCorner,
                                const Point3D& ac_roUpperRightCorner,
                                const Point3D& ac_roForward,
                                double a_dFPS, unsigned int a_uiLoops,
                                CompletionCallback a_pOnComplete,
                                const Color::ColorVector& ac_roColor )
    : Sprite( a_poTexture, ac_roLowerLeftCorner, ac_roUpperRightCorner,
              ac_roForward, ac_roColor ),
      m_dFPS( a_dFPS ), m_uiLoops( a_uiLoops ), m_pOnComplete( a_pOnComplete ),
      m_uiCompletedLoops( 0 ), m_dSeconds( 0 ), m_dUnpauseTime( 0 ),
      m_bPaused( true ) {}
AnimatedSprite::AnimatedSprite( Texture* a_poTexture,
                                const Frame::Array* a_pcoFrameList,
                                const Point2D& ac_roScale,
                                const Point3D& ac_roPosition,
                                const Rotation3D& ac_roRotation,
                                double a_dFPS, unsigned int a_uiLoops,
                                CompletionCallback a_pOnComplete,
                                const Color::ColorVector& ac_roColor )
    : Sprite( a_poTexture, a_pcoFrameList, ac_roScale,
              ac_roPosition, ac_roRotation, ac_roColor ),
      m_dFPS( a_dFPS ), m_uiLoops( a_uiLoops ), m_pOnComplete( a_pOnComplete ),
      m_uiCompletedLoops( 0 ), m_dSeconds( 0 ), m_dUnpauseTime( 0 ),
      m_bPaused( true ) {}
AnimatedSprite::AnimatedSprite( Texture* a_poTexture,
                                const Frame::Array* a_pcoFrameList,
                                const Point2D& ac_roScale,
                                const Point3D& ac_roPosition,
                                const Point3D& ac_roForward,
                                const Point3D& ac_roUp,
                                double a_dFPS, unsigned int a_uiLoops,
                                CompletionCallback a_pOnComplete,
                                const Color::ColorVector& ac_roColor )
    : Sprite( a_poTexture, a_pcoFrameList, ac_roScale,
              ac_roPosition, ac_roForward, ac_roUp, ac_roColor ),
      m_dFPS( a_dFPS ), m_uiLoops( a_uiLoops ), m_pOnComplete( a_pOnComplete ),
      m_uiCompletedLoops( 0 ), m_dSeconds( 0 ), m_dUnpauseTime( 0 ),
      m_bPaused( true ) {}
AnimatedSprite::AnimatedSprite( Texture* a_poTexture,
                                const Frame::Array* a_pcoFrameList,
                                const Point3D& ac_roLowerLeftCorner,
                                const Point3D& ac_roUpperRightCorner,
                                const Point3D& ac_roForward,
                                double a_dFPS, unsigned int a_uiLoops,
                                CompletionCallback a_pOnComplete,
                                const Color::ColorVector& ac_roColor )
    : Sprite( a_poTexture, a_pcoFrameList, ac_roLowerLeftCorner,
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
    if( IsPaused() || IsCompleted() )
    {
        return *this;
    }
    return ( 0.0 == m_dFPS ? IncrementFrame() : CalculateFrame() );
}

// adjust frame based on elapsed time (does nothing if m_dFPS is zero)
AnimatedSprite& AnimatedSprite::CalculateFrame()
{
    if( 0.0 != m_dFPS )
    {
        double dElapsedSeconds = ElapsedSeconds();
        m_uiCompletedLoops = (unsigned int)( dElapsedSeconds /
                                             LengthInSeconds() );
        if( IsCompleted() )
        {
            SetFrameNumber( FrameCount() - 1 );
            Pause();
        }
        else
        {
            SetFrameNumber( dElapsedSeconds / m_dFPS );
        }
    }
    return *this;
}

// increment frame and, if neccessary, completed loop count
AnimatedSprite& AnimatedSprite::IncrementFrame()
{
    ++m_uiFrameNumber;
    if( 0 == m_uiFrameNumber )
    {
        ++m_uiCompletedLoops;
    }
    if( IsCompleted() )
    {
        SetFrameNumber( FrameCount() - 1 );
        Pause();
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
        m_dSeconds = ElapsedTime();
        m_bPaused = true;
    }
    return *this;
}
AnimatedSprite& AnimatedSprite::Rewind()
{
    SetElapsedSeconds( 0 );
    return *this;
}
AnimatedSprite& AnimatedSprite::Complete()
{
    if( 0 == m_uiLoops )
    {
        m_uiLoops = m_uiCompletedLoops + 1;
        m_uiCompletedLoops = m_uiLoops;
        SetFrameNumber( FrameCount() - 1 );
    }
    if( 0.0 == m_dFPS )
    {
        SetElapsedSeconds( LengthInSeconds() );
    }s
    return *this;
}
AnimatedSprite& AnimatedSprite::Seek( int a_uiFrame )
{
    if( 0.0 == m_dFPS )
    {
        m_uiCompletedLoops = a_uiFrame / ( 0 == FrameCount() ? 1 : FrameCount() );
        SetFrameNumber( IsComplete() ? FrameCount() - 1 ? a_uiFrame );
    }
    else
    {
        SetElapsedSeconds(
    }
}
AnimatedSprite& AnimatedSprite::Seek( double a_dSeconds );
AnimatedSprite& AnimatedSprite::Add( int a_uiFrames );
AnimatedSprite& AnimatedSprite::Add( double a_dSeconds );

    // Get properties
    bool IsCompleted() const;
    double ElapsedSeconds() const;
    double LengthInSeconds() const; // returns 0.0 if m_dFPS or m_uiLoops is 0

    // Set properties
    AnimatedSprite& SetLoops( unsigned int a_uiLoops,
                              unsigned int a_uiCompleted = 0 );
    AnimatedSprite& SetFPS( double a_dFPS );
    AnimatedSprite& SetElapsedSeconds( double a_dSeconds );
    AnimatedSprite& SetLengthInSeconds( double a_dSeconds );    // no effect if
                                                                // m_uiLoops = 0

}   // namespace MyFirstEngine
