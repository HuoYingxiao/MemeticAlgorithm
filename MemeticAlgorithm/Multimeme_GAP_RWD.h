#pragma once
#include "DBHC.h"
#include "RMHC.h"
#include "SDHC.h"
#include "OnePointCrossover.h"
#include "UniformCrossover.h"
#include "BitMutaion.h"
#include "ExchangeMutation.h"
#include "Replacement.h"
#include "SimpleHeritance.h"
#include "TournamentSelection.h"
#include "GAPProblem.h"

class Multimeme_GAP_RWD
{
public:
	Multimeme_GAP_RWD(GAPProblem* gap, int populationSize, double innovationRate);
	void runLoop();
	void crossover(int memeIndex, int p1, int p2, int c1, int c2);
	int depthOfSearch();
	void local(int solutionIndex, int memeIndex);
	void mutationOfMeme(int solutionIndex);
	void mutation(int solutionIndex, int memeIndexOperator, int memeIndexIOM);
	void balanceLarge(int solutionIndex, int memeIndex);
	vector<int> createRandomArray(int lengthOfArray);

private:
	GAPProblem* gap;
	int populationSize;
	double innovationRate;
	DBHC* m_DBHC;
	RMHC* m_RMHC;
	SDHC* m_SDHC;
	HillClimbing* localS;
	OnePointCrossover* onePointXO;
	UniformCrossover* uniformXO;
	BitMutation* bitMutation;
	ExchangeMutation* exchangeMutation;
	Replacement* replacement;
	SimpleHeritance* inheritance;
	TournamentSelection* selection;
};

