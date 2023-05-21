#pragma once
#include <string>
#include "LinkedList.h"
using namespace std;


class Kruskal
{
public:
	Kruskal();
	~Kruskal();
	void kAlgorithm(string fileName);
private:
	struct edge
	{
		string left, right;
		double weight = 0;
	};
	void sortAndPrint(edge edgearr[], int twoXDimension);
};

