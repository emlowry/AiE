/******************************************************************************
 * File:               XOr.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 5, 2013
 * Description:        Event class for only one of two events occurring.
 * Last Modified:      November 5, 2013
 * Last Modification:  Moving code from Events.h.
 ******************************************************************************/

#ifndef _EVENTS_XOR_H_
#define _EVENTS_XOR_H_

#include "Events.h"

namespace Events
{
    
// Abstract base Event triggered by only one of two events occurring.
template< typename ReturnsBool, typename OtherReturnsBool >
class XOrBase : public DoubleCallback< bool, ReturnsBool, OtherReturnsBool >
{
private:

    // Simplify typing and prevent template parameter typos
    typedef DoubleCallback< bool, ReturnsBool, OtherReturnsBool > BaseClass;
    typedef XOrBase< ReturnsBool, OtherReturnsBool > ThisClass;

public:

    // return true if only one of m_poCall() or m_poOtherCall() return true
    bool operator()() override;

protected:

    // Constructor should only be called by derived classes
    XOrBase( ReturnsBool* a_poCall, OtherReturnsBool* a_poOtherCall );
    virtual ~XOrBase();

private:

    // class name for the hash function to use
    virtual const char* ClassName() const override;
    static const char* const CLASS_NAME;

};

// Generic derived class for XOr events
template< typename ReturnsBool, typename OtherReturnsBool >
class XOr : public XOrBase< bool, ReturnsBool, OtherReturnsBool >
{
private:
    
    // Simplify typing and prevent template parameter typos
    typedef XOrBase< ReturnsBool, OtherReturnsBool > BaseClass;
    typedef XOr< ReturnsBool, OtherReturnsBool > ThisClass;

public:

    // Reference parameters ensure components exist
    XOr( ReturnsBool& a_roCall, OtherReturnsBool& a_roCall );
    virtual ~XOr();

    ThisClass* Clone() const override;

};

// Partially specialized derived classes for XOr events with one component being
// another Event
template< typename ReturnsBool >
class XOr< ReturnsBool, Event > : public XOrBase< ReturnsBool, Event >
{
private:
    
    // Simplify typing and prevent template parameter typos
    typedef XOrBase< ReturnsBool, Event > BaseClass;
    typedef XOr< ReturnsBool, Event > ThisClass;

public:

    // Reference parameters ensure components exist
    XOr( ReturnsBool& a_roCall, const Event&& ac_rroCall );
    virtual ~XOr();

    ThisClass* Clone() const override;

};
template< typename OtherReturnsBool >
class XOr< Event, OtherReturnsBool > : public XOrBase< Event, OtherReturnsBool >
{
private:
    
    // Simplify typing and prevent template parameter typos
    typedef XOrBase< Event, OtherReturnsBool > BaseClass;
    typedef XOr< Event, OtherReturnsBool > ThisClass;

public:

    // Reference parameters ensure components exist
    XOr( const Event&& ac_rroCall, OtherReturnsBool& a_roCall );
    virtual ~XOr();

    ThisClass* Clone() const override;

};

// Partially specialized derived classes for XOr events with one component being
// another Event
template<>
class XOr< Event, Event > : public XOrBase< Event, Event >
{
private:
    
    // Simplify typing and prevent template parameter typos
    typedef XOrBase< Event, Event > BaseClass;
    typedef XOr< Event, Event > ThisClass;

public:

    // Reference parameters ensure components exist
    XOr( const Event&& ac_rroCall, const Event&& ac_rroCall );
    virtual ~XOr();

    ThisClass* Clone() const override;

};

}   // namespace Events

#endif  // _EVENTS_XOR_H_
