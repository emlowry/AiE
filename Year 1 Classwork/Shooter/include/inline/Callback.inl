/******************************************************************************
 * File:               Callback.inl
 * Author:             Elizabeth Lowry
 * Date Created:       October 29, 2013
 * Description:        Inline function implementations for Callback.h.
 * Last Modified:      November 6, 2013
 * Last Modification:  Simplified templating.
 ******************************************************************************/

#ifndef _CALLBACK_INL_
#define _CALLBACK_INL_

#include <functional>   // for std::hash
#include <sstream>      // for std::stringstream
#include <string>       // for std::string

// Public constructors
template< typename T >
inline Callback< T >::Callback( const Callback&& ac_rroCall )
    : m_poCall( ac_rroCall.Clone() ) {}
template< typename T >
template< typename Callable >
inline Callback< T >::Callback( Callable& a_roTarget )
    : m_poCall( new Wrapper< Callable >( a_roTarget ) ) {}

// Protected constructors
template< typename T >
inline Callback< T >::Callback() : m_poCall( nullptr ) {}
template< typename T >
inline Callback< T >::Callback( Callback* a_poCall ) : m_poCall( a_poCall ) {}

// Destructor
template< typename T >
inline Callback< T >::~Callback()
{
    // Derived classes might set the pointer to something undeletable, so check
    if( nullptr != m_poCall && this != m_poCall )
    {
        delete m_poCall;
        m_poCall = nullptr;
    }
}

// Callback class name
template< typename T >
const char* const Callback< T >::CLASS_NAME = "Callback";
template< typename T >
inline const char* Callback< T >::ClassName() const
{
    return CLASS_NAME;
}

// Clone the callback
template< typename T >
inline Callback< T >* Callback< T >::Clone() const
{
    return new Callback( *m_poCall );
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

// Static functions for creating a new callback out of anything implementing
// operator() with no parameters and the correct return type, without
// unneccessary wrapping if the parameter is already a callback
template< typename T >
inline Callback< T >* Callback< T >::New( const Callback&& ac_rroCall )
{
    return ac_rroCall.Clone();
}
template< typename T >
template< typename Callable >
inline Callback< T >* Callback< T >::New( Callable& a_roTarget )
{
    return new Wrapper< Callable >( a_roTarget );
}

// Call the target of the internal pointer.  Since this assumes the target is
// valid, this operator must be redefined in any child class that sets the
// internal pointer to null (or this, though why anyone would do that...)
template< typename T >
inline T Callback< T >::operator()()
{
    return (*m_poCall)();
}

// Callback default target hash is pointer target's hash, if target is another
// callback, or the hash of the pointer itself if target is null or this.
template< typename T >
inline std::size_t Callback< T >::TargetHash() const
{
    return ( nullptr != m_poCall && this != m_poCall )
            ? m_poCall->Hash()
            : std::hash< const Callback< T >* >()( m_poCall );
}

// Wrapper constructor invokes protected default callback constructor to set
// internal callback pointer to null, since this class points to a non-callback
// object instead.
template< typename T >
template< typename Callable >
inline Callback< T >::Wrapper< Callable >::Wrapper( Callable& a_roTarget )
    : m_poTarget( &a_roTarget ) {}

// Wrapper classname
template< typename T >
template< typename Callable >
const char* const Callback< T >::Wrapper< Callable >::CLASS_NAME = "Wrapper";
template< typename T >
template< typename Callable >
inline const char* Callback< T >::Wrapper< Callable >::ClassName() const
{
    return CLASS_NAME;
}

// Clone a wrapper callback
template< typename T >
template< typename Callable >
inline typename Callback< T >::Wrapper< Callable >*
    Callback< T >::Wrapper< Callable >::Clone() const
{
    return new Wrapper( *m_poTarget );
}

// Wrapper calls its target.  The target has better implement operator() with no
// parameters and the given return type!
template< typename T >
template< typename Callable >
inline T Callback< T >::Wrapper< Callable >::operator()()
{
    return (*m_poTarget)();
}

// Wrapper target hash is hash of the target pointer
template< typename T >
template< typename Callable >
inline std::size_t Callback< T >::Wrapper< Callable >::TargetHash() const
{
    return std::hash< const Callable* >()( m_poTarget );
}

#endif  // _CALLBACK_INL_
