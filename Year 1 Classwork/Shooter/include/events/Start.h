/******************************************************************************
 * File:               Start.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 5, 2013
 * Description:        Event class for another event starting to occur.
 * Last Modified:      November 5, 2013
 * Last Modification:  Moving code from Events.h.
 ******************************************************************************/

#ifndef _EVENTS_START_H_
#define _EVENTS_START_H_

#include "Events.h"

namespace Events
{
    
// Event triggered by another event starting, but not by said event continuing
template< typename ReturnsBool >
class EventStart : public CallbackWrapper< bool, ReturnsBool >
{
private:

    typedef CallbackWrapper< bool, ReturnsBool > BaseClass;
    typedef EventStart< ReturnsBool > ThisClass;

public:

    EventStart( ReturnsBool& a_roCall, bool a_bStarted = false );
    EventStart( const ThisClass& a_roEvent );

    ThisClass* Clone() const override;
    bool operator()() override;

protected:
    
    virtual const char* ClassName() const override;

private:
    
    // Keep copy constructor and assignment operator private to prevent
    // object slicing.  Copy constructor is used by Clone() and should be
    // implemented.  Assignment operator should not be used.
    EventStart( const ThisClass& ac_roEvent );
    ThisClass& operator=( const ThisClass& ac_roEvent );

    // class name for the hash function to use
    static const char* const CLASS_NAME;

    bool m_bStarted;

};

}   // namespace Events

#endif  // _EVENTS_START_H_
