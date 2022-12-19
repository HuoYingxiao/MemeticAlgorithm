#ifndef HILLCLIMBING
#define HILLCLIMBING

#include "Knapsack.h"
#include "GAPProblem.h"

class HillClimbing
{
public:
	HillClimbing(Knapsack* knapsack);
	HillClimbing(GAPProblem* gap);
	virtual void setMoveAcceptance(int i){}
	virtual void localSearch(int solutionIndex){}
protected:
	Knapsack* knapsack;
	GAPProblem* gap;
	int moveAcceptance;
	int problem;
};
#endif // !HILLCLIMBING