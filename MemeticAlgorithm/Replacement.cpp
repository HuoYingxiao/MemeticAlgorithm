#include "Replacement.h"

Replacement::Replacement() {}

vector<int> Replacement::getNextGeneration(Knapsack* knapsack, int populationSize) {
	vector<int> nextGeneration;
	vector<double> valueOfItem;
	for (int i = 0; i < populationSize; i++) {
		nextGeneration.push_back(i);
	}
	for (int i = 0; i < populationSize << 2; i++) {
		valueOfItem.push_back(0.0);
	}
	double bestValue = -INT_MAX;
	double worstValue = INT_MAX;
	int bestIndex = -1;
	int worstIndex = -1;

	for (int i = 0; i < populationSize << 1; i++) {
		double currentValue = knapsack->getSolution(i)->totalValueOfItem();
		valueOfItem[i] = currentValue;
		if ((i >= populationSize) && (currentValue >= bestValue)) {
			bestValue = currentValue;
			bestIndex = i;
		}

		if (currentValue < worstValue) {
			worstIndex = i;
			worstValue = currentValue;
		}
	}

	if (worstIndex < populationSize) {
		nextGeneration[worstIndex] = bestIndex;
	}

	return nextGeneration;

}
void Replacement::doReplacement(Knapsack* knapsack, int populationSize) {
	vector<int> nextPopulation = this->getNextGeneration(knapsack, populationSize);
	for (int i = 0; i < populationSize; i++) {
		if (i != nextPopulation[i])
			knapsack->copySolution(nextPopulation[i], i);
	}
}

vector<int> Replacement::getNextGeneration(GAPProblem* gap, int populationSize) {
	vector<int> nextGeneration;
	vector<int> costs;
	for (int i = 0; i < populationSize; i++) {
		nextGeneration.push_back(i);
	}
	for (int i = 0; i < populationSize << 2; i++) {
		costs.push_back(0);
	}
	double bestValue = -INT_MAX;
	double worstValue = INT_MAX;
	int bestIndex = -1;
	int worstIndex = -1;

	for (int i = 0; i < populationSize << 1; i++) {
		int currentValue = gap->getSolution(i)->costsEvaluate();
		costs[i] = currentValue;
		if ((i >= populationSize) && (currentValue >= bestValue)) {
			bestValue = currentValue;
			bestIndex = i;
		}

		if (currentValue < worstValue) {
			worstIndex = i;
			worstValue = currentValue;
		}
	}

	if (worstIndex < populationSize) {
		nextGeneration[worstIndex] = bestIndex;
	}

	return nextGeneration;

}


void Replacement::doReplacement(GAPProblem* gap, int populationSize) {
	vector<int> nextPopulation = this->getNextGeneration(gap, populationSize);
	for (int i = 0; i < populationSize; i++) {
		if (i != nextPopulation[i])
			gap->copySolution(nextPopulation[i], i);
	}
}