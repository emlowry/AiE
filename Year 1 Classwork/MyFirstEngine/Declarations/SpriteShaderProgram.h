/******************************************************************************
 * File:               SpriteShaderProgram.h
 * Author:             Elizabeth Lowry
 * Date Created:       March 12, 2014
 * Description:        Shader program for Sprite objects.
 * Last Modified:      March 17, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

#ifndef SPRITE_SHADER_PROGRAM__H
#define SPRITE_SHADER_PROGRAM__H

#include "MathLibrary.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "MyFirstEngineMacros.h"

namespace MyFirstEngine
{

using namespace Utility;

// Default Quad shader program
class IMEXPORT_CLASS SpriteShaderProgram
    : public ShaderProgram, public InitializeableSingleton< SpriteShaderProgram >
{
    friend class InitializeableSingleton< SpriteShaderProgram >;

public:

    // virtual destructor present due to inheritance
    virtual ~SpriteShaderProgram() {}
    
    // For use by other shader programs that want to reuse this one's vertex
    // texture coordinate data, like this program reuses the Quad shader's
    // vertex and element data
    static void
        BindTexCoordinateBuffer( const ShaderProgram& ac_roProgram,
                                 const char* ac_pcTexCoordinateAttributeName );
    
    // Draw a textured 1x1 quad at the origin of the XY plane (in model space)
    static void
        DrawSprite( Texture& a_roTexture,
                    const Point2D& ac_roOffsetUV,
                    const Point2D& ac_roSizeUV = Point2D( 1.0, 1.0 ),
                    const Transform2D& ac_roTexTransform = Transform2D::Identity(),
                    const Color::ColorVector& ac_roColor = Color::WHITE );

    // default sprite shader source code files
    static const char* const SPRITE_VERTEX_SHADER_FILE;
    static const char* const SPRITE_FRAGMENT_SHADER_FILE;

    // The texture coordinates of the four corners of a sprite with a frame
    // showing the entire texture within itself with no offsets
    static const float SPRITE_ST_TEX_COORDINATE_DATA[8];
    //static const float SPRITE_XYST_VERTEX_DATA[16];
    //static const unsigned int SPRITE_ELEMENT_DATA[4];

protected:

    // only the parent class's Initialize function can call this.
    SpriteShaderProgram();

    // Instance initialization/termination calls Setup()/Destroy() before
    // constructor/destructor
    virtual void InitializeInstance() override { Setup(); }
    virtual void TerminateInstance() override { Destroy(); }

    // manage the buffers, vertex array, and color uniform variable
    virtual void DestroyData() override;
    virtual void SetupData() override;
    virtual void UseData() const override;
    
    // Uniform variable locations
    GLint m_iModelViewProjectionID;
    GLint m_iTexTransformID;
    GLint m_iColorID;
    GLint m_iTextureID;
    GLint m_iOffsetUVID;
    GLint m_iSizeUVID;
    GLint m_iClampXID;
    GLint m_iClampYID;

    // Vertex array
    GLuint m_uiVertexArrayID;

    // Texture coordinate buffer
    GLuint m_uiTexCoordinateBufferID;

};  // class SpriteShaderProgram

}   // namespace MyFirstEngine

#endif  // SPRITE_SHADER_PROGRAM__H
