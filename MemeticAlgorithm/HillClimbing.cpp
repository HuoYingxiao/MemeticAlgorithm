#include "HillClimbing.h"


HillClimbing::HillClimbing(Knapsack* knapsack)
	:knapsack(knapsack)
	,gap(nullptr)
	,moveAcceptance(0)
	,problem(1){

}


HillClimbing::HillClimbing(GAPProblem* gap)
	:knapsack(nullptr)
	, gap(gap)
	, moveAcceptance(0)
	, problem(0) {

}