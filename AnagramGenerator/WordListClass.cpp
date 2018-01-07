#include "stdafx.h"
#include "WordListClass.h"
#include <iostream>

WordListClass::WordListClass()
{
	Node *nodTemp;

	// Initialize WordList object
	nodTemp = new Node();
	memset(nodTemp->word, 0, MAXWORD);
	nodTemp->intIndex = 0;

	// At the end of the list (next node is NULL)
	nodTemp->nodNext = NULL;

	// Set HEAD and TAIL nodes
	nodHead = nodTemp;
	nodTail = nodTemp;
}

WordListClass::~WordListClass()
{
		// De constructor that returns allocated memory
		Node* nodLast = nodHead;

		// Loop through all nodes in list from head to the tail
		while (nodLast->word != NULL)
		{
			//deallocate node memory and set node pointer to NULL
			Node* nodUnlinked = nodLast;
			nodLast = nodLast->nodNext;
			delete nodUnlinked;
			nodUnlinked = NULL;
		}

		// Memory leak check mechanism
		//_CrtDumpMemoryLeaks();
}

void WordListClass ::AddNode(char* word)
{
	// Add word to link list and update list pointer
	// Set-up Temp node then change tail->next to point to new temp node making temp node new tail
	Node *nodTemp = new Node;
	std::strcpy(nodTemp->word, word);
	nodTemp->intIndex = (nodTail->intIndex + 1) % INT_MAX;
	nodTemp->nodNext = nodTemp;

	nodTail->nodNext = nodTemp;
	nodTail = nodTemp;
	nodTail->nodNext = NULL;
}

void WordListClass::ShowListFromHead()
{
	// Go to the Head of the list
	Node *nodTemp = nodHead;

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

bool WordListClass::blnSearchListFromHead(char* strWord)
{
	// Start from the Head of the linked list
	nodIndex = nodHead;

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



