#include "SimpleHeritance.h"


SimpleHeritance::SimpleHeritance(Knapsack* knapsack)
	:knapsack(knapsack)
	,gap(nullptr)
	,problem(1){

}

SimpleHeritance::SimpleHeritance(GAPProblem* gap)
	:knapsack(nullptr)
	, gap(gap)
	, problem(0) {

}

void SimpleHeritance::inheritance(int p1, int p2, int c1, int c2) {
	if (problem == 1) {
		if (knapsack->getSolution(p1)->totalValueOfItem() == knapsack->getSolution(p2)->totalValueOfItem()) {
			double inherit = rand() / double(RAND_MAX);
			if (inherit >= 0.5) {
				knapsack->copySolution(p1, c1);
				knapsack->copySolution(p1, c2);
			}
			else {
				knapsack->copySolution(p2, c1);
				knapsack->copySolution(p2, c2);
			}
		}
		else if (knapsack->getSolution(p1)->totalValueOfItem() > knapsack->getSolution(p2)->totalValueOfItem()) {
			knapsack->copySolution(p1, c1);
			knapsack->copySolution(p1, c2);
		}
		else {
			knapsack->copySolution(p2, c1);
			knapsack->copySolution(p2, c2);
		}
	}

	if (problem == 0) {
		int p1Costs = gap->getSolution(p1)->costsEvaluate();
		int p2Costs = gap->getSolution(p2)->costsEvaluate();
		if (p1Costs == p2Costs) {
			double inherit = rand() / double(RAND_MAX);
			if (inherit >= 0.5) {
				gap->copySolution(p1, c1);
				gap->copySolution(p1, c2);
			}
			else {
				gap->copySolution(p2, c1);
				gap->copySolution(p2, c2);
			}
		}

		if (p1Costs > p2Costs) {
			gap->copySolution(p1, c1);
			gap->copySolution(p1, c2);
		}

		if (p1Costs < p2Costs) {
			gap->copySolution(p2, c1);
			gap->copySolution(p2, c2);
		}
	}
}