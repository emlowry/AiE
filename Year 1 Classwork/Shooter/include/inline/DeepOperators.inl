/******************************************************************************
 * File:               DeepOperators.inl
 * Author:             Elizabeth Lowry
 * Date Created:       November 12, 2013
 * Description:        Inline function implementations for DeepOperators.h.
 * Last Modified:      November 12, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef _DEEP_OPERATORS_INL_
#define _DEEP_OPERATORS_INL_

// Equality
template< typename T >
inline bool DeepEqualTo< T >::operator()( const T* const ac_cpoLeft,
                                          const T* const ac_cpoRight ) const
{
    return ( ac_cpoLeft != nullptr && ac_cpoRight != nullptr )
            ? base( ac_cpoLeft, ac_cpoRight ) : ac_cpoLeft == ac_cpoRight;
}
template< typename T >
inline bool 
    DeepEqualTo< const T >::operator()( const T* const ac_cpoLeft,
                                        const T* const ac_cpoRight ) const
{
    return ( ac_cpoLeft != nullptr && ac_cpoRight != nullptr )
            ? base( ac_cpoLeft, ac_cpoRight ) : ac_cpoLeft == ac_cpoRight;
}

// Hash
template< typename T >
inline std::size_t DeepHash< T >::operator()( const T* const ac_cpoT ) const
{
    return ( ac_cpoT != nullptr ) ? base( ac_cpoT )
                                  : std::hash< T* >::( nullptr );
}
template< typename T >
inline std::size_t
    DeepHash< const T >::operator()( const T* const ac_cpoT ) const
{
    return ( ac_cpoT != nullptr ) ? base( ac_cpoT )
                                  : std::hash< T* >::( nullptr );
}

// Less Than
template< typename T >
inline bool DeepLess< T >::operator()( const T* const ac_cpoLeft,
                                       const T* const ac_cpoRight ) const
{
    return ( ac_cpoLeft != nullptr && ac_cpoRight != nullptr )
            ? base( ac_cpoLeft, ac_cpoRight )
            : ( nullptr == ac_cpoLeft ) ? ( nullptr != ac_cpoRight ) : false;
}
template< typename T >
inline bool DeepLess< const T >::operator()( const T* const ac_cpoLeft,
                                             const T* const ac_cpoRight ) const
{
    return ( ac_cpoLeft != nullptr && ac_cpoRight != nullptr )
            ? base( ac_cpoLeft, ac_cpoRight )
            : ( nullptr == ac_cpoLeft ) ? ( nullptr != ac_cpoRight ) : false;
}

#endif  // _DEEP_OPERATORS_INL_
