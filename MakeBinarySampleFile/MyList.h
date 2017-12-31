#pragma once

#include <iostream>

#define MAXALPHA 26 

struct ListNode
{
	char chrChar = 0;
	unsigned int uintIndex = 0;
	ListNode* next;
	ListNode* prev;
};

class MyList
{
private:

	ListNode *index;

public:
	ListNode* tail;
	ListNode* head;

	MyList();
	~MyList();

	void AddNode(char chrInChar);
	void  MyList::ShowListFromHead();
	void  MyList::ShowListFromTail();
};

