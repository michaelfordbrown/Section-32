#pragma once

#include <iostream>
#include <fstream>

#include "WordListClass.h"

#define LETTERSINALPHA 26 // Number of letters in the Alphabet
#define FILE_ERROR 10

class HayStackClass
{
private:
	std::ifstream ifsHayStack;
	std::streampos stpHayStackFilePos;
	WordListClass wlcHayThreadListArray[LETTERSINALPHA];

public:
	HayStackClass(char* strFileName);
	~HayStackClass();

	void HayStackClass::blnCloseHayStackFile();
	bool blnCheckHayStackFile(char* strNeedle);
	void LookForNeedleInHayStack(char *strNeedle);
};

