#include "TournamentSelection.h"


TournamentSelection::TournamentSelection(Knapsack* knapsack, int populationSize)
	:knapsack(knapsack)
	,gap(nullptr)
	,populationSize(populationSize)
	,problem(1){

}

TournamentSelection::TournamentSelection(GAPProblem* gap, int populationSize) 
	:knapsack(nullptr)
	,gap(gap)
	,populationSize(populationSize)
	,problem(0) {

}

vector<int> TournamentSelection::createRandomArray(int lengthOfArray) {
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
int TournamentSelection::tournament(int tournamentSize) {
	int currentIndex = 0;
	if (problem == 0){
		int currentValue = -INT_MAX;

		vector<int> perm = createRandomArray(this->populationSize);
		for (int i = 0; i < tournamentSize; i++) {
			int index = perm[i];
			int value = gap->getSolution(perm[i])->costsEvaluate();
			if (value > currentValue) {
				currentValue = value;
				currentIndex = index;
			}
		}
	}
	if (problem == 1) {
		double currentValue = -1000000.0;

		vector<int> perm = createRandomArray(this->populationSize);
		for (int i = 0; i < tournamentSize; i++) {
			int index = perm[i];
			double value = this->knapsack->getSolution(perm[i])->totalValueOfItem();
			if (value > currentValue) {
				currentValue = value;
				currentIndex = index;
			}
		}
	}
	return currentIndex;
}