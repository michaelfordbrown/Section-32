#pragma once

#define MAXWORD 60 // Limited to Word length

class WordListClass
{
private:

	struct Node
	{
		// Found and Not Found words
		char word[MAXWORD] = { 0 };
		// Location of Found word in HayStack (Dictionary)
		int intIndex = 0;
		Node* nodNext;
	};

	Node* nodHead;
	Node* nodTail;
	Node *nodIndex;
	
public:
	WordListClass();
	~WordListClass();

	void AddNode(char* word);
	void ShowListFromHead();
	bool blnSearchListFromHead(char* strWord);

};
