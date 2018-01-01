// MakeBinarySampleFile.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  

#include"MyList.h"
#include "MakeBinaryFile.h"
#include "SearchHayStack.h"

int main()
{
	for (int i = 0; i < 100; i++)
		std::cout << (i % 10);
	std::cout << std::endl;

	MakeBinaryFile mbfText2Binary("TestTextFile.txt", "TestBinaryFile.bin");

	MyList *mlNeedle = new MyList();
	std::cout << "\nEnter Needle: ";

	char chrInput = 0;
	std::cin.get(chrInput);

	
	while ((chrInput != '\n') && (chrInput != 0))
	{
		mlNeedle->AddNode(chrInput);
		std::cin.get(chrInput);
	}

	mlNeedle->ShowListFromHead();


	SearchHayStack("TestBinaryFile.bin", mlNeedle);

	std::cout << "\nSearch Completed\n";

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

