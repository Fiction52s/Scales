#include "Note.h"
#include <string>
#include <iostream>
#include <assert.h>


using namespace std;



Note::Note()
{
	letter = LETTER_C;
	accidental = ACC_NEUTRAL;
}

Note::Note(int p_letter, int p_acc)
{
	letter = p_letter;
	accidental = p_acc;
}

//noteIndex starts at 1
Note::Note(int p_scaleType, int p_startLetter, int p_accidental, int p_noteIndex)
{
	letter = (p_startLetter + (p_noteIndex - 1)) % LETTERS_Count;

	int accidentalOffset = 0;
	if (p_accidental == ACC_SHARP)
	{
		accidentalOffset = 1;
	}
	else if (p_accidental == ACC_FLAT)
	{
		accidentalOffset = -1;
	}

	int currOffset = defaultLetterOffsets[p_startLetter] + accidentalOffset;
	if (p_noteIndex > 1)
	{
		currOffset += scaleIntervals[p_scaleType][p_noteIndex - 1];
	}

	while (currOffset < 0)
	{
		currOffset += TOTAL_HALF_STEPS;
	}

	currOffset = currOffset % TOTAL_HALF_STEPS;

	accidental = GetAccidental(letter, currOffset);
}

int Note::GetAccidental(int p_letter, int p_offset)
{
	int acc = 0;

	int currDefaultLetterOffset = defaultLetterOffsets[p_letter];

	int oneLessOffset = currDefaultLetterOffset - 1;
	if (oneLessOffset < 0)
	{
		oneLessOffset += TOTAL_HALF_STEPS;
	}

	int twoLessOffset = currDefaultLetterOffset - 2;
	if (twoLessOffset < 0)
	{
		twoLessOffset += TOTAL_HALF_STEPS;
	}

	if (p_offset == (currDefaultLetterOffset + 1) % TOTAL_HALF_STEPS)
	{
		acc = ACC_SHARP;
	}
	else if (p_offset == (currDefaultLetterOffset + 2) % TOTAL_HALF_STEPS)
	{
		acc = ACC_DOUBLESHARP;
	}
	else if (p_offset == oneLessOffset)
	{
		acc = ACC_FLAT;
	}
	else if (p_offset == twoLessOffset)
	{
		acc = ACC_DOUBLEFLAT;
	}
	else if (p_offset == currDefaultLetterOffset)
	{
		acc = ACC_NEUTRAL;
	}
	else
	{
		assert(0);
		acc = ACC_NEUTRAL;
	}

	return acc;
}

int Note::GetMyOffset()
{
	return defaultLetterOffsets[letter] + GetAccidentalOffset(accidental);
}

string Note::ToString()
{
	return letterStr[letter] + GetAccidentalString(accidental);
}

string Note::GetAccidentalString(int acc)
{
	switch (acc)
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

int Note::GetAccidentalOffset(int acc)
{
	switch (acc)
	{
	case ACC_NEUTRAL:
		return 0;
	case ACC_SHARP:
		return 1;
	case ACC_FLAT:
		return -1;
	case ACC_DOUBLESHARP:
		return 2;
	case ACC_DOUBLEFLAT:
		return -2;
	default:
		return 0;
	}
}

Scale::Scale()
	:scaleType( SCALE_MAJOR ), letter( LETTER_C ), accidental( ACC_NEUTRAL )
{

}

Scale::Scale(int p_scaleType, int p_letter, int p_accidental)
	:scaleType(p_scaleType),
	letter(p_letter),
	accidental(p_accidental)
{

}

//noteIndex starts at 1
Note Scale::GetNote(int noteIndex)
{
	return Note(scaleType, letter, accidental, noteIndex);
}

string Scale::NotesToString()
{
	string str;
	for (int i = 1; i <= NUM_NOTES_PER_SCALE; ++i)
	{
		str += GetNote(i).ToString() + " ";
	}
	return str;
}

string Scale::NameToString()
{
	string str = letterStr[letter] + Note::GetAccidentalString(accidental);
	if (scaleType == SCALE_MAJOR)
	{
		str += " Major";
	}
	else if (scaleType == SCALE_MINOR)
	{
		str += " minor";
	}

	return str;
}

Scale Scale::GetScaleThatNoteIsXthOf(int p_scaleType, int p_noteIndex, Note &n )
{
	int myOffset = n.GetMyOffset();

	int newOffset = myOffset - scaleIntervals[p_scaleType][p_noteIndex - 1];

	while (newOffset < 0)
	{
		newOffset += TOTAL_HALF_STEPS;
	}

	int scaleLetter = n.letter - (p_noteIndex - 1);

	while (scaleLetter < 0)
	{
		scaleLetter += NUM_NOTES_PER_SCALE;
	}

	int scaleAcc = Note::GetAccidental(scaleLetter, newOffset);

	return Scale(p_scaleType, scaleLetter, scaleAcc);
}

int Scale::GetNumberOfFlats()
{
	int numFlats = 0;
	for (int i = 1; i <= NUM_NOTES_PER_SCALE; ++i)
	{
		if (GetNote(i).accidental == ACC_FLAT)
			numFlats++;
	}
	return numFlats;
}

int Scale::GetNumberOfSharps()
{
	int numSharps = 0;
	for (int i = 1; i <= NUM_NOTES_PER_SCALE; ++i)
	{
		if (GetNote(i).accidental == ACC_SHARP)
			numSharps++;
	}
	return numSharps;
}