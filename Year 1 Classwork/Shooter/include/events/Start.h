/******************************************************************************
 * File:               Start.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 5, 2013
 * Description:        Event class for another event starting to occur.
 * Last Modified:      November 5, 2013
 * Last Modification:  Moving code from Events.h.
 ******************************************************************************/

#ifndef _EVENTS__START_H_
#define _EVENTS__START_H_

#include "events/Typedefs.h"

namespace Events
{
    
// Event triggered by another event starting, but not by said event continuing
class Start : public Event
{
public:

    // Constructors call base class constructors and set Started flag
    Start( const Event& ac_roCall, bool a_bStarted = false );
    template< typename ReturnsBool >
    Start( ReturnsBool& a_roTarget, bool a_bStarted = false );

    // No need to implement - default destructor is fine
    virtual ~Start() {}

    // Implement Clone() so it'll return a Start pointer instead of an Event
    virtual Start* Clone() const override;

    // Returns true if internal call returns true when it wasn't before
    bool operator()() override;

protected:

    // Used by derived class End to avoid unneccessary cloning
    Start( Event* a_poCall, bool a_bStarted );

    // used by the hash function
    virtual const char* ClassName() const override;

    static const char* const CLASS_NAME;

    bool m_bStarted;

};

}   // namespace Events

typedef Events::Start StartEvent;

#include "inline/events/Start.inl"

#endif  // _EVENTS__START_H_
