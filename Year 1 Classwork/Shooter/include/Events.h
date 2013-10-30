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
#include "Callback.h"

namespace Events
{

// Event triggered by a key on the keyboard being down
template< int t_iKey >
bool KeyDownEvent();

// Event triggered by a mouse button being down
template< int t_iButton >
bool MouseButtonDownEvent();

// Event triggered by another event not occurring
template< typename ReturnsBool >
class NotEvent : public CallbackWrapper< bool, ReturnsBool >
{
public:

    NotEvent( ReturnsBool a_roCall );
    NotEvent( const NotEvent< ReturnsBool >& ac_roEvent );

    NotEvent< ReturnsBool >* Clone() const override;
    bool operator()() override;

};

// Abstract event triggered by some combination of events occurring.
template< typename ReturnsBoolOne, typename ReturnsBoolTwo >
class EventCombination : public Callback< bool >
{
public:

    EventCombination( ReturnsBoolOne& a_roCallOne,
                      ReturnsBoolTwo& a_roCallTwo );
    std::size_t Hash() const override;

protected:

    ReturnsBoolOne& m_roCallOne;
    ReturnsBoolTwo& m_roCallTwo;

private:

    // Assignment wouldn't work due to reference members
    EventCombination& operator=( const EventCombination& ac_roEvent );

};

// Event triggered by only one of two events occurring.
template< typename ReturnsBoolOne, typename ReturnsBoolTwo >
class XOrEvent : public EventCombination< ReturnsBoolOne, ReturnsBoolTwo >
{
public:

    XOrEvent( ReturnsBoolOne& a_roCallOne, ReturnsBoolTwo& a_roCallTwo );
    XOrEvent( const XOrEvent< ReturnsBoolOne, ReturnsBoolTwo >& ac_roEvent );

    XOrEvent< ReturnsBoolOne, ReturnsBoolTwo >* Clone() const override;
    bool operator()() override;

};

// Event triggered by at least one of two events occurring.
// Both events are checked, in case they require ongoing tracking.
template< typename ReturnsBoolOne, typename ReturnsBoolTwo >
class OrEvent : public EventCombination< ReturnsBoolOne, ReturnsBoolTwo >
{
public:

    OrEvent( ReturnsBoolOne& a_roCallOne, ReturnsBoolTwo& a_roCallTwo );
    OrEvent( const OrEvent< ReturnsBoolOne, ReturnsBoolTwo >& ac_roEvent );

    OrEvent< ReturnsBoolOne, ReturnsBoolTwo >* Clone() const override;
    bool operator()() override;

};

// Event triggered by two events both occurring
template< typename ReturnsBoolOne, typename ReturnsBoolTwo >
class AndEvent
{
public:

    AndEvent( ReturnsBoolOne& a_roCallOne, ReturnsBoolTwo& a_roCallTwo );
    AndEvent( const AndEvent< ReturnsBoolOne, ReturnsBoolTwo >& ac_roEvent );

    AndEvent< ReturnsBoolOne, ReturnsBoolTwo >* Clone() const override;
    bool operator()() override;

};

// Event triggered by another event starting, but not by said event continuing
template< typename ReturnsBool >
class EventStart : public CallbackWrapper< bool, ReturnsBool >
{
public:

    EventStart( ReturnsBool& a_roCall, bool a_bStarted = false );
    EventStart( const EventStart< ReturnsBool >& a_roEvent );

    EventStart< ReturnsBool >* Clone() const override;
    bool operator()() override;

private:

    bool m_bStarted;

};

// Event triggered by another event ending
template< typename ReturnsBool >
class EventEnd : public EventStart< ReturnsBool >
{
public:

    EventEnd( ReturnsBool& a_roEvent, bool a_bStarted = false );
    EventEnd( const EventEnd< ReturnsBool >& a_roEvent );

    EventEnd< ReturnsBool >* Clone() const override;

private:

    NotEvent<ReturnsBool> m_oNotEvent;
    ReturnsBool& m_roEvent;

};

}   // namespace Events

#include "inline/Events.inl"

#endif  // _EVENTS_H_