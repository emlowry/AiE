/******************************************************************************
 * File:               Drawable.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       February 24, 2014
 * Description:        Implementations for Drawable member functions.
 * Last Modified:      February 26, 2014
 * Last Modification:  Changed how transforms are assembled.
 ******************************************************************************/

#include "../Declarations/Drawable.h"

namespace MyFirstEngine
{

// Constructor
Drawable::Drawable( ShaderProgram* a_poProgram,
                    const Color::ColorVector& ac_roColor,
                    const Point2D& ac_roSize,
                    const Point3D& ac_roPosition,
                    double a_dYaw, double a_dPitch, double a_dRoll )
    : m_oColor( ac_roColor ), m_oScale( ac_roSize ), m_oPosition( ac_roPosition ),
      m_dYaw( a_dYaw ), m_dPitch( a_dPitch ), m_dRoll( a_dRoll ),
      m_poProgram( a_poProgram ), m_oAfterTransform( Transform3D::Identity() ),
      m_oBeforeTransform( Transform3D::Identity() ), m_bVisible( true ) {}

// Apply transformations to the current matrix
void Drawable::ApplyTransforms() const
{
    glMultTransposeMatrixd( &( m_oBeforeTransform[0][0] ) );
    Transform3D oTransform = Space::Scaling( m_oScale );
    glMultTransposeMatrixd( &( oTransform[0][0] ) );
    oTransform = Space::Rotation( m_dRoll, Point3D::Unit( 0 ) );
    glMultTransposeMatrixd( &( oTransform[0][0] ) );
    oTransform = Space::Rotation( m_dPitch, Point3D::Unit( 1 ) );
    glMultTransposeMatrixd( &( oTransform[0][0] ) );
    oTransform = Space::Rotation( m_dYaw, Point3D::Unit( 2 ) );
    glMultTransposeMatrixd( &( oTransform[0][0] ) );
    oTransform = Space::Translation( m_oPosition );
    glMultTransposeMatrixd( &( oTransform[0][0] ) );
    glMultTransposeMatrixd( &( m_oAfterTransform[0][0] ) );
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
    const ShaderProgram& roPreviousProgram = ShaderProgram::Current();

    // start using the shader program
    if( nullptr != m_poProgram )
    {
        m_poProgram->Use();
    }

    // set modelview matrix
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
    ApplyTransforms();

    // Draw the components of this drawable object - points, lines, other
    // drawable objects, etc.
    DrawComponents();

    // reset modelview matrix
    glMatrixMode( GL_MODELVIEW );
    glPopMatrix();

    // Restore previous shader program
    roPreviousProgram.Use();
}

}   // namespace MyFirstEngine
