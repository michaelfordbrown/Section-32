#include "stdafx.h"
#include "SearchHayStack.h"

// Read in next alphabetical character
char chrGetNextLetter(std::ifstream & ifsInFile)
{
	char chrCharIn = 0;

	do
	{
		ifsInFile.get(chrCharIn);
	} while ((!isalpha(chrCharIn) && !ifsInFile.eof()));

	return chrCharIn;
}

// Search HayStack for Needle
void SearchHayStack(char* binHayStackFile, MyList* nsNeedle)
{
	// Needle found flag
	bool blnWordFound = false;

	// Open HayStack binary file
	std::ifstream ifsHayStack;
	ifsHayStack.open(binHayStackFile, std::ios_base::binary);

	if (!ifsHayStack)
	{
		std::cout << binHayStackFile << " binary file failed to open!" << std::endl;
		getchar();
	}

	// Initialize Needle, file pointer to word being matched,  matching characters and flags
	ListNode *mlTemp = nsNeedle->head;
	char chrHayStackChar = 0;
	char chrNeedleChar = 0;
	chrNeedleChar = mlTemp->chrChar;
	bool blnMatching = false;
	std::streampos stpAnchor = std::ios_base::beg;

	// Go through the HayStack
	while (!ifsHayStack.eof())
	{
		chrHayStackChar = chrGetNextLetter(ifsHayStack);

		// Go through the Needle
		while ((mlTemp != NULL) && (!ifsHayStack.eof()))
		{
			chrNeedleChar = mlTemp->chrChar;

			// Matching characters found
			if (tolower(chrHayStackChar) == tolower(chrNeedleChar))
			{
				// Beginning of Needle matched
				if (!blnMatching)
				{
					blnMatching = true;
					stpAnchor = ifsHayStack.tellg();
				}

				// Move to next character in Needle and HayStack
				mlTemp = mlTemp->next;
				chrHayStackChar = chrGetNextLetter(ifsHayStack);
			}
			// Mis-match after finding a match with Needle
			else if (!blnMatching)
			{
				chrHayStackChar = chrGetNextLetter(ifsHayStack);
			}
			// Mis-match of characters 
			else
			{
				mlTemp = nsNeedle->head;
				ifsHayStack.seekg(stpAnchor);
				chrHayStackChar = chrGetNextLetter(ifsHayStack);
				blnMatching = false;
			}
		}
		// Needle FOUND!
		if (blnMatching)
		{
			blnMatching = false;
			mlTemp = nsNeedle->head;
			std::cout << "Match Found At: " << (stpAnchor - (std::streampos)1) << std::endl;
		}
		stpAnchor = std::ios_base::beg;
	}
}

