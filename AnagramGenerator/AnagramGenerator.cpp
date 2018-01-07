// AnagramGenerator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define _CRTDBG_MAP_ALLOC  
#define DEVELOP

#include <stdlib.h>  
#include <crtdbg.h> 

#include <memory>
#include <iostream>
#include <fstream>
#include <string.h>

#include "DictionaryLookUp.h"

#include "HayStackClass.h"

#define MAX_STR 100
#define LETTERSINALPHA 26
#define MAX_DIC 100
#define FILEERROR 10

char* strPhrase = NULL;
char *strUnsortedInput = NULL;
char* strSortedString = NULL;
char *strResults = NULL;
char *strPermutationWord = NULL;

int intMatchCount = 0;
int intMatchMade = 0;

std::ofstream strPermutationsOutfile;

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
	// For each letter in string count the occurrences
	int intPermIndex = 0;
	int intStringLevel = 0;

	intCharCount = 0;

	for (int i = 0; i < intStrLen; i++)
	{
		if ((tolower(chrS[i]) >= 'a') && (tolower( chrS[i]) <= 'z'))
		{
			if ((intPermIndex == 0) && (objPhraseChar[0].chrCharacter) == 0)
			{
				objPhraseChar[0].chrCharacter = tolower(chrS[i]);
				objPhraseChar[0].intCount = 1;
				intStringLevel = 1;
				intCharCount = 1;
			}
			else
			{
				if (tolower(chrS[i]) > objPhraseChar[intPermIndex].chrCharacter)
				{
					intPermIndex++;
					objPhraseChar[intPermIndex].chrCharacter = tolower(chrS[i]);
					objPhraseChar[intPermIndex].intCount = 1;
					intStringLevel++;
					intCharCount++;
				}
				else if (tolower(chrS[i]) == objPhraseChar[intPermIndex].chrCharacter)
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
		std::cout << "\t" << p[intPermIndex].chrCharacter << "\t[" << p[intPermIndex].intCount << "]" << std::endl;
		intPermIndex++;
	}
}

void SortString(char *sortedstr, const char *unsortedstr, int strlen)
{
	// Bubble Sort string
	strcpy(sortedstr, unsortedstr);
	char tempchar = 0;

	for (int i = 1; i < strlen; i++)
	{
		for (int j = 0; j < strlen - 1; j++)
		{
			if ((tolower(sortedstr[j]) >= 'a') && (tolower(sortedstr[j]) <= 'z'))
			{
				if (tolower(sortedstr[j]) > tolower(sortedstr[j + 1]))
				{
					tempchar = tolower(sortedstr[j]);
					sortedstr[j] = tolower(sortedstr[j + 1]);
					sortedstr[j + 1] = tempchar;
				}
			}
		}
	}
}

void Permutation(char s[], int intStringLevel, int intCount[], char res[], int lev, const int intStringIndexze)
{
	// Starting from the letter 'a' determine from intCount if present in string 
	// Branch off decrementing letter intCount (until it reaches 0).
	// If not at end of branch (level = length of string) goto next character
	// Result is an array of level when branching occurs
	int i = 0;
	if (lev == intStringIndexze)
	{
		//std::cout << "Permutation:\t" << res << std::endl;
		strPermutationsOutfile << res << std::endl;
		return;
	}

	// Go through each letter found in string (looking through intCount
	while (i < intStringLevel)
	{
		// Handle letters that have been duplicated with their intCount value
		if (intCount[i] != 0)
		{
			res[lev] = s[i];
			//std::cout << "RES: " << res[lev] << " LEV:" << lev << " i: " << i << std::endl;
			intCount[i]--;
			Permutation(s, intStringLevel, intCount, res, (lev +1), intStringIndexze);
			intCount[i]++;
		}
		i++;
	}
}

void CheckPermutationsAgainstDictionary()
{
#ifdef DEVELOP
	HayStackClass *hscDictionary = new HayStackClass("dictionary.txt");

	strPermutationWord = new char[intPhraseLength + 1];
	memset(strPermutationWord, 0, intPhraseLength + 1);

	// Open (for input) sorted permutations file
	std::ifstream permutationsInfile;
	permutationsInfile.open("permutations.txt");
	if (!strPermutationsOutfile)
	{
		std::cout << "Cannot load file" << std::endl;
		throw FILEERROR;
	}

	permutationsInfile >> strPermutationWord;

	while (!permutationsInfile.eof())
	{
		//std::cout << strPermutationWord << std::endl;
		hscDictionary->LookForNeedleInHayStack(strPermutationWord);
		permutationsInfile >> strPermutationWord;
	}

	hscDictionary->blnCloseHayStackFile();

#else
	// Open "dictionary" file

	// strDicWord and strPermutationWord used for pattern matching
	char strDicWord[MAX_DIC] = { 0 };

	strPermutationWord = new char[intPhraseLength + 1];
	memset(strPermutationWord, 0, intPhraseLength + 1);

	//indexes to permutation list and dictionary 
	int intPermIndex = 0;
	int intDicIndex = 0;

	// Open (for input) sorted permutations file
	std::ifstream permutationsInfile;
	permutationsInfile.open("permutations.txt");

	//input file "dictionary" (sample used for testing software)
	std::ifstream dictionaryInfile;
	dictionaryInfile.open("dictionary.txt");

	//upon failure to open file exit main with failure
	if (!dictionaryInfile || !permutationsInfile)
	{
		std::cout << "dictionary/permutations file failed to open!" << std::endl;
		getchar();

		DereferenceAllocatedMemory();
		throw FILEERROR;
	}

	/*char buf[MAXWORD];

	dictionaryInfile.seekg(263773);
	dictionaryInfile >> buf;
	std::cout << "At P in Dic?: " << buf << std::endl;*/

	int WordFoundArray[26] = { 0 };
	WordList strWordFoundList[LETTERSINALPHA];
	WordList strWordNotFoundList[LETTERSINALPHA];

	std::streampos stoPosition[LETTERSINALPHA] = { 0 };
	unsigned long int intPosition[LETTERSINALPHA] = { 0 };

	permutationsInfile >> strPermutationWord;

	while (!permutationsInfile.eof())
	{
		LookForWord(dictionaryInfile, stoPosition, strWordFoundList, strWordNotFoundList, strPermutationWord);
		permutationsInfile >> strPermutationWord;
	}

	//close files
	dictionaryInfile.close();
#endif
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

	//Count Phrase alphabetical characters
	intCountintStringLevel = CountChar(objPhraseChars, strSortedString, strlen(strSortedString), charCount);
}

void GeneratePermutations()
{
	// Determine denominator for no. of permutations calculations:
	//
	// (length of Phrase!)/((counts of character n)! x (counts of character n+1)! x (counts of character n+2)! . .  .) 
	//
	int permutationDenominator = 1;
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

	// Working (temp) arrays for each letter in phrase assign and the number of occurrences
	for (int i = 0; i < charCount; i++)
	{
		tempStr[i] = objPhraseChars[i].chrCharacter;
		tempCount[i] = objPhraseChars[i].intCount;
	}

	// Create output file where determined sorted permutations are stored for future use
	strPermutationsOutfile.open("permutations.txt");
	if (!strPermutationsOutfile)
	{
		std::cout << "Cannot load file" << std::endl;
		throw FILEERROR;
	}

	//Recursive function that determines permutations (lexicographically sorted)

	// intCountintStringLevel - maximum level of tree (from root to end of branch, length of string)
	// level - used when recursive calling nature of algorithm heads towards branch (until level == intCountintStringLevel)
	// Results are written directly into the Permutations file
	Permutation(tempStr, charCount, tempCount, strResults, level, intCountintStringLevel);

	// Close File
	strPermutationsOutfile.close();
}

int main(int argc, char* argv[])
{
	std::cout << "Anagram Generator" << std::endl;

	try
	{

		if (argc < 2)
		{
			std::cout << "// No Phrase seen from the command line" << std::endl;
			getchar();

			DereferenceAllocatedMemory();
			return EXIT_FAILURE;
		}

		intPhraseLength = strlen((const char*)argv[1]);

		//define Phrase variable from the heap
		strPhrase = new char[intPhraseLength + 1];
		memset(strPhrase, 0, intPhraseLength + 1);

		strcpy(strPhrase, (const char*)argv[1]);
		std::cout << "Test Phase:\t" << strPhrase << std::endl;
	
		SortPhraseCharacters();
		GeneratePermutations();
		
		CheckPermutationsAgainstDictionary();

		DereferenceAllocatedMemory();
	}
	catch (const::std::bad_alloc& e)
	{
		std::cout << "Allocation failed: " << e.what() << std::endl;
		DereferenceAllocatedMemory();
		std::cout << "Press any key to continue . . ." << std::endl;;
		getchar();
		return EXIT_FAILURE;
	}
	catch (int e)
	{
		switch (e)
		{
			case FILE_ERROR:
			{
				DereferenceAllocatedMemory();
				std::cout << "Unexpected File Error" << std::endl;
				std::cout << "Press any key to continue . . ." << std::endl;;
				getchar();
				return EXIT_FAILURE;
				break;
			}
			default:
			{
				DereferenceAllocatedMemory();
				std::cout << "Unknown Application Error" << std::endl;
				std::cout << "Press any key to continue . . ." << std::endl;;
				getchar();
				return EXIT_FAILURE;
				break;
			}
		}
	}
	catch (...)
	{
		DereferenceAllocatedMemory();
		std::cout << "Unexpected Event" << std::endl;
		std::cout << "Press any key to continue . . ." << std::endl;;
		getchar();
		return EXIT_FAILURE;
	}

	std::cout << "Press any key to continue . . ." << std::endl;;
	getchar();
	
	//_CrtDumpMemoryLeaks();
    return EXIT_SUCCESS;
}

