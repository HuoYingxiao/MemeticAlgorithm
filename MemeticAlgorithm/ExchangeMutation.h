#pragma once
#include "GAPProblem.h"
#include "Knapsack.h"

class ExchangeMutation
{
public:
	ExchangeMutation(Knapsack* knapsack);
	ExchangeMutation(GAPProblem* gap);
	void setMutationRate(int intensityOfMutation);
	void mutation(int solutionIndex);
private:
	double mutationRate;
	int solutionSize;
	Knapsack* knapsack;
	GAPProblem* gap;
	int problem;
};

