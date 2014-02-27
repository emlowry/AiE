/******************************************************************************
 * File:               InitializeableSingleton.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 26, 2014
 * Description:        Base class for singleton objects that can be initialized
 *                      and destroyed.
 * Last Modified:      February 26, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef INITIALIZEABLE_SINGLETON__H
#define INITIALIZEABLE_SINGLETON__H

#include "NotCopyable.h"
#include <stdexcept>

namespace Utility
{

// To create a singleton class, inherit from this class, make this class a
// friend, and implement a private default constructor:
//
//  class MySingleton : public InitializeableSingleton< MySingleton >
//  {
//      friend InitializeableSingleton;
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
            T* poInstance = sm_poInstance;
            sm_poInstance = nullptr;
            delete poInstance;
        }
    }

protected:

    // You shouldn't ever construct a singleton directly - the constructor is
    // only called internally by the Instance() function.
    InitializeableSingleton() {}

    static T* sm_poInstance;

};  // class InitializeableSingleton
template< typename T >
T* InitializeableSingleton< T >::sm_poInstance = nullptr;

}   // namespace Utility

#endif  // INITIALIZEABLE_SINGLETON__H
