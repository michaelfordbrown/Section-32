#pragma once

#include <iostream>
#include <fstream>

#define MAXWORD 30
#define MAXALPHA 26

struct Node
{
	char word[MAXWORD] = { 0 };
	std::streamoff stoIndex = 0;
	Node* next;
};

class WordList
{
private:

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

	void addnode(char* word);

	void showlistfromhead();

	bool blnSearchListFromHead(char* strWord);
};

bool OpenDictionaryFile(std::ifstream & dictionaryInFile, char* strFileName);

bool CheckDictionary(std::ifstream & dictionaryInFile, char* strWord, std::streampos  *stoIndex);

bool CheckFoundWords(char *strWord);

void LookForWord(std::ifstream & dictionaryInFile, std::streampos* stoPosition, WordList* strWordFoundList, WordList* strWordNotFoundList, char *strTestWord);

