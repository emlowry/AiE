/******************************************************************************
 * File:               UnitTestGroup.h
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        Class representing a group of tests.
 * Last Modified:      January 5, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

#ifndef UNIT_TEST_GROUP__H
#define UNIT_TEST_GROUP__H

#include "UnitTest.h"
#include <iostream>
#include <list>
#include <string>

class UnitTestGroup
{
public:

    UnitTestGroup( const std::string& ac_roName );

    void AddTest( std::string ac_roName, TestFunctionPointer a_pTest );
    bool operator()( std::ostream& a_roOut = std::cout ) const;

protected:

    std::list< UnitTest > m_oTests;
    std::string m_oName;

};

#endif  // UNIT_TEST_GROUP
