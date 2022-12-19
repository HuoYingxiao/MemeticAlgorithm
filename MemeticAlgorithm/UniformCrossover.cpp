#include "UniformCrossover.h"

UniformCrossover::UniformCrossover(Knapsack* knapsack)
	:knapsack(knapsack) 
	,gap(nullptr)
	,problem(1){
}

UniformCrossover::UniformCrossover(GAPProblem* gap)
	: knapsack(nullptr)
	, gap(gap)
	, problem(0) {
}

void UniformCrossover::crossover(int parent1, int parent2, int child1, int child2) {
	srand((unsigned)time(NULL));
	if (problem == 1) {
		this->knapsack->copySolution(parent1, child1);
		this->knapsack->copySolution(parent2, child2);

		for (int i = 0; i < knapsack->getNumberOfItems(); i++) {
			if ((rand() % 10) < 5) {
				knapsack->exchangeBits(child1, child2, i);
			}
		}
	}
	if (problem == 0) {
		this->gap->copySolution(parent1, child1);
		this->gap->copySolution(parent2, child2);

		for (int i = 0; i < gap->getSolutionSize(); i++) {
			if ((rand() % 10) < 5)
				gap->exchangeBits(child1, child2, i);
		}
	}
}