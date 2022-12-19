#pragma once
#include "Knapsack.h"
#include "GAPProblem.h"


class BitMutation
{
public:
	BitMutation(Knapsack* knapsack);
	BitMutation(GAPProblem* gap);
	void setMutationRate(int intensityOfMutation);
	void bitMutation(int solutionIndex);
private:
	double mutationRate;
	int solutionSize;
	Knapsack* knapsack;
	GAPProblem* gap;
	int problem;
};

