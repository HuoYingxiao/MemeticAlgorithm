#pragma once
#include "Knapsack.h"
#include "GAPProblem.h"

class SimpleHeritance
{
public:
	SimpleHeritance(Knapsack* knapsack);
	SimpleHeritance(GAPProblem* gap);
	void inheritance(int p1, int p2, int c1, int c2);
private:
	Knapsack* knapsack;
	GAPProblem* gap;
	int problem;
};

