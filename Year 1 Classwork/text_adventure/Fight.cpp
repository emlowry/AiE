/******************************************************************************
 * File:         Fight.cpp
 * Author:       Elizabeth Lowry
 * Date Created: September 10, 2013
 * Brief:        Implements the class that runs fights.
 ******************************************************************************/

#include "Fight.h"
#include "Combatant.h"

const unsigned int Fight::NUMBER_OF_ANTAGONISTS = 4;
const unsigned int Fight::NUMBER_OF_PROTAGONISTS = 4;
const unsigned int Fight::INITIAL_HP = 100;
const unsigned int Fight::MAX_ATTACK = 100;
const unsigned int Fight::CRITICAL_HIT_THRESHOLD = 95; // roll higher than this to deal double damage
const unsigned int Fight::CRITICAL_MISS_THRESHOLD = 5; // roll this or lower to hurt yourself instead

Fight::Fight(void)
{
}

Fight::~Fight(void)
{
}

void Fight::AddProtagonist(Combatant& a_roProtagonist)
{
}

void Fight::AddAntagonist(Combatant& a_roAntagonist)
{
}

void Fight::Resolve()
{
}
