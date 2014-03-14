/******************************************************************************
 * File:               Sprite.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 27, 2014
 * Description:        Class representing an textured rectangle, or sprite.
 * Last Modified:      March 13, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

#ifndef SPRITE__H
#define SPRITE__H

#include "Quad.h"
#include "Frame.h"
#include "Texture.h"
#include "MyFirstEngineMacros.h"

namespace MyFirstEngine
{

// A textured rectangle
class IMEXPORT_CLASS Sprite : public Quad
{
public:

    // Main constructors
    Sprite( Texture* a_poTexture = nullptr,
            const Point2D& ac_roScale = Point2D( 1.0 ),
            const Point3D& ac_roPosition = Point3D::Origin(),
            const Rotation3D& ac_roRotation = Rotation3D::None(),
            const Color::ColorVector& ac_roColor = Color::WHITE );
    Sprite( Texture* a_poTexture,
            const Point3D& ac_roLowerLeftCorner,
            const Point3D& ac_roUpperRightCorner,
            const Point3D& ac_roForward = Point3D::Unit(0),
            const Color::ColorVector& ac_roColor = Color::WHITE );
    Sprite( Texture* a_poTexture,
            const Frame::Array* a_pcoFrameList,
            const Point2D& ac_roScale = Point2D( 1.0 ),
            const Point3D& ac_roPosition = Point3D::Origin(),
            const Rotation3D& ac_roRotation = Rotation3D::None(),
            const Color::ColorVector& ac_roColor = Color::WHITE );
    Sprite( Texture* a_poTexture,
            const Frame::Array* a_pcoFrameList,
            const Point3D& ac_roLowerLeftCorner,
            const Point3D& ac_roUpperRightCorner,
            const Point3D& ac_roForward = Point3D::Unit(0),
            const Color::ColorVector& ac_roColor = Color::WHITE );

    // Copy constructor/operator
    Sprite( const Sprite& ac_roSprite );
    Sprite& operator=( const Sprite& ac_roSprite );

    // Destructor
    virtual ~Sprite() {}

    // Frame access operators
    const Frame& GetFrame( unsigned int a_uiFrameNumber ) const;
    const Frame& operator[]( unsigned int a_uiFrameNumber ) const;

    // Frame increment/decrement operators
    Sprite& operator++();   // ++Sprite - returns incremented sprite
    Sprite operator++(int); // Sprite++ - returns copy of pre-increment sprite
    Sprite& operator--();   // --Sprite - returns decremented sprite
    Sprite operator--(int); // Sprite-- - returns copy of pre-decrement sprite

    // Sprite properties
    unsigned int FrameNumber() const { return m_uiFrameNumber; }
    const Frame::Array* FrameList() const { return m_pcoFrameList; }
    unsigned int FrameCount() const
    { return ( nullptr == m_pcoFrameList ? 0 : m_pcoFrameList->Size() ); }
    const Frame& CurrentFrame() const;
    Sprite& SetFrameNumber( unsigned int a_uiFrameNumber );
    Sprite& SetFrameList( const Frame::Array* a_pcoFrameList );
    Texture* GetTexture() const { return m_poTexture; }
    Sprite& SetTexture( Texture* a_poTexture );

    // Current frame properties
    const IntPoint2D& FramePixels() const
    { return CurrentFrame().framePixels; }
    const IntPoint2D& CenterOffset() const
    { return CurrentFrame().centerOffset; }
    const IntPoint2D& SlicePixels() const
    { return CurrentFrame().slicePixels; }
    const IntPoint2D& SliceLocation() const
    { return CurrentFrame().sliceLocation; }
    const IntPoint2D& SliceOffset() const
    { return CurrentFrame().sliceOffset; }
    Frame::Cropping Cropping() const { return CurrentFrame().cropping; }

    // Get/Set display size ( scale / framePixels )
    Point2D DisplaySize() const;
    Sprite& SetDisplaySize( const Point2D& ac_roSize );
    Sprite& SetDisplaySize( double a_dWidth, double a_dHeight );

    // Get UV dimensions for the current frame's slice
    Point2D SliceOffsetUV() const;
    Point2D SliceSizeUV() const;

    // Get the cached model view transformation resulting from this object's
    // scale/rotation/position/pixel dimensions/etc.  If any of those properties
    // have changed since the last time said transformation was calculated,
    // recalculate it.
    virtual const Transform3D& GetModelMatrix() const override;

    // Get the cached texture coordinate transformation resulting from the
    // current frame's dimensions and cropping.  If any of those properties have
    // changed since the last time said transformation was calculated,
    // recalculate it.
    virtual const Transform2D& GetTextureMatrix() const;

    // set a flag indicating that the cached texture coordinate transform matrix
    // for this object should be recalculated
    void UpdateTextureMatrix() { *m_pbUpdateTextureMatrix = true; }

protected:

    // Draw the sprite
    virtual void DrawComponents() const override;
    
    // Default constructor creates null frame list, null texture
    const Frame::Array* m_pcoFrameList;
    unsigned int m_uiFrameNumber;
    Texture* m_poTexture;

    // Transform texture coordinates so that 0 and 1 correspond to slice
    // boundaries, not frame boundaries
    bool* m_pbUpdateTextureMatrix;
    Transform2D* m_poTextureMatrix;

};  // class Sprite

}   // namespace MyFirstEngine

#endif  // SPRITE__H
