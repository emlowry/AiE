/******************************************************************************
 * File:               CallbackWrapper.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 4, 2013
 * Description:        Class that turns anything implementing operator() with no
 *                      parameters into a callback object.
 * Last Modified:      November 4, 2013
 * Last Modification:  Moved code out of Callback.h.
 ******************************************************************************/

#ifndef _CALLBACK_WRAPPER_H_
#define _CALLBACK_WRAPPER_H_

#include "Callback.h"

// Abstract base class for generic and specialized wrapper classes - this way,
// implementation details don't have to be repeated in both.
template< typename T, typename Callable = Callback< T > >
class CallbackWrapperBase : public Callback< T >
{
private:

    // Simplifies typing and reduces template parameter typos
    typedef CallbackWrapperBase< T, Callable > ThisClass;

public:

    // Default implementation simply calls the wrapped object.  Clone is
    // implemented by derived classes.
    virtual T operator()() override;

protected:

    // Base class constructor should only be called by derived class
    // constructors.
    CallbackWrapperBase( Callable* a_poCall );
    virtual ~CallbackWrapperBase();

    // Default class name is "CallbackWrapper" and default target hash is the
    // wrapped object's address.
    virtual const char* ClassName() const override;
    virtual std::size_t TargetHash() const override;

    // Must implement T operator()() with no parameters.
    Callable* m_poCall;

private:

    // class name for the hash function to use
    static const char* const CLASS_NAME;

};

// Generic callback wrapper for turning anything that implements operator() with
// no parameters into a callback
template< typename T, typename Callable = Callback< T > >
class CallbackWrapper : public CallbackWrapperBase< T, Callable >
{
private:
    
    // Simplify typing and reduce template parameter typos
    typedef CallbackWrapperBase< T, Callable > BaseClass;
    typedef CallbackWrapper< T, Callable > ThisClass;

public:

    // Reference parameter ensures that target exists.  If target is local, make
    // sure this wrapper stays local too!
    CallbackWrapper( Callable& a_roCall );
    virtual ~CallbackWrapper();

    virtual ThisClass* Clone() const override;

};

// Specialized wrapper for other callbacks - clones the constructor parameter
// instead of just pointing to it, which allows said parameter to be constant
// and requires that the destructor deallocate the clone.
template< typename T >
class CallbackWrapper< T >
    : public CallbackWrapperBase< T >
{
private:
    
    // Simplify typing and reduce template parameter typos
    typedef CallbackWrapperBase< T > BaseClass;
    typedef CallbackWrapper< T > ThisClass;

public:
    
    // Reference parameter ensures that target exists.  If the final target of
    // the parameter is local, make sure this wrapper stays local too!
    CallbackWrapper( const RootClass&& ac_rroCall );
    virtual ~CallbackWrapper();

    virtual ThisClass* Clone() const override;

protected:

    // Target hash is the wrapped callback's hash.
    virtual std::size_t TargetHash() const override;

};

#include "inline/CallbackWrapper.inl"

#endif  // _CALLBACK_WRAPPER_H_