/******************************************************************************
 * File:               Texture.h
 * Author:             Elizabeth Lowry
 * Date Created:       March 6, 2014
 * Description:        Class representing an texture.
 * Last Modified:      March 17, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

#include "../Declarations/Texture.h"
#include "MathLibrary.h"
#include "SOIL.h"
#include <unordered_map>
#include <vector>

//
// File-local helper classes and functions
//

namespace
{

// all texture units
class TextureList
    : public std::vector< MyFirstEngine::Texture* >,
      public Utility::Singleton< TextureList >
{
    friend class Utility::Singleton< TextureList >;
public:
    virtual ~TextureList() {}
private:
    TextureList() {}
};

// reverse lookup
class TextureLookup
    : public std::unordered_map< MyFirstEngine::Texture*, unsigned int >,
      public Utility::Singleton< TextureLookup >
{
    friend class Utility::Singleton< TextureLookup >;
public:
    typedef std::unordered_map< MyFirstEngine::Texture*, unsigned int > BaseType;
    typedef BaseType::value_type ValueType;
    virtual ~TextureLookup() {}
private:
    TextureLookup() {}
};

// make getting singleton instances shorter to type
static TextureLookup& Lookup() { return TextureLookup::Instance(); }
static TextureList& List() { return TextureList::Instance(); }

}   // namespace

//
// Instance functions
//

namespace MyFirstEngine
{

// Constructor
Texture::Texture( const char* const ac_cpcFile,
                  GLenum a_eWrapS, GLenum a_eWrapT,
                  GLenum a_eMinFilter, GLenum a_eMagFilter,
                  const Color::ColorVector& ac_roBorderColor )
    : m_oSize( 0, 0 ), m_eWrapS( a_eWrapS ), m_eWrapT( a_eWrapT ),
      m_eMinFilter( a_eMinFilter ), m_eMagFilter( a_eMagFilter ),
      m_oBorderColor( ac_roBorderColor ), m_oFile( ac_cpcFile ), 
      m_paucData( nullptr ), m_uiID( 0 ), m_oFrame()
{
    Lookup()[ this ] = List().size();
    List().push_back( this );
}

// Destructor
Texture::~Texture()
{
    Destroy( false );
    List()[ Lookup()[ this ] ] = nullptr;
    Lookup().erase( this );
    unsigned char* paucData = m_paucData;
    m_paucData = nullptr;
    if( nullptr != paucData )
    {
        delete[] paucData;
    }
}

// Is this a valid texture object in OpenGL?
bool Texture::IsValid() const
{
    return ( GL_TRUE == glIsTexture( m_uiID ) );
}

// Unload and delete this texture
void Texture::Destroy( bool a_bCache )
{
    // If already destroyed, just return
    if( !IsValid() )
    {
        return;
    }

    // cache texture data, if neccessary
    if( nullptr == m_paucData && ( m_oFile.IsEmpty() || a_bCache ) )
    {
        glActiveTexture( GL_TEXTURE0 );
        glBindTexture( GL_TEXTURE_2D, m_uiID );
        m_paucData = new unsigned char [ m_oSize.x * m_oSize.y * 4 ];
        glGetTexImage( GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_paucData );
        glBindTexture( GL_TEXTURE_2D, 0 );
    }

    // Destroy the texture object
    glDeleteTextures( 1, &m_uiID );
    m_uiID = 0;
}

// Load this texture to an unused texture unit (if not already loaded),
// unloading other textures if neccessary.
void Texture::Load( bool a_bCache )
{
    // If the image is already loaded, nothing needs to be done
    if( IsValid() )
    {
        return;
    }

    // create the texture
    if( !IsValid() )
    {
        glGenTextures( 1, &m_uiID );
    }

    // bind texture
    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, m_uiID );

    // if there's data in the cache, load it
    if( nullptr != m_paucData )
    {
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, m_oSize.x, m_oSize.y,
                      0, GL_RGBA, GL_UNSIGNED_BYTE, m_paucData );
    }
    else
    {
        // if there's no data in the cache, load using SOIL
        unsigned char* paucData =
            SOIL_load_image( m_oFile, &m_oSize.x, &m_oSize.y, 0, SOIL_LOAD_RGBA );
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, m_oSize.x, m_oSize.y,
                      0, GL_RGBA, GL_UNSIGNED_BYTE, paucData );
        m_oFrame.framePixels = m_oSize;
        m_oFrame.slicePixels = m_oSize;

        // if caching is required, copy to cache
        if( a_bCache )
        {
            m_paucData = new unsigned char[ m_oSize.x * m_oSize.y * 4 ];
            memcpy( m_paucData, paucData, m_oSize.x * m_oSize.y * 4 );
        }

        // Free data loaded with SOIL
        SOIL_free_image_data( paucData );
    }

    // generate mipmaps if neccessary
    if( ( m_eMinFilter != GL_LINEAR && m_eMinFilter != GL_NEAREST ) ||
        ( m_eMagFilter != GL_NEAREST && m_eMagFilter != GL_LINEAR ) )
    {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    // set parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_eMinFilter );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_eMagFilter );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_eWrapS );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_eWrapT );
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, &(m_oBorderColor[0]) );

    // finished loading
    glBindTexture( GL_TEXTURE_2D, 0 );
}

// Make this texture's unit active (load if needed)
void Texture::MakeCurrent()
{
    Load();
    glBindTexture( GL_TEXTURE_2D, m_uiID );
}

//
// Static functions
//

// destroy all textures
void Texture::DestroyAll()
{
    for each( Texture* poTexture in List() )
    {
        if( nullptr != poTexture )
        {
            poTexture->Destroy();
        }
    }
}

}   // namespace MyFirstEngine
