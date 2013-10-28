/******************************************************************************
 * File:               EventHandler.h
 * Author:             Elizabeth Lowry
 * Date Created:       October 24, 2013
 * Description:        Class for reacting to an event.
 * Last Modified:      October 24, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef _EVENT_HANDLER_H_
#define _EVENT_HANDLER_H_

#include "Globals.h"

// Handles reacting to an event, such as a keypress or a mouse click.
// Event must implement operator() with no arguments to return a bool.
// Reaction must implement operator() with no arguments, with no return 
template< typename Event, typename Reaction >
class EventHandler
{
public:

    class Event
    {
    public:
        bool operator()()=0;
    };
    typedef void (Reaction*)();

    EventHandler( Event a_pEvent, Reaction a_pReaction );
    void Run();

private:

    Event m_pEvent;
    Reaction m_pReaction;

};

#endif  // _EVENT_HANDLER_H_