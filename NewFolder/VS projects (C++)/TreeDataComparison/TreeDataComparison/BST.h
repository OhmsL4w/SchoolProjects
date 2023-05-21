#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<string>
using namespace std;
class BST
{
public:
	BST();
	~BST();
	void Insert(char word[50]); // insert method used from BST project
	int TreeHeight();
	void displayStatistics();

private:
	struct node {			// node struct used from BST project
		char word[50];
		int count = 1;
		node* lkid = NULL, * rkid = NULL, * parent = NULL;
	};
	node* root = NULL;
	unsigned long long comparisons = 0, totalWords = 0, distinctWords = 0 , nodePointerChanges = 0; // variables to gather data for this project
	int TreeHeightFinder(node* rootptr);
	
	void wordCounter(node* rootptr);
};



