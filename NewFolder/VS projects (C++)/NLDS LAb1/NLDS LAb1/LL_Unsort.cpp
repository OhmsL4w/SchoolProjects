#include "LL_Unsort.h"
LL_Unsort::LL_Unsort() {
	list = NULL;
	//constructor -makes a node with null. When we construct a "new" lsit, theres IS NO first node!
}

LL_Unsort::~LL_Unsort() {
	node * here = list; //beginning of the list
	node* next;			// this one will let us look one node ahead
	//since c++ doesn't have automatic garbage collection , we have to delete the entire list ourselves 1 node at a tiem.

	//destroying lists consists of doing a traversel and deleting all of the nodes. 
	while (here!= NULL)
	{
		next = here->next;
		delete here;
		here = next;
	}
	//preserving our position in the traversal before deleting the node
	list = NULL;

}

void LL_Unsort::insert(const string word) {
	node *p = list;
	while (p != NULL)
	{
		if (p->word == word) {
			//increasing counter is the word we looking for is already in the list
			p->count++;
			return;
		}
		p = p->next;

	}
	//creating a new node since node is a struct not a class, set count to 1, save word to new node , and the nodes link 
	//will be the current first node on the list and becomes the first node on the list
	node *newNode = new node;
	newNode->count = 1;
	newNode->word = word;
	newNode->next = list;
}

int LL_Unsort::find(string word) {
	
	node* p = list;
		while (p != NULL)
		{
			if (p->word == word) return p->count;
			p = p->next;

		}
		return	0;

}

string LL_Unsort::toString() {
	string result;
	node* p = list;
	if (p == NULL) return "Linked lsit is Empty\n";

	result = "linked list contains:\n";
	while (p != NULL)
	{
		result = result + p->word + " " + to_string(p->count) + "\n";
		p = p->next;
	}
	return result;
}

int LL_Unsort::remove(string word) {
	node* p = list;
	node* q = NULL;
	int newCount;
	while (p != NULL)
	{
		if (p->word == word) {
			newCount = --(p->count);
			if (newCount > 0) return newCount;
			if (q == NULL) list = p->next;
			else			q->next = p->next;
			delete p;
			return newCount;
		}
		q = p;
		p = p->next;
	}
	return -1;
}