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

// instantiate singleton
EventHandler EventHandler::sm_oInstance = EventHandler();

// Check for all events and react to those that occur
void EventHandler::ReactToEvents()
{
    for( EventIndex oEventIndex = m_oEvents.Begin();
         oEventIndex != m_oEvents.End(); ++oEventIndex )
    {
        Lookup::ForwardSet& roReactions = m_oLookup[ m_oEvents[ oEventIndex ] ];
        for( Lookup::ForwardIndex oReactionIndex = roReactions.Begin();
             oReactionIndex != roReactions.End(); ++oReactionIndex )
        {
            roReactions[ oReactionIndex ]();
        }
    }
}

// Stop listening for an event.
void EventHandler::Unlisten( const Event& ac_roEvent )
{
    // If the event isn't being listened for, nothing more needs to be done.
    if( !m_oEvents.Contains( ac_roEvent ) )
    {
        return;
    }

    // Otherwise, get a reference to the stored event.
    Event& roEvent = m_oEvents[ ac_roEvent ];

    // If the event has no reactions, just remove it from the event list and
    // return
    if( m_oLookup.Count( roEvent ) == 0 )
    {
        m_oEvents.Erase( roEvent );
        return;
    }

    // Otherwise, get a copy of the list of the event reactions before removing
    // all associations
    Lookup::ForwardSet oReactions = m_oLookup[ roEvent ];
    m_oLookup.Erase( roEvent );

    // Loop through event reactions.
    for( Lookup::ForwardIndex oReactionIndex = oReactions.Begin();
         oReactionIndex != oReactions.End(); ++oReactionIndex )
    {
        // If no events trigger the reaction anymore, remove it from the set of
        // reactions
        Reaction& roReaction = oReactions[ oReactionIndex ];
        if( m_oLookup.Count( roReaction ) == 0 )
        {
            m_oReactions.Erase( roReaction );
        }
    }

    // Remove the event from the list of events
    m_oEvents.Erase( roEvent );
}

// If the given event occurs, execute the given reaction
void EventHandler::Add( const Event& ac_roEvent,
                        const Reaction& ac_roReaction )
{
    // make sure the event and reaction are present in the event and reaction
    // sets.
    Event& roEvent = m_oEvents[ ac_roEvent ];
    Reaction& roReaction = m_oReactions[ ac_roReaction ];

    // make sure the event and reaction are associated.
    m_oLookup.Insert( roEvent, roReaction );
}
    
// If the given event occurs, don't execute the given reaction
void EventHandler::Remove( const Event& ac_roEvent,
                           const Reaction& ac_roReaction )
{
    // If the event or reaction aren't even present, nothing needs to be done.
    if( !m_oEvents.Contains( ac_roEvent ) ||
        !m_oReactions.Contains( ac_roReaction ) )
    {
        return;
    }

    // get references to the stored event and reaction
    Event& roEvent = m_oEvents[ ac_roEvent ];
    Reaction& roReaction = m_oReactions[ ac_roReaction ];

    // if the two aren't associated, then nothing more needs to be done
    if( !m_oLookup.AreLinked( roEvent, roReaction ) )
    {
        return;
    }

    // Otherwise, remove their association
    m_oLookup.Erase( roEvent, roReaction );

    // If nothing else triggers the reaction anymore, remove it from the list of
    // reactions
    if( m_oLookup.Count( roReaction ) == 0 )
    {
        m_oReactions.Erase( roReaction );
    }
}
    
// Don't execute the given reaction, no matter what event occurs
void EventHandler::Remove( const Reaction& ac_roReaction )
{
    // If the reaction isn't even present, then nothing needs to be done
    if( !m_oReactions.Contains( ac_roReaction ) )
    {
        return;
    }

    // otherwise, get a reference to the stored reaction
    Reaction& roReaction = m_oReactions[ ac_roReaction ];

    // remove all associations between the reaction and events
    m_oLookup.Erase( roReaction );
    m_oReactions.Erase( roReaction );
}
