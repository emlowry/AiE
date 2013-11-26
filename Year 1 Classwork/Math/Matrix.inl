/******************************************************************************
 * File:               Matrix.inl
 * Author:             Elizabeth Lowry
 * Date Created:       November 18, 2013
 * Description:        Function implementations for Matrix template class.
 * Last Modified:      November 18, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef _MATRIX_INL_
#define _MATRIX_INL_

// #include <type_traits>  // for is_whateverable checks
#include <utility>  // for move

namespace Math
{

// Zero matrix
template< typename T, unsigned int M, unsigned int N >
ZERO_MATRIX< T, M, N >( 0 );
template< typename T, unsigned int M, unsigned int N >
const Matrix< T, M, N >& Matrix< T, M, N >::ZERO = ZERO_MATRIX< T, M, N >;

// Identity matrix
template< typename T, unsigned int N >
IDENTITY_MATRIX< T, N >( 1, 0 );
template< typename T, unsigned int M, unsigned int N >
const Matrix< T, ( M < N ? M : N ) >&
    Matrix< T, M, N >::IDENTITY = IDENTITY_MATRIX< T, ( M < N ? M : N ) >;

// TODO - constructors that forward to base class

// Construct with diagonal elements set to the second given value and all others
// set to the first
template< typename T, unsigned int M, unsigned int N >
template< typename U, typename V >
Matrix< T, M, N >::Matrix( const U& ac_rFill, const V& ac_rIdentityFill )
{/*
    if( !std::is_copy_constructable< T >::value )
    {
        throw exception("Non-copy-constructable type");
    }
    if( !std::is_convertible< U, T >:: value )
    {
        throw exception("Non-convertable input type");
    }
    if( !std::is_convertible< V, T >:: value )
    {
        throw exception("Non-convertable input type");
    } /**/
    for( unsigned int i = 0; i < M; ++i )
    {
        for( unsigned int j = 0; j < N; ++j )
        {
            if( i == j )
            {
                m_aaData[i][j]( (T)( ac_rIdentityFill ) );
            }
            else
            {
                m_aaData[i][j]( (T)( ac_rFill ) );
            }
        }
    }
}

// TODO

}   // namespace Math

#endif _MATRIX_INL_
