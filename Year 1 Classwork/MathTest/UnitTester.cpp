/******************************************************************************
 * File:               UnitTester.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        Runs a list of unit test groups.
 * Last Modified:      January 5, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

#include "UnitTester.h"
#include "UnitTestGroup.h"
#include <list>
#include <iostream>

void UnitTester::AddTestGroup( UnitTestGroup& a_roTests )
{
    m_oTests.push_back( a_roTests );
}

void UnitTester::operator()( std::ostream& a_roOut ) const
{
    a_roOut << "Running unit test groups..." << std::endl;
    unsigned int uiFailed = 0;
    for each( UnitTestGroup oGroup in m_oTests )
    {
        if( !oGroup( a_roOut ) )
        {
            ++uiFailed;
        }
    }
    if( 0 == uiFailed )
    {
        a_roOut << std::endl << "PASSED all "
                << m_oTests.size() << " test groups";
    }
    else
    {
        a_roOut << std::endl << "FAILED " << uiFailed << " of "
                << m_oTests.size() << " test groups";
    }
}
