/******************************************************************************
 * File:               KeyDown.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 5, 2013
 * Description:        Event class for a key being down.
 * Last Modified:      November 5, 2013
 * Last Modification:  Moving code from Events.h.
 ******************************************************************************/

#ifndef _EVENTS_KEY_DOWN_H_
#define _EVENTS_KEY_DOWN_H_

#include "Events.h"

namespace Events
{
    
// Event that occurs when a key on the keyboard is down.
template< t_iKey >
class KeyDown : public Event
{
public:

    KeyDown< t_iKey >* Clone() const override;
    bool operator()() override;

private:

    const char* ClassName() const override;
    std::size_t TargetHash() const override;

    static const char* const CLASS_NAME;

};

}   // namespace Events

#define KeyDownEvent( KEY ) Events::KeyDown< KEY >()

#include "inline/events/KeyDown.inl"

#endif  // _EVENTS_KEY_DOWN_H_
