/******************************************************************************
 * File:               UnitTest.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        Class representing a single test.
 * Last Modified:      January 5, 2014
 * Last Modification:  Creation.
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
    if( nullptr != m_pTest )
    {
        oResult = m_pTest();
    }
    a_roOut << "\t" << m_oName << ": "
            << ( oResult.pass ? "PASS" : "FAIL" ) << std::endl;
    if( !oResult.message.empty() )
    {
        a_roOut << "\t\t" << oResult.message << std::endl;
    }
    return oResult.pass;
}
