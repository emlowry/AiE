/******************************************************************************
 * File:               SpriteShaderProgram.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       March 12, 2014
 * Description:        Implementation for SpriteShaderProgram functions.
 * Last Modified:      March 12, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#include "../Declarations/QuadShaderProgram.h"
#include "../Declarations/SpriteShaderProgram.h"

namespace MyFirstEngine
{

// default sprite shader source code files
const char* const SpriteShaderProgram::SPRITE_VERTEX_SHADER_FILE =
                                          "resources/shaders/SpriteVertex.glsl";
const char* const SpriteShaderProgram::SPRITE_FRAGMENT_SHADER_FILE =
                                        "resources/shaders/SpriteFragment.glsl";

// The texture coordinates of the four corners of a sprite with a frame showing
// the entire texture within itself with no offsets
const float SpriteShaderProgram::QUAD_XY_TEX_COORDINATE_DATA[8] = { 0.0f, 0.0f,
                                                                    1.0f, 0.0f,
                                                                    1.0f, 1.0f,
                                                                    0.0f, 0.0f };

// only the parent class's Initialize function can call this.
SpriteShaderProgram::SpriteShaderProgram()
    : m_iTexTransformID( 0 ), m_iColorID( 0 ), m_iTextureID( 0 ),
      m_iOffsetUVID( 0 ), m_iSizeUVID( 0 ), m_iClampXID( 0 ), m_iClampYID( 0 ),
      m_uiVertexArrayID ( 0 ), m_uiTexCoordinateBufferID( 0 ),
      ShaderProgram( Shader( GL_VERTEX_SHADER, SPRITE_VERTEX_SHADER_FILE ),
                     Shader( GL_FRAGMENT_SHADER, SPRITE_FRAGMENT_SHADER_FILE ) ) {}

// Destroy data used by the shader
void SpriteShaderProgram::DestroyData()
{
    // Zero out uniform variable locations
    m_iTexTransformID = 0;
    m_iColorID = 0;
    m_iTextureID = 0;
    m_iOffsetUVID = 0;
    m_iSizeUVID = 0;
    m_iClampXID = 0;
    m_iClampYID = 0;

    // Destroy the vertex array object
    glDeleteVertexArrays( 1, &m_uiVertexArrayID );
    m_uiVertexArrayID = 0;

    // Destroy texture coordinate buffer
    glDeleteBuffers( 1, &m_uiTexCoordinateBufferID );
    m_uiTexCoordinateBufferID = 0;
}

// Load data used by the shader
void SpriteShaderProgram::SetupData()
{
    // Get uniform variable locations
    GLint iTexTransformID = glGetUniformLocation( m_uiID, "u_dm3TexTransform" );
    GLint iColorID = glGetUniformLocation( m_uiID, "u_v4Color" );
    GLint iTextureID = glGetUniformLocation( m_uiID, "u_t2dTexture" );
    GLint iOffsetUVID = glGetUniformLocation( m_uiID, "u_dv2OffsetUV" );
    GLint iSizeUVID = glGetUniformLocation( m_uiID, "u_dv2SizeUV" );
    GLint iClampXID = glGetUniformLocation( m_uiID, "u_bClampX" );
    GLint iClampYID = glGetUniformLocation( m_uiID, "u_bClampY" );

    // Create vertex array object
    GLuint uiVAO;
    glGenVertexArrays( 1, &uiVAO );
    glBindVertexArray( uiVAO );

    // Use Quad shader's element and vertex arrays
    QuadShaderProgram::Initialize();
    QuadShaderProgram::BindElementBuffer();
    QuadShaderProgram::BindVertexBuffer( *this, "i_v2Position" );

    // Load texture coordinate buffer
    GLuint uiVBO;
    glGenBuffers( 1, &uiVBO );
    glBindBuffer( GL_ARRAY_BUFFER, uiVBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( QUAD_XY_TEX_COORDINATE_DATA ),
                  QUAD_XY_TEX_COORDINATE_DATA, GL_STATIC_DRAW );

    // Specify vertex attributes
    GLint iTexCoordinateID = glGetAttribLocation( m_uiID, "i_v2TexCoordinate" );
    glVertexAttribPointer( iTexCoordinateID, 2, GL_FLOAT, GL_FALSE, 0, 0 );
    glEnableVertexAttribArray( iTexCoordinateID );

    // Unbind vertex array object so that other initialization calls can't
    // accidentally add things to it
    glBindVertexArray( 0 );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );

    // now that everything is initialized, store IDs in static variables
    m_iTexTransformID = iTexTransformID;
    m_iColorID = iColorID;
    m_iTextureID = iTextureID;
    m_iOffsetUVID = iOffsetUVID;
    m_iSizeUVID = iSizeUVID;
    m_iClampXID = iClampXID;
    m_iClampYID = iClampYID;
    m_uiTexCoordinateBufferID = uiVBO;
    m_uiVertexArrayID = uiVAO;
}

// Bind vertex array
void SpriteShaderProgram::UseData() const
{
    glBindVertexArray( m_uiVertexArrayID );
}

//
// Static functions
//

// For use by other shader programs that want to reuse this one's vertex
// texture coordinate data, like this program reuses the Quad shader's
// vertex and element data
void SpriteShaderProgram::
    BindTexCoordinateBuffer( const ShaderProgram& ac_roProgram,
                             const char* ac_pcTexCoordinateAttributeName )
{
    glBindBuffer( GL_ARRAY_BUFFER, Instance().m_uiTexCoordinateBufferID );
    GLint iTexCoordinateID =
        glGetAttribLocation( ac_roProgram.ID(),
                             ac_pcTexCoordinateAttributeName );
    glVertexAttribPointer( iTexCoordinateID, 2, GL_FLOAT, GL_FALSE, 0, 0 );
    glEnableVertexAttribArray( iTexCoordinateID );
}

// Draw a textured 1x1 quad at the origin of the XY plane (in model space)
void SpriteShaderProgram::DrawSprite( const Texture& ac_roTexture,
                                      const Point2D& ac_roOffsetUV,
                                      const Point2D& ac_roSizeUV,
                                      const Transform2D& ac_roTexTransform,
                                      const Color::ColorVector& ac_roColor )
{
    // save current shader program
    const ShaderProgram& oPrevious = ShaderProgram::Current();
    Instance().Use();

    // assign uniform values
    glUniformMatrix3dv( Instance().m_iTexTransformID, 1, false,
                        &( ac_roTexTransform[0][0] ) );
    glUniform4fv( Instance().m_iColorID, 1, &( ac_roColor[0] ) );
    glUniform1i( Instance().m_iTextureID, ac_roTexture.Unit() );
    glUniform2dv( Instance().m_iOffsetUVID, 1, &( ac_roOffsetUV[0] ) );
    glUniform2dv( Instance().m_iSizeUVID, 1, &( ac_roSizeUV[0] ) );
    glUniform1i( Instance().m_iClampXID,
                 GL_CLAMP_TO_EDGE == ac_roTexture.WrapS() ? GL_TRUE : GL_FALSE );
    glUniform1i( Instance().m_iClampYID,
                 GL_CLAMP_TO_EDGE == ac_roTexture.WrapT() ? GL_TRUE : GL_FALSE );

    // Use Quad shader's function for drawing elements
    QuadShaderProgram::DrawElements();

    // Resume using previous shader program
    oPrevious.Use();
}

}   // MyFirstEngine
