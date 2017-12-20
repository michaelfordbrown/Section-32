// AnagramGenerator.cpp : Defines the entry point for the console application.
//

/*
Anagram Generator
Write an application that generates all permutations for a given word or phrase and compares these permutations against a dictionary file. Assume that you have access to the dictionary file that contains all permissible words, one word per line. The application should be implemented to read the input word or phrase from the applications command line parameters and to write all valid anagrams, based on the dictionary file’s contents, to standard output.
*/


#include "stdafx.h"

#include <memory>
#include <iostream>
#include <fstream>
#include <string.h>

#define MAX_STR 100
#define LETTERSINALPHA 26
#define MAX_DIC 50

using namespace std;

char* permutations = NULL;
char* phrase = NULL;
char *unsortedInput = NULL;
char* sortedString = NULL;
char *results = NULL;

void 	DereferenceAllocatedMemory()
{
	//dereferences a pointers to allocated memory
	if (results != NULL)
	{
		delete[] results;
		results = NULL;
	}

	if (permutations != NULL)
	{
		delete[]permutations;
		permutations = NULL;
	}

	if (sortedString != NULL)
	{
		delete[]sortedString;
		sortedString = NULL;
	}

	if (unsortedInput != NULL)
	{
		delete[]unsortedInput;
		unsortedInput = NULL;
	}

	if (phrase != NULL)
	{
		delete[]phrase;
		phrase = NULL;
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

struct PhraseChar {
	char character = 0;
	int count = 0;
};

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

void StoreResult(char result[], int sl, const int size)
{
	static int pi = 0;

	char * p = (char*)permutations;

	p = p + (pi * (size +1));

	strcpy(p, result);

	p = p + strlen(result) + 1;
	strcpy(p, "\0");


	pi++;

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

void Permutation(char s[], int sl, int count[], char res[], int lev, const int size)
{
	if (lev == sl)
	{
		cout << "Permutation:\t" << res << endl;
		StoreResult(res, sl, size);

		return;
	}

	int i = 0;
	while (i < sl)
	{
		if (count[i] != 0)
		{
			res[lev] = s[i];
			count[i]--;
			Permutation(s, sl, count, res, (lev +1), size);
			count[i]++;
		}
		i++;
	}
}

int main(int argc, char* argv[])
{
	cout << "Anagram Generator" << endl;

	// Get Phase from command line
	if (argc < 2)
	{
		cout << "// No phrase seen from the command line" << endl;
		getchar();

		DereferenceAllocatedMemory();
		return EXIT_FAILURE;
	}

	for (int i = 0; i < argc; i++)
		cout << "Argument from command line[" << i << "]\t" <<  argv[i] << endl;
	
	const int phraseLength = strlen(argv[1]);

	try
	{
		//define phrase variable from the heap
		phrase = new char[MAX_STR];
		memset(phrase, 0, MAX_STR);

		strcpy(phrase, argv[1]);
		cout << "\nGot Phase:\t" << phrase << endl;
	}
	catch (const::bad_alloc& e)
	{
		cout << "Allocation failed (phrase): " << e.what() << endl;
		getchar();
		return EXIT_FAILURE;
	}
	
	try
	{
		//Sort Phrase characters
		unsortedInput = new char[MAX_STR];
		memset(unsortedInput, 0, MAX_STR);
	}
	catch (const::bad_alloc& e)
	{
		cout << "Allocation failed (unsortedInput): " << e.what() << endl;
		getchar();

		DereferenceAllocatedMemory();
		return EXIT_FAILURE;
	}

	try
	{
		sortedString = new char[MAX_STR];
		memset(sortedString, 0, MAX_STR);
		strcpy(unsortedInput, phrase);
		SortString(sortedString, unsortedInput, strlen(unsortedInput));
	}
	catch (const::bad_alloc& e)
	{
		cout << "Allocation failed (sortedString): " << e.what() << endl;
		getchar();

		DereferenceAllocatedMemory();
		return EXIT_FAILURE;
	}

	cout << "Unsorted String:\t" << unsortedInput << endl;
	cout << "Sorted String:     \t" << sortedString << endl;

	//Count Phrase alphabetical characters
	int countsl = 0;
	int charCount = 0;
	PhraseChar phraseChars[LETTERSINALPHA];

	countsl = CountChar(phraseChars, sortedString, strlen(sortedString), charCount);

	int permutationDenominator = 1;
	//Determine denominator for no. of permutations calculations
	for (int i = 0; i < charCount; i++)
	{
		permutationDenominator = permutationDenominator * Factorial(phraseChars[i].count);
	}

	//determine number of permutations
	const int numberOfPermutations = Factorial(phraseLength) / permutationDenominator;

	try
	{
		//create heap based arrays to hold permutations
		permutations = new char[MAX_STR * (numberOfPermutations + 1)];
		memset(permutations, 0, MAX_STR * (numberOfPermutations + 1));

		//display characters from phrase
		ShowPhraseChars(phraseChars);
	}
	catch (const::bad_alloc& e)
	{
		cout << "Allocation failed (permutations): " << e.what() << endl;
		getchar();

		DereferenceAllocatedMemory();
		return EXIT_FAILURE;
	}
	//determine permutations from sorted list of characters
	char tempStr[LETTERSINALPHA] = { 0 };
	int tempCount[LETTERSINALPHA] = { 0 };

	try
	{
		results = new char[numberOfPermutations];
		memset(results, 0, numberOfPermutations);
	}
	catch (const::bad_alloc& e)
	{
		cout << "Allocation failed (results): " << e.what() << endl;
		getchar();

		DereferenceAllocatedMemory();
		return EXIT_FAILURE;
	}

	int level = 0;

	for (int pi = 0; pi < charCount; pi++)
	{
		tempStr[pi] = phraseChars[pi].character;
		tempCount[pi] = phraseChars[pi].count;
	}

	//recursive function that determines permutations (lexicographical ordering)
	Permutation(tempStr, countsl, tempCount, results, level, MAX_STR);
	
	// Open "dictionary" file

	// dword and pword used for pattern matching
	char dword[MAX_DIC] = { 0 };
	char pword[MAX_STR] = { 0 };

	//pointer to the permutations generated from the input phrase
	char* p;
	p = (char*)permutations;

	//indexes to permutation list and dictionary 
	int pi = 0;
	int di = 0;

	//input file "dictionary" (sample used for testing software)
	ifstream iFile;
	iFile.open("dictionary.txt");

	//upon failure to open file exit main with failure
	if (!iFile)
	{
		cout << "dictionary file failed to open!" << endl;
		getchar();

		DereferenceAllocatedMemory();
		return EXIT_FAILURE;
	}

	//look through "dictionary" matching each permutation with read word from file
	while (!iFile.eof())
	{		
		memset(dword, 0, MAX_DIC);
		iFile >> dword;
		do
		{
			memset(pword, 0, MAX_STR);
			strcpy(pword, p);
			if (strcmp(dword, pword) == 0)
			{
				cout << "Dictionary Word[" << di << "] Matches Phrase Word [" << pi << "]\t" << pword << endl;
			}
			pi++;
			p = p + (MAX_STR + 1);
		} 
		while (pi < numberOfPermutations);

		pi = 0;
		p = (char*)permutations;
		di++;
	}

	//close "Dictionary" file
	iFile.close();
	
	DereferenceAllocatedMemory();

	//pause command window until a key is pressed
	getchar();
	
    return EXIT_FAILURE;
}

