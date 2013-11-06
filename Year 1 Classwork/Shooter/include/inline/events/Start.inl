/******************************************************************************
 * File:               Start.inl
 * Author:             Elizabeth Lowry
 * Date Created:       November 6, 2013
 * Description:        Inline function implementations for Start.h.
 * Last Modified:      November 6, 2013
 * Last Modification:  Moving code from Events.inl and Events.cpp.
 ******************************************************************************/

#ifndef _EVENTS__START_INL_
#define _EVENTS__START_INL_

#include <utility>  // for std::forward

namespace Events
{

// Public constructors
inline Start::Start( const Event&& ac_rroCall, bool a_bStarted )
    : Event( std::forward< const Event >( ac_rroCall ) ),
      m_bStarted( a_bStarted ) {}
template< typename ReturnsBool >
inline Start::Start( ReturnsBool& a_roCall, bool a_bStarted )
    : Event( a_roCall ), m_bStarted( a_bStarted ) {}

// Protected constructor
inline Start::Start( Event* a_poCall, bool a_bStarted )
    : Event( a_poCall ), m_bStarted( a_bStarted ) {}

// Class name
const char* const Start::CLASS_NAME = "Start";
inline const char* Start::ClassName() const
{
    return CLASS_NAME;
}

// Clone
inline Start* Start::Clone() const
{
    return new Start( *m_poCall, m_bStarted );
}

// operator returns true if internal call returns true when it wasn't before
inline bool Start::operator()()
{
    // The boolean value of a boolean assignment is the value of the left-most
    // variable that gets assigned a value.
    return (*m_poCall)() ? ( m_bStarted ? false : ( m_bStarted = true ) )
                         : ( m_bStarted = false );
}

}   // namespace Events

#endif  // _EVENTS__START_INL_