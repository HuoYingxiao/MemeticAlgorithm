#include "GAPProblem.h"


GAPProblem::GAPProblem(int numberOfMemes, vector<int> numberOfMemeOption, int populationSize) 
	:numberOfMemes(numberOfMemes)
	,numberOfMemeOption(numberOfMemeOption)
	,populationSize(populationSize){
	loadInstance();

	for (int i = 0; i < solutionMemory.size(); i++) {
		//solutionMemory[i]->printSolution();
		solutionMemory[i]->initTaskCost();
	}
}

GAPSolution* GAPProblem::getSolution(int Index) {
	return solutionMemory[Index];
}
void GAPProblem::copySolution(int originIndex, int destinationIndex) {
	if (originIndex >= 0 && originIndex < this->solutionMemory.size()) {
		if (destinationIndex >= 0 && destinationIndex < this->solutionMemory.size()) {
			GAPSolution* newSolution = this->solutionMemory[originIndex]->deepCopy();
			GAPSolution* oldSolution = this->solutionMemory[destinationIndex];
			this->solutionMemory[destinationIndex] = newSolution;
			for (int i = 0; i < oldSolution->getWorkers().size(); i++) {
				delete(oldSolution->getWorkers()[i]);
			}
			oldSolution->getWorkers().clear();
			delete(oldSolution);
		}
		else {
			GAPSolution* newSolution = this->solutionMemory[originIndex]->deepCopy();
			this->solutionMemory.push_back(newSolution);
		}
	}
}

int GAPProblem::getSolutionSize() {
	return numberOfTasks;
}

void GAPProblem::bitFlip(int bitIndex, int memoryIndex) {
	if (memoryIndex >= 0 && memoryIndex < this->solutionMemory.size() && this->solutionMemory[memoryIndex] != NULL) {
		this->solutionMemory[memoryIndex]->flip(bitIndex);
	}
}



void GAPProblem::createSolution() {
	GAPSolution* newSolution = new GAPSolution(numberOfWorkers, numberOfTasks, numberOfMemes, numberOfMemeOption);
	solutionMemory.push_back(newSolution);
}


void GAPProblem::exchangeBits(int index1, int index2, int taskIndex) {
	if (index1 >= 0 && index1 < this->solutionMemory.size()) {
		if (index2 >= 0 && index2 < this->solutionMemory.size()) {
			if (this->solutionMemory[index1] != NULL && this->solutionMemory[index2] != NULL) {
				if (taskIndex >= 0 && taskIndex < this->numberOfWorkers) {
					int index1Worker = solutionMemory[index1]->getSolution()[taskIndex];
					solutionMemory[index1]->getSolution()[taskIndex] = solutionMemory[index2]->getSolution()[taskIndex];
					solutionMemory[index2]->getSolution()[taskIndex] = index1Worker;
				}
			}
		}
	}
}

vector<GAPSolution*> GAPProblem::getSolutionMemory() {
	return solutionMemory;
}

//gap-rwd-large.txt gap-rwd-medium.txt  gap-rwd-small.txt
void GAPProblem::loadInstance() {
	ifstream fin;
	fin.open("gap-rwd-large.txt", ios::in);
	string instance = "Instance L2";
	string str;
	vector<string> buffer;
	vector<int> costs, timeConsume;
	while (getline(fin, str)) {
		//cout << "111" << endl;
		if (str != instance)
			continue;
		else {
			
			getline(fin, str);
			buffer = split(str, " ");
			numberOfWorkers = atoi(buffer[0].c_str());
			numberOfTasks = atoi(buffer[1].c_str());
			for (int i = 0; i < populationSize << 1; i++) {
				this->createSolution();
			}

			buffer.clear();
			for (int i = 0; i < numberOfWorkers; i++) {
				buffer.clear();
				getline(fin, str);
				buffer = split(str, " ");
				costs.clear();
				for (int j = 0; j < buffer.size(); j++) {
					costs.push_back(atoi(buffer[j].c_str()));
				}
				for (int j = 0; j < solutionMemory.size(); j++) {
					solutionMemory[j]->getWorkers()[i]->setCosts(costs);
				}
			}
			buffer.clear();
			for (int i = 0; i < numberOfWorkers; i++) {
				buffer.clear();
				getline(fin, str);
				buffer = split(str, " ");
				timeConsume.clear();
				for (int j = 0; j < buffer.size(); j++) {
					timeConsume.push_back(atoi(buffer[j].c_str()));
				}
				for (int j = 0; j < solutionMemory.size(); j++) {
					solutionMemory[j]->getWorkers()[i]->setTimeConsume(timeConsume);
				}
			}
			buffer.clear();
			getline(fin, str);
			vector<string> timeCapacity1 = split(str, " ");;
			//for (int i = 0; i < numberOfWorkers; i++) {
			//	for (int j = 0; j < solutionMemory.size(); j++) {
			//		solutionMemory[j]->getWorkers()[i]->setTimeCapacity(atoi(buffer[i].c_str()));
			//	}
			//}
			getline(fin, str);
			maxTask = atoi(str.c_str());
			//for (int i = 0; i < numberOfWorkers; i++) {
			//	for (int j = 0; j < solutionMemory.size(); j++) {
			//		solutionMemory[j]->getWorkers()[i]->setTimeCapacity(atoi(buffer[i].c_str()));
			//		solutionMemory[j]->getWorkers()[i]->setMaxTasks(maxTask);
			//	}
			//}

			buffer.clear();
			getline(fin, str);
			buffer = split(str, " ");
			for (int i = 0; i < buffer.size(); i++) {
				specialWorkers.push_back(atoi(buffer[i].c_str()) - 1);
			}
			
			getline(fin, str);
			freeTimePct = atoi(str.c_str());
			buffer.clear();

			getline(fin, str);
			buffer = split(str, " ");
			for (int i = 0; i < buffer.size(); i++) {
				largeTasks.push_back(atoi(buffer[i].c_str()) - 1);
			}
			buffer.clear();

			getline(fin, str);
			buffer = split(str, " ");
			for (int i = 0; i < buffer.size(); i++) {
				noviceWorkers.push_back(atoi(buffer[i].c_str()) - 1);
			}
			buffer.clear();

			getline(fin, str);
			maxTask_novice = atoi(str.c_str());
			for (int i = 0; i < numberOfWorkers; i++) {
				for (int j = 0; j < solutionMemory.size(); j++) {
					solutionMemory[j]->getWorkers()[i]->setTimeCapacity(atoi(timeCapacity1[i].c_str()));
					solutionMemory[j]->getWorkers()[i]->setMaxTasks(maxTask);
				}
			}

			for (int i = 0; i < solutionMemory.size(); i++) {
				solutionMemory[i]->setSpecialWorkers(specialWorkers);
				solutionMemory[i]->setNoviceWorkers(noviceWorkers);
				solutionMemory[i]->setNoviceTaskNumber(maxTask_novice);
				solutionMemory[i]->initLargeTasks(largeTasks);
			}
			break;
		}
	}
	

	//cout << solutionMemory[0]->getWorkers().size() << " " << solutionMemory[1]->getWorkers()[4]->getCost(5) << endl;
}

vector<string> GAPProblem::split(const string& str, const string& pattern) {
	vector<string> ret;
	if (pattern.empty())
		return ret;
	size_t start = 0, index = str.find_first_of(pattern, 0);
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