/**************************************************************************************************
 * File:               Game.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       September 17, 2013
 * Description:        Implementations for methods of the Game class.
 * Last Modified:      September 17, 2013
 * Last Modification:  Moving code in from main.cpp.
 **************************************************************************************************/

#include "Game.h"
#include "Sprite.h"
#include "Ball.h"
#include "Player.h"
#include "AIE.h"

const char* const Game::BACKGROUND_TEXTURE_NAME = "./images/tennis_court.png";
const char* const Game::GAME_TITLE = "Pong, starring Venus and Serena Williams!";
const Sprite::Vector Game::LEFT_PLAYER_START_POSITION = {240,396};
const Sprite::Vector Game::RIGHT_PLAYER_START_POSITION = {960,396};
const char* const Game::SCORE_FORMAT = "%s: %d";
const char* const Game::TIME_FORMAT = "%d:%02d:%03d";

Game::Game()
	: m_oBackgroundSprite(BACKGROUND_TEXTURE_NAME,
						  SCREEN_WIDTH,
						  SCREEN_HEIGHT,
						  Sprite::DEFAULT_POSITION,
						  false),
	  m_oLeftPlayer(m_oBall, Player::LEFT, LEFT_PLAYER_START_POSITION, MIN_Y, MAX_Y),
	  m_oRightPlayer(m_oBall, Player::RIGHT, RIGHT_PLAYER_START_POSITION, MIN_Y, MAX_Y),
	  m_poServingPlayer(RandomPlayer()),
	  m_eGameSpeed(MEDIUM),
	  m_eHumanPlayers(BOTH),
	  m_fPlayTime(0.0f),
	  m_eState(START_MATCH)
{
	// Nothing else to do here
}

void Game::EnterMenu()
{
	m_fPlayTime = 0.0f;
	m_oLeftPlayer.Reset();
	m_oRightPlayer.Reset();
	m_oLeftPlayer.SetMode(Player::AI);
	m_oRightPlayer.SetMode(Player::AI);
	m_poServingPlayer = RandomPlayer();
}

void Game::FormatPlayTime(char* a_pcBuffer, unsigned int a_uiBufferSize, float a_fPlayTime)
{
	unsigned int uiMS = (unsigned int)(a_fPlayTime * 1000);
	unsigned int uiS = uiMS / 1000;
	uiMS %= 1000;
	unsigned int uiM = uiS / 60;
	uiS %= 60;
	sprintf_s(a_pcBuffer, a_uiBufferSize, TIME_FORMAT, uiM, uiS, uiMS);
}

float Game::GetSpeed(const Speed ac_eSpeed)
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

void Game::PlayGame()
{
	// Update Sprite Positions and Draw
	ClearScreen();
	float fDeltaT = GetDeltaTime();
	m_fPlayTime += fDeltaT;	// keep track of total time for the match
	Sprite* apoGameSprites[] = { &m_oBackgroundSprite, &m_oLeftPlayer, &m_oRightPlayer, &m_oBall };
	for each (Sprite* poSprite in apoGameSprites)
	{
		poSprite->Update(fDeltaT * GetSpeed(m_eGameSpeed));
		poSprite->Draw();
	}

	// Find and react to collisions
	if (m_oBall.CanRebound(MIN_Y, MAX_Y))
		m_oBall.BounceY();
	if (m_oLeftPlayer.CanHit())
		m_oLeftPlayer.Hit();
	if (m_oRightPlayer.CanHit())
		m_oRightPlayer.Hit();

	// Draw scores and time
	char acBuffer[15];
	sprintf_s(acBuffer, 15, SCORE_FORMAT, m_oLeftPlayer.GetPlayerName(), m_oLeftPlayer.GetScore());
	DrawString(acBuffer, LEFT_SCORE_X, SCORE_Y);
	sprintf_s(acBuffer, 15, SCORE_FORMAT, m_oRightPlayer.GetPlayerName(), m_oRightPlayer.GetScore());
	DrawString(acBuffer, RIGHT_SCORE_X, SCORE_Y);
	if (m_fPlayTime > 0.0f)
	{
		FormatPlayTime(acBuffer, 15, m_fPlayTime);
		DrawString(acBuffer, TIME_X, TIME_Y);
	}
}

bool Game::PlayerScores()
{
	float fBallX = m_oBall.GetPosition().x;
	if ((fBallX < LEFT_PLAYER_LOSES_X) || (RIGHT_PLAYER_LOSES_X < fBallX))
	{
		m_poServingPlayer = (fBallX < LEFT_PLAYER_LOSES_X) ? &m_oRightPlayer : &m_oLeftPlayer;
		m_poServingPlayer->IncrementScore();
		m_oBall.Hide();
		return true;
	}
	return false;
}

bool Game::PlayerWon()
{
	unsigned int uiLeftScore = m_oLeftPlayer.GetScore();
	unsigned int uiRightScore = m_oRightPlayer.GetScore();
	return ((max(uiLeftScore, uiRightScore) >= 4) &&
			(abs((int)uiLeftScore - (int)uiRightScore) >= 2));
}

Player* Game::RandomPlayer()
{
	return (rand()%2 == 0) ? &m_oLeftPlayer : &m_oRightPlayer;
}

bool Game::Run()
{
	switch(m_eState)
	{
		case ENTER_MENU:
			EnterMenu();
			m_eState = MENU;
			break;

		case MENU:
			m_eState = RunMenu();
			break;

		case START_MATCH:
			StartMatch();
			m_eState = START_ROUND;
			break;

		case START_ROUND:
			StartRound();
			m_eState = GAME_STATE;
			break;
		
		case GAME_STATE:
			PlayGame();
			if (PlayerScores())
				m_eState = PlayerWon() ? START_MATCH : START_ROUND;
			break;

		default:
			break;
	}
	return m_eState != END;
}

Game::GameState Game::RunMenu()
{
	float fDummyTime = 0.0f;
	PlayGame();
	if (PlayerScores())
	{
		if(PlayerWon())
		{
			m_oLeftPlayer.Reset();
			m_oRightPlayer.Reset();
		}
		m_poServingPlayer->Serve();
	}

	// TODO: draw actual menu

	return MENU;
}

void Game::Shutdown()
{
	Sprite* apoSprites[4] = { &m_oBackgroundSprite, &m_oLeftPlayer, &m_oRightPlayer, &m_oBall };
	for each (Sprite* poSprite in apoSprites)
		poSprite->Destroy();
}

void Game::StartMatch()
{
	m_oLeftPlayer.Reset();
	m_oRightPlayer.Reset();
	m_oLeftPlayer.SetMode(m_eHumanPlayers != RIGHT ? Player::HUMAN : Player::AI);
	m_oRightPlayer.SetMode(m_eHumanPlayers != LEFT ? Player::HUMAN : Player::AI);
	switch(m_eHumanPlayers)
	{
	case LEFT:
		m_poServingPlayer = &m_oRightPlayer;
		break;
	case RIGHT:
		m_poServingPlayer = &m_oLeftPlayer;
		break;
	case BOTH:
	default:
		m_poServingPlayer = (rand()%2 == 0) ? &m_oLeftPlayer : &m_oRightPlayer;
		break;
	}
	m_fPlayTime = 0.0f;
}

void Game::StartRound()
{
	m_poServingPlayer->Serve();
}
