/******************************************************************************
 * File:               UnitTestGroup.h
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        Class representing a group of tests.
 * Last Modified:      January 5, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#include "UnitTest.h"
#include "UnitTestGroup.h"
#include <string>
#include <list>

UnitTestGroup::UnitTestGroup( const std::string& ac_roName )
    : m_oName( ac_roName ) {}

void UnitTestGroup::AddTest( std::string ac_roName, TestFunctionPointer a_pTest )
{
    m_oTests.push_back( UnitTest( ac_roName, a_pTest ) );
}

bool UnitTestGroup::operator()( std::ostream& a_roOut ) const
{
    a_roOut << "Running " << m_oName << "..." << std::endl;
    unsigned int uiRan = 0;
    unsigned int uiFailed = 0;
    for each( UnitTest oTest in m_oTests )
    {
        if( !oTest( a_roOut ) )
        {
            ++uiFailed;
        }
        ++uiRan;
    }
    a_roOut << m_oName << ": ";
    if( uiFailed )
    {
        a_roOut << uiFailed << " of " << uiRan << " tests FAILED ";
    }
    else
    {
        a_roOut << uiRan << " tests PASSED ";
    }
    a_roOut << std::endl << std::endl;
    return ( 0 == uiFailed );
}
