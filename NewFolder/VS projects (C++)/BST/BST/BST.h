#pragma once

#include <string>
using namespace std;

class BST {
	//all the functions going here except for Help and quit
public:
	BST();
	~BST();
	string insert(string word);
	string remove (string word);
	string search(string word);
	string min();
	string max();
	string next(string word);
	string prev(string word);
	string parent(string word);
	string child(string word);
	void list();
	
private:
	//node struct for the node of a tree, copied from the first lab demo
	struct node {
		string word;
		int count = 1;
		node* lkid = NULL,* rkid = NULL,* parent = NULL;

	};
	node* root = NULL;

	void privsearch(node* rootptr); // private search method which I use to traverse the BST recursively 
	node* Utilhelper(node* rootptr, string word); //a private method i use that uses the word and the root to get to that node in the tree without revealing anything to the user
	void destroyer(node* rootptr); // destroyer method that recursively traverses the tree in postorder and deletes the nodes
};
