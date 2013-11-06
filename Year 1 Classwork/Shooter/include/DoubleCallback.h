/******************************************************************************
 * File:               DoubleCallback.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 4, 2013
 * Description:        Class that turns any two things implementing operator()
 *                      with no parameters into a callback object.
 *                      TODO: after this gets ported to Eclipse, use variadic
 *                      template parameters to implement a MultiCallback class -
 *                      like this one, but combining any number of callables.
 * Last Modified:      November 6, 2013
 * Last Modification:  Simplified templating.
 ******************************************************************************/

#ifndef _DOUBLE_CALLBACK_H_
#define _DOUBLE_CALLBACK_H_

#include "Callback.h"

// Base class that wraps to Callbacks or other callable objects into one.
template< typename T = void >
class DoubleCallback : public Callback< T >
{
public:

    // Sets pointers to clones of parameters
    DoubleCallback( const Callback< T >&& ac_rroCall,
                    const Callback< T >&& ac_rroOtherCall );

    // Sets first pointer to clone of first parameter, sets second pointer to a
    // wrapper pointing to the second parameter
    template< typename OtherCallable >
    DoubleCallback( const Callback< T >&& ac_rroCall,
                    OtherCallable& a_roOtherTarget );

    // Sets first pointer to a wrapper pointing to the first parameter, sets the
    // second pointer to a clone of the second parameter
    template< typename Callable >
    DoubleCallback( Callable& a_roTarget,
                    const Callback< T >&& ac_rroOtherCall );

    // Sets pointers to wrappers pointing to parameters
    template< typename Callable, typename OtherCallable >
    DoubleCallback( Callable& a_roTarget, OtherCallable& a_roOtherTarget );

    // Deallocate the second pointer.  Base Callback destructor will take care
    // of the first.
    virtual ~DoubleCallback();

    // Allocate a double callback that points to clones of the callbacks this
    // one points to
    virtual DoubleCallback* Clone() const override;

    // Hash by class name and both targets' hashes
    virtual std::size_t Hash() const override;

    // Call both targets, but only return the result of the second - in other
    // words, call ( FirstCall(), SecondCall() ).  Be careful if the return type
    // is dynamically allocated data - only make a double callback returning
    // that type if it's a derived class that can dispose of extra objects.
    virtual T operator()() override;

protected:

    // Default constructor sets both pointers to null, for derived classes that
    // point to a pair of things other than other callbacks.
    DoubleCallback();

    // Set the pointers directly.  Assumes the calling derived class constructor
    // has done any neccessary cloning.
    DoubleCallback( Callback< T >* a_poCall, Callback< T >* a_poOtherCall );

    // used by the hash function
    virtual std::size_t OtherTargetHash() const;

    // Other target to call.  This object owns the target and is responsible for
    // deallocating it.
    Callback< T >* m_poOtherCall;

};

#include "inline/DoubleCallback.inl"

#endif  // _DOUBLE_CALLBACK_H_