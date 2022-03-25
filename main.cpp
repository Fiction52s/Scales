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

Scale scales[SCALE_Count][NUM_MAJOR_SCALES];

string majorSharps[NUM_NOTES_PER_SCALE] = {"G", "D", "A", "E", "B", "F#", "C#"};
string majorFlats[NUM_NOTES_PER_SCALE] = { "F", "Bb", "Eb", "Ab", "Db", "Gb", "Cb" };

void FillScales()
{
	scales[SCALE_MAJOR][0] = Scale(SCALE_MAJOR, LETTER_C, ACC_NEUTRAL);
	scales[SCALE_MAJOR][1] = Scale(SCALE_MAJOR, LETTER_D, ACC_NEUTRAL);
	scales[SCALE_MAJOR][2] = Scale(SCALE_MAJOR, LETTER_E, ACC_NEUTRAL);
	scales[SCALE_MAJOR][3] = Scale(SCALE_MAJOR, LETTER_F, ACC_SHARP);
	scales[SCALE_MAJOR][4] = Scale(SCALE_MAJOR, LETTER_A, ACC_FLAT);
	scales[SCALE_MAJOR][5] = Scale(SCALE_MAJOR, LETTER_B, ACC_FLAT);
	scales[SCALE_MAJOR][6] = Scale(SCALE_MAJOR, LETTER_G, ACC_NEUTRAL);
	scales[SCALE_MAJOR][7] = Scale(SCALE_MAJOR, LETTER_A, ACC_NEUTRAL);
	scales[SCALE_MAJOR][8] = Scale(SCALE_MAJOR, LETTER_B, ACC_NEUTRAL);
	scales[SCALE_MAJOR][9] = Scale(SCALE_MAJOR, LETTER_D, ACC_FLAT);
	scales[SCALE_MAJOR][10] = Scale(SCALE_MAJOR, LETTER_E, ACC_FLAT);
	scales[SCALE_MAJOR][11] = Scale(SCALE_MAJOR, LETTER_F, ACC_NEUTRAL);

	scales[SCALE_MINOR][0] = Scale(SCALE_MINOR, LETTER_C, ACC_NEUTRAL);
	scales[SCALE_MINOR][1] = Scale(SCALE_MINOR, LETTER_G, ACC_NEUTRAL);
	scales[SCALE_MINOR][2] = Scale(SCALE_MINOR, LETTER_D, ACC_NEUTRAL);
	scales[SCALE_MINOR][3] = Scale(SCALE_MINOR, LETTER_A, ACC_NEUTRAL);
	scales[SCALE_MINOR][4] = Scale(SCALE_MINOR, LETTER_E, ACC_NEUTRAL);
	scales[SCALE_MINOR][5] = Scale(SCALE_MINOR, LETTER_B, ACC_NEUTRAL);
	scales[SCALE_MINOR][6] = Scale(SCALE_MINOR, LETTER_F, ACC_SHARP);
	scales[SCALE_MINOR][7] = Scale(SCALE_MINOR, LETTER_C, ACC_SHARP);
	scales[SCALE_MINOR][8] = Scale(SCALE_MINOR, LETTER_G, ACC_SHARP);
	scales[SCALE_MINOR][9] = Scale(SCALE_MINOR, LETTER_E, ACC_FLAT);
	scales[SCALE_MINOR][10] = Scale(SCALE_MINOR, LETTER_B, ACC_FLAT);
	scales[SCALE_MINOR][11] = Scale(SCALE_MINOR, LETTER_F, ACC_NEUTRAL);

	chordQualityNames["M"] = "Major";
	chordQualityNames["m"] = "minor";
	chordQualityNames["d"] = "diminished";
	chordQualityNames["A"] = "Augmented";
}

enum QuestionType
{
	Q_NTH_OF_SCALE,
	Q_BACKWARDS_NTH_OF_SCALE,
	Q_ACCIDENTALS,
	Q_CHORD_QUALITIES,
	Q_LIST_CHORD,
	Q_Count
};

int AskNthOfScale( int scaleType )
{
	int noteChoice = rand() % (NUM_NOTES_PER_SCALE-1);
	int scaleChoice = rand() % NUM_MAJOR_SCALES;

	string scaleName = scales[scaleType][scaleChoice].NameToString();

	cout << "What is the " << numbers[noteChoice+1] << " of " << scaleName << "?  ";

	string input;
	cin >> input;

	string noteStr = scales[scaleType][scaleChoice].GetNote(noteChoice + 2).ToString();
	if (input == noteStr)//[noteChoice + 1])
	{
		cout << "Correct!" << endl;
		return 1;
	}
	else
	{
		cout << "Wrong. The " << numbers[noteChoice+1] << " of " << scaleName << " is " << noteStr << endl;
		return 0;
	}
}

int AskBackwardsNthOfScale( int scaleType )
{
	int noteChoice = rand() % (NUM_NOTES_PER_SCALE - 1);
	int scaleChoice = rand() % NUM_MAJOR_SCALES;

	Note n = scales[scaleType][scaleChoice].GetNote(noteChoice + 2);

	string scaleTypeName;
	switch (scaleType)
	{
	case SCALE_MAJOR:
	{
		scaleTypeName = "Major";
		break;
	}
	case SCALE_MINOR:
	{
		scaleTypeName = "minor";
		break;
	}
	}

	string scaleNameLetter = scales[scaleType][scaleChoice].GetNote(1).ToString();
	string scaleName = scales[scaleType][scaleChoice].NameToString();

	string input;
	cout << n.ToString() << " is the " << numbers[noteChoice+1] << " of which " << scaleTypeName << " scale?  ";
	cin >> input;

	if (input == scaleNameLetter)
	{
		cout << "Correct!" << endl;
		return 1;
	}
	else
	{
		cout << "Wrong. " << n.ToString() << " is the " << numbers[noteChoice+1] << " of " << scaleName << endl;
		return 0;
	}
}

int AskAccidentals( int scaleType )
{
	int scaleIndex = rand() % NUM_MAJOR_SCALES;
	Scale &s = scales[scaleType][scaleIndex];

	int numSharps = s.GetNumberOfSharps();
	int numFlats = s.GetNumberOfFlats();

	cout << "Which " << scaleTypeNames[scaleType] << " scale has ";

	//key has ";
	if (numSharps > 0)
	{
		if (numSharps == 1)
		{
			cout << numSharps << " sharp?  ";
		}
		else
		{
			cout << numSharps << " sharps?  ";
		}
		

		string input;
		cin >> input;

		string firstNote = s.GetNote(1).ToString();

		if (input == firstNote)
		{
			cout << "Correct!" << endl;
			return 1;
		}
		else
		{
			cout << "Wrong. The " << scaleTypeNames[scaleType] << " scale with " << numSharps << " sharps is " << s.NameToString() << endl;
			return 0;
		}
	}
	else if (numFlats > 0)
	{
		if (numFlats == 1)
		{
			cout << numFlats << " flat?  ";
		}
		else
		{
			cout << numFlats << " flats?  ";
		}

		string input;
		cin >> input;

		string firstNote = s.GetNote(1).ToString();

		if (input == firstNote)
		{
			cout << "Correct!" << endl;
			return 1;
		}
		else
		{
			cout << "Wrong. The " << scaleTypeNames[scaleType] << " scale with " << numFlats << " flats is " << s.NameToString() << endl;
			return 0;
		}
	}
	else
	{
		cout << "no sharps or flats?  ";

		string input;
		cin >> input;

		string firstNote = s.GetNote(1).ToString();

		if (input == firstNote)
		{
			cout << "Correct!" << endl;
			return 1;
		}
		else
		{
			cout << "Wrong. The " << scaleTypeNames[scaleType] << " scale with no sharps or flats is " << s.NameToString() << endl;
			return 0;
		}
	}
}

int AskChordQualities(int scaleType)
{
	int chordChoice = rand() % NUM_NOTES_PER_SCALE;

	cout << "Which chord quality does the " << numbers[chordChoice] << " chord of a " << scaleTypeNames[scaleType] << " scale have?  ";

	string input;
	cin >> input;

	string quality = chordQualities[scaleType][chordChoice];

	if (input == quality)
	{
		cout << "Correct!" << endl;
		return 1;
	}
	else
	{
		cout << "Wrong. The " << numbers[chordChoice] << " chord of a " << scaleTypeNames[scaleType] << " scale is " << quality << endl;
		return 0;
	}
}

int AskToListChord(int scaleType)
{
	int scaleChoice = rand() % NUM_MAJOR_SCALES;

	Scale &s = scales[scaleType][scaleChoice];

	cout << "List the notes in the " << s.NameToString() << " chord:  ";

	string input1;
	cin >> input1;

	string input2;
	cin >> input2;

	string input3;
	cin >> input3;

	string n1 = s.GetNote(1).ToString();
	string n2 = s.GetNote(3).ToString();
	string n3 = s.GetNote(5).ToString();

	if (input1 == n1 && input2 == n2 && input3 == n3)
	{
		cout << "Correct!" << endl;
		return 1;
	}
	else
	{
		cout << "Wrong. The notes of the " << s.NameToString() << " chord are: " << n1 << " " << n2 << " " << n3 << endl;
		return 0;
	}

}

int main()
{
	FillScales();

	while (true)
	{
		cout << "-----------ROUND START-----------" << endl << endl;
		srand(time(0));

		auto startTime = chrono::high_resolution_clock::now();

		int numQuestions = 10;
		int totalScore = 0;
		for (int i = 0; i < numQuestions; ++i)
		{
			int questionSelection = rand() % Q_Count;
			int scaleTypeSelection = rand() % SCALE_Count;

			totalScore += AskToListChord(scaleTypeSelection);
			/*switch (questionSelection)
			{
			case Q_NTH_OF_SCALE:
			{
				totalScore += AskNthOfScale(scaleTypeSelection);
				break;
			}
			case Q_BACKWARDS_NTH_OF_SCALE:
			{
				totalScore += AskBackwardsNthOfScale(scaleTypeSelection);
				break;
			}
			case Q_ACCIDENTALS:
			{
				totalScore += AskAccidentals(scaleTypeSelection);
				break;
			}
			case Q_CHORD_QUALITIES:
			{
				totalScore += AskChordQualities(scaleTypeSelection);
				break;
			}
			case Q_LIST_CHORD:
			{
				totalScore += AskToListChord(scaleTypeSelection);
				break;
			}
			}*/

			cout << endl;
		}


		auto finishTime = chrono::high_resolution_clock::now();

		chrono::duration<double> totalTime = finishTime - startTime;

		cout << "---------------------------------" << endl;
		cout << "You scored: " << totalScore << "/" << numQuestions << endl;
		cout << "You took " << totalTime.count() << " seconds." << endl;
		cout << "\n\n\n\n" << endl;
	}
}