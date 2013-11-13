/******************************************************************************
 * File:               Typedefs.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 12, 2013
 * Description:        Typedefs used by all event classes.
 * Last Modified:      November 12, 2013
 * Last Modification:  Moved out of Events.h.
 ******************************************************************************/

#ifndef _EVENTS__TYPEDEFS_H_
#define _EVENTS__TYPEDEFS_H_

#include "Callback.h"
#include "DoubleCallback.h"

// Simplify typing and reduce template parameter typos
typedef Callback< bool > Event;
typedef DoubleCallback< bool > DoubleEvent;

#endif  // _EVENTS__TYPEDEFS_H_