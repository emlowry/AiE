/******************************************************************************
 * File:               Texture.h
 * Author:             Elizabeth Lowry
 * Date Created:       March 6, 2014
 * Description:        Class representing an texture.
 * Last Modified:      March 6, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#include "../Declarations/Texture.h"
#include "MathLibrary.h"
#include "SOIL.h"
#include <stack>
#include <unordered_map>
#include <vector>

//
// File-local helper classes and functions
//

// keep track of which loaded textures were most recently used
struct LoadedTexture
{
    MyFirstEngine::Texture* next;
    MyFirstEngine::Texture* previous;
};
MyFirstEngine::Texture* g_poMostRecentlyUsed = nullptr;
MyFirstEngine::Texture* g_poLeastRecentlyUsed = nullptr;

// reverse lookup
class TextureLookup
    : public std::unordered_map< const MyFirstEngine::Texture*, LoadedTexture >,
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

// texture units with no textures loaded
class UnusedUnits
    : public std::stack< GLenum >, public Utility::Singleton< UnusedUnits >
{
    friend class Utility::Singleton< UnusedUnits >;
public:
    virtual ~UnusedUnits() {}
private:
    UnusedUnits() {}
};
unsigned int g_uiMaxUnits = 0;

// make getting singleton instances shorter to type
static TextureLookup& Lookup() { return TextureLookup::Instance(); }
static UnusedUnits& Units() { return UnusedUnits::Instance(); }

// remove a loaded texture from it's current position
static void RemoveLoadedTexture( MyFirstEngine::Texture* a_poTexture )
{
    // get next and previous pointers
    MyFirstEngine::Texture* poNext = Lookup()[ a_poTexture ].next;
    MyFirstEngine::Texture* poPrevious = Lookup()[ a_poTexture ].previous;

    // no need to do more if already done
    if( nullptr == poNext && nullptr == poPrevious )
    {
        return;
    }

    // set pointers to null
    Lookup()[ a_poTexture ].next = nullptr;
    Lookup()[ a_poTexture ].previous = nullptr;

    // adjust next and previous textures' pointers
    if( nullptr != poNext )
    {
        Lookup()[ poNext ].previous = poPrevious;
    }
    if( nullptr != poPrevious )
    {
        Lookup()[ poPrevious ].next = poNext;
    }

    // adjust least/most recently used texture
    if( a_poTexture == g_poLeastRecentlyUsed )
    {
        g_poLeastRecentlyUsed = poNext;
    }
    if( a_poTexture == g_poMostRecentlyUsed )
    {
        g_poMostRecentlyUsed = poPrevious;
    }
}

// insert a loaded texture at the front of the list
static void MakeMostRecentlyUsedTexture( MyFirstEngine::Texture* a_poTexture )
{
    // no need to do anything if already done
    if( a_poTexture == g_poMostRecentlyUsed )
    {
        return;
    }

    // remove from current position
    RemoveLoadedTexture( a_poTexture );

    // insert
    if( nullptr == g_poLeastRecentlyUsed )
    {
        g_poLeastRecentlyUsed = a_poTexture;
    }
    if( nullptr != g_poMostRecentlyUsed )
    {
        Lookup()[ g_poMostRecentlyUsed ].next = a_poTexture;
    }
    Lookup()[ a_poTexture ].previous = g_poMostRecentlyUsed;
    g_poMostRecentlyUsed = a_poTexture;
}

namespace MyFirstEngine
{

//
// Instance functions
//

// Constructor
Texture::Texture( const char* const ac_cpcFile,
                  GLenum a_eWrapS, GLenum a_eWrapT,
                  GLenum a_eMinFilter, GLenum a_eMagFilter,
                  const Color::ColorVector& ac_roBorderColor )
    : m_eWrapS( a_eWrapS ), m_eWrapT( a_eWrapT ),
      m_eMinFilter( a_eMinFilter ), m_eMagFilter( a_eMagFilter ),
      m_oBorderColor( ac_roBorderColor ), m_oFile( ac_cpcFile ), 
      m_paucData( nullptr ), m_uiID( 0 ), m_eUnit( 0 )
{
    LoadedTexture oLoaded = { nullptr, nullptr };
    Lookup()[ this ] = oLoaded;
}

// Destructor
Texture::~Texture()
{
    Destroy( false );
    Lookup().erase( this );
    unsigned char* paucData = m_paucData;
    m_paucData = nullptr;
    if( nullptr != paucData )
    {
        delete[] paucData;
    }
}

// Is this loaded in the current texture unit?
bool Texture::IsCurrent() const
{
    if( glIsTexture( m_uiID ) )
    {
        GLint iActive;
        glGetIntegerv( GL_ACTIVE_TEXTURE, &iActive );
        return ( iActive == m_eUnit );
    }
    return false;
}

// Is this loaded in any texture unit?
bool Texture::IsLoaded() const
{
    return glIsTexture( m_uiID );
}

// Unload and delete this texture
void Texture::Destroy( bool a_bCache )
{
    // If already destroyed, just return
    if( !glIsTexture( m_uiID ) )
    {
        return;
    }

    // cache texture data, if neccessary
    if( ( m_oFile.IsEmpty() || a_bCache ) && nullptr == m_paucData )
    {
        // get the active texture unit before making this one current
        GLint iActive;
        glGetIntegerv( GL_ACTIVE_TEXTURE, &iActive );
        glActiveTexture( m_eUnit );

        // copy data into cache
        m_paucData = new unsigned char [ m_oSize.x * m_oSize.y * 4 ];
        glGetTexImage( GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_paucData );

        // reset the active texture unit
        glActiveTexture( iActive );
    }

    // Destroy the texture object
    glDeleteTextures( 1, &m_uiID );
    Units().push( m_eUnit );
    m_eUnit = 0;
    RemoveLoadedTexture( this );
}

// Load this texture to an unused texture unit (if not already loaded),
// unloading other textures if neccessary.
void Texture::Load( bool a_bCache )
{
    // If the image is already loaded, nothing needs to be done
    if( IsLoaded() )
    {
        return;
    }

    // get the active texture unit
    GLint iActive;
    glGetIntegerv( GL_ACTIVE_TEXTURE, &iActive );

    // get an unused texture unit
    while( Units().empty() )
    {
        if( nullptr == g_poLeastRecentlyUsed )
        {
            throw std::runtime_error( "Texture system not initialized" );
        }
        g_poLeastRecentlyUsed->Destroy( true );
    }
    m_eUnit = Units().top();
    Units().pop();
    glActiveTexture( m_eUnit );

    // create the texture
    glGenTextures( 1, &m_uiID );
    glBindTexture( GL_TEXTURE_2D, m_uiID );

    // set parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_eMinFilter );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_eMagFilter );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_eWrapS );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_eWrapT );
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, &(m_oBorderColor[0]) );

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
            SOIL_load_image( m_oFile, &m_oSize.x, &m_oSize.y, 0, GL_RGBA );
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, m_oSize.x, m_oSize.y,
                      0, GL_RGBA, GL_UNSIGNED_BYTE, paucData );

        // if caching is required, copy to cache
        if( a_bCache )
        {
            m_paucData = new unsigned char[ m_oSize.x * m_oSize.y * 4 ];
            memcpy( m_paucData, paucData, m_oSize.x * m_oSize.y * 4 );
        }

        // Free data loaded with SOIL
        SOIL_free_image_data( paucData );
    }

    // generate mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);

    // finished loading
    glBindTexture( GL_TEXTURE_2D, 0 );
    glActiveTexture( iActive );
    MakeMostRecentlyUsedTexture( this );
}

// Make this texture's unit active (load if needed)
void Texture::MakeCurrent()
{
    // if not loaded, load
    if( !IsLoaded() )
    {
        Load();
    }
    // otherwise, adjust pointers here
    else
    {
        MakeMostRecentlyUsedTexture( this );
    }
    glActiveTexture( m_eUnit );
}

//
// Static functions
//

// can textures be loaded?
bool Texture::IsInitialized()
{
    return !Units().empty();
}

// get available texture units
void Texture::Initialize()
{
    if( !IsInitialized() )
    {
        GLint iMax;
        glGetIntegerv( GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &iMax );
        g_uiMaxUnits = iMax;
        for( GLenum e = GL_TEXTURE0 + iMax - 1; e >= GL_TEXTURE0; --e )
        {
            Units().push( e );
        }
    }
}

// destroy all textures
void Texture::Terminate()
{
    for each( TextureLookup::ValueType oPair in Lookup() )
    {
        oPair.first->Destroy();
    }
    g_poMostRecentlyUsed = nullptr;     // just to be sure
    g_poLeastRecentlyUsed = nullptr;
    while( !Units().empty() )
    {
        Units().pop();
    }
    g_uiMaxUnits = 0;
}

}   // namespace MyFirstEngine
