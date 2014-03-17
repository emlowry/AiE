/******************************************************************************
 * File:               Texture.h
 * Author:             Elizabeth Lowry
 * Date Created:       March 6, 2014
 * Description:        Class representing an texture.
 * Last Modified:      March 12, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

#ifndef TEXTURE__H
#define TEXTURE__H

#include "GLFW.h"
#include "Frame.h"
#include "MathLibrary.h"
#include "MyFirstEngineMacros.h"

namespace MyFirstEngine
{

using Utility::DumbString;

// represents a texture
class IMEXPORT_CLASS Texture : public Utility::NotCopyable
{
public:
    
    // TODO constructor parameters
    Texture( const char* const ac_cpcFile,
             GLenum a_eWrapS = GL_CLAMP_TO_EDGE,
             GLenum a_eWrapT = GL_CLAMP_TO_EDGE,
             GLenum a_eMinFilter = GL_LINEAR_MIPMAP_LINEAR,
             GLenum a_eMagFilter = GL_NEAREST,
             const Color::ColorVector& ac_roBorderColor = Color::TRANSPARENT );
    virtual ~Texture();

    // Get properties
    GLuint ID() const { return m_uiID; }
    const IntPoint2D& Size() const { return m_oSize; }
    const Color::ColorVector& BorderColor() const { return m_oBorderColor; }
    GLenum MinFilter() const { return m_eMinFilter; }
    GLenum MagFilter() const { return m_eMagFilter; }
    GLenum WrapS() const { return m_eWrapS; }
    GLenum WrapT() const { return m_eWrapT; }
    const DumbString& FileName() const { return m_oFile; }
    const Frame& TextureFrame() const { return m_oFrame; }

    bool IsValid() const;   // is this a valid texture object in OpenGL?

#ifndef MY_FIRST_ENGINE_CACHE_TEXTURES
#define TEXTURE__H__CACHE_TEXTURES false
#else
#define TEXTURE__H__CACHE_TEXTURES true
#endif
    void Destroy( bool a_bCache = TEXTURE__H__CACHE_TEXTURES ); // destroy
    void Load( bool a_bCache = TEXTURE__H__CACHE_TEXTURES );    // load data
#undef TEXTURE__H__CACHE_TEXTURES
    void MakeCurrent();     // bind this texture to GL_TEXTURE0

    static void DestroyAll();   // destroy all textures

protected:

    GLuint m_uiID;      // OpenGL id for the texture, 0 = none

    IntPoint2D m_oSize;     // size in pixels
    GLenum m_eMinFilter;    // default is GL_NEAREST_MIPMAP_LINEAR
    GLenum m_eMagFilter;    // default is GL_NEAREST
    GLenum m_eWrapS;        // default is GL_CLAMP_TO_EDGE
    GLenum m_eWrapT;        // default is GL_CLAMP_TO_EDGE
    Color::ColorVector m_oBorderColor;  // if wrap setting is GL_CLAMP_TO_BORDER

    // For no-frame sprites using this texture
    Frame m_oFrame;

    DumbString m_oFile;         // file from which this texture is loaded
    unsigned char* m_paucData;  // texture data cache

};

}   // namespace MyFirstEngine

#endif  // TEXTURE__H
