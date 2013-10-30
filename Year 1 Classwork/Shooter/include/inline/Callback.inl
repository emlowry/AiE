/******************************************************************************
 * File:               Callback.inl
 * Author:             Elizabeth Lowry
 * Date Created:       October 29, 2013
 * Description:        Inline function implementations for Callback.h.
 * Last Modified:      October 29, 2013
 * Last Modification:  Moved code out of Globals.inl.
 ******************************************************************************/

// Create a callback wrapper from any callable object without worrying about the
// template parameter for the callable object's type - in a non-constructor
// function, the template parameters can be inferred from the function params.
template< typename T, typename Callable >
inline static Callback< T >* Callback< T >::MakeCallBack( Callable& a_roCall )
{
    return new CallbackWrapper< T, Callable >( a_roCall );
}

// Wrapper constructor
template< typename T, typename Callable >
inline CallbackWrapper< T, Callable >::CallbackWrapper( Callable& a_roCall )
    : m_poCall( &a_roCall ) {};

// Wrapper copy constructor
template< typename T, typename Callable >
inline CallbackWrapper< T, Callable >::CallbackWrapper(
                            const CallbackWrapper< T, Callable >& ac_roWrapper )
    : m_poCall( ac_roWrapper.m_poCall ) {};

// Dynamically allocate a Callback wrapper that calls the same callable object
// as this wrapper.
template< typename T, typename Callable >
inline CallbackWrapper< T, Callable >* CallbackWrapper< T, Callable >::Clone() const
{
    return new CallbackWrapper( *this );
}

// Hash based on callable object's address.
template< typename T, typename Callable >
inline std::size_t CallbackWrapper< T, Callable >::Hash() const
{
    return (std::size_t)a_poCall;
}

// Pass operator() call to the wrapped object.
template< typename T, typename Callable >
inline T CallbackWrapper< T, Callable >::operator()()
{
    return (*m_poCall)();
}
