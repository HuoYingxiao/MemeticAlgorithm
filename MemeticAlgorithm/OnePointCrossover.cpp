#include "OnePointCrossover.h"


OnePointCrossover::OnePointCrossover(Knapsack* knapsack) 
	:knapsack(knapsack) 
	,gap(nullptr)
	,problem(1){
}

OnePointCrossover::OnePointCrossover(GAPProblem* gap)
	: gap(gap) 
	, knapsack(nullptr)
	,problem(0){
}

void OnePointCrossover::setProblem(int problem) {
	this->problem = problem;
}


void OnePointCrossover::crossover(int parent1, int parent2, int child1, int child2) {
	srand((unsigned)time(NULL));
	if (problem == 0) {
		int point = rand() % (this->gap->getSolutionSize() - 2) + 1;
		this->gap->copySolution(parent1, child1);
		this->gap->copySolution(parent2, child2);
		for (int i = 0; i < gap->getSolutionSize(); i++) {
			if (i < point)
				gap->exchangeBits(child1, child2, i);
		}

	}
	if (problem == 1) {
		int i = rand() % (this->knapsack->getNumberOfItems() - 2) + 1;
		this->knapsack->copySolution(parent1, child1);
		this->knapsack->copySolution(parent2, child2);

		for (parent1 = 0; parent1 < this->knapsack->getNumberOfItems(); parent1++) {
			if (parent1 < i) {
				this->knapsack->exchangeBits(child1, child2, parent1);
			}
		}
	}
}