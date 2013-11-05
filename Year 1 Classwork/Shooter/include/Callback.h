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
protected:

    // Save typing (and prevent mistakes with template parameter) in derived
    // classes by using this typedef.
    typedef Callback< T > RootClass;
    
public:

    // Clone and operator() must be implemented by derived classes.  Hash hashes
    // the callback based on class name (default "Callback") and the hash of a
    // target address (default this) unless overridden by derived classes.
    virtual RootClass* Clone() const = 0;
    virtual std::size_t Hash() const override;
    virtual T operator()() = 0;

    // Turn anything that implements operator() with no parameters into a
    // callable without worrying about the type of said object.
    template< typename Callable >
    static RootClass* Create( Callable& a_roCall );
    static RootClass* Create( const RootClass&& ac_rroCall );
    template< typename Callable, typename OtherCallable >
    static RootClass* Create( Callable& a_roCall,
                              OtherCallable& a_roOtherCall );
    template< typename Callable >
    static RootClass* Create( Callable& a_roCall,
                              const RootClass&& ac_rroOtherCall );
    template< typename OtherCallable >
    static RootClass* Create( const RootClass&& ac_rroCall,
                              OtherCallable& a_roOtherCall );
    static RootClass* Create( const RootClass&& ac_rroCall,
                              const RootClass&& ac_rroOtherCall );

protected:

    // Returns components of this class's hash
    virtual const char* ClassName() const;
    virtual std::size_t TargetHash() const;

private:

    // Make copy and move constructors private to prevent slicing
    Callback( const Callback& ac_roCall );
    Callback( Callback&& a_rroCall );
    Callback& operator=( const Callback& ac_roCall );
    Callback& operator=( Callback&& ac_roCall );

    // Used by the ClassName function
    static const char* const CLASS_NAME;

};

#include "inline/Callback.inl"

#endif  // _CALLBACK_H_