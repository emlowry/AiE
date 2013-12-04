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
inline MatrixBase< T, M, N >::MatrixBase( const T& ac_rFill )
{/*
    if( !std::is_copy_constructable< T >::value )
    {
        throw exception("Non-copy-constructable type");
    } /**/
    for( unsigned int i = 0; i < M*N; ++i )
    {
        m_aaData[i/N][i%N]( ac_rFill );
    }
}

// Assign all elements to the given value
template< typename T, unsigned int M, unsigned int N >
inline MatrixBase< T, M, N >& MatrixBase< T, M, N >::Assign( const T& ac_rFill )
{/*
    if( !std::is_copy_assignable< T >::value )
    {
        throw exception("Non-copy-assignable type");
    } /**/
    for( unsigned int i = 0; i < M*N; ++i )
    {
        m_aaData[i/N][i%N] = ac_rFill;
    }
}
template< typename T, unsigned int M, unsigned int N >
inline MatrixBase< T, M, N >& MatrixBase< T, M, N >::
    operator=( const T& ac_rFill )
{
    Assign( ac_rFill );
}

// Construct with parameter data one row at a time until end of parameter data,
// then filled with given fill value
template< typename T, unsigned int M, unsigned int N >
inline MatrixBase< T, M, N >::MatrixBase( const T* const ac_cpData,
                                          const unsigned int ac_uiSize,
                                          const T& ac_rFill )
{/*
    if( !std::is_copy_constructable< T >::value )
    {
        throw exception("Non-copy-constructable type");
    } /**/
    for( unsigned int i = 0; i < M*N; ++i )
    {
        m_aaData[i/N][i%N]( ( i < ac_uiSize ) ? ac_cpData[i] : ac_rFill );
    }
}
template< typename T, unsigned int M, unsigned int N >
inline MatrixBase< T, M, N >::MatrixBase( const T (&ac_raData)[ M*N ] )
    : MatrixBase( ac_roData, M*N, DEFAULT_FILL ) {}

// Assign parameter data one row at a time until end of parameter data
template< typename T, unsigned int M, unsigned int N >
inline MatrixBase< T, M, N >& MatrixBase< T, M, N >::
    Assign( const T (&ac_raData)[ M*N ] )
{/*
    if( !std::is_copy_assignable< T >::value )
    {
        throw exception("Non-copy-assignable type");
    } /**/
    for( unsigned int i = 0; i < M*N; ++i )
    {
        m_aaData[i/N][i%N] = ac_raData[i];
    }
}
template< typename T, unsigned int M, unsigned int N >
inline MatrixBase< T, M, N >& MatrixBase< T, M, N >::
    operator=( const T (&ac_raData)[ M*N ] )
{
    Assign( ac_raData );
}

// Construct with parameter data where given and fill data elsewhere
template< typename T, unsigned int M, unsigned int N >
inline MatrixBase< T, M, N >::MatrixBase( const T* const* const ac_cpcpData,
                                          const unsigned int ac_uiRows,
                                          const unsigned int ac_uiColumns,
                                          const T& ac_rFill )
{/*
    if( !std::is_copy_constructable< T >::value )
    {
        throw exception("Non-copy-constructable type");
    } /**/
    for( unsigned int i = 0; i < M; ++i )
    {
        for( unsigned int j = 0; j < N; ++j )
        {
            m_aaData[i][j]( ( i < ac_uiRows && j < ac_uiColumns )
                            ? ac_cpcpData[i][j] : ac_rFill );
        }
    }
}
template< typename T, unsigned int M, unsigned int N >
inline MatrixBase< T, M, N >::
    MatrixBase( const T (&ac_raaData)[ M ][ N ] )
    : MatrixBase( ac_raaData, M, N, DEFAULT_FILL ) {}

// Assign parameter data where given
template< typename T, unsigned int M, unsigned int N >
inline MatrixBase< T, M, N >& MatrixBase< T, M, N >::
    Assign( const T (&ac_raaData)[ M ][ N ] )
{/*
    if( !std::is_copy_assignable< T >::value )
    {
        throw exception("Non-copy-assignable type");
    } /**/
    for( unsigned int i = 0; i < M; ++i )
    {
        for( unsigned int j = 0; j < N; ++j )
        {
            m_aaData[i][j] = ac_raaData[i][j];
        }
    }
}
template< typename T, unsigned int M, unsigned int N >
inline MatrixBase< T, M, N >& MatrixBase< T, M, N >::
    operator=( const T (&ac_raaData)[ M ][ N ] )
{
    Assign( ac_raaData );
}

// Construct/assign from a set of columns
template< typename T, unsigned int M, unsigned int N >
inline MatrixBase< T, M, N >::
    MatrixBase( const ColumnVectorType (&ac_raoColumns)[ N ] )
{/*
    if( !std::is_copy_constructable< T >::value )
    {
        throw exception("Non-copy-constructable type");
    } /**/
    for( unsigned int i = 0; i < M; ++i )
    {
        for( unsigned int j = 0; j < N; ++j )
        {
            m_aaData[i][j]( ac_raoColumns[j][i] );
        }
    }
}
template< typename T, unsigned int M, unsigned int N >
inline MatrixBase< T, M, N >& MatrixBase< T, M, N >::
    Assign( const ColumnVectorType (&ac_raoColumns)[ N ] )
{/*
    if( !std::is_copy_assignable< T >::value )
    {
        throw exception("Non-copy-assignable type");
    } /**/
    for( unsigned int i = 0; i < M; ++i )
    {
        for( unsigned int j = 0; j < N; ++j )
        {
            m_aaData[i][j] = ac_raoColumns[j][i];
        }
    }
}
template< typename T, unsigned int M, unsigned int N >
inline MatrixBase< T, M, N >& MatrixBase< T, M, N >::
    operator=( const ColumnVectorType (&ac_raoColumns)[ N ] )
{
    return Assign( ac_raoColumns );
}
template< typename T, unsigned int M, unsigned int N >
inline MatrixBase< T, M, N >::
    MatrixBase( const ColumnVectorType* const (&ac_racpoColumns)[ N ] )
{/*
    if( !std::is_copy_constructable< T >::value )
    {
        throw exception("Non-copy-constructable type");
    } /**/
    for( unsigned int i = 0; i < M; ++i )
    {
        for( unsigned int j = 0; j < N; ++j )
        {
            const ColumnVectorType* const cpcoColumn = ac_racpoColumns[j];
            m_aaData[i][j]( nullptr == cpcoColumn ? DEFAULT_FILL
                                                  : (*cpcoColumn)[i] );
        }
    }
}
template< typename T, unsigned int M, unsigned int N >
inline MatrixBase< T, M, N >& MatrixBase< T, M, N >::
    Assign( const ColumnVectorType* const (&ac_racpoColumns)[ N ] )
{/*
    if( !std::is_copy_assignable< T >::value )
    {
        throw exception("Non-copy-assignable type");
    } /**/
    for( unsigned int i = 0; i < M; ++i )
    {
        for( unsigned int j = 0; j < N; ++j )
        {
            const ColumnVectorType* const cpcoColumn = ac_racpoColumns[j];
            if( nullptr != cpcoColumn )
            {
                m_aaData[i][j] = (*cpcoColumn)[i] ;
            }
        }
    }
}
template< typename T, unsigned int M, unsigned int N >
inline MatrixBase< T, M, N >& MatrixBase< T, M, N >::
    operator=( const ColumnVectorType* const (&ac_racpoColumns)[ N ] )
{
    return Assign( ac_racpoColumns );
}

// Construct/assign from a set of rows
template< typename T, unsigned int M, unsigned int N >
inline MatrixBase< T, M, N >::
    MatrixBase( const RowVectorType (&ac_raoRows)[ M ] )
{/*
    if( !std::is_copy_constructable< T >::value )
    {
        throw exception("Non-copy-constructable type");
    } /**/
    for( unsigned int i = 0; i < M; ++i )
    {
        for( unsigned int j = 0; j < N; ++j )
        {
            m_aaData[i][j]( ac_raoRows[i][j] );
        }
    }
}
template< typename T, unsigned int M, unsigned int N >
inline MatrixBase< T, M, N >& MatrixBase< T, M, N >::
    Assign( const RowVectorType (&ac_raoRows)[ M ] )
{/*
    if( !std::is_copy_assignable< T >::value )
    {
        throw exception("Non-copy-assignable type");
    } /**/
    for( unsigned int i = 0; i < M; ++i )
    {
        for( unsigned int j = 0; j < N; ++j )
        {
            m_aaData[i][j] = ac_raoRows[i][j];
        }
    }
}
template< typename T, unsigned int M, unsigned int N >
inline MatrixBase< T, M, N >& MatrixBase< T, M, N >::
    operator=( const RowVectorType (&ac_raoRows)[ M ] )
{
    return Assign( ac_raoRows );
}
template< typename T, unsigned int M, unsigned int N >
inline MatrixBase< T, M, N >::
    MatrixBase( const RowVectorType* const (&ac_racpoRows)[ M ] )
{/*
    if( !std::is_copy_constructable< T >::value )
    {
        throw exception("Non-copy-constructable type");
    } /**/
    for( unsigned int i = 0; i < M; ++i )
    {
        for( unsigned int j = 0; j < N; ++j )
        {
            const RowVectorType* const cpcoRow = ac_racpoRows[i];
            m_aaData[i][j]( nullptr == cpcoRow ? DEFAULT_FILL : (*cpcoRow)[j] );
        }
    }
}
template< typename T, unsigned int M, unsigned int N >
inline MatrixBase< T, M, N >& MatrixBase< T, M, N >::
    Assign( const RowVectorType* const (&ac_racpoRows)[ M ] )
{/*
    if( !std::is_copy_assignable< T >::value )
    {
        throw exception("Non-copy-assignable type");
    } /**/
    for( unsigned int i = 0; i < M; ++i )
    {
        for( unsigned int j = 0; j < N; ++j )
        {
            const RowVectorType* const cpcoRow = ac_racpoRows[i];
            if( nullptr != cpcoRow )
            {
                m_aaData[i][j] = (*cpcoRow)[j] ;
            }
        }
    }
}
template< typename T, unsigned int M, unsigned int N >
inline MatrixBase< T, M, N >& MatrixBase< T, M, N >::
    operator=( const RowVectorType* const (&ac_racpoRows)[ M ] )
{
    return Assign( ac_racpoRows );
}

}   // namespace Math

#endif  // _MATRIX_BASE_FILL_CONSTRUCTORS_INL_
