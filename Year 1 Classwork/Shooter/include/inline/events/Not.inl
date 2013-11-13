/******************************************************************************
 * File:               Not.inl
 * Author:             Elizabeth Lowry
 * Date Created:       November 6, 2013
 * Description:        Inline function implementations for Not.h.
 * Last Modified:      November 6, 2013
 * Last Modification:  Moving code from Events.inl.
 ******************************************************************************/

#ifndef _EVENTS__NOT_INL_
#define _EVENTS__NOT_INL_

namespace Events
{

// Constructors
inline Not::Not( const Event& ac_roCall ) : Event( ac_roCall ) {}
template< typename ReturnsBool >
inline Not::Not( ReturnsBool& a_roCall ) : Event( a_roCall ) {}
inline Not::Not( Event* a_poCall ) : Event( a_poCall ) {}

// Class name
inline const char* Not::ClassName() const
{
    return CLASS_NAME;
}

// Clone
inline Not* Not::Clone() const
{
    return new Not( *m_poCall );
}

// operator returns true if internal call returns false
inline bool Not::operator()()
{
    return !(*m_poCall)();
}

}   // namespace Events

#endif  // _EVENTS__NOT_INL_