/******************************************************************************
 * File:               Drawable.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       February 24, 2014
 * Description:        Implementations for Drawable member functions.
 * Last Modified:      February 24, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#include "../Declarations/Drawable.h"

namespace MyFirstEngine
{

// Constructor
Drawable::Drawable( ShaderProgram* a_poProgram )
    : m_oColor( Color::WHITE ), m_dYaw( 0.0 ), m_dPitch( 0.0 ), m_dRoll( 0.0 ),
      m_oPosition( Point3D::Origin ), m_oScale( Point3D( 1.0 ) ),
      m_oTransform( Transform3D::Identity() ), m_poProgram( a_poProgram ),
      m_bVisible( true ) {}
Drawable::Drawable( Color::Hex a_oColor, ShaderProgram* a_poProgram )
    : m_oColor( a_oColor ), m_dYaw( 0.0 ), m_dPitch( 0.0 ), m_dRoll( 0.0 ),
      m_oPosition( Point3D::Origin ), m_oScale( Point3D( 1.0 ) ),
      m_oTransform( Transform3D::Identity() ), m_poProgram( a_poProgram ),
      m_bVisible( true ) {}

// Create a full transformation matrix based on the scale, rotations,
// positions, and additional transform
void Drawable::AssembleTransform()
{
    m_oTransform = Space::Scaling( m_oScale );
    m_oTransform *= Space::Rotation( m_dRoll, Point3D::Unit( 0 ) );
    m_oTransform *= Space::Rotation( m_dPitch, Point3D::Unit( 1 ) );
    m_oTransform *= Space::Rotation( m_dYaw, Point3D::Unit( 2 ) );
    m_oTransform *= Space::Translation( m_oPosition );
    m_oTransform *= m_oExtraTransform;
}

// Draw the object to the screen
void Drawable::Draw() const
{
    // In case there is already an active shader program
    ShaderProgram oPreviousProgram = ShaderProgram::Current();

    // Perform setup tasks, such as showing a custom shader program where to
    // look for uniform variable values
    Setup();

    // start using the shader program
    if( nullptr != m_poProgram )
    {
        m_poProgram->Use();
    }

    // set modelview matrix
    AssembleTransform();
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
    glMultTransposeMatrixd( &(m_oTransform[0][0]) );

    // Draw the components of this drawable object - points, lines, other
    // drawable objects, etc.
    DrawComponents();

    // reset modelview matrix
    glMatrixMode( GL_MODELVIEW );
    glPopMatrix();

    // If neccessary, restore previous shader program
    if( nullptr != m_poProgram && *m_poProgram != oPreviousProgram )
    {
        oPreviousProgram.Use();
    }
}

}   // namespace MyFirstEngine
