#include<iostream>
#include <algorithm>
#include <string>
#include "BST.h"
using namespace std;

int main() {
	//instantiate the BST object 
	bool userquit = false;
	BST* my_tree = new BST();
	while (userquit != true) {	//Infinite loop untill user quits 
		string userinput, word{};
		cout << "Enter the command you want to use" << endl;
		cin >> userinput;
		for_each(userinput.begin(), userinput.end(), [](char& c) {  //makes user command case insensitive
			c = ::tolower(c);
		});

		if (userinput == "quit") {
			userquit = true;	
			delete my_tree;
		}
		else if(userinput == "help") { // lists all the functions available to the user
			cout << "insert <string> - inserts a string into tree or increments its counter by 1\n"
				<< "delete <string> - deleters a string from the tree or returns null if not present or decrements the counter by 1 \n"
				<< "search <string> - searches the string in the tree and outputs it and its counter\n"
				<< "min - outputs the minimum string in the tree\n"
				<< "max - outputs the maximum string in the tree\n"
				<< "next <string> - outputs the successor of the current string or shoots a blank line if there are no childs\n"
				<< "prev <string> - just like the next function but this one ouputs its predecessor\n"
				<< "list - lists the current items in the tree in ascending order\n"
				<< "parent <string>- outputs the parent string or a blank line if the node doesn't have a parent\n"
				<< "child <string> - outputs the child string or a blank line if the node doesn't have a child\n"
				<< "help - lists all the comands available to the user\n"
				<< "quit - quits the program\n";
		}
		//all the statements below just takes in a word from a user if its needed and then reverts it to the appropriate method
		
		else if(userinput== "insert"){
			cin >> word;
			cout << my_tree->insert(word);
		}
		else if (userinput == "delete") {
			cin >> word;
			cout << my_tree->remove(word);
		}
		else if (userinput == "min") {
			cout << my_tree->min();
		}
		else if (userinput == "max") {
			cout << my_tree->max();
		}
		else if (userinput == "next") {
			cin >> word;
			cout << my_tree->next(word);
		}
		else if (userinput == "prev") {
			cin >> word;
			cout << my_tree->prev(word);
		}
		else if (userinput == "parent") {
			cin >> word;
			cout << my_tree->parent(word);
		}
		else if (userinput == "child") {
			cin >> word;
			cout << my_tree->child(word);
		}
		else if (userinput == "list") {
			my_tree->list();
		}
		else if (userinput == "search") {
			cin >> word;
			cout << my_tree->search(word);
		}
		else {
			cout << "Enter a valid function" << endl;
		}

	}
}
