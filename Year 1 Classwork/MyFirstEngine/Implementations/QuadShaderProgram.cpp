/******************************************************************************
 * File:               QuadShaderProgram.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       February 26, 2014
 * Description:        Function implementations for the QuadShaderProgram class.
 * Last Modified:      March 17, 2014
 * Last Modification:  Adding replacement for deprecated OpenGL matrix stack.
 ******************************************************************************/

#include "../Declarations/GameEngine.h"
#include "../Declarations/GLFW.h"
#include "../Declarations/QuadShaderProgram.h"
#include "../Declarations/Shader.h"
#include "../Declarations/ShaderProgram.h"

namespace MyFirstEngine
{

// default quad shader source code files
const char* const QuadShaderProgram::QUAD_VERTEX_SHADER_FILE =
                                            "resources/shaders/QuadVertex.glsl";
const char* const QuadShaderProgram::QUAD_FRAGMENT_SHADER_FILE =
                                          "resources/shaders/QuadFragment.glsl";

// The positions of the four corners of an unscaled, unrotated Quad on the
// XY plane.
const float QuadShaderProgram::QUAD_XY_VERTEX_DATA[8] = { -0.5f, 0.5f,
                                                          0.5f, 0.5f,
                                                          0.5f, -0.5f,
                                                          -0.5f, -0.5f };
const unsigned int QuadShaderProgram::QUAD_ELEMENT_DATA[4] = { 0, 1, 3, 2 };

// only the parent class's Initialize function can call this.
QuadShaderProgram::QuadShaderProgram()
    : m_iModelViewProjectionID( 0 ), m_iColorID( 0 ), m_uiElementBufferID( 0 ),
      m_uiVertexArrayID ( 0 ), m_uiVertexBufferID( 0 ),
      ShaderProgram( Shader( GL_VERTEX_SHADER, QUAD_VERTEX_SHADER_FILE ),
                     Shader( GL_FRAGMENT_SHADER, QUAD_FRAGMENT_SHADER_FILE ) ) {}

// Destroy data used by the shader
void QuadShaderProgram::DestroyData()
{
    // Zero out the uniform variable locations
    m_iModelViewProjectionID = 0;
    m_iColorID = 0;

    // Destroy the vertex array object
    glDeleteVertexArrays( 1, &m_uiVertexArrayID );
    m_uiVertexArrayID = 0;

    // Destroy the buffers
    glDeleteBuffers( 1, &m_uiElementBufferID );
    m_uiElementBufferID = 0;
    glDeleteBuffers( 1, &m_uiVertexBufferID );
    m_uiVertexBufferID = 0;
}

// Load data used by the shader
void QuadShaderProgram::SetupData()
{
    // Get location of uniform variables
    GLint iModelViewProjectionID =
        glGetUniformLocation( m_uiID, "u_dm4ModelViewProjection" );
    GLint iColorID = glGetUniformLocation( m_uiID, "u_v4Color" );

    // Create vertex array object
    GLuint uiVAO;
    glGenVertexArrays( 1, &uiVAO );
    glBindVertexArray( uiVAO );

    // Load Element buffer
    GLuint uiEBO;
    glGenBuffers( 1, &uiEBO );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, uiEBO );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( QUAD_ELEMENT_DATA ),
                  QUAD_ELEMENT_DATA, GL_STATIC_DRAW );

    // Load Vertex buffer
    GLuint uiVBO;
    glGenBuffers( 1, &uiVBO );
    glBindBuffer( GL_ARRAY_BUFFER, uiVBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( QUAD_XY_VERTEX_DATA ),
                  QUAD_XY_VERTEX_DATA, GL_STATIC_DRAW );

    // Specify vertex attributes
    GLint iPositionID = glGetAttribLocation( m_uiID, "i_v2Position" );
    glVertexAttribPointer( iPositionID, 2, GL_FLOAT, GL_FALSE, 0, 0 );
    glEnableVertexAttribArray( iPositionID );

    // Unbind vertex array object so that other initialization calls can't
    // accidentally add things to it
    glBindVertexArray( 0 );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

    // now that everything is initialized, store IDs in static variables
    m_iModelViewProjectionID = iModelViewProjectionID;
    m_iColorID = iColorID;
    m_uiElementBufferID = uiEBO;
    m_uiVertexBufferID = uiVBO;
    m_uiVertexArrayID = uiVAO;
}

// Bind vertex array
void QuadShaderProgram::UseData() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uiElementBufferID );
    glBindVertexArray( m_uiVertexArrayID );
}

//
// Static functions
//

// For use by other shader programs that want to reuse this one's vertex
// data
void QuadShaderProgram::
    BindVertexBuffer( const ShaderProgram& ac_roProgram,
                      const char* ac_pcPositionAttributeName )
{
    glBindBuffer( GL_ARRAY_BUFFER, Instance().m_uiVertexBufferID );
    GLint iPositionID = glGetAttribLocation( ac_roProgram.ID(),
                                             ac_pcPositionAttributeName );
    glVertexAttribPointer( iPositionID, 2, GL_FLOAT, GL_FALSE, 0, 0 );
    glEnableVertexAttribArray( iPositionID );
}

// For use by other shader programs that want to reuse this one's element
// buffer
void QuadShaderProgram::BindElementBuffer()
{
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, Instance().m_uiElementBufferID );
}

// For use by other shader programs that reuse this one's elements
void QuadShaderProgram::DrawElements()
{
    glDrawElements( GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, 0 );
}

// Draw a solid-color 1x1 quad at the origin of the XY plane (in model space)
void QuadShaderProgram::DrawQuad( const Color::ColorVector& ac_roColor )
{
    // save previous program
    const ShaderProgram& oPrevious = ShaderProgram::Current();
    Instance().Use();

    // OpenGL uses column vectors, while the MathLibrary transforms are made for
    // use with row vectors.  However, OpenGL stores matrix data in column-major
    // order, while the MathLibrary matrices store data in row-major order, so
    // feeding data from the latter to the former is an automatic transposition.
    glUniformMatrix4dv( Instance().m_iModelViewProjectionID, 1, false,
                        &( GameEngine::ModelViewProjection()[0][0] ) );
    
    // Set other uniforms and draw
    glUniform4fv( Instance().m_iColorID, 1, &( ac_roColor[0] ) );
    DrawElements();

    // return to previous program
    oPrevious.Use();
}

}   // namespace MyFirstEngine
