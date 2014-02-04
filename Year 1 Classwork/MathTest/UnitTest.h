/******************************************************************************
 * File:               UnitTest.h
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        Class representing a single test.
 * Last Modified:      January 5, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

#ifndef UNIT_TEST__H
#define UNIT_TEST__H

#include <exception>
#include <string>
#include <iostream>


class UnitTest
{
public:

    struct Result
    {
        bool pass;
        std::string message;
        Result( bool a_bPass = false, std::string a_oMessage = "" )
            : pass( a_bPass ), message( a_oMessage ) {}
    };
    typedef Result (*TestFunctionPointer)();

    UnitTest( const std::string& ac_roName,
              TestFunctionPointer a_pTest );

    bool operator()( std::ostream& a_roOut = std::cout ) const;

    static Result Fail( std::string a_oMessage = "" );
    static Result Pass( std::string a_oMessage = "" );

    static const Result PASS;
    static const Result FAIL;

protected:

    TestFunctionPointer m_pTest;
    std::string m_oName;

};
typedef UnitTest::TestFunctionPointer TestFunctionPointer;

#endif  // UNIT_TEST__H
