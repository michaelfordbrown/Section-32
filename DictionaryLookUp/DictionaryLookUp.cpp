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

using namespace std;

#define MAXWORD 30
#define MAXALPHA 26



class WordList
{
private:

	struct Node
	{
		char word[MAXWORD] = { 0 };
		streamoff stoIndex = 0;
		Node* next;
	};

	Node* head;
	Node* tail;
	Node *index;

public:
	WordList()
	{
		Node *t;

		t = new Node();
		memset(t->word, 0, MAXWORD);
		t->next = NULL;

		head = t;
		tail = t;

	}

	~WordList()
	{
		Node* last = head;
		while (last->word != NULL)
		{
			Node* unlinked = last;
			last = last->next;
			delete unlinked;
		}
		_CrtDumpMemoryLeaks();
	}

	void addnode(char* word)
	{
		Node *temp = new Node;
		strcpy(temp->word, word);
		//temp->stoIndex = stoPosition;
		temp->next = temp;

		tail->next = temp;
		tail = temp;
		tail->next = NULL;
	}

	void showlistfromhead()
	{
		Node *temp = head;

		if (temp != NULL)
		{
			while (temp != NULL)
			{
				if (strlen(temp->word) > 0)
				{
					cout << temp << "\t" << temp->word << "\t" << temp->next << "\n";
				}
				temp = temp->next;
			}
		}
	}

	bool searchlistfromhead(char* strWord)
	{
		index = head;

		while (index != NULL)
		{
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
};

void addToWordList(WordList* list, char* word)
{
	list[int(word[0]) - int("a")].addnode(word);
}

ifstream dictionaryInFile;

int WordFoundArray[26] = { 0 };

//WordIndex wiWordInDictionary;

bool OpenDictionaryFile(char* strFileName)
{
	dictionaryInFile.open(strFileName);

	if (!dictionaryInFile)
	{
		cout << "dictionary/permutations file failed to open!" << endl;
		getchar();

		return false;
	}

	return true;
}

bool CheckDictionary(char* strWord, streampos* stoIndex)
{
	bool blnWordFound = false;

	char strDicWord[MAXWORD] = { 0 };
	char chrFirstChar = tolower(strWord[0]);
	char chrDicChar = ' ';

	streampos stpFilePos = 0;

	while ((!dictionaryInFile.eof()) && 
		(chrDicChar <= chrFirstChar) &&
		(!blnWordFound))
	{
		memset(strDicWord, 0, MAXWORD);

		if ((stoIndex[int(chrFirstChar) - int('a')] == streampos(0)) && (!blnWordFound))
		{
			dictionaryInFile >> strDicWord;
			chrDicChar = tolower(strDicWord[0]);
			stpFilePos = dictionaryInFile.tellg();

			if (chrDicChar == chrFirstChar)
			{
				stoIndex[int(chrFirstChar) - int('a')] =
					dictionaryInFile.tellg() - 
					streampos(strlen(strDicWord) - 1);
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

WordList strWordFoundList[MAXALPHA];
WordList strWordNotFoundList[MAXALPHA];

streampos stoPosition[MAXALPHA] = { 0 };

void LookForWord(char *strTestWord)
{
	int intListIndex = int(tolower(strTestWord[0])) - int('a');

	if (!strWordFoundList[intListIndex].searchlistfromhead(strTestWord))
	{
		if (!strWordNotFoundList[intListIndex].searchlistfromhead(strTestWord))
		{
			if (CheckDictionary(strTestWord, stoPosition))
			{
				cout << strTestWord << " found at: " << stoPosition[intListIndex] << endl;
				strWordFoundList[intListIndex].addnode(strTestWord);
			}
			else
			{
				strWordNotFoundList[intListIndex].addnode(strTestWord);
			}
		}
		else
		{
			cout << strTestWord << " cannot be found in dictionary.\n";
		}
	}
	else
	{
		cout << strTestWord << " already in dictionary.\n";
	}
}

int main()
{
	OpenDictionaryFile("dictionary.txt");

	LookForWord("Michael");
	dictionaryInFile.seekg(0);
	LookForWord("Aarhus");
	LookForWord("hello");
	LookForWord("world");
	dictionaryInFile.seekg(0);
	LookForWord("Aaron");
	LookForWord("Qwebet");
	dictionaryInFile.seekg(0);
	LookForWord("hello");
	LookForWord("Qwebet");

	cout << "\nWords Found\n";
	cout << "Addr\t\tWord\tNextAddr\n";
	for (int i = 0; i < MAXALPHA; i++)
	{
		strWordFoundList[i].showlistfromhead();
	}

	cout << "\nWords Not Found\n"; 
	cout << "Addr\t\tWord\tNextAddr\n";
	for (int i = 0; i < MAXALPHA; i++)
	{
		strWordNotFoundList[i].showlistfromhead();
	}

	dictionaryInFile.close();

    return EXIT_SUCCESS;
}

