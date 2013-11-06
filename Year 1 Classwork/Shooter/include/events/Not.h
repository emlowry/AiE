/******************************************************************************
 * File:               Not.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 5, 2013
 * Description:        Event class for another event not occurring.
 * Last Modified:      November 5, 2013
 * Last Modification:  Moving code from Events.h.
 ******************************************************************************/

#ifndef _EVENTS_NOT_H_
#define _EVENTS_NOT_H_

#include "Events.h"

namespace Events
{
    
// Event triggered by another event not occurring
template< typename ReturnsBool >
class NotEvent : public CallbackWrapper< bool, ReturnsBool >
{
private:

    typedef CallbackWrapper< bool, ReturnsBool > BaseClass;
    typedef NotEvent< ReturnsBool > ThisClass;

public:

    NotEvent( ReturnsBool a_roCall );
    virtual ~NotEvent();

    ThisClass* Clone() const override;
    bool operator()() override;

protected:
    
    virtual const char* ClassName() const override;

private:
    
    // Keep copy constructor and assignment operator private to prevent
    // object slicing.  Copy constructor is used by Clone() and should be
    // implemented.  Assignment operator should not be used.
    NotEvent( const ThisClass& ac_roEvent );
    ThisClass& operator=( const ThisClass& ac_roEvent );

    // class name for the hash function to use
    static const char* const CLASS_NAME;

};

}   // namespace Events

#endif  // _EVENTS_NOT_H_
