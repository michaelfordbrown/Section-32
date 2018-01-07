#include "stdafx.h"
#include "HayStackClass.h"


HayStackClass::HayStackClass(char* strFileName)
{
	char buf[MAXWORD];

	HayStackClass::ifsHayStack.open(strFileName);

	if (!HayStackClass::ifsHayStack)
	{
		std::cout << "ERROR HayStack file failed to open!" << std::endl;
		getchar();
		throw(FILE_ERROR);
	}
}


HayStackClass::~HayStackClass()
{
}


void HayStackClass::blnCloseHayStackFile()
{
	HayStackClass::ifsHayStack.close();
}

bool HayStackClass::blnCheckHayStackFile(char* strNeedle)
{
	bool blnWordFound = false;
	char strHayThread[MAXWORD];

	//HayStackClass:: stpHayStackFilePos = HayStackClass::ifsHayStack.tellg();
	HayStackClass::ifsHayStack >> strHayThread;
	for (size_t i = 0; i < strlen(strHayThread); i++)
	{
		strHayThread[i] = tolower(strHayThread[i]);
	}

	while ((!HayStackClass::ifsHayStack.eof()) &&
		// OPTIMIZATION: Assuming that dictionary in alphabetical order 
		// as no need to search beyond last word with same first letter 
		(strHayThread[0] <= strNeedle[0]) &&
		// Continue search if Needle has not been found in HayStack(Dictionary)
		(!blnWordFound))
	{
		//if(strHayThread[0] == strNeedle[0])
			// Add straw to the straw list (words read from file) data structure (array of linked list)
			wlcHayThreadListArray[int(strHayThread[0]) - int('a')].AddNode(strHayThread);

		// Has Needle been found in the HayStack
		if (strcmp(strNeedle, strHayThread) == 0)
		{
			blnWordFound = true;
			exit;
		}

		HayStackClass::ifsHayStack >> strHayThread;
		for (size_t i = 0; i < strlen(strHayThread); i++)
		{
			strHayThread[i] = tolower(strHayThread[i]);
		}
	}

	return blnWordFound;
}

void HayStackClass::LookForNeedleInHayStack(char *strNeedle)
{
	// Check if needle has already been found (look in link list of found words)
	if (!wlcHayThreadListArray[int(strNeedle[0]) - int('a')].blnSearchListFromHead(strNeedle))
	{
		// Look through the Haystack (Dictionary) for the Needle
		if (HayStackClass::blnCheckHayStackFile(strNeedle))
		{
			std::cout << strNeedle << " found." << std::endl;
		}
	}
	else
	{
		std::cout << strNeedle << " found." << std::endl;
	}
}