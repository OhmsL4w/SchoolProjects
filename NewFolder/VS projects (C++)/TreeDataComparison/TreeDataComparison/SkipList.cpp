#define _CRT_SECURE_NO_WARNINGS
#include "SkipList.h"
#include <time.h>
#include <iostream> 
SkipList::SkipList()
{
	tail = new node();
	head = new node();
	strcpy(head->word, Neg_Inf);//head->word = Neg_Inf;
	strcpy(tail->word, Pos_Inf);//tail->word = Pos_Inf;
	head->right = tail;
	nodePointerChanges++;
	tail->left = head;
	nodePointerChanges++;
	srand(time(NULL));
	n = 0;
	h = 1;

}

SkipList::~SkipList()
{
}

int SkipList::getListHeight()
{
	return h;
}

SkipList::node* SkipList::search(char word[50]) {
	node* p = head;
	while (true)
	{
		while (strcmp(p->right->word,Pos_Inf) != 0 && strcmp(p->right->word, word) <= 0)  //p->right->word.compare(word) <= 0
		{
			comparisons++;
			p = p->right;
		}

		if (p->down == NULL) return p;
		p = p->down;

	}
}
void SkipList::Insert(char word[50]) {
	node* leftofNTA = search(word);
	if (strcmp(leftofNTA->word, word) == 0) //(leftofNTA->word == word
	{
		comparisons++;
		leftofNTA->value++;
		while (leftofNTA->down != NULL)
		{
			leftofNTA = leftofNTA->down;
			leftofNTA->value++;

		}

		return;
	}
	node* nodeToAdd = new node;
	strcpy(nodeToAdd->word, word);//nodeToAdd->word = word;

	nodeToAdd->right = leftofNTA->right;
	nodePointerChanges++;
	nodeToAdd->left = leftofNTA;
	nodePointerChanges++;
	leftofNTA->right->left = nodeToAdd;
	nodePointerChanges++;
	leftofNTA->right = nodeToAdd;
	nodePointerChanges++;
	node* lanefinder = nodeToAdd;
	bool coinTossed = false;

	while ((rand() & 1) == 0)
	{
		headsFlipped++;
		coinTossed = true;
		while (lanefinder->up == NULL)
		{

			if (lanefinder == head)
			{
				node* newHead = new node;
				strcpy(newHead->word, Neg_Inf);//newHead->word = Neg_Inf;
				node* newTail = new node;
				strcpy(newTail->word, Pos_Inf);//newTail->word = Pos_Inf;
				newHead->down = head;
				nodePointerChanges++;
				head->up = newHead;
				nodePointerChanges++;
				newTail->down = tail;
				nodePointerChanges++;
				tail->up = newTail;
				nodePointerChanges++;
				head = newHead;
				tail = newTail;
				head->right = tail;
				nodePointerChanges++;
				tail->left = newHead;
				nodePointerChanges++;
				
				lanefinder = head;
				h++;
				break;
			}
			lanefinder = lanefinder->left;
		}
		if (lanefinder != head)
		{
			lanefinder = lanefinder->up;

		}
		node* newNodeOnEXP = new node;
		strcpy(newNodeOnEXP->word, word);//newNodeOnEXP->word = word;
		addedNodeToFastLane++;
		lanefinder->right->left = newNodeOnEXP;
		nodePointerChanges++;
		newNodeOnEXP->right = lanefinder->right;
		nodePointerChanges++;
		lanefinder->right = newNodeOnEXP;
		nodePointerChanges++;
		newNodeOnEXP->left = lanefinder;
		nodePointerChanges++;
		newNodeOnEXP->down = nodeToAdd;
		nodePointerChanges++;
		nodeToAdd->up = newNodeOnEXP;
		nodePointerChanges++;
		nodeToAdd = nodeToAdd->up;

	}
	if (coinTossed == false)
	{
		tailsFlipped++;
	}
	return;
}
void SkipList::wordCounter(node* head)
{
	node* A, * B; // A travels the bottom most lane gathering all the nodes while b travels upwards if the node->up != NULL
	A = head;
	B = A;
	while (A->down != NULL)
	{
		A = A->down;
	}
	while (strcmp(A->right->word, Pos_Inf) != 0)
	{
		A = A->right;
		B = A;
		if (A->up == NULL)
		{
			totalNodes++;
			totalNodesatBottom++;
			distinctWords++;
			totalWords = totalWords + A->value;
		}
		else
		{
			distinctWords++;
			totalNodesatBottom++;
			totalWords = totalWords + A->value;
			while (B->up != NULL)
			{
				totalNodes++;
				B = B->up;
			}
		}
	}
}

void SkipList::displayStatistics()
{
	wordCounter(head);
	cout << "\nThe total number of Distinct Words in the Skip List is: " << distinctWords
		<< "\nThe total number of Words in the Skip List is: " << totalWords
		<< "\nThe total number of Comparison made for the Skip List is: " << comparisons
		<< "\nThe total numer of Node Pointer changes for the Skip List is: " << nodePointerChanges
		<< "\nThe total number of Heads Flipped in the Skip List is: " << headsFlipped
		<< "\nThe total number of Tails Flipped in the Skip List is: " << tailsFlipped
		<< "\nThe total number of times a node was added to the fast lane in the Skip List is: " << addedNodeToFastLane
		<< "\nThe total number of nodes on the bottom most lane is: " << totalNodesatBottom
		<< "\nThe total number of nodes in the Skip list is: " << totalNodes
		<< "\nThe height of the Skip List is: " << getListHeight() << endl;
}

