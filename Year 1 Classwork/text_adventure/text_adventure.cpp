/******************************************************************************
 * File:         text_adventure.cpp
 * Author:       Elizabeth Lowry
 * Date Created: September 10, 2013
 * Brief:        The main function for the text_adventure program.
 TODO: Walk, Jump, Attack, Sleep, Drink, Run, Die
 ******************************************************************************/

#include <iostream>
#include <string>

using namespace std;

// move all this stuff elsewhere
const unsigned int NUMBER_OF_ANTAGONISTS = 4;
const unsigned int NUMBER_OF_PROTAGONISTS = 4;
const unsigned int INITIAL_HP = 100;
const unsigned int MAX_ATTACK = 100;
const unsigned int CRITICAL_HIT_THRESHOLD = 95; // roll higher than this to deal double damage
const unsigned int CRITICAL_MISS_THRESHOLD = 5; // roll this or lower to hurt yourself instead

int main(int argc, char* argv[])
{
	unsigned int auiAntagonistHealthValues[NUMBER_OF_ANTAGONISTS];

	for (unsigned int ui = 0; ui < NUMBER_OF_ANTAGONISTS; ui++)
	{
		auiAntagonistHealthValues[ui] = INITIAL_HP;
	}

	cout << "ROUND #1" << endl << endl;

	for (unsigned int uiProtagonist = 0; uiProtagonist < NUMBER_OF_PROTAGONISTS; uiProtagonist++)
	{
		for (unsigned int uiAntagonist = 0; uiAntagonist < NUMBER_OF_ANTAGONISTS; uiAntagonist++)
		{
			unsigned int uiHP = auiAntagonistHealthValues[uiAntagonist];
			cout << "#" << (uiAntagonist + 1) << ":\tAntagonist\t" << uiHP << " HP" << (uiHP > 0 ? "" : " - DEAD") << endl;
		}

		cout << endl << "Attack #" << (uiProtagonist + 1) << endl << endl;

		string oTarget = "";
		unsigned long ulTarget = NUMBER_OF_ANTAGONISTS + 1;
		do
		{
			cout << "Choose the number of a target that isn't dead: ";
			getline(cin, oTarget);
			if (oTarget.empty())
				continue;
			
			unsigned int uiFirstUnconvertedCharPosition = oTarget.length();
			try
			{
				ulTarget = stoul(oTarget, &uiFirstUnconvertedCharPosition);
			}
			catch(exception oException)
			{
				cout << "That's not one of the targets!" << endl;
				ulTarget = NUMBER_OF_ANTAGONISTS + 1;
			}
			if (uiFirstUnconvertedCharPosition < oTarget.length() || ulTarget == 0 || ulTarget > NUMBER_OF_ANTAGONISTS)
			{
				cout << "That's not one of the targets!" << endl;
				ulTarget = NUMBER_OF_ANTAGONISTS + 1;
			}
			else if (auiAntagonistHealthValues[ulTarget] == 0)
			{
				cout << "That target is already dead!" << endl;
				ulTarget = NUMBER_OF_ANTAGONISTS + 1;
			}

		} while (ulTarget > NUMBER_OF_ANTAGONISTS);
		ulTarget--;	// since arrays are indexed starting with 0, not 1
		
		string oDamage = "";
		unsigned long ulDamage = MAX_ATTACK + 1;
		do
		{
			cout << "Choose the amount of damage (1 to " << MAX_ATTACK << " - the higher the damage, the higher the chance of failure) to attempt: ";
			getline(cin, oDamage);
			if (oDamage.empty())
				continue;
			
			unsigned int uiFirstUnconvertedCharPosition = oDamage.length();
			try
			{
				ulDamage = stoull(oDamage, &uiFirstUnconvertedCharPosition);
			}
			catch(exception oException)
			{
				cout << "That's not a valid damage value!" << endl;
				ulDamage = MAX_ATTACK + 1;
			}
			if (uiFirstUnconvertedCharPosition < oDamage.length() || ulDamage == 0 || ulDamage > MAX_ATTACK)
			{
				cout << "That's not a valid damage value!" << endl;
				ulDamage = MAX_ATTACK + 1;
			}

		} while (ulDamage > MAX_ATTACK);

		unsigned int ulDiceRoll = (rand()%MAX_ATTACK) + 1;
		if (ulDiceRoll > CRITICAL_HIT_THRESHOLD && ulDiceRoll >= ulDamage)
		{
			cout << "Critical hit!  You deal " << (ulDamage * 2) << " damage to Antagonist!";
			if (auiAntagonistHealthValues[ulTarget] <= (ulDamage * 2))
				auiAntagonistHealthValues[ulTarget] = 0;
			else
				auiAntagonistHealthValues[ulTarget] -= ulDamage * 2;
		}
		else if (ulDiceRoll >= ulDamage)
		{
			cout << "Hit!  You deal " << ulDamage << " damage to Antagonist.";
			if (auiAntagonistHealthValues[ulTarget] <= ulDamage)
				auiAntagonistHealthValues[ulTarget] = 0;
			else
				auiAntagonistHealthValues[ulTarget] -= ulDamage;
		}
		else if (ulDiceRoll <= CRITICAL_MISS_THRESHOLD)
		{
			cout << "Critical miss!  If protagonists were implemented yet, the one launching this attack would take damage!";
		}
		else
		{
			cout << "Miss!  You deal no damage.";
		}
		cout << endl << endl;
	}

	cout << endl << "END OF ROUND:\n-------------" << endl;
	for (unsigned int uiAntagonist = 0; uiAntagonist < NUMBER_OF_ANTAGONISTS; uiAntagonist++)
	{
		unsigned int uiHP = auiAntagonistHealthValues[uiAntagonist];
		cout << "#" << (uiAntagonist + 1) << ":\tAntagonist\t" << uiHP << " HP" << (uiHP > 0 ? "" : " - DEAD") << endl;
	}
	
	cout << endl << "Press any key to exit...";
	getch();
	
	return 0;
}

