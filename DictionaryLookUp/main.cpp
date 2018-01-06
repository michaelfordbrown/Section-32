#include "stdafx.h"

#include "DictionaryLookUp.h"

using namespace std;

int main()
{

	std::ifstream dictionaryInFile;
	int WordFoundArray[26] = { 0 };
	WordList strWordFoundList[MAXALPHA];
	WordList strWordNotFoundList[MAXALPHA];

	std::streampos stoPosition[MAXALPHA] = { 0 };

	OpenDictionaryFile(dictionaryInFile, "dictionary.txt");

	LookForWord(dictionaryInFile, stoPosition, strWordFoundList, strWordNotFoundList, "Michael");
	dictionaryInFile.seekg(0);
	LookForWord(dictionaryInFile, stoPosition, strWordFoundList, strWordNotFoundList, "Aarhus");
	LookForWord(dictionaryInFile, stoPosition, strWordFoundList, strWordNotFoundList, "hello");
	LookForWord(dictionaryInFile, stoPosition, strWordFoundList, strWordNotFoundList, "world");
	dictionaryInFile.seekg(0);
	LookForWord(dictionaryInFile, stoPosition, strWordFoundList, strWordNotFoundList, "Aaron");
	LookForWord(dictionaryInFile, stoPosition, strWordFoundList, strWordNotFoundList, "Qwebet");
	dictionaryInFile.seekg(0);
	LookForWord(dictionaryInFile, stoPosition, strWordFoundList, strWordNotFoundList, "hello");
	LookForWord(dictionaryInFile, stoPosition, strWordFoundList, strWordNotFoundList, "Qwebet");

	std::cout << "\nWords Found List (Note: List for Each First Letter of Word Found)\n";
	std::cout << "List\tAddr\t\tWord\t\tNextAddr\n";
	for (int i = 0; i < MAXALPHA; i++)
	{
		strWordFoundList[i].showlistfromhead();
	}

	std::cout << "\nWords Not Found List(Note: List for Each First Letter of Word Not Found)\n";
	std::cout << "List\tAddr\t\tWord\t\tNextAddr\n";
	for (int i = 0; i < MAXALPHA; i++)
	{
		strWordNotFoundList[i].showlistfromhead();
	}

	dictionaryInFile.close();

	getchar();

	return EXIT_SUCCESS;
}
