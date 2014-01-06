/******************************************************************************
 * File:               UnitTester.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        Runs a list of unit test groups.
 * Last Modified:      January 5, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#include "InlineMath.h"
#include "UnitTest.h"
#include "UnitTester.h"
#include "UnitTestGroup.h"
#include <conio.h>
#include <iostream>
#include <string>

UnitTest::Result Vector4Test1();
UnitTest::Result Vector4Test2();
UnitTest::Result Vector4Test3();
UnitTest::Result Vector4Test4();

int main(int argc, char* argv[])
{
    // set up
    UnitTester oTester;

    // Vector4 tests
    UnitTestGroup oVector4Tests( "Vector4 Tests" );
    oVector4Tests.AddTest( "Vector4 Test 1", Vector4Test1 );
    oVector4Tests.AddTest( "Vector4 Test 2", Vector4Test2 );
    oVector4Tests.AddTest( "Vector4 Test 3", Vector4Test3 );
    oVector4Tests.AddTest( "Vector4 Test 4", Vector4Test4 );
    oTester.AddTestGroup( oVector4Tests );

    // run
    oTester( std::cout );
	std::cout << std::endl << std::endl << "Press any key to exit...";
	_getch();
    return 0;
}

UnitTest::Result Vector4Test1()
{
    Color::ColorVector oColor( Color::VGA::GREEN );
    if( oColor.fAlpha() != 1.0f )
    {
        return UnitTest::Fail( "Wrong alpha value" );
    }
    if( oColor.fRed() != 0.0f )
    {
        return UnitTest::Fail( "Wrong red value" );
    }
    if( oColor.g != 0x7F )
    {
        return UnitTest::Fail( "Wrong green value" );
    }
    if( oColor.b != 0x00 )
    {
        return UnitTest::Fail( "Wrong blue value" );
    }
    return UnitTest::PASS;
}

UnitTest::Result Vector4Test2()
{
    Color::ColorVector oColor( 0xFF007F00 );
    if( oColor.fAlpha() != 1.0f )
    {
        return UnitTest::Fail( "Wrong alpha value" );
    }
    if( oColor.fRed() != 0.0f )
    {
        return UnitTest::Fail( "Wrong red value" );
    }
    if( oColor.g != 0x7F )
    {
        return UnitTest::Fail( "Wrong green value" );
    }
    if( oColor.b != 0x00 )
    {
        return UnitTest::Fail( "Wrong blue value" );
    }
    return UnitTest::PASS;
}

UnitTest::Result Vector4Test3()
{
    Color::ColorVector oColor( 0xFF000000 );
    oColor |= 0x00007F00;
    if( oColor.fAlpha() != 1.0f )
    {
        return UnitTest::Fail( "Wrong alpha value" );
    }
    if( oColor.fRed() != 0.0f )
    {
        return UnitTest::Fail( "Wrong red value" );
    }
    if( oColor.g != 0x7F )
    {
        return UnitTest::Fail( "Wrong green value" );
    }
    if( oColor.b != 0x00 )
    {
        return UnitTest::Fail( "Wrong blue value" );
    }
    return UnitTest::PASS;
}

UnitTest::Result Vector4Test4()
{
    double adData[4] = { 1.0, 2.0, 3.0, 4.0 };
    Math::Vector< double, 4 > oData( adData );
    if( oData.MagnitudeSquared() != 41.0 )
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
