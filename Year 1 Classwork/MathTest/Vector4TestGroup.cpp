/******************************************************************************
 * File:               Vector4TestGroup.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        Vector4 tests.
 * Last Modified:      February 25, 2014
 * Last Modification:  Changed ColorVector from 8-bit Channel to float.
 ******************************************************************************/

#include "Vector4TestGroup.h"
#include "MathLibrary.h"

Vector4TestGroup::Vector4TestGroup()
    : UnitTestGroup("Vector4 tests")
{
    AddTest( "Create from color Hex constant", ColorConstInit );
    AddTest( "Create from color Hex integer", ColorHexInit );
    AddTest( "Bitwise operation on color vector", ColorBitwiseOp );
    AddTest( "Normalization and magnitude", Normalization );
}

UnitTest::Result Vector4TestGroup::ColorConstInit()
{
    Color::ColorVector oColor( Color::VGA::GREEN );
    if( oColor.a != 1.0f )
    {
        return UnitTest::Fail( "Wrong alpha value" );
    }
    if( oColor.r != 0.0f )
    {
        return UnitTest::Fail( "Wrong red value" );
    }
    if( oColor.GreenChannel() != 0x7F )
    {
        return UnitTest::Fail( "Wrong green value" );
    }
    if( oColor.BlueChannel() != 0x00 )
    {
        return UnitTest::Fail( "Wrong blue value" );
    }
    return UnitTest::PASS;
}

UnitTest::Result Vector4TestGroup::ColorHexInit()
{
    Color::ColorVector oColor( 0xFF007F00 );
    if( oColor.a != 1.0f )
    {
        return UnitTest::Fail( "Wrong alpha value" );
    }
    if( oColor.r != 0.0f )
    {
        return UnitTest::Fail( "Wrong red value" );
    }
    if( oColor.GreenChannel() != 0x7F )
    {
        return UnitTest::Fail( "Wrong green value" );
    }
    if( oColor.BlueChannel() != 0x00 )
    {
        return UnitTest::Fail( "Wrong blue value" );
    }
    return UnitTest::PASS;
}

UnitTest::Result Vector4TestGroup::ColorBitwiseOp()
{
    Color::ColorVector oColor( 0xFF000000 );
    oColor |= 0x00007F00;
    if( oColor.a != 1.0f )
    {
        return UnitTest::Fail( "Wrong alpha value" );
    }
    if( oColor.r != 0.0f )
    {
        return UnitTest::Fail( "Wrong red value" );
    }
    if( oColor.GreenChannel() != 0x7F )
    {
        return UnitTest::Fail( "Wrong green value" );
    }
    if( oColor.BlueChannel() != 0x00 )
    {
        return UnitTest::Fail( "Wrong blue value" );
    }
    return UnitTest::PASS;
}

UnitTest::Result Vector4TestGroup::Normalization()
{
    double adData[4] = { 1.0, 2.0, 3.0, 4.0 };
    Math::Vector< double, 4 > oData( adData );
    if( oData.MagnitudeSquared() != 30.0 )
    {
        return UnitTest::Fail( "Wrong square magnitude" );
    }
    adData[0] = 2.0;
    adData[2] = 2.0;
    adData[3] = 2.0;
    oData = adData;
    if( oData.Magnitude() != 4.0 )
    {
        return UnitTest::Fail( "Wrong square magnitude" );
    }
    oData.Normalize();
    if( oData[0] != 0.5 || oData[1] != 0.5 || oData[2] != 0.5 || oData[3] != 0.5 )
    {
        return UnitTest::Fail( "Wrong normalized vector elements" );
    }
    return UnitTest::PASS;
}
