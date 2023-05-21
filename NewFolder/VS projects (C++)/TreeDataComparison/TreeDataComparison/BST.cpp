#define _CRT_SECURE_NO_WARNINGS
#include "BST.h"
#include <iostream>
BST::BST()
{
}

BST::~BST()
{
}

void BST::Insert(char word[50]) //Insert command that takes in the user word and either increases the count if the node is already present or makes a new node that gets inserted to the left or right
								// depending on its value on the ASCII table, mostly taken from the insert method in the slides.
{
	node* leadtemp = root;
	node* Lagtemp = NULL;
	node* nodetoinsert = new node();
	
	if (root == NULL) {
		node* newroot = new node();
		strcpy(newroot->word, word);//newroot->word = word;
		root = newroot;
	}
	else {
		while (leadtemp != NULL)
		{
			Lagtemp = leadtemp;
			if (strcmp(word,leadtemp->word) > 0 ) { //word > leadtemp->word
				comparisons++;
				leadtemp = leadtemp->rkid;
			}
			else {
				comparisons++;
				leadtemp = leadtemp->lkid;
			}
			if (strcmp(Lagtemp->word,word) == 0) {
				comparisons++;
			
				Lagtemp->count++;
				return ;
			}

		}
		if (strcmp(word, Lagtemp->word) > 0) { //word > Lagtemp->word
			comparisons++;

			Lagtemp->rkid = nodetoinsert;				
			nodePointerChanges++;
			nodetoinsert->parent = Lagtemp;
			nodePointerChanges++;
			strcpy(nodetoinsert->word, word);//nodetoinsert->word = word;

		}
		else
		{

			Lagtemp->lkid = nodetoinsert;
			nodePointerChanges++;
			nodetoinsert->parent = Lagtemp;
			nodePointerChanges++;
			strcpy(nodetoinsert->word, word);//nodetoinsert->word = word;

		}
	}
	return;
}



void BST::wordCounter(node* rootptr)
{
	if (rootptr->lkid != NULL) wordCounter(rootptr->lkid);
	distinctWords++;
	totalWords = totalWords + rootptr->count;
	if (rootptr->rkid != NULL) wordCounter(rootptr->rkid);
}

int BST::TreeHeight()
{
	return TreeHeightFinder(root);
}

void BST::displayStatistics()
{
	wordCounter(root);
	cout << "\nThe total number of Distinct Words in the BST tree is: " << distinctWords
		<< "\nThe total number of Words in the BST tree is: " << totalWords
		<< "\nThe total number of Comparison made for the BST tree is: " << comparisons
		<< "\nThe total numer of Node Pointer changes for the BST tree is: " << nodePointerChanges
		<< "\nThe height of the BST is: " << TreeHeight() << endl;
		
}

int BST::TreeHeightFinder(node* rootptr)
{
	if (rootptr == NULL)
	{
		return -1;
	}
	else
	{// post order traversal that checks both the nodes and the uses the larger one to see which side the tree goes deeper
		int leftHeight = TreeHeightFinder(rootptr->lkid);
		int rightHeight = TreeHeightFinder(rootptr->rkid);
		if (leftHeight > rightHeight) 
		{
			return(leftHeight + 1);
		}
		else
		{
			return(rightHeight + 1);
		}
	}
}