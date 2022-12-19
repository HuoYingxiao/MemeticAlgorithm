#pragma once
#include "Knapsack.h"
#include "GAPProblem.h"

class UniformCrossover
{
public:
	UniformCrossover(Knapsack* knapsack);
	UniformCrossover(GAPProblem* gap);
	void crossover(int parent1, int parent2, int child1, int child2);
private:
	Knapsack* knapsack;
	GAPProblem* gap;
	int problem;
};

