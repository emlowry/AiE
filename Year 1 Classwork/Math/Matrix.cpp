/******************************************************************************
 * File:               Matrix.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       November 18, 2013
 * Description:        Explicit instantiation of Matrix types - these classes
 *                      will be compiled as part of the library, so users can
 *                      use them without having to include the template inline
 *                      function implementations themselves.
 * Last Modified:      November 18, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#include "T_Matrix.h"

namespace Math
{

#define MATRIX_TYPE( T ) template class Matrix< T, 1, 1 >; \
                         template class Matrix< T, 1, 2 >; \
                         template class Matrix< T, 1, 3 >; \
                         template class Matrix< T, 1, 4 >; \
                         template class Matrix< T, 2, 1 >; \
                         template class Matrix< T, 2, 2 >; \
                         template class Matrix< T, 2, 3 >; \
                         template class Matrix< T, 2, 4 >; \
                         template class Matrix< T, 3, 1 >; \
                         template class Matrix< T, 3, 2 >; \
                         template class Matrix< T, 3, 3 >; \
                         template class Matrix< T, 3, 4 >; \
                         template class Matrix< T, 4, 1 >; \
                         template class Matrix< T, 4, 2 >; \
                         template class Matrix< T, 4, 3 >; \
                         template class Matrix< T, 4, 4 >; \

#define MATRIX_MULTIPLY( T, M, N ) template Matrix< T, M, 2 > Matrix< T, M, N >:: \
                                    operator*< 2 >( const Matrix< T, N, 2 >& ac_roMatrix ) const; \
                                   template Matrix< T, M, 3 > Matrix< T, M, N >:: \
                                    operator*< 3 >( const Matrix< T, N, 3 >& ac_roMatrix ) const; \
                                   template Matrix< T, M, 4 > Matrix< T, M, N >:: \
                                    operator*< 4 >( const Matrix< T, N, 4 >& ac_roMatrix ) const; \
                                   template Matrix< typename MatrixInverse< T >::Type, M, 2 > Matrix< T, M, N >:: \
                                    operator/< 2 >( const Matrix< T, 2, N >& ac_roMatrix ) const; \
                                   template Matrix< typename MatrixInverse< T >::Type, M, 3 > Matrix< T, M, N >:: \
                                    operator/< 3 >( const Matrix< T, 3, N >& ac_roMatrix ) const; \
                                   template Matrix< typename MatrixInverse< T >::Type, M, 4 > Matrix< T, M, N >:: \
                                    operator/< 4 >( const Matrix< T, 4, N >& ac_roMatrix ) const;

#undef MATRIX_TYPE

#define MATRIX_CONVERSION( T, U ) template Matrix< T, 1, 1 >::Matrix< U
// TODO

}   // namespace Math
