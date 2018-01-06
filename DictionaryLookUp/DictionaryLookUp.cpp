// DictionaryLookUp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h> 

#include <memory>
#include <iostream>
#include <fstream>
#include <string.h>

#include "DictionaryLookUp.h"

void WordList::addnode(char* word)
{
	Node *temp = new Node;
	strcpy(temp->word, word);
	//temp->stoIndex = stoPosition;
	temp->next = temp;

	tail->next = temp;
	tail = temp;
	tail->next = NULL;
}

void WordList::showlistfromhead()
{
	Node *temp = head;
	int iTest = 0;

	if (temp != NULL)
	{
		while (temp != NULL)
		{
			if (strlen(temp->word) > 0)
			{
				std::cout << char(int(tolower(temp->word[0]))) << "\t" << temp << "\t" << temp->word << "\t\t" << temp->next << "\n";
			}
			temp = temp->next;
		}
	}
}

bool WordList::searchlistfromhead(char* strWord)
{
	index = head;

	while (index != NULL)
	{
		if (strcmp(strWord, "football") == 0)
			;
		if (strcmp(index->word, strWord) == 0)
		{
			return true;
		}
		else
		{
			index = index->next;
		}
	}
	return false;
}

void addToWordList(WordList* list, char* word)
{
	list[int(word[0]) - int('a')].addnode(word);
}

bool OpenDictionaryFile(std::ifstream & dictionaryInFile, char* strFileName)
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

bool CheckDictionary(std::ifstream & dictionaryInFile, char* strWord, std::streampos* stoIndex)
{
	bool blnWordFound = false;

	char strDicWord[MAXWORD] = { 0 };
	char chrFirstChar = tolower(strWord[0]);
	char chrDicChar = ' ';

	std::streampos stpFilePos = 0;

	while ((!dictionaryInFile.eof()) && 
		(chrDicChar <= chrFirstChar) &&
		(!blnWordFound))
	{
		memset(strDicWord, 0, MAXWORD);

		if ((stoIndex[int(chrFirstChar) - int('a')] == std::streampos(0)) && (!blnWordFound))
		{
			dictionaryInFile >> strDicWord;
			chrDicChar = tolower(strDicWord[0]);
			stpFilePos = dictionaryInFile.tellg();

			if (chrDicChar == chrFirstChar)
			{
				stoIndex[int(chrFirstChar) - int('a')] =
					dictionaryInFile.tellg() - 
					std::streampos(strlen(strDicWord) - 1);
			}
		}
		else if (stpFilePos < (stoIndex[int(chrFirstChar) - int('a')]))
		{
			dictionaryInFile.seekg(stoIndex[chrFirstChar - int('a')]);
			dictionaryInFile >> strDicWord;
			chrDicChar = tolower(strDicWord[0]);
			stpFilePos = dictionaryInFile.tellg();
		}
		else
		{
			dictionaryInFile >> strDicWord;
			chrDicChar = tolower(strDicWord[0]);
			stpFilePos = dictionaryInFile.tellg();
		}

		if (strcmp(strWord, "football") == 0)
			;
		if (strcmp(strWord, strDicWord) == 0)
		{
			blnWordFound = true;
		}
	}

	return blnWordFound;
}

bool CheckFoundWords(char *strWord)
{

	int intFoundLinkIndex = tolower(strWord[0] - int('a'));


	return true;
}

void LookForWord(std::ifstream & dictionaryInFile, std::streampos* stoPosition, WordList* strWordFoundList, WordList* strWordNotFoundList, char *strTestWord)
{
	int intListIndex = int(tolower(strTestWord[0])) - int('a');

	if (!strWordFoundList[intListIndex].searchlistfromhead(strTestWord))
	{
		if (!strWordNotFoundList[intListIndex].searchlistfromhead(strTestWord))
		{
			if (CheckDictionary(dictionaryInFile, strTestWord, stoPosition))
			{
				std::cout << strTestWord << " found at: " << stoPosition[intListIndex] << std::endl;
				strWordFoundList[intListIndex].addnode(strTestWord);
			}
			else
			{
				strWordNotFoundList[intListIndex].addnode(strTestWord);
			}
		}
		else
		{
			std::cout << strTestWord << " cannot be found in dictionary.\n";
		}
	}
	else
	{
		std::cout << strTestWord << " already in dictionary.\n";
	}
}


