/******************************************************************************
 * File:              main.cpp
 * Author:            Elizabeth Lowry
 * Date Created:      September 10, 2013
 * Description:       Main function for the Pong program.
 * Last Modified:     September 17, 2013
 * Last Modification: Print scores to the screen, separate code.
 ******************************************************************************/

#include "AIE.h"
#include "Sprite.h"
#include "Ball.h"
#include "Player.h"
#include <string>
#include <cmath>
#include <time.h>
#include <assert.h>
#include <crtdbg.h>
#include <iostream>

using namespace std;

const char* BACKGROUND_TEXTURE_NAME = "./images/tennis_court.png";
const int LEFT_PLAYER_LOSES_X = 200;
const Sprite::Vector LEFT_PLAYER_START_POSITION = {240,396};
const int LEFT_SCORE_X = 100;
const int MIN_Y = 147;
const int MAX_Y = 645;
const char* SCORE_FORMAT = "%s: %d";
const int SCORE_Y = 80;
const float SLOW_SPEED = 1000.0f;
const int RIGHT_PLAYER_LOSES_X = 1000;
const Sprite::Vector RIGHT_PLAYER_START_POSITION = {960,396};
const int RIGHT_SCORE_X = 1000;
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 801;

enum GameState
{
	START_MATCH,
	START_ROUND,
	GAME_STATE,
	END
};

void DrawGame(const float ac_fSpeed,
			  Sprite& a_roBackground,
			  Player& a_roLeftPlayer,
			  Player& a_roRightPlayer,
			  Ball& a_roBall);

bool PlayerWins(Ball& a_roBall,
				Player& a_roLeftPlayer,
				Player& a_roRightPlayer,
				Player*& a_rpoServingPlayer,
				GameState& a_reGameState);

void PlayGame(Ball& a_roBall, Player& a_roLeftPlayer, Player& a_roRightPlayer);

int main( int argc, char* argv[] )
{	
	srand( (unsigned int) time(NULL) );
	Initialise( SCREEN_WIDTH, SCREEN_HEIGHT , false, "Pong!" );

	Sprite oBackgroundSprite(BACKGROUND_TEXTURE_NAME,
							 SCREEN_WIDTH,
							 SCREEN_HEIGHT,
							 Sprite::DEFAULT_POSITION,
							 false);
	Ball oBall;
	Player oLeftPlayer(oBall, Player::LEFT, LEFT_PLAYER_START_POSITION, MIN_Y, MAX_Y);
	Player oRightPlayer(oBall, Player::RIGHT, RIGHT_PLAYER_START_POSITION, MIN_Y, MAX_Y);
	Sprite* apoSprites[4] = { &oBackgroundSprite, &oLeftPlayer, &oRightPlayer, &oBall };

	oLeftPlayer.SetMode(Player::AI);
	oRightPlayer.SetMode(Player::AI);
	Player* poServingPlayer = (rand()%2 == 0) ? &oLeftPlayer : &oRightPlayer;
	float fSpeed = SLOW_SPEED;

	GameState eCurrentState = START_ROUND;
	
	do 
	{
		
		//Test the current game state
		switch(eCurrentState)
		{
			// there should be a state here for choosing speed and which player(s) are AI controlled
		case START_MATCH:
		{
			oLeftPlayer.Reset();
			oRightPlayer.Reset();
			eCurrentState = START_ROUND;
		}

		case START_ROUND:
		{
			poServingPlayer->Serve();
			eCurrentState = GAME_STATE;
			break;
		}
		
		case GAME_STATE:
		{
			DrawGame(fSpeed, oBackgroundSprite, oLeftPlayer, oRightPlayer, oBall);
			if (PlayerWins(oBall, oLeftPlayer, oRightPlayer, poServingPlayer, eCurrentState))
				break;
			PlayGame(oBall, oLeftPlayer, oRightPlayer);
			break;
		}

		// there should be a state here for choosing whether or not to continue

		default:
			break;
		}//End of Switch Statement


	} while ( FrameworkUpdate() == false );
	
	for each (Sprite* poSprite in apoSprites)
	{
		poSprite->Destroy();
	}
	Shutdown();

	return 0;
}

void DrawGame(const float ac_fSpeed,
			  Sprite& a_roBackground,
			  Player& a_roLeftPlayer,
			  Player& a_roRightPlayer,
			  Ball& a_roBall)
{
	float fDeltaT = GetDeltaTime();
	ClearScreen();
	Sprite* apoGameSprites[] = { &a_roBackground, &a_roLeftPlayer, &a_roRightPlayer, &a_roBall };
	for each (Sprite* poSprite in apoGameSprites)
	{
		poSprite->Update(fDeltaT * ac_fSpeed);
		poSprite->Draw();
	}
	char acScoreString[15];
	sprintf_s(acScoreString, 15, SCORE_FORMAT, a_roLeftPlayer.GetPlayerName(), a_roLeftPlayer.GetScore());
	DrawString(acScoreString, LEFT_SCORE_X, SCORE_Y);
	sprintf_s(acScoreString, 15, SCORE_FORMAT, a_roRightPlayer.GetPlayerName(), a_roRightPlayer.GetScore());
	DrawString(acScoreString, RIGHT_SCORE_X, SCORE_Y);
}

bool PlayerWins(Ball& a_roBall,
				Player& a_roLeftPlayer,
				Player& a_roRightPlayer,
				Player*& a_rpoServingPlayer,
				GameState& a_reGameState)
{
	float fBallX = a_roBall.GetPosition().x;
	if ((fBallX < LEFT_PLAYER_LOSES_X) || (fBallX > RIGHT_PLAYER_LOSES_X))
	{
		// right player wins
		a_rpoServingPlayer = (fBallX < LEFT_PLAYER_LOSES_X) ? &a_roRightPlayer : &a_roLeftPlayer;
		a_rpoServingPlayer->IncrementScore();
		a_roBall.Hide();
		unsigned int uiLeftScore = a_roLeftPlayer.GetScore();
		unsigned int uiRightScore = a_roRightPlayer.GetScore();
		if ((max(uiLeftScore, uiRightScore) >= 4) && (abs((int)uiLeftScore - (int)uiRightScore) >= 2))
			a_reGameState = START_MATCH;
		else
			a_reGameState = START_ROUND;
		return true;
	}
	return false;
}

void PlayGame(Ball& a_roBall, Player& a_roLeftPlayer, Player& a_roRightPlayer)
{
	if (a_roBall.CanRebound(MIN_Y, MAX_Y))
		a_roBall.BounceY();
	if (a_roLeftPlayer.CanHit())
		a_roLeftPlayer.Hit();
	if (a_roRightPlayer.CanHit())
		a_roRightPlayer.Hit();
}



