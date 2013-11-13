/******************************************************************************
 * File:               End.inl
 * Author:             Elizabeth Lowry
 * Date Created:       November 7, 2013
 * Description:        Inline function implementations for End.h.
 * Last Modified:      November 7, 2013
 * Last Modification:  Moving code from Events.inl.
 ******************************************************************************/

#ifndef _EVENTS__END_INL_
#define _EVENTS__END_INL_

#include "events/Not.h"

namespace Events
{

// Constructors set internal pointer directly instead of passing to base class
inline End::End( const Event& ac_roCall, bool a_bStarted )
    : m_poEvent( ac_roCall.Clone() ),
      Start( new Not( m_poEvent ), !a_bStarted ) {}
template< typename ReturnsBool >
inline End::End( ReturnsBool& a_roCall, bool a_bStarted )
    : m_poEvent( new Wrapper< ReturnsBool >( a_roCall ) ),
      Start( new Not( m_poEvent ), !a_bStarted ) {}

// Class name
inline const char* End::ClassName() const
{
    return CLASS_NAME;
}

// Clone
inline End* End::Clone() const
{
    // Remember to create the new End using the target of the Not that this
    // object's internal pointer points to
    return new End( *m_poEvent, !m_bStarted );
}

// Target hash is the hash of the target of the Not that this object's internal
// pointer points to
inline std::size_t End::TargetHash() const
{
    // The boolean value of a boolean assignment is the value of the left-most
    // variable that gets assigned a value.
    return m_poEvent->Hash();
}

}   // namespace Events

#endif  // _EVENTS__END_INL_