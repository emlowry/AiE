/******************************************************************************
 * File:               DoubleCallback.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 4, 2013
 * Description:        Class that turns any two things implementing operator()
 *                      with no parameters into a callback object.
 *                      TODO: after this gets ported to Eclipse, use variadic
 *                      template parameters to implement a MultiCallback class -
 *                      like this one, but combining any number of callables.
 * Last Modified:      November 4, 2013
 * Last Modification:  Moved code out of Callback.h.
 ******************************************************************************/

#ifndef _DOUBLE_CALLBACK_WRAPPER_H_
#define _DOUBLE_CALLBACK_WRAPPER_H_

#include "Callback.h"
#include "CallbackWrapper.h"

// Abstract base class for generic and specialized wrapper classes - this way,
// implementation details don't have to be repeated in both.
template< typename T, typename Callable, typename OtherCallable >
class DoubleCallbackBase : public CallbackWrapperBase< T, Callable >
{
private:
    
    // Simplify typing and reduce parameter template typos
    typedef CallbackWrapperBase< T, Callable > BaseClass;
    typedef DoubleCallbackBase< T, Callable, OtherCallable > ThisClass;

public:

    // Redefine Hash to produce a code based on class name and *both* targets.
    virtual std::size_t Hash() const override;

    // Default implementation returns (m_poCall(), m_poOtherCall), so be careful
    // when T is a pointer type to dynamically allocated data.
    virtual T operator()() override;

protected:

    // Constructor should only be called by derived classes
    DoubleCallbackBase( Callable* a_poCall, OtherCallable* a_poOtherCall );
    virtual ~DoubleCallbackBase();
    
    // Default other target hash is hash of other target's address
    virtual std::size_t OtherTargetHash() const;

    OtherCallable* m_poOtherCall;

};

// General implementation for a pair of callable objects joined together into
// one callback
template< typename T, typename Callable, typename OtherCallable >
class DoubleCallback : public DoubleCallbackBase< T, Callable, OtherCallable >
{
private:
    
    // Simplify typing and reduce parameter template typos
    typedef DoubleCallbackBase< T, Callable, OtherCallable > BaseClass;
    typedef DoubleCallback< T, Callable, OtherCallable > ThisClass;

public:

    // Reference parameters ensure that targets exist.  If either target is
    // local, make sure this wrapper stays local too!
    DoubleCallback( Callable& a_roCall, OtherCallable& a_roOtherCall );
    virtual ~DoubleCallback();

    virtual ThisClass* Clone() const override;

};

// Partially specialized implementations for any callable and a callback
template< typename T, typename Callable >
class DoubleCallback< T, Callable, Callback< T > >
    : public DoubleCallbackBase< T, Callable, Callback< T > >
{
private:
    
    // Simplify typing and reduce parameter template typos
    typedef DoubleCallbackBase< T, Callable, RootClass > BaseClass;
    typedef DoubleCallback< T, Callable, RootClass > ThisClass;

public:
    
    // Reference parameters ensure that targets exist.  If the non-callback
    // parameter or the final target of the callback parameter are local, make
    // sure this wrapper stays local too.
    DoubleCallback( Callable& a_roCall, const RootClass&& ac_rroOtherCall );
    virtual ~DoubleCallback();

    virtual ThisClass* Clone() const override;

protected:
    
    // Other target hash is other target's hash
    virtual std::size_t OtherTargetHash() const;

};
template< typename T, typename OtherCallable >
class DoubleCallback< T, Callback< T >, OtherCallable >
    : public DoubleCallbackBase< T, Callback< T >, OtherCallable >
{
private:
    
    // Simplify typing and reduce parameter template typos
    typedef DoubleCallbackBase< T, RootClass, OtherCallable > BaseClass;
    typedef DoubleCallback< T, RootClass, OtherCallable > ThisClass;

public:
    
    // Reference parameters ensure that targets exist.  If the non-callback
    // parameter or the final target of the callback parameter are local, make
    // sure this wrapper stays local too!
    DoubleCallback( const RootClass&& ac_rroCall,
                    OtherCallable& a_roOtherCall );
    virtual ~DoubleCallback();

    virtual ThisClass* Clone() const override;

protected:
    
    // Target hash is target's hash
    virtual std::size_t TargetHash() const;

};

// Fully specialized implementation for a pair of Callbacks
template< typename T >
class DoubleCallback< T, Callback< T >, Callback< T > >
    : public DoubleCallbackBase< T, Callback< T >, Callback< T > >
{
private:
    
    // Simplify typing and reduce parameter template typos
    typedef DoubleCallbackBase< T, RootClass, RootClass > BaseClass;
    typedef DoubleCallback< T, RootClass, RootClass > ThisClass;

public:

    // Reference parameters ensure that targets exist.  If the final target of
    // either parameter are local, make sure this wrapper stays local too!
    DoubleCallback( const RootClass&& ac_rroCall,
                    const RootClass&& ac_rroOtherCall );
    virtual ~DoubleCallback();

    virtual ThisClass* Clone() const override;

protected:
    
    // Target hashes are other targets' hashes
    virtual std::size_t TargetHash() const;
    virtual std::size_t OtherTargetHash() const;

};

#include "inline/DoubleCallback.inl"

#endif  // _DOUBLE_CALLBACK_WRAPPER_H_