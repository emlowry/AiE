/******************************************************************************
 * File:               MatrixBase.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       December 9, 2013
 * Description:        Explicit instantiation of MatrixBase types - these
 *                      classes will be compiled as part of the library, so
 *                      users can use them without having to include the
 *                      template inline function implementations themselves.
 * Last Modified:      December 9, 2013
 * Last Modification:  Finished writing and using macros.
 ******************************************************************************/

#include "T_MatrixBase.h"
#include <string>

namespace Math
{

#define MATRIX_TYPE( T ) \
template struct MatrixFill< T >; \
template class MatrixBase< T, 0, 0 >; \
template class MatrixBase< T, 0, 1 >; \
template class MatrixBase< T, 0, 2 >; \
template class MatrixBase< T, 0, 3 >; \
template class MatrixBase< T, 0, 4 >; \
template class MatrixBase< T, 1, 0 >; \
template class MatrixBase< T, 1, 1 >; \
template class MatrixBase< T, 1, 2 >; \
template class MatrixBase< T, 1, 3 >; \
template class MatrixBase< T, 1, 4 >; \
template class MatrixBase< T, 2, 0 >; \
template class MatrixBase< T, 2, 1 >; \
template class MatrixBase< T, 2, 2 >; \
template class MatrixBase< T, 2, 3 >; \
template class MatrixBase< T, 2, 4 >; \
template class MatrixBase< T, 3, 0 >; \
template class MatrixBase< T, 3, 1 >; \
template class MatrixBase< T, 3, 2 >; \
template class MatrixBase< T, 3, 3 >; \
template class MatrixBase< T, 3, 4 >; \
template class MatrixBase< T, 4, 0 >; \
template class MatrixBase< T, 4, 1 >; \
template class MatrixBase< T, 4, 2 >; \
template class MatrixBase< T, 4, 3 >; \
template class MatrixBase< T, 4, 4 >;
    
MATRIX_TYPE( char )
MATRIX_TYPE( signed char )
MATRIX_TYPE( unsigned char )
MATRIX_TYPE( short )
MATRIX_TYPE( unsigned short )
MATRIX_TYPE( int )
MATRIX_TYPE( unsigned int )
MATRIX_TYPE( long )
MATRIX_TYPE( unsigned long )
MATRIX_TYPE( long long )
MATRIX_TYPE( unsigned long long )
MATRIX_TYPE( float )
MATRIX_TYPE( double )
MATRIX_TYPE( long double )
MATRIX_TYPE( bool )
MATRIX_TYPE( void* )
MATRIX_TYPE( const void* )
MATRIX_TYPE( char* )
MATRIX_TYPE( const char* )
MATRIX_TYPE( std::string )

#undef MATRIX_TYPE

#define MATRIX_TYPE_CONVERSION( T, U ) \
template MatrixBase< T, 0, 0 >:: \
    MatrixBase< U >( const MatrixBase< U, 0, 0 >& ac_roMatrix ); \
template MatrixBase< T, 0, 1 >:: \
    MatrixBase< U >( const MatrixBase< U, 0, 1 >& ac_roMatrix ); \
template MatrixBase< T, 0, 2 >:: \
    MatrixBase< U >( const MatrixBase< U, 0, 2 >& ac_roMatrix ); \
template MatrixBase< T, 0, 3 >:: \
    MatrixBase< U >( const MatrixBase< U, 0, 3 >& ac_roMatrix ); \
template MatrixBase< T, 0, 4 >:: \
    MatrixBase< U >( const MatrixBase< U, 0, 4 >& ac_roMatrix ); \
template MatrixBase< T, 1, 0 >:: \
    MatrixBase< U >( const MatrixBase< U, 1, 0 >& ac_roMatrix ); \
template MatrixBase< T, 1, 1 >:: \
    MatrixBase< U >( const MatrixBase< U, 1, 1 >& ac_roMatrix ); \
template MatrixBase< T, 1, 2 >:: \
    MatrixBase< U >( const MatrixBase< U, 1, 2 >& ac_roMatrix ); \
template MatrixBase< T, 1, 3 >:: \
    MatrixBase< U >( const MatrixBase< U, 1, 3 >& ac_roMatrix ); \
template MatrixBase< T, 1, 4 >:: \
    MatrixBase< U >( const MatrixBase< U, 1, 4 >& ac_roMatrix ); \
template MatrixBase< T, 2, 0 >:: \
    MatrixBase< U >( const MatrixBase< U, 2, 0 >& ac_roMatrix ); \
template MatrixBase< T, 2, 1 >:: \
    MatrixBase< U >( const MatrixBase< U, 2, 1 >& ac_roMatrix ); \
template MatrixBase< T, 2, 2 >:: \
    MatrixBase< U >( const MatrixBase< U, 2, 2 >& ac_roMatrix ); \
template MatrixBase< T, 2, 3 >:: \
    MatrixBase< U >( const MatrixBase< U, 2, 3 >& ac_roMatrix ); \
template MatrixBase< T, 2, 4 >:: \
    MatrixBase< U >( const MatrixBase< U, 2, 4 >& ac_roMatrix ); \
template MatrixBase< T, 3, 0 >:: \
    MatrixBase< U >( const MatrixBase< U, 3, 0 >& ac_roMatrix ); \
template MatrixBase< T, 3, 1 >:: \
    MatrixBase< U >( const MatrixBase< U, 3, 1 >& ac_roMatrix ); \
template MatrixBase< T, 3, 2 >:: \
    MatrixBase< U >( const MatrixBase< U, 3, 2 >& ac_roMatrix ); \
template MatrixBase< T, 3, 3 >:: \
    MatrixBase< U >( const MatrixBase< U, 3, 3 >& ac_roMatrix ); \
template MatrixBase< T, 3, 4 >:: \
    MatrixBase< U >( const MatrixBase< U, 3, 4 >& ac_roMatrix ); \
template MatrixBase< T, 4, 0 >:: \
    MatrixBase< U >( const MatrixBase< U, 4, 0 >& ac_roMatrix ); \
template MatrixBase< T, 4, 1 >:: \
    MatrixBase< U >( const MatrixBase< U, 4, 1 >& ac_roMatrix ); \
template MatrixBase< T, 4, 2 >:: \
    MatrixBase< U >( const MatrixBase< U, 4, 2 >& ac_roMatrix ); \
template MatrixBase< T, 4, 3 >:: \
    MatrixBase< U >( const MatrixBase< U, 4, 3 >& ac_roMatrix ); \
template MatrixBase< T, 4, 4 >:: \
    MatrixBase< U >( const MatrixBase< U, 4, 4 >& ac_roMatrix ); \
template MatrixBase< T, 0, 0 >& MatrixBase< T, 0, 0 >:: \
    Assign< U >( const MatrixBase< U, 0, 0 >& ac_roMatrix ); \
template MatrixBase< T, 0, 1 >& MatrixBase< T, 0, 1 >:: \
    Assign< U >( const MatrixBase< U, 0, 1 >& ac_roMatrix ); \
template MatrixBase< T, 0, 2 >& MatrixBase< T, 0, 2 >:: \
    Assign< U >( const MatrixBase< U, 0, 2 >& ac_roMatrix ); \
template MatrixBase< T, 0, 3 >& MatrixBase< T, 0, 3 >:: \
    Assign< U >( const MatrixBase< U, 0, 3 >& ac_roMatrix ); \
template MatrixBase< T, 0, 4 >& MatrixBase< T, 0, 4 >:: \
    Assign< U >( const MatrixBase< U, 0, 4 >& ac_roMatrix ); \
template MatrixBase< T, 1, 0 >& MatrixBase< T, 1, 0 >:: \
    Assign< U >( const MatrixBase< U, 1, 0 >& ac_roMatrix ); \
template MatrixBase< T, 1, 1 >& MatrixBase< T, 1, 1 >:: \
    Assign< U >( const MatrixBase< U, 1, 1 >& ac_roMatrix ); \
template MatrixBase< T, 1, 2 >& MatrixBase< T, 1, 2 >:: \
    Assign< U >( const MatrixBase< U, 1, 2 >& ac_roMatrix ); \
template MatrixBase< T, 1, 3 >& MatrixBase< T, 1, 3 >:: \
    Assign< U >( const MatrixBase< U, 1, 3 >& ac_roMatrix ); \
template MatrixBase< T, 1, 4 >& MatrixBase< T, 1, 4 >:: \
    Assign< U >( const MatrixBase< U, 1, 4 >& ac_roMatrix ); \
template MatrixBase< T, 2, 0 >& MatrixBase< T, 2, 0 >:: \
    Assign< U >( const MatrixBase< U, 2, 0 >& ac_roMatrix ); \
template MatrixBase< T, 2, 1 >& MatrixBase< T, 2, 1 >:: \
    Assign< U >( const MatrixBase< U, 2, 1 >& ac_roMatrix ); \
template MatrixBase< T, 2, 2 >& MatrixBase< T, 2, 2 >:: \
    Assign< U >( const MatrixBase< U, 2, 2 >& ac_roMatrix ); \
template MatrixBase< T, 2, 3 >& MatrixBase< T, 2, 3 >:: \
    Assign< U >( const MatrixBase< U, 2, 3 >& ac_roMatrix ); \
template MatrixBase< T, 2, 4 >& MatrixBase< T, 2, 4 >:: \
    Assign< U >( const MatrixBase< U, 2, 4 >& ac_roMatrix ); \
template MatrixBase< T, 3, 0 >& MatrixBase< T, 3, 0 >:: \
    Assign< U >( const MatrixBase< U, 3, 0 >& ac_roMatrix ); \
template MatrixBase< T, 3, 1 >& MatrixBase< T, 3, 1 >:: \
    Assign< U >( const MatrixBase< U, 3, 1 >& ac_roMatrix ); \
template MatrixBase< T, 3, 2 >& MatrixBase< T, 3, 2 >:: \
    Assign< U >( const MatrixBase< U, 3, 2 >& ac_roMatrix ); \
template MatrixBase< T, 3, 3 >& MatrixBase< T, 3, 3 >:: \
    Assign< U >( const MatrixBase< U, 3, 3 >& ac_roMatrix ); \
template MatrixBase< T, 3, 4 >& MatrixBase< T, 3, 4 >:: \
    Assign< U >( const MatrixBase< U, 3, 4 >& ac_roMatrix ); \
template MatrixBase< T, 4, 0 >& MatrixBase< T, 4, 0 >:: \
    Assign< U >( const MatrixBase< U, 4, 0 >& ac_roMatrix ); \
template MatrixBase< T, 4, 1 >& MatrixBase< T, 4, 1 >:: \
    Assign< U >( const MatrixBase< U, 4, 1 >& ac_roMatrix ); \
template MatrixBase< T, 4, 2 >& MatrixBase< T, 4, 2 >:: \
    Assign< U >( const MatrixBase< U, 4, 2 >& ac_roMatrix ); \
template MatrixBase< T, 4, 3 >& MatrixBase< T, 4, 3 >:: \
    Assign< U >( const MatrixBase< U, 4, 3 >& ac_roMatrix ); \
template MatrixBase< T, 4, 4 >& MatrixBase< T, 4, 4 >:: \
    Assign< U >( const MatrixBase< U, 4, 4 >& ac_roMatrix ); \
template MatrixBase< T, 0, 0 >& MatrixBase< T, 0, 0 >:: \
    operator=< U >( const MatrixBase< U, 0, 0 >& ac_roMatrix ); \
template MatrixBase< T, 0, 1 >& MatrixBase< T, 0, 1 >:: \
    operator=< U >( const MatrixBase< U, 0, 1 >& ac_roMatrix ); \
template MatrixBase< T, 0, 2 >& MatrixBase< T, 0, 2 >:: \
    operator=< U >( const MatrixBase< U, 0, 2 >& ac_roMatrix ); \
template MatrixBase< T, 0, 3 >& MatrixBase< T, 0, 3 >:: \
    operator=< U >( const MatrixBase< U, 0, 3 >& ac_roMatrix ); \
template MatrixBase< T, 0, 4 >& MatrixBase< T, 0, 4 >:: \
    operator=< U >( const MatrixBase< U, 0, 4 >& ac_roMatrix ); \
template MatrixBase< T, 1, 0 >& MatrixBase< T, 1, 0 >:: \
    operator=< U >( const MatrixBase< U, 1, 0 >& ac_roMatrix ); \
template MatrixBase< T, 1, 1 >& MatrixBase< T, 1, 1 >:: \
    operator=< U >( const MatrixBase< U, 1, 1 >& ac_roMatrix ); \
template MatrixBase< T, 1, 2 >& MatrixBase< T, 1, 2 >:: \
    operator=< U >( const MatrixBase< U, 1, 2 >& ac_roMatrix ); \
template MatrixBase< T, 1, 3 >& MatrixBase< T, 1, 3 >:: \
    operator=< U >( const MatrixBase< U, 1, 3 >& ac_roMatrix ); \
template MatrixBase< T, 1, 4 >& MatrixBase< T, 1, 4 >:: \
    operator=< U >( const MatrixBase< U, 1, 4 >& ac_roMatrix ); \
template MatrixBase< T, 2, 0 >& MatrixBase< T, 2, 0 >:: \
    operator=< U >( const MatrixBase< U, 2, 0 >& ac_roMatrix ); \
template MatrixBase< T, 2, 1 >& MatrixBase< T, 2, 1 >:: \
    operator=< U >( const MatrixBase< U, 2, 1 >& ac_roMatrix ); \
template MatrixBase< T, 2, 2 >& MatrixBase< T, 2, 2 >:: \
    operator=< U >( const MatrixBase< U, 2, 2 >& ac_roMatrix ); \
template MatrixBase< T, 2, 3 >& MatrixBase< T, 2, 3 >:: \
    operator=< U >( const MatrixBase< U, 2, 3 >& ac_roMatrix ); \
template MatrixBase< T, 2, 4 >& MatrixBase< T, 2, 4 >:: \
    operator=< U >( const MatrixBase< U, 2, 4 >& ac_roMatrix ); \
template MatrixBase< T, 3, 0 >& MatrixBase< T, 3, 0 >:: \
    operator=< U >( const MatrixBase< U, 3, 0 >& ac_roMatrix ); \
template MatrixBase< T, 3, 1 >& MatrixBase< T, 3, 1 >:: \
    operator=< U >( const MatrixBase< U, 3, 1 >& ac_roMatrix ); \
template MatrixBase< T, 3, 2 >& MatrixBase< T, 3, 2 >:: \
    operator=< U >( const MatrixBase< U, 3, 2 >& ac_roMatrix ); \
template MatrixBase< T, 3, 3 >& MatrixBase< T, 3, 3 >:: \
    operator=< U >( const MatrixBase< U, 3, 3 >& ac_roMatrix ); \
template MatrixBase< T, 3, 4 >& MatrixBase< T, 3, 4 >:: \
    operator=< U >( const MatrixBase< U, 3, 4 >& ac_roMatrix ); \
template MatrixBase< T, 4, 0 >& MatrixBase< T, 4, 0 >:: \
    operator=< U >( const MatrixBase< U, 4, 0 >& ac_roMatrix ); \
template MatrixBase< T, 4, 1 >& MatrixBase< T, 4, 1 >:: \
    operator=< U >( const MatrixBase< U, 4, 1 >& ac_roMatrix ); \
template MatrixBase< T, 4, 2 >& MatrixBase< T, 4, 2 >:: \
    operator=< U >( const MatrixBase< U, 4, 2 >& ac_roMatrix ); \
template MatrixBase< T, 4, 3 >& MatrixBase< T, 4, 3 >:: \
    operator=< U >( const MatrixBase< U, 4, 3 >& ac_roMatrix ); \
template MatrixBase< T, 4, 4 >& MatrixBase< T, 4, 4 >:: \
    operator=< U >( const MatrixBase< U, 4, 4 >& ac_roMatrix );

MATRIX_TYPE_CONVERSION( char, signed char )
MATRIX_TYPE_CONVERSION( char, unsigned char )
MATRIX_TYPE_CONVERSION( char, short )
MATRIX_TYPE_CONVERSION( char, unsigned short )
MATRIX_TYPE_CONVERSION( char, int )
MATRIX_TYPE_CONVERSION( char, unsigned int )
MATRIX_TYPE_CONVERSION( char, long )
MATRIX_TYPE_CONVERSION( char, unsigned long )
MATRIX_TYPE_CONVERSION( char, long long )
MATRIX_TYPE_CONVERSION( char, unsigned long long )
MATRIX_TYPE_CONVERSION( char, float )
MATRIX_TYPE_CONVERSION( char, double )
MATRIX_TYPE_CONVERSION( char, long double )
MATRIX_TYPE_CONVERSION( char, bool )
MATRIX_TYPE_CONVERSION( char, void* )
MATRIX_TYPE_CONVERSION( char, const void* )
MATRIX_TYPE_CONVERSION( char, char* )
MATRIX_TYPE_CONVERSION( char, const char* )

MATRIX_TYPE_CONVERSION( signed char, char )
MATRIX_TYPE_CONVERSION( signed char, unsigned char )
MATRIX_TYPE_CONVERSION( signed char, short )
MATRIX_TYPE_CONVERSION( signed char, unsigned short )
MATRIX_TYPE_CONVERSION( signed char, int )
MATRIX_TYPE_CONVERSION( signed char, unsigned int )
MATRIX_TYPE_CONVERSION( signed char, long )
MATRIX_TYPE_CONVERSION( signed char, unsigned long )
MATRIX_TYPE_CONVERSION( signed char, long long )
MATRIX_TYPE_CONVERSION( signed char, unsigned long long )
MATRIX_TYPE_CONVERSION( signed char, float )
MATRIX_TYPE_CONVERSION( signed char, double )
MATRIX_TYPE_CONVERSION( signed char, long double )
MATRIX_TYPE_CONVERSION( signed char, bool )
MATRIX_TYPE_CONVERSION( signed char, void* )
MATRIX_TYPE_CONVERSION( signed char, const void* )
MATRIX_TYPE_CONVERSION( signed char, char* )
MATRIX_TYPE_CONVERSION( signed char, const char* )

MATRIX_TYPE_CONVERSION( unsigned char, char )
MATRIX_TYPE_CONVERSION( unsigned char, signed char )
MATRIX_TYPE_CONVERSION( unsigned char, short )
MATRIX_TYPE_CONVERSION( unsigned char, unsigned short )
MATRIX_TYPE_CONVERSION( unsigned char, int )
MATRIX_TYPE_CONVERSION( unsigned char, unsigned int )
MATRIX_TYPE_CONVERSION( unsigned char, long )
MATRIX_TYPE_CONVERSION( unsigned char, unsigned long )
MATRIX_TYPE_CONVERSION( unsigned char, long long )
MATRIX_TYPE_CONVERSION( unsigned char, unsigned long long )
MATRIX_TYPE_CONVERSION( unsigned char, float )
MATRIX_TYPE_CONVERSION( unsigned char, double )
MATRIX_TYPE_CONVERSION( unsigned char, long double )
MATRIX_TYPE_CONVERSION( unsigned char, bool )
MATRIX_TYPE_CONVERSION( unsigned char, void* )
MATRIX_TYPE_CONVERSION( unsigned char, const void* )
MATRIX_TYPE_CONVERSION( unsigned char, char* )
MATRIX_TYPE_CONVERSION( unsigned char, const char* )

MATRIX_TYPE_CONVERSION( short, char )
MATRIX_TYPE_CONVERSION( short, signed char )
MATRIX_TYPE_CONVERSION( short, unsigned char )
MATRIX_TYPE_CONVERSION( short, unsigned short )
MATRIX_TYPE_CONVERSION( short, int )
MATRIX_TYPE_CONVERSION( short, unsigned int )
MATRIX_TYPE_CONVERSION( short, long )
MATRIX_TYPE_CONVERSION( short, unsigned long )
MATRIX_TYPE_CONVERSION( short, long long )
MATRIX_TYPE_CONVERSION( short, unsigned long long )
MATRIX_TYPE_CONVERSION( short, float )
MATRIX_TYPE_CONVERSION( short, double )
MATRIX_TYPE_CONVERSION( short, long double )
MATRIX_TYPE_CONVERSION( short, bool )
MATRIX_TYPE_CONVERSION( short, void* )
MATRIX_TYPE_CONVERSION( short, const void* )
MATRIX_TYPE_CONVERSION( short, char* )
MATRIX_TYPE_CONVERSION( short, const char* )

MATRIX_TYPE_CONVERSION( unsigned short, char )
MATRIX_TYPE_CONVERSION( unsigned short, signed char )
MATRIX_TYPE_CONVERSION( unsigned short, unsigned char )
MATRIX_TYPE_CONVERSION( unsigned short, short )
MATRIX_TYPE_CONVERSION( unsigned short, int )
MATRIX_TYPE_CONVERSION( unsigned short, unsigned int )
MATRIX_TYPE_CONVERSION( unsigned short, long )
MATRIX_TYPE_CONVERSION( unsigned short, unsigned long )
MATRIX_TYPE_CONVERSION( unsigned short, long long )
MATRIX_TYPE_CONVERSION( unsigned short, unsigned long long )
MATRIX_TYPE_CONVERSION( unsigned short, float )
MATRIX_TYPE_CONVERSION( unsigned short, double )
MATRIX_TYPE_CONVERSION( unsigned short, long double )
MATRIX_TYPE_CONVERSION( unsigned short, bool )
MATRIX_TYPE_CONVERSION( unsigned short, void* )
MATRIX_TYPE_CONVERSION( unsigned short, const void* )
MATRIX_TYPE_CONVERSION( unsigned short, char* )
MATRIX_TYPE_CONVERSION( unsigned short, const char* )

MATRIX_TYPE_CONVERSION( int, char )
MATRIX_TYPE_CONVERSION( int, signed char )
MATRIX_TYPE_CONVERSION( int, unsigned char )
MATRIX_TYPE_CONVERSION( int, short )
MATRIX_TYPE_CONVERSION( int, unsigned short )
MATRIX_TYPE_CONVERSION( int, unsigned int )
MATRIX_TYPE_CONVERSION( int, long )
MATRIX_TYPE_CONVERSION( int, unsigned long )
MATRIX_TYPE_CONVERSION( int, long long )
MATRIX_TYPE_CONVERSION( int, unsigned long long )
MATRIX_TYPE_CONVERSION( int, float )
MATRIX_TYPE_CONVERSION( int, double )
MATRIX_TYPE_CONVERSION( int, long double )
MATRIX_TYPE_CONVERSION( int, bool )
MATRIX_TYPE_CONVERSION( int, void* )
MATRIX_TYPE_CONVERSION( int, const void* )
MATRIX_TYPE_CONVERSION( int, char* )
MATRIX_TYPE_CONVERSION( int, const char* )

MATRIX_TYPE_CONVERSION( unsigned int, char )
MATRIX_TYPE_CONVERSION( unsigned int, signed char )
MATRIX_TYPE_CONVERSION( unsigned int, unsigned char )
MATRIX_TYPE_CONVERSION( unsigned int, short )
MATRIX_TYPE_CONVERSION( unsigned int, unsigned short )
MATRIX_TYPE_CONVERSION( unsigned int, int )
MATRIX_TYPE_CONVERSION( unsigned int, long )
MATRIX_TYPE_CONVERSION( unsigned int, unsigned long )
MATRIX_TYPE_CONVERSION( unsigned int, long long )
MATRIX_TYPE_CONVERSION( unsigned int, unsigned long long )
MATRIX_TYPE_CONVERSION( unsigned int, float )
MATRIX_TYPE_CONVERSION( unsigned int, double )
MATRIX_TYPE_CONVERSION( unsigned int, long double )
MATRIX_TYPE_CONVERSION( unsigned int, bool )
MATRIX_TYPE_CONVERSION( unsigned int, void* )
MATRIX_TYPE_CONVERSION( unsigned int, const void* )
MATRIX_TYPE_CONVERSION( unsigned int, char* )
MATRIX_TYPE_CONVERSION( unsigned int, const char* )

MATRIX_TYPE_CONVERSION( long, char )
MATRIX_TYPE_CONVERSION( long, signed char )
MATRIX_TYPE_CONVERSION( long, unsigned char )
MATRIX_TYPE_CONVERSION( long, short )
MATRIX_TYPE_CONVERSION( long, unsigned short )
MATRIX_TYPE_CONVERSION( long, int )
MATRIX_TYPE_CONVERSION( long, unsigned int )
MATRIX_TYPE_CONVERSION( long, unsigned long )
MATRIX_TYPE_CONVERSION( long, long long )
MATRIX_TYPE_CONVERSION( long, unsigned long long )
MATRIX_TYPE_CONVERSION( long, float )
MATRIX_TYPE_CONVERSION( long, double )
MATRIX_TYPE_CONVERSION( long, long double )
MATRIX_TYPE_CONVERSION( long, bool )
MATRIX_TYPE_CONVERSION( long, void* )
MATRIX_TYPE_CONVERSION( long, const void* )
MATRIX_TYPE_CONVERSION( long, char* )
MATRIX_TYPE_CONVERSION( long, const char* )

MATRIX_TYPE_CONVERSION( unsigned long, char )
MATRIX_TYPE_CONVERSION( unsigned long, signed char )
MATRIX_TYPE_CONVERSION( unsigned long, unsigned char )
MATRIX_TYPE_CONVERSION( unsigned long, short )
MATRIX_TYPE_CONVERSION( unsigned long, unsigned short )
MATRIX_TYPE_CONVERSION( unsigned long, int )
MATRIX_TYPE_CONVERSION( unsigned long, unsigned int )
MATRIX_TYPE_CONVERSION( unsigned long, long )
MATRIX_TYPE_CONVERSION( unsigned long, long long )
MATRIX_TYPE_CONVERSION( unsigned long, unsigned long long )
MATRIX_TYPE_CONVERSION( unsigned long, float )
MATRIX_TYPE_CONVERSION( unsigned long, double )
MATRIX_TYPE_CONVERSION( unsigned long, long double )
MATRIX_TYPE_CONVERSION( unsigned long, bool )
MATRIX_TYPE_CONVERSION( unsigned long, void* )
MATRIX_TYPE_CONVERSION( unsigned long, const void* )
MATRIX_TYPE_CONVERSION( unsigned long, char* )
MATRIX_TYPE_CONVERSION( unsigned long, const char* )

MATRIX_TYPE_CONVERSION( long long, char )
MATRIX_TYPE_CONVERSION( long long, signed char )
MATRIX_TYPE_CONVERSION( long long, unsigned char )
MATRIX_TYPE_CONVERSION( long long, short )
MATRIX_TYPE_CONVERSION( long long, unsigned short )
MATRIX_TYPE_CONVERSION( long long, int )
MATRIX_TYPE_CONVERSION( long long, unsigned int )
MATRIX_TYPE_CONVERSION( long long, long )
MATRIX_TYPE_CONVERSION( long long, unsigned long )
MATRIX_TYPE_CONVERSION( long long, unsigned long long )
MATRIX_TYPE_CONVERSION( long long, float )
MATRIX_TYPE_CONVERSION( long long, double )
MATRIX_TYPE_CONVERSION( long long, long double )
MATRIX_TYPE_CONVERSION( long long, bool )
MATRIX_TYPE_CONVERSION( long long, void* )
MATRIX_TYPE_CONVERSION( long long, const void* )
MATRIX_TYPE_CONVERSION( long long, char* )
MATRIX_TYPE_CONVERSION( long long, const char* )

MATRIX_TYPE_CONVERSION( unsigned long long, char )
MATRIX_TYPE_CONVERSION( unsigned long long, signed char )
MATRIX_TYPE_CONVERSION( unsigned long long, unsigned char )
MATRIX_TYPE_CONVERSION( unsigned long long, short )
MATRIX_TYPE_CONVERSION( unsigned long long, unsigned short )
MATRIX_TYPE_CONVERSION( unsigned long long, int )
MATRIX_TYPE_CONVERSION( unsigned long long, unsigned int )
MATRIX_TYPE_CONVERSION( unsigned long long, long )
MATRIX_TYPE_CONVERSION( unsigned long long, unsigned long )
MATRIX_TYPE_CONVERSION( unsigned long long, long long )
MATRIX_TYPE_CONVERSION( unsigned long long, float )
MATRIX_TYPE_CONVERSION( unsigned long long, double )
MATRIX_TYPE_CONVERSION( unsigned long long, long double )
MATRIX_TYPE_CONVERSION( unsigned long long, bool )
MATRIX_TYPE_CONVERSION( unsigned long long, void* )
MATRIX_TYPE_CONVERSION( unsigned long long, const void* )
MATRIX_TYPE_CONVERSION( unsigned long long, char* )
MATRIX_TYPE_CONVERSION( unsigned long long, const char* )

MATRIX_TYPE_CONVERSION( float, char )
MATRIX_TYPE_CONVERSION( float, signed char )
MATRIX_TYPE_CONVERSION( float, unsigned char )
MATRIX_TYPE_CONVERSION( float, short )
MATRIX_TYPE_CONVERSION( float, unsigned short )
MATRIX_TYPE_CONVERSION( float, int )
MATRIX_TYPE_CONVERSION( float, unsigned int )
MATRIX_TYPE_CONVERSION( float, long )
MATRIX_TYPE_CONVERSION( float, unsigned long )
MATRIX_TYPE_CONVERSION( float, long long )
MATRIX_TYPE_CONVERSION( float, unsigned long long )
MATRIX_TYPE_CONVERSION( float, double )
MATRIX_TYPE_CONVERSION( float, long double )
MATRIX_TYPE_CONVERSION( float, bool )
MATRIX_TYPE_CONVERSION( float, void* )
MATRIX_TYPE_CONVERSION( float, const void* )
MATRIX_TYPE_CONVERSION( float, char* )
MATRIX_TYPE_CONVERSION( float, const char* )

MATRIX_TYPE_CONVERSION( double, char )
MATRIX_TYPE_CONVERSION( double, signed char )
MATRIX_TYPE_CONVERSION( double, unsigned char )
MATRIX_TYPE_CONVERSION( double, short )
MATRIX_TYPE_CONVERSION( double, unsigned short )
MATRIX_TYPE_CONVERSION( double, int )
MATRIX_TYPE_CONVERSION( double, unsigned int )
MATRIX_TYPE_CONVERSION( double, long )
MATRIX_TYPE_CONVERSION( double, unsigned long )
MATRIX_TYPE_CONVERSION( double, long long )
MATRIX_TYPE_CONVERSION( double, unsigned long long )
MATRIX_TYPE_CONVERSION( double, float )
MATRIX_TYPE_CONVERSION( double, long double )
MATRIX_TYPE_CONVERSION( double, bool )
MATRIX_TYPE_CONVERSION( double, void* )
MATRIX_TYPE_CONVERSION( double, const void* )
MATRIX_TYPE_CONVERSION( double, char* )
MATRIX_TYPE_CONVERSION( double, const char* )

MATRIX_TYPE_CONVERSION( long double, char )
MATRIX_TYPE_CONVERSION( long double, signed char )
MATRIX_TYPE_CONVERSION( long double, unsigned char )
MATRIX_TYPE_CONVERSION( long double, short )
MATRIX_TYPE_CONVERSION( long double, unsigned short )
MATRIX_TYPE_CONVERSION( long double, int )
MATRIX_TYPE_CONVERSION( long double, unsigned int )
MATRIX_TYPE_CONVERSION( long double, long )
MATRIX_TYPE_CONVERSION( long double, unsigned long )
MATRIX_TYPE_CONVERSION( long double, long long )
MATRIX_TYPE_CONVERSION( long double, unsigned long long )
MATRIX_TYPE_CONVERSION( long double, float )
MATRIX_TYPE_CONVERSION( long double, double )
MATRIX_TYPE_CONVERSION( long double, bool )
MATRIX_TYPE_CONVERSION( long double, void* )
MATRIX_TYPE_CONVERSION( long double, const void* )
MATRIX_TYPE_CONVERSION( long double, char* )
MATRIX_TYPE_CONVERSION( long double, const char* )

MATRIX_TYPE_CONVERSION( bool, char )
MATRIX_TYPE_CONVERSION( bool, signed char )
MATRIX_TYPE_CONVERSION( bool, unsigned char )
MATRIX_TYPE_CONVERSION( bool, short )
MATRIX_TYPE_CONVERSION( bool, unsigned short )
MATRIX_TYPE_CONVERSION( bool, int )
MATRIX_TYPE_CONVERSION( bool, unsigned int )
MATRIX_TYPE_CONVERSION( bool, long )
MATRIX_TYPE_CONVERSION( bool, unsigned long )
MATRIX_TYPE_CONVERSION( bool, long long )
MATRIX_TYPE_CONVERSION( bool, unsigned long long )
MATRIX_TYPE_CONVERSION( bool, float )
MATRIX_TYPE_CONVERSION( bool, double )
MATRIX_TYPE_CONVERSION( bool, long double )
MATRIX_TYPE_CONVERSION( bool, void* )
MATRIX_TYPE_CONVERSION( bool, const void* )
MATRIX_TYPE_CONVERSION( bool, char* )
MATRIX_TYPE_CONVERSION( bool, const char* )

MATRIX_TYPE_CONVERSION( void*, char )
MATRIX_TYPE_CONVERSION( void*, signed char )
MATRIX_TYPE_CONVERSION( void*, unsigned char )
MATRIX_TYPE_CONVERSION( void*, short )
MATRIX_TYPE_CONVERSION( void*, unsigned short )
MATRIX_TYPE_CONVERSION( void*, int )
MATRIX_TYPE_CONVERSION( void*, unsigned int )
MATRIX_TYPE_CONVERSION( void*, long )
MATRIX_TYPE_CONVERSION( void*, unsigned long )
MATRIX_TYPE_CONVERSION( void*, long long )
MATRIX_TYPE_CONVERSION( void*, unsigned long long )
MATRIX_TYPE_CONVERSION( void*, float )
MATRIX_TYPE_CONVERSION( void*, double )
MATRIX_TYPE_CONVERSION( void*, long double )
MATRIX_TYPE_CONVERSION( void*, bool )
MATRIX_TYPE_CONVERSION( void*, char* )

MATRIX_TYPE_CONVERSION( const void*, char )
MATRIX_TYPE_CONVERSION( const void*, signed char )
MATRIX_TYPE_CONVERSION( const void*, unsigned char )
MATRIX_TYPE_CONVERSION( const void*, short )
MATRIX_TYPE_CONVERSION( const void*, unsigned short )
MATRIX_TYPE_CONVERSION( const void*, int )
MATRIX_TYPE_CONVERSION( const void*, unsigned int )
MATRIX_TYPE_CONVERSION( const void*, long )
MATRIX_TYPE_CONVERSION( const void*, unsigned long )
MATRIX_TYPE_CONVERSION( const void*, long long )
MATRIX_TYPE_CONVERSION( const void*, unsigned long long )
MATRIX_TYPE_CONVERSION( const void*, float )
MATRIX_TYPE_CONVERSION( const void*, double )
MATRIX_TYPE_CONVERSION( const void*, long double )
MATRIX_TYPE_CONVERSION( const void*, bool )
MATRIX_TYPE_CONVERSION( const void*, void* )
MATRIX_TYPE_CONVERSION( const void*, const void* )
MATRIX_TYPE_CONVERSION( const void*, char* )
MATRIX_TYPE_CONVERSION( const void*, const char* )

MATRIX_TYPE_CONVERSION( char*, char )
MATRIX_TYPE_CONVERSION( char*, signed char )
MATRIX_TYPE_CONVERSION( char*, unsigned char )
MATRIX_TYPE_CONVERSION( char*, short )
MATRIX_TYPE_CONVERSION( char*, unsigned short )
MATRIX_TYPE_CONVERSION( char*, int )
MATRIX_TYPE_CONVERSION( char*, unsigned int )
MATRIX_TYPE_CONVERSION( char*, long )
MATRIX_TYPE_CONVERSION( char*, unsigned long )
MATRIX_TYPE_CONVERSION( char*, long long )
MATRIX_TYPE_CONVERSION( char*, unsigned long long )
MATRIX_TYPE_CONVERSION( char*, float )
MATRIX_TYPE_CONVERSION( char*, double )
MATRIX_TYPE_CONVERSION( char*, long double )
MATRIX_TYPE_CONVERSION( char*, bool )
MATRIX_TYPE_CONVERSION( char*, void* )

MATRIX_TYPE_CONVERSION( const char*, char )
MATRIX_TYPE_CONVERSION( const char*, signed char )
MATRIX_TYPE_CONVERSION( const char*, unsigned char )
MATRIX_TYPE_CONVERSION( const char*, short )
MATRIX_TYPE_CONVERSION( const char*, unsigned short )
MATRIX_TYPE_CONVERSION( const char*, int )
MATRIX_TYPE_CONVERSION( const char*, unsigned int )
MATRIX_TYPE_CONVERSION( const char*, long )
MATRIX_TYPE_CONVERSION( const char*, unsigned long )
MATRIX_TYPE_CONVERSION( const char*, long long )
MATRIX_TYPE_CONVERSION( const char*, unsigned long long )
MATRIX_TYPE_CONVERSION( const char*, float )
MATRIX_TYPE_CONVERSION( const char*, double )
MATRIX_TYPE_CONVERSION( const char*, long double )
MATRIX_TYPE_CONVERSION( const char*, bool )
MATRIX_TYPE_CONVERSION( const char*, void* )
MATRIX_TYPE_CONVERSION( const char*, const void* )
MATRIX_TYPE_CONVERSION( const char*, char* )
MATRIX_TYPE_CONVERSION( const char*, const char* )

MATRIX_TYPE_CONVERSION( std::string, char* )
MATRIX_TYPE_CONVERSION( std::string, const char* )

#undef MATRIX_TYPE_CONVERSION

#define MATRIX_SIZE_CONVERSION( M, N, P, Q ) \
template MatrixBase< char, M, N >:: \
    MatrixBase< P, Q >( const MatrixBase< char, P, Q >& ac_roMatrix, \
                        const T& ac_rFill ); \
template MatrixBase< signed char, M, N >:: \
    MatrixBase< P, Q >( const MatrixBase< signed char, P, Q >& ac_roMatrix, \
                        const T& ac_rFill ); \
template MatrixBase< unsigned char, M, N >:: \
    MatrixBase< P, Q >( const MatrixBase< unsigned char, P, Q >& ac_roMatrix, \
                        const T& ac_rFill ); \
template MatrixBase< short, M, N >:: \
    MatrixBase< P, Q >( const MatrixBase< short, P, Q >& ac_roMatrix, \
                        const T& ac_rFill ); \
template MatrixBase< unsigned short, M, N >:: \
    MatrixBase< P, Q >( const MatrixBase< unsigned short, P, Q >& ac_roMatrix, \
                        const T& ac_rFill ); \
template MatrixBase< int, M, N >:: \
    MatrixBase< P, Q >( const MatrixBase< int, P, Q >& ac_roMatrix, \
                        const T& ac_rFill ); \
template MatrixBase< unsigned int, M, N >:: \
    MatrixBase< P, Q >( const MatrixBase< unsigned int, P, Q >& ac_roMatrix, \
                        const T& ac_rFill ); \
template MatrixBase< long, M, N >:: \
    MatrixBase< P, Q >( const MatrixBase< long, P, Q >& ac_roMatrix, \
                        const T& ac_rFill ); \
template MatrixBase< unsigned long, M, N >:: \
    MatrixBase< P, Q >( const MatrixBase< unsigned long, P, Q >& ac_roMatrix, \
                        const T& ac_rFill ); \
template MatrixBase< long long, M, N >:: \
    MatrixBase< P, Q >( const MatrixBase< long long, P, Q >& ac_roMatrix, \
                        const T& ac_rFill ); \
template MatrixBase< unsigned long long, M, N >:: \
    MatrixBase< P, Q >( const MatrixBase< unsigned long long, P, Q >& ac_roMatrix, \
                        const T& ac_rFill ); \
template MatrixBase< float, M, N >:: \
    MatrixBase< P, Q >( const MatrixBase< float, P, Q >& ac_roMatrix, \
                        const T& ac_rFill ); \
template MatrixBase< double, M, N >:: \
    MatrixBase< P, Q >( const MatrixBase< double, P, Q >& ac_roMatrix, \
                        const T& ac_rFill ); \
template MatrixBase< long double, M, N >:: \
    MatrixBase< P, Q >( const MatrixBase< long double, P, Q >& ac_roMatrix, \
                        const T& ac_rFill ); \
template MatrixBase< bool, M, N >:: \
    MatrixBase< P, Q >( const MatrixBase< bool, P, Q >& ac_roMatrix, \
                        const T& ac_rFill ); \
template MatrixBase< void*, M, N >:: \
    MatrixBase< P, Q >( const MatrixBase< void*, P, Q >& ac_roMatrix, \
                        const T& ac_rFill ); \
template MatrixBase< const void*, M, N >:: \
    MatrixBase< P, Q >( const MatrixBase< const void*, P, Q >& ac_roMatrix, \
                        const T& ac_rFill ); \
template MatrixBase< char*, M, N >:: \
    MatrixBase< P, Q >( const MatrixBase< char*, P, Q >& ac_roMatrix, \
                        const T& ac_rFill ); \
template MatrixBase< const char*, M, N >:: \
    MatrixBase< P, Q >( const MatrixBase< const char*, P, Q >& ac_roMatrix, \
                        const T& ac_rFill ); \
template MatrixBase< std::string, M, N >:: \
    MatrixBase< P, Q >( const MatrixBase< std::string, P, Q >& ac_roMatrix, \
                        const T& ac_rFill ); \
template MatrixBase< char, M, N >& MatrixBase< char, M, N >:: \
    Assign< P, Q >( const MatrixBase< char, P, Q >& ac_roMatrix ); \
template MatrixBase< signed char, M, N >& MatrixBase< signed char, M, N >:: \
    Assign< P, Q >( const MatrixBase< signed char, P, Q >& ac_roMatrix ); \
template MatrixBase< unsigned char, M, N >& MatrixBase< unsigned char, M, N >:: \
    Assign< P, Q >( const MatrixBase< unsigned char, P, Q >& ac_roMatrix ); \
template MatrixBase< short, M, N >& MatrixBase< short, M, N >:: \
    Assign< P, Q >( const MatrixBase< short, P, Q >& ac_roMatrix ); \
template MatrixBase< unsigned short, M, N >& MatrixBase< unsigned short, M, N >:: \
    Assign< P, Q >( const MatrixBase< unsigned short, P, Q >& ac_roMatrix ); \
template MatrixBase< int, M, N >& MatrixBase< int, M, N >:: \
    Assign< P, Q >( const MatrixBase< int, P, Q >& ac_roMatrix ); \
template MatrixBase< unsigned int, M, N >& MatrixBase< unsigned int, M, N >:: \
    Assign< P, Q >( const MatrixBase< unsigned int, P, Q >& ac_roMatrix ); \
template MatrixBase< long, M, N >& MatrixBase< long, M, N >:: \
    Assign< P, Q >( const MatrixBase< long, P, Q >& ac_roMatrix ); \
template MatrixBase< unsigned long, M, N >& MatrixBase< unsigned long, M, N >:: \
    Assign< P, Q >( const MatrixBase< unsigned long, P, Q >& ac_roMatrix ); \
template MatrixBase< long long, M, N >& MatrixBase< long long, M, N >:: \
    Assign< P, Q >( const MatrixBase< long long, P, Q >& ac_roMatrix ); \
template MatrixBase< unsigned long long, M, N >& MatrixBase< unsigned long long, M, N >:: \
    Assign< P, Q >( const MatrixBase< unsigned long long, P, Q >& ac_roMatrix ); \
template MatrixBase< float, M, N >& MatrixBase< float, M, N >:: \
    Assign< P, Q >( const MatrixBase< float, P, Q >& ac_roMatrix ); \
template MatrixBase< double, M, N >& MatrixBase< double, M, N >:: \
    Assign< P, Q >( const MatrixBase< double, P, Q >& ac_roMatrix ); \
template MatrixBase< long double, M, N >& MatrixBase< long double, M, N >:: \
    Assign< P, Q >( const MatrixBase< long double, P, Q >& ac_roMatrix ); \
template MatrixBase< bool, M, N >& MatrixBase< bool, M, N >:: \
    Assign< P, Q >( const MatrixBase< bool, P, Q >& ac_roMatrix ); \
template MatrixBase< void*, M, N >& MatrixBase< void*, M, N >:: \
    Assign< P, Q >( const MatrixBase< void*, P, Q >& ac_roMatrix ); \
template MatrixBase< const void*, M, N >& MatrixBase< const void*, M, N >:: \
    Assign< P, Q >( const MatrixBase< const void*, P, Q >& ac_roMatrix ); \
template MatrixBase< char*, M, N >& MatrixBase< char*, M, N >:: \
    Assign< P, Q >( const MatrixBase< char*, P, Q >& ac_roMatrix ); \
template MatrixBase< const char*, M, N >& MatrixBase< const char*, M, N >:: \
    Assign< P, Q >( const MatrixBase< const char*, P, Q >& ac_roMatrix ); \
template MatrixBase< std::string, M, N >& MatrixBase< std::string, M, N >:: \
    Assign< P, Q >( const MatrixBase< std::string, P, Q >& ac_roMatrix ); \
template MatrixBase< char, M, N >& MatrixBase< char, M, N >:: \
    operator=< P, Q >( const MatrixBase< char, P, Q >& ac_roMatrix ); \
template MatrixBase< signed char, M, N >& MatrixBase< signed char, M, N >:: \
    operator=< P, Q >( const MatrixBase< signed char, P, Q >& ac_roMatrix ); \
template MatrixBase< unsigned char, M, N >& MatrixBase< unsigned char, M, N >:: \
    operator=< P, Q >( const MatrixBase< unsigned char, P, Q >& ac_roMatrix ); \
template MatrixBase< short, M, N >& MatrixBase< short, M, N >:: \
    operator=< P, Q >( const MatrixBase< short, P, Q >& ac_roMatrix ); \
template MatrixBase< unsigned short, M, N >& MatrixBase< unsigned short, M, N >:: \
    operator=< P, Q >( const MatrixBase< unsigned short, P, Q >& ac_roMatrix ); \
template MatrixBase< int, M, N >& MatrixBase< int, M, N >:: \
    operator=< P, Q >( const MatrixBase< int, P, Q >& ac_roMatrix ); \
template MatrixBase< unsigned int, M, N >& MatrixBase< unsigned int, M, N >:: \
    operator=< P, Q >( const MatrixBase< unsigned int, P, Q >& ac_roMatrix ); \
template MatrixBase< long, M, N >& MatrixBase< long, M, N >:: \
    operator=< P, Q >( const MatrixBase< long, P, Q >& ac_roMatrix ); \
template MatrixBase< unsigned long, M, N >& MatrixBase< unsigned long, M, N >:: \
    operator=< P, Q >( const MatrixBase< unsigned long, P, Q >& ac_roMatrix ); \
template MatrixBase< long long, M, N >& MatrixBase< long long, M, N >:: \
    operator=< P, Q >( const MatrixBase< long long, P, Q >& ac_roMatrix ); \
template MatrixBase< unsigned long long, M, N >& MatrixBase< unsigned long long, M, N >:: \
    operator=< P, Q >( const MatrixBase< unsigned long long, P, Q >& ac_roMatrix ); \
template MatrixBase< float, M, N >& MatrixBase< float, M, N >:: \
    operator=< P, Q >( const MatrixBase< float, P, Q >& ac_roMatrix ); \
template MatrixBase< double, M, N >& MatrixBase< double, M, N >:: \
    operator=< P, Q >( const MatrixBase< double, P, Q >& ac_roMatrix ); \
template MatrixBase< long double, M, N >& MatrixBase< long double, M, N >:: \
    operator=< P, Q >( const MatrixBase< long double, P, Q >& ac_roMatrix ); \
template MatrixBase< bool, M, N >& MatrixBase< bool, M, N >:: \
    operator=< P, Q >( const MatrixBase< bool, P, Q >& ac_roMatrix ); \
template MatrixBase< void*, M, N >& MatrixBase< void*, M, N >:: \
    operator=< P, Q >( const MatrixBase< void*, P, Q >& ac_roMatrix ); \
template MatrixBase< const void*, M, N >& MatrixBase< const void*, M, N >:: \
    operator=< P, Q >( const MatrixBase< const void*, P, Q >& ac_roMatrix ); \
template MatrixBase< char*, M, N >& MatrixBase< char*, M, N >:: \
    operator=< P, Q >( const MatrixBase< char*, P, Q >& ac_roMatrix ); \
template MatrixBase< const char*, M, N >& MatrixBase< const char*, M, N >:: \
    operator=< P, Q >( const MatrixBase< const char*, P, Q >& ac_roMatrix ); \
template MatrixBase< std::string, M, N >& MatrixBase< std::string, M, N >:: \
    operator=< P, Q >( const MatrixBase< std::string, P, Q >& ac_roMatrix );

MATRIX_SIZE_CONVERSION( 0, 0, 0, 1 )
MATRIX_SIZE_CONVERSION( 0, 0, 0, 2 )
MATRIX_SIZE_CONVERSION( 0, 0, 0, 3 )
MATRIX_SIZE_CONVERSION( 0, 0, 0, 4 )
MATRIX_SIZE_CONVERSION( 0, 0, 1, 0 )
MATRIX_SIZE_CONVERSION( 0, 0, 1, 1 )
MATRIX_SIZE_CONVERSION( 0, 0, 1, 2 )
MATRIX_SIZE_CONVERSION( 0, 0, 1, 3 )
MATRIX_SIZE_CONVERSION( 0, 0, 1, 4 )
MATRIX_SIZE_CONVERSION( 0, 0, 2, 0 )
MATRIX_SIZE_CONVERSION( 0, 0, 2, 1 )
MATRIX_SIZE_CONVERSION( 0, 0, 2, 2 )
MATRIX_SIZE_CONVERSION( 0, 0, 2, 3 )
MATRIX_SIZE_CONVERSION( 0, 0, 2, 4 )
MATRIX_SIZE_CONVERSION( 0, 0, 3, 0 )
MATRIX_SIZE_CONVERSION( 0, 0, 3, 1 )
MATRIX_SIZE_CONVERSION( 0, 0, 3, 2 )
MATRIX_SIZE_CONVERSION( 0, 0, 3, 3 )
MATRIX_SIZE_CONVERSION( 0, 0, 3, 4 )
MATRIX_SIZE_CONVERSION( 0, 0, 4, 0 )
MATRIX_SIZE_CONVERSION( 0, 0, 4, 1 )
MATRIX_SIZE_CONVERSION( 0, 0, 4, 2 )
MATRIX_SIZE_CONVERSION( 0, 0, 4, 3 )
MATRIX_SIZE_CONVERSION( 0, 0, 4, 4 )

MATRIX_SIZE_CONVERSION( 0, 1, 0, 0 )
MATRIX_SIZE_CONVERSION( 0, 1, 0, 2 )
MATRIX_SIZE_CONVERSION( 0, 1, 0, 3 )
MATRIX_SIZE_CONVERSION( 0, 1, 0, 4 )
MATRIX_SIZE_CONVERSION( 0, 1, 1, 0 )
MATRIX_SIZE_CONVERSION( 0, 1, 1, 1 )
MATRIX_SIZE_CONVERSION( 0, 1, 1, 2 )
MATRIX_SIZE_CONVERSION( 0, 1, 1, 3 )
MATRIX_SIZE_CONVERSION( 0, 1, 1, 4 )
MATRIX_SIZE_CONVERSION( 0, 1, 2, 0 )
MATRIX_SIZE_CONVERSION( 0, 1, 2, 1 )
MATRIX_SIZE_CONVERSION( 0, 1, 2, 2 )
MATRIX_SIZE_CONVERSION( 0, 1, 2, 3 )
MATRIX_SIZE_CONVERSION( 0, 1, 2, 4 )
MATRIX_SIZE_CONVERSION( 0, 1, 3, 0 )
MATRIX_SIZE_CONVERSION( 0, 1, 3, 1 )
MATRIX_SIZE_CONVERSION( 0, 1, 3, 2 )
MATRIX_SIZE_CONVERSION( 0, 1, 3, 3 )
MATRIX_SIZE_CONVERSION( 0, 1, 3, 4 )
MATRIX_SIZE_CONVERSION( 0, 1, 4, 0 )
MATRIX_SIZE_CONVERSION( 0, 1, 4, 1 )
MATRIX_SIZE_CONVERSION( 0, 1, 4, 2 )
MATRIX_SIZE_CONVERSION( 0, 1, 4, 3 )
MATRIX_SIZE_CONVERSION( 0, 1, 4, 4 )

MATRIX_SIZE_CONVERSION( 0, 2, 0, 0 )
MATRIX_SIZE_CONVERSION( 0, 2, 0, 1 )
MATRIX_SIZE_CONVERSION( 0, 2, 0, 3 )
MATRIX_SIZE_CONVERSION( 0, 2, 0, 4 )
MATRIX_SIZE_CONVERSION( 0, 2, 1, 0 )
MATRIX_SIZE_CONVERSION( 0, 2, 1, 1 )
MATRIX_SIZE_CONVERSION( 0, 2, 1, 2 )
MATRIX_SIZE_CONVERSION( 0, 2, 1, 3 )
MATRIX_SIZE_CONVERSION( 0, 2, 1, 4 )
MATRIX_SIZE_CONVERSION( 0, 2, 2, 0 )
MATRIX_SIZE_CONVERSION( 0, 2, 2, 1 )
MATRIX_SIZE_CONVERSION( 0, 2, 2, 2 )
MATRIX_SIZE_CONVERSION( 0, 2, 2, 3 )
MATRIX_SIZE_CONVERSION( 0, 2, 2, 4 )
MATRIX_SIZE_CONVERSION( 0, 2, 3, 0 )
MATRIX_SIZE_CONVERSION( 0, 2, 3, 1 )
MATRIX_SIZE_CONVERSION( 0, 2, 3, 2 )
MATRIX_SIZE_CONVERSION( 0, 2, 3, 3 )
MATRIX_SIZE_CONVERSION( 0, 2, 3, 4 )
MATRIX_SIZE_CONVERSION( 0, 2, 4, 0 )
MATRIX_SIZE_CONVERSION( 0, 2, 4, 1 )
MATRIX_SIZE_CONVERSION( 0, 2, 4, 2 )
MATRIX_SIZE_CONVERSION( 0, 2, 4, 3 )
MATRIX_SIZE_CONVERSION( 0, 2, 4, 4 )

MATRIX_SIZE_CONVERSION( 0, 3, 0, 0 )
MATRIX_SIZE_CONVERSION( 0, 3, 0, 1 )
MATRIX_SIZE_CONVERSION( 0, 3, 0, 2 )
MATRIX_SIZE_CONVERSION( 0, 3, 0, 4 )
MATRIX_SIZE_CONVERSION( 0, 3, 1, 0 )
MATRIX_SIZE_CONVERSION( 0, 3, 1, 1 )
MATRIX_SIZE_CONVERSION( 0, 3, 1, 2 )
MATRIX_SIZE_CONVERSION( 0, 3, 1, 3 )
MATRIX_SIZE_CONVERSION( 0, 3, 1, 4 )
MATRIX_SIZE_CONVERSION( 0, 3, 2, 0 )
MATRIX_SIZE_CONVERSION( 0, 3, 2, 1 )
MATRIX_SIZE_CONVERSION( 0, 3, 2, 2 )
MATRIX_SIZE_CONVERSION( 0, 3, 2, 3 )
MATRIX_SIZE_CONVERSION( 0, 3, 2, 4 )
MATRIX_SIZE_CONVERSION( 0, 3, 3, 0 )
MATRIX_SIZE_CONVERSION( 0, 3, 3, 1 )
MATRIX_SIZE_CONVERSION( 0, 3, 3, 2 )
MATRIX_SIZE_CONVERSION( 0, 3, 3, 3 )
MATRIX_SIZE_CONVERSION( 0, 3, 3, 4 )
MATRIX_SIZE_CONVERSION( 0, 3, 4, 0 )
MATRIX_SIZE_CONVERSION( 0, 3, 4, 1 )
MATRIX_SIZE_CONVERSION( 0, 3, 4, 2 )
MATRIX_SIZE_CONVERSION( 0, 3, 4, 3 )
MATRIX_SIZE_CONVERSION( 0, 3, 4, 4 )

MATRIX_SIZE_CONVERSION( 0, 4, 0, 0 )
MATRIX_SIZE_CONVERSION( 0, 4, 0, 1 )
MATRIX_SIZE_CONVERSION( 0, 4, 0, 2 )
MATRIX_SIZE_CONVERSION( 0, 4, 0, 3 )
MATRIX_SIZE_CONVERSION( 0, 4, 1, 0 )
MATRIX_SIZE_CONVERSION( 0, 4, 1, 1 )
MATRIX_SIZE_CONVERSION( 0, 4, 1, 2 )
MATRIX_SIZE_CONVERSION( 0, 4, 1, 3 )
MATRIX_SIZE_CONVERSION( 0, 4, 1, 4 )
MATRIX_SIZE_CONVERSION( 0, 4, 2, 0 )
MATRIX_SIZE_CONVERSION( 0, 4, 2, 1 )
MATRIX_SIZE_CONVERSION( 0, 4, 2, 2 )
MATRIX_SIZE_CONVERSION( 0, 4, 2, 3 )
MATRIX_SIZE_CONVERSION( 0, 4, 2, 4 )
MATRIX_SIZE_CONVERSION( 0, 4, 3, 0 )
MATRIX_SIZE_CONVERSION( 0, 4, 3, 1 )
MATRIX_SIZE_CONVERSION( 0, 4, 3, 2 )
MATRIX_SIZE_CONVERSION( 0, 4, 3, 3 )
MATRIX_SIZE_CONVERSION( 0, 4, 3, 4 )
MATRIX_SIZE_CONVERSION( 0, 4, 4, 0 )
MATRIX_SIZE_CONVERSION( 0, 4, 4, 1 )
MATRIX_SIZE_CONVERSION( 0, 4, 4, 2 )
MATRIX_SIZE_CONVERSION( 0, 4, 4, 3 )
MATRIX_SIZE_CONVERSION( 0, 4, 4, 4 )

MATRIX_SIZE_CONVERSION( 1, 0, 0, 0 )
MATRIX_SIZE_CONVERSION( 1, 0, 0, 1 )
MATRIX_SIZE_CONVERSION( 1, 0, 0, 2 )
MATRIX_SIZE_CONVERSION( 1, 0, 0, 3 )
MATRIX_SIZE_CONVERSION( 1, 0, 0, 4 )
MATRIX_SIZE_CONVERSION( 1, 0, 1, 1 )
MATRIX_SIZE_CONVERSION( 1, 0, 1, 2 )
MATRIX_SIZE_CONVERSION( 1, 0, 1, 3 )
MATRIX_SIZE_CONVERSION( 1, 0, 1, 4 )
MATRIX_SIZE_CONVERSION( 1, 0, 2, 0 )
MATRIX_SIZE_CONVERSION( 1, 0, 2, 1 )
MATRIX_SIZE_CONVERSION( 1, 0, 2, 2 )
MATRIX_SIZE_CONVERSION( 1, 0, 2, 3 )
MATRIX_SIZE_CONVERSION( 1, 0, 2, 4 )
MATRIX_SIZE_CONVERSION( 1, 0, 3, 0 )
MATRIX_SIZE_CONVERSION( 1, 0, 3, 1 )
MATRIX_SIZE_CONVERSION( 1, 0, 3, 2 )
MATRIX_SIZE_CONVERSION( 1, 0, 3, 3 )
MATRIX_SIZE_CONVERSION( 1, 0, 3, 4 )
MATRIX_SIZE_CONVERSION( 1, 0, 4, 0 )
MATRIX_SIZE_CONVERSION( 1, 0, 4, 1 )
MATRIX_SIZE_CONVERSION( 1, 0, 4, 2 )
MATRIX_SIZE_CONVERSION( 1, 0, 4, 3 )
MATRIX_SIZE_CONVERSION( 1, 0, 4, 4 )

MATRIX_SIZE_CONVERSION( 1, 1, 0, 0 )
MATRIX_SIZE_CONVERSION( 1, 1, 0, 1 )
MATRIX_SIZE_CONVERSION( 1, 1, 0, 2 )
MATRIX_SIZE_CONVERSION( 1, 1, 0, 3 )
MATRIX_SIZE_CONVERSION( 1, 1, 0, 4 )
MATRIX_SIZE_CONVERSION( 1, 1, 1, 0 )
MATRIX_SIZE_CONVERSION( 1, 1, 1, 2 )
MATRIX_SIZE_CONVERSION( 1, 1, 1, 3 )
MATRIX_SIZE_CONVERSION( 1, 1, 1, 4 )
MATRIX_SIZE_CONVERSION( 1, 1, 2, 0 )
MATRIX_SIZE_CONVERSION( 1, 1, 2, 1 )
MATRIX_SIZE_CONVERSION( 1, 1, 2, 2 )
MATRIX_SIZE_CONVERSION( 1, 1, 2, 3 )
MATRIX_SIZE_CONVERSION( 1, 1, 2, 4 )
MATRIX_SIZE_CONVERSION( 1, 1, 3, 0 )
MATRIX_SIZE_CONVERSION( 1, 1, 3, 1 )
MATRIX_SIZE_CONVERSION( 1, 1, 3, 2 )
MATRIX_SIZE_CONVERSION( 1, 1, 3, 3 )
MATRIX_SIZE_CONVERSION( 1, 1, 3, 4 )
MATRIX_SIZE_CONVERSION( 1, 1, 4, 0 )
MATRIX_SIZE_CONVERSION( 1, 1, 4, 1 )
MATRIX_SIZE_CONVERSION( 1, 1, 4, 2 )
MATRIX_SIZE_CONVERSION( 1, 1, 4, 3 )
MATRIX_SIZE_CONVERSION( 1, 1, 4, 4 )

MATRIX_SIZE_CONVERSION( 1, 2, 0, 0 )
MATRIX_SIZE_CONVERSION( 1, 2, 0, 1 )
MATRIX_SIZE_CONVERSION( 1, 2, 0, 2 )
MATRIX_SIZE_CONVERSION( 1, 2, 0, 3 )
MATRIX_SIZE_CONVERSION( 1, 2, 0, 4 )
MATRIX_SIZE_CONVERSION( 1, 2, 1, 0 )
MATRIX_SIZE_CONVERSION( 1, 2, 1, 1 )
MATRIX_SIZE_CONVERSION( 1, 2, 1, 3 )
MATRIX_SIZE_CONVERSION( 1, 2, 1, 4 )
MATRIX_SIZE_CONVERSION( 1, 2, 2, 0 )
MATRIX_SIZE_CONVERSION( 1, 2, 2, 1 )
MATRIX_SIZE_CONVERSION( 1, 2, 2, 2 )
MATRIX_SIZE_CONVERSION( 1, 2, 2, 3 )
MATRIX_SIZE_CONVERSION( 1, 2, 2, 4 )
MATRIX_SIZE_CONVERSION( 1, 2, 3, 0 )
MATRIX_SIZE_CONVERSION( 1, 2, 3, 1 )
MATRIX_SIZE_CONVERSION( 1, 2, 3, 2 )
MATRIX_SIZE_CONVERSION( 1, 2, 3, 3 )
MATRIX_SIZE_CONVERSION( 1, 2, 3, 4 )
MATRIX_SIZE_CONVERSION( 1, 2, 4, 0 )
MATRIX_SIZE_CONVERSION( 1, 2, 4, 1 )
MATRIX_SIZE_CONVERSION( 1, 2, 4, 2 )
MATRIX_SIZE_CONVERSION( 1, 2, 4, 3 )
MATRIX_SIZE_CONVERSION( 1, 2, 4, 4 )

MATRIX_SIZE_CONVERSION( 1, 3, 0, 0 )
MATRIX_SIZE_CONVERSION( 1, 3, 0, 1 )
MATRIX_SIZE_CONVERSION( 1, 3, 0, 2 )
MATRIX_SIZE_CONVERSION( 1, 3, 0, 3 )
MATRIX_SIZE_CONVERSION( 1, 3, 0, 4 )
MATRIX_SIZE_CONVERSION( 1, 3, 1, 0 )
MATRIX_SIZE_CONVERSION( 1, 3, 1, 1 )
MATRIX_SIZE_CONVERSION( 1, 3, 1, 2 )
MATRIX_SIZE_CONVERSION( 1, 3, 1, 4 )
MATRIX_SIZE_CONVERSION( 1, 3, 2, 0 )
MATRIX_SIZE_CONVERSION( 1, 3, 2, 1 )
MATRIX_SIZE_CONVERSION( 1, 3, 2, 2 )
MATRIX_SIZE_CONVERSION( 1, 3, 2, 3 )
MATRIX_SIZE_CONVERSION( 1, 3, 2, 4 )
MATRIX_SIZE_CONVERSION( 1, 3, 3, 0 )
MATRIX_SIZE_CONVERSION( 1, 3, 3, 1 )
MATRIX_SIZE_CONVERSION( 1, 3, 3, 2 )
MATRIX_SIZE_CONVERSION( 1, 3, 3, 3 )
MATRIX_SIZE_CONVERSION( 1, 3, 3, 4 )
MATRIX_SIZE_CONVERSION( 1, 3, 4, 0 )
MATRIX_SIZE_CONVERSION( 1, 3, 4, 1 )
MATRIX_SIZE_CONVERSION( 1, 3, 4, 2 )
MATRIX_SIZE_CONVERSION( 1, 3, 4, 3 )
MATRIX_SIZE_CONVERSION( 1, 3, 4, 4 )

MATRIX_SIZE_CONVERSION( 1, 4, 0, 0 )
MATRIX_SIZE_CONVERSION( 1, 4, 0, 1 )
MATRIX_SIZE_CONVERSION( 1, 4, 0, 2 )
MATRIX_SIZE_CONVERSION( 1, 4, 0, 3 )
MATRIX_SIZE_CONVERSION( 1, 4, 0, 4 )
MATRIX_SIZE_CONVERSION( 1, 4, 1, 0 )
MATRIX_SIZE_CONVERSION( 1, 4, 1, 1 )
MATRIX_SIZE_CONVERSION( 1, 4, 1, 2 )
MATRIX_SIZE_CONVERSION( 1, 4, 1, 3 )
MATRIX_SIZE_CONVERSION( 1, 4, 2, 0 )
MATRIX_SIZE_CONVERSION( 1, 4, 2, 1 )
MATRIX_SIZE_CONVERSION( 1, 4, 2, 2 )
MATRIX_SIZE_CONVERSION( 1, 4, 2, 3 )
MATRIX_SIZE_CONVERSION( 1, 4, 2, 4 )
MATRIX_SIZE_CONVERSION( 1, 4, 3, 0 )
MATRIX_SIZE_CONVERSION( 1, 4, 3, 1 )
MATRIX_SIZE_CONVERSION( 1, 4, 3, 2 )
MATRIX_SIZE_CONVERSION( 1, 4, 3, 3 )
MATRIX_SIZE_CONVERSION( 1, 4, 3, 4 )
MATRIX_SIZE_CONVERSION( 1, 4, 4, 0 )
MATRIX_SIZE_CONVERSION( 1, 4, 4, 1 )
MATRIX_SIZE_CONVERSION( 1, 4, 4, 2 )
MATRIX_SIZE_CONVERSION( 1, 4, 4, 3 )
MATRIX_SIZE_CONVERSION( 1, 4, 4, 4 )

MATRIX_SIZE_CONVERSION( 2, 0, 0, 0 )
MATRIX_SIZE_CONVERSION( 2, 0, 0, 1 )
MATRIX_SIZE_CONVERSION( 2, 0, 0, 2 )
MATRIX_SIZE_CONVERSION( 2, 0, 0, 3 )
MATRIX_SIZE_CONVERSION( 2, 0, 0, 4 )
MATRIX_SIZE_CONVERSION( 2, 0, 1, 0 )
MATRIX_SIZE_CONVERSION( 2, 0, 1, 1 )
MATRIX_SIZE_CONVERSION( 2, 0, 1, 2 )
MATRIX_SIZE_CONVERSION( 2, 0, 1, 3 )
MATRIX_SIZE_CONVERSION( 2, 0, 1, 4 )
MATRIX_SIZE_CONVERSION( 2, 0, 2, 1 )
MATRIX_SIZE_CONVERSION( 2, 0, 2, 2 )
MATRIX_SIZE_CONVERSION( 2, 0, 2, 3 )
MATRIX_SIZE_CONVERSION( 2, 0, 2, 4 )
MATRIX_SIZE_CONVERSION( 2, 0, 3, 0 )
MATRIX_SIZE_CONVERSION( 2, 0, 3, 1 )
MATRIX_SIZE_CONVERSION( 2, 0, 3, 2 )
MATRIX_SIZE_CONVERSION( 2, 0, 3, 3 )
MATRIX_SIZE_CONVERSION( 2, 0, 3, 4 )
MATRIX_SIZE_CONVERSION( 2, 0, 4, 0 )
MATRIX_SIZE_CONVERSION( 2, 0, 4, 1 )
MATRIX_SIZE_CONVERSION( 2, 0, 4, 2 )
MATRIX_SIZE_CONVERSION( 2, 0, 4, 3 )
MATRIX_SIZE_CONVERSION( 2, 0, 4, 4 )

MATRIX_SIZE_CONVERSION( 2, 1, 0, 0 )
MATRIX_SIZE_CONVERSION( 2, 1, 0, 1 )
MATRIX_SIZE_CONVERSION( 2, 1, 0, 2 )
MATRIX_SIZE_CONVERSION( 2, 1, 0, 3 )
MATRIX_SIZE_CONVERSION( 2, 1, 0, 4 )
MATRIX_SIZE_CONVERSION( 2, 1, 1, 0 )
MATRIX_SIZE_CONVERSION( 2, 1, 1, 1 )
MATRIX_SIZE_CONVERSION( 2, 1, 1, 2 )
MATRIX_SIZE_CONVERSION( 2, 1, 1, 3 )
MATRIX_SIZE_CONVERSION( 2, 1, 1, 4 )
MATRIX_SIZE_CONVERSION( 2, 1, 2, 0 )
MATRIX_SIZE_CONVERSION( 2, 1, 2, 2 )
MATRIX_SIZE_CONVERSION( 2, 1, 2, 3 )
MATRIX_SIZE_CONVERSION( 2, 1, 2, 4 )
MATRIX_SIZE_CONVERSION( 2, 1, 3, 0 )
MATRIX_SIZE_CONVERSION( 2, 1, 3, 1 )
MATRIX_SIZE_CONVERSION( 2, 1, 3, 2 )
MATRIX_SIZE_CONVERSION( 2, 1, 3, 3 )
MATRIX_SIZE_CONVERSION( 2, 1, 3, 4 )
MATRIX_SIZE_CONVERSION( 2, 1, 4, 0 )
MATRIX_SIZE_CONVERSION( 2, 1, 4, 1 )
MATRIX_SIZE_CONVERSION( 2, 1, 4, 2 )
MATRIX_SIZE_CONVERSION( 2, 1, 4, 3 )
MATRIX_SIZE_CONVERSION( 2, 1, 4, 4 )

MATRIX_SIZE_CONVERSION( 2, 2, 0, 0 )
MATRIX_SIZE_CONVERSION( 2, 2, 0, 1 )
MATRIX_SIZE_CONVERSION( 2, 2, 0, 2 )
MATRIX_SIZE_CONVERSION( 2, 2, 0, 3 )
MATRIX_SIZE_CONVERSION( 2, 2, 0, 4 )
MATRIX_SIZE_CONVERSION( 2, 2, 1, 0 )
MATRIX_SIZE_CONVERSION( 2, 2, 1, 1 )
MATRIX_SIZE_CONVERSION( 2, 2, 1, 2 )
MATRIX_SIZE_CONVERSION( 2, 2, 1, 3 )
MATRIX_SIZE_CONVERSION( 2, 2, 1, 4 )
MATRIX_SIZE_CONVERSION( 2, 2, 2, 0 )
MATRIX_SIZE_CONVERSION( 2, 2, 2, 1 )
MATRIX_SIZE_CONVERSION( 2, 2, 2, 3 )
MATRIX_SIZE_CONVERSION( 2, 2, 2, 4 )
MATRIX_SIZE_CONVERSION( 2, 2, 3, 0 )
MATRIX_SIZE_CONVERSION( 2, 2, 3, 1 )
MATRIX_SIZE_CONVERSION( 2, 2, 3, 2 )
MATRIX_SIZE_CONVERSION( 2, 2, 3, 3 )
MATRIX_SIZE_CONVERSION( 2, 2, 3, 4 )
MATRIX_SIZE_CONVERSION( 2, 2, 4, 0 )
MATRIX_SIZE_CONVERSION( 2, 2, 4, 1 )
MATRIX_SIZE_CONVERSION( 2, 2, 4, 2 )
MATRIX_SIZE_CONVERSION( 2, 2, 4, 3 )
MATRIX_SIZE_CONVERSION( 2, 2, 4, 4 )

MATRIX_SIZE_CONVERSION( 2, 3, 0, 0 )
MATRIX_SIZE_CONVERSION( 2, 3, 0, 1 )
MATRIX_SIZE_CONVERSION( 2, 3, 0, 2 )
MATRIX_SIZE_CONVERSION( 2, 3, 0, 3 )
MATRIX_SIZE_CONVERSION( 2, 3, 0, 4 )
MATRIX_SIZE_CONVERSION( 2, 3, 1, 0 )
MATRIX_SIZE_CONVERSION( 2, 3, 1, 1 )
MATRIX_SIZE_CONVERSION( 2, 3, 1, 2 )
MATRIX_SIZE_CONVERSION( 2, 3, 1, 3 )
MATRIX_SIZE_CONVERSION( 2, 3, 1, 4 )
MATRIX_SIZE_CONVERSION( 2, 3, 2, 0 )
MATRIX_SIZE_CONVERSION( 2, 3, 2, 1 )
MATRIX_SIZE_CONVERSION( 2, 3, 2, 2 )
MATRIX_SIZE_CONVERSION( 2, 3, 2, 4 )
MATRIX_SIZE_CONVERSION( 2, 3, 3, 0 )
MATRIX_SIZE_CONVERSION( 2, 3, 3, 1 )
MATRIX_SIZE_CONVERSION( 2, 3, 3, 2 )
MATRIX_SIZE_CONVERSION( 2, 3, 3, 3 )
MATRIX_SIZE_CONVERSION( 2, 3, 3, 4 )
MATRIX_SIZE_CONVERSION( 2, 3, 4, 0 )
MATRIX_SIZE_CONVERSION( 2, 3, 4, 1 )
MATRIX_SIZE_CONVERSION( 2, 3, 4, 2 )
MATRIX_SIZE_CONVERSION( 2, 3, 4, 3 )
MATRIX_SIZE_CONVERSION( 2, 3, 4, 4 )

MATRIX_SIZE_CONVERSION( 2, 4, 0, 0 )
MATRIX_SIZE_CONVERSION( 2, 4, 0, 1 )
MATRIX_SIZE_CONVERSION( 2, 4, 0, 2 )
MATRIX_SIZE_CONVERSION( 2, 4, 0, 3 )
MATRIX_SIZE_CONVERSION( 2, 4, 0, 4 )
MATRIX_SIZE_CONVERSION( 2, 4, 1, 0 )
MATRIX_SIZE_CONVERSION( 2, 4, 1, 1 )
MATRIX_SIZE_CONVERSION( 2, 4, 1, 2 )
MATRIX_SIZE_CONVERSION( 2, 4, 1, 3 )
MATRIX_SIZE_CONVERSION( 2, 4, 1, 4 )
MATRIX_SIZE_CONVERSION( 2, 4, 2, 0 )
MATRIX_SIZE_CONVERSION( 2, 4, 2, 1 )
MATRIX_SIZE_CONVERSION( 2, 4, 2, 2 )
MATRIX_SIZE_CONVERSION( 2, 4, 2, 3 )
MATRIX_SIZE_CONVERSION( 2, 4, 3, 0 )
MATRIX_SIZE_CONVERSION( 2, 4, 3, 1 )
MATRIX_SIZE_CONVERSION( 2, 4, 3, 2 )
MATRIX_SIZE_CONVERSION( 2, 4, 3, 3 )
MATRIX_SIZE_CONVERSION( 2, 4, 3, 4 )
MATRIX_SIZE_CONVERSION( 2, 4, 4, 0 )
MATRIX_SIZE_CONVERSION( 2, 4, 4, 1 )
MATRIX_SIZE_CONVERSION( 2, 4, 4, 2 )
MATRIX_SIZE_CONVERSION( 2, 4, 4, 3 )
MATRIX_SIZE_CONVERSION( 2, 4, 4, 4 )

MATRIX_SIZE_CONVERSION( 3, 0, 0, 0 )
MATRIX_SIZE_CONVERSION( 3, 0, 0, 1 )
MATRIX_SIZE_CONVERSION( 3, 0, 0, 2 )
MATRIX_SIZE_CONVERSION( 3, 0, 0, 3 )
MATRIX_SIZE_CONVERSION( 3, 0, 0, 4 )
MATRIX_SIZE_CONVERSION( 3, 0, 1, 0 )
MATRIX_SIZE_CONVERSION( 3, 0, 1, 1 )
MATRIX_SIZE_CONVERSION( 3, 0, 1, 2 )
MATRIX_SIZE_CONVERSION( 3, 0, 1, 3 )
MATRIX_SIZE_CONVERSION( 3, 0, 1, 4 )
MATRIX_SIZE_CONVERSION( 3, 0, 2, 0 )
MATRIX_SIZE_CONVERSION( 3, 0, 2, 1 )
MATRIX_SIZE_CONVERSION( 3, 0, 2, 2 )
MATRIX_SIZE_CONVERSION( 3, 0, 2, 3 )
MATRIX_SIZE_CONVERSION( 3, 0, 2, 4 )
MATRIX_SIZE_CONVERSION( 3, 0, 3, 1 )
MATRIX_SIZE_CONVERSION( 3, 0, 3, 2 )
MATRIX_SIZE_CONVERSION( 3, 0, 3, 3 )
MATRIX_SIZE_CONVERSION( 3, 0, 3, 4 )
MATRIX_SIZE_CONVERSION( 3, 0, 4, 0 )
MATRIX_SIZE_CONVERSION( 3, 0, 4, 1 )
MATRIX_SIZE_CONVERSION( 3, 0, 4, 2 )
MATRIX_SIZE_CONVERSION( 3, 0, 4, 3 )
MATRIX_SIZE_CONVERSION( 3, 0, 4, 4 )

MATRIX_SIZE_CONVERSION( 3, 1, 0, 0 )
MATRIX_SIZE_CONVERSION( 3, 1, 0, 1 )
MATRIX_SIZE_CONVERSION( 3, 1, 0, 2 )
MATRIX_SIZE_CONVERSION( 3, 1, 0, 3 )
MATRIX_SIZE_CONVERSION( 3, 1, 0, 4 )
MATRIX_SIZE_CONVERSION( 3, 1, 1, 0 )
MATRIX_SIZE_CONVERSION( 3, 1, 1, 1 )
MATRIX_SIZE_CONVERSION( 3, 1, 1, 2 )
MATRIX_SIZE_CONVERSION( 3, 1, 1, 3 )
MATRIX_SIZE_CONVERSION( 3, 1, 1, 4 )
MATRIX_SIZE_CONVERSION( 3, 1, 2, 0 )
MATRIX_SIZE_CONVERSION( 3, 1, 2, 1 )
MATRIX_SIZE_CONVERSION( 3, 1, 2, 2 )
MATRIX_SIZE_CONVERSION( 3, 1, 2, 3 )
MATRIX_SIZE_CONVERSION( 3, 1, 2, 4 )
MATRIX_SIZE_CONVERSION( 3, 1, 3, 0 )
MATRIX_SIZE_CONVERSION( 3, 1, 3, 2 )
MATRIX_SIZE_CONVERSION( 3, 1, 3, 3 )
MATRIX_SIZE_CONVERSION( 3, 1, 3, 4 )
MATRIX_SIZE_CONVERSION( 3, 1, 4, 0 )
MATRIX_SIZE_CONVERSION( 3, 1, 4, 1 )
MATRIX_SIZE_CONVERSION( 3, 1, 4, 2 )
MATRIX_SIZE_CONVERSION( 3, 1, 4, 3 )
MATRIX_SIZE_CONVERSION( 3, 1, 4, 4 )

MATRIX_SIZE_CONVERSION( 3, 2, 0, 0 )
MATRIX_SIZE_CONVERSION( 3, 2, 0, 1 )
MATRIX_SIZE_CONVERSION( 3, 2, 0, 2 )
MATRIX_SIZE_CONVERSION( 3, 2, 0, 3 )
MATRIX_SIZE_CONVERSION( 3, 2, 0, 4 )
MATRIX_SIZE_CONVERSION( 3, 2, 1, 0 )
MATRIX_SIZE_CONVERSION( 3, 2, 1, 1 )
MATRIX_SIZE_CONVERSION( 3, 2, 1, 2 )
MATRIX_SIZE_CONVERSION( 3, 2, 1, 3 )
MATRIX_SIZE_CONVERSION( 3, 2, 1, 4 )
MATRIX_SIZE_CONVERSION( 3, 2, 2, 0 )
MATRIX_SIZE_CONVERSION( 3, 2, 2, 1 )
MATRIX_SIZE_CONVERSION( 3, 2, 2, 2 )
MATRIX_SIZE_CONVERSION( 3, 2, 2, 3 )
MATRIX_SIZE_CONVERSION( 3, 2, 2, 4 )
MATRIX_SIZE_CONVERSION( 3, 2, 3, 0 )
MATRIX_SIZE_CONVERSION( 3, 2, 3, 1 )
MATRIX_SIZE_CONVERSION( 3, 2, 3, 3 )
MATRIX_SIZE_CONVERSION( 3, 2, 3, 4 )
MATRIX_SIZE_CONVERSION( 3, 2, 4, 0 )
MATRIX_SIZE_CONVERSION( 3, 2, 4, 1 )
MATRIX_SIZE_CONVERSION( 3, 2, 4, 2 )
MATRIX_SIZE_CONVERSION( 3, 2, 4, 3 )
MATRIX_SIZE_CONVERSION( 3, 2, 4, 4 )

MATRIX_SIZE_CONVERSION( 3, 3, 0, 0 )
MATRIX_SIZE_CONVERSION( 3, 3, 0, 1 )
MATRIX_SIZE_CONVERSION( 3, 3, 0, 2 )
MATRIX_SIZE_CONVERSION( 3, 3, 0, 3 )
MATRIX_SIZE_CONVERSION( 3, 3, 0, 4 )
MATRIX_SIZE_CONVERSION( 3, 3, 1, 0 )
MATRIX_SIZE_CONVERSION( 3, 3, 1, 1 )
MATRIX_SIZE_CONVERSION( 3, 3, 1, 2 )
MATRIX_SIZE_CONVERSION( 3, 3, 1, 3 )
MATRIX_SIZE_CONVERSION( 3, 3, 1, 4 )
MATRIX_SIZE_CONVERSION( 3, 3, 2, 0 )
MATRIX_SIZE_CONVERSION( 3, 3, 2, 1 )
MATRIX_SIZE_CONVERSION( 3, 3, 2, 2 )
MATRIX_SIZE_CONVERSION( 3, 3, 2, 3 )
MATRIX_SIZE_CONVERSION( 3, 3, 2, 4 )
MATRIX_SIZE_CONVERSION( 3, 3, 3, 0 )
MATRIX_SIZE_CONVERSION( 3, 3, 3, 1 )
MATRIX_SIZE_CONVERSION( 3, 3, 3, 2 )
MATRIX_SIZE_CONVERSION( 3, 3, 3, 4 )
MATRIX_SIZE_CONVERSION( 3, 3, 4, 0 )
MATRIX_SIZE_CONVERSION( 3, 3, 4, 1 )
MATRIX_SIZE_CONVERSION( 3, 3, 4, 2 )
MATRIX_SIZE_CONVERSION( 3, 3, 4, 3 )
MATRIX_SIZE_CONVERSION( 3, 3, 4, 4 )

MATRIX_SIZE_CONVERSION( 3, 4, 0, 0 )
MATRIX_SIZE_CONVERSION( 3, 4, 0, 1 )
MATRIX_SIZE_CONVERSION( 3, 4, 0, 2 )
MATRIX_SIZE_CONVERSION( 3, 4, 0, 3 )
MATRIX_SIZE_CONVERSION( 3, 4, 0, 4 )
MATRIX_SIZE_CONVERSION( 3, 4, 1, 0 )
MATRIX_SIZE_CONVERSION( 3, 4, 1, 1 )
MATRIX_SIZE_CONVERSION( 3, 4, 1, 2 )
MATRIX_SIZE_CONVERSION( 3, 4, 1, 3 )
MATRIX_SIZE_CONVERSION( 3, 4, 1, 4 )
MATRIX_SIZE_CONVERSION( 3, 4, 2, 0 )
MATRIX_SIZE_CONVERSION( 3, 4, 2, 1 )
MATRIX_SIZE_CONVERSION( 3, 4, 2, 2 )
MATRIX_SIZE_CONVERSION( 3, 4, 2, 3 )
MATRIX_SIZE_CONVERSION( 3, 4, 2, 4 )
MATRIX_SIZE_CONVERSION( 3, 4, 3, 0 )
MATRIX_SIZE_CONVERSION( 3, 4, 3, 1 )
MATRIX_SIZE_CONVERSION( 3, 4, 3, 2 )
MATRIX_SIZE_CONVERSION( 3, 4, 3, 3 )
MATRIX_SIZE_CONVERSION( 3, 4, 4, 0 )
MATRIX_SIZE_CONVERSION( 3, 4, 4, 1 )
MATRIX_SIZE_CONVERSION( 3, 4, 4, 2 )
MATRIX_SIZE_CONVERSION( 3, 4, 4, 3 )
MATRIX_SIZE_CONVERSION( 3, 4, 4, 4 )

MATRIX_SIZE_CONVERSION( 4, 0, 0, 0 )
MATRIX_SIZE_CONVERSION( 4, 0, 0, 1 )
MATRIX_SIZE_CONVERSION( 4, 0, 0, 2 )
MATRIX_SIZE_CONVERSION( 4, 0, 0, 3 )
MATRIX_SIZE_CONVERSION( 4, 0, 0, 4 )
MATRIX_SIZE_CONVERSION( 4, 0, 1, 0 )
MATRIX_SIZE_CONVERSION( 4, 0, 1, 1 )
MATRIX_SIZE_CONVERSION( 4, 0, 1, 2 )
MATRIX_SIZE_CONVERSION( 4, 0, 1, 3 )
MATRIX_SIZE_CONVERSION( 4, 0, 1, 4 )
MATRIX_SIZE_CONVERSION( 4, 0, 2, 0 )
MATRIX_SIZE_CONVERSION( 4, 0, 2, 1 )
MATRIX_SIZE_CONVERSION( 4, 0, 2, 2 )
MATRIX_SIZE_CONVERSION( 4, 0, 2, 3 )
MATRIX_SIZE_CONVERSION( 4, 0, 2, 4 )
MATRIX_SIZE_CONVERSION( 4, 0, 3, 0 )
MATRIX_SIZE_CONVERSION( 4, 0, 3, 1 )
MATRIX_SIZE_CONVERSION( 4, 0, 3, 2 )
MATRIX_SIZE_CONVERSION( 4, 0, 3, 3 )
MATRIX_SIZE_CONVERSION( 4, 0, 3, 4 )
MATRIX_SIZE_CONVERSION( 4, 0, 4, 1 )
MATRIX_SIZE_CONVERSION( 4, 0, 4, 2 )
MATRIX_SIZE_CONVERSION( 4, 0, 4, 3 )
MATRIX_SIZE_CONVERSION( 4, 0, 4, 4 )

MATRIX_SIZE_CONVERSION( 4, 1, 0, 0 )
MATRIX_SIZE_CONVERSION( 4, 1, 0, 1 )
MATRIX_SIZE_CONVERSION( 4, 1, 0, 2 )
MATRIX_SIZE_CONVERSION( 4, 1, 0, 3 )
MATRIX_SIZE_CONVERSION( 4, 1, 0, 4 )
MATRIX_SIZE_CONVERSION( 4, 1, 1, 0 )
MATRIX_SIZE_CONVERSION( 4, 1, 1, 1 )
MATRIX_SIZE_CONVERSION( 4, 1, 1, 2 )
MATRIX_SIZE_CONVERSION( 4, 1, 1, 3 )
MATRIX_SIZE_CONVERSION( 4, 1, 1, 4 )
MATRIX_SIZE_CONVERSION( 4, 1, 2, 0 )
MATRIX_SIZE_CONVERSION( 4, 1, 2, 1 )
MATRIX_SIZE_CONVERSION( 4, 1, 2, 2 )
MATRIX_SIZE_CONVERSION( 4, 1, 2, 3 )
MATRIX_SIZE_CONVERSION( 4, 1, 2, 4 )
MATRIX_SIZE_CONVERSION( 4, 1, 3, 0 )
MATRIX_SIZE_CONVERSION( 4, 1, 3, 1 )
MATRIX_SIZE_CONVERSION( 4, 1, 3, 2 )
MATRIX_SIZE_CONVERSION( 4, 1, 3, 3 )
MATRIX_SIZE_CONVERSION( 4, 1, 3, 4 )
MATRIX_SIZE_CONVERSION( 4, 1, 4, 0 )
MATRIX_SIZE_CONVERSION( 4, 1, 4, 2 )
MATRIX_SIZE_CONVERSION( 4, 1, 4, 3 )
MATRIX_SIZE_CONVERSION( 4, 1, 4, 4 )

MATRIX_SIZE_CONVERSION( 4, 2, 0, 0 )
MATRIX_SIZE_CONVERSION( 4, 2, 0, 1 )
MATRIX_SIZE_CONVERSION( 4, 2, 0, 2 )
MATRIX_SIZE_CONVERSION( 4, 2, 0, 3 )
MATRIX_SIZE_CONVERSION( 4, 2, 0, 4 )
MATRIX_SIZE_CONVERSION( 4, 2, 1, 0 )
MATRIX_SIZE_CONVERSION( 4, 2, 1, 1 )
MATRIX_SIZE_CONVERSION( 4, 2, 1, 2 )
MATRIX_SIZE_CONVERSION( 4, 2, 1, 3 )
MATRIX_SIZE_CONVERSION( 4, 2, 1, 4 )
MATRIX_SIZE_CONVERSION( 4, 2, 2, 0 )
MATRIX_SIZE_CONVERSION( 4, 2, 2, 1 )
MATRIX_SIZE_CONVERSION( 4, 2, 2, 2 )
MATRIX_SIZE_CONVERSION( 4, 2, 2, 3 )
MATRIX_SIZE_CONVERSION( 4, 2, 2, 4 )
MATRIX_SIZE_CONVERSION( 4, 2, 3, 0 )
MATRIX_SIZE_CONVERSION( 4, 2, 3, 1 )
MATRIX_SIZE_CONVERSION( 4, 2, 3, 2 )
MATRIX_SIZE_CONVERSION( 4, 2, 3, 3 )
MATRIX_SIZE_CONVERSION( 4, 2, 3, 4 )
MATRIX_SIZE_CONVERSION( 4, 2, 4, 0 )
MATRIX_SIZE_CONVERSION( 4, 2, 4, 1 )
MATRIX_SIZE_CONVERSION( 4, 2, 4, 3 )
MATRIX_SIZE_CONVERSION( 4, 2, 4, 4 )

MATRIX_SIZE_CONVERSION( 4, 3, 0, 0 )
MATRIX_SIZE_CONVERSION( 4, 3, 0, 1 )
MATRIX_SIZE_CONVERSION( 4, 3, 0, 2 )
MATRIX_SIZE_CONVERSION( 4, 3, 0, 3 )
MATRIX_SIZE_CONVERSION( 4, 3, 0, 4 )
MATRIX_SIZE_CONVERSION( 4, 3, 1, 0 )
MATRIX_SIZE_CONVERSION( 4, 3, 1, 1 )
MATRIX_SIZE_CONVERSION( 4, 3, 1, 2 )
MATRIX_SIZE_CONVERSION( 4, 3, 1, 3 )
MATRIX_SIZE_CONVERSION( 4, 3, 1, 4 )
MATRIX_SIZE_CONVERSION( 4, 3, 2, 0 )
MATRIX_SIZE_CONVERSION( 4, 3, 2, 1 )
MATRIX_SIZE_CONVERSION( 4, 3, 2, 2 )
MATRIX_SIZE_CONVERSION( 4, 3, 2, 3 )
MATRIX_SIZE_CONVERSION( 4, 3, 2, 4 )
MATRIX_SIZE_CONVERSION( 4, 3, 3, 0 )
MATRIX_SIZE_CONVERSION( 4, 3, 3, 1 )
MATRIX_SIZE_CONVERSION( 4, 3, 3, 2 )
MATRIX_SIZE_CONVERSION( 4, 3, 3, 3 )
MATRIX_SIZE_CONVERSION( 4, 3, 3, 4 )
MATRIX_SIZE_CONVERSION( 4, 3, 4, 0 )
MATRIX_SIZE_CONVERSION( 4, 3, 4, 1 )
MATRIX_SIZE_CONVERSION( 4, 3, 4, 2 )
MATRIX_SIZE_CONVERSION( 4, 3, 4, 4 )

MATRIX_SIZE_CONVERSION( 4, 4, 0, 0 )
MATRIX_SIZE_CONVERSION( 4, 4, 0, 1 )
MATRIX_SIZE_CONVERSION( 4, 4, 0, 2 )
MATRIX_SIZE_CONVERSION( 4, 4, 0, 3 )
MATRIX_SIZE_CONVERSION( 4, 4, 0, 4 )
MATRIX_SIZE_CONVERSION( 4, 4, 1, 0 )
MATRIX_SIZE_CONVERSION( 4, 4, 1, 1 )
MATRIX_SIZE_CONVERSION( 4, 4, 1, 2 )
MATRIX_SIZE_CONVERSION( 4, 4, 1, 3 )
MATRIX_SIZE_CONVERSION( 4, 4, 1, 4 )
MATRIX_SIZE_CONVERSION( 4, 4, 2, 0 )
MATRIX_SIZE_CONVERSION( 4, 4, 2, 1 )
MATRIX_SIZE_CONVERSION( 4, 4, 2, 2 )
MATRIX_SIZE_CONVERSION( 4, 4, 2, 3 )
MATRIX_SIZE_CONVERSION( 4, 4, 2, 4 )
MATRIX_SIZE_CONVERSION( 4, 4, 3, 0 )
MATRIX_SIZE_CONVERSION( 4, 4, 3, 1 )
MATRIX_SIZE_CONVERSION( 4, 4, 3, 2 )
MATRIX_SIZE_CONVERSION( 4, 4, 3, 3 )
MATRIX_SIZE_CONVERSION( 4, 4, 3, 4 )
MATRIX_SIZE_CONVERSION( 4, 4, 4, 0 )
MATRIX_SIZE_CONVERSION( 4, 4, 4, 1 )
MATRIX_SIZE_CONVERSION( 4, 4, 4, 2 )
MATRIX_SIZE_CONVERSION( 4, 4, 4, 3 )

#undef MATRIX_SIZE_CONVERSION

}   // namespace Math
