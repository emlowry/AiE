/******************************************************************************
 * File:               KeyDown.inl
 * Author:             Elizabeth Lowry
 * Date Created:       November 5, 2013
 * Description:        Inline function implementations for KeyDown.h.
 * Last Modified:      November 5, 2013
 * Last Modification:  Moving code from Events.inl.
 ******************************************************************************/

#ifndef _EVENTS__KEY_DOWN_INL_
#define _EVENTS__KEY_DOWN_INL_

#include "AIE.h"

namespace Events
{

// KeyDown event class name
template< int t_iKey >
const char* const KeyDown< t_iKey >::CLASS_NAME = "KeyDown";
template< int t_iKey >
inline const char* KeyDown< t_iKey >::ClassName() const
{
    return CLASS_NAME;
}

// Allocate a new event checking the same key.
template< int t_iKey >
inline KeyDown< t_iKey >* KeyDown< t_iKey >::Clone() const
{
    return new KeyDown();
}

// Call the AIE framework function
template< int t_iKey >
inline bool KeyDown< t_iKey >::operator()()
{
    return IsKeyDown( t_iKey );
}

// These events are distinguished only by the keys they check, so use the key
// value as the target hash.
template< int t_iKey >
inline std::size_t KeyDown< t_iKey >::TargetHash() const
{
    return (std::size_t)t_iKey;
}

}   // namespace Events

#endif  // _EVENTS__KEY_DOWN_INL_
