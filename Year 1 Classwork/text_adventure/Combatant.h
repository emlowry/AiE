/******************************************************************************
 * File:         Combatant.h
 * Author:       Elizabeth Lowry
 * Date Created: September 10, 2013
 * Brief:        Abstract base class defining what functions a character class
 *               needs in order to participate in a fight.
 ******************************************************************************/

#ifndef _COMBATANT_H_
#define _COMBATANT_H_

class Combatant
{
protected:
	Combatant(void) { }	// never called directly, only by child classes

public:
	virtual ~Combatant(void)=0;

	// abstract combat-related functions go here
};

#endif	// _COMBATANT_H_

