/******************************************************************************
 * File:               End.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 5, 2013
 * Description:        Event class for another event ceasing to occur.
 * Last Modified:      November 5, 2013
 * Last Modification:  Moving code from Events.h.
 ******************************************************************************/

#ifndef _EVENTS_END_H_
#define _EVENTS_END_H_

#include "Events.h"

namespace Events
{
    
// Event triggered by another event ending
template< typename ReturnsBool >
class EventEnd : public EventStart< ReturnsBool >
{
private:

    typedef EventStart< ReturnsBool > BaseClass;
    typedef EventEnd< ReturnsBool > ThisClass;

public:

    EventEnd( ReturnsBool& a_roEvent, bool a_bStarted = false );
    EventEnd( const ThisClass& a_roEvent );

    ThisClass* Clone() const override;

protected:
    
    virtual const char* ClassName() const override;
    virtual std::size_t TargetHash() const override;

private:
    
    // Keep copy constructor and assignment operator private to prevent
    // object slicing.  Copy constructor is used by Clone() and should be
    // implemented.  Assignment operator should not be used.
    EventEnd( const ThisClass& ac_roEvent );
    ThisClass& operator=( const ThisClass& ac_roEvent );

    // class name for the hash function to use
    static const char* const CLASS_NAME;

    NotEvent<ReturnsBool> m_oNotEvent;
    ReturnsBool* m_poEvent;

};

}   // namespace Events

#endif  // _EVENTS_END_H_
