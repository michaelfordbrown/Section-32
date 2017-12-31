#include "stdafx.h"
#include "MyList.h"

MyList::MyList()
{
	ListNode *t;

	t = NULL;

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

void MyList::AddNode(char chrIn)
{	
	ListNode *temp = new ListNode;
	temp->chrChar = chrIn;
	
	if (tail == NULL)
	{
		temp->uintIndex = 0;
		temp->next = NULL;
		head = temp;
		tail = temp;
	}
	else
	{
		temp->uintIndex = tail->uintIndex + 1;
		temp->next = NULL;
		temp->prev = tail;
		tail->next = temp;
		tail = temp;
	}
}

void  MyList::ShowListFromHead()
{
	ListNode *temp = head;

	while (temp != NULL)
	{
		std::cout << temp << "\t" << temp->chrChar << "\t" << temp->uintIndex << "\t" << temp->next << "\t" << temp->prev << "\n";
		temp = temp->next;
	}
}

void  MyList::ShowListFromTail()
{
	ListNode *temp = tail;
	
	do
	{
		std::cout << temp << "\t" << temp->chrChar << "\t" << temp->uintIndex << "\t" << temp->next << "\t" << temp->prev << "\n";
			temp = temp->prev;
	} 
	while (temp != head);
}