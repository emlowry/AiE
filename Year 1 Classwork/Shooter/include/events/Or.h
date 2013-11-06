/******************************************************************************
 * File:               Or.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 5, 2013
 * Description:        Event class for at least one of two events occurring.
 * Last Modified:      November 5, 2013
 * Last Modification:  Moving code from Events.h.
 ******************************************************************************/

#ifndef _EVENTS_OR_H_
#define _EVENTS_OR_H_

#include "Events.h"

namespace Events
{
    
// Event triggered by at least one of two events occurring.
// Both events are checked, in case they require ongoing tracking.
template< typename ReturnsBool, typename OtherReturnsBool >
class OrEvent : public DoubleCallback< bool, ReturnsBool, OtherReturnsBool >
{
private:

    typedef DoubleCallback< bool, ReturnsBool, OtherReturnsBool > BaseClass;
    typedef OrEvent< ReturnsBool, OtherReturnsBool > ThisClass;

public:

    OrEvent( ReturnsBool& a_roCall, OtherReturnsBool& a_roOtherCall );
    OrEvent( const ThisClass& ac_roEvent );

    ThisClass* Clone() const override;
    bool operator()() override;

protected:
    
    virtual const char* ClassName() const override;

private:
    
    // Keep copy constructor and assignment operator private to prevent
    // object slicing.  Copy constructor is used by Clone() and should be
    // implemented.  Assignment operator should not be used.
    OrEvent( const ThisClass& ac_roEvent );
    ThisClass& operator=( const ThisClass& ac_roEvent );

    // class name for the hash function to use
    static const char* const CLASS_NAME;

};

}   // namespace Events

#endif  // _EVENTS_OR_H_
