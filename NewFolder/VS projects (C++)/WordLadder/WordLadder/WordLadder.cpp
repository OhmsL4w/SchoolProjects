//	WordLadder.cpp
//	Date 11/28/21
//	Course: EECS 2510
//	Author: Ohm Rathod
//	Descrption: cpp file that implements all the methods required for this project that were needed from the header file
//	This is the inner workings of the Wordladder project where it finds the shortest ladder from start word to end word.
//	which is by getting to the end word by only changing one letter
#include "WordLadder.h"
#include <iostream>
#include <fstream>
#include <list>
WordLadder::WordLadder(string lexiconFileName, int len) // constructor
{
	ifstream openFile;
	openFile.open(lexiconFileName, ifstream::in);
	if (openFile.good() == false)						// Trying to open the file by the name provided and exiting if we coudln't
	{	
		cout << "Error: could not open the file";
		exit;
	}
	string wordHolder;
	while (!openFile.eof())								// reading the file and storing the words with equal length as the start and end 
	{													// words into the lexicon set
		openFile >> wordHolder;
		if (wordHolder.length() == len)
		{
			lexicon.insert(wordHolder);
		}
	}

}

vector<string> WordLadder::getMinLadder(string start, string end)
{
	vector<string> ladder;			// empty ladder 
	vector<string> wordSeen;		// words seen to keep a track and not requeue the same words 
	vector<string> pred;			// predecessor
	list<string> Q;					// queue
	pred.push_back("");
	wordSeen.push_back(start);
	Q.push_back(start);

	while (Q.size() != 0)
	{
		
		set<string> neighbors = getNeighbors(Q.front());
		for (auto it : neighbors)
		{
			if (findInVector(wordSeen, it) == -1) {
				if (it == end)
				{
					wordSeen.push_back(it);
					pred.push_back(Q.front());
					string tempS = it;
					int tempIndex;
					while (tempS != start)
					{
						ladder.push_back(tempS);
						tempIndex = findInVector(wordSeen, tempS);
						tempS = pred[tempIndex];
					}
					ladder.push_back(start);
					return ladder;
				}
				else
				{
					pred.push_back(Q.front());
					wordSeen.push_back(it);
					Q.push_back(it);
				}
			}
		}
		Q.pop_front();
	}
	return ladder;
}

int WordLadder::getWordCount()
{
	return lexicon.size();								// returning how many words are in the lexicon 
}

void WordLadder::displayResult(vector<string> sequence)
{
	cout << "\nWord Ladder is:";
	if (sequence.size() == 0) 
	{
		cout << " empty" << endl;
		return;
	}
	for (int i = sequence.size() - 1; i >= 0  ; i--)
	{
		cout << " " << sequence[i];
	}
	cout << endl;
}

int WordLadder::findInVector(vector<string> vec, string findThis)
{
	for (int i = 0; i < vec.size(); i++) 
	{
		if (vec[i] == findThis)
		{
			return i;
		}
	}
	return -1;
	
}

bool WordLadder::isWord(string str)
{
	bool foundIt = lexicon.find(str) != lexicon.end();
	if (foundIt == true)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

bool WordLadder::isWordLadder(vector<string> sequence)
{
	bool itIs = false;
	for (int i = 0; i < sequence.size() - 1; i++)
	{
		int hamDist = getHammingDistance(sequence[i], sequence[i + 1]);
		if (hamDist ==  1)
		{
			itIs = true;
			continue;
		}
		else
		{
			itIs = false;
		}

	}
	return itIs;
}

set<string> WordLadder::getNeighbors(string word)
{
	set<string> neighbors;
	string temp;
	for (auto i = lexicon.begin(); i != lexicon.end(); i++)
	{
		temp = *i;
		int hamDistlen = getHammingDistance(word, temp);
		if (hamDistlen == 1)
		{
			neighbors.insert(*i);
		}

	}

	return neighbors;
}

int WordLadder::getHammingDistance(string str1, string str2)
{
	if (str1.size()!= str2.size())
	{
		return -1;
	}
	int hamDist = 0;
	for (int i = 0; i < str1.length(); i++)
	{
		if (str1[i] != str2[i])
		{
			hamDist++;
		}
	}
	
	return hamDist;
}
