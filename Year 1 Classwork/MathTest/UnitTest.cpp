/******************************************************************************
 * File:               UnitTest.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        Class representing a single test.
 * Last Modified:      January 5, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

#include "UnitTest.h"
#include <string>
#include <iostream>

const UnitTest::Result UnitTest::PASS( true );
const UnitTest::Result UnitTest::FAIL( false );

UnitTest::Result UnitTest::Fail( std::string a_oMessage )
{
    return Result( false, a_oMessage );
}
UnitTest::Result UnitTest::Pass( std::string a_oMessage )
{
    return Result( true, a_oMessage );
}

UnitTest::UnitTest( const std::string& ac_roName,
                    TestFunctionPointer a_pTest )
    : m_oName( ac_roName ), m_pTest( a_pTest ) {}

bool UnitTest::operator()( std::ostream& a_roOut ) const
{
    Result oResult;
    try
    {
        oResult = m_pTest();
    }
    catch( const std::exception& croError )
    {
        oResult = Fail( croError.what() );
    }
    catch( const std::string& croString )
    {
        oResult = Fail( croString );
    }
    catch( const char* const cpccString )
    {
        oResult = Fail( cpccString );
    }
    catch( ... )
    {
        oResult = Fail( "Unidentified error" );
    }
    a_roOut << "\t" << ( oResult.pass ? "PASSED" : "FAILED" ) << ": " << m_oName
            << std::endl;
    if( !oResult.message.empty() )
    {
        a_roOut << "\t\t" << oResult.message << std::endl;
    }
    return oResult.pass;
}
