/******************************************************************************
 * File:               Callback.inl
 * Author:             Elizabeth Lowry
 * Date Created:       October 29, 2013
 * Description:        Inline function implementations for Callback.h.
 * Last Modified:      October 29, 2013
 * Last Modification:  Moved code out of Globals.inl.
 ******************************************************************************/

#include "CallbackWrapper.h"
#include "DoubleCallback.h"
#include <functional>
#include <sstream>
#include <string>

// Callback class name
template< typename T >
const char* const Callback< T >::CLASS_NAME = "Callback";
template< typename T >
const char* Callback< T >::ClassName() const
{
    return CLASS_NAME;
}

// Hash callbacks by callback class name and target hash
template< typename T >
inline std::size_t Callback< T >::Hash() const
{
    std::stringstream oStream;
    oStream << ClassName() << "(" << TargetHash() << ")";
    //std::hash< std::string > hasher;
    return std::hash< std::string >()( oStream.str() );
}

// Create a callback from any callable object without worrying about the
// template parameter for the callable object's type - in a non-constructor
// function, the template parameters can be inferred from the function params.
// If the object is iteself a Callback, clone it - otherwise, wrap it.
template< typename T, typename Callable >
inline Callback< T >* NewCallback( Callable& a_roCall )
{
    return new CallbackWrapper< T, Callable >( a_roCall );
}
template< typename T >
inline Callback< T >* NewCallback( const Callback< T >&& ac_rroCall )
{
    return ac_rroCall.Clone();
}

// Create a callback from any pair of callable objects without worrying about
// the template parameters for the callable objects' types.
template< typename T, typename Callable, typename OtherCallable >
inline Callback< T >* NewCallback( Callable& a_roCall,
                                   OtherCallable& a_roOtherCall )
{
    typedef DoubleCallback< T, Callable, OtherCallable > DC;
    return new DC( a_roCall,  a_roOtherCall );
}
template< typename T, typename Callable >
inline Callback< T >* NewCallback( Callable& a_roCall,
                                   const Callback< T >&& ac_rroOtherCall )
{
    typedef DoubleCallback< T, Callable, Callback< T > > DC;
    return new DC( a_roCall, std::forward< Callback< T > >( ac_rroOtherCall ) );
}
template< typename T, typename OtherCallable >
inline Callback< T >* NewCallback( const Callback< T >&& ac_rroCall,
                                   OtherCallable& a_roOtherCall )
{
    typedef DoubleCallback< T, Callback< T >, OtherCallable > DC;
    return new DC( std::forward< Callback< T > >( ac_rroCall ), a_roOtherCall );
}
template< typename T >
inline Callback< T >* NewCallback( const Callback< T >&& ac_rroCall,
                                   const Callback< T >&& ac_rroOtherCall )
{
    typedef DoubleCallback< T, Callback< T >, Callback< T > > DC;
    return new DC( std::forward< Callback< T > >( ac_rroCall ),
                   std::forward< Callback< T > >( ac_rroOtherCall ) );
}

// Callback default target hash is the hash of its address
template< typename T >
inline std::size_t Callback< T >::TargetHash() const
{
    //std::hash< RootClass* > hasher();
    return std::hash< const RootClass* >()( this );
}
