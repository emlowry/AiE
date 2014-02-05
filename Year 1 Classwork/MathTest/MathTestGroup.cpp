/******************************************************************************
 * File:               MathTestGroup.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        Common math functionality tests.
 * Last Modified:      February 5, 2014
 * Last Modification:  Refactoring.
 ******************************************************************************/

#include "MathTestGroup.h"
#include "MathLibrary.h"

MathTestGroup::MathTestGroup()
    : UnitTestGroup("Common math functionality tests")
{
    AddTest( "Convert between degrees and radians", Conversions );
    AddTest( "Linear interpolation between scalar values", Interpolation );
    AddTest( "Obtaining nearest power of two", NearestPower );
    AddTest( "Bitwise operations", ColorBitwise );
}

UnitTest::Result MathTestGroup::Conversions()
{
    double dDegrees = Math::Degrees( Math::PI );
    if( dDegrees != 180.0 )
    {
        return UnitTest::Fail( "Bad conversion from radians to degrees" );
    }
    double dRadians = Math::Radians( 90.0 );
    if( dRadians != Math::PI / 2 )
    {
        return UnitTest::Fail( "Bad conversion from degrees to radians" );
    }
    return UnitTest::PASS;
}

UnitTest::Result MathTestGroup::Interpolation()
{
    int iInterp = Math::Interpolate( 2, 4 );
    if( iInterp != 3 )
    {
        return UnitTest::Fail( "Incorrect default interpolation between 2 and 4" );
    }
    iInterp = Math::Interpolate( -2, 10, 0.75 );
    if( iInterp != 7 )
    {
        return UnitTest::Fail( "Incorrect 3/4-interpolation between -2 and 10" );
    }
    double dInterp = Math::Interpolate( -1.25, 1.75 );
    if( dInterp != 0.25 )
    {
        return UnitTest:: Fail( "Incorrect default interpolation between -1.25 and 1.75" );
    }
    dInterp = Math::Interpolate( 2.5, -1.5, 0.75 );
    if( dInterp != -0.5 )
    {
        return UnitTest::Fail( "Incorrect 3/4-interpolation between 2.5 and -0.7" );
    }
    return UnitTest::PASS;
}

UnitTest::Result MathTestGroup::NearestPower()
{
    int iPow = Math::NearestPowerOfTwo( 5 );
    if( iPow != 4 )
    {
        return UnitTest::Fail( "Incorrect nearest power of two to 5" );
    }
    iPow = Math::NearestPowerOfTwo( 7 );
    if( iPow != 8 )
    {
        return UnitTest::Fail( "Incorrect nearest power of two to 7" );
    }
    double dPow = Math::NearestPowerOfTwo( 11.5 );
    if( dPow != 8.0 )
    {
        return UnitTest::Fail( "Incorrect nearest power of two to 11.5" );
    }
    dPow = Math::NearestPowerOfTwo( 12.5 );
    if( dPow != 16.0 )
    {
        return UnitTest::Fail( "Incorrect nearest power of two to 12.5" );
    }
    return UnitTest::PASS;
}

UnitTest::Result MathTestGroup::ColorBitwise()
{
    Color::Hex oColor = Color::VGA::GREEN & Color::Opacity::HALF;
    if( oColor.i != 0x7F007F00 )
    {
        return UnitTest::Fail( "Incorrect ANDed color" );
    }
    oColor |= Color::VGA::RED;
    if( oColor.i != 0xFFFF7F00 )
    {
        return UnitTest::Fail( "Incorrect ORed color" );
    }
    oColor ^= Color::VGA::AQUA;
    if( oColor.i != 0x00FF80FF )
    {
        return UnitTest::Fail( "Incorrect XORed color" );
    }
    oColor = ~oColor;
    if( oColor.i != 0xFF007F00 )
    {
        return UnitTest::Fail( "Incorrect inverted color" );
    }
    return UnitTest::PASS;
}