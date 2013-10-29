/******************************************************************************
 * File:               EventHandler.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       October 28, 2013
 * Description:        Class for reacting to events.
 * Last Modified:      October 28, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#include "EventHandler.h"
#include "Globals.h"
#include <set>
#include <unordered_map>

// Check for all events and react to those that occur
void EventHandler::ReactToEvents()
{
    for each( Event* poEvent in m_oEvents )
    {
        if( (*poEvent)() )
        {
            for each( Reaction* poReaction in m_oReactions[ poEvent ] )
            {
                (*poReaction)();
            }
        }
    }
}

// Start listening for an event
template< typename ReturnsBool >
inline void Listen( ReturnsBool& a_roEvent )
{
    m_oEvents.insert( new EventWrapper( a_roEvent ) );
}

// Stop listening for an event
template< typename ReturnsBool >
void EventHandler::Unlisten( const ReturnsBool& a_roEvent )
{
    // check to see if the event is being listened for
    Event oEvent = EventWrapper( a_roEvent );
    EventList::iterator oIterator = m_oEvents.find( &oEvent );
    if( m_oEvents.end() == oIterator )
    {
        return;
    }
    Event* poEvent = *oIterator;

    // loop through event reactions and remove them
    for each( Reaction* poReaction in m_oReactions[ poEvent ] )
    {
        m_oTriggers[ poReaction ].erase( poEvent );

        // if no other events cause the reaction, deallocate its wrapper
        if( m_oTriggers[ poReaction ].size() == 0 )
        {
            m_oTriggers.erase( poReaction );
            delete poReaction;
        }
    }
    m_oReactions.erase( poEvent );

    // deallocate the event's wrapper
    m_oEvents.erase( poEvent );
    delete poEvent;
}

// If the given event occurs, execute the given reaction
template< typename ReturnsBool, typename ReturnsVoid >
void EventHandler::Add( ReturnsBool& a_roEvent, ReturnsVoid& a_roReaction )
{
    // make sure the event wrapper is allocated and listed
    Event oEvent = EventWrapper( a_roEvent );
    EventList::iterator oEventIterator = m_oEvents.find( &oEvent );
    Event* poEvent;
    if( m_oEvents.end() == oEventIterator )
    {
        poEvent = new EventWrapper( a_roEvent );
        m_oEvents.insert( poEvent );
    }
    else
    {
        poEvent = *oEventIterator;
    }

    // make sure the reaction wrapper is allocated
    Reaction oReaction = ReactionWrapper( a_roReaction );
    TriggerMap::iterator oReactionIterator = m_oTriggers.find( &oReaction );
    Reaction* poReaction;
    if( m_oTriggers.end() == oReactionIterator )
    {
        poReaction = new ReactionWrapper( a_roReaction );
    }
    
    // associate the event and reaction
    m_oReactions[ poEvent ].insert( poReaction );
    m_oTriggers[ poReaction ].insert( poEvent );
}
    
// If the given event occurs, don't execute the given reaction
template< typename ReturnsBool, typename ReturnsVoid >
void EventHandler::Remove( const ReturnsBool& a_roEvent, const ReturnsVoid& a_roReaction )
{
    // check to see if the event is being listened for
    Event oEvent = EventWrapper( a_roEvent );
    EventList::iterator oEventIterator = m_oEvents.find( &oEvent );
    if( m_oEvents.end() == oEventIterator )
    {
        return;
    }
    Event* poEvent = *oEventIterator;

    // check to see if the reaction wrapper is associated with the event
    Reaction oReaction = ReactionWrapper( a_roReaction );
    ReactionList::iterator oReactionIterator =
        m_oReactions[ poEvent ].find( &oReaction );
    if( m_oTriggers.end() == oReactionIterator )
    {
        return;
    }
    Reaction* poReaction = *oReactionIterator;

    // disassociate the event and reaction
    m_oReactions[ poEvent ].erase( poReaction );
    m_oTriggers[ poReaction ].erase( poEvent );

    // if nothing else triggers the reaction, deallocate its wrapper
    if( m_oTriggers[ poReaction ].size() == 0 )
    {
        m_oTriggers.erase( poReaction );
        delete poReaction;
    }
}
    
// Don't execute the given reaction, no matter what event occurs
template< typename ReturnsVoid >
void EventHandler::Remove( const ReturnsVoid& a_roReaction )
{
    // check to see if the reaction wrapper is associated with any events
    Reaction oReaction = ReactionWrapper( a_roReaction );
    TriggerMap::iterator oTriggerIterator = m_oTriggers.find( &oReaction );
    if( m_oTriggers.end() == oTriggerIterator )
    {
        return;
    }
    Reaction* poReaction = (*oTriggerIterator).first;

    // disassociate the reaction with any events that trigger it
    for each( Event* poEvent in m_oTriggers[ poReaction ] )
    {
        m_oReactions[ poEvent ].erase( poReaction );
    }

    // deallocate the reaction's wrapper
    m_oTriggers.erase( poReaction );
    delete poReaction;
}