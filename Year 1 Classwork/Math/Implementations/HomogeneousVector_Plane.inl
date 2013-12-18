/******************************************************************************
 * File:               HomogeneousVector_Plane.inl
 * Author:             Elizabeth Lowry
 * Date Created:       December 18, 2013
 * Description:        Inline function implementations for 2D HomogeneousVector.
 * Last Modified:      December 18, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef HOMOGENEOUS_VECTOR__PLANE__INL
#define HOMOGENEOUS_VECTOR__PLANE__INL

namespace Plane
{

namespace Space
{

// destructor
inline HomogeneousVector::~HomogeneousVector() {}

// Constructors that forward to base class constructors
inline HomogeneousVector::HomogeneousVector()
    : BaseType(), x( At(0) ), y( At(1) ), z( At(2) ), h( At(3) )
{
    h = 1.0;
}
inline HomogeneousVector::
    HomogeneousVector( const HomogeneousVector& ac_roVector )
    : BaseType( ac_roVector ), x( At(0) ), y( At(1) ), z( At(2) ), h( At(3) ) {}
inline HomogeneousVector::HomogeneousVector( const BaseType& ac_roVector )
    : BaseType( ac_roVector ), x( At(0) ), y( At(1) ), z( At(2) ), h( At(3) ) {}
inline HomogeneousVector::
    HomogeneousVector( const VectorBaseType& ac_roVector )
    : BaseType( ac_roVector ), x( At(0) ), y( At(1) ), z( At(2) ), h( At(3) ) {}
inline HomogeneousVector::HomogeneousVector( const RootType& ac_roMatrix )
    : BaseType( ac_roMatrix ), x( At(0) ), y( At(1) ), z( At(2) ), h( At(3) ) {}
inline HomogeneousVector::HomogeneousVector( HomogeneousVector&& a_rroVector )
    : BaseType( std::forward< HomogeneousVector >( a_rroVector ) ),
      x( At(0) ), y( At(1) ), z( At(2) ), h( At(3) ) {}
inline HomogeneousVector::HomogeneousVector( BaseType&& a_rroVector )
    : BaseType( std::forward< BaseType >( a_rroVector ) ),
      x( At(0) ), y( At(1) ), z( At(2) ), h( At(3) ) {}
inline HomogeneousVector::HomogeneousVector( VectorBaseType&& a_rroVector )
    : BaseType( std::forward< VectorBaseType >( a_rroVector ) ),
      x( At(0) ), y( At(1) ), z( At(2) ), h( At(3) ) {}
inline HomogeneousVector::HomogeneousVector( RootType&& a_rroMatrix )
    : BaseType( std::forward< RootType >( a_rroMatrix ) ),
      x( At(0) ), y( At(1) ), z( At(2) ), h( At(3) ) {}
template< typename U, unsigned int Q, bool t_bOtherIsRow >
inline HomogeneousVector::
    HomogeneousVector( const Vector< U, Q, t_bOtherIsRow >& ac_roVector,
                       double a_dFill )
    : BaseType( ac_roVector, a_dFill ),
      x( At(0) ), y( At(1) ), z( At(2) ), h( At(3) ) {}
template< unsigned int Q, bool t_bOtherIsRow >
inline HomogeneousVector::
    HomogeneousVector( Vector< double, Q, t_bOtherIsRow >&& a_rroVector,
                       double a_dFill )
    : BaseType( std::forward< Vector< double, Q, t_bOtherIsRow > >( a_rroVector ),
                a_dFill ), x( At(0) ), y( At(1) ), z( At(2) ), h( At(3) ) {}
template< typename U, unsigned int Q, bool t_bOtherIsRow >
inline HomogeneousVector::
    HomogeneousVector( const VectorBase< U, Q, t_bOtherIsRow >& ac_roVector,
                       double a_dFill )
    : BaseType( ac_roVector, a_dFill ),
      x( At(0) ), y( At(1) ), z( At(2) ), h( At(3) ) {}
template< unsigned int Q, bool t_bOtherIsRow >
inline HomogeneousVector::
    HomogeneousVector( VectorBase< double, Q, t_bOtherIsRow >&& a_rroVector,
                       double a_dFill )
    : BaseType( std::forward< VectorBase< double, Q, t_bOtherIsRow > >( a_rroVector ),
                a_dFill ), x( At(0) ), y( At(1) ), z( At(2) ), h( At(3) ) {}
template< typename U, unsigned int P, unsigned int Q >
inline HomogeneousVector::
    HomogeneousVector( const MatrixBase< U, P, Q >& ac_roMatrix,
                       double a_dFill )
    : BaseType( ac_roMatrix, a_dFill ),
      x( At(0) ), y( At(1) ), z( At(2) ), h( At(3) ) {}
template< unsigned int P, unsigned int Q >
inline HomogeneousVector::
    HomogeneousVector( MatrixBase< double, P, Q >&& a_rroMatrix,
                       double a_dFill )
    : BaseType( std::forward< MatrixBase< double, P, Q > >( a_rroMatrix ),
                a_dFill ), x( At(0) ), y( At(1) ), z( At(2) ), h( At(3) ) {}
inline HomogeneousVector::HomogeneousVector( double a_dFill )
    : BaseType( a_dFill ), x( At(0) ), y( At(1) ), z( At(2) ), h( At(3) ) {}
inline HomogeneousVector::HomogeneousVector( const double (&ac_radData)[ 4 ] )
    : BaseType( ac_radData ), x( At(0) ), y( At(1) ), z( At(2) ), h( At(3) ) {}
inline HomogeneousVector::HomogeneousVector( const double* const ac_cpdData,
                                             const unsigned int ac_uiSize,
                                             double a_dFill )
    : BaseType( ac_cpdData, ac_uiSize, a_dFill ),
      x( At(0) ), y( At(1) ), z( At(2) ), h( At(3) ) {}

// Construct from the given coordinates
inline HomogeneousVector::
    HomogeneousVector( double a_dX, double a_dY, double a_dZ, double a_dH )
    : x( At(0) ), y( At(1) ), z( At(2) ), h( At(3) )
{
    x = a_dX;
    y = a_dY;
    z = a_dZ;
    h = a_dH;
}

// Construct from a 3D point or a 2D homogeneous vector
inline HomogeneousVector::
    HomogeneousVector( const PointVector& ac_roPoint, double a_dH )
    : BaseType( ac_roPoint ), x( At(0) ), y( At(1) ), z( At(2) ), h( At(3) )
{
    h = a_dH;
}
inline HomogeneousVector::
    HomogeneousVector( const Plane::HomogeneousVector& ac_roVector,
                       double a_dH )
    : BaseType( ac_roVector ), x( At(0) ), y( At(1) ), z( At(2) ), h( At(3) )
{
    h = a_dH;
}
inline HomogeneousVector::
    HomogeneousVector( const Plane::HomogeneousVector& ac_roVector,
                       double a_dH, double a_dZ )
    : BaseType( ac_roVector * ( ac_roVector.h == 0.0 ? 1.0 : a_dZ / ac_roVector.h ) ),
      x( At(0) ), y( At(1) ), z( At(2) ), h( At(3) )
{
    h = a_dH;
}

// re-implement addition and subtraction to account for h value
// this will hide all parent class addition and subtraction operators.
inline HomogeneousVector
    HomogeneousVector::operator+( const HomogeneousVector& ac_roVector ) const
{
    HomogeneousVector oArgument = ac_roVector;
    oArgument *= ( ac_roVector.h == 0.0 ? 1.0 : h / ac_roVector.h );
    return HomogeneousVector( BaseType::operator+( oArgument ) );
}
inline HomogeneousVector&
    HomogeneousVector::operator+=( const HomogeneousVector& ac_roVector )
{
    BaseType::operator+=( ac_roVector *
                          ( ac_roVector.h == 0.0 ? 1.0 : h / ac_roVector.h ) );
    return *this;
}
inline HomogeneousVector
    HomogeneousVector::operator-( const HomogeneousVector& ac_roVector ) const
{
    HomogeneousVector oArgument = ac_roVector;
    oArgument *= ( ac_roVector.h == 0.0 ? 1.0 : h / ac_roVector.h );
    return HomogeneousVector( BaseType::operator-( oArgument ) );
}
inline HomogeneousVector&
    HomogeneousVector::operator-=( const HomogeneousVector& ac_roVector )
{
    BaseType::operator-=( ac_roVector *
                          ( ac_roVector.h == 0.0 ? 1.0 : h / ac_roVector.h ) );
    return *this;
}

// Origin of the coordinate system
inline const HomogeneousVector& HomogeneousVector::Origin()
{
    static HomogeneousVector oOrigin;
    return oOrigin;
}

}   // namespace Space

#endif  // HOMOGENEOUS_VECTOR__PLANE__INL
