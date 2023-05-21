#include "LinkedList.h"
#include <iostream>

LinkedList::LinkedList()
{
}


LinkedList::~LinkedList()
{
}

void LinkedList::insert(string word)
{
	node* newNode = new node;
	newNode->word = word;
	node* h = head;
	if (h == NULL)
	{
		head = newNode;
		return;
	}
	while (h->next != NULL)
	{
		h = h->next;
		if (h->word == word)
		{
			return;
		}
		
	}
	h->next = newNode;
}

LinkedList LinkedList::Union(LinkedList* LLL, LinkedList*LLR)
{
	node* h = LLR->head;
	
	while (h != NULL)
	{
		LLL->insert(h->word);
		h = h->next;
	}
	LLR->head = NULL;
	return *LLL;
}


int LinkedList::find(LinkedList LL[], int dimesion, string word)
{
	for (int i = 0; i < dimesion; i++)
	{
		node* h = LL[i].head;
		if (h == NULL)
		{
			continue;
		}
		while (h != NULL)
		{
			if (h->word == word)
			{
				return i;
			}
			h = h->next;
		}
	}
	return -1;
}

void LinkedList::display(LinkedList LL)
{
	node* h = LL.head;
	while (h != NULL)
	{
		cout << h->word;
		h = h->next;
	}
}

bool LinkedList::findInLL(LinkedList LL, string word)
{
	node* h = LL.head;
	if (h == NULL)
	{
		return false;
	}
	while (h != NULL)
	{
		if (h->word == word)
		{
			return true;
		}
		h = h->next;
	}
	return false;
}


