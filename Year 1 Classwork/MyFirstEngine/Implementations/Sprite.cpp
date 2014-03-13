/******************************************************************************
 * File:               Sprite.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       March 5, 2014
 * Description:        Implementations for Sprite functions.
 * Last Modified:      March 12, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

#include "../Declarations/Sprite.h"
#include "../Declarations/SpriteShaderProgram.h"
#include <stdexcept>
#include <vector>

namespace MyFirstEngine
{

// Main constructors
Sprite::Sprite( const Texture* a_pcoTexture,
                const Color::ColorVector& ac_roColor,
                const Point2D& ac_roSize,
                const Point3D& ac_roPosition,
                const Rotation3D& ac_roRotation )
    : Quad( ac_roColor, ac_roSize, ac_roPosition, ac_roRotation ),
      m_pcoTexture( a_pcoTexture ), m_pcoFrameList( nullptr ),
      m_uiFrameNumber( 0 ), m_pbUpdateTextureMatrix( new bool ),
      m_poTextureMatrix( new Transform2D )
{
    UpdateTextureMatrix();
}
Sprite::Sprite( const Texture* a_pcoTexture,
                const Color::ColorVector& ac_roColor,
                const Point3D& ac_roLowerLeftCorner,
                const Point3D& ac_roUpperRightCorner,
                const Point3D& ac_roForward )
    : Quad( ac_roColor, ac_roLowerLeftCorner,
            ac_roUpperRightCorner, ac_roForward ),
      m_pcoTexture( a_pcoTexture ), m_pcoFrameList( nullptr ),
      m_uiFrameNumber( 0 ), m_pbUpdateTextureMatrix( new bool ),
      m_poTextureMatrix( new Transform2D )
{
    UpdateTextureMatrix();
}
Sprite::Sprite( const Texture* a_pcoTexture,
                const Frame::Array* a_pcoFrameList,
                const Color::ColorVector& ac_roColor,
                const Point2D& ac_roSize,
                const Point3D& ac_roPosition,
                const Rotation3D& ac_roRotation )
    : Quad( ac_roColor, ac_roSize, ac_roPosition, ac_roRotation ),
      m_pcoTexture( a_pcoTexture ), m_pcoFrameList( a_pcoFrameList ),
      m_uiFrameNumber( 0 ), m_pbUpdateTextureMatrix( new bool ),
      m_poTextureMatrix( new Transform2D )
{
    UpdateTextureMatrix();
}
Sprite::Sprite( const Texture* a_pcoTexture,
                const Frame::Array* a_pcoFrameList,
                const Color::ColorVector& ac_roColor,
                const Point3D& ac_roLowerLeftCorner,
                const Point3D& ac_roUpperRightCorner,
                const Point3D& ac_roForward )
    : Quad( ac_roColor, ac_roLowerLeftCorner,
            ac_roUpperRightCorner, ac_roForward ),
      m_pcoTexture( a_pcoTexture ), m_pcoFrameList( a_pcoFrameList ),
      m_uiFrameNumber( 0 ), m_pbUpdateTextureMatrix( new bool ),
      m_poTextureMatrix( new Transform2D )
{
    UpdateTextureMatrix();
}

// Copy constructor/operator
Sprite::Sprite( const Sprite& ac_roSprite )
    : Quad( ac_roSprite ),
      m_pcoTexture( ac_roSprite.m_pcoTexture ),
      m_pcoFrameList( ac_roSprite.m_pcoFrameList ),
      m_uiFrameNumber( ac_roSprite.m_uiFrameNumber ),
      m_pbUpdateTextureMatrix( new bool ), m_poTextureMatrix( new Transform2D )
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

// Get/Set display size ( scale / framePixels )
Point2D Sprite::DisplaySize() const
{
    return Point2D( m_oScale.x * FramePixels().x,
                    m_oScale.y * FramePixels().y );
}
Sprite& Sprite::SetDisplaySize( const Point2D& ac_roSize )
{
    return SetDisplaySize( ac_roSize.x, ac_roSize.y );
}
Sprite& Sprite::SetDisplaySize( double a_dWidth, double a_dHeight )
{
    m_oScale.x = ( 0 == FramePixels().x ? 0 : a_dWidth / FramePixels().x );
    m_oScale.y = ( 0 == FramePixels().y ? 0 : a_dHeight / FramePixels().y );
    return *this;
}

// Get UV dimensions for the current frame's slice
Point2D Sprite::SliceOffsetUV() const
{
    // If there's no texture, return zero
    if( nullptr == m_pcoTexture ||
        0 == m_pcoTexture->Size().x ||
        0 == m_pcoTexture->Size().y )
    {
        return Point2D::Zero();
    }

    // otherwise, translate pixel coordinates to UV coordinates
    return Point2D( (double)( SliceOffset().x ) / m_pcoTexture->Size().x,
                    (double)( SliceOffset().y ) / m_pcoTexture->Size().y );
}
Point2D Sprite::SliceSizeUV() const
{
    // If there's no texture, return zero
    if( nullptr == m_pcoTexture ||
        0 == m_pcoTexture->Size().x ||
        0 == m_pcoTexture->Size().y )
    {
        return Point2D::Zero();
    }

    // otherwise, translate pixel coordinates to UV coordinates
    return Point2D( (double)( SlicePixels().x ) / m_pcoTexture->Size().x,
                    (double)( SlicePixels().y ) / m_pcoTexture->Size().y );
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
Sprite& Sprite::SetTexture( const Texture* a_pcoTexture )
{
    if( a_pcoTexture != m_pcoTexture )
    {
        Frame oFrame = CurrentFrame();
        m_pcoTexture = a_pcoTexture;
        if( !oFrame.SameSize( CurrentFrame() ) )
        {
            UpdateModelMatrix();
            UpdateTextureMatrix();
        }
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
        Point3D oDisplayArea = CurrentFrame().DisplayAreaPixels();
        Point3D oOffset = CurrentFrame().DisplayAreaOffset();
        *m_poModelMatrix = Space::Scaling( oDisplayArea ) *
                           Space::Translation( oOffset ) * m_oBeforeTransform *
                           Space::Scaling( m_oScale ) *
                           m_oRotation.MakeTransform() *
                           Space::Translation( m_oPosition ) * m_oAfterTransform;
        *m_pbUpdateModelMatrix = false;
    }
    return *m_poModelMatrix;
}

// Get the cached texture coordinate transformation resulting from the
// current frame's dimensions and cropping.  If any of those properties have
// changed since the last time said transformation was calculated,
// recalculate it.
const Transform2D& Sprite::GetTextureMatrix() const
{
    if( *m_pbUpdateTextureMatrix )
    {
        Point2D oDisplayArea = CurrentFrame().DisplayAreaPixels();
        Point2D oSliceArea = CurrentFrame().slicePixels;
        Point2D oOffset = CurrentFrame().DisplayAreaSliceOffset();
        *m_poTextureMatrix =
            Plane::Scaling( 0 == oSliceArea.x
                            ? 0 : oDisplayArea.x / oSliceArea.x,
                            0 == oSliceArea.y
                            ? 0 : oDisplayArea.y / oSliceArea.y ) *
            Plane::Translation( 0 == oSliceArea.x
                                ? 0 : -oOffset.x / oSliceArea.x,
                                0 == oSliceArea.y
                                ? 0 : -oOffset.y / oSliceArea.y );
        *m_pbUpdateTextureMatrix = false;
    }
    return *m_poTextureMatrix;
}

// Draw the sprite
void Sprite::DrawComponents() const
{
    // Only draw if there's area to draw
    if( nullptr != m_pcoTexture && CurrentFrame().HasDisplayArea() )
    {
        SpriteShaderProgram::DrawSprite( *m_pcoTexture,
                                         SliceOffsetUV(), SliceSizeUV(),
                                         GetTextureMatrix(), m_oColor );
    }
}

}   // namespace MyFirstEngine
