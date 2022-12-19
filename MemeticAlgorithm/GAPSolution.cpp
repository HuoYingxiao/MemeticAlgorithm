#include "GAPSolution.h"

GAPSolution::GAPSolution(vector<Worker*> workers, vector<int> solution, vector<int> specialWorkers, vector<int> noviceWorkers, vector<Meme*> memes, vector<int> LargeTasks, int percentageOfFree, int noviceTaskNum)
	:workers(workers)
	, numberOfTasks(static_cast<int>(solution.size()))
	, solution(solution)
	, memes(memes)
	, largeTasks(LargeTasks)
	,percentageOfFree(percentageOfFree)
	,noviceTaskNumber(noviceTaskNum)
	,specialWorkers(specialWorkers)
	,noviceWorkers(noviceWorkers){
	//this->noviceTaskNumber = noviceTaskNum;
}

GAPSolution::GAPSolution(int numberOfWorkers, int numberOfTasks, int numberOfMemes, vector<int> numberOfMemeOption) 
	: numberOfTasks(numberOfTasks)
	, percentageOfFree(0)
	, noviceTaskNumber(0){
	for (int i = 0; i < numberOfWorkers; i++) {
		Worker* newWorks = new Worker(i);
		workers.push_back(newWorks);
	}

	for (int i = 0; i < numberOfTasks; i++) {
		int initWorker = rand() % numberOfWorkers;
		solution.push_back(initWorker);
		
	}

	for (int i = 0; i < numberOfMemes; i++) {
		Meme* newMeme = new Meme(rand() % numberOfMemeOption[i], numberOfMemeOption[i]);
		memes.push_back(newMeme);
	}
}

void GAPSolution::initLargeTasks(vector<int> largeTask) {
	this->largeTasks = largeTask;
}

void GAPSolution::initTaskCost() {
	for (int i = 0; i < numberOfTasks; i++) {
		if (solution[i] >= workers.size()) {
			cout << "error1" << endl;
			exit(-1);
		}
		workers[solution[i]]->assignTask(i);
		//cout << largeTasks.size() << endl;
		for (int j = 0; j < largeTasks.size(); j++) {
			if (i == largeTasks[j]) {
				workers[solution[i]]->assignLargeTask();
				break;
			}
		}
	}
}

void GAPSolution::setPercentageOfFree(int pctOfFree) {
	percentageOfFree = pctOfFree;
}
void GAPSolution::setNoviceTaskNumber(int number) {
	noviceTaskNumber = number;
}

GAPSolution::GAPSolution(int numberOfWorkers, int numberOfTasks, vector<int> LargeTasks, int numberOfMemes, vector<int> numberOfMemeOption, int percentageOfFree, int noviceTaskNum)
	:largeTasks(LargeTasks)
	, percentageOfFree(percentageOfFree)
	, noviceTaskNumber(noviceTaskNum)
	,numberOfTasks(numberOfTasks){
	//this->noviceTaskNumber = noviceTaskNum;
	solution.clear();
	for (int i = 0; i < numberOfWorkers; i++) {
		Worker* newWorks = new Worker(i);
		workers.push_back(newWorks);
	}

	for (int i = 0; i < numberOfTasks; i++) {
		int initWorker = rand() % numberOfWorkers;
		solution.push_back(initWorker);
		workers[initWorker]->assignTask(i);
		for (int j = 0; j < largeTasks.size(); j++) {
			if (i == largeTasks[j]) {
				workers[initWorker]->assignLargeTask();
				break;
			}
		}
	}

	for (int i = 0; i < numberOfMemes; i++) {
		Meme* newMeme = new Meme(rand() % numberOfMemeOption[i], numberOfMemeOption[i]);
		memes.push_back(newMeme);
	}
}


void GAPSolution::refreshTaskStatus() {
	for (int i = 0; i < workers.size(); i++) {
		workers[i]->clearTasks();
		workers[i]->setLargeTask(0);
	}
	for (int i = 0; i < solution.size(); i++) {
		workers[solution[i]]->assignTask(i);
		for (int j = 0; j < largeTasks.size(); j++) {
			if (largeTasks[j] == i)
				workers[solution[i]]->assignLargeTask();
		}
	}
}

int GAPSolution::costsEvaluate(int i) {
	refreshTaskStatus();
	int cost = 0;
	for (int i = 0; i < solution.size(); i++) {
		cost += workers[solution[i]]->getCost(i);
	}
	for (int i = 0; i < workers.size(); i++) {
		if (workers[i]->getNumberOfLargeTask() > largeTasks.size() / workers.size()) {
			cout <<i << " " << workers[i]->getNumberOfLargeTask() << " " << largeTasks.size() / workers.size() << endl;
			cost +=  1000;
		}
		if (workers[i]->getTasks().size() > workers[i]->getMaximumTask()) {
			cout << "max" << endl;
			cost += (static_cast<int>(workers[i]->getTasks().size()) - workers[i]->getMaximumTask()) * 1000;
		}
		if (workers[i]->isSpecial()) {
			if (workers[i]->getTasks().size() < 1) {
				cout << "special" << endl;
				cost += 1000;
			}
			if ((workers[i]->getFreeTime() / workers[i]->getTimeCapacity()) * 100 < percentageOfFree) {
				cout << "special free" << endl;
				cost += 1000;
			}
		}
		//if (workers[i]->isNovice()) {
		//	if (workers[i]->getTasks().size() > noviceTaskNumber)
		//		cost += (workers[i]->getTasks().size() - noviceTaskNumber) * 1000;
		//}
	}
	return -cost;
}

int GAPSolution::costsEvaluate() {
	refreshTaskStatus();
	int cost = 0;
	for (int i = 0; i < solution.size(); i++) {
		cost += workers[solution[i]]->getCost(i);
	}
	for (int i = 0; i < workers.size(); i++) {
		if (workers[i]->getNumberOfLargeTask() > largeTasks.size() / workers.size()) {
			cost += ((workers[i]->getNumberOfLargeTask() - largeTasks.size() / workers.size()) * 100);
		}
		if (workers[i]->getTasks().size() > workers[i]->getMaximumTask())
			cost += (static_cast<int>(workers[i]->getTasks().size()) - workers[i]->getMaximumTask()) * 100;
		if (workers[i]->isSpecial()) {
			if (workers[i]->getTasks().size() < 1)
				cost += 100;
			if ((workers[i]->getFreeTime() / workers[i]->getTimeCapacity()) * 100 < percentageOfFree)
				cost += 100;
		}
		//if (workers[i]->isNovice()) {
		//	if (workers[i]->getTasks().size() > noviceTaskNumber)
		//		cost += (workers[i]->getTasks().size() - noviceTaskNumber) * 1000;
		//}
	}
	return -cost;
}

void GAPSolution::setSolutionAtIndex(int v, int index) {
	solution[index] = v;
}

vector<int> GAPSolution::getLargeWorks() {
	return largeTasks;
}

vector<int> GAPSolution::getSolution() {
	return solution;
}
vector<Meme*> GAPSolution::getMemes() {
	return memes;
}
Meme* GAPSolution::getMeme(int index) {
	return memes[index];
}
vector<Worker*> GAPSolution::getWorkers() {
	return workers;
}
void GAPSolution::flip(int index) {
	if (index >= 0 && index < solution.size()) {
		int newWorker = rand() % workers.size();
		while (newWorker == solution[index])
			newWorker = rand() % workers.size();

		//for (int i = 0; i < largeTasks.size(); i++) {
		//	if (index == i) {
		//		workers[solution[index]]->cancelLargeTask();
		//		workers[newWorker]->assignLargeTask();
		//	}
		//}
		//workers[solution[index]]->cancelTask(index);
		//workers[newWorker]->assignTask(index);
		solution[index] = newWorker;
	}
}

void GAPSolution::printSolution() {
	for (int i = 0; i < solution.size(); i++)
		cout << solution[i] << " ";
		//printf("%d ", solution[i]);
	//printf("\n");
	cout << endl;
	for (int i = 0; i < workers.size(); i++) {
		cout << "worker " << i << ": ";
		for (int j = 0; j < solution.size(); j++) {
			if (solution[j] == i)
				cout << j << " ";
		}
		cout << endl;
	}
}

GAPSolution* GAPSolution::deepCopy() {
	vector<Worker*> newWorkers;
	vector<int> newSolution;
	vector<Meme*> newMemes;

	for (int i = 0; i < memes.size(); i++) {
		newMemes.push_back(new Meme(this->memes[i]->getMemeOption(), this->memes[i]->getNumberOfOption()));
	}

	for (int i = 0; i < workers.size(); i++) {
		newWorkers.push_back(workers[i]->clone());
	}

	for (int i = 0; i < solution.size(); i++) {
		newSolution.push_back(solution[i]);
	}

	return new GAPSolution(newWorkers, newSolution, specialWorkers, noviceWorkers, newMemes, largeTasks, this->percentageOfFree, this->noviceTaskNumber);

}

void GAPSolution::setSpecialWorkers(vector<int> specialWorkers) {
	this->specialWorkers = specialWorkers;
}

void GAPSolution::setNoviceWorkers(vector<int> noviceWorkers) {
	this->noviceWorkers = noviceWorkers;
}