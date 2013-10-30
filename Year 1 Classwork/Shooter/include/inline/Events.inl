/******************************************************************************
 * File:               Events.inl
 * Author:             Elizabeth Lowry
 * Date Created:       October 29, 2013
 * Description:        Inline function implementations for Events.h.
 * Last Modified:      October 29, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

namespace Events
{

// Is the given key down?
template< int t_iKey >
inline bool Events::KeyDownEvent()
{
    return IsKeyDown( t_iKey );
}

// Is the given mouse button down?
template< int t_iButton >
inline bool Events::MouseButtonDownEvent()
{
    return GetMouseButtonDown( t_iButton );
}

//
// NotEvent
//

// Constructor
template< typename ReturnsBool >
inline NotEvent< ReturnsBool >::NotEvent( ReturnsBool a_roCall )
    : CallbackWrapper< bool, ReturnsBool >( a_roCall ) {}

// Copy Constructor
template< typename ReturnsBool >
inline NotEvent< ReturnsBool >::
    NotEvent(const NotEvent< ReturnsBool >& ac_roEvent )
    : CallbackWrapper< bool, ReturnsBool >( *(ac_roEvent.m_poCall) ) {}

// Dynamically allocate a copy pointing to the same event
template< typename ReturnsBool >
inline NotEvent< ReturnsBool >* NotEvent< ReturnsBool >::Clone() const
{
    return new NotEvent< ReturnsBool >( *this );
}

// Negation of the wrapped call result
template< typename ReturnsBool >
inline bool NotEvent< ReturnsBool >::operator()()
{
    return !(*m_roCall)();
}

//
// EventCombination
//

// Constructor
template< typename ReturnsBoolOne, typename ReturnsBoolTwo >
inline EventCombination< ReturnsBoolOne, ReturnsBoolTwo >::
    EventCombination( ReturnsBoolOne& a_roCallOne, ReturnsBoolTwo& a_roCallTwo )
        : m_poCallOne( &a_roCallOne ), m_poCallTwo( &a_roCallTwo ) {}

// Hash based on concatenation of the target addresses
template< typename ReturnsBoolOne, typename ReturnsBoolTwo >
inline std::size_t
    EventCombination< ReturnsBoolOne, ReturnsBoolTwo >::Hash() const
{
    std::size_t uiPartOne = (std::size_t)m_poCallOne;
    uiPartOne << ( 8 * sizeof( m_poCallOne ) );
    return uiPartOne + (std::size_t)m_poCallTwo;
}

//
// XOrEvent
//

// Constructor
template< typename ReturnsBoolOne, typename ReturnsBoolTwo >
inline XOrEvent< ReturnsBoolOne, ReturnsBoolTwo >::
    XOrEvent( ReturnsBoolOne& a_roCallOne, ReturnsBoolTwo& a_roCallTwo )
    : BaseClass( a_roCallOne, a_roCallTwo ) {}

// Copy Constructor
template< typename ReturnsBoolOne, typename ReturnsBoolTwo >
inline XOrEvent< ReturnsBoolOne, ReturnsBoolTwo >::
    XOrEvent( const ThisClass& ac_roEvent )
    : BaseClass( *(ac_roEvent.m_poCallOne), *(ac_roEvent.m_poCallTwo) ) {}

// Dynamically allocate a copy pointing to the same events
template< typename ReturnsBoolOne, typename ReturnsBoolTwo >
inline XOrEvent< ReturnsBoolOne, ReturnsBoolTwo >*
    XOrEvent< ReturnsBoolOne, ReturnsBoolTwo >::Clone() const
{
    return new XOrEvent< ReturnsBoolOne, ReturnsBoolTwo >( *this );
};

// Exclusive-or of the call results
template< typename ReturnsBoolOne, typename ReturnsBoolTwo >
inline bool XOrEvent< ReturnsBoolOne, ReturnsBoolTwo >::operator()()
{
    return (*m_poCallOne)() ? !(*m_poCallTwo)() : (*m_poCallTwo)();
}

//
// OrEvent
//

// Constructor
template< typename ReturnsBoolOne, typename ReturnsBoolTwo >
inline OrEvent< ReturnsBoolOne, ReturnsBoolTwo >::
    OrEvent( ReturnsBoolOne& a_roCallOne, ReturnsBoolTwo& a_roCallTwo )
    : EventCombination< ReturnsBoolOne, ReturnsBoolTwo >( a_roCallOne,
                                                          a_roCallTwo ) {}

// Copy Constructor
template< typename ReturnsBoolOne, typename ReturnsBoolTwo >
inline OrEvent< ReturnsBoolOne, ReturnsBoolTwo >::
    OrEvent(const OrEvent< ReturnsBoolOne, ReturnsBoolTwo >& ac_roEvent )
    : EventCombination< ReturnsBoolOne, ReturnsBoolTwo >(
                                                  *(ac_roEvent.m_poCallOne),
                                                  *(ac_roEvent.m_poCallTwo) ) {}

// Dynamically allocate a copy pointing to the same events
template< typename ReturnsBoolOne, typename ReturnsBoolTwo >
inline OrEvent< ReturnsBoolOne, ReturnsBoolTwo >*
    OrEvent< ReturnsBoolOne, ReturnsBoolTwo >::Clone() const
{
    return new OrEvent< ReturnsBoolOne, ReturnsBoolTwo >( *this );
}

// Exclusive-or of the call results.  Make sure both are checked, in case they
// track their own results.
template< typename ReturnsBoolOne, typename ReturnsBoolTwo >
inline bool OrEvent< ReturnsBoolOne, ReturnsBoolTwo >::operator()()
{
    bool bOne = (*m_poCallOne)();
    return (*m_poCallTwo)() || bOne;
}

//
// AndEvent
//

// Constructor
template< typename ReturnsBoolOne, typename ReturnsBoolTwo >
inline AndEvent< ReturnsBoolOne, ReturnsBoolTwo >::
    AndEvent( ReturnsBoolOne& a_roCallOne, ReturnsBoolTwo& a_roCallTwo )
    : EventCombination< ReturnsBoolOne, ReturnsBoolTwo >( a_roCallOne,
                                                          a_roCallTwo ) {}

// Copy Constructor
template< typename ReturnsBoolOne, typename ReturnsBoolTwo >
inline AndEvent< ReturnsBoolOne, ReturnsBoolTwo >::
    AndEvent( const AndEvent< ReturnsBoolOne, ReturnsBoolTwo >& ac_roEvent )
    : EventCombination< ReturnsBoolOne, ReturnsBoolTwo >(
                                                  *(ac_roEvent.m_poCallOne),
                                                  *(ac_roEvent.m_poCallTwo) ) {}

// Dynamically allocate a copy pointing to the same events
template< typename ReturnsBoolOne, typename ReturnsBoolTwo >
inline AndEvent< ReturnsBoolOne, ReturnsBoolTwo >*
    AndEvent< ReturnsBoolOne, ReturnsBoolTwo >::Clone() const
{
    return new AndEvent< ReturnsBoolOne, ReturnsBoolTwo >( *this );
}

// And of the call results.
template< typename ReturnsBoolOne, typename ReturnsBoolTwo >
inline bool AndEvent< ReturnsBoolOne, ReturnsBoolTwo >::operator()()
{
    return (*a_roCallOne)() && (*a_roCallTwo)();
}

//
// EventStart
//

// Constructor
template< typename ReturnsBool >
inline EventStart< ReturnsBool >::EventStart( ReturnsBool& a_roCall,
                                              bool a_bStarted )
    : CallbackWrapper< bool, ReturnsBool >( a_roCall ),
      m_bStarted( a_bStarted ) {}

// Copy Constructor
template< typename ReturnsBool >
inline EventStart< ReturnsBool >::EventStart(
                                   const EventStart< ReturnsBool >& ac_roEvent )
    : CallbackWrapper< bool, ReturnsBool >( *(ac_roEvent.m_poCall) ),
      m_bStarted( ac_roEvent.m_bStarted ) {}

// Dynamically allocate a copy pointing to the same event
template< typename ReturnsBool >
inline EventStart< ReturnsBool >* EventStart< ReturnsBool >::Clone() const
{
    return new EventStart( *m_poCall, m_bStarted );
}

//
// EventEnd
//

// Constructor
template< typename ReturnsBool >
inline EventEnd< ReturnsBool >::EventEnd( ReturnsBool& a_roEvent,
                                          bool a_bStarted = false )
    : m_poEvent( &a_roEvent ), m_oNotEvent( a_roEvent ),
      EventStart< ReturnsBool >( m_oNotEvent, !a_bStarted ) {}

// Copy Constructor
template< typename ReturnsBool >
inline EventEnd< ReturnsBool >::EventEnd(
                                      const EventEnd< ReturnsBool >& a_roEvent )
    : m_poEvent( a_roEvent.m_poEvent ), m_oNotEvent( *(a_roEvent.m_poEvent) ),
      EventStart< ReturnsBool >( m_oNotEvent, m_bStarted ) {}

// Dynamically allocate a copy pointing to the same event
template< typename ReturnsBool >
inline EventEnd< ReturnsBool >* EventEnd< ReturnsBool >::Clone() const
{
    return new EventEnd( *m_poEvent, !m_bStarted );
}

}   // namespace Events
