/******************************************************************************
 * File:               HomogeneousVector_Templates.inl
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        Template function implementations for HomogeneousVector.
 * Last Modified:      January 5, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef HOMOGENEOUS_VECTOR__TEMPLATES__INL
#define HOMOGENEOUS_VECTOR__TEMPLATES__INL

#include "Declarations/HomogeneousVector.h"
#include "Declarations/PointVector.h"

namespace Plane
{

// Constructors that forward to base class constructors
template< typename U, unsigned int Q, bool t_bOtherIsRow >
inline HomogeneousVector::
    HomogeneousVector( const Vector< U, Q, t_bOtherIsRow >& ac_roVector,
                       double a_dFill )
    : BaseType( ac_roVector, a_dFill ),
      x( At(0) ), y( At(1) ), h( At(2) ) {}
template< unsigned int Q, bool t_bOtherIsRow >
inline HomogeneousVector::
    HomogeneousVector( Vector< double, Q, t_bOtherIsRow >&& a_rroVector,
                       double a_dFill )
    : BaseType( std::forward< Vector< double, Q, t_bOtherIsRow > >( a_rroVector ),
                a_dFill ), x( At(0) ), y( At(1) ), h( At(2) ) {}
template< typename U, unsigned int Q, bool t_bOtherIsRow >
inline HomogeneousVector::
    HomogeneousVector( const VectorBase< U, Q, t_bOtherIsRow >& ac_roVector,
                       double a_dFill )
    : BaseType( ac_roVector, a_dFill ), x( At(0) ), y( At(1) ), h( At(2) ) {}
template< unsigned int Q, bool t_bOtherIsRow >
inline HomogeneousVector::
    HomogeneousVector( VectorBase< double, Q, t_bOtherIsRow >&& a_rroVector,
                       double a_dFill )
    : BaseType( std::forward< VectorBase< double, Q, t_bOtherIsRow > >( a_rroVector ),
                a_dFill ), x( At(0) ), y( At(1) ), h( At(2) ) {}
template< typename U, unsigned int P, unsigned int Q >
inline HomogeneousVector::
    HomogeneousVector( const MatrixBase< U, P, Q >& ac_roMatrix,
                       double a_dFill )
    : BaseType( ac_roMatrix, a_dFill ), x( At(0) ), y( At(1) ), h( At(2) ) {}
template< unsigned int P, unsigned int Q >
inline HomogeneousVector::
    HomogeneousVector( MatrixBase< double, P, Q >&& a_rroMatrix,
                       double a_dFill )
    : BaseType( std::forward< MatrixBase< double, P, Q > >( a_rroMatrix ),
                a_dFill ), x( At(0) ), y( At(1) ), h( At(2) ) {}

// Scalar multiplication, division, and modulo
template< typename T >
inline HomogeneousVector HomogeneousVector::operator*( const T& ac_rScalar ) const
{
    HomogeneousVector oResult = BaseType::operator*( ac_rScalar );
    oResult.h = h;
    return oResult;
}
template< typename T >
inline HomogeneousVector& HomogeneousVector::operator*=( const T& ac_rScalar )
{
    double dH = h;
    BaseType::operator*=( ac_rScalar );
    h = dH;
    return *this;
}
template< typename T >
inline HomogeneousVector HomogeneousVector::operator/( const T& ac_rScalar ) const
{
    HomogeneousVector oResult = BaseType::operator/( ac_rScalar );
    oResult.h = h;
    return oResult;
}
template< typename T >
inline HomogeneousVector& HomogeneousVector::operator/=( const T& ac_rScalar )
{
    double dH = h;
    BaseType::operator/=( ac_rScalar );
    h = dH;
    return *this;
}
template< typename T >
inline HomogeneousVector HomogeneousVector::operator%( const T& ac_rScalar ) const
{
    HomogeneousVector oResult = BaseType::operator%( ac_rScalar );
    oResult.h = h;
    return oResult;
}
template< typename T >
inline HomogeneousVector& HomogeneousVector::operator%=( const T& ac_rScalar )
{
    double dH = h;
    BaseType::operator%=( ac_rScalar );
    h = dH;
    return *this;
}

// Matrix multiplication and division
template< unsigned int N >
inline Math::Matrix< double, 1, N > HomogeneousVector::
    operator*( const Math::Matrix< double, 3, N >& ac_roMatrix ) const
{
    HomogeneousVector oCopy( *this );
    return oCopy.Homoginize().BaseType::operator*( ac_roMatrix );
}
template< unsigned int N >
inline Math::Matrix< double, 1, N > HomogeneousVector::
    operator/( const Math::Matrix< double, N, 3 >& ac_roMatrix ) const
{
    HomogeneousVector oCopy( *this );
    return oCopy.Homoginize().BaseType::operator/( ac_roMatrix );
}

}   // namespace Plane

// Vector scalar multiplication and division in the other direction
template< typename U >
inline Plane::HomogeneousVector
    operator*( const U& ac_rScalar,
               const Plane::HomogeneousVector& ac_roVector )
{
    return ac_roVector.operator*( ac_rScalar );
}
template< typename U >
inline Plane::HomogeneousVector
    operator/( const U& ac_rScalar,
               const Plane::HomogeneousVector& ac_roVector )
{
    if( !( Plane::PointVector( ac_roVector ).IsInvertable() ) )
    {
        throw std::invalid_argument( "Cannot divide by a non-invertable matrix" );
    }
    return Plane::HomogeneousVector(
        Plane::PointVector( ac_roVector ).Inverse().operator*( ac_rScalar ) );
}

namespace Space
{

// Constructors that forward to base class constructors
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

// Scalar multiplication, division, and modulo
template< typename T >
inline HomogeneousVector HomogeneousVector::operator*( const T& ac_rScalar ) const
{
    HomogeneousVector oResult = BaseType::operator*( ac_rScalar );
    oResult.h = h;
    return oResult;
}
template< typename T >
inline HomogeneousVector& HomogeneousVector::operator*=( const T& ac_rScalar )
{
    double dH = h;
    BaseType::operator*=( ac_rScalar );
    h = dH;
    return *this;
}
template< typename T >
inline HomogeneousVector HomogeneousVector::operator/( const T& ac_rScalar ) const
{
    HomogeneousVector oResult = BaseType::operator/( ac_rScalar );
    oResult.h = h;
    return oResult;
}
template< typename T >
inline HomogeneousVector& HomogeneousVector::operator/=( const T& ac_rScalar )
{
    double dH = h;
    BaseType::operator/=( ac_rScalar );
    h = dH;
    return *this;
}
template< typename T >
inline HomogeneousVector HomogeneousVector::operator%( const T& ac_rScalar ) const
{
    HomogeneousVector oResult = BaseType::operator%( ac_rScalar );
    oResult.h = h;
    return oResult;
}
template< typename T >
inline HomogeneousVector& HomogeneousVector::operator%=( const T& ac_rScalar )
{
    double dH = h;
    BaseType::operator%=( ac_rScalar );
    h = dH;
    return *this;
}

// Matrix multiplication and division
template< unsigned int N >
inline Math::Matrix< double, 1, N > HomogeneousVector::
    operator*( const Math::Matrix< double, 4, N >& ac_roMatrix ) const
{
    HomogeneousVector oCopy( *this );
    return oCopy.Homoginize().BaseType::operator*( ac_roMatrix );
}
template< unsigned int N >
inline Math::Matrix< double, 1, N > HomogeneousVector::
    operator/( const Math::Matrix< double, N, 4 >& ac_roMatrix ) const
{
    HomogeneousVector oCopy( *this );
    return oCopy.Homoginize().BaseType::operator/( ac_roMatrix );
}

}   // namespace Space

// Vector scalar multiplication and division in the other direction
template< typename U >
inline Space::HomogeneousVector
    operator*( const U& ac_rScalar,
               const Space::HomogeneousVector& ac_roVector )
{
    return ac_roVector.operator*( ac_rScalar );
}
template< typename U >
inline Space::HomogeneousVector
    operator/( const U& ac_rScalar,
               const Space::HomogeneousVector& ac_roVector )
{
    if( !( Space::PointVector( ac_roVector ).IsInvertable() ) )
    {
        throw std::invalid_argument( "Cannot divide by a non-invertable matrix" );
    }
    return Space::HomogeneousVector(
        Space::PointVector( ac_roVector ).Inverse().operator*( ac_rScalar ) );
}

#endif  // HOMOGENEOUS_VECTOR__TEMPLATES__INL