/******************************************************************************
 * File:               Or.inl
 * Author:             Elizabeth Lowry
 * Date Created:       November 6, 2013
 * Description:        Inline function implementations for Or.h.
 * Last Modified:      November 6, 2013
 * Last Modification:  Moving code from Events.inl.
 ******************************************************************************/

#ifndef _EVENTS__OR_INL_
#define _EVENTS__OR_INL_

namespace Events
{

// Constructors
inline Or::Or( const Event& ac_roCall, const Event& ac_roOtherCall )
    : DoubleEvent( ac_roCall, ac_roOtherCall ) {}
template< typename OtherReturnsBool >
inline Or::Or( const Event& ac_roCall, OtherReturnsBool& a_roOtherTarget )
    : DoubleEvent( ac_roCall, a_roOtherTarget ) {}
template< typename ReturnsBool >
inline Or::Or( ReturnsBool& a_roTarget, const Event& ac_roOtherCall )
    : DoubleEvent( a_roTarget, ac_roOtherCall ) {}
template< typename ReturnsBool, typename OtherReturnsBool >
inline Or::Or( ReturnsBool& a_roTarget, OtherReturnsBool& a_roOtherTarget )
    : DoubleEvent( a_roTarget, a_roOtherTarget ) {}

// Class name
inline const char* Or::ClassName() const
{
    return CLASS_NAME;
}

// Clone
inline Or* Or::Clone() const
{
    return new Or( *m_poCall, *m_poOtherCall );
}

// operator returns true if only one of the two calls returns true
inline bool Or::operator()()
{
    return (*m_poCall)() ? !(*m_poOtherCall)() : (*m_poOtherCall)();
}

}   // namespace Events

#endif  // _EVENTS__OR_INL_
