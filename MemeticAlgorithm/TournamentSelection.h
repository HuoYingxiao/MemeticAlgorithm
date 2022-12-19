#pragma once
#include "Knapsack.h"
#include "GAPProblem.h"

class TournamentSelection
{
public:
	TournamentSelection(Knapsack* knapsack, int populationSize);
	TournamentSelection(GAPProblem* gap, int populationSize);
	vector<int> createRandomArray(int lengthOfArray);
	int tournament(int tournamentSize);
private:
	int populationSize;
	Knapsack* knapsack;
	GAPProblem* gap;
	int problem;
};

