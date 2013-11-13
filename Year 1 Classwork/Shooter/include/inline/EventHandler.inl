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
inline void EventHandler::StartListening( const Event& ac_roEvent )
{
    m_oInstance.Listen( ac_roEvent );
}
template< typename ReturnsBool >
inline void EventHandler::StartListening( ReturnsBool& a_roTarget )
{
    m_oInstance.Listen( Event( a_roTarget ) );
}

// Stop listening for an event
inline void EventHandler::StopListening( const Event& ac_roEvent )
{
    m_oInstance.Unlisten( ac_roEvent );
}
template< typename ReturnsBool >
inline void EventHandler::StopListening( ReturnsBool& a_roTarget )
{
    m_oInstance.Unlisten( Event( a_roTarget ) );
}

// When the given event occurs, execute the given reaction
inline void EventHandler::AddReaction( const Event& ac_roEvent,
                                       const Reaction& ac_roReaction )
{
    m_oInstance.Add( ac_roEvent, ac_roReaction );
}
template< typename ReturnsVoid >
inline void EventHandler::AddReaction( const Event& ac_roEvent,
                                       ReturnsVoid& a_roReactionTarget )
{
    m_oInstance.Add( ac_roEvent, Reaction( a_roReactionTarget ) );
}
template< typename ReturnsBool >
inline void EventHandler::AddReaction( ReturnsBool& a_roEventTarget,
                                       const Reaction& ac_roReaction )
{
    m_oInstance.Add( Event( a_roEventTarget ), ac_roReaction );
}
template< typename ReturnsBool, typename ReturnsVoid >
inline void EventHandler::AddReaction( ReturnsBool& a_roEventTarget,
                                       ReturnsVoid& a_roReactionTarget )
{
    m_oInstance.Add( Event( a_roEventTarget ), Reaction( a_roReactionTarget ) );
}
    
// When the given event occurs, don't execute the given reaction
inline void EventHandler::RemoveReaction( const Event& ac_roEvent,
                                          const Reaction& ac_roReaction )
{
    m_oInstance.Remove( ac_roEvent, ac_roReaction );
}
template< typename ReturnsVoid >
inline void EventHandler::RemoveReaction( const Event& ac_roEvent,
                                          ReturnsVoid& a_roReactionTarget )
{
    m_oInstance.Remove( ac_roEvent, Reaction( a_roReactionTarget ) );
}
template< typename ReturnsBool >
inline void EventHandler::RemoveReaction( ReturnsBool& a_roEventTarget,
                                          const Reaction& ac_roReaction )
{
    m_oInstance.Remove( Event( a_roEventTarget ), ac_roReaction );
}
template< typename ReturnsBool, typename ReturnsVoid >
inline void EventHandler::RemoveReaction( ReturnsBool& a_roEventTarget,
                                          ReturnsVoid& a_roReactionTarget )
{
    m_oInstance.Remove( Event( a_roEventTarget ),
                        Reaction( a_roReactionTarget ) );
}
    
// Don't execute the given reaction, no matter what event occurs
inline void EventHandler::RemoveReaction( const Reaction& ac_roReaction )
{
    m_oInstance.Remove( ac_roReaction );
}
template< typename ReturnsVoid >
inline void EventHandler::RemoveReaction( ReturnsVoid& a_roTarget )
{
    m_oInstance.Remove( Reaction( a_roTarget ) );
}

//
// Private implementations used by the singleton instance
//

// Start listening for an event
inline void EventHandler::Listen( const Event& ac_roEvent )
{
    m_oEvents.insert( ac_roEvent.Clone() );
}

#endif  // _EVENT_HANDLER_INL_
