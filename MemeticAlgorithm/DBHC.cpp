#include "DBHC.h"

DBHC::DBHC(Knapsack* knapsack) 
	:HillClimbing(knapsack){

}


DBHC::DBHC(GAPProblem* gap)
	: HillClimbing(gap) {

}

void DBHC::setMoveAcceptance(int i) {
	if (i == 1 || i == 0)
		this->moveAcceptance = i;
}

vector<int> DBHC::createRandomArray(int lengthOfArray) {
	srand((unsigned)time(NULL));
	vector<int> perm;

	for (int i = 0; i < lengthOfArray; i++) {
		perm.push_back(i);
	}

	for (int i = 0; i < lengthOfArray; i++) {
		int j = rand() % lengthOfArray;
		int temp = perm[i];
		perm[i] = perm[j];
		perm[j] = temp;
	}

	return perm;
}

void DBHC::localSearch(int solutionIndex) {
	if (problem == 1) {
		vector<int> perm = createRandomArray(this->knapsack->getNumberOfItems());
		double currentValue = this->knapsack->getSolution(solutionIndex)->totalValueOfItem();
		double changedValue;

		for (int i = 0; i < perm.size(); i++) {
			this->knapsack->bitFilp(perm[i], solutionIndex);
			changedValue = this->knapsack->getSolution(solutionIndex)->totalValueOfItem();
			if (moveAcceptance == 1) {
				if (changedValue >= currentValue) {
					currentValue = changedValue;
				}
				else {
					this->knapsack->bitFilp(perm[i], solutionIndex);
				}
			}
			else if (moveAcceptance == 0) {
				if (changedValue > currentValue)
					currentValue = changedValue;
				else
					this->knapsack->bitFilp(perm[i], solutionIndex);
			}
		}
	}
	if (problem == 0) {
		vector<int> perm = createRandomArray(gap->getSolutionSize());
		int currentValue = gap->getSolution(solutionIndex)->costsEvaluate();
		int changedValue = 0;
		int solutionAtIndex;
		for (int i = 0; i < perm.size(); i++) {
			solutionAtIndex = gap->getSolution(solutionIndex)->getSolution()[perm[i]];
			gap->bitFlip(perm[i], solutionIndex);
			changedValue = gap->getSolution(solutionIndex)->costsEvaluate();
			if (moveAcceptance == 1) {
				if (changedValue >= currentValue)
					currentValue = changedValue;
				else
					gap->getSolution(solutionIndex)->setSolutionAtIndex(solutionAtIndex, perm[i]);
			}
			else if (moveAcceptance == 0) {
				if (changedValue > currentValue)
					currentValue = changedValue;
				else
					gap->getSolution(solutionIndex)->setSolutionAtIndex(solutionAtIndex, perm[i]);
			}
		}
	}
}