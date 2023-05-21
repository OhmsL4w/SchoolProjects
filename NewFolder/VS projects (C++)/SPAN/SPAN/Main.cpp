//	Main.cpp
//	Date 12/5/21
//	Course: EECS 2510
//	Author: Ohm Rathod
//	Descrption: Main of the MST program that takes in the file name and redirects it to the algorithms
#include "Kruskal.h"
#include "Prim.h"
#include <iostream>
#include <string>

using namespace std;
int main(int argc, char* argv[])
{
	if (argc == 0)
	{
		cout << "incorrect number of arguments";
		return -1;
	}
	string filename = argv[1];
	Kruskal* KMST = new Kruskal;
	KMST->kAlgorithm(filename);
	Prim* PMST = new Prim;
	PMST->PAlgorithm(filename);
}