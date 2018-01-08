#include "stdafx.h"
#include "NeedleClass.h"

char strResults[MAX_NEEDLE_WORD + 1];
int intCountingStringLevel = 0;
std::ofstream ofsPermutations;
std::ifstream ifsPermutations;

int Factorial(int n)
{
	int intValue = 1;

	// The intValue of 0! is 1
	if (n > 0)
	{
		for (int i = 1; i <= n; i++)
			intValue = intValue * i;
	}

	return intValue;
}

NeedleClass::NeedleClass()
{
}


NeedleClass::~NeedleClass()
{
	/*if (NeedleClass::strNeedleWord != NULL)
	{
		delete[] NeedleClass::strNeedleWord;
		strNeedleWord = NULL;
	}

	if (NeedleClass::intLetterCountArray != NULL)
	{
		delete[] NeedleClass::intLetterCountArray;
		NeedleClass::intLetterCountArray = NULL;
	}

	if (NeedleClass::chrLetterCountArray != NULL)
	{
		delete[] NeedleClass::chrLetterCountArray;
		NeedleClass::chrLetterCountArray = NULL;
	}

	if (NeedleClass::strPermResult != NULL)
	{
		delete[] NeedleClass::strPermResult;
		NeedleClass::strPermResult = NULL;
	}

	if (NeedleClass::strSortedNeedleWord != NULL)
	{
		delete[] NeedleClass::strSortedNeedleWord;
		NeedleClass::strSortedNeedleWord = NULL;
	}*/
}

NeedleClass::NeedleClass(const char * strWord)
{
	// Initialize Needle word

	NeedleClass::intNeedleWordLength = strlen(strWord);
	if (strlen(strWord) > MAX_NEEDLE_WORD)
		throw NEEDLE_TOO_LONG_ERROR;

	// Initialize class member data
	memset(NeedleClass::strNeedleWord, 0, sizeof(NeedleClass::strNeedleWord));
	strcpy(NeedleClass::strNeedleWord, strWord);

	// Sort Needle Characters
	NeedleClass::SortCharacters();

	// Count number of different letters in Needle
	memset(NeedleClass::intLetterCountArray, 0, sizeof(NeedleClass::intLetterCountArray));
	memset(NeedleClass::chrLetterCountArray, 0, sizeof(NeedleClass::chrLetterCountArray));

	// Count number of different letters in Needle
	NeedleClass::CountLetters();
	intCountingStringLevel  = NeedleClass::intStringLevel;

	// Determine denominator for no. of permutations calculations:
	// NOTE: Maybe needed if permutations placed into memory data structure rather than text file.
	// (length of Phrase!)/((counts of character n)! x (counts of character n+1)! x (counts of character n+2)! . .  .) 
	NeedleClass::DetermineNumberOfPermutations();

	// Create output file where determined sorted permutations are stored for future use
	CreatePermutationsOutfile();

	// intCountintStringLevel - maximum level of tree (from root to end of branch, length of string)
	// level - used when recursive calling nature of algorithm heads towards branch (until level == intCountintStringLevel)
	// Results are written directly into the Permutations file	
	int intLevel = 0;
	memset(NeedleClass::strPermResult, 0, sizeof(NeedleClass::strPermResult));
	memset(strResults, 0, sizeof(strResults));

	char chrTempStr[MAX_LETTERS] = { 0 };
	int intTempCount[MAX_LETTERS] = { 0 };

	for (int i = 0; i < intCharCount; i++)
	{
		chrTempStr[i] = chrLetterCountArray[i];
		intTempCount[i] = intLetterCountArray[i];
	}

	CalculatePermutations(chrTempStr, intCharCount, intTempCount, strResults, intLevel, intCountingStringLevel);

	// Close File
	ClosePermutationsFile();
}

int NeedleClass::intGetNeedleWordLength()
{
	return NeedleClass::intNeedleWordLength;
}

void NeedleClass::SortCharacters()
{
	//Sort Phrase characters
	memset(NeedleClass::strSortedNeedleWord, 0, sizeof(NeedleClass::strSortedNeedleWord));
	for (int i = 0; i < NeedleClass::intNeedleWordLength + 1; i++)
	{
		NeedleClass::strSortedNeedleWord[i] = 0;
	}

	// Bubble Sort on strNeedleWord
	strcpy(NeedleClass::strSortedNeedleWord, NeedleClass::strNeedleWord);
	char chrTemp = 0;

	for (int i = 1; i < NeedleClass::intNeedleWordLength; i++)
	{
		for (int j = 0; j < NeedleClass::intNeedleWordLength - 1; j++)
		{
			if ((tolower(NeedleClass::strSortedNeedleWord[j]) >= 'a') && (tolower(NeedleClass::strSortedNeedleWord[j]) <= 'z'))
			{
				if (tolower(NeedleClass::strSortedNeedleWord[j]) > tolower(NeedleClass::strSortedNeedleWord[j + 1]))
				{
					chrTemp = tolower(NeedleClass::strSortedNeedleWord[j]);
					NeedleClass::strSortedNeedleWord[j] = tolower(NeedleClass::strSortedNeedleWord[j + 1]);
					NeedleClass::strSortedNeedleWord[j + 1] = chrTemp;
				}
			}
		}
	}
}

void NeedleClass::CountLetters()
{
	int intPermIndex = 0;
	NeedleClass::intStringLevel = 0;
	intCharCount = 0;

	for (int i = 0; i < NeedleClass::intNeedleWordLength; i++)
	{
		if ((tolower(NeedleClass::strSortedNeedleWord[i]) >= 'a') && (tolower(NeedleClass::strSortedNeedleWord[i]) <= 'z'))
		{
			if ((intPermIndex == 0) && (NeedleClass::chrLetterCountArray[0]) == 0)
			{
				NeedleClass::chrLetterCountArray[0] = tolower(NeedleClass::strSortedNeedleWord[i]);
				NeedleClass::intLetterCountArray[0] = 1;
				NeedleClass::intStringLevel = 1;
				intCharCount = 1;
			}
			else
			{
				if (tolower(NeedleClass::strSortedNeedleWord[i]) > NeedleClass::chrLetterCountArray[intPermIndex])
				{
					intPermIndex++;
					NeedleClass::chrLetterCountArray[intPermIndex] = tolower(NeedleClass::strSortedNeedleWord[i]);
					NeedleClass::intLetterCountArray[intPermIndex] = 1;
					NeedleClass::intStringLevel++;
					intCharCount++;
				}
				else if (tolower(NeedleClass::strSortedNeedleWord[i]) == NeedleClass::chrLetterCountArray[intPermIndex])
				{
					NeedleClass::intLetterCountArray[intPermIndex] = NeedleClass::intLetterCountArray[intPermIndex] + 1;
					NeedleClass::intStringLevel++;
				}
			}
		}
	}
}

void NeedleClass::DetermineNumberOfPermutations()
{
	unsigned long int uliPermutationDenominator = 1;
	for (int i = 0; i < intCharCount; i++)
	{
		uliPermutationDenominator = uliPermutationDenominator * (unsigned long int)Factorial(NeedleClass::intLetterCountArray[i]);
	}

	NeedleClass::uliNumberOfPermutations = (unsigned long int)Factorial(NeedleClass::intNeedleWordLength) / uliPermutationDenominator;
}

void NeedleClass::CreatePermutationsOutfile()
{
	// Create output file where determined sorted permutations are stored for future use
	ofsPermutations.open("permutations.txt");
	if (!ofsPermutations)
	{
		std::cout << "ERROR: Cannot make permutations file" << std::endl;
		throw NEEDLE_PERM_FILE_ERROR;
	}
}

void NeedleClass::ClosePermutationsFile()
{
	ofsPermutations.close();
}

//void NeedleClass::CalculatePermutations(char strPermResult[], int intLevel)
void 	NeedleClass::CalculatePermutations(char s[], int intStringLevel, int intCount[], char res[], int lev, const int intStringIndexze)
{

	int i = 0;
	if (lev == intStringIndexze)
	{
		//std::cout << "Permutation:\t" << res << std::endl;
		ofsPermutations << res << std::endl;
		return;
	}

	// Go through each letter found in string (looking through intCount
	while (i < intStringLevel)
	{
		// Handle letters that have been duplicated with their intCount value
		if (intCount[i] != 0)
		{
			res[lev] = s[i];
			//std::cout << "RES: " << res[lev] << " LEV:" << lev << " i: " << i << std::endl;
			intCount[i]--;
			CalculatePermutations(s, intStringLevel, intCount, res, (lev + 1), intStringIndexze);
			intCount[i]++;
		}
		i++;
	}

}

