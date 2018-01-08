#pragma once

#include <iostream>
#include <fstream>

#include "WordListClass.h"

#define LETTERSINALPHA 26 
#define HAYSTACK_FILE_ERROR 10

class HayStackClass
{
private:
	std::ifstream ifsHayStack;
	std::streampos stpHayStackFilePos;
	WordListClass wlcHayThreadListArray[26];

public:
	HayStackClass(char* strFileName);
	~HayStackClass();

	void HayStackClass::blnCloseHayStackFile();
	bool blnCheckHayStackFile(const char* strNeedle);
	void LookForNeedleInHayStack(const char *strNeedle);
};

