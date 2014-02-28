/******************************************************************************
 * File:               Singleton.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 5, 2014
 * Description:        Base class for singleton objects.
 * Last Modified:      February 27, 2014
 * Last Modification:  Updating comment.
 ******************************************************************************/

#ifndef SINGLETON__H
#define SINGLETON__H

#include "NotCopyable.h"

namespace Utility
{

// To create a singleton class, inherit from this class, make this class a
// friend, and implement a private default constructor:
//
//  class MySingleton : public Singleton< MySingleton >
//  {
//      friend Singleton;
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
//  };  // MySingleton
template< typename T >
class Singleton : public NotCopyable
{
public:
    
    // You can destroy an object of a type derived from the singleton class
    // through a pointer or reference of this base type.
    virtual ~Singleton() {}

    // If the singleton instance is only used internally by static member
    // functions, then making this a protected or private base class instead of
    // a public one will make this Instance() function protected or private as
    // well, respectively.
    static T& Instance() { static T instance; return instance; }

protected:

    // You shouldn't ever construct a singleton directly - the constructor is
    // only called internally by the Instance() function.
    Singleton() {}

};  // class Singleton

}   // namespace Utility

#endif  // SINGLETON__H
