/******************************************************************************
 * File:               EventHandler.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       October 28, 2013
 * Description:        Class for reacting to events.
 * Last Modified:      October 29, 2013
 * Last Modification:  Refactoring.
 ******************************************************************************/

#include "EventHandler.h"
#include "Callback.h"
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

// Stop listening for an event.
void EventHandler::Unlisten( const Event& ac_roEvent )
{
    // Check to see if the event is being listened for.
    EventSet::iterator oIterator =
        m_oEvents.find( const_cast< Event* >( &ac_roEvent ) );

    // If the event isn't being listened for, nothing more needs to be done.
    if( m_oEvents.end() == oIterator )
    {
        return;
    }

    // Otherwise, get a pointer to the stored event.
    Event* poEvent = *oIterator;

    // Loop through event reactions.
    for each( Reaction* poReaction in m_oReactions[ poEvent ] )
    {
        // Erase the event from the reaction's list of triggers.
        m_oTriggers[ poReaction ].erase( poEvent );

        // If no other events trigger the reaction, remove its list of triggers
        // and deallocate the stored copy.
        if( m_oTriggers[ poReaction ].size() == 0 )
        {
            m_oTriggers.erase( poReaction );
            delete poReaction;
        }
    }

    // Remove this event's list of reactions.
    m_oReactions.erase( poEvent );

    // Deallocate the stored copy of the event.
    m_oEvents.erase( poEvent );
    delete poEvent;
}

// If the given event occurs, execute the given reaction
void EventHandler::Add( const Event& ac_roEvent,
                        const Reaction& ac_roReaction )
{
    // Check to see if the event is already being listened for
    EventSet::iterator oEventIterator =
        m_oEvents.find( const_cast< Event* >( &ac_roEvent ) );
    Event* poEvent;

    // If the 
    if( m_oEvents.end() == oEventIterator )
    {
        poEvent = ac_roEvent.Clone();
        m_oEvents.insert( poEvent );
    }
    else
    {
        poEvent = *oEventIterator;
    }

    // make sure the reaction wrapper is allocated
    TriggerMap::iterator oReactionIterator =
        m_oTriggers.find( const_cast< Reaction* >( &ac_roReaction ) );
    Reaction* poReaction = ( m_oTriggers.end() == oReactionIterator )
                           ? ac_roReaction.Clone() : (*oReactionIterator).first;
    
    // associate the event and reaction
    m_oReactions[ poEvent ].insert( poReaction );
    m_oTriggers[ poReaction ].insert( poEvent );
}
    
// If the given event occurs, don't execute the given reaction
void EventHandler::Remove( const Event& ac_roEvent, const Reaction& ac_roReaction )
{
    // check to see if the event is being listened for
    EventSet::iterator oEventIterator =
        m_oEvents.find( const_cast< Event* >( &ac_roEvent ) );
    if( m_oEvents.end() == oEventIterator )
    {
        return;
    }
    Event* poEvent = *oEventIterator;

    // check to see if the reaction wrapper is associated with the event
    ReactionSet::iterator oReactionIterator =
        m_oReactions[ poEvent ].find( const_cast< Reaction* >( &ac_roReaction ) );
    if( m_oReactions[ poEvent ].end() == oReactionIterator )
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
void EventHandler::Remove( const Reaction& ac_roReaction )
{
    // check to see if the reaction wrapper is associated with any events
    TriggerMap::iterator oTriggerIterator =
        m_oTriggers.find( const_cast< Reaction* >( &ac_roReaction ) );
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
