// AnagramGenerator.cpp : Defines the entry point for the console application.
//

/*
Anagram Generator
Write an application that generates all permutations for a given word or phrase and compares these permutations against a dictionary file. Assume that you have access to the dictionary file that contains all permissible words, one word per line. The application should be implemented to read the input word or phrase from the applications command line parameters and to write all valid anagrams, based on the dictionary file’s contents, to standard output.
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

char* phrase = NULL;
char *unsortedInput = NULL;
char* sortedString = NULL;
char *results = NULL;
char *pword = NULL;

ofstream permutationsOutfile;

struct PhraseChar {
	char character = 0;
	int count = 0;
};

int phraseLength = 0;
PhraseChar phraseChars[LETTERSINALPHA];
int charCount = 0;
int countsl = 0;

int CountChar(PhraseChar *p, const char *s, int strlen, int& cc);

void 	DereferenceAllocatedMemory()
{
	//dereferences a pointers to allocated memory
	if (results != NULL)
	{
		delete[] results;
		results = NULL;
	}
	
	if (sortedString != NULL)
	{
		delete[] sortedString;
		sortedString = NULL;
	}

	if (unsortedInput != NULL)
	{
		delete[] unsortedInput;
		unsortedInput = NULL;
	}

	if (phrase != NULL)
	{
		delete[] phrase;
		phrase = NULL;
	}

	if (pword != NULL)
	{
		delete[] pword;
		pword = NULL;
	}

};

int Factorial(int n)
{
	int value = 1;

	// The value of 0! is 1
	if (n > 0)
	{
		for (int i = 1; i <= n; i++)
			value = value * i;
	}

	return value;
}


int CountChar(PhraseChar *p, const char *s, int strlen, int& cc)
{
	int pi = 0;
	int sl = 0;

	cc = 0;

	for (int si = 0; si < strlen; si++)
	{
		if ((s[si] >= 'a') && (s[si] <= 'z'))
		{
			if ((pi == 0) && (p[0].character) == 0)
			{
				p[0].character = s[si];
				p[0].count = 1;
				sl = 1;
				cc = 1;
			}
			else
			{
				if (s[si] > p[pi].character)
				{
					pi++;
					p[pi].character = s[si];
					p[pi].count = 1;
					sl++;
					cc++;
				}
				else if (s[si] == p[pi].character)
				{
					p[pi].count = p[pi].count + 1;
					sl++;
				}
			}
		}
	}
	return sl;
}

void ShowPhraseChars(PhraseChar *p)
{
	int pi = 0;
	while (p[pi].count > 0)
	{
		cout << "\t" << p[pi].character << "\t[" << p[pi].count << "]\n";
		pi++;
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

//Permutation(sortedString, countsl, tempCount, results, level, phraseLength);
void Permutation(char s[], int sl, int count[], char res[], int lev, const int size)
{
	int i = 0;
	if (lev == size)
	{
		//cout << "Permutation:\t" << res << endl;
		permutationsOutfile << res << endl;

		return;
	}

	while (i < sl)
	{
		if (count[i] != 0)
		{
			res[lev] = s[i];
			//cout << "RES: " << res[lev] << " LEV:" << lev << " i: " << i << endl;
			count[i]--;
			Permutation(s, sl, count, res, (lev +1), size);
			count[i]++;
		}
		i++;
	}
}


void CheckPermutationsAgainstDictionary()
{
	// Open "dictionary" file

	// dword and pword used for pattern matching
	char dword[MAX_DIC] = { 0 };

	pword = new char[phraseLength + 1];
	memset(pword, 0, phraseLength + 1);

	//indexes to permutation list and dictionary 
	int pi = 0;
	int di = 0;

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
	int dci = 0;

	//look through "dictionary" matching each permutation with read word from file
	while (!dictionaryInfile.eof())
	{
		memset(dword, 0, MAX_DIC);

		dictionaryInfile >> dword;
		//cout << "Read Dic:" << dword << endl;
		bPatternMatch = false;
		while (!permutationsInfile.eof() && (strlen(dword) > 0) && !bPatternMatch)
		{
			//bPatternMatch = false;
			memset(pword, 0, phraseLength + 1);
			permutationsInfile >> pword;
			
			dci = 0;
			int pcl = strlen(pword);
			int dcl = strlen(dword);

			int pci = 0;
			int dci = 0;

			//cout << "Looking for pattern: " << dword << " in string " << pword << endl;

			for (pci = 0; pci < pcl; pci++)
			{
				for (dci = 0; (dci < dcl) && ((pci + dci) < pcl); dci++)
				{
					if (pword[dci + pci] != dword[dci])
					{
						bPatternMatch = false;
						break;
					}
				}
				if (dci == dcl)
				{
					bPatternMatch = true;
					//if (strcmp(dword, pword) == 0)
					if (bPatternMatch)
					{
						cout << "Dictionary Word[" << di << "] " << dword << " Matches Phrase Word [" << pi << "]\t" << pword << endl;
						break;
					}
				}
			}


			pi++;
		}

		permutationsInfile.clear();
		permutationsInfile.seekg(0, ios::beg);

		pi = 0;
		di++;
	}

	//close "Dictionary" file
	dictionaryInfile.close();
	permutationsInfile.close();

}

void SortPhraseCharacters()
{
		//Sort Phrase characters
		unsortedInput = new char[phraseLength + 1];
		memset(unsortedInput, 0, phraseLength + 1);

		sortedString = new char[phraseLength + 1];
		memset(sortedString, 0, phraseLength + 1);
		strcpy(unsortedInput, phrase);
		SortString(sortedString, unsortedInput, strlen(unsortedInput));


	cout << "Unsorted String:\t" << unsortedInput << endl;
	cout << "Sorted String:     \t" << sortedString << endl;

	//Count Phrase alphabetical characters

	countsl = CountChar(phraseChars, sortedString, strlen(sortedString), charCount);
}

void GeneratePermutations()
{
	int permutationDenominator = 1;
	//Determine denominator for no. of permutations calculations
	for (int i = 0; i < charCount; i++)
	{
		permutationDenominator = permutationDenominator * Factorial(phraseChars[i].count);
	}

	//determine number of permutations
	const int numberOfPermutations = Factorial(phraseLength) / permutationDenominator;

	//determine permutations from sorted list of characters
	char tempStr[LETTERSINALPHA] = { 0 };
	int tempCount[LETTERSINALPHA] = { 0 };

		results = new char[phraseLength + 1];
		memset(results, 0, phraseLength + 1);

	int level = 0;

	for (int pi = 0; pi < charCount; pi++)
	{
		tempStr[pi] = phraseChars[pi].character;
		tempCount[pi] = phraseChars[pi].count;
	}

	//recursive function that determines permutations (lexicographical ordering)
	permutationsOutfile.open("permutations.txt");

	if (!permutationsOutfile)
	{
		cout << "Cannot load file" << endl;
		throw EXIT_FAILURE;
	}

	Permutation(tempStr, charCount, tempCount, results, level, countsl);

	permutationsOutfile.close();
}

int main(int argc, char* argv[])
{
	cout << "Anagram Generator" << endl;

try
{
	if (argc < 2)
	{
		cout << "// No phrase seen from the command line" << endl;
		getchar();

		DereferenceAllocatedMemory();
		throw EXIT_FAILURE;
	}

	for (int i = 0; i < argc; i++)
		cout << "Argument from command line[" << i << "]\t" << argv[i] << endl;

	phraseLength = strlen((const char*)argv[1]);

	//define phrase variable from the heap
	phrase = new char[phraseLength + 1];
	memset(phrase, 0, phraseLength + 1);

	strcpy(phrase, (const char*)argv[1]);
	cout << "\nGot Phase:\t" << phrase << endl;
	
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
	
//pause command window until a key is pressed
	getchar();
	
	//_CrtDumpMemoryLeaks();
    return EXIT_SUCCESS;
}

