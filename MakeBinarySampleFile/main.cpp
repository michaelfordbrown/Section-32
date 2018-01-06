// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// check for memory leaks
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  

#include"MyList.h"
#include "MakeBinaryFile.h"
#include "SearchHayStack.h"

int main()
{
	// Convert text based test file to a binary file
	MakeBinaryFile mbfText2Binary("TestTextFile.txt", "TestBinaryFile.bin");


	// Create linked list for Needle
	MyList *mlNeedle = new MyList();

	// Get Needle string from console
	std::cout << "\nEnter Needle: ";
	char chrInput = 0;
	std::cin.get(chrInput);
		
	while ((chrInput != '\n') && (chrInput != 0))
	{
		mlNeedle->AddNode(chrInput);
		std::cin.get(chrInput);
	}

	// Display Needle
	mlNeedle->ShowListFromHead();
	
	// Search HayStack for Needle
	SearchHayStack("TestBinaryFile.bin", mlNeedle);
	std::cout << "\nSearch Completed\n";

	// Return allocated memory to the heap
	ListNode* last = mlNeedle->head;
	while (last != NULL)
	{
		ListNode* unlinked = last;
		last = last->next;
		delete unlinked;
		unlinked = NULL;
	}

	// Pause console screen
	getchar();
	

	return 0;

	// check for memory leaks
	_CrtDumpMemoryLeaks();

}

