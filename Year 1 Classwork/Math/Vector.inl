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
inline Vector< T, N >::Vector( const MatrixType& ac_roMatrix )
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
inline Vector< T, N >::Vector( MatrixType&& a_rroMatrix )
    : BaseType( std::forward( a_rroMatrix ) ) {}
template< typename T, unsigned int N >
template< typename U, unsigned int Q, bool t_bOtherIsRow >
inline Vector< T, N >::
    Vector( const NumericVectorBase< U, Q, t_bOtherIsRow >& ac_roVector,
            const T& ac_rFill )
    : BaseType( ac_roVector, ac_rFill ) {}
template< typename T, unsigned int N >
template< typename U, unsigned int Q, bool t_bOtherIsRow >
inline Vector< T, N >::
    Vector( const VectorBase< U, Q, t_bOtherIsRow >& ac_roVector,
            const T& ac_rFill )
    : BaseType( ac_roVector, ac_rFill ) {}
template< typename T, unsigned int N >
template< typename U, unsigned int P, unsigned int Q >
inline Vector< T, N >::Vector( const MatrixBase< U, P, Q >& ac_roMatrix,
                               const T& ac_rFill )
    : BaseType( ac_roMatrix, ac_rFill ) {}
template< typename T, unsigned int N >
template< typename U >
inline Vector< T, N >::Vector( const U& ac_rFill ) : BaseType( ac_rFill ) {}
template< typename T, unsigned int N >
template< typename U, unsigned int t_uiSize >
inline Vector< T, N >::Vector( const U (&ac_raData)[ t_uiSize ],
                               const T& ac_rFill )
    : BaseType( ac_raData, ac_rFill ) {}
template< typename T, unsigned int N >
template< typename U >
inline Vector< T, N >::Vector( const U* const ac_cpData,
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
inline Vector< T, N, false >::Vector( const VectorBaseType& ac_roVector )
    : BaseType( ac_roVector ) {}
template< typename T, unsigned int N >
inline Vector< T, N, false >::Vector( const MatrixType& ac_roMatrix )
    : BaseType( ac_roMatrix ) {}
template< typename T, unsigned int N >
inline Vector< T, N, false >::Vector( Vector&& a_rroVector )
    : BaseType( std::forward( a_rroVector ) ) {}
template< typename T, unsigned int N >
inline Vector< T, N, false >::Vector( VectorBaseType&& a_rroVector )
    : BaseType( std::forward( a_rroVector ) ) {}
template< typename T, unsigned int N >
inline Vector< T, N, false >::Vector( MatrixType&& a_rroMatrix )
    : BaseType( std::forward( a_rroMatrix ) ) {}
template< typename T, unsigned int N >
template< typename U, unsigned int Q, bool t_bOtherIsRow >
inline Vector< T, N, false >::
    Vector( const Vector< U, Q, t_bOtherIsRow >& ac_roVector )
    : BaseType( ac_roVector ) {}
template< typename T, unsigned int N >
template< typename U, unsigned int Q, bool t_bOtherIsRow >
inline Vector< T, N, false >::
    Vector( const VectorBase< U, Q, t_bOtherIsRow >& ac_roVector )
    : BaseType( ac_roVector ) {}
template< typename T, unsigned int N >
template< typename U, unsigned int P, unsigned int Q >
inline Vector< T, N, false >::Vector( const MatrixBase< U, P, Q >& ac_roMatrix,
                                      const T& ac_rFill )
    : BaseType( ac_roMatrix, ac_rFill ) {}
template< typename T, unsigned int N >
template< typename U >
inline Vector< T, N, false >::Vector( const U& ac_rFill )
    : BaseType( ac_rFill ) {}
template< typename T, unsigned int N >
template< typename U, unsigned int t_uiSize >
inline Vector< T, N, false >::Vector( const U (&ac_raData)[ t_uiSize ],
                                      const T& ac_rFill )
    : BaseType( ac_raData, ac_rFill ) {}
template< typename T, unsigned int N >
template< typename U >
inline Vector< T, N, false >::Vector( const U* const ac_cpData,
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
inline Vector< MatrixInverse< T >::Type, P, true >
    Vector< T, N >::operator/( const Matrix< T, P, N >& ac_roMatrix ) const
{
    Vector< MatrixInverse< T >::Type, P > Result;
    return Result( MatrixType::operator/( ac_roMatrix ) );
}

// Column vector 1x1 matrix multiplication produces another column matrix
template< typename T, unsigned int N >
inline Vector< T, N, false >
    Vector< T, N, false >::
    operator*( const Matrix< T, 1, 1 >& ac_roMatrix ) const
{
    return Vector< T, N, false >( MatrixType::operator*( ac_roMatrix ) );
}
template< typename T, unsigned int N >
inline Vector< MatrixInverse< T >::Type, N, false >
    Vector< T, N, false >::
    operator/( const Matrix< T, 1, 1 >& ac_roMatrix ) const
{
    typedef Vector< MatrixInverse< T >::Type, N, false > Result;
    return Result( MatrixType::operator/( ac_roMatrix ) );
}

}   // namespace Math

#endif  // _VECTOR_INL_
