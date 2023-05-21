#define _CRT_SECURE_NO_WARNINGS
#include "RBT.h"
#include <iostream>
RBT::RBT()
{
	
	Tnil->color = "BLACK";
	strcpy(Tnil->word, "");//Tnil->word = "";
	Tnil->parent = Tnil->rkid = Tnil->lkid = Tnil;
	root = Tnil;
}

RBT::~RBT()
{
}

void RBT::Insert(char word[50])
{
	node* lead = root;	// X or lead searches for the insertion point in the tree 
	node* lag = Tnil; // Y or lag, lags behind lead and is leads parent
	
	while (lead != Tnil)
	{
		lag = lead;
		if (strcmp(word, lead->word) == 0) //(word == lead->word
		{

			comparisons++;
			lead->count++;
			return;
		}
		else if (strcmp(word, lead->word) < 0)
		{
			comparisons++;
			lead = lead->lkid; //word < lead->word
		}
		else
		{
			comparisons++;
			lead = lead->rkid;
		}

	}
	node* nodetoAdd = new node;
	strcpy(nodetoAdd->word, word);//nodetoAdd->word = word;
	nodetoAdd->parent = lag;
	
	nodePointerChanges++;
	if (lag == Tnil)
	{
		root = nodetoAdd;
	}
	else if (strcmp(word, lag->word) < 0) //word < lag->word
	{
		comparisons++;
		lag->lkid = nodetoAdd;
		nodePointerChanges++;
	}
	else
	{
		comparisons++;
		lag->rkid = nodetoAdd;
		nodePointerChanges++;
	}
	nodetoAdd->lkid = nodetoAdd->rkid = Tnil;
	nodePointerChanges++; nodePointerChanges++;
	nodetoAdd->color = "RED";
	colorChanges++;
	while (nodetoAdd->parent->color == "RED")
	{
		if (nodetoAdd->parent == nodetoAdd->parent->parent->lkid)
		{
			lag = nodetoAdd->parent->parent->rkid;
			if (lag->color == "RED")		//Case 1
			{
				nodetoAdd->parent->color = "BLACK";
				colorChanges++;
				lag->color = "BLACK";
				colorChanges++;
				nodetoAdd->parent->parent->color = "RED";
				colorChanges++;
				nodetoAdd = nodetoAdd->parent->parent;
				nodePointerChanges++;
			}
			else 
			{
				if (nodetoAdd == nodetoAdd->parent->rkid)
				{
					nodetoAdd = nodetoAdd->parent;				// Case2
					nodePointerChanges++;
					leftRotate(nodetoAdd);						// Case2
				}
				nodetoAdd->parent->color = "BLACK";			//case 3
				colorChanges++;
				nodetoAdd->parent->parent->color = "RED";
				colorChanges++;
				rightRotate(nodetoAdd->parent->parent);
				
			}
			
			
		}
		else
		{
			lag = nodetoAdd->parent->parent->lkid;
			if (lag->color == "RED")
			{
				nodetoAdd->parent->color = "BLACK";
				colorChanges++;
				lag->color = "BLACK";
				colorChanges++;
				nodetoAdd->parent->parent->color = "RED";
				colorChanges++;
				nodetoAdd = nodetoAdd->parent->parent;
				nodePointerChanges++;
			}
			else
			{
				if (nodetoAdd == nodetoAdd->parent->lkid)
				{
					nodetoAdd = nodetoAdd->parent;				// Case2
					nodePointerChanges++;
					rightRotate(nodetoAdd);						// Case2
				}
				nodetoAdd->parent->color = "BLACK";
				colorChanges++;
				nodetoAdd->parent->parent->color = "RED";	//case 3
				colorChanges++;
				leftRotate(nodetoAdd->parent->parent);
			}

		}
	}
	root->color = "BLACK";
	colorChanges++;
	
}
void RBT::leftRotate(node* nodeToRotate)
{
	leftRotations++;
	node* Y = nodeToRotate->rkid; //Y is x's right (Non nil) child 
	nodeToRotate->rkid = Y->lkid; // moves Y's left subtree into x's right subtree
	nodePointerChanges++;
	if (Y->lkid != Tnil) 
	{
		Y->lkid->parent = nodeToRotate;
		nodePointerChanges++;
	}
		
	Y->parent = nodeToRotate->parent; //Links nodeToRotate's parent to Y
	nodePointerChanges++;
	if (nodeToRotate->parent == Tnil) // if NTR doesnt have a parent that it becomes the new root 
	{
		root = Y;					  // if it does have a parent than Y replaces NTR and NTR gets placed on Y's left 

	}
	else if (nodeToRotate == nodeToRotate->parent->lkid) // which makes Y NTR's parent 
	{
		nodeToRotate->parent->lkid = Y;
		nodePointerChanges++;
	}
	else
	{
		nodeToRotate->parent->rkid = Y;
		nodePointerChanges++;
	}
		
	Y->lkid = nodeToRotate;
	nodePointerChanges++;
	nodeToRotate->parent = Y;
	nodePointerChanges++;
}
void RBT::rightRotate(node* nodeToRotate) // leftRotate method with all "lkid"s replaced with "rkid"s and vice versa
{
	rightRotations++;
	node* Y = nodeToRotate->lkid; 
	nodeToRotate->lkid = Y->rkid; 
	nodePointerChanges++;
	if (Y->rkid != Tnil)
	{
		Y->rkid->parent = nodeToRotate;
		nodePointerChanges++;
	}
	Y->parent = nodeToRotate->parent;
	nodePointerChanges++;
	if (nodeToRotate->parent == Tnil)
	{
		root = Y;
	}
	else if (nodeToRotate == nodeToRotate->parent->rkid)
	{
		nodeToRotate->parent->rkid = Y;
		nodePointerChanges++;
	}
	else
	{
		nodeToRotate->parent->lkid = Y;
		nodePointerChanges++;
	}
	Y->rkid = nodeToRotate;
	nodePointerChanges++;
	nodeToRotate->parent = Y;
	nodePointerChanges++;
}

int RBT::TreeHeight()
{
	return TreeHeightFinder(root);
}

void RBT::wordCounter(node* rootptr)
{
	if (rootptr->lkid != Tnil) wordCounter(rootptr->lkid);
	distinctWords++;
	totalWords = totalWords + rootptr->count;
	if (rootptr->rkid != Tnil) wordCounter(rootptr->rkid);
}

void RBT::displayStatistics()
{
	wordCounter(root);
	cout << "\nThe total number of Distinct Words in the RBT tree is: " << distinctWords
		<< "\nThe total number of Words in the RBT tree is: " << totalWords
		<< "\nThe total number of Comparison made for the RBT tree is: " << comparisons
		<< "\nThe total numer of Node Pointer changes for the RBT tree is: " << nodePointerChanges
		<< "\nThe total number of Color changes in the RBT tree is: " << colorChanges
		<< "\nThe total number of Left Rotations Used for the RBT tree is: " << leftRotations
		<< "\nThe total number of Right Rotations Used for the RBT tree is: " << rightRotations
		<< "\nThe height of the RBT is: " << TreeHeight() << endl;
}

int RBT::TreeHeightFinder(node* rootptr)
{
	if (rootptr == Tnil)
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