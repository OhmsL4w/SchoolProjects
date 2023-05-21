// Huff.cpp file
// Date: 10/10/21
// Course: EECS 2510
// Author: Ohm Rathod
// Description: the inner workings of the tree and the methods that are implemented
// from the huff.h file.

#include "HUFF.h"
#include <fstream>
#include <iostream>
#include <string>


using namespace std;

Huffman::Huffman()
{
}
Huffman::~Huffman()
{
}
void Huffman::MakeTreeBuilder(string inputFile, string outputFile)
{
	std::ifstream ifs;
	ifs.open(inputFile, ifstream::in | ifstream::binary);
	if (ifs.good() == false) 
	{ //Checks if the file was able to be opened, returns if it wasn't
		cout << "Error: could not open the file";
		return;
	}
	unsigned char byte = ifs.get();
	int totalbytes{};
	int freq[256] = {};
	
	while (!ifs.eof()) // Reads the entire file while increment the count at the byte that occured in the file for example "ACT 1" count at ASCI value of A will be increased than C than T,etc
	{
		totalbytes++;
		freq[byte]++;
		byte = ifs.get();
	}
	node* nodefreq[256] = {};	// making the node array from the frequency array gotten from the file 
	for (int i = 0; i < 256; i++)
	{
		node* leafNode = new node();
		leafNode->symbol =  char(i);
		leafNode->weight = freq[i];
		nodefreq[i] = leafNode;
	}
	node* root = treeMaker(nodefreq); // sends the nodearray with the frequencies as the weights to make a huffman tree out of it.

	ofstream writeToOFile(outputFile, ios::binary); // Finally opens/makes an outputfile from the outputfilname provided to the function and writes 															
	for (int i = 0; i < 510; i++)					// the 510 node pairs that were used to make the tree 		
	{
		writeToOFile << unsigned char(nodePairs[i]);
	}
	writeToOFile.close(); // closing the outputfile and
	ifs.close();		  // input file

}

void Huffman::EncodeFile(string inputFile, string outputFile)
{
	std::ifstream ifs;
	ifs.open(inputFile, ifstream::in | ifstream::binary);
	if (ifs.good() == false) 
	{ 
		cout << "Error: could not open the file";
	}
	unsigned char byte = ifs.get();
	int totalBytesRead{};
	int freq[256] = {};
	while (!ifs.eof())
	{
		totalBytesRead++;
		freq[byte]++;
		byte = ifs.get();
	}
	node* nodefreq[256] = {};				

	for (int i = 0; i < 256; i++)
	{
		node* leafNode = new node();
		leafNode->symbol = char(i);
		leafNode->weight = freq[i];
		nodefreq[i] = leafNode;
	}
	node* root = treeMaker(nodefreq);				// same process til here of making the tree after reading the file and make a node frequency array and then making a tree from it
	bitString(root);								// getting the path to each of the leaves or the bitstring for each of the character using the tree;			

	ofstream writeToOFile(outputFile, ios::binary); // opening/making the ouputfile 
	ifs.clear();									// and bringing the pointer to the begining of the file input file
	ifs.seekg(0);
	unsigned char byteToWrite = 0;					// char to manipulate the individual bits and write it to file
	string bitsToflip{};							// string that holds the string paths thjat are to be converted into an array
	byte = ifs.get();

	while (!ifs.eof())								// while block that read in a character from the inputfile and writes the bitstring of the character stored in bitStrArr to the outputfile
	{		
		bitsToflip += bitStrArr[byte];
		int temp = bitsToflip.length();
		while (bitsToflip.length() <= 8) 
		{
			if (ifs.eof())
			{
				break;
			}
			byte = ifs.get();
			bitsToflip += bitStrArr[byte];
			
		}
		for (int i = 0; i <= 7; i++)			 // the bit string of the character is loaded into a string and depending on it the individual bits in a byte are flipped 
			{									 // and the resulting byte is printed out to the output file
			if (bitsToflip[i] == '1')
			{
					byteToWrite |= (1 << (7 - i));
			}
				
			}
	
			bitsToflip.erase(0, 8);
			writeToOFile << byteToWrite;
			byteToWrite = 0;
			byte = ifs.get();
	}
	if (bitsToflip.length() != 0) 
	{													// If block to flip the last of the bits while also
		int paddindToAdd = 8 - bitsToflip.length();		// sending the bit string to a method to get padded 
														// and switching the bits in the last byte and writing it out
		bitsToflip = paddingBitFinder(paddindToAdd, bitsToflip, root);
		for (int i = 0; i <= 7; i++)
		{
			if (bitsToflip[i] == '1') 
			{
				byteToWrite |= (1 << (7 - i));
			}
				
		}
		bitsToflip.erase(0, 8);
		writeToOFile << byteToWrite;
		byteToWrite = 0;
		
	}
	for (int i = 0; i < 510; i++)					//writing the node pairs that the tree produced at the end of the file and closing both 
	{												//input and output files
		writeToOFile << unsigned char(nodePairs[i]);
	}
	writeToOFile.close();
	ifs.close();

	
}

void Huffman::DecodeFile(string inputFile, string outputFile)
{

	std::ifstream ifs;
	ifs.open(inputFile, ifstream::in | ifstream::binary); // checks if file was opened properly
	if (ifs.good() == false) {
		cout << "Error: could not open the file";
	}
	int totalBytesRead{0};
	unsigned char byte = ifs.get();
	while (!ifs.eof()) // gettting to the end of the file while also counting how many chars were read
	{
		totalBytesRead++;
		byte = ifs.get();
	}
	int nodePairArr[510] = {};
	ifs.clear();		// reaching the point in file where the pairs of the nodes that made up the tree start
	int tempnodepairstart = totalBytesRead - 510;
	ifs.seekg(tempnodepairstart);
	
	for (int i = 0; i < 510; i++) //reding in the nodepairs and storing them in an array
	{
		byte = ifs.get();
		nodePairArr[i] = unsigned int(byte);
		
	}
	node * rootptr = decodeTreeMaker(nodePairArr);	  // sending the nodepair array in private method that will return the pointer to root with the tree built
	ifs.clear();								      // going back to the top of the file for the final reading and 
	ifs.seekg(0);									  // decoding
	string bitsForDecoding{};						  // string that will hold the multiple decoding bits so we can use it to traverse the tree
	node* travelnode = rootptr;
	ofstream writeToOFile(outputFile, ios::out | ios::binary);
	byte = ifs.get();
	bitsForDecoding = bitsForDecoding + binaryConverter(byte); // opening the file and converting the char into its binary reprensentation and loading into a string 
	int i = 1;
	while (bitsForDecoding.size() >= 0 && i < tempnodepairstart) // tree made from the last 510 bytes of the file is used to to decode the characters, the binary representation guides  
	{															// where we have to go in the tree 0 is a right and 1 is left, keep doing this until a leaf is reached and print that leafs
																// character to the ouput file
		while (travelnode->lch != NULL && travelnode->rch != NULL)
		{
			if (bitsForDecoding[0] == '1') 
			{
				travelnode = travelnode->rch;
				bitsForDecoding.erase(0, 1);

			}
			else if (bitsForDecoding[0] == NULL)
			{
				if (i < tempnodepairstart)
				{
					byte = ifs.get();
					bitsForDecoding = bitsForDecoding + binaryConverter(byte);
					i++;
					continue;
				}
				break;
			}
			else 
			{
				travelnode = travelnode->lch;
				bitsForDecoding.erase(0, 1);

			}

		}

		writeToOFile << travelnode->symbol;
		writeToOFile.flush();
		travelnode = rootptr;  // after printing out the character going back to the root to start again
		
	}
	writeToOFile.close();		//closing input and output files
	ifs.close();
}

void Huffman::EncodeFileWithTree(string inputFile, string treeFile, string outputFile)
{
	std::ifstream ifs;
	ifs.open(treeFile, ifstream::in | ifstream::binary); // checks if file was opened properly
	if (ifs.good() == false) 
	{
		cout << "Error: could not open the file";
		return;
	}
	unsigned char byte{};
	int nodePairArr[510] = {};
	for (int i = 0; i < 510; i++) //reading in the nodepairs and storing them in an array
	{
		byte = ifs.get();
		nodePairArr[i] = unsigned int(byte);

	}
	node* rootptr = decodeTreeMaker(nodePairArr); // making the tree with the tree file.
	bitString(rootptr);
	ifstream inputfilereader;
	inputfilereader.open(inputFile, ifstream::in | ifstream::binary);
	if (ifs.good() == false) 
	{
		cout << "Error: could not open the file";
		return;
	}
	ofstream writeToOFile(outputFile, ios::binary);

	byte = inputfilereader.get();
	string bitsToflip{};
	unsigned char byteToWrite = 0;// char to manipulate the individual bits and write it to file
	while (!inputfilereader.eof()) // same procedure as used in the encodefile function but this time using the the bitstring to each of the characters is made from 
	{							   // the tree builder file provided rest is same 
		bitsToflip += bitStrArr[byte];
		int temp = bitsToflip.length();
		while (bitsToflip.length() <= 8)
		{
			if (inputfilereader.eof())
			{
				break;
			}
			byte = inputfilereader.get();
			bitsToflip += bitStrArr[byte];

		}
		for (int i = 0; i <= 7; i++)
		{
			if (bitsToflip[i] == '1')
			{
				byteToWrite |= (1 << (7 - i));
			}

		}

		bitsToflip.erase(0, 8);
		writeToOFile << byteToWrite;
		byteToWrite = 0;
		byte = inputfilereader.get();
	}
	if (bitsToflip.length() > 8)
	{
		while (bitsToflip.length() > 8)
		{
			for (int i = 0; i <= 7; i++)
			{
				if (bitsToflip[i] == '1') {
					byteToWrite |= (1 << (7 - i));
				}
			}
			bitsToflip.erase(0, 8);
			writeToOFile << byteToWrite;
			byteToWrite = 0;
		}
	}
	if (bitsToflip.length() != 0) 
	{													// If block to flip the last of the bits while also
		int paddindToAdd = 8 - bitsToflip.length();		// sending the bit string to a method to get padded 
														// and switching the bits in the last byte and writing it out
		bitsToflip = paddingBitFinder(paddindToAdd, bitsToflip, root);
		for (int i = 0; i <= 7; i++)
		{
			if (bitsToflip[i] == '1') {
				byteToWrite |= (1 << (7 - i));
			}

		}
		bitsToflip.erase(0, 8);
		writeToOFile << byteToWrite;
		byteToWrite = 0;

	}
	for (int i = 0; i < 510; i++)
	{
		writeToOFile << unsigned char(nodePairArr[i]);
	}
	writeToOFile.close();			// closing all the files
	ifs.close();	
	inputfilereader.close();
}

void Huffman::DisplayHelp() 
{								// help function that shows what functions the user has avialable to use and how to use them
	cout << "\n -me encode file (input file, output file)" <<
		"\n-md decode file (input file, output file)" <<
		"\n-mt build a tree-builder from a file (input file, ouput file)" <<
		"\n-met encode a file with a specified tree-builder file (input file, tree-builder file, outputfile)" <<
		"\n-m followed byt anything other than 'e', 'd', 't', or 'et' is not valid" <<
		"\n-h, -?, -help to ask for help " <<
		"\nTo specify the input file, use -i:<filename>" <<
		"\nTo specify the output file, use -o:<filename>" <<
		"\nTo specify the tree-builder input file, use -t<filename>" << 
		"\nExample input for encoding with a treefiel-> -me -i:inputfilename -t:Treebuilderfilename -o:ouputfilename" ;
}

Huffman::node* Huffman::treeMaker(node * nodearr[])
{
	int firstnum, secondnum, firstnodeweight, secondnodeweight, count;
	firstnum = secondnum = firstnodeweight = secondnodeweight = INT_MAX;
	count = 0;
	// uses the node arr and find 2 mins in 1 go and uses those two mins and makes an internal node with those two nodes as its left and right child
	// and it keeps doing this until each of the nodes have been used up and there remains only 1 single tree;
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			if (nodearr[j] == NULL)
			{
				continue;
			}

			if (nodearr[j]->weight < firstnodeweight) 
			{
				secondnodeweight = firstnodeweight;
				firstnodeweight = nodearr[j]->weight;
				secondnum = firstnum;
				firstnum = j;
			}
			else if (nodearr[j]->weight < secondnodeweight)
			{
				secondnodeweight = nodearr[j]->weight;
				secondnum = j;
			}
		}
		if (firstnum == secondnum) 
		{
			break;
		}
		nodePairs[count] = firstnum;
		count++;
		nodePairs[count] = secondnum;
		count++;
		node* internalNode = new node();
		internalNode->weight = nodearr[firstnum]->weight + nodearr[secondnum]->weight;
		internalNode->lch = nodearr[firstnum];
		internalNode->rch = nodearr[secondnum];
		nodearr[firstnum] = internalNode;
		nodearr[secondnum] = NULL;
		firstnodeweight = secondnodeweight = INT_MAX;
	}
	nodearr[0] = nodearr[firstnum]; // changing the trees location from fistnum to 0, but think its not necessary as im returning the root anyways
	nodearr[firstnum] = NULL;
	root = nodearr[0];
	
	return root;
}

void Huffman::bitString(node* rootptr)
{ // uses a in-oder traversal recursion to make the bitstring for the corresponding character and stores it in the bitStrArr at the appropriate place
	if (rootptr->lch != NULL) 
	{
		bitholder.append("0");
		bitString(rootptr->lch);
	}
	if (rootptr->lch == NULL && rootptr->rch == NULL) 
	{
		bitStrArr[rootptr->symbol] = bitholder ;
	
	}
	
	if (rootptr->rch != NULL) 
	{
		bitholder.append("1");
		bitString(rootptr->rch);
	}
	if (rootptr != root) 
	{
		bitholder.pop_back();
	}
	
}

Huffman::node* Huffman::decodeTreeMaker(int decodeArr[])
{
	node* tempnodefreq[256] = {  };
	int tempfirstnum = 0;
	for (int i = 0; i < 256; i++)	//makes a temp array with all nodes = to their indices 
	{								//use this temp array to make the tree for decoding
		node* leafNode = new node();
		leafNode->symbol = char(i);
		tempnodefreq[i] = leafNode;
	}
	for (int i = 0; i <= 508; i+=2)
	{	// for loop that uses the indices passed into the array to make the tree
		node* internalNode = new node();
		internalNode->lch = tempnodefreq[decodeArr[i]];
		internalNode->rch = tempnodefreq[decodeArr[i+1]];
		tempnodefreq[decodeArr[i]] = internalNode;
		tempnodefreq[decodeArr[i + 1]] = NULL;
		tempfirstnum = decodeArr[i];
	}
	root = tempnodefreq[tempfirstnum];
	return root;
}

string Huffman::paddingBitFinder(int bitsToPad, string bitsPathholder, node* rootptr)
{
	node* templag = NULL;									
	while (bitsToPad > 0)						// while loop that keeps going until a string long enough to = bitsToPad int is found and return that string
												// the string cant be a leaf and has to be an internal node which mean looking 2 steps ahead 
												// travelling back and forth if needed while making the string 
	{
		
		if (rootptr->lch->lch == NULL && rootptr->lch->rch == NULL 
			&& rootptr->rch->rch==NULL &&rootptr->rch->lch== NULL) 
		{
			bitsToPad++;
			bitsPathholder.pop_back();
			if (rootptr == templag->lch) 
			{
				rootptr = templag;
				rootptr = rootptr->rch;
			}
			else 
			{
				rootptr = templag;
				rootptr = rootptr->lch;
			}
		}
		if (rootptr->lch->lch != NULL && rootptr->lch->rch != NULL) 
		{
			bitsToPad--;
			bitsPathholder.append("0");
			templag = rootptr;
			rootptr = rootptr->lch;
			continue;
		}
		if (rootptr->rch->lch != NULL && rootptr->rch->rch != NULL) 
		{
			bitsToPad--;
			bitsPathholder.append("1");
			templag = rootptr;
			rootptr = rootptr->rch;
			continue;
		}
		
	}
	return bitsPathholder;
}

string Huffman::binaryConverter(unsigned char character)
{
	string binaryNum{};
	string temp{};
	int tempnum = character;
	// simple int to binary converter using mod and division 
	while (tempnum != 0)
	{
		temp = temp + to_string(tempnum % 2);
		tempnum = tempnum / 2;
	}
	if (temp.length() != 8) 
	{
		while (temp.length() < 8) 
		{
			temp.append("0");
		}
	}
	for (int i =  temp.length()-1; i>= 0; i--)
	{
		 binaryNum = binaryNum + temp[i];
	}
	
	temp = {};
	return binaryNum;
}
