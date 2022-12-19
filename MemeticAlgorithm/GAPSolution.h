#pragma once
#include <vector>
#include "Worker.h"
#include "Meme.h"

using namespace std;
class GAPSolution
{
public:
	GAPSolution(vector<Worker*> workers, vector<int> solution, vector<int> specialWorkers, vector<int> noviceWorkers, vector<Meme*> memes, vector<int> LargeTasks, int percentageOfFree, int noviceTaskNumber);
	GAPSolution(int numberOfWorkers, int numberOfTasks, vector<int> LargeTasks, int numberOfMemes, vector<int> numberOfMemeOption, int percentageOfFree, int noviceTaskNumber);
	GAPSolution(int numberOfWorkers, int numberOfTasks, int numberOfMemes, vector<int> numberOfMemeOption);
	int costsEvaluate();
	vector<int> getSolution();
	vector<Meme*> getMemes();
	Meme* getMeme(int index);
	vector<Worker*> getWorkers();
	void flip(int index);
	void setSolutionAtIndex(int v, int index);
	void printSolution();
	GAPSolution* deepCopy();
	void setSpecialWorkers(vector<int> specialWorkers);
	void setNoviceWorkers(vector<int> noviceWorkers);
	void initLargeTasks(vector<int> largeTask);
	void initTaskCost();
	void setPercentageOfFree(int pctOfFree);
	void setNoviceTaskNumber(int number);
	void refreshTaskStatus();
	int costsEvaluate(int i);
	vector<int> getLargeWorks();
private:
	vector<Worker*> workers;
	vector<int> solution;
	vector<Meme*> memes;
	vector<int> largeTasks;
	vector<int> specialWorkers;
	vector<int> noviceWorkers;
	int percentageOfFree;
	int noviceTaskNumber;
	int numberOfTasks;
};

