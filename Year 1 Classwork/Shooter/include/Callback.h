/******************************************************************************
 * File:               Callback.h
 * Author:             Elizabeth Lowry
 * Date Created:       October 29, 2013
 * Description:        Parent class for callbacks.
 * Last Modified:      November 6, 2013
 * Last Modification:  Simplified templating.
 ******************************************************************************/

#ifndef _CALLBACK_H_
#define _CALLBACK_H_

#include "Hashable.h"

// Parent class for callbacks.  Child classes will offer different operator()
// behavior and their own ClassName() values.
template< typename T = void >
class Callback : public Hashable
{
protected:

public:

    // Sets pointer to a clone of the parameter
    Callback( const Callback&& ac_rroCall );

    // Sets pointer to a wrapper pointing to the callable
    template< typename Callable >
    Callback( Callable& a_roCall );

    // Deletes the target of the pointer, if not null or self (in case a derived
    // class sets it to such values).
    ~Callback();

    // Allocate a new Callback pointing to a clone of the callback this one
    // points to.  Redefine this in derived classes to return pointers to said
    // derived classes instead of just Callback pointers. 
    virtual Callback* Clone() const;

    // Has based on class name and hash of target
    virtual std::size_t Hash() const override;

    // Returns a clone
    static Callback* New( const Callback&& ac_rroCall );

    // Returns a wrapper pointing to the parameter - if the parameter is local,
    // make sure the resulting Callback is deallocated at the end of scope so
    // that you don't end up with a callback pointing to deallocated memory!
    template< typename Callable >
    static Callback* New( Callable& a_roTarget );

    // Call internal callback pointer.  Redefine this in any class that can have
    // a null internal pointer or that has specialized behavior.
    virtual T operator()();

protected:

    // Used by constructor and make function when parameter isn't a Callback
    template< typename Callable >
    class Wrapper;

    // sets internal pointer to null, for non-wrapper child classes
    Callback();

    // Assumes cloning has been done by calling child class constructor
    Callback( Callback* a_poCall );

    // Returns components of this class's hash
    virtual const char* ClassName() const;
    virtual std::size_t TargetHash() const;

    // The actual target, a child class either wrapping a non-callback or
    // implementing some custom operator() behavior.  This object owns the
    // target and is responsible for deallocating it.
    Callback* m_poCall;

private:

    // Make copy and move constructors private to prevent slicing
    Callback( const Callback& ac_roCall );
    Callback( Callback&& a_rroCall );
    Callback& operator=( const Callback& ac_roCall );
    Callback& operator=( Callback&& ac_roCall );

    // Used by the ClassName function
    static const char* const CLASS_NAME;

};

// Wraps a non-callback object for use by the main Callback class
template< typename T >
template< typename Callable >
class Callback< T >::Wrapper : public Callback< T >
{
public:

    // The target can't be cloned, obviously, so it will be pointed to instead.
    // Unlike the parent class, the target isn't owned by this object, so it
    // won't be deallocated in the destructor.
    Wrapper( Callable& a_roTarget );
    virtual ~Wrapper(); // default implementation - no deallocations needed here

    virtual Wrapper* Clone() const override;
    virtual T operator()() override;

protected:

    virtual const char* ClassName() const override;
    virtual std::size_t TargetHash() const override;

    Callable* m_poTarget;

private:

    static const char* const CLASS_NAME;

};

#include "inline/Callback.inl"

#endif  // _CALLBACK_H_