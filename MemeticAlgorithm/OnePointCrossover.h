#pragma once
#include "Knapsack.h"
#include "GAPProblem.h"

class OnePointCrossover
{
public:
	OnePointCrossover(Knapsack* knapsack);
	OnePointCrossover(GAPProblem* gap);
	void setProblem(int problem);
	void crossover(int parent1, int parent2, int child1, int child2);
private:
	Knapsack* knapsack;
	GAPProblem* gap;
	int problem;
};

