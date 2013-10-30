/******************************************************************************
 * File:               Callback.inl
 * Author:             Elizabeth Lowry
 * Date Created:       October 29, 2013
 * Description:        Inline function implementations for Callback.h.
 * Last Modified:      October 29, 2013
 * Last Modification:  Moved code out of Globals.inl.
 ******************************************************************************/

// Wrapper constructors.
template< typename T, typename Callable >
inline CallbackWrapper< T, Callable >::CallbackWrapper( Callable& a_roCall )
    : m_roCall( a_roCall ) {};
template< typename T, typename Callable >
inline CallbackWrapper< T, Callable >::CallbackWrapper(
                            const CallbackWrapper< T, Callable >& ac_roWrapper )
    : m_roCall( a_roWrapper.m_roCall ) {};

// Dynamically allocate a Callback wrapper that calls the same callable object
// as this wrapper.
template< typename T, typename Callable >
inline CallbackWrapper< T, Callable >* CallbackWrapper< T, Callable >::Clone()
{
    return new CallbackWrapper( m_roCall );
}

// Hash based on callable object's address.
template< typename T, typename Callable >
inline std::size_t CallbackWrapper< T, Callable >::Hash() const
{
    return &a_roCall;
}

// Pass operator() call to the wrapped object.
template< typename T, typename Callable >
inline T CallbackWrapper< T, Callable >::operator()()
{
    return m_roCall();
}
