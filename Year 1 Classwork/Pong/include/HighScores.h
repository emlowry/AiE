/******************************************************************************
 * File:               HighScores.h
 * Author:             Elizabeth Lowry
 * Date Created:       September 23, 2013
 * Description:        Definitions for the class that handles high score lists.
 * Last Modified:      September 24, 2013
 * Last Modification:  Debugging.
 ******************************************************************************/

#ifndef _HIGH_SCORES_H_
#define _HIGH_SCORES_H_

#include "Globals.h"
#include "MatchScore.h"
#include "Player.h"
#include "StopWatch.h"
#include <list>

// Manages the game's high score lists
class HighScores
{
public:

	HighScores( const Player& a_roLeftPlayer,
				const Player& a_roRightPlayer,
				const StopWatch& a_roPlayTime,
				const Speed& a_reGameSpeed,
				const HumanPlayers& a_reHumanPlayers,
				const ScoreListType& a_reDisplayListType );

	void Draw() const;
	void RecordScore();

private:

	typedef std::list<MatchScore> ScoreList;

	void AddScoreToList( const MatchScore& ac_roScore,
						 ScoreListType a_eListType );
	unsigned int ScoreListIndex( const ScoreListType a_eListType ) const;

	static const XYPair LIST_POSITION;
	static const unsigned int SCORE_LIST_SIZE = 5;
	static const char* const SCORE_PREFIX;	// "#%d:   "

	const Player& m_roLeftPlayer;
	const Player& m_roRightPlayer;
	const StopWatch& m_roPlayTime;
	const Speed& m_reGameSpeed;
	const HumanPlayers& m_reHumanPlayers;
	const ScoreListType& m_reDisplayListType;	// What type of list do we draw?

	ScoreList m_aoScoreLists[NUMBER_OF_SPEEDS * NUMBER_OF_SCORE_LIST_TYPES];

};

#endif	// _HIGH_SCORES_H_