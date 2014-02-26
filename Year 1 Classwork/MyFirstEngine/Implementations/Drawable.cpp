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
      m_oPosition( Point3D::Origin() ), m_oScale( Point3D( 1.0 ) ),
      m_oExtraTransform( Transform3D::Identity() ), m_poProgram( a_poProgram ),
      m_bVisible( true ) {}
Drawable::Drawable( const Color::ColorVector& ac_roColor,
                    ShaderProgram* a_poProgram )
    : m_oColor( ac_roColor ), m_dYaw( 0.0 ), m_dPitch( 0.0 ), m_dRoll( 0.0 ),
      m_oPosition( Point3D::Origin() ), m_oScale( Point3D( 1.0 ) ),
      m_oExtraTransform( Transform3D::Identity() ), m_poProgram( a_poProgram ),
      m_bVisible( true ) {}

// Create a full transformation matrix based on the scale, rotations,
// positions, and additional transform
void Drawable::AssembleTransform( Transform3D& a_roTransform ) const
{
    a_roTransform = Space::Scaling( m_oScale );
    a_roTransform *= Space::Rotation( m_dRoll, Point3D::Unit( 0 ) );
    a_roTransform *= Space::Rotation( m_dPitch, Point3D::Unit( 1 ) );
    a_roTransform *= Space::Rotation( m_dYaw, Point3D::Unit( 2 ) );
    a_roTransform *= Space::Translation( m_oPosition );
    a_roTransform *= m_oExtraTransform;
}

// Draw the object to the screen
void Drawable::Draw() const
{
    // Don't bother if the object isn't visible
    if( !m_bVisible )
    {
        return;
    }

    // In case there is already an active shader program
    ShaderProgram oPreviousProgram = ShaderProgram::Current();

    // start using the shader program
    if( nullptr != m_poProgram )
    {
        m_poProgram->Use();
    }

    // set modelview matrix
    Transform3D oTransform;
    AssembleTransform( oTransform );
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
    glMultTransposeMatrixd( &( oTransform[0][0] ) );

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
