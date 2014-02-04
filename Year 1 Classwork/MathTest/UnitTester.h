/******************************************************************************
 * File:               UnitTester.h
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        Runs a list of unit test groups.
 * Last Modified:      January 5, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

#ifndef UNIT_TESTER__H
#define UNIT_TESTER__H

#include "UnitTestGroup.h"
#include <list>
#include <iostream>

class UnitTester
{
public:

    void AddTestGroup( UnitTestGroup& a_roTests );
    void operator()( std::ostream& a_roOut = std::cout ) const;

protected:

    std::list< UnitTestGroup > m_oTests;

};

#endif  // UNIT_TESTER__H
