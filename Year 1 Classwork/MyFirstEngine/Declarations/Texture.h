/******************************************************************************
 * File:               Texture.h
 * Author:             Elizabeth Lowry
 * Date Created:       March 6, 2014
 * Description:        Class representing an texture.
 * Last Modified:      March 6, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef TEXTURE__H
#define TEXTURE__H

#include "GLFW.h"
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
             GLenum a_eMinFilter = GL_NEAREST_MIPMAP_LINEAR,
             GLenum a_eMagFilter = GL_NEAREST,
             const Color::ColorVector& ac_roBorderColor = Color::TRANSPARENT );
    virtual ~Texture();

    bool IsCurrent() const; // is this loaded in the current texture unit?
    bool IsLoaded() const;  // is this loaded in any texture unit?

#ifndef MY_FIRST_ENGINE_CACHE_TEXTURES
#define TEXTURE__H__CACHE_TEXTURES false
#else
#define TEXTURE__H__CACHE_TEXTURES true
#endif
    void Destroy( bool a_bCache = TEXTURE__H__CACHE_TEXTURES ); // destroy
    void Load( bool a_bCache = TEXTURE__H__CACHE_TEXTURES );
                            // load this texture to an unused texture unit (if
                            //  not already loaded), unloading other textures if
                            //  neccessary
#undef TEXTURE__H__CACHE_TEXTURES
    void MakeCurrent();     // make this texture's unit active (load if needed)

    static bool IsInitialized();    // can textures be loaded?
    static void Initialize();       // get available texture units
    static void Terminate();        // destroy all textures

protected:

    GLuint m_uiID;      // OpenGL id for the texture, 0 = none
    GLenum m_eUnit;     // texture unit to which this texture is bound, 0 = none

    IntPoint2D m_oSize; // size in pixels
    GLenum m_eMinFilter;    // default is GL_NEAREST_MIPMAP_LINEAR
    GLenum m_eMagFilter;    // default is GL_NEAREST
    GLenum m_eWrapT;        // default is GL_CLAMP_TO_EDGE
    GLenum m_eWrapS;        // default is GL_CLAMP_TO_EDGE
    Color::ColorVector m_oBorderColor;  // if wrap setting is GL_CLAMP_TO_BORDER

    DumbString m_oFile;         // file from which this texture is loaded
    unsigned char* m_paucData;  // texture data cache

};

}   // namespace MyFirstEngine

#endif  // TEXTURE__H
