#pragma once

#include <iostream>
#include <fstream>

#define MAXWORD 30
#define MAXALPHA 26

class MakeBinaryFile
{
private:
	std::ifstream  ifsTextInFile;
	std::ofstream ofsBinaryOutFile;

	char strTextInFilePath[MAXWORD] = { 0 };
	char strBinaryOutFilePath[MAXWORD] = { 0 };


public:
	MakeBinaryFile(char *strTextInFilePath, char *strBinaryOutFilePath);

	~MakeBinaryFile();

	bool OpenInputTextFile();

	bool OpenOutputBinaryFile();

	void CopyTextFileToBinaryFile();

	void CloseInputTextFile();

	void CloseOutputBinaryFile();
};

