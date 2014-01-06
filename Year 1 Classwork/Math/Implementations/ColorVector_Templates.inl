/******************************************************************************
 * File:               ColorVector_Templates.inl
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        Template function implementations for ColorVector class.
 * Last Modified:      January 5, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef COLOR_VECTOR__TEMPLATES__INL
#define COLOR_VECTOR__TEMPLATES__INL

#include "Declarations/ColorConstants.h"
#include "Declarations/ColorVector.h"

namespace Color
{

// Constructors that forward to base class constructors
template< typename U, unsigned int Q, bool t_bOtherIsRow >
inline ColorVector::
    ColorVector( const Vector< U, Q, t_bOtherIsRow >& ac_roVector,
                 const Channel& ac_rFill )
    : BaseType( ac_roVector, ac_rFill ),
      a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) )
{
    if( Q < SIZE )
    {
        Shift( 1 );
        *this |= OPAQUE;
    }
}
template< unsigned int Q, bool t_bOtherIsRow >
inline ColorVector::
    ColorVector( Vector< Channel, Q, t_bOtherIsRow >&& a_rroVector,
                 const Channel& ac_rFill )
    : BaseType( std::forward< Vector< Channel, Q, t_bOtherIsRow > >( a_rroVector ),
                ac_rFill ),
      a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) )
{
    if( Q < SIZE )
    {
        Shift( 1 );
        *this |= OPAQUE;
    }
}
template< typename U, unsigned int Q, bool t_bOtherIsRow >
inline ColorVector::
    ColorVector( const VectorBase< U, Q, t_bOtherIsRow >& ac_roVector,
                 const Channel& ac_rFill )
    : BaseType( ac_roVector, ac_rFill ),
      a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) )
{
    if( Q < SIZE )
    {
        Shift( 1 );
        *this |= OPAQUE;
    }
}
template< unsigned int Q, bool t_bOtherIsRow >
inline ColorVector::
    ColorVector( VectorBase< Channel, Q, t_bOtherIsRow >&& a_rroVector,
                 const Channel& ac_rFill )
    : BaseType( std::forward< VectorBase< Channel, Q, t_bOtherIsRow > >( a_rroVector ),
                ac_rFill ),
      a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) )
{
    if( Q < SIZE )
    {
        Shift( 1 );
        *this |= OPAQUE;
    }
}
template< typename U, unsigned int P, unsigned int Q >
inline ColorVector::ColorVector( const MatrixBase< U, P, Q >& ac_roMatrix,
                                 const Channel& ac_rFill )
    : BaseType( ac_roMatrix, ac_rFill ),
      a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) )
{
    if( Q < SIZE )
    {
        Shift( 1 );
        *this |= OPAQUE;
    }
}
template< unsigned int P, unsigned int Q >
inline ColorVector::ColorVector( MatrixBase< Channel, P, Q >&& a_rroMatrix,
                                 const Channel& ac_rFill )
    : BaseType( std::forward< MatrixBase< Channel, P, Q > >( a_rroMatrix ),
                ac_rFill ),
      a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) )
{
    if( Q < SIZE )
    {
        Shift( 1 );
        *this |= OPAQUE;
    }
}

// Construct from vectors or matrices of floating-point types
template< unsigned int P, unsigned int Q >
inline ColorVector::ColorVector( const MatrixBase< float, P, Q >& ac_roMatrix,
                                 const Channel& ac_rFill )
    : BaseType( (Matrix< float, P, Q >)ac_roMatrix * 255.0f, ac_rFill ),
      a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) )
{
    if( Q < SIZE )
    {
        Shift( 1 );
        *this |= OPAQUE;
    }
}
template< unsigned int Q, bool t_bOtherIsRow >
inline ColorVector::
    ColorVector( const Vector< float, Q, t_bOtherIsRow >& ac_roVector,
                 const Channel& ac_rFill )
    : BaseType( ac_roVector * 255.0f, ac_rFill ),
      a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) )
{
    if( Q < SIZE )
    {
        Shift( 1 );
        *this |= OPAQUE;
    }
}
template< unsigned int Q, bool t_bOtherIsRow >
inline ColorVector::
    ColorVector( const VectorBase< float, Q, t_bOtherIsRow >& ac_roVector,
                 const Channel& ac_rFill )
    : BaseType( (Vector< float, Q, t_bOtherIsRow >)ac_roVector * 255.0f, ac_rFill ),
      a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) )
{
    if( Q < SIZE )
    {
        Shift( 1 );
        *this |= OPAQUE;
    }
}
template< unsigned int P, unsigned int Q >
inline ColorVector::ColorVector( const MatrixBase< double, P, Q >& ac_roMatrix,
                                 const Channel& ac_rFill )
    : BaseType( (Matrix< double, P, Q >)ac_roMatrix * 255.0, ac_rFill ),
      a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) )
{
    if( Q < SIZE )
    {
        Shift( 1 );
        *this |= OPAQUE;
    }
}
template< unsigned int Q, bool t_bOtherIsRow >
inline ColorVector::
    ColorVector( const Vector< double, Q, t_bOtherIsRow >& ac_roVector,
                 const Channel& ac_rFill )
    : BaseType( ac_roVector * 255.0, ac_rFill ),
      a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) )
{
    if( Q < SIZE )
    {
        Shift( 1 );
        *this |= OPAQUE;
    }
}
template< unsigned int Q, bool t_bOtherIsRow >
inline ColorVector::
    ColorVector( const VectorBase< double, Q, t_bOtherIsRow >& ac_roVector,
                 const Channel& ac_rFill )
    : BaseType( (Vector< double, Q, t_bOtherIsRow >)ac_roVector * 255.0, ac_rFill ),
      a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) )
{
    if( Q < SIZE )
    {
        Shift( 1 );
        *this |= OPAQUE;
    }
}
template< unsigned int P, unsigned int Q >
inline ColorVector::
    ColorVector( const MatrixBase< long double, P, Q >& ac_roMatrix,
                 const Channel& ac_rFill )
    : BaseType( (Matrix< long double, P, Q >)ac_roMatrix * 255.0L, ac_rFill ),
      a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) )
{
    if( Q < SIZE )
    {
        Shift( 1 );
        *this |= OPAQUE;
    }
}
template< unsigned int Q, bool t_bOtherIsRow >
inline ColorVector::
    ColorVector( const Vector< long double, Q, t_bOtherIsRow >& ac_roVector,
                 const Channel& ac_rFill )
    : BaseType( ac_roVector * 255.0L, ac_rFill ),
      a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) )
{
    if( Q < SIZE )
    {
        Shift( 1 );
        *this |= OPAQUE;
    }
}
template< unsigned int Q, bool t_bOtherIsRow >
inline ColorVector::
    ColorVector( const VectorBase< long double, Q, t_bOtherIsRow >& ac_roVector,
                 const Channel& ac_rFill )
    : BaseType( (Vector< long double, Q, t_bOtherIsRow >)ac_roVector * 255.0L, ac_rFill ),
      a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) )
{
    if( Q < SIZE )
    {
        Shift( 1 );
        *this |= OPAQUE;
    }
}

// Assign from vectors/matrices of floating-point type
template< unsigned int P, unsigned int Q >
inline ColorVector& ColorVector::
    operator=( const MatrixBase< float, P, Q >& ac_roMatrix )
{
    int iShift = ( Q < 4 ? -1 : 0 );
    Shift( iShift );
    BaseType::operator=( (Matrix< float, P, Q >)ac_roMatrix * 255.0f );
    Shift( -1 * iShift );
    return *this;
}
template< unsigned int Q, bool t_bOtherIsRow >
inline ColorVector& ColorVector::
    operator=( const Vector< float, Q, t_bOtherIsRow >& ac_roVector )
{
    int iShift = ( Q < 4 ? -1 : 0 );
    Shift( iShift );
    BaseType::operator=( ac_roVector * 255.0f );
    Shift( -1 * iShift );
    return *this;
}
template< unsigned int Q, bool t_bOtherIsRow >
inline ColorVector& ColorVector::
    operator=( const VectorBase< float, Q, t_bOtherIsRow >& ac_roVector )
{
    int iShift = ( Q < 4 ? -1 : 0 );
    Shift( iShift );
    BaseType::operator=( (Vector< float, Q, t_bOtherIsRow >)ac_roVector * 255.0f );
    Shift( -1 * iShift );
    return *this;
}
template< unsigned int P, unsigned int Q >
inline ColorVector& ColorVector::
    operator=( const MatrixBase< double, P, Q >& ac_roMatrix )
{
    int iShift = ( Q < 4 ? -1 : 0 );
    Shift( iShift );
    BaseType::operator=( (Matrix< double, P, Q >)ac_roMatrix * 255.0 );
    Shift( -1 * iShift );
    return *this;
}
template< unsigned int Q, bool t_bOtherIsRow >
inline ColorVector& ColorVector::
    operator=( const Vector< double, Q, t_bOtherIsRow >& ac_roVector )
{
    int iShift = ( Q < 4 ? -1 : 0 );
    Shift( iShift );
    BaseType::operator=( ac_roVector * 255.0 );
    Shift( -1 * iShift );
    return *this;
}
template< unsigned int Q, bool t_bOtherIsRow >
inline ColorVector& ColorVector::
    operator=( const VectorBase< double, Q, t_bOtherIsRow >& ac_roVector )
{
    int iShift = ( Q < 4 ? -1 : 0 );
    Shift( iShift );
    BaseType::operator=( (Vector< double, Q, t_bOtherIsRow >)ac_roVector * 255.0 );
    Shift( -1 * iShift );
    return *this;
}
template< unsigned int P, unsigned int Q >
inline ColorVector& ColorVector::
    operator=( const MatrixBase< long double, P, Q >& ac_roMatrix )
{
    int iShift = ( Q < 4 ? -1 : 0 );
    Shift( iShift );
    BaseType::operator=( (Matrix< long double, P, Q >)ac_roMatrix * 255.0L );
    Shift( -1 * iShift );
    return *this;
}
template< unsigned int Q, bool t_bOtherIsRow >
inline ColorVector& ColorVector::
    operator=( const Vector< long double, Q, t_bOtherIsRow >& ac_roVector )
{
    int iShift = ( Q < 4 ? -1 : 0 );
    Shift( iShift );
    BaseType::operator=( ac_roVector * 255.0L );
    Shift( -1 * iShift );
    return *this;
}
template< unsigned int Q, bool t_bOtherIsRow >
inline ColorVector& ColorVector::
    operator=( const VectorBase< long double, Q, t_bOtherIsRow >& ac_roVector )
{
    int iShift = ( Q < 4 ? -1 : 0 );
    Shift( iShift );
    BaseType::operator=( (Vector< long double, Q, t_bOtherIsRow >)ac_roVector * 255.0L );
    Shift( -1 * iShift );
    return *this;
}

// arithmatic operators for use with scalars
template< typename T >
inline ColorVector ColorVector::operator*( const T& ac_rScalar ) const
{
    return ColorVector( (Hex)(*this) * ac_rScalar );
}
template< typename T >
inline ColorVector ColorVector::operator/( const T& ac_rScalar ) const
{
    return ColorVector( (Hex)(*this) / ac_rScalar );
}
template< typename T >
inline ColorVector ColorVector::operator%( const T& ac_rScalar ) const
{
    return ColorVector( BaseType::operator%( ac_rScalar ) );
}
template< typename T >
inline ColorVector& ColorVector::operator*=( const T& ac_rScalar )
{
    *this = operator*( ac_rScalar );
    return *this;
}
template< typename T >
inline ColorVector& ColorVector::operator/=( const T& ac_rScalar )
{
    *this = operator/( ac_rScalar );
    return *this;
}
template< typename T >
inline ColorVector& ColorVector::operator%=( const T& ac_rScalar )
{
    *this = operator%( ac_rScalar );
    return *this;
}

// ColorVector scalar multiplication and division in the other direction
template< typename U >
inline Color::ColorVector
    operator*( const U& ac_rScalar, const Color::ColorVector& ac_roVector )
{
    return ac_roVector.operator*( ac_rScalar );
}
template< typename U >
inline Color::ColorVector
    operator/( const U& ac_rScalar, const Color::ColorVector& ac_roVector )
{
    return Color::ColorVector().operator*( ac_rScalar ).operator/( ac_roVector );
}

}   // namespace Color

#endif  // COLOR_VECTOR__TEMPLATES__INL