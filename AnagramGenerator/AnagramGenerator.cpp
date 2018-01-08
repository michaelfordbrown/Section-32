// AnagramGenerator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define _CRTDBG_MAP_ALLOC  

#include <stdlib.h>  
#include <crtdbg.h> 

#include <memory>
#include <iostream>
#include <fstream>
#include <string.h>

#include "HayStackClass.h"
#include "NeedleClass.h"

#define MAX_STR 100
#define LETTERSINALPHA 26
#define MAX_DIC 100
#define FILEERROR 10

char* strPhrase = NULL;
char *strUnsortedInput = NULL;
char* strSortedString = NULL;
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
	/*if (strResults != NULL)
	{
		delete[] strResults;
		strResults = NULL;
	}*/
	
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

void ShowPhraseChars(PhraseChar *p)
{
	int intPermIndex = 0;
	while (p[intPermIndex].intCount > 0)
	{
		std::cout << "\t" << p[intPermIndex].chrCharacter << "\t[" << p[intPermIndex].intCount << "]" << std::endl;
		intPermIndex++;
	}
}

void CheckPermutationsAgainstDictionary(NeedleClass *ncPhrase)
{

	HayStackClass *hscDictionary = new HayStackClass("dictionary.txt");

	strPermutationWord = new char[ncPhrase->intGetNeedleWordLength() + 1];
	memset(strPermutationWord, 0, ncPhrase->intGetNeedleWordLength() + 1);
	for (int i = 0; i < (ncPhrase->intGetNeedleWordLength() + 1); i++)
	{
		strPermutationWord[i] = 0;
	}

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

	permutationsInfile.close();

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

		NeedleClass *ncPhrase = new NeedleClass(argv[1]);
		CheckPermutationsAgainstDictionary(ncPhrase);
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
			case HAYSTACK_FILE_ERROR:
			{
				DereferenceAllocatedMemory();
				std::cout << "HAYSTACK: Unexpected File Error" << std::endl;
				std::cout << "Press any key to continue . . ." << std::endl;;
				getchar();
				return EXIT_FAILURE;
				break;
			}
			case NEEDLE_PERM_FILE_ERROR:
			{
				DereferenceAllocatedMemory();
				std::cout << "NEEDLE: Unexpected File Error" << std::endl;
				std::cout << "Press any key to continue . . ." << std::endl;;
				getchar();
				return EXIT_FAILURE;
				break;
			}

			case NEEDLE_TOO_LONG_ERROR:
			{
				DereferenceAllocatedMemory();
				std::cout << "NEEDLE: Unexpected Data Entry Error" << std::endl;
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
	
	_CrtDumpMemoryLeaks();
    return EXIT_SUCCESS;
}

