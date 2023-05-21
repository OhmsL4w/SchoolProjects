#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <string>
using namespace std;

class RBT
{
public:
	RBT();
	~RBT();
	void Insert(char word[50]);
	int TreeHeight();
	void displayStatistics();

private:
	struct node
	{
		char word[50];
		int count = 1;
		string color;
		node* lkid = NULL, * rkid = NULL, *parent = NULL;
	};
	unsigned long long comparisons = 0, distinctWords = 0, totalWords = 0, nodePointerChanges = 0,
		colorChanges = 0, leftRotations = 0, rightRotations = 0;
	node* root = NULL;
	node* Tnil = new node();
	void wordCounter(node* head);
	int TreeHeightFinder(node* rootptr);
	void leftRotate(node* nodeToRotate);
	void rightRotate(node* nodeToRotate);
};