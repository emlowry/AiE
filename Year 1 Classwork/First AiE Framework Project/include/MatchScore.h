/******************************************************************************
 * File:               MatchScore.h
 * Author:             Elizabeth Lowry
 * Date Created:       September 24, 2013
 * Description:        Definitions for the class that handles the score from a
 *                       single match.
 * Last Modified:      September 24, 2013
 * Last Modification:  Created.
 ******************************************************************************/

#ifndef _MATCH_SCORE_H_
#define _MATCH_SCORE_H_

#include "Globals.h"

// Stores the score from a single match
class MatchScore
{
public:
	
	typedef bool (*ScoreComparer)( const MatchScore&, const MatchScore& );

	MatchScore( HumanPlayers a_eHumanPlayers,
				unsigned long a_ulTicks,
				unsigned int a_uiLeftScore,
				unsigned int a_uiRightScore );
	bool HumanLost() const;
	bool HumanWon() const;
	static void Print( char* a_pcBuffer,
					   unsigned int a_uiBufferSize,
					   const MatchScore& a_roScore );
	void Print( char* a_pcBuffer, unsigned int a_uiBufferSize ) const;

	static const ScoreComparer COMPARERS[NUMBER_OF_SCORE_LIST_TYPES];

private:
	
	static bool CompareAscendingHumanWinTime( const MatchScore& a_roFirstScore,
											  const MatchScore& a_roSecondScore );
	static bool CompareDescendingHumanLossTime( const MatchScore& a_roFirstScore,
												const MatchScore& a_roSecondScore );
	static bool CompareDescendingHumanPoints( const MatchScore& a_roFirstScore,
											  const MatchScore& a_roSecondScore );
	unsigned int HigherHumanScore() const;

	// leftScore-rightScore   time   human players
	static const char* const SCORE_TEXT_FORMAT;

	HumanPlayers m_eHumanPlayers;
	unsigned long m_ulTicks;
	unsigned int m_uiLeftScore;
	unsigned int m_uiRightScore;

};

#endif	// _MATCH_SCORE_H_