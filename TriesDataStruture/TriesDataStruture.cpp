// TriesDataStruture.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <memory>
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

#define LETTERSINALPHA 26

class TrieNode {
public:
	char *children;
	bool endOfWord;
public:
	TrieNode() {
		try {
			children = new char[LETTERSINALPHA];
			memset(children, 0, LETTERSINALPHA);
			endOfWord = false;
		}
		catch (const::bad_alloc& e)
		{
			cout << "Allocation failed (TrieNode): " << e.what() << endl;
		}
	}
	~TrieNode() {
		if (children != NULL)
		{
			delete[]children;
			children = NULL;
		}
	}
};

class Trie:private TrieNode {

	public:

	TrieNode root;

public:

	/*
	void insert(char * word)
	{
		TrieNode current = root;
		for (int i = 0; i < strlen(word); i++) {
			char character = word[i];
			TrieNode node = current.children[i];
			if (node == NULL) {
				node = new TrieNode();

			}
		}
			TrieNode::endOfWord = true;
	}
	*/
};


int main()
{
    return 0;
}

