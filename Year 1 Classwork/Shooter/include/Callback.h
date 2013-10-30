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
    virtual std::size_t Hash() const override;
    virtual T operator()() = 0;

    template< typename Callable >
    static Callback< T >* Create( Callable& a_roCall );

protected:
    
    // Returns components of this class's hash
    virtual const char* ClassName() const;
    virtual std::size_t TargetHash() const;

private:

    static const char* const CLASS_NAME;

};

// Wrapper class for turning anything that implements operator() with no
// parameters into a callback
template< typename T, typename Callable >
class CallbackWrapper : public Callback< T >
{
public:

    CallbackWrapper( Callable& a_roCall );
    virtual ~CallbackWrapper();

    virtual CallbackWrapper< T, Callable >* Clone() const override;
    virtual T operator()() override;

protected:

    virtual const char* ClassName() const override;
    virtual std::size_t TargetHash() const override;

    Callable* a_poCall;  // Must implement T operator()()

private:

    // Keep copy constructor and assignment operator private to prevent
    // object slicing.  Copy constructor is used by Clone() and should be
    // implemented.  Assignment operator should not be used.
    CallbackWrapper( const CallbackWrapper< T, Callable >& ac_roWrapper );
    CallbackWrapper& operator=(
        const CallbackWrapper< T, Callable >& ac_roWrapper );

    // class name for the hash function to use
    static const char* const CLASS_NAME;

};

#include "inline/Callback.inl"

#endif  // _CALLBACK_H_