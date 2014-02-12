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
using MyFirstEngine::GameState;
using MyFirstEngine::GameWindow;

class SimpleState : public GameState, public Singleton< SimpleState >
{
    friend class Singleton< SimpleState >;
public:
    virtual ~SimpleState() {}
protected:
    virtual void OnEnter() { m_oWindow.Open(); }
private:
    SimpleState() : m_oWindow( 800, 600, "Simple Test Program" ) {}
    GameWindow m_oWindow;
};

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

	    std::cout << std::endl << "Press any key to continue...";
	    _getch();

        std::cout << "\tLaunching game window." << std::endl;
        SimpleState::Instance().Push();

	    std::cout << std::endl << "Close game window to continue...";
        GameEngine::Run();

        std::cout << "\tWindow closed." << std::endl
                  << std::endl << "Terminating Game Engine...";
        GameEngine::Terminate();
        std::cout << "\tGame Engine terminated." << std::endl;
    }

	std::cout << std::endl << "Press any key to exit...";
	_getch();

    //TODO
    return 0;
}
