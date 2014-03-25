/******************************************************************************
 * File:               Sprite.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       March 5, 2014
 * Description:        Implementations for Sprite functions.
 * Last Modified:      March 17, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

#include "../Declarations/Sprite.h"
#include "../Declarations/SpriteShaderProgram.h"
#include <stdexcept>
#include <vector>

namespace MyFirstEngine
{

// Main constructors
Sprite::Sprite( Texture& a_roTexture,
                const Point2D& ac_roScale,
                const Point3D& ac_roPosition,
                const Rotation3D& ac_roRotation,
                const Color::ColorVector& ac_roColor )
    : Quad( ac_roColor, ac_roScale, ac_roPosition, ac_roRotation ),
      m_poTexture( &a_roTexture ), m_pcoFrameList( nullptr ),
      m_uiFrameNumber( 0 ), m_pbUpdateTextureMatrix( new bool ),
      m_poTextureMatrix( new Transform2D )
{
    UpdateTextureMatrix();
}
Sprite::Sprite( Texture& a_roTexture,
                const Point2D& ac_roScale,
                const Point3D& ac_roPosition,
                const Point3D& ac_roForward,
                const Point3D& ac_roUp,
                const Color::ColorVector& ac_roColor )
    : Quad( ac_roColor, ac_roScale, ac_roPosition, ac_roForward, ac_roUp ),
      m_poTexture( &a_roTexture ), m_pcoFrameList( nullptr ),
      m_uiFrameNumber( 0 ), m_pbUpdateTextureMatrix( new bool ),
      m_poTextureMatrix( new Transform2D )
{
    UpdateTextureMatrix();
}
Sprite::Sprite( Texture& a_roTexture,
                const Point3D& ac_roLowerLeftCorner,
                const Point3D& ac_roUpperRightCorner,
                const Point3D& ac_roForward,
                const Color::ColorVector& ac_roColor )
    : Quad( ac_roColor, ac_roLowerLeftCorner,
            ac_roUpperRightCorner, ac_roForward ),
      m_poTexture( &a_roTexture ), m_pcoFrameList( nullptr ),
      m_uiFrameNumber( 0 ), m_pbUpdateTextureMatrix( new bool ),
      m_poTextureMatrix( new Transform2D )
{
    UpdateTextureMatrix();
}
Sprite::Sprite( Texture& a_roTexture,
                const Frame::Array& ac_roFrameList,
                const Point2D& ac_roScale,
                const Point3D& ac_roPosition,
                const Rotation3D& ac_roRotation,
                const Color::ColorVector& ac_roColor )
    : Quad( ac_roColor, ac_roScale, ac_roPosition, ac_roRotation ),
      m_poTexture( &a_roTexture ), m_pcoFrameList( &ac_roFrameList ),
      m_uiFrameNumber( 0 ), m_pbUpdateTextureMatrix( new bool ),
      m_poTextureMatrix( new Transform2D )
{
    UpdateTextureMatrix();
}
Sprite::Sprite( Texture& a_roTexture,
                const Frame::Array& ac_roFrameList,
                const Point2D& ac_roScale,
                const Point3D& ac_roPosition,
                const Point3D& ac_roForward,
                const Point3D& ac_roUp,
                const Color::ColorVector& ac_roColor )
    : Quad( ac_roColor, ac_roScale, ac_roPosition, ac_roForward, ac_roUp ),
      m_poTexture( &a_roTexture ), m_pcoFrameList( &ac_roFrameList ),
      m_uiFrameNumber( 0 ), m_pbUpdateTextureMatrix( new bool ),
      m_poTextureMatrix( new Transform2D )
{
    UpdateTextureMatrix();
}
Sprite::Sprite( Texture& a_roTexture,
                const Frame::Array& ac_roFrameList,
                const Point3D& ac_roLowerLeftCorner,
                const Point3D& ac_roUpperRightCorner,
                const Point3D& ac_roForward,
                const Color::ColorVector& ac_roColor )
    : Quad( ac_roColor, ac_roLowerLeftCorner,
            ac_roUpperRightCorner, ac_roForward ),
      m_poTexture( &a_roTexture ), m_pcoFrameList( &ac_roFrameList ),
      m_uiFrameNumber( 0 ), m_pbUpdateTextureMatrix( new bool ),
      m_poTextureMatrix( new Transform2D )
{
    UpdateTextureMatrix();
}
    
// Default constructor only callable by derived classes
Sprite::Sprite()
    : m_poTexture( nullptr ), m_pcoFrameList( nullptr ),
      m_uiFrameNumber( 0 ), m_pbUpdateTextureMatrix( new bool ),
      m_poTextureMatrix( new Transform2D ) {}

// Copy constructor/operator
Sprite::Sprite( const Sprite& ac_roSprite )
    : Quad( ac_roSprite ),
      m_poTexture( ac_roSprite.m_poTexture ),
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
    m_poTexture = ac_roSprite.m_poTexture;

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
        return ( nullptr == m_poTexture ? Frame::ZERO
                                         : m_poTexture->TextureFrame() );
    }
    return (*m_pcoFrameList)[ a_uiFrameNumber % FrameCount() ];
}
const Frame& Sprite::operator[]( unsigned int a_uiFrameNumber ) const
{
    if( 0 == FrameCount() )
    {
        return ( nullptr == m_poTexture ? Frame::ZERO
                                         : m_poTexture->TextureFrame() );
    }
    return (*m_pcoFrameList)[ a_uiFrameNumber % FrameCount() ];
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
    SetScale( ( 0 == FramePixels().x ? 0 : a_dWidth / FramePixels().x ),
              ( 0 == FramePixels().y ? 0 : a_dHeight / FramePixels().y ) );
    return *this;
}

// Get UV dimensions for the current frame's slice
Point2D Sprite::SliceOffsetUV() const
{
    return ( nullptr == m_poTexture ? Point2D::Zero() :
             CurrentFrame().SliceOffsetUV( m_poTexture->Size() ) );
}
Point2D Sprite::SliceSizeUV() const
{
    return ( nullptr == m_poTexture ? Point2D::Zero() :
             CurrentFrame().SliceSizeUV( m_poTexture->Size() ) );
}

// Sprite properties
const Frame::Array& Sprite::FrameList() const
{
    return ( nullptr == m_pcoFrameList ? Frame::Array::EMPTY
                                       : *m_pcoFrameList );
}
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
Sprite& Sprite::SetFrameList( const Frame::Array& ac_roFrameList )
{
    // save current frame
    Frame oFrame = CurrentFrame();

    // set frame list
    m_pcoFrameList = ( &Frame::Array::EMPTY == &ac_roFrameList
                       ? nullptr : &ac_roFrameList );
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
Sprite& Sprite::SetTexture( Texture& a_roTexture )
{
    if( &a_roTexture != m_poTexture )
    {
        Frame oFrame = CurrentFrame();
        m_poTexture = &a_roTexture;
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
        CurrentFrame().DisplayAreaVertexTransform( *m_poModelMatrix );
        *m_poModelMatrix *= m_oBeforeTransform *
                            Space::Scaling( m_oScale ) *
                            m_oRotation.MakeTransform() *
                            Space::Translation( m_oPosition ) *
                            m_oAfterTransform;
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
        CurrentFrame().DisplayAreaTextureTransform( *m_poTextureMatrix );
        *m_pbUpdateTextureMatrix = false;
    }
    return *m_poTextureMatrix;
}

// Draw the sprite
void Sprite::DrawComponents() const
{
    // Only draw if there's area to draw
    if( nullptr != m_poTexture && CurrentFrame().HasDisplayArea() )
    {
        SpriteShaderProgram::DrawSprite( *m_poTexture,
                                         SliceOffsetUV(), SliceSizeUV(),
                                         GetTextureMatrix(), m_oColor );
    }
}

}   // namespace MyFirstEngine
