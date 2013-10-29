/******************************************************************************
 * File:               EventHandler.h
 * Author:             Elizabeth Lowry
 * Date Created:       October 24, 2013
 * Description:        Class for reacting to events.
 * Last Modified:      October 24, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef _EVENT_HANDLER_H_
#define _EVENT_HANDLER_H_

#include "Globals.h"
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
    class Event : public Hashable { public: virtual bool operator()() = 0; };
    template< typename ReturnsBool >
    class EventWrapper : public Event
    {
    public:
        inline EventWrapper( ReturnsBool& a_roReturnsBool )
            : m_roReturnsBool( a_roReturnsBool ) {}
        inline EventWrapper( const EventWrapper& a_roEvent )
            : m_roReturnsBool( a_roEvent.m_roReturnsBool ) {}
        inline size_t Hash() const { return &m_roReturnsBool; }
        inline virtual bool operator()() { return m_roReturnsBool(); }
    private:
        EventWrapper& operator=( const EventWrapper& a_roEvent );
        ReturnsBool& m_roReturnsBool;
    };

    // Holds a functor, function object, or other object implementing operator()
    // with no parameters.  Any return type is possible, but returned values are
    // ignored, so it might as well return null.  This represents a reaction to
    // an event - if an event occurs, the associated reactions will all be
    // executed.
    class Reaction : public Hashable { public: virtual void operator()() = 0; };
    template< typename ReturnsVoid >
    class ReactionWrapper : public Reaction
    {
    public:
        inline ReactionWrapper( ReturnsVoid& a_roReturnsVoid )
            : m_roReturnsVoid( a_roReturnsVoid ) {}
        inline ReactionWrapper( const ReactionWrapper& a_roReaction )
            : m_roReturnsVoid( a_roReaction.m_roReturnsVoid ) {}
        inline size_t Hash() const { return &m_roReturnsVoid; }
        inline virtual void operator()() { m_roReturnsVoid(); }
    private:
        ReactionWrapper& operator=( const ReactionWrapper& a_roReaction );
        ReturnsVoid& m_roReturnsVoid;
    };

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
    inline void Listen( ReturnsBool& a_roEvent );

    // Stop listening for an event
    template< typename ReturnsBool >
    void Unlisten( const ReturnsBool& a_roEvent );

    // If the given event occurs, execute the given reaction
    template< typename ReturnsBool, typename ReturnsVoid >
    void Add( ReturnsBool& a_roEvent, ReturnsVoid& a_roReaction );
    
    // If the given event occurs, don't execute the given reaction
    template< typename ReturnsBool, typename ReturnsVoid >
    void Remove( const ReturnsBool& a_roEvent, const ReturnsVoid& a_roReaction );
    
    // Don't execute the given reaction, no matter what event occurs
    template< typename ReturnsVoid >
    void Remove( const ReturnsVoid& a_roReaction );

    EventSet m_oEvents;         // Events we're listening for
    ReactionMap m_oReactions;   // Reactions to events
    TriggerMap m_oTriggers;     // Reverse lookup of above

    static EventHandler m_oInstance;    // Singleton

};

#endif  // _EVENT_HANDLER_H_