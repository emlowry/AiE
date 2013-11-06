/******************************************************************************
 * File:               CallbackWrapper.inl
 * Author:             Elizabeth Lowry
 * Date Created:       November 4, 2013
 * Description:        Inline function implementations for CallbackWrapper.h.
 * Last Modified:      November 4, 2013
 * Last Modification:  Moved code out of Callback.inl.
 ******************************************************************************/

// Base class constructor
template< typename T, typename Callable >
inline CallbackWrapperBase< T, Callable >::
    CallbackWrapperBase( Callable* a_poCall )
    : m_poCall( a_poCall ) {}

// Generic class constructor
template< typename T, typename Callable >
inline CallbackWrapper< T, Callable >::CallbackWrapper( Callable& a_roCall )
    : BaseClass( &a_roCall ) {}

// Specialized class constructor
template< typename T >
inline CallbackWrapper< T >::
    CallbackWrapper( const RootClass&& ac_rroCall )
    : BaseClass( ac_roCall.Clone() ) {}

// Specialized class destructor
template< typename T >
inline CallbackWrapper< T >::~CallbackWrapper()
{
    delete m_poCall;
}

// CallbackWrapper class name
template< typename T, typename Callable >
const char* const CallbackWrapperBase< T, Callable >::
    CLASS_NAME = "CallbackWrapper";
template< typename T, typename Callable >
inline const char* CallbackWrapperBase< T, Callable >::ClassName() const
{
    return CLASS_NAME;
}

// Dynamically allocate a Callback wrapper that calls the same callable object
// as this wrapper.
template< typename T, typename Callable >
inline CallbackWrapper< T, Callable >*
    CallbackWrapper< T, Callable >::Clone() const
{
    return new ThisClass( *m_poCall );
}
template< typename T >
inline CallbackWrapper< T >*
    CallbackWrapper< T >::Clone() const
{
    return new ThisClass( *m_poCall );
}

// Pass operator() call to the wrapped object.
template< typename T, typename Callable >
inline T CallbackWrapperBase< T, Callable >::operator()()
{
    return (*m_poCall)();
}

// CallbackWrapper target hash is the hash of the target, if the target is
// another callback, or of the target's address.
template< typename T, typename Callable >
std::size_t CallbackWrapperBase< T, Callable >::TargetHash() const
{
    std::hash< Callable* > hasher();
    return hasher( m_poCall );
}
template< typename T >
std::size_t CallbackWrapper< T >::TargetHash() const
{
    return m_poCall->Hash();
}
