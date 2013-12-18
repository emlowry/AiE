/******************************************************************************
 * File:               ColorVectorConstructors.h
 * Author:             Elizabeth Lowry
 * Date Created:       December 16, 2013
 * Description:        Destructor and constructors for color vector class.
 * Last Modified:      December 16, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef COLOR_VECTOR__CONSTRUCTORS__INL
#define COLOR_VECTOR__CONSTRUCTORS__INL

#include "Declarations/ColorConstants.h"

namespace Color
{

// Destructor does nothing
inline ColorVector::~ColorVector() {}

// Constructors that forward to base class constructors
inline ColorVector::ColorVector()
    : BaseType( 0xFF ), a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) ) {}
inline ColorVector::ColorVector( const ColorVector& ac_roVector )
    : BaseType( ac_roVector ), a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) ) {}
inline ColorVector::ColorVector( const BaseType& ac_roVector )
    : BaseType( ac_roVector ), a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) ) {}
inline ColorVector::ColorVector( const VectorBaseType& ac_roVector )
    : BaseType( ac_roVector ), a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) ) {}
inline ColorVector::ColorVector( const RootType& ac_roMatrix )
    : BaseType( ac_roMatrix ), a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) ) {}
inline ColorVector::ColorVector( ColorVector&& a_rroVector )
    : BaseType( std::forward< ColorVector >( a_rroVector ) ),
      a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) ) {}
inline ColorVector::ColorVector( BaseType&& a_rroVector )
    : BaseType( std::forward< BaseType >( a_rroVector ) ),
      a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) ) {}
inline ColorVector::ColorVector( VectorBaseType&& a_rroVector )
    : BaseType( std::forward< VectorBaseType >( a_rroVector ) ),
      a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) ) {}
inline ColorVector::ColorVector( RootType&& a_rroMatrix )
    : BaseType( std::forward< RootType >( a_rroMatrix ) ),
      a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) ) {}
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
inline ColorVector::ColorVector( const Channel& ac_rFill )
    : BaseType( ac_rFill ), a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) ) {}
inline ColorVector::ColorVector( const Channel (&ac_raData)[ 4 ] )
    : BaseType( ac_raData ), a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) ) {}
inline ColorVector::ColorVector( const Channel* const ac_cpData,
                                 const unsigned int ac_uiSize,
                                 const Channel& ac_rFill )
    : BaseType( ac_cpData, ac_uiSize, ac_rFill ),
      a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) ) {}

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

// Construct from hex value
inline ColorVector::ColorVector( Channel a_ucRed,
                                 Channel a_ucGreen,
                                 Channel a_ucBlue,
                                 Channel a_ucAlpha )
    : a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) )
{
    a = a_ucAlpha;
    r = a_ucRed;
    g = a_ucGreen;
    b = a_ucBlue;
}
inline ColorVector::ColorVector( float a_fRed,
                                 float a_fGreen,
                                 float a_fBlue,
                                 float a_fAlpha )
    : a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) )
{
    a = (Channel)( a_fAlpha * 0xFF );
    r = (Channel)( a_fRed * 0xFF );
    g = (Channel)( a_fGreen * 0xFF );
    b = (Channel)( a_fBlue * 0xFF );
}
inline ColorVector::ColorVector( FourChannelInt a_uiHex )
    : a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) )
{
    a = Hex(a_uiHex).a;
    r = Hex(a_uiHex).r;
    g = Hex(a_uiHex).g;
    b = Hex(a_uiHex).b;
}
inline ColorVector::ColorVector( const Hex& ac_rHex )
    : a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) )
{
    a = ac_rHex.a;
    r = ac_rHex.r;
    g = ac_rHex.g;
    b = ac_rHex.b;
}

}   // namespace Color

#endif  // COLOR_VECTOR__CONSTRUCTORS__INL
