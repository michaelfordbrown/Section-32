// MakeBinarySampleFile.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  

#include"MyList.h"
#include "MakeBinaryFile.h"
#include "SearchHayStack.h"

/*void MakeBadMatchTable(MyList *mlPattern, unsigned int *uintDistances)
{

	ListNode *mlTemp = mlPattern->head;
	unsigned int uintPatternLength = 0;
	unsigned int uintDefaultValue = 0;

	int i = 0;

	for (int i = 0; i < (MAXALPHA + 1); i++)
		uintDistances[i] = 0;

	while (mlTemp->chrChar != '\0')
	{
		uintPatternLength = uintPatternLength++;
		mlTemp = mlTemp->next;
	}
	uintDefaultValue = uintPatternLength;

	mlTemp = mlPattern->head;
	while (mlTemp->chrChar != '\0')
	{
		uintDistances[int(tolower(mlTemp->chrChar)) - int('a')] = uintPatternLength - i - 1;
		i++;

		if ((i == uintPatternLength) && (uintDistances[int(tolower(mlTemp->chrChar)) - int('a')] == 0))
			uintDistances[int(tolower(mlTemp->chrChar)) - int('a')] = uintDefaultValue;
		mlTemp = mlTemp->next;
	}

	
	uintDistances[MAXALPHA] = uintDefaultValue;
}*/

int main()
{
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

