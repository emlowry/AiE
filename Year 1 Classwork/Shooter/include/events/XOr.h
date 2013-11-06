/******************************************************************************
 * File:               XOr.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 5, 2013
 * Description:        Event class for only one of two events occurring.
 * Last Modified:      November 5, 2013
 * Last Modification:  Moving code from Events.h.
 ******************************************************************************/

#ifndef _EVENTS__XOR_H_
#define _EVENTS__XOR_H_

#include "Events.h"

namespace Events
{
    
// Event triggered by only one of two events occurring.
class XOr: public DoubleEvent
{
public:

    // constructors that just call base class constructors
    XOr( const Event&& ac_rroCall, const Event&& ac_rroOtherCall );
    template< typename OtherReturnsBool >
    XOr( const Event&& ac_rroCall, OtherReturnsBool& a_roOtherTarget );
    template< typename ReturnsBool >
    XOr( ReturnsBool& a_roTarget, const Event&& a_roOtherCall );
    template< typename ReturnsBool, typename OtherReturnsBool >
    XOr( ReturnsBool& a_roCall, OtherReturnsBool& a_roOtherTarget );

    // Destructor doesn't need to be implemented - default is fine.
    virtual ~XOr();

    // Implement Clone() so it returns XOr pointers instead of base class
    XOr* Clone() const override;

    // return true if only one of m_poCall() or m_poOtherCall() return true
    bool operator()() override;

private:

    // class name for the hash function to use
    const char* ClassName() const override;
    static const char* const CLASS_NAME;

};

}   // namespace Events

typedef Events::XOr XOrEvent;

#include "inline/events/XOr.inl"

#endif  // _EVENTS__XOR_H_
