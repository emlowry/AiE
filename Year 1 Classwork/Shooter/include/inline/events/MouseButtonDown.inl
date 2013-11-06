/******************************************************************************
 * File:               MouseButtonDown.inl
 * Author:             Elizabeth Lowry
 * Date Created:       November 5, 2013
 * Description:        Inline function implementations for MouseButtonDown.h.
 * Last Modified:      November 5, 2013
 * Last Modification:  Moving code from Events.inl.
 ******************************************************************************/

#include "AIE.h"

namespace Events
{

// MouseButtonDown event class name
template< int t_iButton >
const char* const MouseButtonDown< t_iButton >::CLASS_NAME = "MouseButtonDown";
template< int t_iButton >
inline const char* MouseButtonDown< t_iButton >::ClassName() const
{
    return CLASS_NAME;
}

// Allocate an event checking for the same button being down
template< int t_iButton >
inline MouseButtonDown< t_iButton >* MouseButtonDown< t_iButton >::Clone() const
{
    return new MouseButtonDown();
}

// Call the AIE framework function
template< int t_iButton >
inline bool MouseButtonDown< t_iButton >::operator()()
{
    return GetMouseButtonDown( t_iButton );
}

// These events are distinguished only by the button they check, so use the
// button value as the target hash.
template< int t_iButton >
inline std::size_t MouseButtonDown< t_iButton >::TargetHash() const
{
    return (std::size_t)t_iButton;
}

}   // namespace Events
