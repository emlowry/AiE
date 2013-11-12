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
#include "DoubleCallback.h"

// Simplify typing and reduce template parameter typos
typedef Callback< bool > Event;
typedef DoubleCallback< bool > DoubleEvent;

#include "events/And.h"
#include "events/End.h"
#include "events/KeyDown.h"
#include "events/MouseButtonDown.h"
#include "events/Start.h"
#include "events/Not.h"
#include "events/Or.h"
#include "events/XOr.h"

#endif  // _EVENTS_H_