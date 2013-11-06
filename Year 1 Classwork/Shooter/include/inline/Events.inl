/******************************************************************************
 * File:               Events.inl
 * Author:             Elizabeth Lowry
 * Date Created:       October 29, 2013
 * Description:        Inline function implementations for Events.h.
 * Last Modified:      October 29, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#include "AIE.h"
#include <functional>
#include <sstream>
#include <string>

namespace Events
{

// Create an event from anything that implements operator() with no parameters to
// return a bool.
template< typename Callable >
Event* NewEvent( Callable& a_roEvent )
{
    return NewCallback< bool >( a_roEvent );
}
Event* NewEvent( const Event&& ac_rroEvent )
{
    return NewCallback< bool >( std::forward< const Event >( ac_rroEvent ) );
}

//
// NotEvent
//

// Constructor
template< typename ReturnsBool >
inline NotEvent< ReturnsBool >::NotEvent( ReturnsBool& a_roCall )
    : BaseClass( a_roCall ) {}

// Copy Constructor
template< typename ReturnsBool >
inline NotEvent< ReturnsBool >::
    NotEvent(const NotEvent< ReturnsBool >& ac_roEvent )
    : BaseClass( *(ac_roEvent.m_poCall) ) {}

// Dynamically allocate a copy pointing to the same event
template< typename ReturnsBool >
inline NotEvent< ReturnsBool >* NotEvent< ReturnsBool >::Clone() const
{
    return new ThisClass( *this );
}

// Class name
template< typename ReturnsBool >
inline const char* const NotEvent< ReturnsBool >::CLASS_NAME = "NotEvent";
template< typename ReturnsBool >
inline const char* NotEvent< ReturnsBool >::ClassName() const
{
    return CLASS_NAME;
}

// Negation of the wrapped call result
template< typename ReturnsBool >
inline bool NotEvent< ReturnsBool >::operator()()
{
    return !(*m_roCall)();
}

//
// XOrEvent
//

// Constructor
template< typename ReturnsBool, typename OtherReturnsBool >
inline XOrEvent< ReturnsBool, OtherReturnsBool >::
    XOrEvent( ReturnsBool& a_roCall, OtherReturnsBool& a_roOtherCall )
    : BaseClass( a_roCall, a_roOtherCall ) {}

// Copy Constructor
template< typename ReturnsBool, typename OtherReturnsBool >
inline XOrEvent< ReturnsBool, OtherReturnsBool >::
    XOrEvent( const ThisClass& ac_roEvent )
    : BaseClass( *(ac_roEvent.m_poCall), *(ac_roEvent.m_poOtherCall) ) {}

// Dynamically allocate a copy pointing to the same events
template< typename ReturnsBool, typename OtherReturnsBool >
inline XOrEvent< ReturnsBool, OtherReturnsBool >*
    XOrEvent< ReturnsBool, OtherReturnsBool >::Clone() const
{
    return new ThisClass( *this );
};

// Exclusive-or of the call results
template< typename ReturnsBool, typename OtherReturnsBool >
inline bool XOrEvent< ReturnsBool, OtherReturnsBool >::operator()()
{
    return (*m_poCall)() ? !(*m_poOtherCall)() : (*m_poOtherCall)();
}

//
// OrEvent
//

// Constructor
template< typename ReturnsBool, typename OtherReturnsBool >
inline OrEvent< ReturnsBool, OtherReturnsBool >::
    OrEvent( ReturnsBool& a_roCall, OtherReturnsBool& a_roOtherCall )
    : BaseClass( a_roCall, a_roOtherCall ) {}

// Copy Constructor
template< typename ReturnsBool, typename OtherReturnsBool >
inline OrEvent< ReturnsBool, OtherReturnsBool >::
    OrEvent(const ThisClass& ac_roEvent )
    : BaseClass( *(ac_roEvent.m_poCall), *(ac_roEvent.m_poOtherCall) ) {}

// Dynamically allocate a copy pointing to the same events
template< typename ReturnsBool, typename OtherReturnsBool >
inline OrEvent< ReturnsBool, OtherReturnsBool >*
    OrEvent< ReturnsBool, OtherReturnsBool >::Clone() const
{
    return new ThisClass( *this );
}

// Exclusive-or of the call results.  Make sure both are checked, in case they
// track their own results.
template< typename ReturnsBool, typename OtherReturnsBool >
inline bool OrEvent< ReturnsBool, OtherReturnsBool >::operator()()
{
    bool bOne = (*m_poCall)();
    return (*m_poOtherCall)() || bOne;
}

//
// AndEvent
//

// Constructor
template< typename ReturnsBool, typename OtherReturnsBool >
inline AndEvent< ReturnsBool, OtherReturnsBool >::
    AndEvent( ReturnsBool& a_roCall, OtherReturnsBool& a_roOtherCall )
    : BaseClass( a_roCall, a_roOtherCall ) {}

// Copy Constructor
template< typename ReturnsBool, typename OtherReturnsBool >
inline AndEvent< ReturnsBool, OtherReturnsBool >::
    AndEvent( const ThisClass& ac_roEvent )
    : BaseClass( *(ac_roEvent.m_poCall), *(ac_roEvent.m_poOtherCall) ) {}

// Dynamically allocate a copy pointing to the same events
template< typename ReturnsBool, typename OtherReturnsBool >
inline AndEvent< ReturnsBool, OtherReturnsBool >*
    AndEvent< ReturnsBool, OtherReturnsBool >::Clone() const
{
    return new ThisClass( *this );
}

// And of the call results.
template< typename ReturnsBoolOne, typename ReturnsBoolTwo >
inline bool AndEvent< ReturnsBool, OtherReturnsBool >::operator()()
{
    return (*a_roCall)() && (*a_roOtherCall)();
}

//
// EventStart
//

// Constructor
template< typename ReturnsBool >
inline EventStart< ReturnsBool >::EventStart( ReturnsBool& a_roCall,
                                              bool a_bStarted )
    : BaseClass( a_roCall ), m_bStarted( a_bStarted ) {}

// Copy Constructor
template< typename ReturnsBool >
inline EventStart< ReturnsBool >::EventStart( const ThisClass& ac_roEvent )
    : BaseClass( *(ac_roEvent.m_poCall) ), m_bStarted( ac_roEvent.m_bStarted ) {}

// Dynamically allocate a copy pointing to the same event
template< typename ReturnsBool >
inline EventStart< ReturnsBool >* EventStart< ReturnsBool >::Clone() const
{
    return new ThisClass( *m_poCall, m_bStarted );
}

//
// EventEnd
//

// Constructor
template< typename ReturnsBool >
inline EventEnd< ReturnsBool >::EventEnd( ReturnsBool& a_roEvent,
                                          bool a_bStarted = false )
    : m_poEvent( &a_roEvent ), m_oNotEvent( a_roEvent ),
      m_poCall( m_oNotEvent ), m_bStarted( !a_bStarted ) {}

// Copy Constructor
template< typename ReturnsBool >
inline EventEnd< ReturnsBool >::EventEnd( const ThisClass& a_roEvent )
    : m_poEvent( a_roEvent.m_poEvent ), m_oNotEvent( *(a_roEvent.m_poEvent) ),
      m_poCall( m_oNotEvent), m_bStarted( a_roEvent.m_bStarted ) {}

// Dynamically allocate a copy pointing to the same event
template< typename ReturnsBool >
inline EventEnd< ReturnsBool >* EventEnd< ReturnsBool >::Clone() const
{
    return new ThisClass( *m_poEvent, !m_bStarted );
}

}   // namespace Events
