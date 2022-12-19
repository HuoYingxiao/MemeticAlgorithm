#pragma once
#include <iostream>
#include <vector>
#include <string>

#include "Solution.h"

//using namespace std;
class Knapsack
{
public:
	Knapsack(int numberOfMemes, vector<int> numberOfMemeOption, int populationSize);
	double getMaxWeight();
	Solution* getSolution(int Index);
	int getNumberOfItems();
	void copySolution(int originalIndex, int destinationIndex);
	void bitFilp(int bitIndex, int memoryIndex);
	void createSolution();
	void exchangeBits(int index1, int index2, int itemIndex);
	void loadInstance();
	vector<string> split(const string& str, const string& pattern);
private:
	int numberOfItems;
	vector<Solution*> solutionMemory;
	vector<double> valueOfItems;
	vector<double> weightOfItems;
	double maxWeight;
	double bestObjectFunction;
	int numberOfMemes;
	vector<int> numberOfMemeOption;
};

