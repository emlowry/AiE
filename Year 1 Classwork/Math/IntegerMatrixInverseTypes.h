/******************************************************************************
 * File:               IntegerMatrixInverseTypes.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 25, 2013
 * Description:        Template specializations for the types to use for inverse
 *                      matrices of integer matrices.
 * Last Modified:      November 25, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef _INTEGER_MATRIX_INVERSE_TYPES_H_
#define _INTEGER_MATRIX_INVERSE_TYPES_H_

#include "Matrix.h"

namespace Math
{

// define inverse data types
template<>
struct MatrixInverse< bool >
{
    typedef float Type;
};
template<>
struct MatrixInverse< char >
{
    typedef float Type;
};
template<>
struct MatrixInverse< signed char >
{
    typedef float Type;
};
template<>
struct MatrixInverse< unsigned char >
{
    typedef float Type;
};
template<>
struct MatrixInverse< short >
{
    typedef double Type;
};
template<>
struct MatrixInverse< unsigned short >
{
    typedef double Type;
};
template<>
struct MatrixInverse< int >
{
    typedef double Type;
};
template<>
struct MatrixInverse< unsigned int >
{
    typedef double Type;
};
template<>
struct MatrixInverse< long >
{
    typedef long double Type;
};
template<>
struct MatrixInverse< unsigned long >
{
    typedef long double Type;
};
template<>
struct MatrixInverse< long long >
{
    typedef long double Type;
};
template<>
struct MatrixInverse< unsigned long long >
{
    typedef long double Type;
};

}   // namespace Math

#endif  // _INTEGER_MATRIX_INVERSE_TYPES_H_
