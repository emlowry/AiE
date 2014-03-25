/******************************************************************************
 * File:               main.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       February 4, 2014
 * Description:        Runs a simple game to demonstrate MyFirstEngine.
 * Last Modified:      March 25, 2014
 * Last Modification:  Testing mouse and keyboard input.
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
        Typewriter::ReturnToStart();
        Typewriter::SetColor( Color::VGA::SILVER );
        Typewriter::Type( "\t\tMy pixel art font:\n");
        Typewriter::SetColor( Color::WHITE );
        Typewriter::Type( " !\"#$%&'()*+,-./0123456789:;<=>?\n"
                          "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_\n"
                          "`abcdefghijklmnopqrstuvwxyz{|}~\n\n");
        Typewriter::SetColor( Color::VGA::SILVER );
        Typewriter::Type( "Konami code:\t");
        Typewriter::SetColor( Color::WHITE );
        Typewriter::TypeSymbol( "up" );
        Typewriter::TypeSymbol( "up" );
        Typewriter::TypeSymbol( "down" );
        Typewriter::TypeSymbol( "down" );
        Typewriter::TypeSymbol( "left" );
        Typewriter::TypeSymbol( "right" );
        Typewriter::TypeSymbol( "left" );
        Typewriter::TypeSymbol( "right" );
        Typewriter::Type( "BA[START]\n" );
        Typewriter::SetColor( Color::VGA::SILVER );
        Typewriter::Type( "Missing char:\t");
        Typewriter::SetColor( Color::WHITE );
        Typewriter::TypeSymbol( "horseshoe" );
        Typewriter::Type( "\n\n\t" );
        Typewriter::SetColor( Color::ColorWheel::RED );
        Typewriter::TypeSymbol( "heart" );
        Typewriter::SetColor( Color::ColorWheel::RED_ORANGE );
        Typewriter::TypeSymbol( "music" );
        Typewriter::SetColor( Color::ColorWheel::ORANGE );
        Typewriter::TypeSymbol( "heart" );
        Typewriter::SetColor( Color::ColorWheel::GOLD );
        Typewriter::Type( "T" );
        Typewriter::SetColor( Color::ColorWheel::YELLOW );
        Typewriter::Type( "A" );
        Typewriter::SetColor( Color::ColorWheel::GREEN_YELLOW );
        Typewriter::Type( "S" );
        Typewriter::SetColor( Color::ColorWheel::CHARTREUSE );
        Typewriter::Type( "T" );
        Typewriter::SetColor( Color::ColorWheel::HARLEQUIN_GREEN );
        Typewriter::Type( "E " );
        Typewriter::SetColor( Color::ColorWheel::GREEN );
        Typewriter::Type( "T" );
        Typewriter::SetColor( Color::ColorWheel::LEAF_GREEN );
        Typewriter::Type( "H" );
        Typewriter::SetColor( Color::ColorWheel::SPRING_GREEN );
        Typewriter::Type( "E " );
        Typewriter::SetColor( Color::ColorWheel::AQUAMARINE );
        Typewriter::Type( "R" );
        Typewriter::SetColor( Color::ColorWheel::CYAN );
        Typewriter::Type( "A" );
        Typewriter::SetColor( Color::ColorWheel::SKY_BLUE );
        Typewriter::Type( "I" );
        Typewriter::SetColor( Color::ColorWheel::MEGAMAN_BLUE );
        Typewriter::Type( "N" );
        Typewriter::SetColor( Color::ColorWheel::ROYAL_BLUE );
        Typewriter::Type( "B" );
        Typewriter::SetColor( Color::ColorWheel::BLUE );
        Typewriter::Type( "O" );
        Typewriter::SetColor( Color::ColorWheel::VIOLET_BLUE );
        Typewriter::Type( "W" );
        Typewriter::SetColor( Color::ColorWheel::VIOLET );
        Typewriter::Type( "!" );
        Typewriter::SetColor( Color::ColorWheel::PURPLE );
        Typewriter::Type( "!" );
        Typewriter::SetColor( Color::ColorWheel::MAGENTA );
        Typewriter::Type( "!" );
        Typewriter::SetColor( Color::ColorWheel::VIOLET_RED );
        Typewriter::TypeSymbol( "heart" );
        Typewriter::SetColor( Color::ColorWheel::ROSE );
        Typewriter::TypeSymbol( "music" );
        Typewriter::SetColor( Color::ColorWheel::CRIMSON );
        Typewriter::TypeSymbol( "heart" );
        GameEngine::MainWindow().SwapBuffers();
    }
protected:
    virtual void InitializeInstance() override
    {
        m_oTexture.Load();
        m_oFontTexture.Load();
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
        m_oSprite.SetDisplaySize( 40, 80 );
    }
    virtual void TerminateInstance() override
    {
        m_oTexture.Destroy();
    }
    virtual void OnEnter() override
    {
        GameEngine::MainWindow().MakeCurrent();
        Typewriter::SetFont( m_oFont );
        Typewriter::SetFontSize( 16 );
        Typewriter::SetTabSize( 64 );
        Typewriter::SetStartPosition( -300, 100 );
        Camera::Enable();
        Camera::UseWindowPixelScreenSize();
        Camera::SetDepthOfView( 800 );
        m_oSprite.Rewind();
        m_oSprite.Play();
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
        m_aoQuads[5].SetScale( 200 + ( 40 * std::sin( dAngle2 ) ) );
        m_aoQuads[6].SetScale( 80 + ( 80 * std::sin( dAngle3 ) ),
                               80 + ( 80 * std::cos( dAngle3 ) ) );
        m_aoQuads[7].SetPosition( 240 * std::sin( dAngle1 ),
                                  240 * std::cos( dAngle1 ) );
        m_oSprite.SetPosition( Mouse::Position() );
        m_oSprite.SetVisible( Mouse::Window() == &GameEngine::MainWindow() );
        if( Mouse::ButtonTime() <= a_dDeltaTime )
        {
            if( Mouse::ButtonIsPressed() )
            {
                m_oSprite.Pause();
            }
            else
            {
                m_oSprite.Play();
            }
        }
        if( Keyboard::KeyTime( Keyboard::SPACE ) <= a_dDeltaTime )
        {
            if( Keyboard::KeyIsPressed( Keyboard::SPACE ) )
            {
                m_oSprite.SetColor( Color::Opacity::HALF );
            }
            else
            {
                m_oSprite.SetColor( Color::OPAQUE );
            }
        }
        m_oSprite.Update( a_dDeltaTime );
        if( Keyboard::KeyIsPressed( Keyboard::ESCAPE ) )
        {
            GameEngine::ClearStates();
        }
    }
private:
    SimpleState() : m_oTexture( "resources/images/warhol_soup.png" ),
                    m_oFontTexture( "resources/images/font.png" ),
                    m_oFont( m_oFontTexture, 16, 8 ),
                    m_oSprite( m_oTexture, m_oFrameList, 4 )
    {
        m_aoQuads[0] = Quad( Color::GrayScale::WHITE, Point2D( 640, 640 ) );
        m_aoQuads[1] = Quad( Color::GrayScale::THREE_QUARTERS, Point2D( 560, 560 ) );
        m_aoQuads[2] = Quad( Color::GrayScale::ONE_HALF, Point2D( 480, 480 ) );
        m_aoQuads[3] = Quad( Color::GrayScale::ONE_QUARTER, Point2D( 400, 400 ) );
        m_aoQuads[4] = Quad( Color::BLACK, Point2D( 320, 320 ) );
        m_aoQuads[5] = Quad( Color::ColorWheel::ROSE, Point2D( 240, 240 ) );
        m_aoQuads[6] = Quad( Color::ColorWheel::VIOLET, Point2D( 160, 160 ) );
        m_aoQuads[7] = Quad( Color::ColorWheel::MEGAMAN_BLUE, Point2D( 80, 80 ) );

        // printable ascii frames
        for( unsigned int ui = 0; ui < 95; ++ui )
        {
            m_oFont.Map( (char)( ui + 32 ), 8, 16, ( ui % 16 ) * 8, ( ui / 16 ) * 16, 3 );
        }
        
        // map special characters
        m_oFont[ HTML::nbsp ] = m_oFont[ ' ' ];
        m_oFont.Map( HTML::cent, 8, 16, 3*8, 6*16, 3);
        m_oFont.Map( HTML::yen, 8, 16, 4*8, 6*16, 3);
        m_oFont.Map( HTML::plusmn, 8, 16, 5*8, 6*16, 3);
        m_oFont.Map( HTML::divide, 8, 16, 6*8, 6*16, 3);
        m_oFont.Map( HTML::iquest, 8, 16, 8*8, 6*16, 3);
        m_oFont.Map( HTML::deg, 8, 16, 11*8, 6*16, 3);
        m_oFont.Map( HTML::pound, 8, 16, 12*8, 6*16, 3);
        m_oFont.Map( HTML::iexcl, 8, 16, 13*8, 6*16, 3);
        m_oFont.Map( HTML::laquo, 8, 16, 14*8, 6*16, 3);
        m_oFont.Map( HTML::raquo, 8, 16, 15*8, 6*16, 3);

        // Free up HTML codes to make room for custom characters
        m_oFont.Map( 0, "sup2" );   // '\xB2'
        m_oFont.Map( 0, "sup3" );   // '\xB3'
        m_oFont.Map( 0, "acute" );  // '\xB4'
        m_oFont.Map( 0, "micro" );  // '\xB5'
        m_oFont.Map( 0, "para" );   // '\xB6'
        m_oFont.Map( 0, "middot" ); // '\xB7'
        m_oFont.Map( 0, "cedil" );  // '\xB8'
        m_oFont.Map( 0, "Oslash" ); // '\xD8'
        m_oFont.Map( 0, "Ugrave" ); // '\xD9'
        m_oFont.Map( 0, "Uacute" ); // '\xDA'
        m_oFont.Map( 0, "Ucirc" );  // '\xDB'
        m_oFont.Map( 0, "Uuml" );   // '\xDC'
        m_oFont.Map( 0, "Yacute" ); // '\xDD'
        m_oFont.Map( 0, "THORN" );  // '\xDE'
        m_oFont.Map( 0, "Yuml" );   // '\xDF'
        m_oFont.Map( 0, "oslash" ); // '\xF8'
        m_oFont.Map( 0, "ugrave" ); // '\xF9'
        m_oFont.Map( 0, "uacute" ); // '\xFA'
        m_oFont.Map( 0, "ucirc" );  // '\xFB'
        m_oFont.Map( 0, "uuml" );   // '\xFC'
        m_oFont.Map( 0, "yacute" ); // '\xFD'
        m_oFont.Map( 0, "thorn" );  // '\xFE'
        m_oFont.Map( 0, "yuml" );   // '\xFF'

        // map custom special characters
        m_oFont.Map( '\xB2', "left", 8, 16, 15*8, 5*16, 3 );
        m_oFont.Map( '\xB3', "right", 8, 16, 0*8, 6*16, 3 );
        m_oFont.Map( '\xB4', "up", 8, 16, 1*8, 6*16, 3 );
        m_oFont.Map( '\xB5', "down", 8, 16, 2*8, 6*16, 3 );
        m_oFont.Map( '\xB6', "music", 8, 16, 7*8, 6*16, 3 );
        m_oFont.Map( '\xB7', "smile", 8, 16, 9*8, 6*16, 3 );
        m_oFont.Map( '\xB8', "frown", 8, 16, 10*8, 6*16, 3 );
        m_oFont.Map( '\xD8', "Square", 8, 16, 0, 7*16, 3 );
        m_oFont.Map( '\xD9', "Circle", 8, 16, 8, 7*16, 3 );
        m_oFont.Map( '\xDA', "Triangle", 8, 16, 2*8, 7*16, 3 );
        m_oFont.Map( '\xDB', "Spade", 8, 16, 3*8, 7*16, 3 );
        m_oFont.Map( '\xDC', "Heart", 8, 16, 4*8, 7*16, 3 );
        m_oFont.Map( '\xDD', "Diamond", 8, 16, 5*8, 7*16, 3 );
        m_oFont.Map( '\xDE', "Club", 8, 16, 6*8, 7*16, 3 );
        m_oFont.Map( '\xDF', "Star", 8, 16, 7*8, 7*16, 3 );
        m_oFont.Map( '\xF8', "square", 8, 16, 8*8, 7*16, 3 );
        m_oFont.Map( '\xF9', "circle", 8, 16, 9*8, 7*16, 3 );
        m_oFont.Map( '\xFA', "triangle", 8, 16, 10*8, 7*16, 3 );
        m_oFont.Map( '\xFB', "spade", 8, 16, 11*8, 7*16, 3 );
        m_oFont.Map( '\xFC', "heart", 8, 16, 12*8, 7*16, 3 );
        m_oFont.Map( '\xFD', "diamond", 8, 16, 13*8, 7*16, 3 );
        m_oFont.Map( '\xFE', "club", 8, 16, 14*8, 7*16, 3 );
        m_oFont.Map( '\xFF', "star", 8, 16, 15*8, 7*16, 3 );
    }
    Quad m_aoQuads[8];
    Texture m_oTexture;
    Texture m_oFontTexture;
    Font m_oFont;
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
                  << std::endl << "Close game window or press Escape to exit...";
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
