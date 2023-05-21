#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <string>
using namespace std;

class SkipList
{
public:
	SkipList();
	~SkipList();
	void Insert(char word[50]);
	int getListHeight();
	void displayStatistics();
	
private:
	struct node
	{
		char word[50];
		int value = 1;
		node* up = NULL, * down = NULL, * left = NULL, * right = NULL;
	};
	unsigned long long comparisons = 0, distinctWords = 0, totalWords = 0,
		nodePointerChanges = 0, headsFlipped = 0, tailsFlipped = 0, addedNodeToFastLane = 0,
		totalNodes = 0, totalNodesatBottom = 0;
	const char Neg_Inf[50] = "negInf"; // head node which we will never attempt to insert anything
	const char Pos_Inf[50] = "posInf"; // tail node which we will never attempt to insert anything
	node* head, * tail;
	int h;
	int n;
	void wordCounter(node* head);
	node* search(char word[50]);
};

