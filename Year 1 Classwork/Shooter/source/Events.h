/******************************************************************************
 * File:               Events.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       October 28, 2013
 * Description:        Implementations for detection of the more complex events.
 * Last Modified:      October 28, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#include "Events.h"

namespace Events
{

// Is the internally-watched event taking place when it was not previously?
bool EventStart::operator()()
{
    if( m_roEvent() )
    {
        if( m_bStarted)
        {
            return false;
        }
        m_bStarted = true;
        return true;
    }
    m_bStarted = false;
    return false;
}

}   // namespace Events
