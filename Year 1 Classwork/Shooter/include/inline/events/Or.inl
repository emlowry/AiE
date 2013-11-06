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

#include <utility>  // for std::forward

namespace Events
{

// Constructors
inline Or::Or( const Event&& ac_rroCall, const Event&& ac_rroOtherCall )
    : DoubleEvent( std::forward< const Event >( ac_rroCall ),
                   std::forward< const Event >( ac_rroOtherCall ) ) {}
template< typename OtherReturnsBool >
inline Or::Or( const Event&& ac_rroCall, OtherReturnsBool& a_roOtherTarget )
    : DoubleEvent( std::forward< const Event >( ac_rroCall ),
                   a_roOtherTarget ) {}
template< typename ReturnsBool >
inline Or::Or( ReturnsBool& a_roTarget, const Event&& ac_rroOtherCall )
    : DoubleEvent( a_roTarget,
                   std::forward< const Event >( ac_rroOtherCall ) ) {}
template< typename ReturnsBool, typename OtherReturnsBool >
inline Or::Or( ReturnsBool& a_roTarget, OtherReturnsBool& ac_rroOtherTarget )
    : DoubleEvent( a_roTarget, a_roOtherTarget ) {}

// Class name
const char* const Or::CLASS_NAME = "Or";
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
