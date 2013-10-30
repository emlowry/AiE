/******************************************************************************
 * File:               Events.h
 * Author:             Elizabeth Lowry
 * Date Created:       October 28, 2013
 * Description:        Classes and functions for detecting specific events.
 * Last Modified:      October 28, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef _EVENTS_H_
#define _EVENTS_H_

#include "AIE.h"
#include "Callback.h"

namespace Events
{

// Event triggered by a key on the keyboard being down
template< int t_iKey >
bool KeyDownEvent();

// Event triggered by a mouse button being down
template< int t_iButton >
bool MouseButtonDownEvent();

// Event triggered by another event not occurring
template< typename ReturnsBool >
class NotEvent : public CallbackWrapper< bool, ReturnsBool >
{
private:

    typedef CallbackWrapper< bool, ReturnsBool > BaseClass;
    typedef NotEvent< ReturnsBool > ThisClass;

public:

    NotEvent( ReturnsBool a_roCall );
    virtual ~NotEvent();

    ThisClass* Clone() const override;
    bool operator()() override;

protected:
    
    virtual const char* ClassName() const override;

private:
    
    // Keep copy constructor and assignment operator private to prevent
    // object slicing.  Copy constructor is used by Clone() and should be
    // implemented.  Assignment operator should not be used.
    NotEvent( const ThisClass& ac_roEvent );
    ThisClass& operator=( const ThisClass& ac_roEvent );

    // class name for the hash function to use
    static const char* const CLASS_NAME;

};

// Abstract event triggered by some combination of events occurring.
template< typename ReturnsBool, typename OtherReturnsBool >
class EventCombination : public CallbackWrapper< bool, ReturnsBool >
{
private:
    
    typedef CallbackWrapper< bool, ReturnsBool > BaseClass;
    typedef EventCombination< ReturnsBool, OtherReturnsBool > ThisClass;

public:

    EventCombination( ReturnsBool& a_roCall,
                      OtherReturnsBool& a_roOtherCall );
    virtual ~EventCombination();
    std::size_t Hash() const override;

protected:
    
    virtual const char* ClassName() const override;
    virtual std::size_t OtherTargetHash() const;

    OtherReturnsBool* m_poOtherCall;

private:

    // class name for the hash function to use
    static const char* const CLASS_NAME;

};

// Event triggered by only one of two events occurring.
template< typename ReturnsBool, typename OtherReturnsBool >
class XOrEvent : public EventCombination< ReturnsBool, OtherReturnsBool >
{
private:

    typedef EventCombination< ReturnsBool, OtherReturnsBool > BaseClass;
    typedef XOrEvent< ReturnsBool, OtherReturnsBool > ThisClass;

public:

    XOrEvent( ReturnsBool& a_roCall, OtherReturnsBool& a_roOtherCall );

    ThisClass* Clone() const override;
    bool operator()() override;

protected:
    
    virtual const char* ClassName() const override;

private:
    
    // Keep copy constructor and assignment operator private to prevent
    // object slicing.  Copy constructor is used by Clone() and should be
    // implemented.  Assignment operator should not be used.
    XOrEvent( const ThisClass& ac_roEvent );
    ThisClass& operator=( const ThisClass& ac_roEvent );

    // class name for the hash function to use
    static const char* const CLASS_NAME;

};

// Event triggered by at least one of two events occurring.
// Both events are checked, in case they require ongoing tracking.
template< typename ReturnsBool, typename OtherReturnsBool >
class OrEvent : public EventCombination< ReturnsBool, OtherReturnsBool >
{
private:

    typedef EventCombination< ReturnsBool, OtherReturnsBool > BaseClass;
    typedef OrEvent< ReturnsBool, OtherReturnsBool > ThisClass;

public:

    OrEvent( ReturnsBool& a_roCall, OtherReturnsBool& a_roOtherCall );
    OrEvent( const ThisClass& ac_roEvent );

    ThisClass* Clone() const override;
    bool operator()() override;

protected:
    
    virtual const char* ClassName() const override;

private:
    
    // Keep copy constructor and assignment operator private to prevent
    // object slicing.  Copy constructor is used by Clone() and should be
    // implemented.  Assignment operator should not be used.
    OrEvent( const ThisClass& ac_roEvent );
    ThisClass& operator=( const ThisClass& ac_roEvent );

    // class name for the hash function to use
    static const char* const CLASS_NAME;

};

// Event triggered by two events both occurring
template< typename ReturnsBool, typename OtherReturnsBool >
class AndEvent
{
private:

    typedef EventCombination< ReturnsBool, OtherReturnsBool > BaseClass;
    typedef AndEvent< ReturnsBool, OtherReturnsBool > ThisClass;

public:

    AndEvent( ReturnsBool& a_roCall, OtherReturnsBool& a_roOtherCall );
    AndEvent( const ThisClass& ac_roEvent );

    ThisClass* Clone() const override;
    bool operator()() override;

protected:
    
    virtual const char* ClassName() const override;

private:
    
    // Keep copy constructor and assignment operator private to prevent
    // object slicing.  Copy constructor is used by Clone() and should be
    // implemented.  Assignment operator should not be used.
    AndEvent( const ThisClass& ac_roEvent );
    ThisClass& operator=( const ThisClass& ac_roEvent );

    // class name for the hash function to use
    static const char* const CLASS_NAME;

};

// Event triggered by another event starting, but not by said event continuing
template< typename ReturnsBool >
class EventStart : public CallbackWrapper< bool, ReturnsBool >
{
private:

    typedef CallbackWrapper< bool, ReturnsBool > BaseClass;
    typedef EventStart< ReturnsBool > ThisClass;

public:

    EventStart( ReturnsBool& a_roCall, bool a_bStarted = false );
    EventStart( const ThisClass& a_roEvent );

    ThisClass* Clone() const override;
    bool operator()() override;

protected:
    
    virtual const char* ClassName() const override;

private:
    
    // Keep copy constructor and assignment operator private to prevent
    // object slicing.  Copy constructor is used by Clone() and should be
    // implemented.  Assignment operator should not be used.
    EventStart( const ThisClass& ac_roEvent );
    ThisClass& operator=( const ThisClass& ac_roEvent );

    // class name for the hash function to use
    static const char* const CLASS_NAME;

    bool m_bStarted;

};

// Event triggered by another event ending
template< typename ReturnsBool >
class EventEnd : public EventStart< ReturnsBool >
{
private:

    typedef EventStart< ReturnsBool > BaseClass;
    typedef EventEnd< ReturnsBool > ThisClass;

public:

    EventEnd( ReturnsBool& a_roEvent, bool a_bStarted = false );
    EventEnd( const ThisClass& a_roEvent );

    ThisClass* Clone() const override;

protected:
    
    virtual const char* ClassName() const override;
    virtual std::size_t TargetHash() const override;

private:
    
    // Keep copy constructor and assignment operator private to prevent
    // object slicing.  Copy constructor is used by Clone() and should be
    // implemented.  Assignment operator should not be used.
    EventEnd( const ThisClass& ac_roEvent );
    ThisClass& operator=( const ThisClass& ac_roEvent );

    // class name for the hash function to use
    static const char* const CLASS_NAME;

    NotEvent<ReturnsBool> m_oNotEvent;
    ReturnsBool* m_poEvent;

};

}   // namespace Events

#include "inline/Events.inl"

#endif  // _EVENTS_H_