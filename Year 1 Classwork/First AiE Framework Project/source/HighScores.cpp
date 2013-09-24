/******************************************************************************
 * File:               Scores.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       September 23, 2013
 * Description:        Implementations for methods of the Scores class.
 * Last Modified:      September 23, 2013
 * Last Modification:  Created.  TODO: implementation
 ******************************************************************************/

#include "HighScores.h"
#include <cstdio>	// for sprintf_s

// leftScore-rightScore \t time \t human players
const char* const HighScores::SCORE_TEXT_FORMAT = "%d-%d\t%s\t%s vs. %s";

// Default constructor
HighScores::HighScores( const Player& a_roLeftPlayer,
						const Player& a_roRightPlayer,
						const StopWatch& a_roPlayTime,
						const Speed& a_reGameSpeed,
						const HumanPlayers& a_reHumanPlayers)
	: m_roLeftPlayer(a_roLeftPlayer),
	  m_roRightPlayer(a_roRightPlayer),
	  m_roPlayTime(a_roPlayTime),
	  m_reGameSpeed(a_reGameSpeed),
	  m_reHumanPlayers(a_reHumanPlayers)
{
}

// Draw the scores to the screen
void HighScores::Draw() const
{
}

// Record the current score, time, speed, and set of human players.  Add the
// score to a list, if appropriate.
void HighScores::RecordScore()
{
	Score oScore;
	oScore.leftScore = m_roLeftPlayer.GetScore();
	oScore.rightScore = m_roRightPlayer.GetScore();
	oScore.ticks = m_roPlayTime.GetTicks();
	char acBuffer[20];
	m_roPlayTime.PrintTime( acBuffer, 20 );
	sprintf_s( oScore.text,
			   SCORE_TEXT_BUFFER_SIZE,
			   SCORE_TEXT_FORMAT,
			   oScore.leftScore,
			   oScore.rightScore,
			   acBuffer,
			   m_reHumanPlayers != RIGHT ? "Human" : "AI",
			   m_reHumanPlayers != LEFT ? "Human" : "AI" );
}

// Destroy sprites
void HighScores::Shutdown()
{
}
