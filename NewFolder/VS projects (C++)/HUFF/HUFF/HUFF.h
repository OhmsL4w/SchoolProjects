// Huff.h file
// Date: 10/10/21
// Course: EECS 2510
// Author: Ohm Rathod
// Description: all the methods that are to be implemented in huff.cpp file and 
// struct for the node.

#pragma once
#include <string>

using namespace std;
class Huffman {
public:
	Huffman();													// generic constructor
	~Huffman();													// and destructor
	void MakeTreeBuilder(string inputFile, string outputFile);	// Uses the input and the ouput file name and makes a tree and puts that tree as a result of the file into the outputfile
	void EncodeFile(string inputFile, string outputFile);		// function that takes it the input and the ouput file names and encodes the input file and puts the encoded info in the output file
	void DecodeFile(string inputFile, string outputFile);		// uses the encoded inputfile and the output filename to decode and puts the result into the output file
	void EncodeFileWithTree(string inputFile, string treeFile, string outputFile);	//encodes the input file with a tree file and puts the encoded info into the ouputfile
	void DisplayHelp();											// Displays all the functions available to use to the User;


private:
	struct node
	{
		unsigned  char symbol = {};
		int weight = {};
		node* lch = NULL, * rch = NULL;
	};
	int nodePairs[510] = {};									//array to store the pairs of numbers which make up each tree/subtree
	string bitholder = {};										// string to hold the 0s and 1s of the lead nodes
	string bitStrArr[256] = {};									// array that will hold all the paths to each of the leaves, table for encoding/ decoding
	node* root = NULL;
	node* treeMaker(node* nodearr[]);							 // private treemaker that takes the frequency array and uses that to make a huffman tree 
	void bitString(node* rootptr);								// takes in the root and travel in an in-order traversal creating a bit string or the path to each of the leafs
	node* decodeTreeMaker(int decodeArr[] );					// takes in a nodepair array and uses that to make a tree
	string paddingBitFinder(int bitsToPad, string bitsPathholder, node* rootptr); // uses logic to find out how many padding bits out of 8 are needed to complete the final bit 
	string binaryConverter(unsigned char character);			 //simple binary converter that converts the char into its binary representation
};
