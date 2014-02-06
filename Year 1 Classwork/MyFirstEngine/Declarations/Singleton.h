/******************************************************************************
 * File:               Singleton.h
 * Author:             Elizabeth Lowry
 * Date Created:       February 5, 2014
 * Description:        Base class for singlton objects.
 * Last Modified:      February 5, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef SINGLETON__H
#define SINGLETON__H

// To create a singleton class without having to define your own MakeInstance
// implementation, inherit from this class instead, make this class a friend,
// and implement a private default constructor:
//
//  class MySingleton : public Singleton< MySingleton >
//  {
//      // non-private class stuff goes here
//  
//  private:
//      friend DefaultSingleton;
//      MySingleton()
//      {
//          // constructor tasks go here
//      }
//  };
template< typename T >
class Singleton
{
public:
    
    virtual ~Singleton() {}
    static T& Instance() { static T instance; return instance; }

protected:

    Singleton() {}

private:

    // Don't implement these, since singletons shouldn't be copyable.
    Singleton( const Singleton& ac_roSingleton );
    Singleton( Singleton&& a_rroSingleton );
    Singleton& operator=( const Singleton& ac_roSingleton );
    Singleton& operator=( Singleton&& a_rrSingleton );

};

#endif  // SINGLETON__H
