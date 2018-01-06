// DictionaryLookUp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define _CRTDBG_MAP_ALLOC  // Memory leek check mechanism 
#include <stdlib.h>  
#include <crtdbg.h> 

#include <memory>
#include <iostream>
#include <fstream>
#include <string.h>

#include "DictionaryLookUp.h"

void WordList::AddNode(char* word)
{
	// Add word to link list and update list pointer
	Node *nodTemp = new Node;
	strcpy(nodTemp->word, word);
	//temp->stoIndex = stoPosition;
	nodTemp->nodNext = nodTemp;

	nodTail->nodNext = nodTemp;
	nodTail = nodTemp;
	nodTail->nodNext = NULL;
}

void WordList::ShowListFromHead()
{
	// Go to the Head of the list
	Node *nodTemp = nodHead;
	int iTest = 0;

	// Go through list until the end has been reached
	while (nodTemp != NULL)
	{
		// if a valid word/string has been found in the list
		if (strlen(nodTemp->word) > 0)
		{
			std::cout << char(int(tolower(nodTemp->word[0]))) << "\t" << nodTemp << "\t" << nodTemp->word << "\t\t" << nodTemp->nodNext << "\n";
		}
		// Go to the next word in the list
		nodTemp = nodTemp->nodNext;
	}
}

bool WordList::blnSearchListFromHead(char* strWord)
{
	// Start from the Head of the linked list
	nodIndex = nodHead;

	if (strcmp(strWord, "football") == 0)
		std::cout << "Word Search: FootBall Search\n";

	// Before getting to the end of the list . . 
	while (nodIndex != NULL)
	{
		// If word found in list then  . . .
		if (strcmp(nodIndex->word, strWord) == 0)
		{
			return true;
		}
		// Go to the next word in the list
		else
		{
			nodIndex = nodIndex->nodNext;
		}
	}
	// Word has not been found in the list.
	return false;
}

void addToWordList(WordList* list, char* word)
{
	// Use first character of word to index the correct link list of words
	list[int(word[0]) - int('a')].AddNode(word);
}

bool blnOpenDictionaryFile(std::ifstream & dictionaryInFile, char* strFileName)
{
	dictionaryInFile.open(strFileName);

	if (!dictionaryInFile)
	{
		std::cout << "dictionary/permutations file failed to open!" << std::endl;
		getchar();
		return false;
	}
	return true;
}

bool blnCheckDictionary(std::ifstream & dictionaryInFile, char* strWord, std::streampos* stoIndex)
{
	bool blnWordFound = false;

	char strDicWord[MAXWORD] = { 0 };
	char chrFirstChar = tolower(strWord[0]);
	char chrDicChar = 'a';

	dictionaryInFile.clear();
	dictionaryInFile.seekg(0);

	std::streampos stpFilePos = std::ios::beg;

	stpFilePos = dictionaryInFile.tellg();
	dictionaryInFile >> strDicWord;
	for (size_t i = 0; i < strlen(strDicWord); i++)
	{
		strDicWord[i] = tolower(strDicWord[i]);
	}
	chrDicChar = tolower(strDicWord[0]);

	// DEBUG
	if (strcmp(strWord, "football") == 0)
		std::cout << "Dictionary Search: FootBall Search\n";

	while ((!dictionaryInFile.eof()) && 
		// OPTIMIZATION: Assuming that dictionary in alphabetical order no need to search beyond last word with same first letter 
		(chrDicChar <= chrFirstChar) && 
		// Continue search if Needle has not been found in HayStack(Dictionary)
		(!blnWordFound))
	{
		//memset(strDicWord, 0, MAXWORD);

		// When first time that first letter of Needle seen  . . .
		if ((stoIndex[int(chrDicChar) - int('a')] == std::streampos(0)) && (chrDicChar > 'a'))
		{
			// Record HayStack(Dictionary) file position to record position of character in Found list
			std::cout << "Words Starting with letter " << chrDicChar << " Located At: " << stpFilePos << std::endl;
			stoIndex[int(chrDicChar) - int('a')] =
				stpFilePos;
		}
		// Jump to position in HayStack(Dictionary) where the words start with same first character as Needle
		else if (stpFilePos < (stoIndex[int(chrFirstChar) - int('a')]))
		{
			dictionaryInFile.seekg(stoIndex[chrFirstChar - int('a')]);
		}
		// Progress through HayStack(Dictionary) while first character of words match

		// Needle found in HayStack (Dictionary) . . .
		//DEBUG
		if (strcmp(strWord, "aaron") == 0)
			std::cout << "Dic Search: aaron\n";
		if (strcmp(strWord, strDicWord) == 0)
		{
			blnWordFound = true;
		}

		stpFilePos = dictionaryInFile.tellg();
		dictionaryInFile >> strDicWord;
		for (size_t i = 0; i < strlen(strDicWord); i++)
		{
			strDicWord[i] = tolower(strDicWord[i]);
		}
		chrDicChar = tolower(strDicWord[0]);
	}

	return blnWordFound;
}

void LookForWord(std::ifstream & dictionaryInFile, std::streampos* stoPosition, WordList* strWordFoundList, WordList* strWordNotFoundList, char *strTestWord)
{
	// Found and Not Found is an array of list with each list member of array dedicated to a letter of alphabet
	// (from first character of Needle word)
	int intListIndex = int(tolower(strTestWord[0])) - int('a');

	// Check if needle has already been found (look in link list of found words)
	if (!strWordFoundList[intListIndex].blnSearchListFromHead(strTestWord))
	{
		// Check if there has been an unsuccessful search for needle before (look in link list of not found words)
		if (!strWordNotFoundList[intListIndex].blnSearchListFromHead(strTestWord))
		{
			// Look through the Haystack (Dictionary) for the Needle
			// If Needle found return position in dictionary file and add to Found list.
			if (blnCheckDictionary(dictionaryInFile, strTestWord, stoPosition))
			{
				std::cout << strTestWord << " found at: " << stoPosition[intListIndex] << std::endl;
				strWordFoundList[intListIndex].AddNode(strTestWord);
			}
			// If Needle not found then add to Not Found list.
			else
			{
				strWordNotFoundList[intListIndex].AddNode(strTestWord);
			}
		}
		else
		// If Needle already in Not Found list . . .
		{
			std::cout << strTestWord << " cannot be found in dictionary.\n";
		}
	}
	// If Needle already in Found list  . . .
	else
	{
		std::cout << strTestWord << " already in dictionary.\n";
	}
}


