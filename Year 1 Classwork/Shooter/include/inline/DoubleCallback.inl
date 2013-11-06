/******************************************************************************
 * File:               DoubleCallback.inl
 * Author:             Elizabeth Lowry
 * Date Created:       November 4, 2013
 * Description:        Inline function implementations for DoubleCallback.h.
 * Last Modified:      November 6, 2013
 * Last Modification:  Simplified templating.
 ******************************************************************************/

#ifndef _DOUBLE_CALLBACK_INL_
#define _DOUBLE_CALLBACK_INL_

#include <functional>   // for std::hash
#include <sstream>      // for std::stringstream
#include <string>       // for std::string
#include <utility>      // for std::forward

// Public constructors
template< typename T >
inline DoubleCallback< T >::
    DoubleCallback( const Callback< T >&& ac_rroCall,
                    const Callback< T >&& ac_rroOtherCall )
    : Callback( std::forward< const Callback< T > >( ac_rroCall ) ),
      m_poOtherCall( ac_rroOtherCall.Clone() ) {}
template< typename T >
template< typename OtherCallable >
inline DoubleCallback< T >::DoubleCallback( const Callback< T >&& ac_rroCall,
                                            OtherCallable& a_roOtherTarget )
    : Callback( std::forward< const Callback< T > >( ac_rroCall ) ),
      m_poOtherCall( new Wrapper< OtherCallable >( a_roOtherTarget ) ) {}
template< typename T >
template< typename Callable >
inline DoubleCallback< T >::
    DoubleCallback( Callable& a_roTarget,
                    const Callback< T >&& ac_rroOtherCall )
    : Callback( a_roTarget ), m_poOtherCall( ac_rroOtherCall.Clone() ) {}
template< typename T >
template< typename Callable, typename OtherCallable >
inline DoubleCallback< T >::DoubleCallback( Callable& a_roTarget,
                                            OtherCallable& a_roOtherTarget )
    : Callback( a_roTarget ),
      m_poOtherCall( new Wrapper< OtherCallable >( a_roOtherTarget ) ) {}

// Protected constructors
template< typename T >
inline DoubleCallback< T >::DoubleCallback() : m_poOtherCall( nullptr ) {}
template< typename T >
inline DoubleCallback< T >::DoubleCallback( Callback< T >* a_poCall,
                                            Callback< T >* a_poOtherCall )
    : Callback( a_poCall ), m_poOtherCall( a_poOtherCall ) {}

// Destructor deallocates the second pointer (base class destructor will handle
// the first pointer)
template< typename T >
inline DoubleCallback< T >::~DoubleCallback()
{
    // derived classes could set the second pointer to something undeleteable,
    // so check
    if( nullptr != m_poOtherCall && this != m_poOtherCall )
    {
        delete m_poOtherCall;
        m_poOtherCall = nullptr;
    }
}

// Clone this callback
template< typename T >
inline DoubleCallback< T >* DoubleCallback< T >::Clone() const
{
    return new DoubleCallback( *m_poCall, *m_poOtherCall );
}

// Hash double callbacks by callback class name and both targets' hashes
template< typename T >
inline std::size_t DoubleCallback< T >::Hash() const
{
    std::stringstream oStream;
    oStream << ClassName() << "(" << TargetHash()
            << "," << OtherTargetHash() << ")";
    std::hash< std::string > hasher;
    return hasher( oStream.str() );
}

// Call both targets, return the result of the second - calling this is
// thus equivalent to calling ( FirstCall(), SecondCall() )
template< typename T >
inline T DoubleCallback< T >::operator()()
{
    return ( (*m_poCall)(), (*m_poOtherCall)() );
}

// Other target hash is hash of other target, if target is valid, or of other
// target's address
template< typename T >
inline std::size_t DoubleCallback< T >::OtherTargetHash() const
{
    return ( nullptr != m_poOtherCall && this != m_poOtherCall )
            ? m_poOtherCall->Hash()
            : std::hash< const Callback< T >* >()( m_poOtherCall );
}

#endif  // _DOUBLE_CALLBACK_INL_
