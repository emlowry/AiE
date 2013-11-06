/******************************************************************************
 * File:               End.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 5, 2013
 * Description:        Event class for another event ceasing to occur.
 * Last Modified:      November 5, 2013
 * Last Modification:  Moving code from Events.h.
 ******************************************************************************/

#ifndef _EVENTS__END_H_
#define _EVENTS__END_H_

#include "Events.h"
#include "events/Not.h"

namespace Events
{
    
// Event triggered by another event ending
class End : public Start
{
public:

    // Constructors set up internal Not and then sets internal pointer directly
    End( const Event&& ac_rroCall, bool a_bStarted = false );
    template< typename ReturnsBool >
    End( ReturnsBool& a_roTarget, bool a_bStarted = false );

    // No need to implement - default destructor is fine
    virtual ~End();

    // Implement Clone() so it'll return an End pointer instead of a Start
    End* Clone() const override;

protected:
    
    // used by the hash function
    const char* ClassName() const override;
    std::size_t TargetHash() const override;

    static const char* const CLASS_NAME;

};

}   // namespace Events

typedef Events::Start StartEvent;

#endif  // _EVENTS__END_H_
