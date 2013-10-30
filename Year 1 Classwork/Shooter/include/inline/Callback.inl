/******************************************************************************
 * File:               Callback.inl
 * Author:             Elizabeth Lowry
 * Date Created:       October 29, 2013
 * Description:        Inline function implementations for Callback.h.
 * Last Modified:      October 29, 2013
 * Last Modification:  Moved code out of Globals.inl.
 ******************************************************************************/

#include <functional>
#include <sstream>
#include <string>

// Callback class name
template< typename T >
const char* const CallBack< T >::CLASS_NAME = "Callback";
template< typename T >
const char* CallBack< T >::ClassName() const
{
    return CLASS_NAME;
}

// Hash callbacks by callback class name and target hash
template< typename T >
inline static std::size_t Callback< T >::Hash() const
{
    stringstream oStream;
    oStream << ClassName() << "(" << TargetHash() << ")";
    std::hash<string> hasher;
    return hasher( oStream.str() );
}

// Callback default target hash is the hash of its address
template< typename T >
std::size_t CallBack< T >::TargetHash() const
{
    std::hash< Callback< T >* > hasher();
    return hasher( this );
}

// Create a callback from any callable object without worrying about the
// template parameter for the callable object's type - in a non-constructor
// function, the template parameters can be inferred from the function params.
// If the object is iteself a Callback, clone it - otherwise, wrap it.
template< typename T, typename Callable >
inline static Callback< T >* Callback< T >::Create( Callable& a_roCall )
{
    return new CallbackWrapper< T, Callable >( a_roCall );
}
template< typename T >
inline static Callback< T >*
    Callback< T >::Create( const Callback< T >& a_roCall )
{
    return a_roCall.Clone();
}

// CallbackWrapper class name
template< typename T, typename Callable >
const char* const CallBackWrapper< T, Callable >::CLASS_NAME ="CallbackWrapper";
template< typename T, typename Callable >
const char* CallBackWrapper< T, Callable >::ClassName() const
{
    return CLASS_NAME;
}

// CallbackWrapper default target hash is the hash of the target, if the target
// is hashable, or the target's address.
template< typename T, typename Callable >
std::size_t CallBackWrapper< T, Callable >::TargetHash() const
{
    std::hash< Callable* > hasher();
    return hasher( m_poCall );
}
template< typename T >
std::size_t CallBackWrapper< T, Hashable >::TargetHash() const
{
    return m_poCall->Hash();
}

// Wrapper constructor
template< typename T, typename Callable >
inline CallbackWrapper< T, Callable >::CallbackWrapper( Callable& a_roCall )
    : m_poCall( &a_roCall ) {};
template< typename T >
inline CallbackWrapper< T, Callback >::CallbackWrapper( const Callback& a_roCall )
    : m_poCall( a_roCall.Clone() ) {};

// Wrapper copy constructor
template< typename T, typename Callable >
inline CallbackWrapper< T, Callable >::CallbackWrapper(
                            const CallbackWrapper< T, Callable >& ac_roWrapper )
    : m_poCall( ac_roWrapper.m_poCall ) {};

// Dynamically allocate a Callback wrapper that calls the same callable object
// as this wrapper using the private copy constructor.
template< typename T, typename Callable >
inline CallbackWrapper< T, Callable >* CallbackWrapper< T, Callable >::Clone() const
{
    return new CallbackWrapper( *this );
}

// Pass operator() call to the wrapped object.
template< typename T, typename Callable >
inline T CallbackWrapper< T, Callable >::operator()()
{
    return (*m_poCall)();
}
