/******************************************************************************
 * File:               NotCopyable.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 6, 2014
 * Description:        Base class for non-copyable objects.
 * Last Modified:      February 6, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef NOT_COPYABLE__H
#define NOT_COPYABLE__H

#include "MyFirstEngineMacros.h"

// Classes that inherit from this one can't be copied because this one has
// inaccessable move/copy constructors and assignment operators.
class IMEXPORT_CLASS NotCopyable
{
public:

    // You can still delete a NotCopyable object through a reference of this
    // base type.
    virtual ~NotCopyable() {}

protected:

    // You should never create a plain NotCopyable object, only objects derived
    // from NotCopyable.
    NotCopyable() {}

private:

    // Not only are these private, they're also not implemented.  This ensures
    // that derived classes don't get auto-generated move/copy constructors or
    // assignment operators.
    NotCopyable( const NotCopyable& ac_roOriginal );
    NotCopyable( NotCopyable&& a_rroOriginal );
    NotCopyable& operator=( const NotCopyable& ac_roOriginal );
    NotCopyable& operator=( NotCopyable&& a_rroOriginal );

};  // class NotCopyable

#endif  // NOT_COPYABLE__H