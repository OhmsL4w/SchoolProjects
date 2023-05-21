#include "Prim.h"
#include "LinkedList.h"
#include <iostream>
#include <fstream>
Prim::Prim()
{
}

Prim::~Prim()
{
}

void Prim::PAlgorithm(string fileName)
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
	LinkedList set ;							 // set linked list which holds the first N strings in a linked list of linked list
	edge* edgearr = new edge[twoXDimension];			 // edge linked list which will hold the weights 
	edge* Pqueue = new edge[twoXDimension];						 // edge array that will be used as a priority queue
	string* strsetarr = new string[dimension];					 // string that is used to read in the vertices
	string Vertices;
	for (int i = 0; i < dimension; i++)
	{
		openFile >> Vertices;
		strsetarr[i] = Vertices; 
	}
	int rowCount = 0, count = 0;								// rowcount is used to findout which row im on and use that word or letter while making an edge and count is just used to increase the position in the edge array
	double matrix;												// int holder for the numbers we read from the adjacency matrix
	while (count != (twoXDimension))							// reading in the adjaceny matrix
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
	int countCheck = 0;
	int whereToLook = 0;
	bool endOfProgram = false;
 	while (countCheck != twoXDimension)
	{
		for (int i = 0; i < dimension; i++,whereToLook++)							// loading all the adjacent vertices of the first vetice
		{
			if (edgearr[whereToLook].weight != 0)
			{
				for (int j = 0;j < twoXDimension; j++)
				{
					if (Pqueue[j].weight == 0)
					{
						Pqueue[j].left = edgearr[whereToLook].left;
						Pqueue[j].right = edgearr[whereToLook].right;
						Pqueue[j].weight = edgearr[whereToLook].weight;
						
						break;
					}

				}
				
			}
			countCheck++;
		}
		edge poppedEdge = pop(Pqueue, twoXDimension);
		bool leftWord = set.findInLL(set, poppedEdge.left);
		bool rightWord = set.findInLL(set, poppedEdge.right);
		if (leftWord == false || rightWord == false)
		{
			set.insert(poppedEdge.left);
			set.insert(poppedEdge.right);
			cout << "\n" << poppedEdge.left << " - " << poppedEdge.right << ": " << poppedEdge.weight;
			PMSTWeight = PMSTWeight + poppedEdge.weight;
		}
		else
		{
			
			while (rightWord != false)
			{
				poppedEdge = pop(Pqueue, twoXDimension);
				rightWord = set.findInLL(set, poppedEdge.right);
				if (countCheck == twoXDimension)
				{
					endOfProgram = true;
					break;
				}	
	
			}
			if (endOfProgram == true)
			{
				break;
			}
			set.insert(poppedEdge.left);
			set.insert(poppedEdge.right);
			cout << "\n" << poppedEdge.left << " - " << poppedEdge.right << ": " << poppedEdge.weight;
			PMSTWeight = PMSTWeight + poppedEdge.weight;
		
			
		}
		whereToLook = findInArr(strsetarr, dimension, poppedEdge.right);
		whereToLook = (whereToLook * dimension) ;
	

	}
	cout << "\nMST Weight for Prims Algorithm: " << PMSTWeight;
}

Prim::edge Prim::pop(edge queue[],int dimension)
{
	auto temp = INT_MAX;
	int index = 0;

	for (int i = 0; i < dimension; i++)
	{
		if (temp > queue[i].weight && queue[i].weight > 0)
		{
			temp = queue[i].weight;
			index = i;
		}
		if (temp == queue[i].weight)
		{
			if (queue[index].left == queue[i].left)
			{
				if (queue[index].right > queue[i].right)
				{
					index = i;
				}
			}
			if (queue[index].left < queue[i].left)
			{
				index = i;
			}
		}
	}
	edge tempedge = queue[index];
	queue[index].weight = 0;
	return(tempedge);
}

int Prim::findInArr(string vertices[],int dimension, string word)
{
	for (int i = 0; i < dimension; i++) 
	{
		if (vertices[i] == word)
		{
			return(i);
		}
	}
	return -1;
}
