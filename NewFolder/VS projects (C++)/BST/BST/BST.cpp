#include "BST.h"
#include <iostream>

BST::BST()
{
}

BST::~BST() //just calls the private post order recursive method that delete every node in post order before quitting
{
	destroyer(root);
}



string BST::insert(string word) //Insert command that takes in the user word and either increases the count if the node is already present or makes a new node that gets inserted to the left or right
								// depending on its value on the ASCII table, mostly taken from the insert method in the slides.
{
	node* leadtemp = root;
	node* Lagtemp = NULL;
	node* nodetoinsert = new node();
	if (root == NULL) {
		node* newroot = new node();
		newroot->word = word;
		root = newroot;
	}
	else {
		while (leadtemp != NULL)
		{
			Lagtemp = leadtemp;
			if (word > leadtemp->word) {
				leadtemp = leadtemp->rkid;
			}
			else {
				leadtemp = leadtemp->lkid;
			}
			if (Lagtemp->word == word) {
				Lagtemp->count++;
				return (Lagtemp->word + " " + to_string(Lagtemp->count)+ "\n");
			}
			
		}
		if (word > Lagtemp->word) {
			Lagtemp->rkid = nodetoinsert;
			nodetoinsert->word = word;
			nodetoinsert->parent = Lagtemp;
		}
		else
		{
			Lagtemp->lkid = nodetoinsert;
			nodetoinsert->parent = Lagtemp;
			nodetoinsert->word = word;

		}
	}
	return(nodetoinsert->word + " " + to_string(nodetoinsert->count)+ "\n");
}

string BST::remove(string word)	// remove method that implements all the 3 cases while removing a node from the tree as well as takes care or reconnecting the nodes back together
								// Used the psuedowriting in the slides(pt2 all the way to the end) to implement the different scenarios
								// This method also uses my UtilHelper method that gets to the node given the string and the root and returns a node pointer to that node.
{
	if (root == NULL)
		return "Set is Empty\n";
	node* toRemove = Utilhelper(root, word);
	if (toRemove->word == word + " not in set")
	{
		return (word + " not in set\n");
	}
	if (toRemove->count > 1) {
		toRemove->count--;
		return (word + " " + to_string(toRemove->count) +"\n");
	}
	if (toRemove->rkid == NULL && toRemove->lkid == NULL) {
		if (toRemove == root) {
			root = NULL;
			
		}
		else {
			if (toRemove->parent->rkid == toRemove) {
				toRemove->parent->rkid = NULL;
				delete toRemove;
			}
			else {
				toRemove->parent->lkid = NULL;
				delete toRemove;
			}
		}
	}
	else if(toRemove->rkid==NULL){
		if (toRemove->parent->rkid == toRemove) {
			toRemove->parent->rkid = toRemove->lkid;
			delete toRemove;
		}
		else {
			toRemove->parent->lkid = toRemove->lkid;
			delete toRemove;
		}

	}
	
	else if (toRemove->lkid == NULL) {
		if (toRemove->parent->rkid == toRemove) {
			toRemove->parent->rkid = toRemove->rkid;
			delete toRemove;
		}
		else {
			toRemove->parent->lkid = toRemove->rkid;
			delete toRemove;
		}
		
	}
	else {
		node* succOfRemove = Utilhelper(root, next(toRemove->word));
		toRemove->word = succOfRemove->word;
		toRemove->count = succOfRemove->count;
		if (succOfRemove == toRemove->rkid) {
			toRemove->rkid = succOfRemove->rkid;
		}
		else {
			succOfRemove->parent->lkid = NULL;
		}
		delete succOfRemove;
	}
	return string(word +" 0\n");
}

string BST::search(string word) // uses my Util Helper method to get to the node in the tree or return a "not in set" string inside the node if the string is not present in the tree
{								// this method returns the word of the node as well as the count of the node

	if (root == NULL) {
		return "Set is Empty\n";
	}
	node* searching = Utilhelper(root, word);
	if (searching->word == word + " not in set\n")
	{
		return (word + " not in set\n");
	}
	string foundit = searching->word + " " + to_string(searching->count) + "\n";
	return string(foundit);
}
	
string BST::min()				// uses the logic given in the slides to get to the min of the BST
{
	node* temp = root;
	if (root == NULL) 
		return "\n";
	while (temp->lkid != NULL) {
		temp = temp->lkid;
	}
	string minword = temp->word;
	return string(minword + " " +to_string(temp->count)+ "\n");
}

string BST::max()			// uses the logic given in the slides to get to the max of the BST 
{
	node* temp = root;
	if (root == NULL)
		return "\n";
	while (temp->rkid != NULL) {
		temp = temp->rkid;
	}
	string maxword = temp->word;
	return string(maxword + " " + to_string(temp->count)+"\n");
}

string BST::next(string word) // also uses the logic given in the slides to find the successor of the string given 
							  // uses the util helper method to get to the node first and then logic from there and returns the word and count or "not in set" or " doesnt have a successsor"
{
	if (root == NULL)
		return "Set Empty\n";
	node* successor = Utilhelper(root, word);
	if (successor->word == word + " not in set")
	{
		return (word + " not in set\n");
	}
	if (successor->rkid != NULL) {
		successor = successor->rkid;
		while (successor->lkid!=NULL)
		{
			successor = successor->lkid;
		}
		return (successor->word);
	}
	
	node* tempsuccessor = successor->parent;
	while (tempsuccessor != NULL && successor == tempsuccessor->rkid && tempsuccessor != root) {
		successor = tempsuccessor;
		tempsuccessor = successor->parent;
	}
	if (tempsuccessor == root)
		return (word + " does not have a successor\n");
	return (tempsuccessor->word);	
}

string BST::prev(string word)	// also uses the logic given in the slides to find the predecessor of the string given
								// uses the util helper method to get to the node first and then logic from there and returns the word and count or "not in set" or " doesnt have a predecessor"
{
	if (root == NULL)
		return "Set Empty \n";
	node* predeccessor = Utilhelper(root, word);
	if (predeccessor->word == word + " not in set")
	{
		return (word + " not in set\n");
	}
	if (predeccessor->lkid != NULL) {
		predeccessor = predeccessor->lkid;
		while (predeccessor->rkid != NULL) {
			predeccessor = predeccessor->rkid;
		}
		return (predeccessor->word + "\n");
	}

	node* temppred = predeccessor->parent;
	while (temppred != NULL && predeccessor == temppred->lkid && temppred != root) {
		predeccessor = temppred;
		temppred = predeccessor->parent;
	}
	if (temppred == root)
		return (word + " does not have a predecessor\n");
	return (temppred->word + to_string(temppred->count)+ "\n");
}

string BST::parent(string word) // uses the util helper method to get to the node given the string and just returns the parents word and count and the other cases if parent is NULl, or word isnt in the set 
{
	
	if (root == NULL) 
		return "Set is Empty";
	
	node* parentfinder = Utilhelper(root, word);
	if (parentfinder->word == word + " not in set")
	{
		return (word + " not in set\n");
	}
	if (parentfinder->parent == NULL) {
		return "NULL";
	}
	parentfinder = parentfinder->parent;
	string foundit = parentfinder->word + " " + to_string(parentfinder->count);
	return string(foundit);
}

string BST::child(string word) // uses same logic as the parent method but returns the child of the node instead of the parent
								// also accounts for the other cases such as if either or both children are null or the word isnt in the set
{
	
	string children;
	if (root == NULL) 
		return "Set is Empty\n";
	
	node* childFinder = Utilhelper(root, word);
	if (childFinder->word == word + " not in set")
	{
		return (word + " not in set\n");
	}
	if (childFinder->lkid == NULL) {
		children += "NULL ";
	}
	else
	{
		children += " " + childFinder->lkid->word + " " + to_string(childFinder->lkid->count)+ " ";
	}
	if (childFinder->rkid != NULL) {
		children += childFinder->rkid->word + " " + to_string(childFinder->rkid->count) + " ";
	}
	else
	{
		children += " NULL";
	} 

	
	return string(children+"\n");
}

void BST::list()	// just reverts to the private search method that recursively traverses the tree in inorder traversal and prints out the nodes word and count 
{
	if (root == NULL) {
		cout << "Set Empty\n" << endl;
	}
	else {
		cout << "[ ";
		privsearch(root);
		cout << "]" << endl;
	}
}

void BST::privsearch(node* rootptr) // private recursive method that calls itself inorder and prints out the word and the count
{
	
	if (rootptr->lkid != NULL)privsearch(rootptr->lkid);
	cout << rootptr->word << " " << rootptr->count << " ";
	if (rootptr->rkid != NULL)privsearch(rootptr->rkid);
	
}

BST::node* BST::Utilhelper(node* rootptr,string word) // gets a string and the root and uses that to get to the node in the tree and returns that node pointer or makes a new node that is returned to the method 
													// with the word set as word + "Not In set" 
{
	node* util = rootptr;
	node* noword = new node();
	
	while (util->word != word) {
		if (word > util->word) {
			if (util->rkid == NULL) {
				noword->word = word + " not in set";
				return (noword);
			}
			util = util->rkid;
		}
		else {
			if (util->lkid == NULL) {
				noword->word = word + " not in set";
				return (noword);
			}
			util = util->lkid;
		}
	}
	return (util);
}

void BST::destroyer(node* rootptr)	// recursive method that traverses the tree in postorder and delete the nodes in that order
{
	if (rootptr->lkid != NULL)destroyer(rootptr->lkid);
	if (rootptr->rkid != NULL)destroyer(rootptr->rkid);
	delete rootptr;
}

