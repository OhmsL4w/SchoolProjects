#pragma once
#include <string>
using namespace std;

class LinkedList
{
private:
	struct node
	{
		 string word;
		 node* next = NULL;
	};
	
public:
	node* head = NULL;
	LinkedList();
	~LinkedList();
	void insert(string word);
	LinkedList Union(LinkedList* LLL, LinkedList* LLR);
	int find(LinkedList LL[],int dimension, string word);
	void display(LinkedList LL);
	bool findInLL(LinkedList LL, string word);
};

