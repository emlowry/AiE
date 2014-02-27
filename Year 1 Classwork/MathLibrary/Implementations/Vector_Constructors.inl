/******************************************************************************
 * File:               Vector_Constructors.inl
 * Author:             Elizabeth Lowry
 * Date Created:       December 17, 2013
 * Description:        Constructor implementations for Vector.h.
 * Last Modified:      January 5, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

#ifndef VECTOR__CONSTRUCTORS__INL
#define VECTOR__CONSTRUCTORS__INL

// #include <type_traits>  // for std::is_whateverable checks
#include <utility>  // for std::forward and std::move

namespace Math
{

// Destructor doesn't need to do anything
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >::~Vector() {}

// Constructors that forward to base class constructors
// Private so they can only be called by the friend child class
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >::Vector() : BaseType() {}
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U, unsigned int P, unsigned int Q >
inline Vector< T, N, t_bIsRow >::
    Vector( const Matrix< U, P, Q >& ac_roMatrix, const T& ac_rFill )
    : BaseType( ac_roMatrix, ac_rFill ) {}
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >::Vector( const T& ac_rFill )
    : BaseType( ac_rFill ) {}
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >::Vector( const T (&ac_raData)[ N ] )
    : BaseType( ac_raData ) {}

// Assignment operators that pass to base class
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U, unsigned int P, unsigned int Q >
inline Vector< T, N, t_bIsRow >& Vector< T, N, t_bIsRow >::
    operator=( const Matrix< U, P, Q >& ac_roMatrix )
{
    BaseType::operator=( ac_roMatrix );
    return *this;
}
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >& Vector< T, N, t_bIsRow >::
    operator=( const T& ac_rFill )
{
    BaseType::operator=( ac_rFill );
    return *this;
}
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >& Vector< T, N, t_bIsRow >::
    operator=( const T (&ac_raData)[ N ] )
{
    BaseType::operator=( ac_raData );
    return *this;
}

// Copy construct/assign from a different kind of vector
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U, unsigned int Q, bool t_bOtherIsRow >
inline Vector< T, N, t_bIsRow >::
    Vector( const Vector< U, Q, t_bOtherIsRow >& ac_roVector, const T& ac_rFill )
{/*
    if( !std::is_copy_assignable< T >::value )
    {
        throw exception("Non-copy-assignable type");
    }
    if( !std::is_convertible< U, T >:: value )
    {
        throw exception("Non-convertable input type");
    } /**/
    for( unsigned int i = 0; i < N; ++i )
    {
        At(i) = ( i < Q ) ? (T)(ac_roVector[i]) : ac_rFill;
    }
}
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U, unsigned int Q, bool t_bOtherIsRow >
inline Vector< T, N, t_bIsRow >& Vector< T, N, t_bIsRow >::
    operator=( const Vector< U, Q, t_bOtherIsRow >& ac_roVector )
{/*
    if( !std::is_copy_assignable< T >::value )
    {
        throw exception("Non-copy-assignable type");
    }
    if( !std::is_convertible< U, T >:: value )
    {
        throw exception("Non-convertable input type");
    } /**/
    if( ThisIsNot( ac_roVector ) )
    {
        for( unsigned int i = 0; i < N && i < Q; ++i )
        {
            At(i) = (T)(ac_roVector[i]);
        }
    }
    return *this;
}

}   // namespace Math

#endif  // VECTOR__CONSTRUCTORS__INL