#pragma once
#include "Knapsack.h"
#include "DBHC.h"
#include "RMHC.h"
#include "SDHC.h"
#include "OnePointCrossover.h"
#include "UniformCrossover.h"
#include "BitMutaion.h"
#include "Replacement.h"
#include "SimpleHeritance.h"
#include "TournamentSelection.h"

class MultiMeme
{
public:
	MultiMeme(Knapsack* knapsack, int populationSize, double innovationRate);
	void runLoop();
	void crossover(int memeIndex, int p1, int p2, int c1, int c2);
	int depthOfSearch();
	void local(int solutionIndex, int memeIndex);
	void mutationOfMeme(int solutionIndex);

private:
	Knapsack* knapsack;
	int populationSize;
	double innovationRate;
	DBHC* m_DBHC;
	RMHC* m_RMHC;
	SDHC* m_SDHC;
	HillClimbing* localS;
	OnePointCrossover* onePointXO;
	UniformCrossover* uniformXO;
	BitMutation* bitMutation;
	Replacement* replacement;
	SimpleHeritance* inheritance;
	TournamentSelection* selection;


};

