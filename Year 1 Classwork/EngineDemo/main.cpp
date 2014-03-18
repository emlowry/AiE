/******************************************************************************
 * File:               main.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       February 4, 2014
 * Description:        Runs a simple game to demonstrate MyFirstEngine.
 * Last Modified:      March 18, 2014
 * Last Modification:  Animated sprite testing.
 ******************************************************************************/

#include "MyFirstEngine.h"
#include <cmath>
#include <conio.h>
#include <iostream>

using namespace MyFirstEngine;
using namespace Utility;

class SimpleState : public GameState, public InitializeableSingleton< SimpleState >
{
    friend class InitializeableSingleton< SimpleState >;
public:
    virtual ~SimpleState() {}
    virtual void Draw() const override
    {
        GameEngine::MainWindow().Clear();
        for each( const Quad& croQuad in m_aoQuads )
        {
            croQuad.Draw();
        }
        m_oSprite.Draw();
        GameEngine::MainWindow().SwapBuffers();
    }
protected:
    virtual void InitializeInstance() override
    {
        m_oTexture.Load();
        m_oFrameList.SetSize( 4 );
        for( unsigned int ui = 0; ui < 4; ++ui )
        {
            m_oFrameList[ui] = Frame::ZERO;
            m_oFrameList[ui].framePixels = m_oTexture.Size() / 2;
            m_oFrameList[ui].slicePixels = m_oTexture.Size() / 2;
            m_oFrameList[ui].sliceLocation.x = ( ui / 2 ) * ( m_oTexture.Size().x / 2 );
            m_oFrameList[ui].sliceLocation.y = ( ui % 2 ) * ( m_oTexture.Size().y / 2 );
        }
        m_oSprite.UpdateTextureMatrix();
        m_oSprite.SetDisplaySize( 0.125, 0.25 );
        m_oSprite.Play();
    }
    virtual void TerminateInstance() override
    {
        m_oTexture.Destroy();
    }
    virtual void OnEnter() override
    {
        GameEngine::MainWindow().MakeCurrent();
    }
    virtual void OnUpdate( double a_dDeltaTime )
    {
        double dAngle1 = Math::ScrollRadians( GameEngine::LastTime() );
        double dAngle2 = Math::ScrollRadians( GameEngine::LastTime() * 2 );
        double dAngle3 = Math::ScrollRadians( GameEngine::LastTime() / 2 );
        m_aoQuads[0].SetYaw( dAngle1 );
        m_aoQuads[1].SetPitch( dAngle1 );
        m_aoQuads[2].SetRoll( dAngle1 );
        m_aoQuads[3].SetTaitBryanAngles( dAngle1,
                                         dAngle1,
                                         dAngle1 );
        m_aoQuads[4].SetTaitBryanAngles( -dAngle1,
                                         -dAngle1,
                                         -dAngle1 );
        m_aoQuads[5].SetScale( 0.625 + ( 0.125 * std::sin( dAngle2 ) ) );
        m_aoQuads[6].SetScale( 0.25 + ( 0.25 * std::sin( dAngle3 ) ),
                               0.25 + ( 0.25 * std::cos( dAngle3 ) ) );
        m_aoQuads[7].SetPosition( 0.5 * std::sin( dAngle1 ),
                                  0.5 * std::cos( dAngle1 ) );
        m_oSprite.SetPosition( m_aoQuads[7].GetPosition() );
        if( 0.0 < dAngle1 && a_dDeltaTime > dAngle1 )
        {
            m_oSprite.Seek( dAngle1 );
        }
        m_oSprite.Update( a_dDeltaTime );
    }
private:
    SimpleState() : m_oTexture( "resources/images/warhol_soup.png" ), m_oSprite( &m_oTexture, &m_oFrameList, 2, 1 )
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
    Texture m_oTexture;
    AnimatedSprite m_oSprite;
    Frame::Array m_oFrameList;
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
        SimpleState::Initialize();
        GameEngine::MainWindow().SetClearColor( Color::GrayScale::ONE_HALF );
        SimpleState::Instance().Push();
        GameEngine::Run();

        std::cout << "\tWindow closed." << std::endl
                  << std::endl << "Terminating Game Engine...";
        SimpleState::Terminate();
        GameEngine::Terminate();
        std::cout << "\tGame Engine terminated." << std::endl;
    }

    //TODO
    return 0;
}
