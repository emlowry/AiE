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
    : ColorVector( WHITE ) {}
inline ColorVector::ColorVector( const ColorVector& ac_roVector )
    : BaseType( ac_roVector ), a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) ) {}
inline ColorVector::ColorVector( const BaseType& ac_roVector )
    : BaseType( ac_roVector ), a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) ) {}
inline ColorVector::ColorVector( const VectorBaseType& ac_roVector )
    : BaseType( ac_roVector ), a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) ) {}
inline ColorVector::ColorVector( const RootType& ac_roMatrix )
    : BaseType( ac_roVector ), a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) ) {}
inline ColorVector::ColorVector( ColorVector&& a_rroVector )
    : BaseType( std::forward( a_rroVector ) ),
      a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) ) {}
inline ColorVector::ColorVector( BaseType&& a_rroVector )
    : BaseType( std::forward( a_rroVector ) ),
      a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) ) {}
inline ColorVector::ColorVector( VectorBaseType&& a_rroVector )
    : BaseType( std::forward( a_rroVector ) ),
      a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) ) {}
inline ColorVector::ColorVector( RootType&& a_rroMatrix )
    : BaseType( std::forward( a_rroMatrix ) ),
      a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) ) {}
template< unsigned int Q, bool t_bOtherIsRow >
inline ColorVector::
    ColorVector( const Vector< Channel, Q, t_bOtherIsRow >& ac_roVector,
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
    ColorVector( const VectorBase< Channel, Q, t_bOtherIsRow >& ac_roVector,
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
template< typename U >
inline ColorVector::ColorVector( const MatrixBase< U, 1, 4 >& ac_roMatrix )
    : BaseType( ac_roMatrix ) {}
template< unsigned int P, unsigned int Q >
inline ColorVector::ColorVector( const MatrixBase< Channel, P, Q >& ac_roMatrix,
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
template<>
inline ColorVector::ColorVector( const MatrixBase< float, 1, 4 >& ac_roMatrix )
    : BaseType( ac_roMatrix * 255.0f ),
      a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) ) {}
template< unsigned int P, unsigned int Q >
inline ColorVector::ColorVector( const MatrixBase< float, P, Q >& ac_roMatrix,
                                 const Channel& ac_rFill )
    : BaseType( ac_roMatrix * 255.0f, ac_rFill ),
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
    : BaseType( ac_roVector * 255.0f, ac_rFill ),
      a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) )
{
    if( Q < SIZE )
    {
        Shift( 1 );
        *this |= OPAQUE;
    }
}
template<>
inline ColorVector::
    ColorVector( const MatrixBase< double, 1, 4 >& ac_roMatrix )
    : BaseType( ac_roMatrix * 255.0 ),
      a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) ) {}
template< unsigned int P, unsigned int Q >
inline ColorVector::ColorVector( const MatrixBase< double, P, Q >& ac_roMatrix,
                                 const Channel& ac_rFill )
    : BaseType( ac_roMatrix * 255.0, ac_rFill ),
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
    : BaseType( ac_roVector * 255.0, ac_rFill ),
      a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) )
{
    if( Q < SIZE )
    {
        Shift( 1 );
        *this |= OPAQUE;
    }
}
template<>
inline ColorVector::
    ColorVector( const MatrixBase< long double, 1, 4 >& ac_roMatrix )
    : BaseType( ac_roMatrix * 255.0L ),
      a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) ) {}
template< unsigned int P, unsigned int Q >
inline ColorVector::
    ColorVector( const MatrixBase< long double, P, Q >& ac_roMatrix,
                 const Channel& ac_rFill )
    : BaseType( ac_roMatrix * 255.0L, ac_rFill ),
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
    : BaseType( ac_roVector * 255.0L, ac_rFill ),
      a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) )
{
    if( Q < SIZE )
    {
        Shift( 1 );
        *this |= OPAQUE;
    }
}

// Construct from hex value
inline ColorVector::ColorVector( Channel a_uiRed,
                                 Channel a_uiGreen,
                                 Channel a_uiBlue,
                                 Channel a_uiAlpha = 0xFF )
    : ColorVector( Hex( a_uiRed, a_uiGreen, a_uiBlue, a_uiAlpha ) ) {}
inline ColorVector::ColorVector( float a_fRed,
                                 float a_fGreen,
                                 float a_fBlue,
                                 float a_fAlpha = 1.0 )
    : ColorVector( Hex( a_fRed, a_fGreen, a_fBlue, a_fAlpha ) ) {}
inline ColorVector::ColorVector( FourChannelInt a_uiHex )
    : ColorVector( Hex( a_uiHex ) ) {}
inline ColorVector::ColorVector( const Hex& ac_rHex )
    : m_aaData( { { ac_rHex.a, ac_rHex.r, ac_rHex.g, ac_rHex.b } } ),
      a( At(0) ), r( At(1) ), g( At(2) ), b( At(3) ) {}

}   // namespace Color

#endif  // COLOR_VECTOR__CONSTRUCTORS__INL
