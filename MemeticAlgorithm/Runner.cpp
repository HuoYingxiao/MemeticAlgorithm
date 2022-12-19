#include "Runner.h"

Runner::Runner() {
	MEME_OPTIONS.push_back(5);
	MEME_OPTIONS.push_back(5);
	MEME_OPTIONS.push_back(2);
	MEME_OPTIONS.push_back(3);

	MEME_OPTIONS_GAP.push_back(5);
	MEME_OPTIONS_GAP.push_back(4);
	MEME_OPTIONS_GAP.push_back(2);
	MEME_OPTIONS_GAP.push_back(2);
	MEME_OPTIONS_GAP.push_back(4);
	MEME_OPTIONS_GAP.push_back(3);
	//MEME_OPTIONS_GAP.push_back(3);
}

int Runner::getNumberOfRuns() {
	return TOTAL_RUNS;
}

void Runner::runTest_GAP(int trial) {
	GAPProblem* gap = new GAPProblem(MEMES_GAP, MEME_OPTIONS_GAP, POPULATION_SIZE);
	Multimeme_GAP_RWD* multiMeme_GAP = new Multimeme_GAP_RWD(gap, POPULATION_SIZE, INNOVATION_RATE);


	string filename = "gap_rwd_out" + to_string(trial);
	filename = filename + ".txt";
	ofstream fout, fout2;


	fout.open(filename, ios::out);


	int bestValue1 = -INT_MAX, worstValue1 = INT_MAX, currentValue1 = 0;
	int generationCount = 0;
	for (generationCount = 0; generationCount < MAX_GENERATION; generationCount++) {
		bestValue1 = -INT_MAX;
		worstValue1 = INT_MAX;
		multiMeme_GAP->runLoop();
		for (int i = 0; i < POPULATION_SIZE; i++) {
			currentValue1 = gap->getSolution(i)->costsEvaluate();
			if (currentValue1 > bestValue1)
				bestValue1 = currentValue1;
			if (currentValue1 < worstValue1)
				worstValue1 = currentValue1;
		}
		if (generationCount < numberOf)
			fout << "bestValue: " << -bestValue1 << " worstValue: " << -worstValue1 << endl;
	}
	fout.close();

	double bestValue = -INT_MAX;
	int bestSolution = 0;

	for (int i = 0; i < POPULATION_SIZE; i++) {
		double currentValue = gap->getSolution(i)->costsEvaluate();
		if (currentValue > bestValue) {
			bestValue = currentValue;
			bestSolution = i;
		}
	}
	bestValue = gap->getSolution(bestSolution)->costsEvaluate(1);
	//for (int i = 0; i < gap->getSolution(bestSolution)->getWorkers().size(); i++) {
	//	cout << gap->getSolution(bestSolution)->getWorkers()[i]->getNumberOfLargeTask() << endl;
	//}
	cout << "cost: " <<  - bestValue << endl;
	gap->getSolution(bestSolution)->printSolution();

}

void Runner::runTest_GAP_exp() {
	
	string filename = "100_" + to_string(POPULATION_SIZE);
	filename = filename + "_";
	filename = filename + to_string(INNOVATION_RATE);
	filename = filename + "_out_with_extra_local";
	filename = filename + ".txt";
	ofstream fout;


	fout.open(filename, ios::out);

	for (int exp = 0; exp < 20; exp++) {
		GAPProblem* gap = new GAPProblem(MEMES_GAP, MEME_OPTIONS_GAP, POPULATION_SIZE);
		Multimeme_GAP_RWD* multiMeme_GAP = new Multimeme_GAP_RWD(gap, POPULATION_SIZE, INNOVATION_RATE);
		int sum1 = 0;
		for (int i = 0; i < POPULATION_SIZE; i++) {
			int currentValue = gap->getSolution(i)->costsEvaluate();
			sum1 += currentValue;
		}
		double avg1 = sum1 / POPULATION_SIZE;


		//int bestValue1 = -INT_MAX, worstValue1 = INT_MAX, currentValue1 = 0;
		int generationCount = 0;
		for (generationCount = 0; generationCount < MAX_GENERATION; generationCount++) {
			multiMeme_GAP->runLoop();
		}
		

		double bestValue = -INT_MAX;
		int bestSolution = 0;
		int sum2 = 0;
		for (int i = 0; i < POPULATION_SIZE; i++) {
			int currentValue = gap->getSolution(i)->costsEvaluate();
			sum2 += currentValue;
			if (currentValue > bestValue) {
				bestValue = currentValue;
				bestSolution = i;
			}
		}
		bestValue = gap->getSolution(bestSolution)->costsEvaluate();
		//for (int i = 0; i < gap->getSolution(bestSolution)->getWorkers().size(); i++) {
		//	cout << gap->getSolution(bestSolution)->getWorkers()[i]->getNumberOfLargeTask() << endl;
		//}
		double avg = -sum2 / POPULATION_SIZE;
		double avg_optimization = avg / avg1;
		fout << -bestValue << "," << avg << "," << -avg_optimization << endl;
		cout << "cost: " << -bestValue << endl;
		gap->getSolution(bestSolution)->printSolution();
		delete gap;
		delete multiMeme_GAP;
	}
	fout.close();
}

void Runner::runTest_GAP_detail(int trial) {
	GAPProblem* gap = new GAPProblem(MEMES_GAP, MEME_OPTIONS_GAP, POPULATION_SIZE);
	Multimeme_GAP_RWD* multiMeme_GAP = new Multimeme_GAP_RWD(gap, POPULATION_SIZE, INNOVATION_RATE);


	string filename = "gap_rwd_out" + to_string(trial);
	string filename2 = filename + "_detail";
	filename2 = filename2 + ".txt";
	filename = filename + ".txt";
	ofstream fout, fout2;


	fout.open(filename, ios::out);
	fout2.open(filename2, ios::out);


	int bestValue1 = -INT_MAX, worstValue1 = INT_MAX, currentValue1 = 0;
	int generationCount = 0;
	for (generationCount = 0; generationCount < MAX_GENERATION; generationCount++) {
		bestValue1 = -INT_MAX;
		worstValue1 = INT_MAX;
		multiMeme_GAP->runLoop();
		for (int i = 0; i < POPULATION_SIZE; i++) {
			currentValue1 = gap->getSolution(i)->costsEvaluate();
			if (currentValue1 > bestValue1)
				bestValue1 = currentValue1;
			if (currentValue1 < worstValue1)
				worstValue1 = currentValue1;
		}
		if (generationCount < numberOf)
			fout << "bestValue: " << -bestValue1 << " worstValue: " << -worstValue1 << endl;
		for (int i = 0; i < gap->getSolutionMemory().size(); i++) {
			fout2 << -gap->getSolutionMemory()[i]->costsEvaluate() << ",";
		}
		fout2 << endl;
	}
	fout.close();

	double bestValue = -INT_MAX;
	int bestSolution = 0;

	for (int i = 0; i < POPULATION_SIZE; i++) {
		double currentValue = gap->getSolution(i)->costsEvaluate();
		if (currentValue > bestValue) {
			bestValue = currentValue;
			bestSolution = i;
		}
	}
	bestValue = gap->getSolution(bestSolution)->costsEvaluate(1);
	//for (int i = 0; i < gap->getSolution(bestSolution)->getWorkers().size(); i++) {
	//	cout << gap->getSolution(bestSolution)->getWorkers()[i]->getNumberOfLargeTask() << endl;
	//}
	cout << "cost: " << -bestValue << endl;
	gap->getSolution(bestSolution)->printSolution();

}

void Runner::runTest(int trial) {
	Knapsack* knapsack = new Knapsack(MEMES, MEME_OPTIONS, POPULATION_SIZE);
	MultiMeme* multiMeme = new MultiMeme(knapsack, POPULATION_SIZE, INNOVATION_RATE);
	string filename = "out" + to_string(trial);
	filename = filename + +".txt";
	ofstream fout;
	fout.open(filename, ios::out);

	double bestValue1 = -INT_MAX, worstValue1 = INT_MAX, currentValue1 = 0;
	int generationCount = 0;
	for (generationCount = 0; generationCount < MAX_GENERATION; generationCount++) {
		bestValue1 = -INT_MAX;
		worstValue1 = INT_MAX;
		multiMeme->runLoop();
		for (int i = 0; i < POPULATION_SIZE; i++) {
			currentValue1 = knapsack->getSolution(i)->totalValueOfItem();
			if (currentValue1 > bestValue1)
				bestValue1 = currentValue1;
			if (currentValue1 < worstValue1)
				worstValue1 = currentValue1;
		}
		if (generationCount < numberOf)
			fout << "bestValue: " << bestValue1 << " worstValue: " << worstValue1 << endl;
	}
	fout.close();

	double bestValue = -INT_MAX;
	int bestSolution = 0;

	for (int i = 0; i < POPULATION_SIZE; i++) {
		double currentValue = knapsack->getSolution(i)->totalValueOfItem();
		if (currentValue > bestValue) {
			bestValue = currentValue;
			bestSolution = i;
		}
	}

	cout << bestValue << endl;
	knapsack->getSolution(bestSolution)->printSolution();
}

void Runner::test() {
}

int main() {
	
	Runner* runner = new Runner();
	runner->runTest_GAP_exp();
	/*for (int i = 0; i < runner->getNumberOfRuns(); i++) {
		srand((unsigned)time(NULL));
		cout << "Trial#" << i + 1 << endl;
		//runner->runTest(i + 1);
		//runner->runTest_GAP(i + 1);
		runner->runTest_GAP_detail(i + 1);
	}*/
}