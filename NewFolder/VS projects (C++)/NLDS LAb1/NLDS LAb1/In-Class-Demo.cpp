//=========================================================
//LL_demo.cpp - unsort linked list demo

// this program is a friver to demonstrate how classes are implement in c++
// It instantiates an unsorted linked list(implented in a sepreate class) that holds words.
// adds several words to thelist, deletes a few, displates the resulting list, and then destroys what's left of it.

//	Author: Larry Thomas, UNiversity of Toledo 

#include "LL_Unsort.h"
#include <iostream>

using namespace std;

int main() {
	// this program manipulates a linked list, so create one.

	LL_Unsort* myList = new LL_Unsort();

	cout << "------------------------\n";
	cout << myList->toString();

	//Adding some words to the list;
	myList->insert("Cat");
	myList->insert("Dog");
	myList->insert("Cat");
	myList->insert("Zebra");
	myList->insert("Ferret");
	myList->insert("Iguana");
	
	// output the contents of the list again to sow that we have 2 cats, a dog, zebra, ferrret and an iguana
	cout << "--------------------\n";
	cout << myList->toString();

	// gettting rid of iguana
	cout << "\n\nRemoving Iguana\n";
	myList->remove("Iguana");
	cout << "\n\nRemoving Zebra\n";
	myList->remove("Zebra");
	
	//removing Advark\, should return -1 since not in list

	cout << "\n\nRemoving Aardvark\n";
	cout << "the new count for Aardvark is " << myList->remove("Aardvark") << endl;

	cout << "\nAbout to delete ""Dog:""\n";
	cout<< "the new count for Dog is " << myList->remove("Dog") << endl;

	cout << "\n\n----------------\n";
	delete myList;

	return 0;

}