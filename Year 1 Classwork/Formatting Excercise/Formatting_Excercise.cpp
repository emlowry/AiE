/*************************************************************************************************
 * File:               Formatting_Excercise.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       September 17, 2013
 * Description:        Problem 1 in the Algorithm Design and Function Pseudocode lab.
 * Last Modified:      September 17, 2013
 * Last Modification:  Creation.
 *************************************************************************************************/

#include <iostream>

int main()
{
	int iDay,iMonth;	// variables for holding month and day of the month
	bool bCorrectDate = false;	// Has the day of the month been confirmed as valid?

	// Get the month
	std::cout << "What is the current month number? (1-12)";
	std::cin >> iMonth;

	// Make sure to get a valid month
	while(iMonth < 1 || iMonth > 12)
	{
		std::cout << "Please enter a valid month (1-12): ";
		std::cin >> iMonth;
	}

	// Get the date
	std::cout << "What is the current date? (1-31)";
	std::cin >> iDay;

	// Make sure to get a valid day of the month
	while(!bCorrectDate)
	{
		switch(iMonth)
		{
		// Thirty days have
		case 9:	// September,
		case 4:	// April,
		case 6:	// June,
		case 11:	// and November.
			if(iDay > 0 && iDay < 31)
				bCorrectDate = true;
			break;

		// All the rest have Thirty-one,
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			if(iDay > 0 && iDay < 32)
				bCorrectDate = true;
			break;

		// save February.
		case 2:
			if(iDay > 0 && iDay < 29)
				bCorrectDate = true;
			break;
		}

		// If the day of the month wasn't valid for the given month, get a new one
		if(!bCorrectDate)
		{
			std::cout << "Please enter a correct date: ";
			std::cin >> iDay;
		}
	}	// finished verifying day of the month
}

/* Pseudocode for Excercise 2:

// In ScreenObject.h:
	class ScreenObject
	{
	public:

		// ... Other public declarations, including constructor(s), go here ...

		void ScrollPosition();

	private:

		struct Position
		{
			float x;
			float y;
		}

		const unsigned int SCREEN_WIDTH = 600;
		const unsigned int SCREEN_HEIGHT = 800;

		Position position;

		// ... Other private declarations go here ...

	}

// In ScreenObject.cpp:

	void ScreenObject::ScrollPosition()
	{
		if (position.x >= SCREEN_WIDTH)
			position.x -= SCREEN_WIDTH;
		else if (position.x < 0)
			position.x += SCREEN_WIDTH;

		if (position.y >= SCREEN_HEIGHT)
			position.y -= SCREEN_HEIGHT;
		else if (position.y < 0)
			position.y += SCREEN_HEIGHT;
	}

// In file containing main function:

	void ScrollPositions(Collection<ScreenObject*> a_oObjects);

	// ... Other code, including the main function, goes here ...

	void ScrollPositions(Collection<ScreenObject*> a_oObjects)
	{
		for each (ScreenObject* o in a_oObjects)
			o->ScrollPosition();
	}
*/

/* Pseudocode for Excercise 3:

	struct Position
	{
		float x;
		float y;
	}

	Position NextPosition(Position a_sGhost, Position a_sPacman)
	{
		Position asPossible[] =
		{
			{ min(a_sGhost.x + 1, SCREEN_WIDTH), a_sGhost.y },
			{ max(a_sGhost.x - 1, 0), a_sGhost.y },
			{ a_sGhost.x, min(a_sGhost.y + 1, SCREEN_HEIGHT) },
			{ a_sGhost.x, max(a_sGhost.y - 1, 0) }
		};
		unsigned int finalDistance = MAX_INT;
		Position sResult = a_sGhost;
		for(unsigned int ui = 0; ui < 4; ui++)
		{
			if (!SquareIsEmpty(asPossible[ui]))
				continue;
			possibleDistance = max( abs(a_sPacman.x - asPossible[ui].x),
									abs(a_sPacman.y - asPossible[ui].y) );
			if (finalDistance <= possibleDistance)
				continue;
			finalDistance = possibleDistance;
			sResult = asPossible[ui];
		}
		return result;
	}

*/