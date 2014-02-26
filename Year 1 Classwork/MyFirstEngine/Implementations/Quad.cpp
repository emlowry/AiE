/******************************************************************************
 * File:               Quad.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       February 24, 2014
 * Description:        Function implementations for the Quad class.
 * Last Modified:      February 25, 2014
 * Last Modification:  Implementation.
 ******************************************************************************/

#include "../Declarations/GLFW.h"
#include "../Declarations/Quad.h"
#include "../Declarations/Shader.h"
#include "../Declarations/ShaderProgram.h"

namespace MyFirstEngine
{

// name of the default quad shader program
const char* const Quad::QUAD_SHADER_PROGRAM_NAME = "Quad";

// default quad shader source code files
const char* const
    Quad::QUAD_VERTEX_SHADER_FILE = "resources/Shaders/QuadVertex.glsl";
const char* const
    Quad::QUAD_FRAGMENT_SHADER_FILE = "resources/Shaders/QuadFragment.glsl";

// The positions of the four corners of an unscaled, unrotated Quad on the
// XY plane.
const float Quad::QUAD_XY_VERTEX_DATA[8] = { -0.5f, 0.5f,
                                             0.5f, 0.5f,
                                             0.5f, -0.5f,
                                             -0.5f, -0.5f };
const unsigned int Quad::QUAD_ELEMENT_DATA[6] = { 0, 1, 2,
                                                  2, 3, 0 };

// Pre-initialization values
GLint Quad::sm_iQuadColorID = 0;
ShaderProgram Quad::sm_oQuadProgram = ShaderProgram::Null();
GLuint Quad::sm_uiQuadElementBufferID = 0;
GLuint Quad::sm_uiQuadVertexBufferID = 0;
GLuint Quad::sm_uiQuadVertexArrayID = 0;

// Public constructor
Quad::Quad( const Point2D& ac_roSize,
            const Point3D& ac_roPosition,
            Color::Hex a_oColor )
    : Drawable( a_oColor, &sm_oQuadProgram )
{
    m_oScale = ac_roSize;
    m_oPosition = ac_roPosition;
}

// Draw the four corners
void Quad::DrawComponents() const
{
    if( IsInitialized() )
    {
        glUniform4fv( sm_iQuadColorID, 1, &( m_oColor[0] ) );
        glBindVertexArray( sm_uiQuadVertexArrayID );
        glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
    }
}

//
// Static functions
//

// Initialize the vertices that get reused every time and load the default
// Quad shader program
void Quad::Initialize()
{
    // Load shader program
    Shader oVertexShader( GL_VERTEX_SHADER, QUAD_VERTEX_SHADER_FILE );
    Shader oFragmentShader( GL_FRAGMENT_SHADER, QUAD_FRAGMENT_SHADER_FILE );
    ShaderProgram oProgram = ShaderProgram( QUAD_SHADER_PROGRAM_NAME,
                                            oVertexShader, oFragmentShader );

    // Get location of color uniform variable
    GLint iColorID = glGetUniformLocation( oProgram.ID(), "u_v4Color" );

    // Create vertex array object
    GLuint uiVAO;
    glGenVertexArrays( 1, &uiVAO );
    glBindVertexArray( uiVAO );

    // Load Vertex buffer
    GLuint uiVBO;
    glGenBuffers( 1, &uiVBO );
    glBindBuffer( GL_ARRAY_BUFFER, uiVBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( QUAD_XY_VERTEX_DATA ),
                  QUAD_XY_VERTEX_DATA, GL_STATIC_DRAW );

    // Specify vertex attributes
    GLint iPositionID = glGetAttribLocation( oProgram.ID(), "i_v2Position" );
    glVertexAttribPointer( iPositionID, 2, GL_FLOAT, GL_FALSE, 0, 0 );
    glEnableVertexAttribArray( iPositionID );

    // Load Element buffer
    GLuint uiEBO;
    glGenBuffers( 1, &uiEBO );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, uiEBO );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( QUAD_ELEMENT_DATA ),
                  QUAD_ELEMENT_DATA, GL_STATIC_DRAW );

    // Unbind vertex array object so that other initialization calls can't
    // accidentally add things to it
    glBindVertexArray( 0 );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

    // now that everything is initialized, store IDs in static variables
    sm_iQuadColorID = iColorID;
    sm_oQuadProgram = oProgram;
    sm_uiQuadElementBufferID = uiEBO;
    sm_uiQuadVertexBufferID = uiVBO;
    sm_uiQuadVertexArrayID = uiVAO;
}

// get rid of the vertex data
void Quad::Terminate()
{
    // Destroy the Quad shader
    sm_oQuadProgram.VertexShader().Delete();
    sm_oQuadProgram.FragmentShader().Delete();
    sm_oQuadProgram.Delete();
    sm_oQuadProgram = ShaderProgram::Null();
    sm_iQuadColorID = 0;

    // Destroy the vertex array object
    glDeleteVertexArrays( 1, &sm_uiQuadVertexArrayID );
    sm_uiQuadVertexArrayID = 0;

    // Destroy the buffers
    glDeleteBuffers( 1, &sm_uiQuadElementBufferID );
    sm_uiQuadElementBufferID = 0;
    glDeleteBuffers( 1, &sm_uiQuadVertexBufferID );
    sm_uiQuadVertexBufferID = 0;
}

}   // namespace MyFirstEngine
