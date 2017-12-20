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
#define CLEN 120
#define LETTERSINALPHA 26

using namespace std;

char* permutations = NULL;
char* phrase = NULL;
char *unsortedInput = NULL;
char* sortedString = NULL;

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

//Swap to char within char array
void TempSwap(char*t, int a, int b)
{
	char temp;

	temp = t[a];
	t[a] = t[b];
	t[b] = temp;
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
		cout << "Result:\t" << res << endl;
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
	cout << "Anagram Generator\n";

	// Get Phase from command line
	if (argc < 2)
		// No phrase seen from the command line
		return EXIT_FAILURE;

	for (int i = 0; i < argc; i++)
		cout << "Argument from command line[" << i << "]\t" <<  argv[i] << endl;

	//Define phrase variable from the heap
	const int phraseLength = strlen(argv[1]);

	phrase = new char[MAX_STR];
	memset(phrase, 0, MAX_STR);

	strcpy(phrase, argv[1]);

	cout << "\nGot Phase:\t" << phrase << endl;
	
	//Sort Phrase character
	unsortedInput = new char[MAX_STR];
	memset(unsortedInput, 0, MAX_STR);

	sortedString = new char[MAX_STR];
	memset(sortedString, 0, MAX_STR);

	strcpy(unsortedInput, phrase);

	SortString(sortedString, unsortedInput, strlen(unsortedInput));

	cout << "Unsorted String:\t" << unsortedInput << endl;
	cout << "Sorted String:     \t" << sortedString << endl;

	//Count Phrase alphabetical characters
	int countsl = 0;
	int charCount = 0;
	PhraseChar phraseChars[LETTERSINALPHA];

	countsl = CountChar(phraseChars, sortedString, strlen(sortedString), charCount);

	//Determine denominator for no. of permutations calculations

	int permutationDenominator = 1;
	for (int i = 0; i < charCount; i++)
	{
		permutationDenominator = permutationDenominator * Factorial(phraseChars[i].count);
	}

	const int numberOfPermutations = Factorial(phraseLength)/ permutationDenominator;

	permutations = new char[MAX_STR * (numberOfPermutations+1) ];
	memset(permutations, 0, MAX_STR * (numberOfPermutations + 1));

	int startIndex = 0;
	int endIndex = phraseLength - 1;

	int noofchar = 0;
		
	ShowPhraseChars(phraseChars);

	char tempStr[LETTERSINALPHA] = { 0 };
	int tempCount[LETTERSINALPHA] = { 0 };
	char *results = new char[numberOfPermutations];
	memset(results, 0, numberOfPermutations);

	int level = 0;

	for (int pi = 0; pi < charCount; pi++)
	{
		tempStr[pi] = phraseChars[pi].character;
		tempCount[pi] = phraseChars[pi].count;
	}


	Permutation(tempStr, countsl, tempCount, results, level, MAX_STR);
	
	// Open Dictionary

	char dword[50] = { 0 };
	char pword[MAX_STR] = { 0 };
	char* p;
	p = (char*)permutations;

	ifstream iFile;
	iFile.open("dictionary1.txt");

	if (!iFile)
		return EXIT_FAILURE;

	int pi = 0;
	int di = 0;

	while (!iFile.eof())
	{		
		memset(dword, 0, 50);
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

	iFile.close();
	
	delete[] results;

	delete []permutations;


	delete []sortedString;
	delete []unsortedInput;
	delete []phrase;

	results = NULL;
	//permutations = NULL;

//	sortedString = NULL;
//	unsortedInput = NULL;
	phrase = NULL;

	getchar();

	_CrtDumpMemoryLeaks();

    return 0;
}

