/******************************************************************************
 * File:               Or.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 5, 2013
 * Description:        Event class for at least one of two events occurring.
 * Last Modified:      November 5, 2013
 * Last Modification:  Moving code from Events.h.
 ******************************************************************************/

#ifndef _EVENTS__OR_H_
#define _EVENTS__OR_H_

#include "events/Typedefs.h"

namespace Events
{
    
// Event triggered by at least one of two events occurring.
// Both events are checked, in case they require ongoing tracking.
class Or: public DoubleEvent
{
public:

    // constructors that just call base class constructors
    Or( const Event& ac_roCall, const Event& ac_roOtherCall );
    template< typename OtherReturnsBool >
    Or( const Event& ac_roCall, OtherReturnsBool& a_roOtherTarget );
    template< typename ReturnsBool >
    Or( ReturnsBool& a_roTarget, const Event& a_roOtherCall );
    template< typename ReturnsBool, typename OtherReturnsBool >
    Or( ReturnsBool& a_roCall, OtherReturnsBool& a_roOtherTarget );
    
    // Destructor doesn't need to be implemented - default is fine.
    virtual ~Or() {}

    // Implement Clone() so it returns Or pointers instead of base class
    Or* Clone() const override;

    // return true if at least one of m_poCall() or m_poOtherCall() return true
    bool operator()() override;

private:

    // class name for the hash function to use
    const char* ClassName() const override;
    static const char* const CLASS_NAME;

};

}   // namespace Events

typedef Events::Or OrEvent;

#include "inline/events/Or.inl"

#endif  // _EVENTS__OR_H_
