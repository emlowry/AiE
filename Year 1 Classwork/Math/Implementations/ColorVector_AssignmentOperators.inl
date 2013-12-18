/******************************************************************************
 * File:               ColorVector_AssignmentOperators.h
 * Author:             Elizabeth Lowry
 * Date Created:       December 16, 2013
 * Description:        Assignment operators for the ColorVector class.
 * Last Modified:      December 16, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef COLOR_VECTOR__ASSIGNMENT_OPERATORS__INL
#define COLOR_VECTOR__ASSIGNMENT_OPERATORS__INL

namespace Color
{

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

// Assign from or convert to color Hex value
inline ColorVector& ColorVector::operator=( FourChannelInt a_uiHex )
{
    return operator=( Hex( a_uiHex ) );
}
inline ColorVector& ColorVector::operator=( const Hex& ac_rHex )
{
    a = ac_rHex.a;
    r = ac_rHex.r;
    g = ac_rHex.g;
    b = ac_rHex.b;
    return *this;
}
inline ColorVector::operator Hex() const
{
    return Hex( r, g, b, a );
}

}   // namespace Color

#endif  // COLOR_VECTOR__ASSIGNMENT_OPERATORS__INL
