#include "Worker.h"
#include <algorithm>

Worker::Worker(int index)
	:index(index)
	,timeCapacity(0)
	,maximumTasks(0)
	,freeTime(0)
	,special(0)
	,novice(0)
	,numberOfLargeTask(0){

}

Worker::Worker(int index, vector<int> costs, vector<int> time, int maxTask)
	:index(index)
	,costs(costs)
	,timeConsume(time)
	,maximumTasks(maxTask)
	,timeCapacity(0)
	,freeTime(0)
	,special(0)
	,novice(0)
	,numberOfLargeTask(0){

}

void Worker::clearTasks() {
	tasks.clear();
}

void Worker::assignTask(int task) {
	tasks.push_back(task);
	if (task >= 0 && task < timeConsume.size()) {
		freeTime -= timeConsume[task];
	}
	else {
		cout << task << " " << timeConsume.size() << endl;
		cout << "time consume loaded fail" << endl;
		exit(-1);
	}
}

void Worker::cancelTask(int task) {
	swap(tasks[task], *(end(tasks) - 1));
	tasks.pop_back();
	freeTime += timeConsume[task];
}

void Worker::assignLargeTask() {
	numberOfLargeTask++;
}

void Worker::cancelLargeTask() {
	if(numberOfLargeTask > 0)
		numberOfLargeTask--;
}

int Worker::getNumberOfLargeTask() {
	return numberOfLargeTask;
}

int Worker::getFreeTime() {
	return freeTime;
}
void Worker::setCosts(vector<int> costs) {
	this->costs = costs;
}
void Worker::setTimeConsume(vector<int> timeConsume) {
	this->timeConsume = timeConsume;
}

void Worker::setTimeCapacity(int time) {
	timeCapacity = time;
	freeTime = timeCapacity;
}

void Worker::setMaxTasks(int maxTasks) {
	maximumTasks = maxTasks;
}

int Worker::isSpecial() {
	return special;
}
int Worker::isNovice() {
	return novice;
}
int Worker::getCost(int task) {
	if(task >= 0 && task < costs.size())
		return costs[task];
	else {
		cout << "failed to get cost" << endl;
		return 0;
	}
}
int Worker::getTimeConsume(int task) {
	return timeConsume[task];
}
int Worker::getMaximumTask() {
	return maximumTasks;
}
int Worker::getTimeCapacity() {
	return timeCapacity;
}

void Worker::setSpecial(int special) {
	this->special = special;
}


void Worker::setNovice(int novice) {
	this->novice = novice;
}

vector<int> Worker::getTasks() {
	return tasks;
}

void Worker::setLargeTask(int num) {
	numberOfLargeTask = num;
}

void Worker::setFreeTime(int freeTime) {
	this->freeTime = freeTime;
}

Worker* Worker::clone() {
	vector<int> newCosts;
	vector<int> newTimeConsume;

	for (int i = 0; i < costs.size(); i++) {
		newCosts.push_back(costs[i]);
	}
	for (int i = 0; i < timeConsume.size(); i++) {
		newTimeConsume.push_back(timeConsume[i]);
	}
	Worker* newWorker = new Worker(this->index, newCosts, newTimeConsume, maximumTasks);

	newWorker->setNovice(novice);
	newWorker->setSpecial(special);
	newWorker->setLargeTask(numberOfLargeTask);
	newWorker->setTimeCapacity(timeCapacity);
	//newWorker->setFreeTime(this->freeTime);

	for (int i = 0; i < tasks.size(); i++) {
		newWorker->assignTask(tasks[i]);
	}

	return newWorker;
}