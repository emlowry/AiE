/******************************************************************************
 * File:              main.cpp
 * Author:            Elizabeth Lowry
 * Date Created:      September 10, 2013
 * Description:       Main function for the Pong program.
 * Last Modified:     September 17, 2013
 * Last Modification: Refactoring.
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
const float FAST_SPEED = 3000.0f;
const int LEFT_PLAYER_LOSES_X = 200;
const Sprite::Vector LEFT_PLAYER_START_POSITION = {240,396};
const int LEFT_SCORE_X = 100;
const int MAX_Y = 645;
const float MEDIUM_SPEED = 2000.0f;
const int MIN_Y = 147;
const char* SCORE_FORMAT = "%s: %d";
const int SCORE_Y = 700;
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

enum Speed
{
	SLOW,
	MEDIUM,
	FAST
};

enum HumanPlayers
{
	LEFT,
	RIGHT,
	BOTH
};

float GetSpeed(const Speed ac_eSpeed);

void PlayGame(const Speed ac_eSpeed,
			  float& a_rfPlayTime,
			  Sprite& a_roBackground,
			  Player& a_roLeftPlayer,
			  Player& a_roRightPlayer,
			  Ball& a_roBall);

bool PlayerScores(Ball& a_roBall,
				  Player& a_roLeftPlayer,
				  Player& a_roRightPlayer,
				  Player*& a_rpoServingPlayer);

bool PlayerWins(const Player& ac_roLeftPlayer, const Player& ac_roPlayer);

void StartMatch(const HumanPlayers ac_eHumanPlayers,
				float& a_rfPlayTime,
				Player& a_roLeftPlayer,
				Player& a_roRightPlayer,
				Player*& a_rpoServingPlayer);

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

	Player* poServingPlayer = NULL;
	Speed eGameSpeed = MEDIUM;
	HumanPlayers eHumanPlayers = BOTH;

	GameState eCurrentState = START_MATCH;
	float fPlayTime = 0.0f;
	
	do 
	{
		
		//Test the current game state
		switch(eCurrentState)
		{
			// there should be a state here for choosing speed and which player(s) are AI controlled

		case START_MATCH:
			StartMatch(eHumanPlayers, fPlayTime, oLeftPlayer, oRightPlayer, poServingPlayer);
			eCurrentState = START_ROUND;

		case START_ROUND:
			poServingPlayer->Serve();
			eCurrentState = GAME_STATE;
			break;
		
		case GAME_STATE:
			PlayGame(eGameSpeed, fPlayTime, oBackgroundSprite, oLeftPlayer, oRightPlayer, oBall);
			if (PlayerScores(oBall, oLeftPlayer, oRightPlayer, poServingPlayer))
				eCurrentState = PlayerWins(oLeftPlayer, oRightPlayer) ? START_MATCH : START_ROUND;
			break;

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

float GetSpeed(const Speed ac_eSpeed)
{
	float fSpeed = MEDIUM_SPEED;
	switch(ac_eSpeed)
	{
	case FAST:
		fSpeed = FAST_SPEED;
		break;
	case SLOW:
		fSpeed = SLOW_SPEED;
		break;
	case MEDIUM:
	default:
		// speed is already set to medium
		break;
	}
	return fSpeed;
}

void PlayGame(const Speed ac_eSpeed,
			  float& a_rfPlayTime,
			  Sprite& a_roBackground,
			  Player& a_roLeftPlayer,
			  Player& a_roRightPlayer,
			  Ball& a_roBall)
{
	// Update Sprite Positions and Draw
	ClearScreen();
	float fDeltaT = GetDeltaTime();
	a_rfPlayTime += fDeltaT;	// keep track of total time for the match
	Sprite* apoGameSprites[] = { &a_roBackground, &a_roLeftPlayer, &a_roRightPlayer, &a_roBall };
	for each (Sprite* poSprite in apoGameSprites)
	{
		poSprite->Update(fDeltaT * GetSpeed(ac_eSpeed));
		poSprite->Draw();
	}

	// Find and react to collisions
	if (a_roBall.CanRebound(MIN_Y, MAX_Y))
		a_roBall.BounceY();
	if (a_roLeftPlayer.CanHit())
		a_roLeftPlayer.Hit();
	if (a_roRightPlayer.CanHit())
		a_roRightPlayer.Hit();

	// Draw scores
	char acScoreString[15];
	sprintf_s(acScoreString, 15, SCORE_FORMAT, a_roLeftPlayer.GetPlayerName(), a_roLeftPlayer.GetScore());
	DrawString(acScoreString, LEFT_SCORE_X, SCORE_Y);
	sprintf_s(acScoreString, 15, SCORE_FORMAT, a_roRightPlayer.GetPlayerName(), a_roRightPlayer.GetScore());
	DrawString(acScoreString, RIGHT_SCORE_X, SCORE_Y);
}

bool PlayerScores(Ball& a_roBall,
				  Player& a_roLeftPlayer,
				  Player& a_roRightPlayer,
				  Player*& a_rpoServingPlayer)
{
	float fBallX = a_roBall.GetPosition().x;
	if ((fBallX < LEFT_PLAYER_LOSES_X) || (RIGHT_PLAYER_LOSES_X < fBallX))
	{
		a_rpoServingPlayer = (fBallX < LEFT_PLAYER_LOSES_X) ? &a_roRightPlayer : &a_roLeftPlayer;
		a_rpoServingPlayer->IncrementScore();
		a_roBall.Hide();
		return true;
	}
	return false;
}

bool PlayerWins(const Player& ac_roLeftPlayer, const Player& ac_roRightPlayer)
{
	unsigned int uiLeftScore = ac_roLeftPlayer.GetScore();
	unsigned int uiRightScore = ac_roRightPlayer.GetScore();
	return ((max(uiLeftScore, uiRightScore) >= 4) &&
			(abs((int)uiLeftScore - (int)uiRightScore) >= 2));
}

void StartMatch(const HumanPlayers ac_eHumanPlayers,
				float& a_rfPlayTime,
				Player& a_roLeftPlayer,
				Player& a_roRightPlayer,
				Player*& a_rpoServingPlayer)
{
	a_roLeftPlayer.Reset();
	a_roRightPlayer.Reset();
	a_roLeftPlayer.SetMode(ac_eHumanPlayers != RIGHT ? Player::HUMAN : Player::AI);
	a_roRightPlayer.SetMode(ac_eHumanPlayers != LEFT ? Player::HUMAN : Player::AI);
	switch(ac_eHumanPlayers)
	{
	case LEFT:
		a_rpoServingPlayer = &a_roRightPlayer;
		break;
	case RIGHT:
		a_rpoServingPlayer = &a_roLeftPlayer;
		break;
	case BOTH:
	default:
		a_rpoServingPlayer = (rand()%2 == 0) ? &a_roLeftPlayer : &a_roRightPlayer;
		break;
	}
	a_rfPlayTime = 0.0f;
}




