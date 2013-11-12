/******************************************************************************
 * File:               And.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 5, 2013
 * Description:        Event class for two events both occurring.
 * Last Modified:      November 5, 2013
 * Last Modification:  Moving code from Events.h.
 ******************************************************************************/

#ifndef _EVENTS__AND_H_
#define _EVENTS__AND_H_

#include "Events.h"

namespace Events
{
    
// Event triggered by two events both occurring
class And: public DoubleEvent
{
public:

    // constructors that just call base class constructors
    And( const Cloneable& ac_roCall, const Cloneable& ac_roOtherCall );
    template< typename OtherReturnsBool >
    And( const Cloneable& ac_roCall, OtherReturnsBool& a_roOtherCall );
    template< typename ReturnsBool >
    And( ReturnsBool& a_roCall, const Cloneable& ac_roOtherCall );
    template< typename ReturnsBool, typename OtherReturnsBool >
    And( ReturnsBool& a_roCall, OtherReturnsBool& a_roOtherCall );
    
    // Destructor doesn't need to be implemented - default is fine.
    virtual ~And();

    // Implement Clone() so it returns And pointers instead of base class
    And* Clone() const override;

    // return true if only one of m_poCall() or m_poOtherCall() return true
    bool operator()() override;

private:

    // class name for the hash function to use
    const char* ClassName() const override;
    static const char* const CLASS_NAME;

};

}   // namespace Events

typedef Events::And AndEvent;

#include "inline/events/And.inl"

#endif  // _EVENTS__AND_H_
