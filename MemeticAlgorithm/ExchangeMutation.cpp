#include "ExchangeMutation.h"


ExchangeMutation::ExchangeMutation(Knapsack* knapsack)
	:knapsack (knapsack) 
	,mutationRate(1.0 / knapsack->getNumberOfItems())
	,gap(nullptr)
	,problem(1)
	,solutionSize(knapsack->getNumberOfItems()){

}
ExchangeMutation::ExchangeMutation(GAPProblem* gap)
	:gap(gap)
	, mutationRate(1.0 / gap->getSolutionSize())
	,knapsack(nullptr)
	,problem(0)
	,solutionSize(gap->getSolutionSize()){

}


void ExchangeMutation::setMutationRate(int intensityOfMutation) {
	if (problem == 0)
		this->mutationRate = (intensityOfMutation * 1.0) / (gap->getSolutionSize() * 1.0);
	if (problem == 1)
		this->mutationRate = (intensityOfMutation * 1.0) / (knapsack->getNumberOfItems() * 1.0);
}


void ExchangeMutation::mutation(int solutionIndex) {
	if (problem == 0) {
		int bitIndex = 0;
		for (int i = 0; i < solutionSize; i++) {
			if (rand() / double(RAND_MAX) < mutationRate) {
				bitIndex = rand() % solutionSize;
				if (bitIndex != i) {
					//cout << "1111";
					int temp = gap->getSolution(solutionIndex)->getSolution()[i];
					//cout << temp << gap->getSolution(solutionIndex)->getSolution()[bitIndex] << endl;
					gap->getSolution(solutionIndex)->setSolutionAtIndex(gap->getSolution(solutionIndex)->getSolution()[bitIndex], i);
					gap->getSolution(solutionIndex)->setSolutionAtIndex(temp, bitIndex);
				}
			}
		}
	}


	if (problem == 1) {
		int bitIndex = 0;
		for (int i = 0; i < solutionSize; i++) {
			if (rand() / double(RAND_MAX) < mutationRate) {
				bitIndex = rand() % solutionSize;
				if (bitIndex != i) {
					knapsack->bitFilp(i, solutionIndex);
					knapsack->bitFilp(bitIndex, solutionIndex);
				}
			}
		}
	}
}