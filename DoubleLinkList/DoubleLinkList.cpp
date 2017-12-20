// DoubleLinkList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>

using namespace std;

class DoubleList
{

private:

	struct DoubleNode
	{
		int data;
		DoubleNode* prev;
		DoubleNode* next;
	};

	DoubleNode* head;
	DoubleNode* tail;


public:
	DoubleList()
	{
		DoubleNode *t;
		
		t = new DoubleNode();
		t->data = 0;
		t->prev = NULL;

		head = t;
		tail = t;
	}

	~DoubleList()
	{
		DoubleNode* last = tail;
		while (last->data != NULL)
		{
			DoubleNode* unlinked = last;
			last = last->prev;
			delete unlinked;
		}
	}

	void addnode(int value)
	{
		DoubleNode *temp = new DoubleNode;
		temp->data = value;
		temp->prev = tail;

		tail->next = temp;
		tail = temp;

		tail->next = NULL;
	}

	void showlistfromhead()
	{
		DoubleNode *temp = head;

		cout << "\nHead Node\tAddr\t\tData\tPrevAddr\tNextAddr\n";
		cout << "\t\t" << temp << "\t" << temp->data << "\t" << temp->prev << "\t" << temp->next << "\n";

		cout << "\nAddr\t\tData\tPrevAddr\tNextAddr\n";
		while (temp != NULL)
		{
			cout << temp << "\t" << temp->data << "\t" << temp->prev << "\t" << temp->next << "\n";
			temp = temp->next;
		}
		cout << endl;
	}

	void showlistfromtail()
	{
		DoubleNode *temp = tail;

		cout << "\nTail Node\tAddr\t\tData\tPrevAddr\tNextAddr\n";
		cout << "\t\t" << temp << "\t" << temp->data << "\t" << temp->prev << "\t" << temp->next << "\n";

		cout << "\nAddr\t\tData\tPrevAddr\tNextAddr\n";
		while (temp != NULL)
		{
			cout << temp << "\t" << temp->data << "\t" << temp->prev << "\t" << temp->next << "\n";
			temp = temp->prev;
		}
		cout << endl;
	}

	void reverse()
	{
		DoubleNode * index = head;
		DoubleNode *temp = NULL;; // = new DoubleNode();
		
		while (index != NULL)
		{
			cout << "Index a:\t" << index << "\t" << index->data << "\t" << index->prev <<  "\t" << index->next << "\n"; 
			
			temp = index->prev;

			index->prev = index->next;
			index->next = temp;
			index = index->prev;

		}
		head = temp->prev;
	}

};

void adddoublelistitems(DoubleList& list, int s)
{
	for (int i = s; i < (s + 100); i++)
	{
		list.addnode(i);
	}
}

int main()
{
	DoubleList doublelist1;

	try
	{
		for (int i = 1; i < 10; i++)
		{
			doublelist1.addnode(i);
		}
	}
	catch (...)
	{
		throw;
	}

	doublelist1.showlistfromhead();
	doublelist1.reverse();
	doublelist1.showlistfromhead();

	getchar();
    return 0;
}

