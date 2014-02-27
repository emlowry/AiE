/******************************************************************************
 * File:               main.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       February 4, 2014
 * Description:        Runs a simple game to demonstrate MyFirstEngine.
 * Last Modified:      February 25, 2014
 * Last Modification:  Testing quads.
 ******************************************************************************/

#include "MyFirstEngine.h"
#include <conio.h>
#include <iostream>

using namespace MyFirstEngine;
using namespace Utility;

class SimpleState : public GameState, public Singleton< SimpleState >
{
    friend class Singleton< SimpleState >;
public:
    virtual ~SimpleState() {}
    virtual void Draw() const override
    {
        GameEngine::MainWindow().Clear();
        m_oQuad1.Draw();
        m_oQuad2.Draw();
        GameEngine::MainWindow().SwapBuffers();
    }
protected:
    virtual void OnEnter() override
    {
        GameEngine::MainWindow().MakeCurrent();
    }
    virtual void OnUpdate( double a_dDeltaTime )
    {
        m_oQuad1.AddYaw( a_dDeltaTime );
        m_oQuad1.AddPitch( a_dDeltaTime );
        m_oQuad1.AddRoll( a_dDeltaTime );
        m_oQuad2.AddYaw( -a_dDeltaTime );
        m_oQuad2.AddPitch( -a_dDeltaTime );
        m_oQuad2.AddRoll( -a_dDeltaTime );
    }
private:
    SimpleState()
        : m_oQuad2( Color::ColorWheel::ROSE,
                    Point2D( 0.5, 0.5 ) ) {}
    Quad m_oQuad1;
    Quad m_oQuad2;
};

int main(int argc, char* argv[])
{
    std::cout << "Initializing Game Engine...";
    bool bSuccess = GameEngine::Initialize( 800, 600, "Simple Test Program" );
    if( !bSuccess )
    {
        std::cout << "\tGame Engine initialization failed." << std::endl;
    }
    else
    {
        std::cout << "\tGame Engine Initialized." << std::endl
                  << std::endl << "Close game window to continue...";
        SimpleState::Instance().Push();
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
