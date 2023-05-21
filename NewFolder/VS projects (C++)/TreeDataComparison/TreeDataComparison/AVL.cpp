#define _CRT_SECURE_NO_WARNINGS
#include "AVL.h"
#include <iostream>

AVL::AVL()
{
}

AVL::~AVL()
{
}

void AVL::Insert(char word[50])
{
	
	node* nodeToAdd;            
   	node* A, * F, * P, *B , * Q;
	node* C, * CL, * CR;
	int BFA;
	if (root == NULL) {
		nodeToAdd = new node;
		strcpy(nodeToAdd->word, word);//nodeToAdd->word = word;
		nodeToAdd->lkid = nodeToAdd->rkid = NULL; 
		nodeToAdd->balanceFactor = 0;
		root = nodeToAdd;

		return;
	}
	F= Q = NULL;
	A = P = root;
	while (P != NULL)
	{
		if (strcmp(word, P->word) == 0)//word == P->word
		{ // already here increment the count of the node and return
			comparisons++;
			P->count++;
			return;
		}
		if (P->balanceFactor != 0)
		{
			A = P;
			F = Q;
		}
		if (strcmp(word, P->word) < 0 )//(word < P->word)
		{
			comparisons++;
			Q = P;
			P = P->lkid;
		}
		else
		{
			comparisons++;
			Q = P;
			P = P->rkid;
		}
	}
	nodeToAdd = new node;
	strcpy(nodeToAdd->word, word);//nodeToAdd->word = word;
	nodeToAdd->rkid = nodeToAdd->lkid = NULL;
	nodePointerChanges++; nodePointerChanges++;
	nodeToAdd->balanceFactor = 0;
	
	if (strcmp(word, Q->word) < 0)
	{
		comparisons++;
		Q->lkid = nodeToAdd;
		nodePointerChanges++;
	}//word < Q->word
	else
	{
		comparisons++;
		Q->rkid = nodeToAdd;
		nodePointerChanges++;
	}
	if (strcmp(word, A->word) > 0)//word > A->word
	{
		comparisons++;
		B = P = A->rkid;
		BFA = -1;
		BFchanges++;
	}
	else
	{
		comparisons++;
		B = P = A->lkid;
		BFA = +1;
		BFchanges++;
	}
	while (P != nodeToAdd)
	{
		if (strcmp(word, P->word) > 0)//word > P->word
		{
			comparisons++;
			P->balanceFactor = -1;
			BFchanges++;
			P = P->rkid;
		}
		else {
			comparisons++;
			P->balanceFactor = +1;
			BFchanges++;
			P = P->lkid;
		}
	}
	if (A->balanceFactor == 0)
	{
		A->balanceFactor = BFA;
		BFchanges++;
		return;
	}
	if (A->balanceFactor == -BFA)
	{
		A->balanceFactor = 0;
		BFchanges++;
		return;
	}
	if (BFA == 1)
	{
		if (B->balanceFactor == 1) 
		{ // LR Roatation
			rotationsUsed++;
			A->lkid = B->rkid;
			B->rkid = A;
			nodePointerChanges++; nodePointerChanges++;
			A->balanceFactor = B->balanceFactor = 0;
			BFchanges++; BFchanges++;
			
		}
		else
		{
			rotationsUsed++;
			C = B->rkid;
			CL = C->lkid;
			CR = C->rkid;
			B->rkid = C->lkid;
			nodePointerChanges++;
			A->lkid = C->rkid;
			nodePointerChanges++;
			C->rkid = A;
			nodePointerChanges++;
			C->lkid = B;
			nodePointerChanges++;
			switch (C->balanceFactor)
			{
			case 0:
				A->balanceFactor = 0;
				BFchanges++;
				B->balanceFactor = 0;
				BFchanges++;
				break;

			case 1:
				A->balanceFactor = -1;
				BFchanges++;
				B->balanceFactor = 0;
				BFchanges++;
				break;

			case -1:
				A->balanceFactor = 0;
				BFchanges++;
				B->balanceFactor = 1;
				BFchanges++;
				break;
			}
			C->balanceFactor = 0;
			BFchanges++;
			B = C;
			
		}

	}
	else 
	{			//RL Rotation
		if (B->balanceFactor == -1)
		{
			rotationsUsed++;
			A->rkid = B->lkid;
			nodePointerChanges++;
			B->lkid = A;
			nodePointerChanges++;
			A->balanceFactor = B->balanceFactor = 0;
			BFchanges++; BFchanges++;
		}
		else {
			rotationsUsed++;
			C = B->lkid;
			CL = C->lkid;
			CR = C->rkid;
			B->lkid = C->rkid;
			nodePointerChanges++;
			A->rkid = C->lkid;
			nodePointerChanges++;
			C->lkid = A;
			nodePointerChanges++;
			C->rkid = B;
			nodePointerChanges++;
			switch (C->balanceFactor)
			{
			case 0:
				A->balanceFactor = 0;
				BFchanges++;
				B->balanceFactor = 0;
				BFchanges++;
				break;

			case -1:
				A->balanceFactor = +1;
				BFchanges++;
				B->balanceFactor = 0;
				BFchanges++;
				break;

			case 1:
				A->balanceFactor = 0;
				BFchanges++;
				B->balanceFactor = -1;
				BFchanges++;
				break;
			}
			C->balanceFactor = 0;
			BFchanges++;
			B = C;
		}
	}
	if (F == NULL)
	{
		root = B;
		return;
	}
	if (A == F->lkid)
	{
		F->lkid = B;
		nodePointerChanges++;
		return;
	}
	if (A == F->rkid)
	{
		F->rkid = B;
		nodePointerChanges++;
		return;
	}
	return;
}
int AVL::TreeHeight()
{
	return TreeHeightFinder(root);
}
void AVL::wordCounter(node* rootptr)
{
	if (rootptr->lkid != NULL) wordCounter(rootptr->lkid);
	distinctWords++;
	totalWords = totalWords + rootptr->count;
	if (rootptr->rkid != NULL) wordCounter(rootptr->rkid);
}

void AVL::displayStatistics()
{
	wordCounter(root);
	cout << "\nThe total number of Distinct Words in the AVL tree is: " << distinctWords
		<< "\nThe total number of Words in the AVL tree is: " << totalWords
		<< "\nThe total number of Comparison made for the AVL tree is: " << comparisons
		<< "\nThe total numer of Node Pointer changes for the AVL tree is: " << nodePointerChanges
		<< "\nThe total number of Balance Factor changes in the AVL tree is: " << BFchanges
		<< "\nThe total number of Rotations Used for the AVL tree is: " << rotationsUsed 
		<< "\nThe height of the AVL Tree is: " << TreeHeight() << endl;
}

int AVL::TreeHeightFinder(node* rootptr)
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