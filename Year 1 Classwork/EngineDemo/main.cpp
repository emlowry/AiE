/******************************************************************************
 * File:               main.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       February 4, 2014
 * Description:        Runs a simple game to demonstrate MyFirstEngine.
 * Last Modified:      February 4, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#include "MyFirstEngine.h"
#include <conio.h>
#include <iostream>

using MyFirstEngine::GameEngine;

int main(int argc, char* argv[])
{
    std::cout << "Initializing Game Engine...";
    bool bSuccess = GameEngine::Initialize();
    if( !bSuccess )
    {
        std::cout << "\tGame Engine initialization failed." << std::endl;
    }
    else
    {
        std::cout << "\tGame Engine Initialized." << std::endl;

	    std::cout << std::endl << "Press any key to continue..." << std::endl;
	    _getch();

        GameWindow oWindow;
        oWindow.Open();

        std::cout << std::endl << "Terminating Game Engine...";
        GameEngine::Terminate();
        std::cout << "\tGame Engine terminated." << std::endl;
    }

	std::cout << std::endl << "Press any key to exit..." << std::endl;
	_getch();

    //TODO
    return 0;
}
