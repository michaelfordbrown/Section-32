// MakeBinarySampleFile.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  

#include"MyList.h"
#include "MakeBinaryFile.h"
#include "SearchHayStack.h"

/*
struct ListNode
{
	char chrChar  = 0;
	ListNode* next;
};

class MyList
{
private:

	ListNode* tail;
	ListNode *index;

public:
	ListNode* head;

	MyList();
	~MyList();

	void addnode(char chrInChar);
	void  MyList::showlistfromhead();
};

MyList::MyList()
{
	ListNode *t;

	t = new ListNode();
	t->chrChar = 0;
	t->next = NULL;

	head = t;
	tail = t;
}

MyList::~MyList()
{
	ListNode* last = head;
	while (last != NULL)
	{
		ListNode* unlinked = last;
		last = last->next;
		delete unlinked;
	}
	//_CrtDumpMemoryLeaks();
}

void MyList::addnode(char chrIn)
{
	tail->chrChar = chrIn;

	ListNode *temp = new ListNode;
	temp->chrChar = 0;
	temp->next = temp;

	tail->next = temp;
	tail = temp;
	tail->next = NULL;
}

void  MyList::showlistfromhead()
{
	ListNode *temp = head;

	if (temp != NULL)
	{
		while (temp != NULL)
		{
			std::cout << temp << "\t" << temp->chrChar << "\t" << temp->next << "\n";
			temp = temp->next;
		}
	}
}



void SearchHayStack (char* chrInBinaryFile, MyList* nsNeedle)
{
	bool blnWordFound = false;

	std::ifstream ifsHayStack;
	ifsHayStack.open(chrInBinaryFile, std::ios_base::binary);

	if (!ifsHayStack)
	{
		std::cout << chrInBinaryFile << " binary file failed to open!" << std::endl;
		getchar();
	}

	ListNode *mlTemp = nsNeedle->head;
	char chrHayStackChar = 0;
	char chrNeedleChar = 0;
	chrNeedleChar = mlTemp->chrChar;
	bool blnMatching = false;
	std::streampos stpAnchor = 0;

	while (!ifsHayStack.eof())
	{
		ifsHayStack.get(chrHayStackChar);

		while ((mlTemp->chrChar != '\0') && (!ifsHayStack.eof()))
		{
			if (tolower(chrHayStackChar) == tolower(chrNeedleChar))
			{
				if (!blnMatching)
				{
					blnMatching = true;
					stpAnchor = ifsHayStack.tellg();
				}

				mlTemp = mlTemp->next;
				chrNeedleChar = mlTemp->chrChar;

				ifsHayStack.get(chrHayStackChar);
			}
			else if (!blnMatching)
			{
				ifsHayStack.get(chrHayStackChar);
			}
			else
			{
				mlTemp = nsNeedle->head;
				chrNeedleChar = mlTemp->chrChar;

				ifsHayStack.seekg(stpAnchor);
				ifsHayStack.get(chrHayStackChar);
				blnMatching = false;
			}
		}
		if (blnMatching)
		{
			blnMatching = false;
			mlTemp = nsNeedle->head;
			chrNeedleChar = mlTemp->chrChar;
			std::cout << "Match Found At: " << ifsHayStack.tellg() << std::endl;
		}
		stpAnchor = 0;
	}
}
*/

int main()
{
	MakeBinaryFile mbfText2Binary("TestTextFile.txt", "TestBinaryFile.bin");

	MyList *mlNeedle = new MyList();
	std::cout << "\nEnter Needle: ";

	char chrInput = 0;
	std::cin.get(chrInput);

	while ((chrInput != '\n') && (chrInput != 0))
	{
		mlNeedle->addnode(chrInput);
		std::cin.get(chrInput);
	}

	mlNeedle->showlistfromhead();

	SearchHayStack("TestBinaryFile.bin", mlNeedle);

	ListNode* last = mlNeedle->head;
	while (last != NULL)
	{
		ListNode* unlinked = last;
		last = last->next;
		delete unlinked;
		unlinked = NULL;
	}

	getchar();
	

	return 0;

	_CrtDumpMemoryLeaks();

}

