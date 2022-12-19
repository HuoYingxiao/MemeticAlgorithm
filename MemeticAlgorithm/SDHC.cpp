#include "SDHC.h"

SDHC::SDHC(Knapsack* knapsack)
	:HillClimbing(knapsack) {

}

SDHC::SDHC(GAPProblem* gap) 
	:HillClimbing(gap){

}

void SDHC::setMoveAcceptance(int i) {
	if (i == 1 || i == 0) {
		this->moveAcceptance = i;
	}
}

void SDHC::localSearch(int solutionIndex) {
	if (problem == 1) {
		double currentValue = this->knapsack->getSolution(solutionIndex)->totalValueOfItem();
		double changedValue = -1000000;

		int index = -1;

		for (int i = 0; i < this->knapsack->getNumberOfItems(); i++) {
			this->knapsack->bitFilp(i, solutionIndex);
			changedValue = this->knapsack->getSolution(solutionIndex)->totalValueOfItem();
			if (moveAcceptance == 1) {
				if (changedValue >= currentValue) {
					index = i;
					currentValue = changedValue;
				}
			}
			else if (moveAcceptance == 0) {
				if (changedValue > currentValue) {
					index = i;
					currentValue = changedValue;
				}
			}
			this->knapsack->bitFilp(i, solutionIndex);
		}
		if (index != -1)
			this->knapsack->bitFilp(index, solutionIndex);
	}
	if (problem == 0) {
		int currentValue = this->gap->getSolution(solutionIndex)->costsEvaluate();
		int changedValue = currentValue;
		int index = -1;
		int solutionAtIndex = 0;

		for (int i = 0; i < gap->getSolutionSize(); i++) {
			solutionAtIndex = gap->getSolution(solutionIndex)->getSolution()[i];
			gap->bitFlip(i, solutionIndex);
			changedValue = gap->getSolution(solutionIndex)->costsEvaluate();
			if (moveAcceptance == 1) {
				if (changedValue >= currentValue) {
					index = i;
					currentValue = changedValue;
				}
			}
			else if (moveAcceptance == 0) {
				if (changedValue > currentValue) {
					index = i;
					currentValue = changedValue;
				}
			}
			gap->getSolution(solutionIndex)->setSolutionAtIndex(solutionAtIndex, i);
		}
		if (index != -1)
			gap->bitFlip(index, solutionIndex);
	}
}
