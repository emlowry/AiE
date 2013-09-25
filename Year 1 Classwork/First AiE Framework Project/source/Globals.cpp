/******************************************************************************
 * File:               Globals.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       September 24, 2013
 * Description:        Implementations for global functions.
 * Last Modified:      September 24, 2013
 * Last Modification:  Creation.
 ******************************************************************************/

#include "Globals.h"
#include "AIE.h"
#include <cstring>

// Draw a string with newline ('\n') characters in it
void DrawMultilineString( const char* a_pcText,
						  int a_iXPos,
						  int a_iYPos,
						  SColour a_sColour )
{
	// Copy the string
	const unsigned int cuiLength = strlen(a_pcText);
	char* pcTextCopy;
	pcTextCopy = new char[cuiLength + 1];
	strcpy_s( pcTextCopy, cuiLength + 1, a_pcText );

	// loop through the tokens and draw them
	unsigned int uiLine = 0;
	char* pcContext = NULL;
	for( char* pcToken = strtok_s( pcTextCopy, "\n", &pcContext );
		 pcToken != NULL;
		 ++uiLine, pcToken = strtok_s( NULL, "\n", &pcContext ) )
	{
		DrawString( pcToken,
					a_iXPos,
					a_iYPos + ( LINE_SEPARATION * uiLine ),
					a_sColour );
	}

	// delete the copy
	delete [] pcTextCopy;
}

// If at least one of the given keys is pressed, return true
bool IsOneOfTheseKeysDown( const int* const ac_pciKeys,
								 const unsigned int ac_uiKeyCount )
{
	for( const int* pciKey = ac_pciKeys;
		 pciKey != ac_pciKeys + ac_uiKeyCount;
		 ++pciKey )
	{
		if( IsKeyDown( *pciKey ) )
		{
			return true;
		}
	}
	return false;
}