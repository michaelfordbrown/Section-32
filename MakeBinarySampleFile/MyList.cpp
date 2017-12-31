#include "stdafx.h"
#include "MyList.h"

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
