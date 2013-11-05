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

// Create a callback from any callable object without worrying about the
// template parameter for the callable object's type - in a non-constructor
// function, the template parameters can be inferred from the function params.
// If the object is iteself a Callback, clone it - otherwise, wrap it.
template< typename T, typename Callable >
inline Callback< T >* Callback< T >::Create( Callable& a_roCall )
{
    return new CallbackWrapper< T, Callable >( a_roCall );
}
template< typename T >
inline Callback< T >* Callback< T >::Create( const RootClass&& ac_rroCall )
{
    return ac_rroCall.Clone();
}

// Create a callback from any pair of callable objects without worrying about
// the template parameters for the callable objects' types.
template< typename T, typename Callable, typename OtherCallable >
inline Callback< T >* Callback<T>::Create( Callable& a_roCall,
                                           OtherCallable& a_roOtherCall )
{
    return new DoubleCallback< T, Callable, OtherCallable >( a_roCall,
                                                             a_roOtherCall );
}
template< typename T, typename Callable >
inline Callback< T >* Callback<T>::Create( Callable& a_roCall,
                                           const RootClass&& ac_rroOtherCall )
{
    return new DoubleCallback< T, Callable, RootClass >( a_roCall,
                                                         ac_rroOtherCall );
}
template< typename T, typename OtherCallable >
inline Callback< T >* Callback<T>::Create( const RootClass&& ac_rroCall,
                                           OtherCallable& a_roOtherCall )
{
    return new DoubleCallback< T, RootClass, OtherCallable >( ac_rroCall,
                                                              a_roOtherCall );
}
template< typename T >
inline Callback< T >* Callback<T>::Create( const RootClass&& ac_rroCall,
                                           const RootClass&& ac_rroOtherCall )
{
    return new DoubleCallback< T, RootClass, RootClass >( ac_rroCall,
                                                          ac_rroOtherCall );
}

// Hash callbacks by callback class name and target hash
template< typename T >
inline std::size_t Callback< T >::Hash() const
{
    stringstream oStream;
    oStream << ClassName() << "(" << TargetHash() << ")";
    std::hash<string> hasher;
    return hasher( oStream.str() );
}

// Callback default target hash is the hash of its address
template< typename T >
inline std::size_t CallBack< T >::TargetHash() const
{
    std::hash< RootClass* > hasher();
    return hasher( this );
}
