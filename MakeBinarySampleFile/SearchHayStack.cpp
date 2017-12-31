#include "stdafx.h"
#include "SearchHayStack.h"

char chrGetNextLetter(std::ifstream & ifsInFile)
{
	char chrCharIn = 0;

	do
	{
		ifsInFile.get(chrCharIn);
	}
	while ((!isalpha(chrCharIn) && !ifsInFile.eof()));

	return chrCharIn;
}

void SearchHayStack(char* chrInBinaryFile, MyList* nsNeedle)
{
	bool blnWordFound = false;

	std::ifstream ifsHayStack;
	ifsHayStack.open(chrInBinaryFile, std::ios_base::binary);

	if (!ifsHayStack)
	{
		std::cout << chrInBinaryFile << " binary file failed to open!" << std::endl;
		getchar();
	}

	ListNode *mlTemp = nsNeedle->head;
	char chrHayStackChar = 0;
	char chrNeedleChar = 0;
	chrNeedleChar = mlTemp->chrChar;
	bool blnMatching = false;
	std::streampos stpAnchor = std::ios_base::beg;

	while (!ifsHayStack.eof())
	{
		chrHayStackChar = chrGetNextLetter(ifsHayStack);

		while ((mlTemp->chrChar != '\0') && (!ifsHayStack.eof()))
		{
			if (tolower(chrHayStackChar) == tolower(chrNeedleChar))
			{
				if (!blnMatching)
				{
					blnMatching = true;
					stpAnchor = ifsHayStack.tellg();
				}

				mlTemp = mlTemp->next;
				chrNeedleChar = mlTemp->chrChar;

				chrHayStackChar = chrGetNextLetter(ifsHayStack);
			}
			else if (!blnMatching)
			{
				chrHayStackChar = chrGetNextLetter(ifsHayStack);
			}
			else
			{
				mlTemp = nsNeedle->head;
				chrNeedleChar = mlTemp->chrChar;

				ifsHayStack.seekg(stpAnchor);
				chrHayStackChar = chrGetNextLetter(ifsHayStack);
				blnMatching = false;
			}
		}
		if (blnMatching)
		{
			blnMatching = false;
			mlTemp = nsNeedle->head;
			chrNeedleChar = mlTemp->chrChar;
			std::cout << "Match Found At: " << stpAnchor << std::endl;
		}
		stpAnchor = std::ios_base::beg;
	}
}
