// Main.cpp file
// Date: 10/10/21
// Course: EECS 2510
// Author: Ohm Rathod
// Description: The main part of the logic from where the program is redirected to a method depending on the input from the user.
// The input is taken as a command argument and is parsed to get the filenames according, what type of function the user wants to perfrom with the file(s)
// and the filename is then sent to their appropritate function.
// This project can Encode any file given to it using Huffman Encoding and it can also decode a Hufman encoded file. It uses the Huffman tree logic
// and flipping individual bits in a byte logic to encode a the file. this project can also create a tree builder file which would contain the pairs that made up the
// Huffman tree. While this project can encode & decode any file, any file apart from text file would need the appropriate outputfilename and extension according to the inputfile
// like input file is "tobeenocoded.jpg" the output file when decoding the encoded jpg should have a jpg extension like "decoded.jpg" and same thing goes for other types of files 
// This is to ensure the original file is produced when decoded instead of a txt file. Huffman encoding shortens the file size by encoding and it more secure than just sending important
// files as is.

#include <iostream>
#include <string>
#include <fstream>
#include"HUFF.h"
#include<time.h>

using namespace std;

int main(int argc, char* argv[]) 
{
	// validate user input and check thers only 1 param
	// open the file 
	// loop through the file byte by byte and increment counts for each character
	clock_t start = clock();
	Huffman* my_tree = new Huffman();

	if (argc == 0) 
	{
		cout << "incorrect number of arguments";
		return 1;
	}
	string command = argv[1];
	string temp{};
	string filenameholder{};				//strings to store the different filenames from the command argument input 
	string inputfilename{};
	string treefilename{};
	string outputfilename{};

	for (int i = 2; i < argc; i++)  // loops throught the command arguments and parses and gets the file names and stores it in appropriate string
	{
		filenameholder = argv[i];
		temp = filenameholder.substr(0, filenameholder.find(":") + 1);
		if (temp == "-i:") 
		{
			inputfilename = filenameholder.erase(0,3);
		}
		else if (temp == "-o:")
		{
			outputfilename = filenameholder.erase(0,3);
		}
		else if (temp == "-t:") 
		{

			treefilename = filenameholder.erase(0,3);
		}
		else
		{
			cout << "\nError invalid file command";
			return 1;
		}
	}
	// if else logic block to check what kind of function the user wants to perform
	if (command == "-me") 
	{
		if (argc < 4)
		{

			outputfilename = inputfilename;
			int periodfind = outputfilename.find('.');
			outputfilename.erase(periodfind, outputfilename.length() - periodfind);
			outputfilename += ".huf";

		}
		my_tree->EncodeFile(inputfilename, outputfilename);
	}
	else if (command == "-md")
	{
		if (argc < 4) 
		{

			outputfilename = filenameholder;
			int periodfind = outputfilename.find('.');
			outputfilename.erase(periodfind, outputfilename.length() - periodfind);
			outputfilename += ".txt";

		}
		
		my_tree->DecodeFile(inputfilename, outputfilename);
	}
	else if (command == "-mt") 
	{
		if (argc < 4)
		{

			outputfilename = filenameholder;
			int periodfind = outputfilename.find('.');
			outputfilename.erase(periodfind, outputfilename.length() - periodfind);
			outputfilename += ".htree";

		}
		my_tree->MakeTreeBuilder(inputfilename, outputfilename);
	}
	else if (command == "-met")
	{
		if (argc < 5 )
		{

			outputfilename = inputfilename;
			int periodfind = outputfilename.find('.');
			outputfilename.erase(periodfind, outputfilename.length() - periodfind);
			outputfilename += ".huf";

		}

		my_tree->EncodeFileWithTree(inputfilename, treefilename, outputfilename);
	}
	else if (command == "-h" || command == "-?" || command == "-help")
	{
		my_tree->DisplayHelp();
		return 1;
	}
	else 
	{
		cout << "\ninvalid commad";
		return 1;
	}
	cout << "Time: "<<(double)(clock() - start) / CLOCKS_PER_SEC << " seconds"; // to get the total time of the function too to execute

}