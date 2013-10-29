/******************************************************************************
 * File:               Events.h
 * Author:             Elizabeth Lowry
 * Date Created:       October 28, 2013
 * Description:        Classes and functions for detecting specific events.
 * Last Modified:      October 28, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef _EVENTS_H_
#define _EVENTS_H_

#include "AIE.h"

namespace Events
{

// Event triggered by a key on the keyboard being down
template< int t_iKey >
bool KeyDownEvent()
{
    return IsKeyDown( t_iKey );
}

// Event triggered by a mouse button being down
template< int t_iButton >
bool MouseButtonDownEvent()
{
    return GetMouseButtonDown( t_iButton );
}

// Event triggered by another event not occurring
template< typename ReturnsBool >
class NotEvent
{
public:
    inline NotEvent( ReturnsBool a_roEvent ) : m_roEvent( a_roEvent ) {}
    inline bool operator()() { return !m_roEvent(); }
private:
    ReturnsBool& m_roEvent;
};

// Event triggered by some combination of multiple options
template< typename... Events >
class MultiEvent
{
public:
    inline MultiEvent( Recursion& a_roRecursion, Events&... a_roEvents )
        : m_roRecursion( a_roRecursion ), m_roEvents( a_roEvents ) {}
    inline bool operator()() { return Recurse( m_roEvents ); }
private:
    Events&... m_roEvents;
    template< typename ReturnsBool >
    virtual bool Recurse( ReturnsBool& a_roEvent, Events&... a_roEvents ) = 0;
};

// Event triggered by only one event occurring out of multiple options
template< typename... Events >
class XOrEvent : public MultiEvent< Events >
{
public:

    inline XOrEvent( Events&... a_roEvents ) : MultiEvent( a_roEvents ) {}

private:

    template< typename ReturnsBool >
    inline bool Recurse( ReturnsBool a_roEvent, Events&... a_roEvents )
    { return a_roEvent() ? RecurseNone( a_roEvents ) : Recurse( a_roEvents ); }

    template< typename ReturnsBool >
    inline bool RecurseNone( ReturnsBool a_roEvent, Events&... a_roEvents )
    { return a_roEvent() ? false : RecurseNone( a_roEvents ); }

    template< typename ReturnsBool >
    inline bool Recurse( ReturnsBool a_roEvent ) { return a_roEvent(); }

    template< typename ReturnsBool >
    inline bool RecurseNone( ReturnsBool a_roEvent ) { return !a_roEvent(); }
};

// Event triggered by at least one event occurring out of multiple options
template< typename... Events >
class OrEvent : public MultiEvent< Events >
{
public:

    inline OrEvent( Events&... a_roEvents ) : MultiEvent( a_roEvents ) {}

private:

    template< typename ReturnsBool >
    inline bool Recurse( ReturnsBool a_roEvent, Events&... a_roEvents )
    { return a_roEvent() || Recurse( a_roEvents ); }

    template< typename ReturnsBool >
    inline bool Recurse( ReturnsBool a_roEvent ) { return a_roEvent(); }
};

// Event triggered by multiple events all occurring
template< typename... Events >
class AndEvent : public MultiEvent< Events >
{
public:

    inline AndEvent( Events&... a_roEvents ) : MultiEvent( a_roEvents ) {}

private:

    template< typename ReturnsBool >
    inline bool Recurse( ReturnsBool a_roEvent, Events&... a_roEvents )
    { return a_roEvent() && Recurse( a_roEvents ); }

    template< typename ReturnsBool >
    inline bool Recurse( ReturnsBool a_roEvent ) { return a_roEvent(); }
};

// Event triggered by another event starting, but not by said event continuing
template< typename ReturnsBool >
class EventStart
{
public:
    inline StartEvent( ReturnsBool& a_roEvent )
        : m_bStarted( false ), m_roEvent( a_roEvent ) {}
    bool operator()();
private:
    bool m_bStarted;
    ReturnsBool& m_roEvent;
};

// Event triggered by another event ending
template< typename ReturnsBool >
class EventEnd : public EventStart< ReturnsBool >
{
public:
    inline EndEvent( ReturnsBool& a_roEvent )
        : m_roNotEvent( a_roEvent ), EventStart( m_roNotEvent ) {}
private:
    NotEvent<ReturnsBool> m_roNotEvent;
};

}   // namespace Events

#endif  // _EVENTS_H_