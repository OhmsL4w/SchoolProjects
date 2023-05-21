// Main.cpp
//Date 11/28/21
//Course: EECS 2510
//Author: Ohm Rathod
//Descrption: Main of the word ladder project that checks the arguments and makes sure that the two
//words supplied are the same length.
#include "WordLadder.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;
int main(int argc, char* argv[])
{
	WordLadder* my_ladder;
	if (argc == 0 || argc < 4 || argc  > 4)
	{
		cout << "incorrect number of arguments";
		return -1;
	}
	string filename{};
	string startWord{}, endWord{};
	filename = argv[1];
	startWord = argv[2];
	endWord = argv[3];
	if (startWord.size() != endWord.size())
	{
		cout << "different length words";
		return -1;
	}
	my_ladder = new WordLadder(filename, startWord.size());
	for_each(startWord.begin(), startWord.end(), [](char& c)
	{
		c = ::toupper(c);
	});
	for_each(endWord.begin(), endWord.end(), [](char& c)
	{
		c = ::toupper(c);
	});
	vector<string> ladder = my_ladder->getMinLadder(startWord, endWord);
	my_ladder->displayResult(ladder);
}