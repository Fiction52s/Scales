#include <string>
#include <iostream>
#include <time.h>
#include <random>
#include <map>
#include <vector>
#include <chrono>
#include <assert.h>

#include "Note.h"

using namespace std;

Scale majorScales[NUM_MAJOR_SCALES];

string sharps[NUM_NOTES_PER_SCALE] = {"G", "D", "A", "E", "B", "F#", "C#"};
string flats[NUM_NOTES_PER_SCALE] = { "F", "Bb", "Eb", "Ab", "Db", "Gb", "Cb" };

int AskNthOfMajorScale()
{
	int noteChoice = rand() % (NUM_NOTES_PER_SCALE-1);
	int scaleChoice = rand() % NUM_MAJOR_SCALES;

	string input;

	string scaleName = majorScales[scaleChoice].NameToString();

	cout << "What is the: " << numbers[noteChoice] << " of " << scaleName << "?  ";

	cin >> input;

	string noteStr = majorScales[scaleChoice].GetNote(noteChoice + 2).ToString();
	if (input == noteStr)//[noteChoice + 1])
	{
		cout << "Correct!" << endl;
		return 1;
	}
	else
	{
		cout << "Wrong. The " << numbers[noteChoice] << " of " << scaleName << " is " << noteStr << endl;
		return 0;
	}
}

int AskBackwardsNthOfMajorScale()
{
	int noteChoice = rand() % (NUM_NOTES_PER_SCALE - 1);
	int scaleChoice = rand() % NUM_MAJOR_SCALES;

	Note n = majorScales[scaleChoice].GetNote(noteChoice + 2);

	string scaleName = majorScales[scaleChoice].GetNote(1).ToString();

	string input;
	cout << n.ToString() << " is the " << numbers[noteChoice] << " of which major scale?  ";
	cin >> input;

	if (input == scaleName)//[noteChoice + 1])
	{
		cout << "Correct!" << endl;
		return 1;
	}
	else
	{
		cout << "Wrong. " << n.ToString() << " is the " << numbers[noteChoice] << " of " << scaleName << endl;
		return 0;
	}
}

int AskNumberOfSharps()
{
	int numSharps = (rand() % NUM_NOTES_PER_SCALE) + 1; //1-7

	cout << "Which key has " << numSharps << " sharps?  ";

	string input;
	cin >> input;

	if (input == sharps[numSharps - 1])
	{
		cout << "Correct!" << endl;
		return 1;
	}
	else
	{
		cout << "Wrong. The key with " << numSharps << " sharps is " << sharps[numSharps - 1] << endl;
		return 0;
	}
}

int AskNumberOfFlats()
{
	int numFlats = (rand() % NUM_NOTES_PER_SCALE) + 1; //1-7

	cout << "Which key has " << numFlats << " flats?  ";

	string input;
	cin >> input;

	if (input == flats[numFlats - 1])
	{
		cout << "Correct!" << endl;
		return 1;
	}
	else
	{
		cout << "Wrong. The key with " << numFlats << " flats is " << flats[numFlats - 1] << endl;
		return 0;
	}
}

int AskNumberOfAccidentals()
{
	int r = rand() % 2;

	if (r == 0)
	{
		return AskNumberOfSharps();
	}
	else
	{
		return AskNumberOfFlats();
	}
}

void FillMajorScales()
{
	/*{
		{ "C", "D", "E", "F", "G", "A", "B" },
		{ "D", "E", "F#", "G", "A", "B", "C#" },
		{ "E", "F#", "G#", "A", "B", "C#", "D#" },
		{ "F#", "G#", "A#", "B", "C#", "D#", "E#" },
		{ "Ab", "Bb", "C", "Db", "Eb", "F", "G" },
		{ "Bb", "C", "D", "Eb", "F", "G", "A" },
		{ "G", "A", "B", "C", "D", "E", "F#" },
		{ "A", "B", "C#", "D", "E", "F#", "G#" },
		{ "B", "C#", "D#", "E", "F#", "G#", "A#" },
		{ "Db", "Eb", "F", "Gb", "Ab", "Bb", "C" },
		{ "Eb", "F", "G", "Ab", "Bb", "C", "D" },
		{ "F", "G", "A", "Bb", "C", "D", "E" },
	};*/
	majorScales[0] = Scale(SCALE_MAJOR, LETTER_C, ACC_NEUTRAL);
	majorScales[1] = Scale(SCALE_MAJOR, LETTER_D, ACC_NEUTRAL);
	majorScales[2] = Scale(SCALE_MAJOR, LETTER_E, ACC_NEUTRAL);
	majorScales[3] = Scale(SCALE_MAJOR, LETTER_F, ACC_SHARP);
	majorScales[4] = Scale(SCALE_MAJOR, LETTER_A, ACC_FLAT);
	majorScales[5] = Scale(SCALE_MAJOR, LETTER_B, ACC_FLAT);
	majorScales[6] = Scale(SCALE_MAJOR, LETTER_G, ACC_NEUTRAL);
	majorScales[7] = Scale(SCALE_MAJOR, LETTER_A, ACC_NEUTRAL);
	majorScales[8] = Scale(SCALE_MAJOR, LETTER_B, ACC_NEUTRAL);
	majorScales[9] = Scale(SCALE_MAJOR, LETTER_D, ACC_FLAT);
	majorScales[10] = Scale(SCALE_MAJOR, LETTER_E, ACC_FLAT);
	majorScales[11] = Scale(SCALE_MAJOR, LETTER_F, ACC_NEUTRAL);
}

int main()
{
	FillMajorScales();

	while (true)
	{
		/*int scaleType = SCALE_MAJOR;
		int letter = LETTER_B;
		int acc = ACC_NEUTRAL;

		Note n(LETTER_F, ACC_NEUTRAL);
		Scale testScale = Scale::GetScaleThatNoteIsXthOf(SCALE_MAJOR, 6, n);
		cout << "test: ";
		testScale.PrintName();
		cout << endl;

		Scale s(scaleType, letter, acc);
		s.PrintName();
		cout << ": ";
		s.PrintNotes();
		cout << endl;

		int x;
		cin >> x;*/

		cout << "-----------ROUND START-----------" << endl;
		srand(time(0));

		auto startTime = chrono::high_resolution_clock::now();

		int numQuestions = 10;
		int totalScore = 0;
		for (int i = 0; i < numQuestions; ++i)
		{
			totalScore += AskBackwardsNthOfMajorScale();
			//totalScore += AskNthOfMajorScale();
			//totalScore += AskNumberOfAccidentals();
		}


		auto finishTime = chrono::high_resolution_clock::now();

		chrono::duration<double> totalTime = finishTime - startTime;

		cout << "---------------------------------" << endl;
		cout << "You scored: " << totalScore << "/" << numQuestions << endl;
		cout << "You took " << totalTime.count() << " seconds." << endl;
		cout << "\n\n\n\n" << endl;
	}
}