/******************************************************************************
 * File:               Events.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 5, 2013
 * Description:        Classes and functions for detecting specific events.
 * Last Modified:      November 5, 2013
 * Last Modification:  Moving classes into separate files.
 ******************************************************************************/

#ifndef _EVENTS_H_
#define _EVENTS_H_

#include "Callback.h"

// Simplify typing and reduce template parameter typos
typedef Callback< bool > Event;

// Create an event from anything that implements operator() with no parameters to
// return a bool.
template< typename Callable >
Event* NewEvent( Callable& a_roEvent );
Event* NewEvent( const Event&& ac_rroEvent );

#include "events/And.h"
#include "events/End.h"
#include "events/KeyDown.h"
#include "events/MouseButtonDown.h"
#include "events/Not.h"
#include "events/Or.h"
#include "events/Start.h"
#include "events/XOr.h"

#include "inline/Events.inl"

#endif  // _EVENTS_H_