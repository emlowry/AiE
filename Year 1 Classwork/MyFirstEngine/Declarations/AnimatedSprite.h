/******************************************************************************
 * File:               AnimatedSprite.h
 * Author:             Elizabeth Lowry
 * Date Created:       March 13, 2014
 * Description:        Class representing an sprite that loops through frames.
 * Last Modified:      March 13, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef ANIMATED_SPRITE__H
#define ANIMATED_SPRITE__H

#include "Sprite.h"
#include "MyFirstEngineMacros.h"

namespace MyFirstEngine
{

class IMEXPORT_CLASS AnimatedSprite : public Sprite
{
public:

    // animation completion callback
    typedef void (*CompletionCallback)( AnimatedSprite& a_roSprite );
    
    AnimatedSprite( Texture* a_poTexture = nullptr,
                    const Point2D& ac_roSize = Point2D( 1.0 ),
                    const Point3D& ac_roPosition = Point3D::Origin(),
                    const Rotation3D& ac_roRotation = Rotation3D::None(),
                    double a_dFPS = 0.0, unsigned int a_uiLoops = 0,
                    const Color::ColorVector& ac_roColor = Color::WHITE,
                    CompletionCallback a_pOnComplete = nullptr );
    virtual ~AnimatedSprite() {}

    // increment frame if appropriate
    void Update( double a_dDeltaTime );

    // control progress
    void Play();
    void Pause();
    void Rewind();  // does not pause a playing animation or start a paused one

    // Get properties
    bool IsCompleted() const;
    bool IsPaused() const { return m_bPaused; }
    unsigned int CompletedLoops() const { return m_uiCompletedLoops; }
    unsigned int Loops() const { return m_uiLoops; }
    double FPS() const { return m_dFPS; }
    double ElapsedSeconds() const;
    double LengthInSeconds() const; // returns 0.0 if m_dFPS or m_uiLoops is 0

    // Set properties
    AnimatedSprite& SetLoops( unsigned int a_uiLoops,
                              unsigned int a_uiCompleted = 0 );
    AnimatedSprite& SetFPS( double a_dFPS );
    AnimatedSprite& SetElapsedSeconds( double a_dSeconds );
    AnimatedSprite& SetLengthInSeconds( double a_dSeconds );

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
