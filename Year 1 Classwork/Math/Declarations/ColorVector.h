/******************************************************************************
 * File:               ColorVector.h
 * Author:             Elizabeth Lowry
 * Date Created:       December 11, 2013
 * Description:        Vector for representing RGBA colors.
 * Last Modified:      December 11, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef COLOR_VECTOR__H
#define COLOR_VECTOR__H

#include "Hex.h"
#include "Vector.h"

namespace Color
{
// Handles RGB colors (no transparency)
class ColorVector : public Math::Vector< Channel, 4 >
{
public:

    // simplify typing
    typedef Vector< Channel, 4 > BaseType;
    typedef BaseType::RootType RootType;
    typedef BaseType::BaseType VectorBaseType;
    typedef BaseType::InverseType InverseType;

    // inherit assignment operators
    using BaseType::operator=;
    
    // destructor
    virtual ~ColorVector();

    // Constructors that forward to base class constructors
    ColorVector();
    ColorVector( const ColorVector& ac_roVector );
    ColorVector( const BaseType& ac_roVector );
    ColorVector( const VectorBaseType& ac_roVector );
    ColorVector( const RootType& ac_roMatrix );
    ColorVector( ColorVector&& a_rroVector );
    ColorVector( BaseType&& a_rroVector );
    ColorVector( VectorBaseType&& a_rroVector );
    ColorVector( RootType&& a_rroMatrix );
    template< typename U, unsigned int Q, bool t_bOtherIsRow >
    ColorVector( const Vector< U, Q, t_bOtherIsRow >& ac_roVector,
                 const Channel& ac_rFill = 0 );
    template< unsigned int Q, bool t_bOtherIsRow >
    ColorVector( Vector< Channel, Q, t_bOtherIsRow >&& a_rroVector,
                 const Channel& ac_rFill = 0 );
    template< typename U, unsigned int Q, bool t_bOtherIsRow >
    ColorVector( const VectorBase< U, Q, t_bOtherIsRow >& ac_roVector,
                 const Channel& ac_rFill = 0 );
    template< unsigned int Q, bool t_bOtherIsRow >
    ColorVector( VectorBase< Channel, Q, t_bOtherIsRow >&& a_rroVector,
                 const Channel& ac_rFill = 0 );
    template< typename U, unsigned int P, unsigned int Q >
    ColorVector( const MatrixBase< U, P, Q >& ac_roMatrix,
                 const Channel& ac_rFill = 0 );
    template< unsigned int P, unsigned int Q >
    ColorVector( MatrixBase< Channel, P, Q >&& a_rroMatrix,
                 const Channel& ac_rFill = 0 );
    ColorVector( const Channel& ac_rFill );
    ColorVector( const Channel (&ac_raData)[ 4 ] );
    ColorVector( const Channel* const ac_cpData,
                 const unsigned int ac_uiSize,
                 const Channel& ac_rFill = 0 );

    // Construct from vectors or matrices of floating-point types
    template< unsigned int P, unsigned int Q >
    ColorVector( const MatrixBase< float, P, Q >& ac_roMatrix,
                 const Channel& ac_rFill = 0 );
    template< unsigned int Q, bool t_bOtherIsRow >
    ColorVector( const Vector< float, Q, t_bOtherIsRow >& ac_roVector,
                 const Channel& ac_rFill = 0 );
    template< unsigned int Q, bool t_bOtherIsRow >
    ColorVector( const VectorBase< float, Q, t_bOtherIsRow >& ac_roVector,
                 const Channel& ac_rFill = 0 );
    template< unsigned int P, unsigned int Q >
    ColorVector( const MatrixBase< double, P, Q >& ac_roMatrix,
                 const Channel& ac_rFill = 0 );
    template< unsigned int Q, bool t_bOtherIsRow >
    ColorVector( const Vector< double, Q, t_bOtherIsRow >& ac_roVector,
                 const Channel& ac_rFill = 0 );
    template< unsigned int Q, bool t_bOtherIsRow >
    ColorVector( const VectorBase< double, Q, t_bOtherIsRow >& ac_roVector,
                 const Channel& ac_rFill = 0 );
    template< unsigned int P, unsigned int Q >
    ColorVector( const MatrixBase< long double, P, Q >& ac_roMatrix,
                 const Channel& ac_rFill = 0 );
    template< unsigned int Q, bool t_bOtherIsRow >
    ColorVector( const Vector< long double, Q, t_bOtherIsRow >& ac_roVector,
                 const Channel& ac_rFill = 0 );
    template< unsigned int Q, bool t_bOtherIsRow >
    ColorVector( const VectorBase< long double, Q, t_bOtherIsRow >& ac_roVector,
                 const Channel& ac_rFill = 0 );

    // Assign from vectors/matrices of floating-point type
    template< unsigned int P, unsigned int Q >
    ColorVector& operator=( const MatrixBase< float, P, Q >& ac_roMatrix );
    template< unsigned int Q, bool t_bOtherIsRow >
    ColorVector&
        operator=( const Vector< float, Q, t_bOtherIsRow >& ac_roVector );
    template< unsigned int Q, bool t_bOtherIsRow >
    ColorVector&
        operator=( const VectorBase< float, Q, t_bOtherIsRow >& ac_roVector );
    template< unsigned int P, unsigned int Q >
    ColorVector& operator=( const MatrixBase< double, P, Q >& ac_roMatrix );
    template< unsigned int Q, bool t_bOtherIsRow >
    ColorVector&
        operator=( const Vector< double, Q, t_bOtherIsRow >& ac_roVector );
    template< unsigned int Q, bool t_bOtherIsRow >
    ColorVector&
        operator=( const VectorBase< double, Q, t_bOtherIsRow >& ac_roVector );
    template< unsigned int P, unsigned int Q >
    ColorVector&
        operator=( const MatrixBase< long double, P, Q >& ac_roMatrix );
    template< unsigned int Q, bool t_bOtherIsRow >
    ColorVector&
        operator=( const Vector< long double, Q, t_bOtherIsRow >& ac_roVector );
    template< unsigned int Q, bool t_bOtherIsRow >
    ColorVector&
        operator=( const VectorBase< long double, Q, t_bOtherIsRow >& ac_roVector );

    // Construct/assign from or convert to hex value
    ColorVector( Channel a_ucRed,
                 Channel a_ucGreen,
                 Channel a_ucBlue,
                 Channel a_ucAlpha = 0xFF );
    ColorVector( float a_fRed,
                 float a_fGreen,
                 float a_fBlue,
                 float a_fAlpha = 1.0 );
    ColorVector( FourChannelInt a_uiHex );
    ColorVector( const Hex& ac_rHex );
    ColorVector& operator=( FourChannelInt a_uiHex );
    ColorVector& operator=( const Hex& ac_rHex );
    operator Hex() const;

    // Bitwise operators
    ColorVector operator~() const;
    ColorVector operator&( const ColorVector& ac_roVector ) const;
    ColorVector operator|( const ColorVector& ac_roVector ) const;
    ColorVector operator^( const ColorVector& ac_roVector ) const;
    ColorVector& operator&=( const ColorVector& ac_roVector );
    ColorVector& operator|=( const ColorVector& ac_roVector );
    ColorVector& operator^=( const ColorVector& ac_roVector );
    ColorVector operator&( const Hex& ac_rHex ) const;
    ColorVector operator|( const Hex& ac_rHex ) const;
    ColorVector operator^( const Hex& ac_rHex ) const;
    ColorVector& operator&=( const Hex& ac_rHex );
    ColorVector& operator|=( const Hex& ac_rHex );
    ColorVector& operator^=( const Hex& ac_rHex );

    // inherit regular arithmatic operators
    using BaseType::operator+;
    using BaseType::operator+=;
    using BaseType::operator-;
    using BaseType::operator-=;
    using BaseType::operator*;
    using BaseType::operator*=;
    using BaseType::operator/;
    using BaseType::operator/=;

    // arithmatic operators for use with scalars
    template< typename T >
    ColorVector operator*( const T& ac_rScalar ) const;
    template< typename T >
    ColorVector operator/( const T& ac_rScalar ) const;
    template< typename T >
    ColorVector operator%( const T& ac_rScalar ) const;
    template< typename T >
    ColorVector& operator*=( const T& ac_rScalar );
    template< typename T >
    ColorVector& operator/=( const T& ac_rScalar );
    template< typename T >
    ColorVector& operator%=( const T& ac_rScalar );

    // arithmatic operators for use with other color vectors
    ColorVector operator+( const ColorVector& ac_roVector ) const;
    ColorVector operator-( const ColorVector& ac_roVector ) const;
    ColorVector operator*( const ColorVector& ac_roVector ) const;
    ColorVector operator/( const ColorVector& ac_roVector ) const;
    ColorVector& operator+=( const ColorVector& ac_roVector );
    ColorVector& operator-=( const ColorVector& ac_roVector );
    ColorVector& operator*=( const ColorVector& ac_roVector );
    ColorVector& operator/=( const ColorVector& ac_roVector );

    // arithmatic operators for use with color hexes
    ColorVector operator+( const Hex& ac_rHex ) const;
    ColorVector operator-( const Hex& ac_rHex ) const;
    ColorVector operator*( const Hex& ac_rHex ) const;
    ColorVector operator/( const Hex& ac_rHex ) const;
    ColorVector& operator+=( const Hex& ac_rHex );
    ColorVector& operator-=( const Hex& ac_rHex );
    ColorVector& operator*=( const Hex& ac_rHex );
    ColorVector& operator/=( const Hex& ac_rHex );

    // Return rgb values as floats
    float fAlpha() const;
    float fRed() const;
    float fGreen() const;
    float fBlue() const;

    // rgb value access
    Channel& a; // m_aaData[0][0]
    Channel& r; // m_aaData[0][1]
    Channel& g; // m_aaData[0][2]
    Channel& b; // m_aaData[0][3]

};

}   // namespace Color

// ColorVector scalar multiplication and division in the other direction
template< typename U >
Color::ColorVector
    operator*( const U& ac_roScalar, const Color::ColorVector ac_roVector );
template< typename U >
Color::ColorVector
    operator/( const U& ac_roScalar, const Color::ColorVector ac_roVector );

#include "Implementations/ColorVector.inl"

#endif  // COLOR_VECTOR__H
