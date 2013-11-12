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
#include <utility>  // for std::forward

namespace Events
{

// Constructors set internal pointer directly instead of passing to base class
inline End::End( const Event&& ac_rroCall, bool a_bStarted )
    : m_bCall( new Not( std::forward< const Event >( ac_rroCall ) ) ),
      m_bStarted( !a_bStarted ) {}
template< typename ReturnsBool >
inline End::End( ReturnsBool& a_roCall, bool a_bStarted )
    : m_bCall( new Not( a_roCall ) ), m_bStarted( !a_bStarted ) {}

// Class name
const char* const End::CLASS_NAME = "End";
inline const char* End::ClassName() const
{
    return CLASS_NAME;
}

// Clone
inline End* End::Clone() const
{
    // Remember to create the new End using the target of the Not that this
    // object's internal pointer points to
    return new End( *( m_poCall->m_poCall ), !m_bStarted );
}

// Target hash is the hash of the target of the Not that this object's internal
// pointer points to
inline std::size_t End::TargetHash() const
{
    // The boolean value of a boolean assignment is the value of the left-most
    // variable that gets assigned a value.
    return m_poCall->m_poCall->Hash();
}

}   // namespace Events

#endif  // _EVENTS__END_INL_