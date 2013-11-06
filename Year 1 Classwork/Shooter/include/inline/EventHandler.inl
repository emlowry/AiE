/******************************************************************************
 * File:               EventHandler.inl
 * Author:             Elizabeth Lowry
 * Date Created:       October 29, 2013
 * Description:        Inline function implementations for EventHandler.
 * Last Modified:      October 29, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef _EVENT_HANDLER_INL_
#define _EVENT_HANDLER_INL_

//
// Public, static functions used to interact with the singleton instance
//

// Check for all events and react to those that occur
inline void EventHandler::Run()
{
    m_oInstance.ReactToEvents();
}

// Start listening for an event
template< typename ReturnsBool >
inline void EventHandler::StartListening( ReturnsBool& a_roEvent )
{
    m_oInstance.Listen( a_roEvent );
}

// Stop listening for an event
template< typename ReturnsBool >
inline void EventHandler::StopListening( ReturnsBool& a_roEvent )
{
    m_oInstance.Unlisten( a_roEvent );
}

// When the given event occurs, execute the given reaction
template< typename ReturnsBool, typename ReturnsVoid >
inline void EventHandler::AddReaction( ReturnsBool& a_roEvent,
                                       ReturnsVoid& a_roReaction )
{
    m_oInstance.Add( a_roEvent, a_roReaction );
}
    
// When the given event occurs, don't execute the given reaction
template< typename ReturnsBool, typename ReturnsVoid >
inline void EventHandler::RemoveReaction( ReturnsBool& a_roEvent,
                                          ReturnsVoid& a_roReaction )
{
    m_oInstance.Remove( a_roEvent, a_roReaction );
}
    
// Don't execute the given reaction, no matter what event occurs
template< typename ReturnsVoid >
inline void EventHandler::RemoveReaction( ReturnsVoid& a_roReaction )
{
    m_oInstance.Remove( a_roReaction );
}

//
// Private implementations used by the singleton instance
//

// Start listening for an event
template< typename ReturnsBool >
inline void EventHandler::Listen( ReturnsBool& a_roCall )
{
    Event oEvent = CallbackWrapper< bool, ReturnsBool >( a_roCall );
    Listen( oEvent );
}
inline void EventHandler::Listen( Event& a_roEvent )
{
    m_oEvents.insert( a_roEvent.Clone() );
}

// Stop listening for an event
template< typename ReturnsBool >
inline void EventHandler::Unlisten( ReturnsBool& a_roCall )
{
    Event oEvent = CallbackWrapper< bool, ReturnsBool >( a_roEvent );
    Unlisten( oEvent );
}

// If the given event occurs, execute the given reaction
template< typename ReturnsBool, typename ReturnsVoid >
inline void EventHandler::Add( ReturnsBool& a_roBoolCall, ReturnsVoid& a_roVoidCall )
{
    Event oEvent = CallbackWrapper< bool, ReturnsBool >( a_roBoolCall );
    Reaction oReaction = CallbackWrapper< void, ReturnsBool >( a_roVoidCall );
    Add( oEvent, oReaction );
}
template< typename ReturnsBool >
inline void EventHandler::Add( ReturnsBool& a_roBoolCall, Reaction& a_roReaction )
{
    Event oEvent = CallbackWrapper< bool, ReturnsBool >( a_roBoolCall );
    Add( oEvent, a_roReaction );
}
template< typename ReturnsVoid >
inline void EventHandler::Add( Event& a_roEvent, ReturnsVoid& a_roVoidCall )
{
    Reaction oReaction = CallbackWrapper< void, ReturnsBool >( a_roVoidCall );
    Add( a_roEvent, oReaction );
}
    
// If the given event occurs, don't execute the given reaction
template< typename ReturnsBool, typename ReturnsVoid >
inline void EventHandler::Remove( ReturnsBool& a_roBoolCall, ReturnsVoid& a_roVoidCall )
{
    Event oEvent = CallbackWrapper< bool, ReturnsBool >( a_roBoolCall );
    Reaction oReaction = CallbackWrapper< void, ReturnsBool >( a_roVoidCall );
    Remove( oEvent, oReaction );
}
template< typename ReturnsBool >
inline void EventHandler::Remove( ReturnsBool& a_roBoolCall, Reaction& a_roReaction )
{
    Event oEvent = CallbackWrapper< bool, ReturnsBool >( a_roBoolCall );
    Remove( oEvent, a_roReaction );
}
template< typename ReturnsVoid >
inline void EventHandler::Remove( Event& a_roEvent, ReturnsVoid& a_roVoidCall )
{
    Reaction oReaction = CallbackWrapper< void, ReturnsBool >( a_roVoidCall );
    Remove( a_roEvent, oReaction );
}
    
// Don't execute the given reaction, no matter what event occurs
template< typename ReturnsVoid >
inline void EventHandler::Remove( ReturnsVoid& a_roReaction )
{
    Reaction oReaction = CallbackWrapper< void, ReturnsVoid >( a_roReaction );
    Remove( oReaction );
}

#endif  // _EVENT_HANDLER_INL_
