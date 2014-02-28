/******************************************************************************
 * File:               Drawable.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       February 24, 2014
 * Description:        Implementations for Drawable member functions.
 * Last Modified:      February 27, 2014
 * Last Modification:  Refactoring and debugging.
 ******************************************************************************/

#include "../Declarations/Drawable.h"

namespace MyFirstEngine
{

// Constructor
Drawable::Drawable( ShaderProgram* a_poProgram,
                    const Color::ColorVector& ac_roColor,
                    const Point3D& ac_roScale,
                    const Point3D& ac_roPosition,
                    double a_dYaw, double a_dPitch, double a_dRoll )
    : m_oColor( ac_roColor ), m_oScale( ac_roScale ), m_oPosition( ac_roPosition ),
      m_dYaw( a_dYaw ), m_dPitch( a_dPitch ), m_dRoll( a_dRoll ),
      m_poProgram( a_poProgram ), m_oAfterTransform( Transform3D::Identity() ),
      m_oBeforeTransform( Transform3D::Identity() ), m_bVisible( true ),
      m_pbUpdateModelView( new bool ), m_poModelView( new Transform3D )
{
    UpdateModelView();  // cached modelview transform hasn't been generated
}
Drawable::Drawable( const Drawable& ac_roObject )
    : m_oColor( ac_roObject.m_oColor ), m_oScale( ac_roObject.m_oScale ),
      m_oPosition( ac_roObject.m_oPosition ), m_dYaw( ac_roObject.m_dYaw ),
      m_dPitch( ac_roObject.m_dPitch ), m_dRoll( ac_roObject.m_dRoll ),
      m_poProgram( ac_roObject.m_poProgram ), m_bVisible( ac_roObject.m_bVisible ),
      m_oAfterTransform( ac_roObject.m_oAfterTransform ),
      m_oBeforeTransform( ac_roObject.m_oBeforeTransform ),
      m_pbUpdateModelView( new bool ), m_poModelView( new Transform3D )
{
    UpdateModelView();  // cached modelview transform hasn't been generated
}
Drawable& Drawable::operator=( const Drawable& ac_roObject )
{
    m_oColor = ac_roObject.m_oColor;
    m_oScale = ac_roObject.m_oScale;
    m_oPosition = ac_roObject.m_oPosition;
    m_dYaw = ac_roObject.m_dYaw;
    m_dPitch = ac_roObject.m_dPitch;
    m_dRoll = ac_roObject.m_dRoll;
    m_poProgram = ac_roObject.m_poProgram;
    m_bVisible = ac_roObject.m_bVisible;
    m_oAfterTransform = ac_roObject.m_oAfterTransform;
    m_oBeforeTransform = ac_roObject.m_oBeforeTransform;
    UpdateModelView();
    return *this;
}

// Destructor deallocates the dynamically stored modelview transform cache
// and flag.
Drawable::~Drawable()
{
    delete m_pbUpdateModelView;
    delete m_poModelView;
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

    // Set modelview matrix
    // OpenGL uses column vectors, while the MathLibrary transforms are made for
    // use with row vectors.  However, OpenGL stores matrix data in column-major
    // order, while the MathLibrary matrices store data in row-major order, so
    // feeding data from the latter to the former is an automatic transposition.
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
    glMultMatrixd( &( ModelView()[0][0] ) );

    // Draw the components of this drawable object - points, lines, other
    // drawable objects, etc.
    DrawComponents();

    // reset modelview matrix
    glMatrixMode( GL_MODELVIEW );
    glPopMatrix();

    // Restore previous shader program
    roPreviousProgram.Use();
}

// Apply transformations to the current matrix
const Transform3D& Drawable::ModelView() const
{
    // If One of the transformation properties has been updated,
    if( *m_pbUpdateModelView )
    {
        // Recompute the modelview matrix
        *m_poModelView = m_oBeforeTransform * Space::Scaling( m_oScale ) *
                         Space::Rotation( m_dRoll, Point3D::Unit( 0 ) ) *
                         Space::Rotation( m_dPitch, Point3D::Unit( 1 ) ) *
                         Space::Rotation( m_dYaw, Point3D::Unit( 2 ) ) *
                         Space::Translation( m_oPosition ) * m_oAfterTransform;
        *m_pbUpdateModelView = false;
    }
    return *m_poModelView;
}

// Set color
Drawable& Drawable::SetColor( const Color::ColorVector& ac_roColor )
{
    m_oColor = ac_roColor;
    return *this;
}
Drawable& Drawable::SetColor( float a_fRed, float a_fGreen, float a_fBlue,
                              float a_fAlpha )
{
    m_oColor.r = a_fRed;
    m_oColor.g = a_fGreen;
    m_oColor.b = a_fBlue;
    m_oColor.a = a_fAlpha;
    return *this;
}
Drawable& Drawable::SetColor( Color::Channel a_ucRed,
                              Color::Channel a_ucGreen,
                              Color::Channel a_ucBlue,
                              Color::Channel a_ucAlpha )
{
    m_oColor.RedChannel( a_ucRed );
    m_oColor.GreenChannel( a_ucGreen );
    m_oColor.BlueChannel( a_ucBlue );
    m_oColor.AlphaChannel( a_ucAlpha );
    return *this;
}

// Add rotation properties
Drawable& Drawable::AddPitch( double a_dPitch )
{
    if( a_dPitch != 0.0 )
    {
        m_dPitch += a_dPitch;
        UpdateModelView();
    }
    return *this;
}
Drawable& Drawable::AddRoll( double a_dRoll )
{
    if( a_dRoll != 0.0 )
    {
        m_dRoll += a_dRoll;
        UpdateModelView();
    }
    return *this;
}
Drawable& Drawable::AddYaw( double a_dYaw )
{
    if( a_dYaw != 0.0 )
    {
        m_dYaw += a_dYaw;
        UpdateModelView();
    }
    return *this;
}
Drawable& Drawable::AddRotation( double a_dYaw, double a_dPitch, double a_dRoll )
{
    if( a_dYaw != 0.0 || a_dPitch != 0.0 || a_dRoll != 0.0 )
    {
        m_dYaw += a_dYaw;
        m_dPitch += a_dPitch;
        m_dRoll += a_dRoll;
        UpdateModelView();
    }
    return *this;
}

// Set rotation properties
Drawable& Drawable::SetPitch( double a_dPitch )
{
    if( a_dPitch != m_dPitch )
    {
        m_dPitch = a_dPitch;
        UpdateModelView();
    }
    return *this;
}
Drawable& Drawable::SetRoll( double a_dRoll )
{
    if( a_dRoll != m_dRoll )
    {
        m_dRoll = a_dRoll;
        UpdateModelView();
    }
    return *this;
}
Drawable& Drawable::SetYaw( double a_dYaw )
{
    if( a_dYaw != m_dYaw )
    {
        m_dYaw = a_dYaw;
        UpdateModelView();
    }
    return *this;
}
Drawable& Drawable::SetRotation( double a_dYaw, double a_dPitch, double a_dRoll )
{
    if( a_dYaw != m_dYaw || a_dPitch != m_dPitch || a_dRoll != m_dRoll )
    {
        m_dYaw = a_dYaw;
        m_dPitch = a_dPitch;
        m_dRoll = a_dRoll;
        UpdateModelView();
    }
    return *this;
}

// Add position and scale
Drawable& Drawable::AddPosition( const Point3D& ac_roPosition )
{
    if( ac_roPosition != m_oPosition )
    {
        m_oPosition += ac_roPosition;
        UpdateModelView();
    }
    return *this;
}
Drawable& Drawable::AddPosition( double a_dX, double a_dY, double a_dZ )
{
    if( a_dX != m_oPosition.x || a_dY != m_oPosition.y || a_dZ != m_oPosition.z )
    {
        m_oPosition.x += a_dX;
        m_oPosition.y += a_dY;
        m_oPosition.z += a_dZ;
        UpdateModelView();
    }
    return *this;
}
Drawable& Drawable::AddScale( const Point3D& ac_roScale )
{
    if( ac_roScale != m_oScale )
    {
        m_oScale += ac_roScale;
        UpdateModelView();
    }
    return *this;
}
Drawable& Drawable::AddScale( double a_dX, double a_dY, double a_dZ )
{
    if( a_dX != m_oScale.x || a_dY != m_oScale.y || a_dZ != m_oScale.z )
    {
        m_oScale.x += a_dX;
        m_oScale.y += a_dY;
        m_oScale.z += a_dZ;
        UpdateModelView();
    }
    return *this;
}
Drawable& Drawable::AddScale( double a_dFactor )
{
    if( a_dFactor != m_oScale.x ||
        a_dFactor != m_oScale.y ||
        a_dFactor != m_oScale.z )
    {
        m_oScale.x += a_dFactor;
        m_oScale.y += a_dFactor;
        m_oScale.z += a_dFactor;
        UpdateModelView();
    }
    return *this;
}

// Set position and scale
Drawable& Drawable::
    SetPosition( const Point3D& ac_roPosition )
{
    if( ac_roPosition != m_oPosition )
    {
        m_oPosition = ac_roPosition;
        UpdateModelView();
    }
    return *this;
}
Drawable& Drawable::SetPosition( double a_dX, double a_dY, double a_dZ )
{
    if( a_dX != m_oPosition.x || a_dY != m_oPosition.y || a_dZ != m_oPosition.z )
    {
        m_oPosition.x = a_dX;
        m_oPosition.y = a_dY;
        m_oPosition.z = a_dZ;
        UpdateModelView();
    }
    return *this;
}
Drawable& Drawable::SetScale( const Point3D& ac_roScale )
{
    if( ac_roScale != m_oScale )
    {
        m_oScale = ac_roScale;
        UpdateModelView();
    }
    return *this;
}
Drawable& Drawable::SetScale( double a_dX, double a_dY, double a_dZ )
{
    if( a_dX != m_oScale.x || a_dY != m_oScale.y || a_dZ != m_oScale.z )
    {
        m_oScale.x = a_dX;
        m_oScale.y = a_dY;
        m_oScale.z = a_dZ;
        UpdateModelView();
    }
    return *this;
}
Drawable& Drawable::SetScale( double a_dFactor )
{
    if( a_dFactor != m_oScale.x ||
        a_dFactor != m_oScale.y ||
        a_dFactor != m_oScale.z )
    {
        m_oScale.x = a_dFactor;
        m_oScale.y = a_dFactor;
        m_oScale.z = a_dFactor;
        UpdateModelView();
    }
    return *this;
}

// Apply/Set additional transformation
Drawable& Drawable::ApplyAfterTransform( const Transform3D& ac_roTransform )
{
    if( ac_roTransform != Transform3D::Identity() )
    {
        m_oAfterTransform *= ac_roTransform;
        UpdateModelView();
    }
    return *this;
}
Drawable& Drawable::SetAfterTransform( const Transform3D& ac_roTransform )
{
    if( ac_roTransform != m_oAfterTransform )
    {
        m_oAfterTransform = ac_roTransform;
        UpdateModelView();
    }
    return *this;
}
Drawable& Drawable::ApplyBeforeTransform( const Transform3D& ac_roTransform )
{
    if( ac_roTransform != Transform3D::Identity() )
    {
        m_oBeforeTransform *= ac_roTransform;
        UpdateModelView();
    }
    return *this;
}
Drawable& Drawable::SetBeforeTransform( const Transform3D& ac_roTransform )
{
    if( ac_roTransform != m_oBeforeTransform )
    {
        m_oBeforeTransform = ac_roTransform;
        UpdateModelView();
    }
    return *this;
}

// Show/Hide
Drawable& Drawable::Show()
{
    m_bVisible = true;
    return *this;
}
Drawable& Drawable::Hide()
{
    m_bVisible = false;
    return *this;
}
Drawable& Drawable::SetVisible( bool a_bVisible )
{
    m_bVisible = a_bVisible;
    return *this;
}

}   // namespace MyFirstEngine
