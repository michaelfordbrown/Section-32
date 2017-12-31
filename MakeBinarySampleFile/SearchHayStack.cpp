#include "stdafx.h"
#include "SearchHayStack.h"
#define DEVELOP

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


	for (int i = 0; i < (MAXALPHA + 1); i++)
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
	for (int i = 0; i < (MAXALPHA + 1); i++)
	{
		chrC = int('a') + i;
		if (i == MAXALPHA)
			chrC = int('*');
		std::cout << i << "\t" << chrC << "\t" << uintDistances[i] << std::endl;
	}

}

char chrGetNextLetter(std::ifstream & ifsInFile)
{
	char chrCharIn = 0;

	ifsInFile.get(chrCharIn);
	chrCharIn = tolower(chrCharIn);
	if (!isalpha(chrCharIn) && !ifsInFile.eof())
		chrCharIn = MAXALPHA + int('a');

	return chrCharIn;
}

void SearchHayStack(char* binHayStackFile, MyList* nsNeedle)
{
	bool blnWordFound = false;
	unsigned int *uintBadMatchTable = new unsigned int[MAXALPHA];

	MakeBadMatchTable(nsNeedle, uintBadMatchTable);

	std::ifstream ifsHayStack;
	ifsHayStack.open(binHayStackFile, std::ios_base::binary);

	if (!ifsHayStack)
	{
		std::cout << binHayStackFile << " binary file failed to open!" << std::endl;
		getchar();
	}



#ifdef DEVELOP
	char chrHayStackChar = 0;
	char chrNeedleChar = 0;

	std::streampos stpSkip = std::ios_base::beg;
	std::streampos stpHayPointer = std::ios_base::beg;

	ListNode *InTemp = nsNeedle->tail;
	unsigned int uintNeedleLength = InTemp->uintIndex;
	unsigned int uintSkip = 0;

	ifsHayStack.seekg(uintNeedleLength, stpHayPointer);

	while (!ifsHayStack.eof())
	{
		chrHayStackChar = chrGetNextLetter(ifsHayStack);
		chrNeedleChar = tolower(InTemp->chrChar);

		if (chrHayStackChar == chrNeedleChar)
		{
			if (InTemp != nsNeedle->head)
			{
				ifsHayStack.seekg(-2, std::ios_base::cur);
				InTemp = InTemp->prev;
			}
			else
			{
				ifsHayStack.seekg(-1, std::ios_base::cur);
				std::cout << "Match Found At: " << ifsHayStack.tellg() << std::endl;
				uintSkip = uintNeedleLength + 1;
				ifsHayStack.seekg(uintSkip, std::ios_base::cur);
				InTemp = nsNeedle->tail;
			}
		}
		else
		{
			ifsHayStack.seekg(-1, std::ios_base::cur);
			//std::cout << "Mis Match Now At: " << ifsHayStack.tellg() << std::endl;
			uintSkip = uintBadMatchTable[int(tolower(chrHayStackChar)) -
				int('a')];
			ifsHayStack.seekg(uintSkip, std::ios_base::cur);

			InTemp = nsNeedle->tail;
		}
	}
#else
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
#endif
}
