// scratchwork.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "tinyxml2.h"
#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <conio.h>

using namespace std;

const char ESCAPE = 27;
const char ENTER = 13;

/*
void PrintAsciiMan() {
	cout << "\\o/\n I\n/ \\" << endl;
}

float GetFloatFromUser(const string ca_oRequest, const string ca_oFailureMessage = "");

char GetCharFromUser(const string ca_oRequest, const string ca_oOptions = "", const string ca_oFailureMessage = "");

void DisplayMenu(const float ca_fFirstNumber, const float ca_fSecondNumber);

float PerformCalculation(const float ca_fFirstNumber, const float ca_fSecondNumber, const char ca_cOperation);

float Add(const float ca_fFirstNumber, const float ca_fSecondNumber);
float Subtract(const float ca_fFirstNumber, const float ca_fSecondNumber);
float Multiply(const float ca_fFirstNumber, const float ca_fSecondNumber);
float Divide(const float ca_fFirstNumber, const float ca_fSecondNumber);
float Modulo(const float ca_fFirstNumber, const float ca_fSecondNumber);

void ExcerciseTwoFunction(char* a_pcString);
unsigned int ExcerciseThreeFunction(char* a_pcString);
bool PasswordChecker(string oPassword);

float Average(const int (&ca_aiValues)[10]);
void DisplayTile(const int (ca_aiGrid)[8][8]);

struct Point2D
{
	float x;
	float y;
};

struct SimplePlayer
{
	unsigned long score;	// start at 0, usually
	unsigned int health;	// start at 100, usually
	float direction;		// angle
	Point2D position;
};

struct AlienGrunt
{
	Point2D target;
	Point2D position;
	unsigned int health;
	unsigned int bullets;
};

struct Point3D
{
	float x;
	float y;
	float z;
};
struct Color
{
	float red;
	float green;
	float blue;
	float alpha;
};

struct Triangle
{
	Point3D vertices[3];
	Color color;
};

struct Spaceship
{
	unsigned int health;
	unsigned int armorCapacity;
	unsigned int missiles[4];
	unsigned int laserBatteryHeat[6];
	Point3D position;
	Point3D velocity;
};

struct Gun
{
	unsigned int bullets;
	float cooldownPeriod;
};

struct ArmedPlayer
{
	Gun gun;
	unsigned int health;
	unsigned int armor;
	float smartBombChargePeriod;
	unsigned int smartBombs;
};

void expand( int*& a_raiArray, unsigned int& a_ruiCapacity );
void sort( int* const ac_aiArray, const unsigned int ac_uiSize );
/**/


struct Score
{
    string name;
    unsigned long points;
};

bool DescendingOrder( const Score& a_roFirstScore, const Score& a_roSecondScore );
void PrintScores( const list<Score>& a_roScores );
bool ReadScores( list<Score>& a_roScores, const string& a_roFileName );

int main(int argc, char* argv[])
{
/*	bool keepLooping = true;
	char currentChar = 0;
	string currentLine = "";
	cout << "Please enter some text (press q or ESC to quit): ";

	while(keepLooping)
	{
		currentChar = getch();
		switch(currentChar)
		{
		case ENTER:
			cout << endl << "\tYou entered: " << currentLine << endl << "\nPlease enter some text (press q or ESC to quit): ";
			currentLine = "";
			break;

		case 'q':
		case ESCAPE:
			keepLooping = false;
			break;

		default:
			cout << currentChar;
			currentLine += currentChar;
			break;
		}
	}
	
	for (int i = 1; i <= 10; i++)
	{
		for (int j = 1; j <= 10; j++)
			cout << j << " ";
		cout << endl;
	}

	for(unsigned int ui = 0; ui < 5; ui++)
	{
		PrintAsciiMan();
	}

	bool bKeepLooping = true;
	float fFirstNumber = GetFloatFromUser("Please enter your first number (it doesn't have to be positive or an integer)");
	do
	{
		float fSecondNumber = GetFloatFromUser("Please enter your second number (it doesn't have to be positive or an integer)");
		DisplayMenu(fFirstNumber, fSecondNumber);
		char cOperation = GetCharFromUser("Please enter an operation (+, -, *, /, or %)", "+-* /%");
		fFirstNumber = PerformCalculation(fFirstNumber, fSecondNumber, cOperation);
		cOperation = GetCharFromUser("Do you want to quit?  Enter \"y\" if yes, anything else if no");
		switch(cOperation)
		{
		case 'y':
		case 'Y':
			bKeepLooping = false;
			break;
		default:
			cout << endl << "The first number is now " << fFirstNumber << endl;
			break;
		}
	} while (bKeepLooping);

	char acName[256] = "";
	do
	{
	cout << "Please enter your name: ";
		try
		{
			cin.getline(acName, 256);
		}
		catch (exception oException)
		{
			strcpy(acName,"");
		}
	} while (strlen(acName) == 0);

	unsigned int uiUppercase = 0;
	unsigned int uiLowercase = 0;
	unsigned int uiDigit = 0;
	unsigned int uiSymbol = 0;
	for (unsigned int ui = 0; ui < strlen(acName); ui++)
	{
		if (acName[ui] >= 'A' && acName[ui] <= 'Z')
			uiUppercase++;
		else if (acName[ui] >= 'a' && acName[ui] <= 'z')
			uiLowercase++;
		else if (acName[ui] >= '0' && acName[ui] <= '9')
			uiDigit++;
		else if (acName[ui] >= '!')
			uiSymbol++;
	}
	string oName(acName);
	bool bPassword = PasswordChecker(oName);

	cout << "Excercise 1: \"" << acName << "\"" << endl;
	ExcerciseTwoFunction(acName);
	cout << "Excercise 2: \"" << acName << "\"" << endl;
	cout << "Excercise 3: " << ExcerciseThreeFunction(acName) << " total characters" << endl;
	cout << "Excercise 4: " << uiUppercase << " uppercase letters, "
							<< uiLowercase << " lowercase letters, "
							<< uiDigit << " digits, and "
							<< uiSymbol << " symbols" << endl;
	cout << "Password check: " << (bPassword ? "" : "in") << "valid password" << endl;

	cout << "Excercise 4: average of { ";
	int aiValues[10];
	for (unsigned int ui = 0; ui < 10; ui++)
	{
		aiValues[ui] = rand()%10;
		cout << (ui != 0 ? ", " : "") << aiValues[ui];
	}
	cout << " } is " << Average(aiValues) << endl;

	cout << "Excercise 5:" << endl;
	int aiGrid[8][8];
	for (unsigned int ui = 0; ui < 64; ui++)
		aiGrid[ui/8][ui%8] = ui + 1;
	DisplayTile(aiGrid);

	unsigned int uiSize = 0;
	unsigned int uiCapacity = 16;
	int* aiValues = new int[uiCapacity];

	cout << "Please enter a set of numbers separated by spaces: ";
	string oInput = "";
	while( oInput.empty() )
	{
		getline( cin, oInput );
	}
	istringstream oSin( oInput );
	int iInput;
	while( oSin >> iInput )
	{
		if( uiSize == uiCapacity )
		{
			expand( aiValues, uiCapacity );
		}
		aiValues[uiSize] = iInput;
		++uiSize;
	}
	cout << endl << "Here are your numbers sorted in ascending order:" << endl;
	sort( aiValues, uiSize );
	for( int* pi = aiValues; pi != aiValues + uiSize; ++pi )
	{
		cout << (pi == aiValues ? "" : " ") << *pi;
	}
	delete[] aiValues;
/**/

    // get file name
    string oFileName = "";
    do
    {
        cout << "Please enter a score file name (name must not include whitespace): ";
        cin >> oFileName;
    } while( oFileName.empty() );

    // read and print scores
    list<Score> oScores;
    if( ReadScores( oScores, oFileName ) )
    {
        oScores.sort( DescendingOrder );
        PrintScores( oScores );
    }

	cout << endl << endl << "Press any key to exit...";
	getch();
	/**/
	return 0;
}

inline bool DescendingOrder( const Score& a_roFirstScore, const Score& a_roSecondScore )
{
    return ( a_roFirstScore.points > a_roSecondScore.points );
}

void PrintScores( const list<Score>& a_roScores )
{
    cout << endl << "HIGH SCORES\n===========";
    unsigned int uiPlace = 1;
    for( list<Score>::const_iterator oIter = a_roScores.begin();
         a_roScores.end() != oIter;
         ++oIter, ++uiPlace )
    {
        cout << endl << "#" << uiPlace << ":\t" << (*oIter).points << "\t" << (*oIter).name;
    }
}

bool ReadScores( list<Score>& a_roScores, const string& a_roFileName )
{
    // try to open the XML file
    tinyxml2::XMLDocument oXML;
    tinyxml2::XMLError oError = oXML.LoadFile( a_roFileName.c_str() );
    if( tinyxml2::XML_SUCCESS != oError )
    {
        cout << "Unable to parse XML file.";
        return false;
    }

    // structure of XML file:
    // - scores         root element, FirstChildElement of the document
    // - - score        a single player score
    // - - - name       name of the player that made the score
    // - - - points     point value of the score
    tinyxml2::XMLElement* poRoot = oXML.FirstChildElement( "scores" );
    if( NULL == poRoot )
    {
        cout << "No score list in XML file.";
        return false;
    }
    if( poRoot->NoChildren() || NULL == poRoot->FirstChildElement( "score" ) )
    {
        cout << "No scores in list.";
        return false;
    }

    // loop through the score elements
    for( tinyxml2::XMLElement* poScore = poRoot->FirstChildElement( "score" );
         poScore != NULL;
         poScore = poScore->NextSiblingElement( "score" ) )
    {
        Score oValue;
        oValue.name = poScore->FirstChildElement( "name" )->GetText();
        string oPoints = poScore->FirstChildElement( "points" )->GetText();
        try
        {
            oValue.points = stoul( oPoints );
        }
        catch( exception oException )
        {
            continue;
        }
        a_roScores.push_back(oValue);
    }

    return true;
}

/*
void expand( int*& a_raiArray, unsigned int& a_ruiCapacity )
{
	int* aiNewArray = new int[a_ruiCapacity * 2];
	int* piNew = aiNewArray;
	memcpy( aiNewArray, a_raiArray, a_ruiCapacity );
	delete[] a_raiArray;
	a_raiArray = aiNewArray;
	a_ruiCapacity *= 2;
}

void sort( int* const ac_aiArray, const unsigned int ac_uiSize )
{
	if( ac_uiSize <= 1 )
		return;
	for( int* piCurrent = ac_aiArray;
		 piCurrent < ac_aiArray + ac_uiSize - 1;
		 ++piCurrent )
	{
		int* piSmallestFound = piCurrent + 1;
		for( int* piCandidate = piSmallestFound + 1;
			 piCandidate < ac_aiArray + ac_uiSize;
			 ++piCandidate )
		{
			if( *piCandidate < *piSmallestFound )
			{
				piSmallestFound = piCandidate;
			}
		}
		if( *piCurrent <= *piSmallestFound )
		{
			++piCurrent;
		}
		if( piSmallestFound != piCurrent )
		{
			int iValue = *piCurrent;
			*piCurrent = *piSmallestFound;
			*piSmallestFound = iValue;
		}
	}
}

void ExcerciseTwoFunction(char* a_pcString)
{
	for (unsigned int ui = 0; ui < strlen(a_pcString); ui++)
	{
		if (a_pcString[ui] == ' ')
			a_pcString[ui] = '_';
		else if (a_pcString[ui] >= 'A' && a_pcString[ui] <= 'Z')
			a_pcString[ui] += ('a' - 'A');
		else if (a_pcString[ui] >= 'a' && a_pcString[ui] <= 'z')
			a_pcString[ui] -= ('a' - 'A');
	}
}

unsigned int ExcerciseThreeFunction(char* a_pcString)
{
	unsigned int uiResult;
	for (uiResult = 0; a_pcString[uiResult] != 0; uiResult++);
	return uiResult;
}

bool PasswordChecker(string oPassword)
{
	if (oPassword.length() < 8)
		return false;
	bool bUppercase = false;
	bool bLowercase = false;
	unsigned int uiDigits = 0;
	for (unsigned int ui = 0; ui < oPassword.length(); ui++)
	{
		if (oPassword[ui] >= 'A' && oPassword[ui] <= 'Z')
			bUppercase = true;
		if (oPassword[ui] >= 'a' && oPassword[ui] <= 'z')
			bLowercase = true;
		if (oPassword[ui] >= '0' && oPassword[ui] <= '9')
			uiDigits++;
	}
	return (bUppercase && bLowercase && (uiDigits >= 3));
}

float Average(const int (&ca_aiValues)[10])
{
	float fSum = 0.0f;
	for(unsigned int ui = 0; ui < 10; ui++)
		fSum += ca_aiValues[ui];
	return fSum / 10;
}

void DisplayTile(const int (ca_aiGrid)[8][8])
{
	for (unsigned int uiRow = 0; uiRow < 8; uiRow++)
	{
		for (unsigned int uiColumn = 0; uiColumn < 8; uiColumn++)
			cout << '\t' << ca_aiGrid[uiRow][uiColumn];
		cout << endl;
	}
}

float GetFloatFromUser(const string ca_oRequest, const string ca_oFailureMessage)
{
	string oValue = "";
	float fValue = 0.0f;
	do
	{
		cout << ca_oRequest << ": ";
		getline(cin, oValue);
		if (oValue.empty())
			continue;

		unsigned int uiFirstUnconvertedCharIndex = oValue.length();
		exception* poException = NULL;
		try
		{
			fValue = stof(oValue, &uiFirstUnconvertedCharIndex);
		}
		catch (exception oException)
		{
			poException = &oException;
		}
		if (poException != NULL || uiFirstUnconvertedCharIndex < oValue.length())
		{
			if (!ca_oFailureMessage.empty())
				cout << ca_oFailureMessage << endl;
			oValue = "";
		}
	} while (oValue.empty());
	return fValue;
}

char GetCharFromUser(const string ca_oRequest, const string ca_oOptions, const string ca_oFailureMessage)
{
	string oValue = "";
	while(true)
	{
		cout << ca_oRequest << ": ";
		getline(cin, oValue);
		if (oValue.empty())
			continue;
		if (!ca_oFailureMessage.empty() && (oValue.length() > 1 || ca_oOptions.find(oValue[0]) == string::npos))
			cout << ca_oFailureMessage << endl;
		else
			return oValue[0];
	}
}

void DisplayMenu(const float ca_fFirstNumber, const float ca_fSecondNumber)
{
	cout << "The operation is " << ca_fFirstNumber << " ? " << ca_fSecondNumber << ", where ? can be any one of +, -, *, /, or %." << endl << endl
		 << "\t+\tAddition\tAdd " << ca_fSecondNumber << " to " << ca_fFirstNumber << endl
		 << "\t-\tSubtraction\tSubtract " << ca_fSecondNumber << " from " << ca_fFirstNumber << endl
		 << "\t*\tMultiplication\tMultiply " << ca_fFirstNumber << " by " << ca_fSecondNumber << endl
		 << "\t/\tDivision\tDivide " << ca_fFirstNumber << " by " << ca_fSecondNumber << endl
		 << "\t%\tModulo\tFind the remainder of the division of " << ca_fFirstNumber << " by " << ca_fSecondNumber << endl << endl;
}

float PerformCalculation(const float ca_fFirstNumber, const float ca_fSecondNumber, const char ca_cOperation)
{
	float fResult = ca_fFirstNumber;
	switch(ca_cOperation)
	{
	case '+':
		fResult = Add(ca_fFirstNumber, ca_fSecondNumber);
		break;
	case '-':
		fResult = Subtract(ca_fFirstNumber, ca_fSecondNumber);
		break;
	case '*':
		fResult = Multiply(ca_fFirstNumber, ca_fSecondNumber);
		break;
	case '/':
		fResult = Divide(ca_fFirstNumber, ca_fSecondNumber);
		break;
	case '%':
		fResult = Modulo(ca_fFirstNumber, ca_fSecondNumber);
		break;
	default:
		cout << "Hmm.  Somehow, an invalid operation made it past the input check.  I can't do anything with '" << ca_cOperation << "'" << endl;
		break;
	}
	return fResult;
}

float Add(const float ca_fFirstNumber, const float ca_fSecondNumber)
{
	float fResult = ca_fFirstNumber + ca_fSecondNumber;
	cout << ca_fFirstNumber << " + " << ca_fSecondNumber << " = " << fResult << endl;
	return fResult;
}

float Subtract(const float ca_fFirstNumber, const float ca_fSecondNumber)
{
	float fResult = ca_fFirstNumber - ca_fSecondNumber;
	cout << ca_fFirstNumber << " - " << ca_fSecondNumber << " = " << fResult << endl;
	return fResult;
}

float Multiply(const float ca_fFirstNumber, const float ca_fSecondNumber)
{
	float fResult = ca_fFirstNumber * ca_fSecondNumber;
	cout << ca_fFirstNumber << " * " << ca_fSecondNumber << " = " << fResult << endl;
	return fResult;
}

float Divide(const float ca_fFirstNumber, const float ca_fSecondNumber)
{
	if (ca_fSecondNumber == 0.0f)
	{
		cout << "No, you fool!  YOU'LL DOOM US ALL!!!" << endl;
		return ca_fFirstNumber;
	}
	float fResult = ca_fFirstNumber / ca_fSecondNumber;
	cout << ca_fFirstNumber << " / " << ca_fSecondNumber << " = " << fResult << endl;
	return fResult;
}

float Modulo(const float ca_fFirstNumber, const float ca_fSecondNumber)
{
	float fResult = ca_fFirstNumber;
	if (ca_fSecondNumber == 0.0f)
	{
		cout << "No, you fool!  YOU'LL DOOM US ALL!!!" << endl;
		return fResult;
	}
	if ((ca_fSecondNumber - (int) ca_fSecondNumber) == 0)
		fResult = ((int) ca_fFirstNumber % (int) ca_fSecondNumber) + (ca_fFirstNumber - (int) ca_fFirstNumber);
	else
		fResult = ca_fFirstNumber - ((((int) (ca_fFirstNumber / ca_fSecondNumber))) * ca_fSecondNumber);
	cout << ca_fFirstNumber << " % " << ca_fSecondNumber << " = " << fResult << endl;
	return fResult;
}
/**/
