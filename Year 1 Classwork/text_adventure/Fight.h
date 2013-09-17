/******************************************************************************
 * File:         Fight.h
 * Author:       Elizabeth Lowry
 * Date Created: September 10, 2013
 * Brief:        Defines the class that runs fights.
 ******************************************************************************/

#ifndef _FIGHT_H_
#define _FIGHT_H_

#include "Combatant.h"

class Fight
{
public:
	Fight(void);
	~Fight(void);

	void AddProtagonist(Combatant& a_roProtagonist);
	void AddAntagonist(Combatant& a_roAntagonist);
	void Resolve();

private:
	static const unsigned int NUMBER_OF_ANTAGONISTS;
	static const unsigned int NUMBER_OF_PROTAGONISTS;
	static const unsigned int INITIAL_HP;
	static const unsigned int MAX_ATTACK;
	static const unsigned int CRITICAL_HIT_THRESHOLD; // roll higher than this to deal double damage
	static const unsigned int CRITICAL_MISS_THRESHOLD; // roll this or lower to hurt yourself instead
};

#endif	// _FIGHT_H_

