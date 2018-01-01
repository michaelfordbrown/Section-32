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
		std::cout << i << "\t" << chrC << "\t" << uintDistances[i] << "\t";
	}
	std::cout << std::endl;

}

char chrGetNextLetter(std::ifstream & ifsInFile)
{
	char chrCharIn = 0;

	ifsInFile.get(chrCharIn);
	chrCharIn = tolower(chrCharIn);

	while (!isalpha(chrCharIn) && !ifsInFile.eof())
	{
		ifsInFile.seekg(-1, std::ios::cur);
		//std::cout << "Cur GNL File Pos: " << chrCharIn << " at: " << ifsInFile.tellg() << "\t";

		ifsInFile.seekg(-1, std::ios::cur);
		ifsInFile.get(chrCharIn);
		chrCharIn = tolower(chrCharIn);

		ifsInFile.seekg(-1, std::ios::cur);
		//std::cout << "New GNL File Pos: " << chrCharIn << " at: " << ifsInFile.tellg() << std::endl;
		ifsInFile.seekg(1, std::ios::cur);
	}

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

	bool blnEndSearch = false;
	bool blnMatchInProgress = false;

	char chrHayStackChar = 0;
	char chrNeedleChar = 0;

	std::streampos stpSkip = std::ios_base::beg;
	std::streampos stpAncor = std::ios_base::beg;
	std::streampos stpHayPointer = std::ios_base::beg;

	ListNode *InTemp = nsNeedle->tail;
	char chrSkipChar = tolower(InTemp->chrChar);
	unsigned int uintNeedleLength = (InTemp->uintIndex)+1;
	unsigned int uintSkip = 0;

	int intCurrentFilePoisiton = 0;

	int intOffsetEnd = 0 - (int)uintNeedleLength;
	ifsHayStack.seekg(intOffsetEnd, ifsHayStack.end);
	int intFinalSearchPosition = (int)ifsHayStack.tellg();

	ifsHayStack.seekg((uintNeedleLength - 1), ifsHayStack.beg);
	stpAncor = ifsHayStack.tellg();

	while (!ifsHayStack.eof() && !blnEndSearch)
	{
		chrHayStackChar = chrGetNextLetter(ifsHayStack);
		chrNeedleChar = tolower(InTemp->chrChar);

		if (chrHayStackChar == chrNeedleChar)
		{
			blnMatchInProgress = true;
			if (InTemp != nsNeedle->head)
			{
				ifsHayStack.seekg(-2, std::ios::cur);
				InTemp = InTemp->prev;
			}
			else
			{
				ifsHayStack.seekg(-1, std::ios::cur);
				std::cout << "Match Found At: " << ifsHayStack.tellg() << std::endl;

				intCurrentFilePoisiton = (int)ifsHayStack.tellg();
				if ((intCurrentFilePoisiton < intFinalSearchPosition) && (intCurrentFilePoisiton >= 0))
				{
					uintSkip = uintNeedleLength;
					ifsHayStack.seekg(stpAncor);
					ifsHayStack.seekg(uintSkip, std::ios::cur);
					stpAncor = ifsHayStack.tellg();
					InTemp = nsNeedle->tail;
				}
				else
				{
					blnEndSearch = true;
				}
			}
		}
		else
		{

			if (!blnMatchInProgress)
			{
				uintSkip = uintBadMatchTable[int(tolower(chrHayStackChar)) -
				int('a')];
				blnMatchInProgress = false;
			}
			else
			{
				uintSkip = uintBadMatchTable[int(tolower(chrSkipChar)) -
					int('a')];
			}

			ifsHayStack.seekg(-1, std::ios_base::cur);
			ifsHayStack.seekg(stpAncor);
			intCurrentFilePoisiton = (int)ifsHayStack.tellg();
			if ((intCurrentFilePoisiton < intFinalSearchPosition) && (intCurrentFilePoisiton >= 0))
			{
				ifsHayStack.seekg(stpAncor);
				ifsHayStack.seekg(uintSkip, std::ios::cur);
				stpAncor = ifsHayStack.tellg();
				InTemp = nsNeedle->tail;
			}
			else
			{
				blnEndSearch = true;
			}

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
