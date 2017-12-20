// DictionaryTest.cpp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <memory>
#include <iostream>
#include <fstream>
#include <string.h>

#define MAX_STR 32
#define CLEN 120
#define LETTERSINALPHA 26

using namespace std;

int main()
{

	// Open Dictionary

	char* dword = new char[MAX_STR];
	char* pword = new char[MAX_STR];
	char *p = "dog";
	
	int numberOfPermutations = 1;

	ifstream iFile;
	//C:\Users\micha\Source\Repos\IMGModelling\DoubleLinkList\AnagramGenerator
	iFile.open("..\\AnagramGenerator\\dictionary1.txt");

	if (!iFile)
		return EXIT_FAILURE;

	int pi = 0;
	int di = 0;

	while (!iFile.eof())
	{
		memset(dword, 0, MAX_STR);
		iFile >> dword;
		cout << dword << endl;
		do
		{
			memset(pword, 0, MAX_STR);
			strcpy(pword, p);
			if (strcmp(dword, pword) == 0)
			{
				cout << "Dictionary Word[" << di << "] Matches Phrase Word [" << pword << "]\n";
			}
			pi++;
		} while (pi < numberOfPermutations);

		pi = 0;
		di++;
	}

	iFile.close();

	delete[] dword;
	delete[] pword;

    return 0;
}

