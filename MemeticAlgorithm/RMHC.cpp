#include "RMHC.h"

RMHC::RMHC(Knapsack* knapsack) 
	:HillClimbing(knapsack){

}

RMHC::RMHC(GAPProblem* gap)
	: HillClimbing(gap) {

}

void RMHC::setMoveAcceptance(int i) {
	if (i == 1 || i == 0)
		this->moveAcceptance = i;
}


void RMHC::localSearch(int solutionIndex) {
	if (problem == 1) {
		double bestValue = knapsack->getSolution(solutionIndex)->totalValueOfItem();
		double currentValue = 0;

		for (int i = 0; i < 20; i++) {
			int bitIndex = rand() % knapsack->getNumberOfItems();
			knapsack->bitFilp(bitIndex, solutionIndex);
			currentValue = knapsack->getSolution(solutionIndex)->totalValueOfItem();
			if (currentValue > bitIndex)
				bestValue = currentValue;
			else
				knapsack->bitFilp(bitIndex, solutionIndex);
		}
	}
	if (problem == 0) {
		int bestValue = gap->getSolution(solutionIndex)->costsEvaluate();
		int currentValue = bestValue;

		for (int i = 0; i < 20; i++) {
			int bitIndex = rand() % gap->getSolutionSize();
			int solutionAtIndex = gap->getSolution(solutionIndex)->getSolution()[bitIndex];
			gap->bitFlip(bitIndex, solutionIndex);
			currentValue = gap->getSolution(solutionIndex)->costsEvaluate();
			if (currentValue > bitIndex)
				bestValue = currentValue;
			else
				gap->getSolution(solutionIndex)->setSolutionAtIndex(solutionAtIndex, bitIndex);
		}
	}
}


void RMHC::localSearch(int solutionIndex, int timesOfSearch) {
	if (problem == 1) {
		double bestValue = knapsack->getSolution(solutionIndex)->totalValueOfItem();
		double currentValue = 0;

		for (int i = 0; i < timesOfSearch * 10; i++) {
			int bitIndex = rand() % knapsack->getNumberOfItems();
			knapsack->bitFilp(bitIndex, solutionIndex);
			currentValue = knapsack->getSolution(solutionIndex)->totalValueOfItem();
			if (currentValue > bitIndex)
				bestValue = currentValue;
			else
				knapsack->bitFilp(bitIndex, solutionIndex);
		}
	}
	if (problem == 0) {
		int bestValue = gap->getSolution(solutionIndex)->costsEvaluate();
		int currentValue = bestValue;

		for (int i = 0; i < timesOfSearch * 10; i++) {
			int bitIndex = rand() % gap->getSolutionSize();
			int solutionAtIndex = gap->getSolution(solutionIndex)->getSolution()[bitIndex];
			gap->bitFlip(bitIndex, solutionIndex);
			currentValue = gap->getSolution(solutionIndex)->costsEvaluate();
			if (currentValue > bitIndex)
				bestValue = currentValue;
			else
				gap->getSolution(solutionIndex)->setSolutionAtIndex(solutionAtIndex, bitIndex);
		}
	}
}