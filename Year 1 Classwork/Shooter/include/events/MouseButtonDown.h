/******************************************************************************
 * File:               MouseButtonDown.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 5, 2013
 * Description:        Event class for a mouse button being down.
 * Last Modified:      November 5, 2013
 * Last Modification:  Moving code from Events.h.
 ******************************************************************************/

#ifndef _EVENTS__MOUSE_BUTTON_DOWN_H_
#define _EVENTS__MOUSE_BUTTON_DOWN_H_

#include "events/Typedefs.h"

namespace Events
{
    
// Event that occurs when a key on the keyboard is down.
template< int t_iButton >
class MouseButtonDown : public Event
{
public:
    
    // No need to implement (con/de)structor - default implementations are fine
    MouseButtonDown() {}
    virtual ~MouseButtonDown() {}

    // Implement Clone() to return MouseButtonDown pointer instead of base class
    MouseButtonDown* Clone() const override;

    // Returns true if template button is down
    bool operator()() override;

private:

    // Used by hash function
    const char* ClassName() const override;
    std::size_t TargetHash() const override;

    static const char* const CLASS_NAME;

};

}   // namespace Events

#define MouseButtonDownEvent( KEY ) Events::MouseButtonDown< KEY >()

#include "inline/events/MouseButtonDown.inl"

#endif  // _EVENTS__MOUSE_BUTTON_DOWN_H_
