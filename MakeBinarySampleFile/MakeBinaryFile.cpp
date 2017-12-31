#include "stdafx.h"
#include "MakeBinaryFile.h"


MakeBinaryFile::MakeBinaryFile(char *strInFile, char *strOutFile)
{
	strcpy(strTextInFilePath, strInFile);
	strcpy(strBinaryOutFilePath, strOutFile);

	OpenInputTextFile();
	OpenOutputBinaryFile();

	CopyTextFileToBinaryFile();

	CloseInputTextFile();
	CloseOutputBinaryFile();
}


MakeBinaryFile::~MakeBinaryFile()
{
}

bool MakeBinaryFile::OpenInputTextFile()
{
	// Open text file for input, start reading at the beginning
	ifsTextInFile.open(strTextInFilePath, std::ios_base::in);

	if (!ifsTextInFile)
	{
		std::cout << strTextInFilePath << " text file failed to open!" << std::endl;
		getchar();

		return false;
	}

	return true;
}

bool MakeBinaryFile::OpenOutputBinaryFile()
{
	// Open binary file for output, deleting all existing data (truncate)
	ofsBinaryOutFile.open(strBinaryOutFilePath, std::ios_base::binary | std::ios_base::trunc);

	if (!ofsBinaryOutFile)
	{
		std::cout << strBinaryOutFilePath << " binary file failed to open!" << std::endl;
		getchar();

		return false;
	}

	return true;
}

void MakeBinaryFile::CloseInputTextFile()
{
	ifsTextInFile.close();
}

void MakeBinaryFile::CloseOutputBinaryFile()
{
	ofsBinaryOutFile.close();
}

void MakeBinaryFile::CopyTextFileToBinaryFile() 
{
	char chrInChar;

	while (!ifsTextInFile.eof())
	{
		ifsTextInFile.get(chrInChar);

		std::cout << chrInChar;

		ofsBinaryOutFile << chrInChar;

	}
}
