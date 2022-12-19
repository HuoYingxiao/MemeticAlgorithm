#include "Knapsack.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "Item.h"
#include "Meme.h"
#include "Solution.h"
#include <vector>

using namespace std;

Knapsack::Knapsack(int numberOfMemes, vector<int> numberOfMemeOption, int populationSize) 
	:bestObjectFunction(0)
	,numberOfMemes(numberOfMemes)
	,numberOfMemeOption(numberOfMemeOption){
	this->loadInstance();
	for (int i = 0; i < populationSize << 1; i++) {
		this->createSolution();
	}
}

double Knapsack::getMaxWeight() {
	return maxWeight;
}

void Knapsack::createSolution() {
	Solution* newSolution = new Solution(this->numberOfItems, this->maxWeight, this->numberOfMemes, this->numberOfMemeOption);
	for (int i = 0; i < this->numberOfItems; i++) {
		newSolution->getItems()[i]->setValue(valueOfItems[i]);
		newSolution->getItems()[i]->setWeight(weightOfItems[i]);
	}
	this->bestObjectFunction = max(this->bestObjectFunction, newSolution->totalValueOfItem());
	solutionMemory.push_back(newSolution);
}

void Knapsack::loadInstance() {
	ifstream fin;
	//instance_23_10000.txt instance_15_375.txt
	fin.open("instance_23_10000.txt", ios::in);
	string str;
	vector<string> buffer;
	getline(fin, str);
	buffer = split(str, " ");
	this->numberOfItems = atoi(buffer[0].c_str());
	this->maxWeight = atof(buffer[1].c_str());
	while (getline(fin, str)) {
		buffer = split(str, " ");
		this->valueOfItems.push_back(atof(buffer[0].c_str()));
		this->weightOfItems.push_back(atof(buffer[1].c_str()));
	}
	fin.close();
}

vector<string> Knapsack::split(const string& str, const string& pattern) {
	vector<string> ret;
	if (pattern.empty())
		return ret;
	size_t start =0, index = str.find_first_of(pattern, 0);
	while (index != str.npos) {
		if (start != index)
			ret.push_back(str.substr(start, index - start));
		start = index + 1;
		index = str.find_first_of(pattern, start);
	}
	if (!str.substr(start).empty())
		ret.push_back(str.substr(start));
	return ret;
}

Solution* Knapsack::getSolution(int Index) {
	return solutionMemory[Index];
}

int Knapsack::getNumberOfItems() {
	return numberOfItems;
}

void Knapsack::copySolution(int originIndex, int destinationIndex) {
	if (originIndex >= 0 && originIndex < this->solutionMemory.size()) {
		if (destinationIndex >= 0 && destinationIndex < this->solutionMemory.size()) {
			Solution* newSolution = this->solutionMemory[originIndex]->deepCopy();
			this->solutionMemory[destinationIndex] = newSolution;
		}
		else {
			Solution* newSolution = this->solutionMemory[originIndex]->deepCopy();
			this->solutionMemory.push_back(newSolution);
		}
	}
}

void Knapsack::bitFilp(int bitIndex, int memoryIndex) {
	if (memoryIndex >= 0 && memoryIndex < this->solutionMemory.size() && this->solutionMemory[memoryIndex] != NULL) {
		this->solutionMemory[memoryIndex]->flip(bitIndex);
	}
}

void Knapsack::exchangeBits(int index1, int index2, int itemIndex) {
	if (index1 >= 0 && index1 < this->solutionMemory.size()) {
		if (index2 >= 0 && index2 < this->solutionMemory.size()) {
			if (this->solutionMemory[index1] != NULL && this->solutionMemory[index2] != NULL) {
				if (itemIndex >= 0 && itemIndex < this->getNumberOfItems()) {
					double item1Value = this->solutionMemory[index1]->getItems()[itemIndex]->getValue();
					double item1Weight = this->solutionMemory[index1]->getItems()[itemIndex]->getWeight();
					double item2Value = this->solutionMemory[index2]->getItems()[itemIndex]->getValue();
					double item2Weight = this->solutionMemory[index2]->getItems()[itemIndex]->getWeight();
					
					this->solutionMemory[index1]->getItems()[itemIndex]->setValue(item1Value);
					this->solutionMemory[index1]->getItems()[itemIndex]->setWeight(item1Weight);
					this->solutionMemory[index2]->getItems()[itemIndex]->setValue(item2Value);
					this->solutionMemory[index2]->getItems()[itemIndex]->setWeight(item2Weight);
				}
			}
		}
	}
}

