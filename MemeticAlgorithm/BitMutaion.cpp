#include "BitMutaion.h"

BitMutation::BitMutation(Knapsack* knapsack) 
	:knapsack(knapsack)
	, solutionSize(knapsack->getNumberOfItems())
	,mutationRate(1.0 / knapsack->getNumberOfItems())
	, gap(nullptr)
	, problem(1){
}

BitMutation::BitMutation(GAPProblem* gap)
	:knapsack(nullptr)
	, solutionSize(gap->getSolutionSize())
	, mutationRate(1.0 / gap->getSolutionSize())
	, gap(gap)
	, problem(0) {
}





void BitMutation::setMutationRate(int intensityOfMutation) {
	this->mutationRate = (intensityOfMutation * 1.0) / (this->solutionSize * 1.0);
}


void BitMutation::bitMutation(int solutionIndex) {
	if(problem == 0){
	
		for (int i = 0; i < gap->getSolutionSize(); i++) {
			if (((double)rand() / RAND_MAX) < this->mutationRate)
				gap->bitFlip(i, solutionIndex);
		}
	}
	if (problem == 1) {
		for (int i = 0; i < this->knapsack->getNumberOfItems(); i++) {
			if (((double)rand() / RAND_MAX) < this->mutationRate)
				this->knapsack->bitFilp(i, solutionIndex);
		}
	}
}