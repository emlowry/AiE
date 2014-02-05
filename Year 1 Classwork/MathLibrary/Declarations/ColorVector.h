/******************************************************************************
 * File:               ColorVector.h
 * Author:             Elizabeth Lowry
 * Date Created:       December 11, 2013
 * Description:        Vector for representing RGBA colors.
 * Last Modified:      February 5, 2014
 * Last Modification:  Refactoring.
 ******************************************************************************/

#ifndef COLOR_VECTOR__H
#define COLOR_VECTOR__H

#include "Hex.h"
#include "Vector.h"
#include "ImExportMacro.h"

namespace Color
{
// Handles RGBA colors
class IMEXPORT_CLASS ColorVector : public Math::Vector< Channel, 4 >
{
public:

    // simplify typing
    typedef Vector< Channel, SIZE, IS_ROW_VECTOR > BaseType;
    typedef BaseType::BaseType RootType;

    // destructor
    virtual ~ColorVector();

    // Constructors that forward to base class constructors
    ColorVector();
    ColorVector( const ColorVector& ac_roVector );
    ColorVector( const RootType& ac_roMatrix );
    ColorVector( ColorVector&& a_rroVector );
    template< typename U, unsigned int Q, bool t_bOtherIsRow >
    ColorVector( const Vector< U, Q, t_bOtherIsRow >& ac_roVector,
                 const Channel& ac_rFill = 0 );
    template< typename U, unsigned int P, unsigned int Q >
    ColorVector( const Matrix< U, P, Q >& ac_roMatrix,
                 const Channel& ac_rFill = 0 );
    ColorVector( const Channel& ac_rFill );
    ColorVector( const Channel (&ac_raData)[ 4 ] );
    
    // Assignment operators that pass to base class
    template< typename U, unsigned int Q, bool t_bOtherIsRow >
    ColorVector& operator=( const Vector< U, Q, t_bOtherIsRow >& ac_roVector );
    template< typename U, unsigned int P, unsigned int Q >
    ColorVector& operator=( const Matrix< U, P, Q >& ac_roMatrix );
    ColorVector& operator=( const Channel& ac_rFill );
    ColorVector& operator=( const Channel (&ac_raData)[ 4 ] );
    
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
    ColorVector operator&( const Hex& ac_roHex ) const;
    ColorVector operator|( const Hex& ac_roHex ) const;
    ColorVector operator^( const Hex& ac_roHex ) const;
    ColorVector operator<<( unsigned char a_ucBits ) const;
    ColorVector operator>>( unsigned char a_ucBits ) const;
    ColorVector& operator&=( const ColorVector& ac_roVector );
    ColorVector& operator|=( const ColorVector& ac_roVector );
    ColorVector& operator^=( const ColorVector& ac_roVector );
    ColorVector& operator&=( const Hex& ac_roHex );
    ColorVector& operator|=( const Hex& ac_roHex );
    ColorVector& operator^=( const Hex& ac_roHex );
    ColorVector& operator<<=( unsigned char a_ucBits );
    ColorVector& operator>>=( unsigned char a_ucBits );

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

// Always include template function implementations with this header
#include "Implementations/ColorVector_Templates.inl"
#ifdef INLINE_IMPLEMENTATION
#include "Implementations/ColorVector.inl"
#endif

#endif  // COLOR_VECTOR__H
