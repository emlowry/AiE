/******************************************************************************
 * File:               MatchScore.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       September 24, 2013
 * Description:        Definitions for the class that handles the score from a
 *                       single match.
 * Last Modified:      September 24, 2013
 * Last Modification:  Created.
 ******************************************************************************/

#include "Globals.h"
#include "MatchScore.h"
#include "StopWatch.h"	// for StopWatch::Print
#include <algorithm>	// for max
#include <cstdio>	// for sprintf_s

const MatchScore::ScoreComparer MatchScore::COMPARERS[NUMBER_OF_SCORE_LIST_TYPES] =
{
	MatchScore::CompareDescendingHumanPoints,	// HIGH_SCORES
	MatchScore::CompareAscendingHumanWinTime,	// FAST_WINS
	MatchScore::CompareDescendingHumanLossTime,	// SLOW_LOSSES
};
// leftScore-rightScore \t time \t human players
const char* const MatchScore::SCORE_TEXT_FORMAT = "%d-%d   %s   %s";

// Constructor instantiates all members in initializer list
MatchScore::MatchScore( HumanPlayers a_eHumanPlayers,
						unsigned long a_ulTicks,
						unsigned int a_uiLeftScore,
						unsigned int a_uiRightScore )
	: m_eHumanPlayers( a_eHumanPlayers ),
	  m_ulTicks( a_ulTicks ),
	  m_uiLeftScore( a_uiLeftScore ),
	  m_uiRightScore( a_uiRightScore )
{
}

// Returns true if the first score has a faster human win time than the second
// score.
bool MatchScore::CompareAscendingHumanWinTime( const MatchScore& a_roFirstScore,
											   const MatchScore& a_roSecondScore )
{
	// If humans won in both scores (or didn't win in both scores), return true
	// if the first score was won faster.
	if ( a_roFirstScore.HumanWon() == a_roSecondScore.HumanWon() )
	{
		return ( a_roFirstScore.m_ulTicks < a_roSecondScore.m_ulTicks );
	}

	// Otherwise, return true if the first score was won by a human
	return a_roFirstScore.HumanWon();
}

// Returns true if the first score has a slower human loss time than the second
// score.
bool MatchScore::CompareDescendingHumanLossTime( const MatchScore& a_roFirstScore,
												 const MatchScore& a_roSecondScore )
{
	// If humans lost in both scores (or didn't lose in both scores), return
	// true if the first score was lost more slowly.
	if ( a_roFirstScore.HumanWon() == a_roSecondScore.HumanWon() )
	{
		return ( a_roFirstScore.m_ulTicks > a_roSecondScore.m_ulTicks );
	}

	// Otherwise, return true if the first score was lost by a human
	return a_roFirstScore.HumanLost();
}

// Returns true if the left score has a higher number of points scored by a
// human than the right score.
bool MatchScore::CompareDescendingHumanPoints( const MatchScore& a_roFirstScore,
											   const MatchScore& a_roSecondScore )
{
	return ( a_roFirstScore.HigherHumanScore() < a_roSecondScore.HigherHumanScore() );
}

// Get the higher human score in a score struct
unsigned int MatchScore::HigherHumanScore() const
{
	switch( m_eHumanPlayers )
	{
	// breaks for these cases should never be reached, but are
	// included to indicate intent and in case the code changes.
	case LEFT: return m_uiLeftScore; break;
	case RIGHT: return m_uiRightScore; break;
	case BOTH:
	default: break;	// fall out of the switch...
	}
	// ... and return the higher point value.
	return std::max( m_uiLeftScore, m_uiRightScore );
}

// Did a human lose in the given score?
bool MatchScore::HumanLost() const
{
	// If both players were human, the answer is obviously yes.
	if( m_eHumanPlayers == BOTH )
	{
		return true;
	}

	// otherwise, return true if the human had the lower score
	return ( ( m_eHumanPlayers == LEFT && m_uiLeftScore < m_uiRightScore ) ||
			 ( m_eHumanPlayers == RIGHT && m_uiLeftScore > m_uiRightScore ) );
}

// Did a human win in the given score?
bool MatchScore::HumanWon() const
{
	// If both players were human, the answer is obviously yes.
	if( m_eHumanPlayers == BOTH )
	{
		return true;
	}

	// otherwise, return true if the human had the higher score
	return ( ( m_eHumanPlayers == LEFT && m_uiLeftScore > m_uiRightScore ) ||
			 ( m_eHumanPlayers == RIGHT && m_uiLeftScore < m_uiRightScore ) );
}

// Print a score to the provided char array (static version)
void MatchScore::Print( char* a_pcBuffer,
						unsigned int a_uiBufferSize,
						const MatchScore& a_roScore )
{
	char acTimeText[20];
	StopWatch::Print( acTimeText, 20, a_roScore.m_ulTicks );
	sprintf_s( a_pcBuffer,
			   a_uiBufferSize,
			   SCORE_TEXT_FORMAT,
			   a_roScore.m_uiLeftScore,
			   a_roScore.m_uiRightScore,
			   acTimeText,
			   HUMAN_PLAYER_STRINGS[a_roScore.m_eHumanPlayers] );
}

// Print a score to the provided char array (const version)
void MatchScore::Print( char* a_pcBuffer, unsigned int a_uiBufferSize ) const
{
	Print( a_pcBuffer, a_uiBufferSize, *this );
}