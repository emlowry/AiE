/******************************************************************************
 * File:               Cloneable.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 7, 2013
 * Description:        Abstract parent struct for objects that must be cloned
 *                      instead of copied in order to prevent slicing.
 * Last Modified:      November 7, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef _CLONE__CLONEABLE_H_
#define _CLONE__CLONEABLE_H_

// Derived classes should probably make this a virtual base class in case their
// own derived classes inherit from other derived classes of Cloneable.
class Cloneable
{
public:

    // If you want to make it easier to remember to make a derived class's
    // Clone() return a pointer of the derived type instead of Cloneable, you
    // can use this as the base class instead.
    template< typename Derived >
    class Type : public virtual Cloneable
    {
    public:
        virtual Derived* Clone() const override = 0;
    };

    // Derived classes must implement this function to return a dynamically
    // allocated copy of the current object.  The override declaration should
    // probably return a pointer of the derived type instead of Cloneable.
    virtual Cloneable* Clone() const = 0;

private:

    // Disable copy and move constructors and assignment operators - Cloneable
    // objects should be cloned instead to prevent slicing.
    Cloneable( const Cloneable& ac_roToCopy );
    Cloneable( Cloneable&& a_rroToMove );
    Cloneable& operator=( const Cloneable& ac_roToCopy );
    Cloneable& operator=( Cloneable&& ac_rroToMove );

};

#define CloneableType Cloneable::Type

#endif  // _CLONE__CLONEABLE_H_