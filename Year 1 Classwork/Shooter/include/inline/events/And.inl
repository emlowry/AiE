/******************************************************************************
 * File:               And.inl
 * Author:             Elizabeth Lowry
 * Date Created:       November 6, 2013
 * Description:        Inline function implementations for And.h.
 * Last Modified:      November 6, 2013
 * Last Modification:  Moving code from Events.inl.
 ******************************************************************************/

#ifndef _EVENTS__AND_INL_
#define _EVENTS__AND_INL_

#include <utility>  // for std::forward

namespace Events
{

// Constructors
inline And::And( const Event&& ac_rroCall, const Event&& ac_rroOtherCall )
    : DoubleEvent( std::forward< const Event >( ac_rroCall ),
                   std::forward< const Event >( ac_rroOtherCall ) ) {}
template< typename OtherReturnsBool >
inline And::And( const Event&& ac_rroCall, OtherReturnsBool& a_roOtherTarget )
    : DoubleEvent( std::forward< const Event >( ac_rroCall ),
                   a_roOtherTarget ) {}
template< typename ReturnsBool >
inline And::And( ReturnsBool& a_roTarget, const Event&& ac_rroOtherCall )
    : DoubleEvent( a_roTarget,
                   std::forward< const Event >( ac_rroOtherCall ) ) {}
template< typename ReturnsBool, typename OtherReturnsBool >
inline And::And( ReturnsBool& a_roTarget, OtherReturnsBool& ac_rroOtherTarget )
    : DoubleEvent( a_roTarget, a_roOtherTarget ) {}

// Class name
const char* const And::CLASS_NAME = "And";
inline const char* And::ClassName() const
{
    return CLASS_NAME;
}

// Clone
inline And* And::Clone() const
{
    return new And( *m_poCall, *m_poOtherCall );
}

// operator returns true if only one of the two calls returns true
inline bool And::operator()()
{
    return (*m_poCall)() ? !(*m_poOtherCall)() : (*m_poOtherCall)();
}

}   // namespace Events

#endif  // _EVENTS__AND_INL_
