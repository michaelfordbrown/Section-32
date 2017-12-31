#include "stdafx.h"
#include "SearchHayStack.h"

void MakeBadMatchTable(MyList *mlPattern, unsigned int *uintDistances)
{

	ListNode *mlTemp = mlPattern->head;
	unsigned int uintPatternLength = 0;
	unsigned int uintDefaultValue = 0;

	unsigned int ui = 0;

	while (mlTemp != NULL)
	{
		uintPatternLength = uintPatternLength++;
		mlTemp = mlTemp->next;
	}
	uintDefaultValue = uintPatternLength;


	for (int i = 0; i < (MAXALPHA); i++)
		uintDistances[i] = uintDefaultValue;

	mlTemp = mlPattern->head;
	while (mlTemp != NULL)
	{
		if (ui < (uintPatternLength - 1))
		{
			uintDistances[int(tolower(mlTemp->chrChar)) - int('a')] = uintPatternLength - ui - 1;
		}

		ui++;
		mlTemp = mlTemp->next;
	}

	char chrC;
	for (int i = 0; i < MAXALPHA; i++)
	{
		chrC = int('a') + i;
		std::cout << i << "\t" << chrC << "\t" << uintDistances[i] << std::endl;
	}

}

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
	unsigned int *uintBadMatchTable = new unsigned int[MAXALPHA];

	MakeBadMatchTable(nsNeedle, uintBadMatchTable);

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
		while ((mlTemp != NULL) && (!ifsHayStack.eof()))
		{
			chrNeedleChar = mlTemp->chrChar;
			if (tolower(chrHayStackChar) == tolower(chrNeedleChar))
			{
				if (!blnMatching)
				{
					blnMatching = true;
					stpAnchor = ifsHayStack.tellg();
				}
				mlTemp = mlTemp->next;
				chrHayStackChar = chrGetNextLetter(ifsHayStack);
			}
			else if (!blnMatching)
			{
				chrHayStackChar = chrGetNextLetter(ifsHayStack);
			}
			else
			{
				mlTemp = nsNeedle->head;
				ifsHayStack.seekg(stpAnchor);
				chrHayStackChar = chrGetNextLetter(ifsHayStack);
				blnMatching = false;
			}
		}
		if (blnMatching)
		{
			blnMatching = false;
			mlTemp = nsNeedle->head;
			std::cout << "Match Found At: " << stpAnchor << std::endl;
		}
		stpAnchor = std::ios_base::beg;
	}
}
