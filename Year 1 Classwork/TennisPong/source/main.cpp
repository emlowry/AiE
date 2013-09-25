/******************************************************************************
 * File:               main.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       September 10, 2013
 * Description:        Main function for the Pong program.
 * Last Modified:      September 17, 2013
 * Last Modification:  Moving code to Game class.
 ******************************************************************************/

#include "AIE.h"
#include "Game.h"
#include <stdlib.h>
#include <time.h>

int main( int argc, char* argv[] )
{
	// Initialize
	srand( (unsigned int) time(NULL) );
	Initialise( Game::SCREEN_WIDTH,
				Game::SCREEN_HEIGHT ,
				false, Game::GAME_TITLE );
	Game oGame;

	// Play
	do {} while( !FrameworkUpdate() && oGame.Run() );

	// Quit
	oGame.Shutdown();
	Shutdown();
	return 0;
}
