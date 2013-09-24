/******************************************************************************
 * File:               HighScores.h
 * Author:             Elizabeth Lowry
 * Date Created:       September 23, 2013
 * Description:        Definitions for the class that handles high score lists.
 * Last Modified:      September 23, 2013
 * Last Modification:  Created.
 ******************************************************************************/

#ifndef _HIGH_SCORES_H_
#define _HIGH_SCORES_H_

#include "EnumsAndStructs.h"
#include "StopWatch.h"
#include "Player.h"

class HighScores
{
public:

	HighScores( const Player& a_roLeftPlayer,
				const Player& a_roRightPlayer,
				const StopWatch& a_roPlayTime,
				const Speed& a_reGameSpeed,
				const HumanPlayers& a_reHumanPlayers );

	void Draw() const;
	void RecordScore();
	void Shutdown();

private:

	struct Score
	{
		unsigned long long ticks;
		unsigned int leftScore;
		unsigned int rightScore;
		char text[50];
	};

	static const unsigned int SCORE_TEXT_BUFFER_SIZE = 50;
	// leftScore-rightScore \t time \t human players
	static const char* const SCORE_TEXT_FORMAT;

	const Player& m_roLeftPlayer;
	const Player& m_roRightPlayer;
	const StopWatch& m_roPlayTime;
	const Speed& m_reGameSpeed;
	const HumanPlayers& m_reHumanPlayers;

};

#endif	// _HIGH_SCORES_H_