/******************************************************************************
 * File:               Callback.h
 * Author:             Elizabeth Lowry
 * Date Created:       October 29, 2013
 * Description:        Abstract parent struct for callbacks.
 * Last Modified:      October 29, 2013
 * Last Modification:  Moved code out of Globals.h.
 ******************************************************************************/

#ifndef _CALLBACK_H_
#define _CALLBACK_H_

#include "Hashable.h"

// Abstract parent class for callbacks
template< typename T >
class Callback : public Hashable
{
public:
    virtual Callback< T >* Clone() const = 0;
    virtual T operator()() = 0;
};

// Wrapper class for turning anything that implements operator() with no
// parameters into a callback
template< typename T, typename Callable >
class CallbackWrapper : public Callback< T >
{
public:

    CallbackWrapper( Callable& a_roCall );
    CallbackWrapper( const CallbackWrapper< T, Callable >& ac_roWrapper );

    // Dynamically allocate another wrapper that refers to the same callable
    // object as this one.
    virtual CallbackWrapper< T, Callable >* Clone() override;
    virtual std::size_t Hash() const override;  // Hash by target address
    virtual T operator()() override;            // Pass to wrapped object

protected:

    Callable a_roCall;  // Must implement T operator()()

private:

    // Assignment operator wouldn't work due to reference member.
    CallbackWrapper& operator=(
        const CallbackWrapper< T, Callable >& ac_roWrapper );

};

#include "inline/Callback.inl"

#endif  // _CALLBACK_H_