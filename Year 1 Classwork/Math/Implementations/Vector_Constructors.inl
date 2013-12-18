/******************************************************************************
 * File:               Vector_Constructors.inl
 * Author:             Elizabeth Lowry
 * Date Created:       December 17, 2013
 * Description:        Constructor implementations for Vector.h.
 * Last Modified:      December 17, 2013
 * Last Modification:  Moving code out of Vector.inl.
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
inline Vector< T, N, t_bIsRow >::Vector( const Vector& ac_roVector )
    : BaseType( ac_roVector ) {}
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >::Vector( const BaseType& ac_roVector )
    : BaseType( ac_roVector ) {}
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >::Vector( const RootType& ac_roMatrix )
    : BaseType( ac_roMatrix ) {}
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >::Vector( Vector&& a_rroVector )
    : BaseType( std::forward< Vector >( a_rroVector ) ) {}
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >::Vector( BaseType&& a_rroVector )
    : BaseType( std::forward< BaseType >( a_rroVector ) ) {}
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >::Vector( RootType&& a_rroMatrix )
    : BaseType( std::forward< RootType >( a_rroMatrix ) ) {}
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U, unsigned int Q, bool t_bOtherIsRow >
inline Vector< T, N, t_bIsRow >::
    Vector( const Vector< U, Q, t_bOtherIsRow >& ac_roVector,
            const T& ac_rFill )
    : BaseType( ac_roVector, ac_rFill ) {}
template< typename T, unsigned int N, bool t_bIsRow >
template< unsigned int Q, bool t_bOtherIsRow >
inline Vector< T, N, t_bIsRow >::
    Vector( Vector< T, Q, t_bOtherIsRow >&& a_rroVector,
            const T& ac_rFill )
    : BaseType( std::forward< Vector< T, Q, t_bOtherIsRow > >( a_rroVector ),
                ac_rFill ) {}
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U, unsigned int Q, bool t_bOtherIsRow >
inline Vector< T, N, t_bIsRow >::
    Vector( const VectorBase< U, Q, t_bOtherIsRow >& ac_roVector,
            const T& ac_rFill )
    : BaseType( ac_roVector, ac_rFill ) {}
template< typename T, unsigned int N, bool t_bIsRow >
template< unsigned int Q, bool t_bOtherIsRow >
inline Vector< T, N, t_bIsRow >::
    Vector( VectorBase< T, Q, t_bOtherIsRow >&& a_rroVector,
            const T& ac_rFill )
    : BaseType( std::forward< VectorBase< T, Q, t_bOtherIsRow > >( a_rroVector ),
                ac_rFill ) {}
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U, unsigned int P, unsigned int Q >
inline Vector< T, N, t_bIsRow >::
    Vector( const MatrixBase< U, P, Q >& ac_roMatrix, const T& ac_rFill )
    : BaseType( ac_roMatrix, ac_rFill ) {}
template< typename T, unsigned int N, bool t_bIsRow >
template< unsigned int P, unsigned int Q >
inline Vector< T, N, t_bIsRow >::
    Vector( MatrixBase< T, P, Q >&& a_rroMatrix, const T& ac_rFill )
    : BaseType( std::forward< MatrixBase< T, P, Q > >( a_rroMatrix ), ac_rFill ) {}
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >::Vector( const T& ac_rFill )
    : BaseType( ac_rFill ) {}
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >::Vector( const T (&ac_raData)[ N ] )
    : BaseType( ac_raData ) {}
template< typename T, unsigned int N, bool t_bIsRow >
inline Vector< T, N, t_bIsRow >::Vector( const T* const ac_cpData,
                                         const unsigned int ac_uiSize,
                                         const T& ac_rFill )
    : BaseType( ac_cpData, ac_uiSize, ac_rFill ) {}

// Copy and move assign from a different type of numeric vector
// These are specified to remove ambiguity between MatrixBase::operator= and
// VectorBase::operator=, since both could work - MatrixBase::operator= is
// available through inheritance from Matrix, VectorBase::operator= through
// inheritance from VectorBase.
template< typename T, unsigned int N, bool t_bIsRow >
template< typename U, unsigned int Q, bool t_bOtherIsRow >
inline Vector< T, N, t_bIsRow >& Vector< T, N, t_bIsRow >::
    operator=( const Vector< U, Q, t_bOtherIsRow >& ac_roVector )
{
    BaseType::operator=( ac_roVector );
    return *this;
}
template< typename T, unsigned int N, bool t_bIsRow >
template< unsigned int Q, bool t_bOtherIsRow >
inline Vector< T, N, t_bIsRow >& Vector< T, N, t_bIsRow >::
    operator=( Vector< T, Q, t_bOtherIsRow >&& a_rroVector )
{
    BaseType::operator=(
                std::forward< Vector< T, Q, t_bOtherIsRow > >( a_rroVector ) );
    return *this;
}

}   // namespace Math

#endif  // VECTOR__CONSTRUCTORS__INL