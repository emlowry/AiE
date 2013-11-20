/******************************************************************************
 * File:               MatrixBase.h
 * Author:             Elizabeth Lowry
 * Date Created:       November 20, 2013
 * Description:        Base class for matrices of any type.
 *                      The library compiles MatrixBase classes with dimensions
 *                      of any combination of 1, 2, 3, or 4 for string, char*,
 *                      and void* types.  If a user needs to instantiate a
 *                      MatrixBase class with type or dimensions beyond these,
 *                      then they need to include T_MatrixBase.h instead.
 * Last Modified:      November 20, 2013
 * Last Modification:  Moving code in from Matrix.h.
 ******************************************************************************/

#ifndef _MATRIX_BASE_H_
#define _MATRIX_BASE_H_

namespace Math
{

// Base class for matrices.  For matrices with mathematical operations beyond
// transposition, use the child Matrix class instead.
template< typename T, unsigned int M, unsigned int N = M >
class MatrixBase
{
public:

    // Simplify typing
    typedef MatrixBase< T, N, M > TransposeType;
    static const T& DEFAULT_FILL;   // referance to MatrixFill< T >::DEFAULT

    // Default constructor fills array with DEFAULT_FILL
    MatrixBase();

    // Virtual destructor needed, since Transpose and assignment functions
    // are virtual.  Assignment operators are implemented in terms of virtual
    // Assign functions in case child classes have more fields to set.
    virtual ~MatrixBase();
    
    // Copy/move constructor/operator
    MatrixBase( const MatrixBase& ac_roMatrix );
    virtual MatrixBase& Assign( const MatrixBase& ac_roMatrix );
    MatrixBase& operator=( const MatrixBase& ac_roMatrix );
    MatrixBase( MatrixBase&& a_rroMatrix );
    virtual MatrixBase& Assign( MatrixBase&& a_rroMatrix );
    MatrixBase& operator=( MatrixBase&& a_rroMatrix );

    // Construct/assign from a differently-sized matrix
    template< typename U, unsigned int P, unsigned int Q >
    MatrixBase( const MatrixBase< U, P, Q >& ac_roMatrix,
                const T& ac_roFill = MatrixFill< T >::DEFAULT );
    template< typename U, unsigned int P, unsigned int Q >
    virtual MatrixBase& Assign( const MatrixBase< U, P, Q >& ac_roMatrix );
    MatrixBase& operator=( const MatrixBase< U, P, Q >& ac_roMatrix );

    // Construct with all values equal to parameter
    template< typename U >
    MatrixBase( const U& ac_rFill );
    template< typename U, typename V >
    MatrixBase( const U& ac_rFill, const V& ac_rIdentityFill );

    // Construct with data filled in with parameter data one row at a time, one
    // column at a time, until end of parameter data, then filled with either
    // default/previous data
    template< typename U >
    MatrixBase( const U (&ac_raData)[ M * N ] );
    template< typename U, unsigned int t_uiDataSize >
    MatrixBase( const U (&ac_raData)[ t_uiDataSize ],
                const T& ac_roFill = MatrixFill< T >::DEFAULT );
    template< typename U >
    MatrixBase( const U* const ac_cpData,
                const unsigned int ac_uiSize = M * N,
                const T& ac_roFill = MatrixFill< T >::DEFAULT );

    // Construct with data filled in with parameter data where given and either
    // default/previous data elsewhere
    template< typename U >
    MatrixBase( const U (&ac_raaData)[ M ][ N ] );
    template< typename U, unsigned int t_uiRows, unsigned int t_uiColumns >
    MatrixBase( const U (&ac_raaData)[ t_uiRows ][ t_uiColumns ],
                const T& ac_roFill = MatrixFill< T >::DEFAULT );
    template< typename U >
    MatrixBase( const U* const* const ac_cpcpData,
                const unsigned int ac_uiRows = M,
                const unsigned int ac_uiColumns = N,
                const T& ac_roFill = MatrixFill< T >::DEFAULT );
    
    // Array access - *non-virtual* override in VectorBase child class
    T (&operator[])( unsigned int a_uiRow )[ N ];
    const T (&operator[])( unsigned int a_uiRow )[ N ];
    T& operator[]( unsigned int a_uiRow, unsigned int a_uiColumn );
    const T& operator[]( unsigned int a_uiRow, unsigned int a_uiColumn ) const;

    // Transpose - redefine in child classes to return correct type
    virtual TransposeType Transpose() const;

protected:

    // elements of the matrix
    T m_aaData[ M ][ N ];

};

// Used whenever values at a given coordinate aren't specified, as in
// constructing a matrix from another matrix with smaller dimensions.
template< typename T >
struct MatrixFill
{
    // redefine for non-numeric types
    static const T DEFAULT = 0;
};
template< typename T >
struct MatrixFill< T* >
{
    static const T* DEFAULT;
};

//
// For non-numeric types, be sure to add the following:
//
//  // YourType.h:
//  template<>
//  struct MatrixFill< YourType >
//  {
//      static const YourType DEFAULT;
//  };
//
//  // YourType.cpp:
//  const YourType MatrixFill< YourType >::DEFAULT = /* default YourType */;
//

}   // namespace Math

#endif  // _MATRIX_BASE_H_
