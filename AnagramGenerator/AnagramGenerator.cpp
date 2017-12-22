// AnagramGenerator.cpp : Defines the entry point for the console application.
//

/*
Anagram Generator
Write an application that generates all permutations for a given word or strPhrase and compares these permutations against a dictionary file. Assume that you have access to the dictionary file that contains all permisintStringIndexble words, one word per line. The application should be implemented to read the input word or strPhrase from the applications command line parameters and to write all valid anagrams, based on the dictionary file’s contents, to standard output.
*/


#include "stdafx.h"

//#define _CRTDBG_MAP_ALLOC  
//#include <stdlib.h>  
//#include <crtdbg.h> 

#include <memory>
#include <iostream>
#include <fstream>
#include <string.h>

#define MAX_STR 100
#define LETTERSINALPHA 26
#define MAX_DIC 50

using namespace std;

char* strPhrase = NULL;
char *strUnsortedInput = NULL;
char* strSortedString = NULL;
char *strResults = NULL;
char *strPermutationWord = NULL;

int intMatchCount = 0;
int intMatchMade = 0;

ofstream strPermutationsOutfile;

struct PhraseChar {
	char chrCharacter = 0;
	int intCount = 0;
};

int intPhraseLength = 0;
PhraseChar objPhraseChars[LETTERSINALPHA];
int charCount = 0;
int intCountintStringLevel = 0;


void 	DereferenceAllocatedMemory()
{
	//dereferences a pointers to allocated memory
	if (strResults != NULL)
	{
		delete[] strResults;
		strResults = NULL;
	}
	
	if (strSortedString != NULL)
	{
		delete[] strSortedString;
		strSortedString = NULL;
	}

	if (strUnsortedInput != NULL)
	{
		delete[] strUnsortedInput;
		strUnsortedInput = NULL;
	}

	if (strPhrase != NULL)
	{
		delete[] strPhrase;
		strPhrase = NULL;
	}

	if (strPermutationWord != NULL)
	{
		delete[] strPermutationWord;
		strPermutationWord = NULL;
	}

};

int Factorial(int n)
{
	int intValue = 1;

	// The intValue of 0! is 1
	if (n > 0)
	{
		for (int i = 1; i <= n; i++)
			intValue = intValue * i;
	}

	return intValue;
}


int CountChar(PhraseChar *objPhraseChar, const char *chrS, int intStrLen, int& intCharCount)
{
	int intPermIndex = 0;
	int intStringLevel = 0;

	intCharCount = 0;

	for (int i = 0; i < intStrLen; i++)
	{
		if ((chrS[i] >= 'a') && (chrS[i] <= 'z'))
		{
			if ((intPermIndex == 0) && (objPhraseChar[0].chrCharacter) == 0)
			{
				objPhraseChar[0].chrCharacter = chrS[i];
				objPhraseChar[0].intCount = 1;
				intStringLevel = 1;
				intCharCount = 1;
			}
			else
			{
				if (chrS[i] > objPhraseChar[intPermIndex].chrCharacter)
				{
					intPermIndex++;
					objPhraseChar[intPermIndex].chrCharacter = chrS[i];
					objPhraseChar[intPermIndex].intCount = 1;
					intStringLevel++;
					intCharCount++;
				}
				else if (chrS[i] == objPhraseChar[intPermIndex].chrCharacter)
				{
					objPhraseChar[intPermIndex].intCount = objPhraseChar[intPermIndex].intCount + 1;
					intStringLevel++;
				}
			}
		}
	}
	return intStringLevel;
}

void ShowPhraseChars(PhraseChar *p)
{
	int intPermIndex = 0;
	while (p[intPermIndex].intCount > 0)
	{
		cout << "\t" << p[intPermIndex].chrCharacter << "\t[" << p[intPermIndex].intCount << "]\n";
		intPermIndex++;
	}
}

void SortString(char *sortedstr, const char *unsortedstr, int strlen)
{
	strcpy(sortedstr, unsortedstr);
	char tempchar = 0;

	for (int i = 1; i < strlen; i++)
	{
		for (int j = 0; j < strlen - 1; j++)
		{
			if ((sortedstr[j] >= 'a') && (sortedstr[j] <= 'z'))
			{
				if (sortedstr[j] > sortedstr[j + 1])
				{
					tempchar = sortedstr[j];
					sortedstr[j] = sortedstr[j + 1];
					sortedstr[j + 1] = tempchar;
				}
			}
		}
	}
}

void Permutation(char s[], int intStringLevel, int intCount[], char res[], int lev, const int intStringIndexze)
{
	int i = 0;
	if (lev == intStringIndexze)
	{
		//cout << "Permutation:\t" << res << endl;
		strPermutationsOutfile << res << endl;

		return;
	}

	while (i < intStringLevel)
	{
		if (intCount[i] != 0)
		{
			res[lev] = s[i];
			//cout << "RES: " << res[lev] << " LEV:" << lev << " i: " << i << endl;
			intCount[i]--;
			Permutation(s, intStringLevel, intCount, res, (lev +1), intStringIndexze);
			intCount[i]++;
		}
		i++;
	}
}

void CheckPermutationsAgainstDictionary()
{
	// Open "dictionary" file

	// strDicWord and strPermutationWord used for pattern matching
	char strDicWord[MAX_DIC] = { 0 };

	strPermutationWord = new char[intPhraseLength + 1];
	memset(strPermutationWord, 0, intPhraseLength + 1);

	//indexes to permutation list and dictionary 
	int intPermIndex = 0;
	int intDicIndex = 0;

	ifstream permutationsInfile;
	permutationsInfile.open("permutations.txt");

	//input file "dictionary" (sample used for testing software)
	ifstream dictionaryInfile;

	dictionaryInfile.open("dictionary.txt");

	//upon failure to open file exit main with failure
	if (!dictionaryInfile || !permutationsInfile)
	{
		cout << "dictionary/permutations file failed to open!" << endl;
		getchar();

		DereferenceAllocatedMemory();
		throw EXIT_FAILURE;
	}

	bool bPatternMatch = false;
	int intDecCharIndex = 0;

	//look through "dictionary" matching each permutation with read word from file
	while (!dictionaryInfile.eof())
	{
		memset(strDicWord, 0, MAX_DIC);

		dictionaryInfile >> strDicWord;
		int intDicWordLen = strlen(strDicWord);

		//cout << "Read Dic:" << strDicWord << endl;
		bPatternMatch = false;
		while (!permutationsInfile.eof() && (strlen(strDicWord) > 0) && !bPatternMatch)
		{
			memset(strPermutationWord, 0, intPhraseLength + 1);
			permutationsInfile >> strPermutationWord;
			int intPermWordLen = strlen(strPermutationWord);

			intDecCharIndex = 0;
			int intPermCharIndex = 0;
			int intDecCharIndex = 0;

			//cout << "Looking for pattern: " << strDicWord << " in string " << strPermutationWord << endl;

			//Search Optimization: Only match when word length from dictionary is <= pattern
			if (intDicWordLen <= intPermWordLen)
			{
				//Search Optimization: Only look up the Pattern when intStringIndexze >= Dictionary word 

				for (intPermCharIndex = 0; intPermCharIndex <= (intPermWordLen - intDicWordLen); intPermCharIndex++)
				{
					for (intDecCharIndex = 0; (intDecCharIndex < intDicWordLen) && ((intPermCharIndex + intDecCharIndex) < intPermWordLen); intDecCharIndex++)
					{
						intMatchCount++;
						if (strPermutationWord[intDecCharIndex + intPermCharIndex] != strDicWord[intDecCharIndex])
						{
							bPatternMatch = false;
							break;
						}
					}
					if (intDecCharIndex == intDicWordLen)
					{
						bPatternMatch = true;

						if (bPatternMatch)
						{
							cout << "Dictionary Word[" << intDicIndex << "] " << strDicWord << " Matches strPhrase Word [" << intPermIndex << "]\t" << strPermutationWord << endl;
							intMatchMade++;
							break;
						}
					}
				}
			}

			intPermIndex++;
		}

		permutationsInfile.clear();
		permutationsInfile.seekg(0, ios::beg);

		intPermIndex = 0;
		intDicIndex++;
	}

	//close "Dictionary" file
	dictionaryInfile.close();
	permutationsInfile.close();

}

void SortPhraseCharacters()
{
		//Sort Phrase characters
		strUnsortedInput = new char[intPhraseLength + 1];
		memset(strUnsortedInput, 0, intPhraseLength + 1);

		strSortedString = new char[intPhraseLength + 1];
		memset(strSortedString, 0, intPhraseLength + 1);
		strcpy(strUnsortedInput, strPhrase);
		SortString(strSortedString, strUnsortedInput, strlen(strUnsortedInput));


	cout << "Unsorted String:\t" << strUnsortedInput << endl;
	cout << "Sorted String:     \t" << strSortedString << endl;

	//Count Phrase alphabetical characters

	intCountintStringLevel = CountChar(objPhraseChars, strSortedString, strlen(strSortedString), charCount);
}

void GeneratePermutations()
{
	int permutationDenominator = 1;
	//Determine denominator for no. of permutations calculations
	for (int i = 0; i < charCount; i++)
	{
		permutationDenominator = permutationDenominator * Factorial(objPhraseChars[i].intCount);
	}

	//determine number of permutations
	const int numberOfPermutations = Factorial(intPhraseLength) / permutationDenominator;

	//determine permutations from sorted list of characters
	char tempStr[LETTERSINALPHA] = { 0 };
	int tempCount[LETTERSINALPHA] = { 0 };

		strResults = new char[intPhraseLength + 1];
		memset(strResults, 0, intPhraseLength + 1);

	int level = 0;

	for (int i = 0; i < charCount; i++)
	{
		tempStr[i] = objPhraseChars[i].chrCharacter;
		tempCount[i] = objPhraseChars[i].intCount;
	}

	//recursive function that determines permutations (lexicographical ordering)
	strPermutationsOutfile.open("permutations.txt");

	if (!strPermutationsOutfile)
	{
		cout << "Cannot load file" << endl;
		throw EXIT_FAILURE;
	}

	Permutation(tempStr, charCount, tempCount, strResults, level, intCountintStringLevel);

	strPermutationsOutfile.close();
}

int main(int argc, char* argv[])
{
	cout << "Anagram Generator" << endl;

try
{
	if (argc < 2)
	{
		cout << "// No Phrase seen from the command line" << endl;
		getchar();

		DereferenceAllocatedMemory();
		throw EXIT_FAILURE;
	}

	for (int i = 0; i < argc; i++)
		cout << "Argument from command line[" << i << "]\t" << argv[i] << endl;

	intPhraseLength = strlen((const char*)argv[1]);

	//define Phrase variable from the heap
	strPhrase = new char[intPhraseLength + 1];
	memset(strPhrase, 0, intPhraseLength + 1);

	strcpy(strPhrase, (const char*)argv[1]);
	cout << "\nGot Phase:\t" << strPhrase << endl;
	
	SortPhraseCharacters();

	GeneratePermutations();

	CheckPermutationsAgainstDictionary();

	DereferenceAllocatedMemory();
}
catch (const::bad_alloc& e)
{
	cout << "Allocation failed: " << e.what() << endl;
	DereferenceAllocatedMemory();
	getchar();
	return EXIT_FAILURE;
}
catch (...)
{
	DereferenceAllocatedMemory();
	cout << "Unexpected Event: ";
}
	
//cout << "Number of matches tested: \t" << intMatchCount << endl;
//cout << "Number of matches made: \t" << intMatchMade << endl;

	cout << "Press any key to continue . . .\n";
	getchar();
	
	//_CrtDumpMemoryLeaks();
    return EXIT_SUCCESS;
}

