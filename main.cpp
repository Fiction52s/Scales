#include <string>
#include <iostream>
#include <time.h>
#include <random>
#include <map>
#include <vector>
#include <chrono>
#include <assert.h>

using namespace std;

const static int NUM_SCALES = 12;
const static int NUM_NOTES_PER_SCALE = 7;

string numbers[] = { "2nd", "3rd", "4th", "5th", "6th", "7th" };

string scales[NUM_SCALES][NUM_NOTES_PER_SCALE] =
{
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
};

string sharps[NUM_NOTES_PER_SCALE] = {"G", "D", "A", "E", "B", "F#", "C#"};
string flats[NUM_NOTES_PER_SCALE] = { "F", "Bb", "Eb", "Ab", "Db", "Gb", "Cb" };

int AskNthOfMajorScale()
{
	int noteChoice = rand() % (NUM_NOTES_PER_SCALE-1);
	int scaleChoice = rand() % NUM_SCALES;

	string input;
	cout << "What is the: " << numbers[noteChoice] << " of " << scales[scaleChoice][0] << " major?  ";// << endl;
	cin >> input;

	if (input == scales[scaleChoice][noteChoice + 1])
	{
		cout << "Correct!" << endl;
		return 1;
	}
	else
	{
		cout << "Wrong. The " << numbers[noteChoice] << " of " << scales[scaleChoice][0] << " major is " << scales[scaleChoice][noteChoice+1] << endl;
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

const static int TOTAL_HALF_STEPS = 12;

enum Letter
{
	LETTER_C,
	LETTER_D,
	LETTER_E,
	LETTER_F,
	LETTER_G,
	LETTER_A,
	LETTER_B,
	LETTERS_Count
};

string letterStr[] = { "C", "D", "E", "F", "G", "A", "B" };

enum ScaleType
{
	SCALE_MAJOR,
	SCALE_MINOR,
};

enum Accidental
{
	ACC_NEUTRAL,
	ACC_SHARP,
	ACC_FLAT,
	ACC_DOUBLESHARP,
	ACC_DOUBLEFLAT,
};

int scaleIntervals[][7]
{
	{ 0, 2, 4, 5, 7, 9, 11 },
	{ 0, 2, 3, 5, 7, 8, 10 }
};


int defaultLetterOffsets[] = { 0, 2, 4, 5, 7, 9, 11 };

struct Note
{
	Note()
	{
		letter = LETTER_C;
		accidental = ACC_NEUTRAL;
	}

	int letter;
	int accidental;
	string ToString()
	{
		return letterStr[letter] + GetAccidentalString();
	}

	string GetAccidentalString()
	{
		switch (accidental)
		{
		case ACC_NEUTRAL:
			return "";
		case ACC_SHARP:
			return "#";
		case ACC_FLAT:
			return "b";
		case ACC_DOUBLESHARP:
			return "##";
		case ACC_DOUBLEFLAT:
			return "bb";
		default:
			return "_error";
		}
	}
};



//noteIndex starts at 1
Note GetNote(int scaleType, int startLetter, int accidental, int noteIndex)
{
	Note note;

	note.letter = (startLetter + (noteIndex-1)) % LETTERS_Count;

	int accidentalOffset = 0;
	if (accidental == ACC_SHARP)
	{
		accidentalOffset = 1;
	}
	else if (accidental == ACC_FLAT)
	{
		accidentalOffset = -1;
	}

	int currOffset = defaultLetterOffsets[startLetter] + accidentalOffset;
	if (noteIndex > 1)
	{
		currOffset += scaleIntervals[scaleType][noteIndex - 1];
	}

	while (currOffset < 0)
	{
		currOffset += TOTAL_HALF_STEPS;
	}

	currOffset = currOffset % TOTAL_HALF_STEPS;

	int currDefaultLetterOffset = defaultLetterOffsets[note.letter];

	int oneLessOffset = currDefaultLetterOffset - 1;
	if (oneLessOffset < 0 )
	{
		oneLessOffset += TOTAL_HALF_STEPS;
	}

	int twoLessOffset = currDefaultLetterOffset - 2;
	if (twoLessOffset < 0)
	{
		twoLessOffset += TOTAL_HALF_STEPS;
	}

	if (currOffset == (currDefaultLetterOffset + 1) % TOTAL_HALF_STEPS )
	{
		note.accidental = ACC_SHARP;
	}
	else if (currOffset == (currDefaultLetterOffset + 2) % TOTAL_HALF_STEPS)
	{
		note.accidental = ACC_DOUBLESHARP;
	}
	else if (currOffset == oneLessOffset)
	{
		note.accidental = ACC_FLAT;
	}
	else if (currOffset == twoLessOffset)
	{
		note.accidental = ACC_DOUBLEFLAT;
	}
	else if (currOffset == currDefaultLetterOffset)
	{
		note.accidental = ACC_NEUTRAL;
	}
	else
	{
		assert(0);
		note.accidental = ACC_NEUTRAL;
	}

	return note;
}

void PrintScale(int scaleType, int startLetter, int accidental)
{
	for (int i = 1; i < 8; ++i)
	{
		cout << GetNote(scaleType, startLetter, accidental, i).ToString() << " ";
	}
	cout << endl;
}

int main()
{
	while (true)
	{
		int scaleType = SCALE_MAJOR;
		int letter = LETTER_B;
		int acc = ACC_NEUTRAL;

		for (int li = 0; li < LETTERS_Count; ++li)
		{
			PrintScale(scaleType, li, acc);
		}
		

		int x;
		cin >> x;




		//cout << "-----------ROUND START-----------" << endl;
		//srand(time(0));

		//auto startTime = chrono::high_resolution_clock::now();

		//int numQuestions = 10;
		//int totalScore = 0;
		//for (int i = 0; i < numQuestions; ++i)
		//{
		//	totalScore += AskNthOfMajorScale();
		//	//totalScore += AskNumberOfAccidentals();
		//}


		//auto finishTime = chrono::high_resolution_clock::now();

		//chrono::duration<double> totalTime = finishTime - startTime;

		//cout << "---------------------------------" << endl;
		//cout << "You scored: " << totalScore << "/" << numQuestions << endl;
		//cout << "You took " << totalTime.count() << " seconds." << endl;
		//cout << "\n\n\n\n" << endl;
	}
}