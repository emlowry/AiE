/******************************************************************************
 * File:               UnitTester.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        Runs a list of unit test groups.
 * Last Modified:      January 5, 2014
 * Last Modification:  Creation.
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
    for each( UnitTestGroup oGroup in m_oTests )
    {
        oGroup( a_roOut );
    }
}
