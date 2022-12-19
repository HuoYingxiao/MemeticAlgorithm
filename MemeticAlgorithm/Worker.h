#pragma once
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
class Worker
{
public:
	Worker(int index);
	Worker(int index, vector<int> costs, vector<int> timeConsume, int maxTask);
	void assignTask(int task);
	void cancelTask(int task);
	void assignLargeTask();
	void cancelLargeTask();
	void setLargeTask(int num);
	void setSpecial(int special);
	void setNovice(int novice);
	void setCosts(vector<int> costs);
	void setTimeConsume(vector<int> timeConsume);
	void setTimeCapacity(int time);
	void setFreeTime(int freeTime);
	void setMaxTasks(int maxTasks);
	int isSpecial();
	int isNovice();
	int getFreeTime();
	int getCost(int task);
	int getTimeConsume(int task);
	int getMaximumTask();
	int getTimeCapacity();
	int getNumberOfLargeTask();
	vector<int> getTasks();
	Worker* clone();
	void clearTasks();
private:
	int index;
	vector<int> costs;
	vector<int> timeConsume;
	vector<int> tasks;
	int freeTime;
	int timeCapacity;
	int maximumTasks;
	int special;
	int novice;
	int numberOfLargeTask;
};

