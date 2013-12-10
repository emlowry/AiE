/******************************************************************************
 * File:               Vector.inl
 * Author:             Elizabeth Lowry
 * Date Created:       November 25, 2013
 * Description:        Inline and other function implementations for Vector.
 * Last Modified:      November 25, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef _VECTOR_INL_
#define _VECTOR_INL_

// #include <type_traits>  // for std::is_whateverable checks
#include <utility>  // for std::forward and std::move

namespace Math
{

// Destructors do nothing
template< typename T, unsigned int N >
inline Vector< T, N >::~Vector() {}
template< typename T, unsigned int N >
inline Vector< T, N, false >::~Vector() {}

// Row vector constructors that forward to base class constructors
template< typename T, unsigned int N >
inline Vector< T, N >::Vector() : BaseType() {}
template< typename T, unsigned int N >
inline Vector< T, N >::Vector( const Vector& ac_roVector )
    : BaseType( ac_roVector ) {}
template< typename T, unsigned int N >
inline Vector< T, N >& Vector< T, N >::operator=( const Vector& ac_roVector )
{
    return BaseType::operator=( ac_roVector );
}
template< typename T, unsigned int N >
inline Vector< T, N >::Vector( const BaseType& ac_roVector )
    : BaseType( ac_roVector ) {}
template< typename T, unsigned int N >
inline Vector< T, N >::Vector( const VectorBaseType& ac_roVector )
    : BaseType( ac_roVector ) {}
template< typename T, unsigned int N >
inline Vector< T, N >::Vector( const RootType& ac_roMatrix )
    : BaseType( ac_roMatrix ) {}
template< typename T, unsigned int N >
inline Vector< T, N >::Vector( Vector&& a_rroVector )
    : BaseType( std::forward( a_rroVector ) ) {}
template< typename T, unsigned int N >
inline Vector< T, N >& Vector< T, N >::operator=( Vector&& a_rroVector )
{
    return BaseType::operator=( std::forward( a_rroVector ) );
}
template< typename T, unsigned int N >
inline Vector< T, N >::Vector( BaseType&& a_rroVector )
    : BaseType( std::forward( a_rroVector ) ) {}
template< typename T, unsigned int N >
inline Vector< T, N >::Vector( VectorBaseType&& a_rroVector )
    : BaseType( std::forward( a_rroVector ) ) {}
template< typename T, unsigned int N >
inline Vector< T, N >::Vector( RootType&& a_rroMatrix )
    : BaseType( std::forward( a_rroMatrix ) ) {}
template< typename T, unsigned int N >
template< unsigned int Q, bool t_bOtherIsRow >
inline Vector< T, N >::
    Vector( const NumericVectorBase< T, Q, t_bOtherIsRow >& ac_roVector,
            const T& ac_rFill )
    : BaseType( ac_roVector, ac_rFill ) {}
template< typename T, unsigned int N >
template< unsigned int Q, bool t_bOtherIsRow >
inline Vector< T, N >::
    Vector( const VectorBase< T, Q, t_bOtherIsRow >& ac_roVector,
            const T& ac_rFill )
    : BaseType( ac_roVector, ac_rFill ) {}
template< typename T, unsigned int N >
template< typename U >
inline Vector< T, N >::
    Vector( const MatrixBase< U, ROWS, COLUMNS >& ac_roMatrix )
    : BaseType( ac_roMatrix ) {}
template< typename T, unsigned int N >
template< unsigned int P, unsigned int Q >
inline Vector< T, N >::Vector( const MatrixBase< T, P, Q >& ac_roMatrix,
                               const T& ac_rFill )
    : BaseType( ac_roMatrix, ac_rFill ) {}
template< typename T, unsigned int N >
inline Vector< T, N >::Vector( const T& ac_rFill ) : BaseType( ac_rFill ) {}
template< typename T, unsigned int N >
inline Vector< T, N >::Vector( const T (&ac_raData)[ N ] )
    : BaseType( ac_raData ) {}
template< typename T, unsigned int N >
inline Vector< T, N >::Vector( const T* const ac_cpData,
                               const unsigned int ac_uiSize,
                               const T& ac_rFill )
    : BaseType( ac_cpData, ac_uiSize, ac_rFill ) {}

// Column vector constructors that forward to base class constructors
template< typename T, unsigned int N >
inline Vector< T, N, false >::Vector() : BaseType() {}
template< typename T, unsigned int N >
inline Vector< T, N, false >::Vector( const Vector& ac_roVector )
    : BaseType( ac_roVector ) {}
template< typename T, unsigned int N >
inline Vector< T, N, false >& Vector< T, N, false >::
    operator=( const Vector& ac_roVector )
{
    return BaseType::operator=( ac_roVector );
}
template< typename T, unsigned int N >
inline Vector< T, N, false >::Vector( const VectorBaseType& ac_roVector )
    : BaseType( ac_roVector ) {}
template< typename T, unsigned int N >
inline Vector< T, N, false >::Vector( const MatrixType& ac_roMatrix )
    : BaseType( ac_roMatrix ) {}
template< typename T, unsigned int N >
inline Vector< T, N, false >::Vector( Vector&& a_rroVector )
    : BaseType( std::forward( a_rroVector ) ) {}
template< typename T, unsigned int N >
inline Vector< T, N, false >& Vector< T, N, false >::
    operator=( Vector&& a_rroVector )
{
    return BaseType::operator=( std::forward( a_rroVector ) );
}
template< typename T, unsigned int N >
inline Vector< T, N, false >::Vector( VectorBaseType&& a_rroVector )
    : BaseType( std::forward( a_rroVector ) ) {}
template< typename T, unsigned int N >
inline Vector< T, N, false >::Vector( RootType&& a_rroMatrix )
    : BaseType( std::forward( a_rroMatrix ) ) {}
template< typename T, unsigned int N >
template< unsigned int Q, bool t_bOtherIsRow >
inline Vector< T, N, false >::
    Vector( const Vector< T, Q, t_bOtherIsRow >& ac_roVector )
    : BaseType( ac_roVector ) {}
template< typename T, unsigned int N >
template< unsigned int Q, bool t_bOtherIsRow >
inline Vector< T, N, false >::
    Vector( const VectorBase< T, Q, t_bOtherIsRow >& ac_roVector )
    : BaseType( ac_roVector ) {}
template< typename T, unsigned int N >
template< typename U >
inline Vector< T, N, false >::
    Vector( const MatrixBase< U, ROWS, COLUMNS >& ac_roMatrix )
    : BaseType( ac_roMatrix ) {}
template< typename T, unsigned int N >
template< unsigned int P, unsigned int Q >
inline Vector< T, N, false >::Vector( const MatrixBase< T, P, Q >& ac_roMatrix,
                                      const T& ac_rFill )
    : BaseType( ac_roMatrix, ac_rFill ) {}
template< typename T, unsigned int N >
inline Vector< T, N, false >::Vector( const T& ac_rFill )
    : BaseType( ac_rFill ) {}
template< typename T, unsigned int N >
inline Vector< T, N, false >::Vector( const T (&ac_raData)[ N ] )
    : BaseType( ac_raData ) {}
template< typename T, unsigned int N >
inline Vector< T, N, false >::Vector( const T* const ac_cpData,
                                      const unsigned int ac_uiSize,
                                      const T& ac_rFill )
    : BaseType( ac_cpData, ac_uiSize, ac_rFill ) {}

// Row vector matrix multiplication produces another row matrix
template< typename T, unsigned int N >
template< unsigned int P >
inline Vector< T, P >
    Vector< T, N >::operator*( const Matrix< T, N, P >& ac_roMatrix ) const
{
    return Vector< T, P >( MatrixType::operator*( ac_roMatrix ) );
}
template< typename T, unsigned int N >
template< unsigned int P >
inline Vector< typename MatrixInverse< T >::Type, P, true >
    Vector< T, N >::operator/( const Matrix< T, P, N >& ac_roMatrix ) const
{
    Vector< typename MatrixInverse< T >::Type, P > Result;
    return Result( MatrixType::operator/( ac_roMatrix ) );
}

}   // namespace Math

#endif  // _VECTOR_INL_
