/******************************************************************************
 * File:               XOr.inl
 * Author:             Elizabeth Lowry
 * Date Created:       November 6, 2013
 * Description:        Inline function implementations for XOr.h.
 * Last Modified:      November 6, 2013
 * Last Modification:  Moving code from Events.inl.
 ******************************************************************************/

#ifndef _EVENTS__XOR_INL_
#define _EVENTS__XOR_INL_

namespace Events
{

// Constructors
inline XOr::XOr( const Event& ac_roCall, const Event& ac_roOtherCall )
    : DoubleEvent( ac_roCall, ac_roOtherCall ) {}
template< typename OtherReturnsBool >
inline XOr::XOr( const Event& ac_roCall, OtherReturnsBool& a_roOtherTarget )
    : DoubleEvent( ac_roCall, a_roOtherTarget ) {}
template< typename ReturnsBool >
inline XOr::XOr( ReturnsBool& a_roTarget, const Event& ac_roOtherCall )
    : DoubleEvent( a_roTarget, ac_roOtherCall ) {}
template< typename ReturnsBool, typename OtherReturnsBool >
inline XOr::XOr( ReturnsBool& a_roTarget, OtherReturnsBool& a_roOtherTarget )
    : DoubleEvent( a_roTarget, a_roOtherTarget ) {}

// Class name
inline const char* XOr::ClassName() const
{
    return CLASS_NAME;
}

// Clone
inline XOr* XOr::Clone() const
{
    return new XOr( *m_poCall, *m_poOtherCall );
}

// operator returns true if only one of the two calls returns true
inline bool XOr::operator()()
{
    return (*m_poCall)() ? !(*m_poOtherCall)() : (*m_poOtherCall)();
}

}   // namespace Events

#endif  // _EVENTS__XOR_INL_
