/******************************************************************************
 * File:               KeyDown.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 5, 2013
 * Description:        Event class for a key being down.
 * Last Modified:      November 5, 2013
 * Last Modification:  Moving code from Events.h.
 ******************************************************************************/

#ifndef _EVENTS__KEY_DOWN_H_
#define _EVENTS__KEY_DOWN_H_

#include "events/Typedefs.h"

namespace Events
{
    
// Event that occurs when a key on the keyboard is down.
template< int t_iKey >
class KeyDown : public Event
{
public:

    // No need to implement (con/de)structor - default implementations are fine
    KeyDown() {}
    virtual ~KeyDown() {}

    // Implement Clone() so it'll return a KeyDown pointer instead of base class
    KeyDown* Clone() const override;

    // Return true if template key is down
    bool operator()() override;

private:

    // Used by the hash function
    const char* ClassName() const override;
    std::size_t TargetHash() const override;

    static const char* const CLASS_NAME;

};

}   // namespace Events

#define KeyDownEvent( KEY ) Events::KeyDown< KEY >()

#include "inline/events/KeyDown.inl"

#endif  // _EVENTS__KEY_DOWN_H_
