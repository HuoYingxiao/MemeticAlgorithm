#pragma once
#include "Knapsack.h"
#include "GAPProblem.h"

class Replacement
{
public:
	Replacement();
	vector<int> getNextGeneration(Knapsack* knapsack, int populationSize);
	vector<int> getNextGeneration(GAPProblem* gap, int populationSize);
	void doReplacement(Knapsack* knapsack, int populationSize);
	void doReplacement(GAPProblem* gap, int populationSize);
};

