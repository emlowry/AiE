/******************************************************************************
 * File:               EventHandler.h
 * Author:             Elizabeth Lowry
 * Date Created:       October 24, 2013
 * Description:        Class for reacting to events.
 * Last Modified:      October 29, 2013
 * Last Modification:  Refactoring.
 ******************************************************************************/

#ifndef _EVENT_HANDLER_H_
#define _EVENT_HANDLER_H_

#include "Callback.h"
#include <set>
#include <unordered_map>

using std::size_t;

// Handles reacting to an events, such as keypresses or mouse clicks
class EventHandler
{
public:

    // Check for all events and react to those that occur
    static inline void Run() { m_oInstance.ReactToEvents(); }

    // Start listening for an event
    template< typename ReturnsBool >
    static inline void StartListening( ReturnsBool& a_roEvent )
    { m_oInstance.Listen( a_roEvent ); }

    // Stop listening for an event
    template< typename ReturnsBool >
    static inline void StopListening( ReturnsBool& a_roEvent )
    { m_oInstance.Unlisten( a_roEvent ); }

    // When the given event occurs, execute the given reaction
    template< typename ReturnsBool, typename ReturnsVoid >
    static inline void AddReaction( ReturnsBool& a_roEvent,
                                    ReturnsVoid& a_roReaction )
    { m_oInstance.Add( a_roEvent, a_roReaction ); }
    
    // When the given event occurs, don't execute the given reaction
    template< typename ReturnsBool, typename ReturnsVoid >
    static inline void RemoveReaction( ReturnsBool& a_roEvent,
                                       ReturnsVoid& a_roReaction )
    { m_oInstance.Remove( a_roEvent, a_roReaction ); }
    
    // Don't execute the given reaction, no matter what event occurs
    template< typename ReturnsVoid >
    static inline void RemoveReaction( ReturnsVoid& a_roReaction )
    { m_oInstance.Remove( a_roReaction ); }

private:

    // Holds a functor, function object, or other object implementing operator()
    // with no parameters to return a bool.  This represents an event - if
    // myEvent() returns true, then the event is occurring.
    typedef Callback< bool > Event;

    // Holds a functor, function object, or other object implementing operator()
    // with no parameters.  Any return type is possible, but returned values are
    // ignored, so it might as well return null.  This represents a reaction to
    // an event - if an event occurs, the associated reactions will all be
    // executed.
    typedef Callback< void > Reaction;

    // typedef these to save space
    typedef std::set< Event*, HashablePointerLess > EventSet;
    typedef std::set< Reaction*, HashablePointerLess > ReactionSet;
    typedef std::unordered_map< Event*, ReactionSet, HashablePointerHash >
            ReactionMap;
    typedef std::unordered_map< Reaction*, EventSet, HashablePointerHash >
            TriggerMap;

    // Constructor is private - this class is a singleton that users interact
    // with via static functions.
    EventHandler();
    
    // Check for all events and react to those that occur
    void ReactToEvents();

    // Start listening for an event
    template< typename ReturnsBool >
    void Listen( ReturnsBool& a_roCall );
    void Listen( Event& a_roEvent );

    // Stop listening for an event
    template< typename ReturnsBool >
    void Unlisten( ReturnsBool& a_roCall );
    void Unlisten( Event& ac_roEvent );

    // If the given event occurs, execute the given reaction
    template< typename ReturnsBool, typename ReturnsVoid >
    void Add( ReturnsBool& a_roBoolCall, ReturnsVoid& a_roVoidCall );
    template< typename ReturnsBool >
    void Add( ReturnsBool& a_roBoolCall, Reaction& a_roReaction );
    template< typename ReturnsVoid >
    void Add( Event& a_roEvent, ReturnsVoid& a_roVoidCall );
    void Add( Event& a_roEvent, Reaction& a_roReaction );
    
    // If the given event occurs, don't execute the given reaction
    template< typename ReturnsBool, typename ReturnsVoid >
    void Remove( ReturnsBool& a_roBoolCall, ReturnsVoid& a_roVoidCall );
    template< typename ReturnsBool >
    void Remove( ReturnsBool& a_roBoolCall, Reaction& a_roReaction );
    template< typename ReturnsVoid >
    void Remove( Event& a_roEvent, ReturnsVoid& a_roVoidCall );
    void Remove( Event& a_roEvent, Reaction& a_roReaction );
    
    // Don't execute the given reaction, no matter what event occurs
    template< typename ReturnsVoid >
    void Remove( ReturnsVoid& a_roCall );
    void Remove( Reaction& a_roReaction );

    EventSet m_oEvents;         // Events we're listening for
    ReactionMap m_oReactions;   // Reactions to events
    TriggerMap m_oTriggers;     // Reverse lookup of above

    static EventHandler m_oInstance;    // Singleton

};

#include "inline/EventHandler.inl"

#endif  // _EVENT_HANDLER_H_