// high_scores.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

#define LIST_SIZE 10

void ScoreUpdate(const unsigned long long ca_ullNewScore,
				 const string ca_oNewScorer,
				 unsigned long long (&a_raullScores)[LIST_SIZE],
				 string (&a_raullNames)[LIST_SIZE]);

int main(int argc, char* argv[])
{
	//const unsigned int LIST_SIZE = 10;
	string aoNames[10];
	unsigned long long aullScores[10];

	unsigned int uiIndex = 0;

	while (uiIndex < LIST_SIZE) {
		string oName = "";
		string oUnparsedScore = "";
		unsigned long long ullScore = 0;

		do
		{
			cout << "Please enter a name: ";
			getline(cin, oName);
		} while (oName.empty());

		do
		{
			cout << "Please enter a score (a positive integer): ";
			getline(cin, oUnparsedScore);
			if (oUnparsedScore.empty()) {
				continue;
			}
			unsigned int iFirstUnconvertedCharPosition = oUnparsedScore.length();
			try
			{
				ullScore = stoull(oUnparsedScore, &iFirstUnconvertedCharPosition);
			}
			catch(exception oException)
			{
				cout << "\"" << oUnparsedScore << "\" is not a valid score." << endl;
				oUnparsedScore = "";
			}
			if (iFirstUnconvertedCharPosition < oUnparsedScore.length())
			{
				cout << "\"" << oUnparsedScore << "\" is not a valid score." << endl;
				oUnparsedScore = "";
			}
		} while (oUnparsedScore.empty());

		aoNames[uiIndex] = oName;
		aullScores[uiIndex] = ullScore;
		uiIndex++;
	}

	cout << endl << "HIGH SCORES" << endl << "-----------" << endl;

	for(uiIndex = 0; uiIndex < LIST_SIZE - 1; uiIndex++)
	{
		unsigned int uiHighestLaterScoreIndex = uiIndex + 1;
		for (unsigned int ui = uiIndex + 2; ui < LIST_SIZE; ui++)
		{
			if (aullScores[ui] > aullScores[uiHighestLaterScoreIndex])
				uiHighestLaterScoreIndex = ui;
		}
		unsigned long long ullHighestLaterScore = aullScores[uiHighestLaterScoreIndex];
		string oHighestLaterScorerName = aoNames[uiHighestLaterScoreIndex];

		if (aullScores[uiIndex] >= ullHighestLaterScore)	// don't rearrange scores that are already in order
		{
			cout << "#" << (uiIndex + 1) << ": \t" << aullScores[uiIndex] << "\t" << aoNames[uiIndex] << endl;
			uiIndex++;
		}

		if (uiHighestLaterScoreIndex > uiIndex)	// don't swap a score with itself, if the next highest score was just the next score
		{
			aullScores[uiHighestLaterScoreIndex] = aullScores[uiIndex];
			aoNames[uiHighestLaterScoreIndex] = aoNames[uiIndex];
			aullScores[uiIndex] = ullHighestLaterScore;
			aoNames[uiIndex] = oHighestLaterScorerName;
		}
		cout << "#" << (uiIndex + 1) << ": \t" << aullScores[uiIndex] << "\t" << aoNames[uiIndex] << endl;
	}
	
	cout << endl << "Press any key to exit...";
	getch();
	return 0;
}

void ScoreUpdate(const unsigned long long ca_ullNewScore,
				 const string ca_oNewScorer,
				 unsigned long long (&a_raullScores)[LIST_SIZE],
				 string (&a_raullNames)[LIST_SIZE])
{
}

