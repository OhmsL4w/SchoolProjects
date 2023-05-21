//LL_Unsort.h

// Header file for the unsorted linked list class LL_Unsort
//
//Author: Larry Thomas, University of Toledo 
// Date: August 30,2021

// The unsorted linked list class supports isnert, remove and find operations in addition to toStri
#pragma once
#include <string>

using namespace std;

class LL_Unsort {
public:
	LL_Unsort();
	~LL_Unsort();
	 
	void insert(const string word);
	int remove(const string word);
	int find(const string word);
	string toString();
	
private:
	//the linked list nodes are maintained as structs (rather than creating a class just for them)
	struct node
	{
		string word;		//A node consists of a node, an integer that maintains a count of how many times we've seen the word
		int count = 1;		// and a linkt to the next nod. when we create a NEW node, that link defaults to NULL;
		node* next = NULL;

	};
	node * list = NULL; // the variable "List" refers to the first node in the list (we start with NO nodes)
};