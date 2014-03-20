/******************************************************************************
 * File:               AnimatedSprite.h
 * Author:             Elizabeth Lowry
 * Date Created:       March 13, 2014
 * Description:        Class representing an sprite that loops through frames.
 * Last Modified:      March 18, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

#ifndef ANIMATED_SPRITE__H
#define ANIMATED_SPRITE__H

#include "Sprite.h"
#include "MyFirstEngineMacros.h"

namespace MyFirstEngine
{

// A textured rectangle that changes frame automatically
class IMEXPORT_CLASS AnimatedSprite : public Sprite
{
public:

    // animation completion callback
    typedef void (*Callback)( AnimatedSprite& a_roSprite );
    
    // Main constructors
    AnimatedSprite( Texture& a_roTexture,
                    const Frame::Array& ac_roFrameList,
                    double a_dFPS = 0.0, unsigned int a_uiLoops = 0,
                    const Point2D& ac_roScale = Point2D( 1.0 ),
                    const Point3D& ac_roPosition = Point3D::Origin(),
                    const Rotation3D& ac_roRotation = Rotation3D::None(),
                    const Color::ColorVector& ac_roColor = Color::WHITE );
    AnimatedSprite( Texture& a_roTexture,
                    const Frame::Array& ac_roFrameList,
                    double a_dFPS, unsigned int a_uiLoops,
                    const Point2D& ac_roScale,
                    const Point3D& ac_roPosition,
                    const Point3D& ac_roForward,
                    const Point3D& ac_roUp = Point3D::Unit(2),
                    const Color::ColorVector& ac_roColor = Color::WHITE );
    AnimatedSprite( Texture& a_roTexture,
                    const Frame::Array& ac_roFrameList,
                    double a_dFPS, unsigned int a_uiLoops,
                    const Point3D& ac_roLowerLeftCorner,
                    const Point3D& ac_roUpperRightCorner,
                    const Point3D& ac_roForward = Point3D::Unit(0),
                    const Color::ColorVector& ac_roColor = Color::WHITE );
    AnimatedSprite( Texture& a_roTexture,
                    const Frame::Array& ac_roFrameList,
                    double a_dFPS, unsigned int a_uiLoops,
                    Callback a_pOnComplete,
                    const Point2D& ac_roScale = Point2D( 1.0 ),
                    const Point3D& ac_roPosition = Point3D::Origin(),
                    const Rotation3D& ac_roRotation = Rotation3D::None(),
                    const Color::ColorVector& ac_roColor = Color::WHITE );
    AnimatedSprite( Texture& a_roTexture,
                    const Frame::Array& ac_roFrameList,
                    double a_dFPS, unsigned int a_uiLoops,
                    Callback a_pOnComplete,
                    const Point2D& ac_roScale,
                    const Point3D& ac_roPosition,
                    const Point3D& ac_roForward,
                    const Point3D& ac_roUp = Point3D::Unit(2),
                    const Color::ColorVector& ac_roColor = Color::WHITE );
    AnimatedSprite( Texture& a_roTexture,
                    const Frame::Array& ac_roFrameList,
                    double a_dFPS, unsigned int a_uiLoops,
                    Callback a_pOnComplete,
                    const Point3D& ac_roLowerLeftCorner,
                    const Point3D& ac_roUpperRightCorner,
                    const Point3D& ac_roForward = Point3D::Unit(0),
                    const Color::ColorVector& ac_roColor = Color::WHITE );

    // Copy constructor/operator
    AnimatedSprite( const AnimatedSprite& ac_roSprite );
    AnimatedSprite& operator=( const AnimatedSprite& ac_roSprite );
    AnimatedSprite( const Sprite& ac_roSprite );
    AnimatedSprite& operator=( const Sprite& ac_roSprite );

    // Destructor
    virtual ~AnimatedSprite() {}

    // increment frame if appropriate
    virtual AnimatedSprite& Update( double a_dDeltaTime = 0.0 );

    // adjust frame based on elapsed time (does nothing if m_dFPS is zero)
    AnimatedSprite& CalculateFrame();

    // increment frame and, if neccessary, completed loop count
    AnimatedSprite& IncrementFrame();

    // control progress
    AnimatedSprite& Play();
    AnimatedSprite& Pause();
    AnimatedSprite& Rewind();   // does not pause/unpause
    AnimatedSprite& Complete();
    AnimatedSprite& Seek( unsigned int a_uiFrame );
    AnimatedSprite& Seek( double a_dSeconds );
    AnimatedSprite& Add( int a_iFrames );
    AnimatedSprite& Add( double a_dSeconds );

    // Get properties
    bool IsCompleted() const;
    bool IsPaused() const { return m_bPaused; }
    unsigned int Loops() const { return m_uiLoops; }
    double FPS() const { return m_dFPS; }
    unsigned int CompletedLoops() const { return m_uiCompletedLoops; }
    Callback CompletionCallback() const { return m_pOnComplete; }
    unsigned int LengthInFrames() const { return m_uiLoops * FrameCount(); }
    double LengthInSeconds() const
    { return ( 0.0 == m_dFPS ? 0.0 : LengthInFrames() / m_dFPS ); }
    unsigned int ElapsedFrames() const;
    double ElapsedSeconds() const;

    // Set properties
    AnimatedSprite& SetFPS( double a_dFPS )
    { m_dFPS = a_dFPS; return Seek( ElapsedFrames() ); }
    AnimatedSprite& SetCompletionCallback( Callback a_pOnComplete )
    { m_pOnComplete = a_pOnComplete; return *this; }
    AnimatedSprite& SetLoops( unsigned int a_uiLoops );
    AnimatedSprite& SetLengthInSeconds( double a_dSeconds );    // no effect if
                                                                // m_uiLoops = 0

    // Call the completion callback, if there is one, on this animated sprite
    void OnComplete() { if( nullptr != m_pOnComplete ) m_pOnComplete( *this ); }

protected:

    // Animation progress
    bool m_bPaused;
    unsigned int m_uiCompletedLoops;
    double m_dSeconds;  // total play time before last pause
    double m_dUnpauseTime;

    // Animation properties
    unsigned int m_uiLoops; // 0 = infinite
    double m_dFPS;  // 0.0 = increment frame on draw, regardless of elapsed time

    // What to do when the animation finishes looping
    Callback m_pOnComplete;   // nullptr = do nothing

private:
    
    // prevent frame list rvalue references from binding to public constructors
    AnimatedSprite( Texture& a_roTexture,
                    const Frame::Array&& ac_rroFrameList,
                    double a_dFPS = 0.0, unsigned int a_uiLoops = 0,
                    const Point2D& ac_roScale = Point2D( 1.0 ),
                    const Point3D& ac_roPosition = Point3D::Origin(),
                    const Rotation3D& ac_roRotation = Rotation3D::None(),
                    const Color::ColorVector& ac_roColor = Color::WHITE );
    AnimatedSprite( Texture& a_roTexture,
                    const Frame::Array&& ac_rroFrameList,
                    double a_dFPS, unsigned int a_uiLoops,
                    const Point2D& ac_roScale,
                    const Point3D& ac_roPosition,
                    const Point3D& ac_roForward,
                    const Point3D& ac_roUp = Point3D::Unit(2),
                    const Color::ColorVector& ac_roColor = Color::WHITE );
    AnimatedSprite( Texture& a_roTexture,
                    const Frame::Array&& ac_rroFrameList,
                    double a_dFPS, unsigned int a_uiLoops,
                    const Point3D& ac_roLowerLeftCorner,
                    const Point3D& ac_roUpperRightCorner,
                    const Point3D& ac_roForward = Point3D::Unit(0),
                    const Color::ColorVector& ac_roColor = Color::WHITE );
    AnimatedSprite( Texture& a_roTexture,
                    const Frame::Array&& ac_rroFrameList,
                    double a_dFPS, unsigned int a_uiLoops,
                    Callback a_pOnComplete,
                    const Point2D& ac_roScale = Point2D( 1.0 ),
                    const Point3D& ac_roPosition = Point3D::Origin(),
                    const Rotation3D& ac_roRotation = Rotation3D::None(),
                    const Color::ColorVector& ac_roColor = Color::WHITE );
    AnimatedSprite( Texture& a_roTexture,
                    const Frame::Array&& ac_rroFrameList,
                    double a_dFPS, unsigned int a_uiLoops,
                    Callback a_pOnComplete,
                    const Point2D& ac_roScale,
                    const Point3D& ac_roPosition,
                    const Point3D& ac_roForward,
                    const Point3D& ac_roUp = Point3D::Unit(2),
                    const Color::ColorVector& ac_roColor = Color::WHITE );
    AnimatedSprite( Texture& a_roTexture,
                    const Frame::Array&& ac_rroFrameList,
                    double a_dFPS, unsigned int a_uiLoops,
                    Callback a_pOnComplete,
                    const Point3D& ac_roLowerLeftCorner,
                    const Point3D& ac_roUpperRightCorner,
                    const Point3D& ac_roForward = Point3D::Unit(0),
                    const Color::ColorVector& ac_roColor = Color::WHITE );

};  // class AnimatedSprite

}   // namespace MyFirstEngine

#endif  // ANIMATED_SPRITE__H
