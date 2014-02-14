/******************************************************************************
 * File:               ColorVector_Templates.inl
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        Template function implementations for ColorVector class.
 * Last Modified:      January 5, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

#ifndef COLOR_VECTOR__TEMPLATES__INL
#define COLOR_VECTOR__TEMPLATES__INL

#include "../Declarations/ColorConstants.h"
#include "../Declarations/ColorVector.h"

namespace Color
{

// Constructors that forward to base class constructors
template< typename U, unsigned int Q, bool t_bOtherIsRow >
inline ColorVector::
    ColorVector( const Vector< U, Q, t_bOtherIsRow >& ac_roVector,
                 const Channel& ac_rFill )
    : BaseType( ac_roVector, ac_rFill ),
      a( m_aaData[0][0] ),
      r( m_aaData[0][1] ),
      g( m_aaData[0][2] ),
      b( m_aaData[0][3] )
{
    if( Q < SIZE )
    {
        Shift( 1 );
        *this |= OPAQUE;
    }
}
template< typename U, unsigned int P, unsigned int Q >
inline ColorVector::ColorVector( const Matrix< U, P, Q >& ac_roMatrix,
                                 const Channel& ac_rFill )
    : BaseType( ac_roMatrix, ac_rFill ),
      a( m_aaData[0][0] ),
      r( m_aaData[0][1] ),
      g( m_aaData[0][2] ),
      b( m_aaData[0][3] )
{
    if( Q < SIZE )
    {
        Shift( 1 );
        *this |= OPAQUE;
    }
}

// Assignment operators that pass to base class
template< typename U, unsigned int Q, bool t_bOtherIsRow >
inline ColorVector& ColorVector::
    operator=( const Vector< U, Q, t_bOtherIsRow >& ac_roVector )
{
    BaseType::operator=( ac_roVector );
    return *this;
}
template< typename U, unsigned int P, unsigned int Q >
inline ColorVector& ColorVector::
    operator=( const Matrix< U, P, Q >& ac_roMatrix )
{
    BaseType::operator=( ac_roMatrix );
    return *this;
}

}   // namespace Color

#endif  // COLOR_VECTOR__TEMPLATES__INL