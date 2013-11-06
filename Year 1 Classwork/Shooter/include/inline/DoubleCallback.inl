/******************************************************************************
 * File:               DoubleCallback.inl
 * Author:             Elizabeth Lowry
 * Date Created:       November 4, 2013
 * Description:        Inline function implementations for DoubleCallback.h.
 * Last Modified:      November 4, 2013
 * Last Modification:  Moved code out of Callback.inl.
 ******************************************************************************/

#include <functional>
#include <sstream>
#include <string>

// Base class constructor
template< typename T, typename Callable, typename OtherCallable >
inline DoubleCallbackBase< T, Callable, OtherCallable >::
    DoubleCallbackBase( Callable* a_poCall, OtherCallable* a_poOtherCall )
    : BaseClass( a_poCall ), m_poOtherCall( a_poOtherCall ) {}

// Generic class constructor
template< typename T, typename Callable, typename OtherCallable >
inline DoubleCallback< T, Callable, OtherCallable >::
    DoubleCallback( Callable& a_roCall, OtherCallable& a_roOtherCall )
    : BaseClass( &a_roCall, &a_roOtherCall ) {}

// Partially-specialized class constructors
template< typename T, typename Callable >
inline DoubleCallback< T, Callable >::
    DoubleCallback( Callable& a_roCall, const RootClass&& ac_rroOtherCall )
    : BaseClass( &a_roCall, ac_rroOtherCall.Clone() ) {}
template< typename T, typename OtherCallable >
inline DoubleCallback< T, Callback< T >, OtherCallable >::
    DoubleCallback( const RootClass&& ac_rroCall, OtherCallable& a_roOtherCall )
    : BaseClass( ac_rroCall.Clone(), &a_roOtherCall ) {}

// Fully-specialized class constructor
template< typename T >
inline DoubleCallback< T >::DoubleCallback( const RootClass&& ac_rroCall,
                                            const RootClass&& ac_rroOtherCall )
    : BaseClass( ac_rroCall.Clone(), ac_rroOtherCall.Clone() ) {}

// Partially and fully specialized class destructors
template< typename T, typename Callable >
inline DoubleCallback< T, Callable >::~DoubleCallback()
{
    delete m_poOtherCall;
}
template< typename T, typename OtherCallable >
inline DoubleCallback< T, Callback< T >, OtherCallable >::~DoubleCallback()
{
    delete m_poCall;
}
template< typename T >
inline DoubleCallback< T >::~DoubleCallback()
{
    delete m_poCall;
    delete m_poOtherCall;
}

// Dynamically allocate a Callback wrapper that calls the same callable object
// as this wrapper.
template< typename T, typename Callable, typename OtherCallable >
inline DoubleCallback< T, Callable, OtherCallable >*
    DoubleCallback< T, Callable, OtherCallable >::Clone() const
{
    return new ThisClass( *m_poCall, *m_poOtherCall );
}
template< typename T, typename Callable >
inline DoubleCallback< T, Callable >*
    DoubleCallback< T, Callable >::Clone() const
{
    return new ThisClass( *m_poCall, *m_poOtherCall );
}
template< typename T, typename OtherCallable >
inline DoubleCallback< T, Callback< T >, OtherCallable >*
    DoubleCallback< T, Callback< T >, OtherCallable >::Clone() const
{
    return new ThisClass( *m_poCall, *m_poOtherCall );
}
template< typename T >
inline DoubleCallback< T >* DoubleCallback< T >::Clone() const
{
    return new ThisClass( *m_poCall, *m_poOtherCall );
}

// Hash double callbacks by callback class name and both targets' hashes
template< typename T, typename Callable, typename OtherCallable >
inline std::size_t DoubleCallbackBase< T, Callable, OtherCallable >::
    Hash() const
{
    std::stringstream oStream;
    oStream << ClassName() << "(" << TargetHash()
            << "," << OtherTargetHash() << ")";
    std::hash< std::string > hasher;
    return hasher( oStream.str() );
}

// Call both wrapped objects, return the result of the second - calling this is
// thus equivalent to calling ( FirstCall(), SecondCall() )
template< typename T, typename Callable, typename OtherCallable >
inline T DoubleCallbackBase< T, Callable, OtherCallable >::operator()()
{
    return ( (*m_poCall)(), (*m_poOtherCall)() );
}

// Other target hash is hash of other target, if other target is a callback, or
// other target's address
template< typename T, typename Callable, typename OtherCallable >
inline std::size_t DoubleCallbackBase< T, Callable, OtherCallable >::
    OtherTargetHash() const
{
    std::hash< OtherCallable* > hasher;
    return hasher( m_poOtherCall );
}
template< typename T, typename Callable >
inline std::size_t DoubleCallback< T, Callable >::OtherTargetHash() const
{
    return m_poOtherCall->Hash();
}
template< typename T >
inline std::size_t DoubleCallback< T >::OtherTargetHash() const
{
    return m_poOtherCall->Hash();
}

// Target hash is hash of other target, if other target is a callback
template< typename T, typename OtherCallable >
inline std::size_t DoubleCallback< T, Callback< T >, OtherCallable >::
    TargetHash() const
{
    return m_poCall->Hash();
}
template< typename T >
inline std::size_t DoubleCallback< T >::TargetHash() const
{
    return m_poCall->Hash();
}
