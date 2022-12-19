#pragma once
#include "GAPSolution.h"
//#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class GAPProblem
{
public:
	GAPProblem(int numberOfMemes, vector<int> numberOfMemeOption, int populationSize);
	GAPSolution* getSolution(int Index);
	void copySolution(int originIndex, int destinationIndex);
	void bitFlip(int bitIndex, int memoryIndex);
	void createSolution();
	void exchangeBits(int index1, int index2, int taskIndex);
	void loadInstance();
	vector<string> split(const string& str, const string& pattern);
	int getSolutionSize();
	vector<GAPSolution*> getSolutionMemory();
private:
	int populationSize;
	int numberOfWorkers;
	int numberOfTasks;
	vector<int> largeTasks;
	vector<int> specialWorkers;
	vector<int> noviceWorkers;
	int maxTask;
	int maxTask_novice;
	int freeTimePct;
	vector<GAPSolution*> solutionMemory;
	int bestObjectFunction;
	int numberOfMemes;
	vector<int> numberOfMemeOption;
};

