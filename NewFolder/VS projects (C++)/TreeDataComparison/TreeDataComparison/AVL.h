#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <string>
using namespace std;

class AVL
{
public:
	AVL();
	~AVL();
	void Insert(char word[50]);
	int TreeHeight(); // pulic tree height method that redirects to the private tree height finder
	void displayStatistics();
private:
	struct node
	{
		char word[50];
		int count = 1;
		int balanceFactor = 1;
		node* lkid = NULL, * rkid = NULL;
	};
	unsigned long long comparisons = 0, distinctWords = 0, totalWords = 0, nodePointerChanges = 0, BFchanges = 0, rotationsUsed = 0; // all the variables to get the data for the project
	int TreeHeightFinder(node* rootptr); // private method to find the height of the tree using a recursion
	void wordCounter(node* rootptr);
	node* root = NULL;
};

