/******************************************************************************
 * File:               main.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       February 4, 2014
 * Description:        Runs a simple game to demonstrate MyFirstEngine.
 * Last Modified:      March 5, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

#include "MyFirstEngine.h"
#include <cmath>
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
        for each( const Quad& croQuad in m_aoQuads )
        {
            croQuad.Draw();
        }
        GameEngine::MainWindow().SwapBuffers();
    }
protected:
    virtual void OnEnter() override
    {
        GameEngine::MainWindow().MakeCurrent();
    }
    virtual void OnUpdate( double a_dDeltaTime )
    {
        m_aoQuads[0].SetYaw( GameEngine::LastTime() );
        m_aoQuads[1].SetPitch( GameEngine::LastTime() );
        m_aoQuads[2].SetRoll( GameEngine::LastTime() );
        m_aoQuads[3].SetTaitBryanAngles( GameEngine::LastTime(),
                                         GameEngine::LastTime(),
                                         GameEngine::LastTime() );
        m_aoQuads[4].SetTaitBryanAngles( -GameEngine::LastTime(),
                                         -GameEngine::LastTime(),
                                         -GameEngine::LastTime() );
        m_aoQuads[5].SetScale( 0.625 + ( 0.125 * std::sin( 2 * GameEngine::LastTime() ) ) );
        m_aoQuads[6].SetScale( 0.25 + ( 0.25 * std::sin( GameEngine::LastTime() / 2 ) ),
                               0.25 + ( 0.25 * std::cos( GameEngine::LastTime() / 2 ) ) );
        m_aoQuads[7].SetPosition( 0.5 * std::sin( GameEngine::LastTime() ),
                                  0.5 * std::cos( GameEngine::LastTime() ) );
    }
private:
    SimpleState()
    {
        m_aoQuads[0] = Quad( Color::GrayScale::WHITE, Point2D( 2.0, 2.0 ) );
        m_aoQuads[1] = Quad( Color::GrayScale::THREE_QUARTERS, Point2D( 1.75, 1.75 ) );
        m_aoQuads[2] = Quad( Color::GrayScale::ONE_HALF, Point2D( 1.5, 1.5 ) );
        m_aoQuads[3] = Quad( Color::GrayScale::ONE_QUARTER, Point2D( 1.25, 1.25 ) );
        m_aoQuads[4] = Quad( Color::BLACK, Point2D( 1.0, 1.0 ) );
        m_aoQuads[5] = Quad( Color::ColorWheel::ROSE, Point2D( 0.75, 0.75 ) );
        m_aoQuads[6] = Quad( Color::ColorWheel::VIOLET, Point2D( 0.5, 0.5 ) );
        m_aoQuads[7] = Quad( Color::ColorWheel::MEGAMAN_BLUE, Point2D( 0.25, 0.25 ) );
    }
    Quad m_aoQuads[8];
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
                  << std::endl << "Close game window to exit...";
        SimpleState::Instance().Push();
        GameEngine::Run();

        std::cout << "\tWindow closed." << std::endl
                  << std::endl << "Terminating Game Engine...";
        GameEngine::Terminate();
        std::cout << "\tGame Engine terminated." << std::endl;
    }

    //TODO
    return 0;
}
