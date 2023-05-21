#pragma once
#include <string>
using namespace std;

class Prim
{
private:
	struct edge
	{
		string left, right;
		double weight = 0;
	};

public:
	
	Prim();
	~Prim();
	void PAlgorithm(string fileName);
	double PMSTWeight = 0;
	edge pop(edge queue[], int dimension);
	int findInArr(string vertices[], int dimension, string word);
};
