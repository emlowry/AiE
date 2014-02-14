/******************************************************************************
 * File:               HomogeneousVector_Templates.inl
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        Template function implementations for HomogeneousVector.
 * Last Modified:      February 10, 2014
 * Last Modification:  Templatizing PointVector.
 ******************************************************************************/

#ifndef HOMOGENEOUS_VECTOR__TEMPLATES__INL
#define HOMOGENEOUS_VECTOR__TEMPLATES__INL

#include "../Declarations/HomogeneousVector.h"

namespace Plane
{

// Constructors that forward to base class constructors
template< typename U, unsigned int Q, bool t_bOtherIsRow >
inline HomogeneousVector::
    HomogeneousVector( const Vector< U, Q, t_bOtherIsRow >& ac_roVector,
                       double a_dFill )
    : BaseType( ac_roVector, a_dFill ),
      x( m_aaData[0][0] ), y( m_aaData[0][1] ), h( m_aaData[0][2] )
{
    if( Q < 3 )
    {
        h = 1.0;
    }
}
template< typename U, unsigned int P, unsigned int Q >
inline HomogeneousVector::
    HomogeneousVector( const Matrix< U, P, Q >& ac_roMatrix,
                       double a_dFill )
    : BaseType( ac_roMatrix, a_dFill ),
      x( m_aaData[0][0] ), y( m_aaData[0][1] ), h( m_aaData[0][2] )
{
    if( Q < 3 )
    {
        h = 1.0;
    }
}

// Assignment operators that pass to base class
template< typename U, unsigned int Q, bool t_bOtherIsRow >
inline HomogeneousVector& HomogeneousVector::
    operator=( const Vector< U, Q, t_bOtherIsRow >& ac_roVector )
{
    BaseType::operator=( ac_roVector );
    return *this;
}
template< typename U, unsigned int P, unsigned int Q >
inline HomogeneousVector& HomogeneousVector::
    operator=( const Matrix< U, P, Q >& ac_roMatrix )
{
    BaseType::operator=( ac_roMatrix );
    return *this;
}

// override matrix multiplication to homogenize first
template< unsigned int P >
inline typename std::conditional< P == 3, HomogeneousVector,
                                          Math::Vector< double, P > >::type
    HomogeneousVector::
    operator*( const Math::Matrix< double, 3, P >& ac_roMatrix ) const
{
    HomogeneousVector oCopy( *this );
    if( P == 3 )
    {
        return oCopy.operator*=( ac_roMatrix );
    }
    typedef typename std::conditional< P == 3, HomogeneousVector,
                                               Math::Vector< double, P > >::type
            ResultType;
    return ResultType( oCopy.Homogenize().BaseType::operator*( ac_roMatrix ) );
}
template< unsigned int P >
inline typename std::conditional< P == 3, HomogeneousVector,
                                          Math::Vector< double, P > >::type
    HomogeneousVector::
    operator/( const Math::Matrix< double, P, 3 >& ac_roMatrix ) const
{
    HomogeneousVector oCopy( *this );
    if( P == 3 )
    {
        return oCopy.operator*=( ac_roMatrix );
    }
    typedef typename std::conditional< P == 3, HomogeneousVector,
                                               Math::Vector< double, P > >::type
            ResultType;
    return ResultType( oCopy.Homogenize().BaseType::operator/( ac_roMatrix ) );
}

}   // namespace Plane

namespace Space
{

// Constructors that forward to base class constructors
template< typename U, unsigned int Q, bool t_bOtherIsRow >
inline HomogeneousVector::
    HomogeneousVector( const Vector< U, Q, t_bOtherIsRow >& ac_roVector,
                       double a_dFill )
    : BaseType( ac_roVector, a_dFill ),
      x( m_aaData[0][0] ),
      y( m_aaData[0][1] ),
      z( m_aaData[0][2] ),
      h( m_aaData[0][3] )
{
    if( Q < 4 )
    {
        h = 1.0;
    }
}
template< typename U, unsigned int P, unsigned int Q >
inline HomogeneousVector::
    HomogeneousVector( const Matrix< U, P, Q >& ac_roMatrix,
                       double a_dFill )
    : BaseType( ac_roMatrix, a_dFill ),
      x( m_aaData[0][0] ),
      y( m_aaData[0][1] ),
      z( m_aaData[0][2] ),
      h( m_aaData[0][3] )
{
    if( Q < 4 )
    {
        h = 1.0;
    }
}

// Assignment operators that pass to base class
template< typename U, unsigned int Q, bool t_bOtherIsRow >
inline HomogeneousVector& HomogeneousVector::
    operator=( const Vector< U, Q, t_bOtherIsRow >& ac_roVector )
{
    BaseType::operator=( ac_roVector );
    return *this;
}
template< typename U, unsigned int P, unsigned int Q >
inline HomogeneousVector& HomogeneousVector::
    operator=( const Matrix< U, P, Q >& ac_roMatrix )
{
    BaseType::operator=( ac_roMatrix );
    return *this;
}

// override matrix multiplication to homogenize first
template< unsigned int P >
inline typename std::conditional< P == 4, HomogeneousVector,
                                          Math::Vector< double, P > >::type
    HomogeneousVector::
    operator*( const Math::Matrix< double, 4, P >& ac_roMatrix ) const
{
    HomogeneousVector oCopy( *this );
    if( P == 4 )
    {
        return oCopy.operator*=( ac_roMatrix );
    }
    typedef typename std::conditional< P == 4, HomogeneousVector,
                                               Math::Vector< double, P > >::type
            ResultType;
    return ResultType( oCopy.Homogenize().BaseType::operator*( ac_roMatrix ) );
}
template< unsigned int P >
inline typename std::conditional< P == 4, HomogeneousVector,
                                          Math::Vector< double, P > >::type
    HomogeneousVector::
    operator/( const Math::Matrix< double, P, 4 >& ac_roMatrix ) const
{
    HomogeneousVector oCopy( *this );
    if( P == 4 )
    {
        return oCopy.operator*=( ac_roMatrix );
    }
    typedef typename std::conditional< P == 4, HomogeneousVector,
                                               Math::Vector< double, P > >::type
            ResultType;
    return ResultType( oCopy.Homogenize().BaseType::operator/( ac_roMatrix ) );
}

}   // namespace Space

#endif  // HOMOGENEOUS_VECTOR__TEMPLATES__INL