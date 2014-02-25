/******************************************************************************
 * File:               Drawable.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 24, 2014
 * Description:        Base class for drawable objects.
 * Last Modified:      February 24, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef DRAWABLE__H
#define DRAWABLE__H

#include "MathLibrary.h"
#include "ShaderProgram.h"
#include "MyFirstEngineMacros.h"

namespace MyFirstEngine
{

// represents an object that can be drawn on the screen
class IMEXPORT_CLASS Drawable
{
public:

    // The drawable object DOES NOT own the shader object passed in.  A pointer
    // is passed in to distinguish between using whatever shader program is
    // current (indicated by a null pointer) or using no shader program
    // (indicated by a pointer to a program equal to ShaderProgram::Null() )
    Drawable( ShaderProgram* a_poProgram = nullptr );
    Drawable( Color::Hex a_oColor,
              ShaderProgram* a_poProgram = nullptr );
    virtual ~Drawable() {}

    // Draw the object to the screen
    void Draw() const;

    // Add/Get/Set color
    Color::Hex GetColor() const { return m_oColor; }
    void SetColor( Color::Hex a_oHex ) { m_oColor = a_oHex; }

    // Add/Get/Set rotation properties
    void AddPitch( double a_dPitch ) { m_dPitch += a_dPitch; }
    double GetPitch() const { return m_dPitch; }
    void SetPitch( double a_dPitch = 0.0 ) { m_dPitch = a_dPitch; }
    void AddRoll( double a_dRoll ) { m_dRoll += a_dRoll; }
    double GetRoll() const { return m_dRoll; }
    void SetRoll( double a_dRoll = 0.0 ) { m_dRoll = a_dRoll; }
    void AddYaw( double a_dYaw ) { m_dYaw += a_dYaw; }
    double GetYaw() const { return m_dYaw; }
    void SetYaw( double a_dYaw = 0.0 ) { m_dYaw = a_dYaw; }

    // Add/Get/Set Position and Scale
    void AddPosition( const Point3D& ac_roPosition )
    { m_oPosition += ac_roPosition; }
    const Point3D& GetPosition() const { return m_oPosition; }
    void SetPosition( const Point3D& ac_roPosition = Point3D::Origin() )
    { m_oPosition = ac_roPosition; }
    void AddScale( const Point3D& ac_roScale ) { m_oScale += ac_roScale; }
    const Point3D& GetScale() const { return m_oScale; }
    void SetScale( const Point3D& ac_roScale = Point3D( 1.0 ) )
    { m_oScale = ac_roScale; }

    // Apply/Get/Set additional transformation
    void ApplyExtraTransformation( const Transform3D& ac_roTransform )
    { m_oExtraTransform *= ac_roTransform; }
    const Transform3D& GetExtraTransformation() const
    { return m_oExtraTransform; }
    void SetExtraTransformation(
        const Transform3D& ac_roTransform = Transform3D::Identity() )
    { m_oExtraTransform = ac_roTransform; }

    // Show/Hide
    bool IsVisible() const { return m_bVisible; }
    void Show() { m_bVisible = true; }
    void Hide() { m_bVisible = false; }
    void SetVisible( bool a_bVisible ) { m_bVisible = a_bVisible; }

protected:

    // Create a full transformation matrix based on the scale, rotations,
    // positions, and additional transform.  Assumes points are row vectors, so
    // make sure to transpose if the points to transform are column vectors.
    void AssembleTransform();

    // perform any neccessary tasks the shader program needs before its own
    // setup (indicating places to get uniform values from, for example).
    virtual void Setup() const {}

    // This is where the actual work of drawing the object, whatever it is,
    // takes place.
    virtual void DrawComponents() const = 0;

    // Default color for everything
    Color::Hex m_oColor;

    // Basic scale/position/rotation
    double m_dYaw;  // first rotation, about world z-axis
    double m_dPitch;    // second rotation, about model y-axis
    double m_dRoll; // third rotation, about model x-axis
    Point3D m_oPosition;    // applied after rotation
    Point3D m_oScale;   // applied before rotation

    // Additional transformations applied to vertices after the transformations
    // due to the above properties
    Transform3D m_oExtraTransform;

    // The complete modelview transform matrix
    Transform3D m_oTransform;

    // Shader program to use - if null, use whatever program is current
    ShaderProgram* m_poProgram;

    // Is this object even visible?
    bool m_bVisible;

};  // class Drawable

}   // namespace MyFirstEngine

#endif  // DRAWABLE__H
