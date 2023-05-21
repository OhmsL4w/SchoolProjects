//	Kruskal.cpp//	Date 12/5/21
//	Course: EECS 2510
//	Author: Ohm Rathod
//	Descrption:Implementation of the Kruskal algorithm. takes in the file name and make outputs a minimum spanning tree out of it
#include"Kruskal.h"
#include <fstream>
#include <iostream>
Kruskal::Kruskal()
{

}

Kruskal::~Kruskal()
{
}

void Kruskal::kAlgorithm(string fileName)
{
	ifstream openFile;
	openFile.open(fileName, ifstream::in);
	if (openFile.good() == false)						// Trying to open the file by the name provided and exiting if we coudln't
	{
		cout << "Error: could not open the file";
		exit;
	}
	double dimension;
	openFile >> dimension;
	double twoXDimension = dimension * dimension;
	LinkedList* set = new LinkedList[dimension];				 // set linked list which holds the first N strings in a linked list of linked list
	edge* edgearr = new edge[dimension * dimension];			 // edge linked list which will hold the weights 
	string* strsetarr = new string[dimension];					 // string that is used to read in the vertices
	string Vertices;

	for (int i = 0; i < dimension; i++)
	{
		openFile >> Vertices;
		strsetarr[i] = Vertices;
		set[i].insert(Vertices);
	}
	
	int rowCount = 0, count = 0;								// rowcount is used to findout which row im on and use that word or letter while making an edge and count is just used to increase the position in the edge array
	double matrix;										        // int holder for the numbers we read from the adjacency matrix
	while (count!= (twoXDimension))								// reading in the adjaceny matrix
	{						
		for (int column = 0; column < dimension; column++)
		{
			openFile >> matrix;
			edgearr[count].left = strsetarr[rowCount];
			edgearr[count].right = strsetarr[column];
			edgearr[count].weight = matrix;
			count++;
		}
		rowCount++;
	}
	openFile.close();
	edge temp;
	for (int i = 0; i < (twoXDimension); i++) // sorting the array in ascending order
	{
		for (int j = 0; j < (twoXDimension); j++)
		{
			if (edgearr[i].weight < edgearr[j].weight)
			{
				temp = edgearr[i];
				edgearr[i] = edgearr[j];
				edgearr[j] = temp;
			}
		}
	}
	for (int i = 0; i < (twoXDimension); i++)
	{
		if (edgearr[i].weight == 0)
		{
			continue;
		}
		int leftWord = set->find(set, dimension, edgearr[i].left) ;
		int rightWord = set->find(set, dimension,edgearr[i].right);
		if (leftWord == rightWord)
		{
			edgearr[i].weight = 0;
		}
		else
		{
			set->Union(&set[leftWord], &set[rightWord]);
			
		}	
	}
	sortAndPrint(edgearr, twoXDimension);

}

void Kruskal::sortAndPrint(edge edgearr[], int twoXDimension)
{
	for (int i = 0; i < (twoXDimension); i++)
	{
		if (edgearr[i].weight != 0)
		{
			if (edgearr[i].left > edgearr[i].right)
			{
				string temp = edgearr[i].left;
				edgearr[i].left = edgearr[i].right;
				edgearr[i].right = temp;
			}

		}
	}
	edge temp;
	string first, second;
	for (int i = 0; i < (twoXDimension); i++) // sorting the array in ascending order
	{
		for (int j = 0; j < (twoXDimension); j++)
		{
			first = edgearr[i].left + edgearr[i].right;
			second = edgearr[j].left + edgearr[j].right;
			if (first < second)
			{
				temp = edgearr[i];
				edgearr[i] = edgearr[j];
				edgearr[j] = temp;
			}
		}
	}
	double MSTWeight = 0;
	for (int i = 0; i < (twoXDimension); i++)
	{
		if (edgearr[i].weight != 0)
		{
			cout << edgearr[i].left << " - " << edgearr[i].right << ": " << edgearr[i].weight<< endl;
			MSTWeight = MSTWeight + edgearr[i].weight;

		}
	}
	cout << "MST Weight for Kruskals Algorithm: " << MSTWeight << endl;
}


