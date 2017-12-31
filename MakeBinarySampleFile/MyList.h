#pragma once

#include <iostream>

struct ListNode
{
	char chrChar = 0;
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

