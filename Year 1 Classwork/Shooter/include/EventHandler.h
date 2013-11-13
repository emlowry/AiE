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

#include "Events.h"
#include "Clone.h"
#include "DoubleLookup.h"
#include <set>
#include <unordered_map>

using std::size_t;

// Handles reacting to an events, such as keypresses or mouse clicks
class EventHandler
{
private:

    // Holds a functor, function object, or other object implementing operator()
    // with no parameters.  Any return type is possible, but returned values are
    // ignored, so it might as well return null.  This represents a reaction to
    // an event - if an event occurs, the associated reactions will all be
    // executed.
    typedef Callback< void > Reaction;

public:

    // Destructor clears internal lists to deallocate memory
    ~EventHandler();

    // Check for all events and react to those that occur
    static void Run();

    // Start listening for an event
    static void StartListening( const Event& ac_roEvent );
    template< typename ReturnsBool >
    static void StartListening( ReturnsBool& a_roTarget );

    // Stop listening for an event
    static void StopListening( const Event& ac_roEvent );
    template< typename ReturnsBool >
    static void StopListening( ReturnsBool& a_roTarget );

    // When the given event occurs, execute the given reaction
    static void AddReaction( const Event& ac_roEvent,
                             const Reaction& ac_roReaction );
    template< typename ReturnsVoid >
    static void AddReaction( const Event& ac_roEvent,
                             ReturnsVoid& a_roReactionTarget );
    template< typename ReturnsBool >
    static void AddReaction( ReturnsBool& a_roEventTarget,
                             const Reaction& ac_roReactionTarget );
    template< typename ReturnsBool, typename ReturnsVoid >
    static void AddReaction( ReturnsBool& a_roEventTarget,
                             ReturnsVoid& a_roReactionTarget );
    
    // When the given event occurs, don't execute the given reaction
    static void RemoveReaction( const Event& ac_roEvent,
                                const Reaction& ac_roReaction );
    template< typename ReturnsVoid >
    static void RemoveReaction( const Event& ac_roEvent,
                                ReturnsVoid& a_roReactionTarget );
    template< typename ReturnsBool >
    static void RemoveReaction( ReturnsBool& a_roEventTarget,
                                const Reaction& ac_rroReaction );
    template< typename ReturnsBool, typename ReturnsVoid >
    static void RemoveReaction( ReturnsBool& a_roEventTarget,
                                ReturnsVoid& a_roReactionTarget );
    
    // Don't execute the given reaction, no matter what event occurs
    static inline void RemoveReaction( const Reaction& ac_roReaction );
    template< typename ReturnsVoid >
    static inline void RemoveReaction( ReturnsVoid& a_roTarget );

private:

    // typedef these to save space
    typedef CloneSet< Event > EventSet;
    typedef EventSet::Index EventIndex;
    typedef CloneSet< Reaction > ReactionSet;
    typedef ReactionSet::Index ReactionIndex;
    typedef DoubleLookup< Event, Reaction > Lookup;

    // Constructor is private - this class is a singleton that users interact
    // with via static functions.
    EventHandler() {}
    
    // Check for all events and react to those that occur
    void ReactToEvents();

    // Start listening for an event
    void Listen( const Event& ac_roEvent );

    // Stop listening for an event
    void Unlisten( const Event& ac_roEvent );

    // If the given event occurs, execute the given reaction
    void Add( const Event& ac_roEvent, const Reaction& ac_roReaction );
    
    // If the given event occurs, don't execute the given reaction
    void Remove( const Event& ac_roEvent, const Reaction& ac_roReaction );
    
    // Don't execute the given reaction, no matter what event occurs
    void Remove( const Reaction& ac_roReaction );

    // Store and own clones, do deep checks for equality to prevent duplicates
    EventSet m_oEvents;         // Events we're listening for
    ReactionSet m_oReactions;   // Reactions to events

    // Stores and does not own references to the contents of m_oEvents and
    // m_oReactions, checks for address equality (so make sure to look up using
    // references from m_oEvents and m_oReactions, not from function arguments).
    Lookup m_oLookup;

    static EventHandler sm_oInstance;    // Singleton

};

#include "inline/EventHandler.inl"

#endif  // _EVENT_HANDLER_H_