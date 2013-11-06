/******************************************************************************
 * File:               MouseButtonDown.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 5, 2013
 * Description:        Event class for a mouse button being down.
 * Last Modified:      November 5, 2013
 * Last Modification:  Moving code from Events.h.
 ******************************************************************************/

#ifndef _EVENTS_MOUSE_BUTTON_DOWN_H_
#define _EVENTS_MOUSE_BUTTON_DOWN_H_

#include "Events.h"

namespace Events
{
    
// Event that occurs when a key on the keyboard is down.
template< int t_iButton >
class MouseButtonDown : public Event
{
public:

    MouseButtonDown< t_iButton >* Clone() const override;
    bool operator()() override;

private:

    const char* ClassName() const override;
    std::size_t TargetHash() const override;

    static const char* const CLASS_NAME;

};

}   // namespace Events

#define MouseButtonDownEvent( KEY ) Events::MouseButtonDown< KEY >()

#include "inline/events/MouseButtonDown.inl"

#endif  // _EVENTS_MOUSE_BUTTON_DOWN_H_
