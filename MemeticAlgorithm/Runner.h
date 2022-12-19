#pragma once
#include <vector>
#include "Knapsack.h"
#include "MultiMeme.h"
#include "Multimeme_GAP_RWD.h"
#include <fstream>

using namespace std;
class Runner
{
public:
	Runner();
	void runTest(int trial);
	void runTest_GAP(int trial);
	int getNumberOfRuns();
	void test();
	void runTest_GAP_detail(int trial);
	void runTest_GAP_exp();
private:
	const int TOTAL_RUNS = 5;
	const int MAX_GENERATION = 100;
	const int POPULATION_SIZE = 16;
	const double INNOVATION_RATE = 0.8;
	const int numberOf = 100;
	const int MEMES = 4;
	const int MEMES_GAP = 6;
	vector<int> MEME_OPTIONS;
	vector<int> MEME_OPTIONS_GAP;
};

