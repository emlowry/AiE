/******************************************************************************
 * File:               AnimatedSprite.h
 * Author:             Elizabeth Lowry
 * Date Created:       March 13, 2014
 * Description:        Class representing an sprite that loops through frames.
 * Last Modified:      March 17, 2014
 * Last Modification:  Adding more constructors.
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
    typedef void (*CompletionCallback)( AnimatedSprite& a_roSprite );
    
    // Main constructors
    AnimatedSprite( Texture* a_poTexture = nullptr,
                    const Point2D& ac_roScale = Point2D( 1.0 ),
                    const Point3D& ac_roPosition = Point3D::Origin(),
                    const Rotation3D& ac_roRotation = Rotation3D::None(),
                    double a_dFPS = 0.0, unsigned int a_uiLoops = 0,
                    CompletionCallback a_pOnComplete = nullptr,
                    const Color::ColorVector& ac_roColor = Color::WHITE );
    AnimatedSprite( Texture* a_poTexture,
                    const Point2D& ac_roScale,
                    const Point3D& ac_roPosition,
                    const Point3D& ac_roForward,
                    const Point3D& ac_roUp = Point3D::Unit(2),
                    double a_dFPS = 0.0, unsigned int a_uiLoops = 0,
                    CompletionCallback a_pOnComplete = nullptr,
                    const Color::ColorVector& ac_roColor = Color::WHITE );
    AnimatedSprite( Texture* a_poTexture,
                    const Point3D& ac_roLowerLeftCorner,
                    const Point3D& ac_roUpperRightCorner,
                    const Point3D& ac_roForward = Point3D::Unit(0),
                    double a_dFPS = 0.0, unsigned int a_uiLoops = 0,
                    CompletionCallback a_pOnComplete = nullptr,
                    const Color::ColorVector& ac_roColor = Color::WHITE );
    AnimatedSprite( Texture* a_poTexture,
                    const Frame::Array* a_pcoFrameList,
                    const Point2D& ac_roScale = Point2D( 1.0 ),
                    const Point3D& ac_roPosition = Point3D::Origin(),
                    const Rotation3D& ac_roRotation = Rotation3D::None(),
                    double a_dFPS = 0.0, unsigned int a_uiLoops = 0,
                    CompletionCallback a_pOnComplete = nullptr,
                    const Color::ColorVector& ac_roColor = Color::WHITE );
    AnimatedSprite( Texture* a_poTexture,
                    const Frame::Array* a_pcoFrameList,
                    const Point2D& ac_roScale,
                    const Point3D& ac_roPosition,
                    const Point3D& ac_roForward,
                    const Point3D& ac_roUp = Point3D::Unit(2),
                    double a_dFPS = 0.0, unsigned int a_uiLoops = 0,
                    CompletionCallback a_pOnComplete = nullptr,
                    const Color::ColorVector& ac_roColor = Color::WHITE );
    AnimatedSprite( Texture* a_poTexture,
                    const Frame::Array* a_pcoFrameList,
                    const Point3D& ac_roLowerLeftCorner,
                    const Point3D& ac_roUpperRightCorner,
                    const Point3D& ac_roForward = Point3D::Unit(0),
                    double a_dFPS = 0.0, unsigned int a_uiLoops = 0,
                    CompletionCallback a_pOnComplete = nullptr,
                    const Color::ColorVector& ac_roColor = Color::WHITE );

    // Copy constructor/operator
    AnimatedSprite( const AnimatedSprite& ac_roSprite );
    AnimatedSprite& operator=( const AnimatedSprite& ac_roSprite );
    AnimatedSprite( const Sprite& ac_roSprite );
    AnimatedSprite& operator=( const Sprite& ac_roSprite );

    // Destructor
    virtual ~AnimatedSprite() {}

    // increment frame if appropriate
    AnimatedSprite& Update( double a_dDeltaTime = 0.0 );

    // adjust frame based on elapsed time (does nothing if m_dFPS is zero)
    AnimatedSprite& CalculateFrame();

    // increment frame and, if neccessary, completed loop count
    AnimatedSprite& IncrementFrame();

    // control progress
    void Play();
    void Pause();
    void Rewind();  // does not pause a playing animation or start a paused one
    void Complete();
    void Seek( int a_uiFrame );
    void Seek( double a_dSeconds );
    void Add( int a_uiFrames );
    void Add( double a_dSeconds );

    // Get properties
    bool IsCompleted() const;
    bool IsPaused() const { return m_bPaused; }
    unsigned int Loops() const { return m_uiLoops; }
    double FPS() const { return m_dFPS; }
    unsigned int CompletedLoops() const { return m_uiCompletedLoops; }
    double ElapsedSeconds() const;
    double LengthInSeconds() const; // returns 0.0 if m_dFPS or m_uiLoops is 0

    // Set properties
    AnimatedSprite& SetLoops( unsigned int a_uiLoops,
                              unsigned int a_uiCompleted = 0 );
    AnimatedSprite& SetFPS( double a_dFPS );
    AnimatedSprite& SetElapsedSeconds( double a_dSeconds );
    AnimatedSprite& SetLengthInSeconds( double a_dSeconds );    // no effect if
                                                                // m_uiLoops = 0

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
    CompletionCallback m_pOnComplete;   // nullptr = do nothing

};  // class AnimatedSprite

}   // namespace MyFirstEngine

#endif  // ANIMATED_SPRITE__H
