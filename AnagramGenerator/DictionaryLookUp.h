#pragma once

#include <iostream>
#include <fstream>

#define MAXWORD 30 // Limited to Word length
#define LETTERSINALPHA 26 // Number of letters in the Alphabet

struct Node
{
	// Found and Not Found words
	char word[MAXWORD] = { 0 };
	// Location of Found word in HayStack (Dictionary)
	std::streamoff stoIndex = 0;
	Node* nodNext;
};

class WordList
{
private:
	Node* nodHead;
	Node* nodTail;
	Node *nodIndex;

public:
	WordList()
	{
		Node *nodTemp;

		// Initialize WordList object
		nodTemp = new Node();
		memset(nodTemp->word, 0, MAXWORD);
		nodTemp->nodNext = NULL;

		nodHead = nodTemp;
		nodTail = nodTemp;

	}

	~WordList()
	{
		// De constructor that returns allocated memory
		Node* nodLast = nodHead;
		while (nodLast->word != NULL)
		{
			Node* nodUnlinked = nodLast;
			nodLast = nodLast->nodNext;
			delete nodUnlinked;
		}
		// Memory leak check mechanism
		_CrtDumpMemoryLeaks();
	}

	void AddNode(char* word);
	void ShowListFromHead();
	bool blnSearchListFromHead(char* strWord);
};

bool blnOpenDictionaryFile(std::ifstream & dictionaryInFile, char* strFileName);
bool blnCheckDictionary(std::ifstream & dictionaryInFile, char* strWord, std::streampos  *stoIndex);
void LookForWord(std::ifstream & dictionaryInFile, std::streampos* stoPosition, WordList* strWordFoundList, WordList* strWordNotFoundList, char *strTestWord);

