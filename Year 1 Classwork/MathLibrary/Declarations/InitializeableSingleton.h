/******************************************************************************
 * File:               InitializeableSingleton.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 26, 2014
 * Description:        Base class for singleton objects that can be initialized
 *                      and destroyed.
 * Last Modified:      February 27, 2014
 * Last Modification:  Adding virtual functions.
 ******************************************************************************/

#ifndef INITIALIZEABLE_SINGLETON__H
#define INITIALIZEABLE_SINGLETON__H

#include "NotCopyable.h"
#include <stdexcept>

namespace Utility
{

// To create a singleton class, inherit from this class, make this class a
// friend, and implement a private default constructor and, if neccessary,
// InitializeInstance and TerminateInstance functions:
//
//  class MySingleton : public InitializeableSingleton< MySingleton >
//  {
//      friend InitializeableSingleton;
//
//  public:
//
//      virtual ~MySingleton()
//      {
//          // destructor tasks go here
//      }
//      
//      // non-private class stuff goes here
//  
//  private:
//      
//      MySingleton()
//      {
//          // constructor tasks go here
//      }
//
//      // this can be left out if there's nothing for it to do
//      virtual void InitializeInstance() override
//      {
//          // setup tasks go here
//      }
//
//      // this can be left out if there's nothing for it to do
//      virtual void TerminateInstance() override
//      {
//          // tear down tasks go here
//      }
//      
//  };  // MySingleton
template< typename T >
class InitializeableSingleton : public NotCopyable
{
public:
    
    // You can destroy an object of a type derived from the singleton class
    // through a pointer or reference of this base type.
    virtual ~InitializeableSingleton() {}

    // Create the instance
    static void Initialize()
    {
        if( nullptr == sm_poInstance )
        {
            sm_poInstance = new T();
            Instance().InitializeInstance();
        }
    }

    // Has the singleton been initialized yet?
    static bool IsInitialized()
    {
        return nullptr != sm_poInstance;
    }

    // If the singleton instance is only used internally by static member
    // functions, then making this a protected or private base class instead of
    // a public one will make this Instance() function protected or private as
    // well, respectively.
    static T& Instance()
    {
        if( nullptr == sm_poInstance )
        {
            throw std::runtime_error( "Instance not initialized" );
        }
        return *sm_poInstance;
    }

    // Destroy the instance
    static void Terminate()
    {
        if( nullptr != sm_poInstance )
        {
            Instance().TerminateInstance();
            T* poInstance = sm_poInstance;
            sm_poInstance = nullptr;
            delete poInstance;
        }
    }

protected:

    // You shouldn't ever construct a singleton directly - the constructor is
    // only called internally by the Instance() function.
    InitializeableSingleton() {}

    // Virtual function lookup is disabled in constructors and destructors, so
    // any child-class-specific initialization tasks should be specified here so
    // they can be called after/before the constructor/destructor
    virtual void InitializeInstance() {};
    virtual void TerminateInstance() {};

    static T* sm_poInstance;

};  // class InitializeableSingleton
template< typename T >
T* InitializeableSingleton< T >::sm_poInstance = nullptr;

}   // namespace Utility

#endif  // INITIALIZEABLE_SINGLETON__H
