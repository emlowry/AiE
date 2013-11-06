/******************************************************************************
 * File:               Not.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 5, 2013
 * Description:        Event class for another event not occurring.
 * Last Modified:      November 5, 2013
 * Last Modification:  Moving code from Events.h.
 ******************************************************************************/

#ifndef _EVENTS__NOT_H_
#define _EVENTS__NOT_H_

#include "Events.h"

namespace Events
{
    
// Event triggered by another event not occurring
class Not : public Event
{
public:

    // Constructors just call base class constructors
    Not( const Event&& ac_rroCall );
    template< typename ReturnsBool >
    Not( ReturnsBool& a_roTarget );

    // No need to implement - default destructor is fine
    virtual ~Not();

    // Implement Clone() so it'll return a Not pointer instead of an Event
    Not* Clone() const override;

    // Returns true if calling the internal pointer returns false
    bool operator()() override;

protected:
    
    // used by the hash function
    const char* ClassName() const override;

    static const char* const CLASS_NAME;

};

}   // namespace Events

typedef Events::Not NotEvent;

#endif  // _EVENTS__NOT_H_
