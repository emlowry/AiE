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

    // TODO

    bool IsCurrent() const; // is this loaded in the current texture unit?
    bool IsLoaded() const;  // is this loaded in any texture unit?
    bool IsValid() const;   // is this actually a texture in OpenGL?

    void Destroy();         // unload and delete this texture
    void MakeCurrent();     // make this texture's unit active (load if needed)
    void Load();            // load this texture to an unused texture unit (if
                            //  not already loaded), unloading other textures if
                            //  neccessary, and make that texture unit current

    static bool IsInitialized();    // can textures be loaded?
    static void Initialize();       // set up texture storage
    static void Terminate();        // destroy all textures

private:
    
    // PIMPLE idiom - these classes are only defined in the cpp, so inheritance
    // from an stl container won't result in warnings.
    class TextureList;
    class UnusedUnits;

    void Load( GLint a_iUnit ); // load to given texture unit
    GLint UnLoad();     // unload from texture unit, return former texture unit

    GLuint m_uiID;      // OpenGL id for the texture
    GLint m_iUnit;      // texture unit to which this texture is bound
    IntPoint2D m_oSize; // size in pixels

    GLenum m_iMinFilter;    // default is GL_NEAREST_MIPMAP_LINEAR
    GLenum m_iMagFilter;    // default is GL_NEAREST
    GLenum m_iWrapT;        // default is GL_CLAMP_TO_EDGE
    GLenum m_iWrapS;        // default is GL_CLAMP_TO_EDGE
    Color::ColorVector m_oBorderColor;  // if wrap setting is GL_CLAMP_TO_BORDER

    DumbString m_oFile;         // file from which this texture is loaded
    unsigned char* m_pucData;   // texture data, if not loaded and no file

    // if this texture is loaded, the loaded textures made current before and
    // after this one was last made current, if any.
    Texture* m_poNextUsedTexture;
    Texture* m_poPreviousUsedTexture;

    // for determining which texture to unload to make room for a new one
    static Texture* m_poMostRecentlyUsedTexture;
    static Texture* m_poLeastRecentlyUsedTexture;

    // store all textures
    static TextureList& m_roList;
    static UnusedUnits& m_roUnits;
};

}   // namespace MyFirstEngine

#endif  // TEXTURE__H
