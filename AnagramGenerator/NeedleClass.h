#pragma once
#include <iostream>
#include <fstream>

// Constants
#define MAX_NEEDLE_WORD 30
#define MAX_LETTERS 26

// Event Errors
#define NEEDLE_PERM_FILE_ERROR 20
#define NEEDLE_TOO_LONG_ERROR 21

class NeedleClass
{
public:
	int intNeedleWordLength;
	char strNeedleWord[MAX_NEEDLE_WORD + 1];
	char strSortedNeedleWord[MAX_NEEDLE_WORD + 1];
	char strPermResult[MAX_NEEDLE_WORD + 1];
	char chrLetterCountArray[MAX_LETTERS];
	int intLetterCountArray[MAX_LETTERS];
	int intStringLevel;
	int intCharCount;
	unsigned long int uliNumberOfPermutations;
	std::ofstream ofsPermutations;


public:
	NeedleClass();
	~NeedleClass();

	NeedleClass(const char* strWord);
	int intGetNeedleWordLength();
	void SortCharacters();
	void CountLetters();
	void DetermineNumberOfPermutations();
	void CreatePermutationsOutfile();
	void ClosePermutationsFile();
	//void CalculatePermutations(char strPermResult[], int intLevel);
	void 	CalculatePermutations(char s[], int intStringLevel, int intCount[], char res[], int lev, const int intStringIndexze);
};

