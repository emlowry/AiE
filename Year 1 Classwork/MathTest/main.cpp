/******************************************************************************
 * File:               main.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       January 5, 2014
 * Description:        Runs a list of unit test groups.
 * Last Modified:      January 5, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

#include "UnitTester.h"
#include "MathTestGroup.h"
#include "Matrix3x3TestGroup.h"
#include "Matrix4x4TestGroup.h"
#include "Vector2TestGroup.h"
#include "Vector3TestGroup.h"
#include "Vector4TestGroup.h"
#include <conio.h>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    // set up
    UnitTester oTester;
    oTester.AddTestGroup( Matrix3x3TestGroup() );
    oTester.AddTestGroup( Matrix4x4TestGroup() );
    oTester.AddTestGroup( Vector2TestGroup() );
    oTester.AddTestGroup( Vector3TestGroup() );
    oTester.AddTestGroup( Vector4TestGroup() );
    oTester.AddTestGroup( MathTestGroup() );

    // run
    oTester( std::cout );
	std::cout << std::endl << std::endl << "Press any key to exit...";
	_getch();
    return 0;
}
