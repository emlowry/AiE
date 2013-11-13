/******************************************************************************
 * File:               main.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       September 30, 2013
 * Description:        Main function for the Shoot'em up program.
 * Last Modified:      September 30, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#include "GameEngine.h"
#include "LoadScreen.h"

int main( int argc, char* argv[] )
{	
    GameEngine::Initialize( "Stupid Shooter v. 1.0" );
    GameEngine::SetState( LoadScreen::State );
    GameEngine::Run();
    GameEngine::Shutdown();
    return 0;
}

