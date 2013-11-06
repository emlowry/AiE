/******************************************************************************
 * File:               And.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 5, 2013
 * Description:        Event class for two events both occurring.
 * Last Modified:      November 5, 2013
 * Last Modification:  Moving code from Events.h.
 ******************************************************************************/

#ifndef _EVENTS_AND_H_
#define _EVENTS_AND_H_

#include "Events.h"

namespace Events
{
    
// Event triggered by two events both occurring
template< typename ReturnsBool, typename OtherReturnsBool >
class AndEvent : public DoubleCallback< bool, ReturnsBool, OtherReturnsBool >
{
private:

    typedef DoubleCallback< bool, ReturnsBool, OtherReturnsBool > BaseClass;
    typedef AndEvent< ReturnsBool, OtherReturnsBool > ThisClass;

public:

    AndEvent( ReturnsBool& a_roCall, OtherReturnsBool& a_roOtherCall );
    AndEvent( const ThisClass& ac_roEvent );

    ThisClass* Clone() const override;
    bool operator()() override;

protected:
    
    virtual const char* ClassName() const override;

private:
    
    // Keep copy constructor and assignment operator private to prevent
    // object slicing.  Copy constructor is used by Clone() and should be
    // implemented.  Assignment operator should not be used.
    AndEvent( const ThisClass& ac_roEvent );
    ThisClass& operator=( const ThisClass& ac_roEvent );

    // class name for the hash function to use
    static const char* const CLASS_NAME;

};

}   // namespace Events

#endif  // _EVENTS_AND_H_
