/******************************************************************************
 * File:               Scores.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       September 23, 2013
 * Description:        Implementations for methods of the Scores class.
 * Last Modified:      September 24, 2013
 * Last Modification:  Starting to implement.
 ******************************************************************************/

#include "HighScores.h"
#include "MatchScore.h"
#include "StopWatch.h"
#include "AIE.h"

const XYPair HighScores::LIST_POSITION = {250,400};
const char* const HighScores::SCORE_PREFIX = "#%d:   ";

// Constructor instantiates most members in initializer list
HighScores::HighScores( const Player& a_roLeftPlayer,
						const Player& a_roRightPlayer,
						const StopWatch& a_roPlayTime,
						const Speed& a_reGameSpeed,
						const HumanPlayers& a_reHumanPlayers,
						const ScoreListType& a_reDisplayListType )
	: m_roLeftPlayer( a_roLeftPlayer ),
	  m_roRightPlayer( a_roRightPlayer ),
	  m_roPlayTime( a_roPlayTime ),
	  m_reGameSpeed( a_reGameSpeed ),
	  m_reHumanPlayers( a_reHumanPlayers ),
	  m_reDisplayListType( a_reDisplayListType )
{
	// instantiate all the score lists
	for( ScoreList* poScoreList = m_aoScoreLists;
		 poScoreList <
			m_aoScoreLists + ( NUMBER_OF_SPEEDS * NUMBER_OF_SCORE_LIST_TYPES );
		 ++poScoreList )
	{
		*poScoreList = ScoreList();
	}
}

// Add the score to a list.  Keep the list at or below max size.
void HighScores::AddScoreToList( const MatchScore& ac_roScore,
								 ScoreListType a_eListType )
{
	ScoreList& roScoreList = m_aoScoreLists[ScoreListIndex( a_eListType )];
	roScoreList.push_back( ac_roScore );
	roScoreList.sort( MatchScore::COMPARERS[a_eListType] );
	if( roScoreList.size() > SCORE_LIST_SIZE )
	{
		roScoreList.pop_back();
	}
}

// Draw the scores to the screen
void HighScores::Draw() const
{
	// Select the list to display
	const ScoreList& roScoreList =
		m_aoScoreLists[ScoreListIndex( m_reDisplayListType )];

	// Iterate through the list
	const unsigned int cuiBufferSize = 64;
	char acScoreTextBuffer[cuiBufferSize];
	ScoreList::const_iterator oScoreIterator = roScoreList.cbegin();
	for( unsigned int ui = 0;
		 oScoreIterator != roScoreList.cend();
		 ++ui, ++oScoreIterator )
	{
		// Print the place in the list
		sprintf_s( acScoreTextBuffer, cuiBufferSize, SCORE_PREFIX, ui + 1 );

		// Print the score after the place
		unsigned int uiStartPrint = strlen( acScoreTextBuffer );
		(*oScoreIterator).Print( acScoreTextBuffer + uiStartPrint,
								 cuiBufferSize - uiStartPrint );

		// Draw the string
		DrawString( acScoreTextBuffer,
					(int)LIST_POSITION.x,
					(int)LIST_POSITION.y + ( ui * LINE_SEPARATION ) );
	}
}

// Record the current score, time, speed, and set of human players.  Add the
// score to the appropriate group of lists.
void HighScores::RecordScore()
{
	// Create a score object
	MatchScore oMatchScore( m_reHumanPlayers,
							m_roPlayTime.GetTicks(),
							m_roLeftPlayer.GetScore(),
							m_roRightPlayer.GetScore() );
	
	// try adding this score to the list of high human scores
	AddScoreToList( oMatchScore, HIGH_SCORES );

	// If a human player won this match, try adding the score to the list of
	// fast human wins.
	if( oMatchScore.HumanWon() )
	{
		AddScoreToList( oMatchScore, FAST_WINS );
	}

	// If a human player lost this match, try adding the score to the list of
	// slow human losses.
	if( oMatchScore.HumanLost() )
	{
		AddScoreToList( oMatchScore, SLOW_LOSSES );
	}
}

// Given a score type, what is the array index for the score list of this type
// for the current game speed?
unsigned int HighScores::ScoreListIndex( const ScoreListType a_eListType ) const
{
	return ( m_reGameSpeed * NUMBER_OF_SCORE_LIST_TYPES ) + a_eListType;
}
