/******************************************************************************
 * File:               MatrixBaseFillConstructors.inl
 * Author:             Elizabeth Lowry
 * Date Created:       November 25, 2013
 * Description:        MatrixBase (and VectorBase) constructors and assignment
 *                      operators that fill the object with values from
 *                      parameters of the matrix (or vector) data type.
 * Last Modified:      November 25, 2013
 * Last Modification:  Moving code out of MatrixBase.inl.
 ******************************************************************************/

#ifndef _MATRIX_BASE_FILL_CONSTRUCTORS_INL_
#define _MATRIX_BASE_FILL_CONSTRUCTORS_INL_

// #include <type_traits>  // for std::is_whateverable checks

namespace Math
{

// Construct with all elements set to the given value
template< typename T, unsigned int M, unsigned int N >
template< typename U >
inline MatrixBase< T, M, N >::MatrixBase( const U& ac_rFill )
{/*
    if( !std::is_copy_constructable< T >::value )
    {
        throw exception("Non-copy-constructable type");
    }
    if( !std::is_convertible< U, T >:: value )
    {
        throw exception("Non-convertable input type");
    } /**/
    for( unsigned int i = 0; i < M*N; ++i )
    {
        m_aaData[i/N][i%N]( (T)( ac_rFill ) );
    }
}

// Assign all elements to the given value
template< typename T, unsigned int M, unsigned int N >
template< typename U >
inline MatrixBase< T, M, N >& MatrixBase< T, M, N >::Assign( const U& ac_rFill )
{/*
    if( !std::is_copy_assignable< T >::value )
    {
        throw exception("Non-copy-assignable type");
    }
    if( !std::is_convertible< U, T >:: value )
    {
        throw exception("Non-convertable input type");
    } /**/
    for( unsigned int i = 0; i < M*N; ++i )
    {
        m_aaData[i/N][i%N] = (T)( ac_rFill );
    }
}
template< typename T, unsigned int M, unsigned int N >
template< typename U >
inline MatrixBase< T, M, N >& MatrixBase< T, M, N >::
    operator=( const U& ac_rFill )
{
    Assign( ac_rFill );
}

// Construct with parameter data one row at a time until end of parameter data,
// then filled with given fill value
template< typename T, unsigned int M, unsigned int N >
template< typename U >
inline MatrixBase< T, M, N >::MatrixBase( const U* const ac_cpData,
                                          const unsigned int ac_uiSize,
                                          const T& ac_rFill )
{/*
    if( !std::is_copy_constructable< T >::value )
    {
        throw exception("Non-copy-constructable type");
    }
    if( !std::is_convertible< U, T >:: value )
    {
        throw exception("Non-convertable input type");
    } /**/
    for( unsigned int i = 0; i < M*N; ++i )
    {
        m_aaData[i/N][i%N]( ( i < ac_uiSize ) ? (T)(ac_cpData[i]) : ac_rFill );
    }
}
template< typename T, unsigned int M, unsigned int N >
template< typename U, unsigned int t_uiSize >
inline MatrixBase< T, M, N >::MatrixBase( const U (&ac_raData)[ t_uiSize ],
                                          const T& ac_rFill)
    : MatrixBase( ac_roData, t_uiSize, ac_rFill ) {}

// Assign parameter data one row at a time until end of parameter data
template< typename T, unsigned int M, unsigned int N >
template< typename U, unsigned int t_uiSize >
inline MatrixBase< T, M, N >& MatrixBase< T, M, N >::
    Assign( const U (&ac_raData)[ t_uiSize ] )
{/*
    if( !std::is_copy_assignable< T >::value )
    {
        throw exception("Non-copy-assignable type");
    }
    if( !std::is_convertible< U, T >:: value )
    {
        throw exception("Non-convertable input type");
    } /**/
    for( unsigned int i = 0; i < M*N && i < t_uiSize; ++i )
    {
        m_aaData[i/N][i%N] = ac_raData[i];
    }
}
template< typename T, unsigned int M, unsigned int N >
template< typename U, unsigned int t_uiSize >
inline MatrixBase< T, M, N >& MatrixBase< T, M, N >::
    operator=( const U (&ac_raData)[ t_uiSize ] )
{
    Assign( ac_raData );
}

// Construct with parameter data where given and fill data elsewhere
template< typename T, unsigned int M, unsigned int N >
template< typename U >
inline MatrixBase< T, M, N >::MatrixBase( const U* const* const ac_cpcpData,
                                          const unsigned int ac_uiRows = M,
                                          const unsigned int ac_uiColumns = N,
                                          const T& ac_rFill )
{/*
    if( !std::is_copy_constructable< T >::value )
    {
        throw exception("Non-copy-constructable type");
    }
    if( !std::is_convertible< U, T >:: value )
    {
        throw exception("Non-convertable input type");
    } /**/
    for( unsigned int i = 0; i < M; ++i )
    {
        for( unsigned int j = 0; j < N; ++j )
        {
            m_aaData[i][j]( ( i < ac_uiRows && j < ac_uiColumns )
                            ? (T)(ac_cpcpData[i][j]) : ac_rFill );
        }
    }
}
template< typename T, unsigned int M, unsigned int N >
template< typename U, unsigned int t_uiRows, unsigned int t_uiColumns >
inline MatrixBase< T, M, N >::
    MatrixBase( const U (&ac_raaData)[ t_uiRows ][ t_uiColumns ],
                const T& ac_rFill )
    : MatrixBase( ac_raaData, t_uiRows, t_uiColumns, ac_rFill ) {}

// Assign parameter data where given
template< typename T, unsigned int M, unsigned int N >
template< typename U, unsigned int t_uiRows, unsigned int t_uiColumns >
inline MatrixBase< T, M, N >& MatrixBase< T, M, N >::
    Assign( const U (&ac_raaData)[ t_uiRows ][ t_uiColumns ] )
{/*
    if( !std::is_copy_assignable< T >::value )
    {
        throw exception("Non-copy-assignable type");
    }
    if( !std::is_convertible< U, T >:: value )
    {
        throw exception("Non-convertable input type");
    } /**/
    for( unsigned int i = 0 && i < t_uiRows; i < M; ++i )
    {
        for( unsigned int j = 0 && j < t_uiColumns; j < N; ++j )
        {
            m_aaData[i][j] = (T)(ac_raaData[i][j]);
        }
    }
}
template< typename T, unsigned int M, unsigned int N >
template< typename U, unsigned int t_uiRows, unsigned int t_uiColumns >
inline MatrixBase< T, M, N >& MatrixBase< T, M, N >::
    operator=( const U (&ac_raaData)[ t_uiRows ][ t_uiColumns ] )
{
    Assign( ac_raaData );
}

}   // namespace Math

#endif  // _MATRIX_BASE_FILL_CONSTRUCTORS_INL_
