/******************************************************************************
 * File:               ColorVector_Templates.inl
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        Template function implementations for ColorVector class.
 * Last Modified:      February 25, 2014
 * Last Modification:  Changed from 8-bit channel to float.
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
                 float a_fFill )
    : BaseType( ac_roVector, a_fFill ),
      r( m_aaData[0][0] ),
      g( m_aaData[0][1] ),
      b( m_aaData[0][2] ),
      a( m_aaData[0][3] ) {}
template< typename U, unsigned int P, unsigned int Q >
inline ColorVector::ColorVector( const Matrix< U, P, Q >& ac_roMatrix,
                                 float a_fFill )
    : BaseType( ac_roMatrix, a_fFill ),
      r( m_aaData[0][0] ),
      g( m_aaData[0][1] ),
      b( m_aaData[0][2] ),
      a( m_aaData[0][3] ) {}

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