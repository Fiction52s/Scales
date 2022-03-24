#ifndef __NOTE_H__
#define __NOTE_H__

#include <string>

const static int NUM_MAJOR_SCALES = 12;
const static int NUM_NOTES_PER_SCALE = 7;
const static int TOTAL_HALF_STEPS = 12;

static std::string numbers[] = { "2nd", "3rd", "4th", "5th", "6th", "7th" };
static std::string letterStr[] = { "C", "D", "E", "F", "G", "A", "B" };

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

static int scaleIntervals[][7]
{
	{ 0, 2, 4, 5, 7, 9, 11 },
	{ 0, 2, 3, 5, 7, 8, 10 }
};


static int defaultLetterOffsets[] = { 0, 2, 4, 5, 7, 9, 11 };

struct Note
{
	int letter;
	int accidental;

	Note();
	Note(int p_letter, int p_acc);
	Note(int p_scaleType, int p_startLetter, int p_accidental, int p_noteIndex);
	static int GetAccidental(int p_letter, int p_offset);
	int GetMyOffset();
	std::string ToString();
	static std::string GetAccidentalString(int acc);
	static int GetAccidentalOffset(int acc);
};

struct Scale
{
	int scaleType;
	int letter;
	int accidental;

	Scale();
	Scale(int p_scaleType, int p_letter, int p_accidental);
	Note GetNote(int noteIndex);
	std::string NotesToString();
	std::string NameToString();
	static Scale GetScaleThatNoteIsXthOf( int p_scaleType, int p_noteIndex, Note &n);
	int GetNumberOfFlats();
	int GetNumberOfSharps();
};

#endif
