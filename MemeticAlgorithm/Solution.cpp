
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "Meme.h"
#include "Item.h"
#include "Solution.h"

using namespace std;

Solution::Solution(vector<Item*> items, vector<int> solution, double maxWeight, vector<Meme*> memes)
	:items(items)
	, solution(solution)
	, maxWeight(maxWeight)
	, memes(memes) {

}

Solution::Solution(int numberOfItems, double maxWeight, int numberOfMemes, vector<int> numberOfMemeOption)
	:maxWeight(maxWeight){
	for (int i = 0; i < numberOfItems; i++) {
		Item* newItem = new Item(i);
		items.push_back(newItem);
	}
	
	for (int i = 0; i < numberOfItems; i++) {
		solution.push_back(rand() % 2);
		//cout << solution[i];
	}
	//cout << endl;

	
	
	for (int i = 0; i < numberOfMemes; i++) {
		Meme* newMeme = new Meme(rand() % numberOfMemeOption[i], numberOfMemeOption[i]);
		memes.push_back(newMeme);
	}
	
}

vector<int> Solution::getSolution() {
	return this->solution;
}

vector<Meme*> Solution::getMemes() {
	return this->memes;
}

Meme* Solution::getMeme(int memeIndex) {
	return this->memes[memeIndex];
}

vector<Item*> Solution::getItems() {
	return this->items;
}

double Solution::totalValueOfItem() {
	double value = 0;
	double weight = 0;
	for (int i = 0; i < this->solution.size(); i++) {
		if (this->solution[i] == 1) {
			weight += items[i]->getWeight();
			value += items[i]->getValue();
		}
		if (weight > maxWeight) {
			return -weight;
		}
	}
	return value;
}

void Solution::flip(int Index) {
	if (Index >= 0 && Index < solution.size()) {
		if (solution[Index] == 0) {
			solution[Index] = 1;
			return;
		}
		if (solution[Index] == 1)
			solution[Index] = 0;
	}
}

void Solution::printSolution() {
	for (int i = 0; i < solution.size(); i++) {
		printf("%d", solution[i]);
	}
	printf("\n");
}

Solution* Solution::deepCopy() {
	vector<Item*> newItems;
	vector<int> newSolution;
	vector<Meme*> newMemes;

	for (int i = 0; i < memes.size(); i++) {
		newMemes.push_back(new Meme(this->memes[i]->getMemeOption(), this->memes[i]->getNumberOfOption()));
	}

	for (int i = 0; i < items.size(); i++) {
		newItems.push_back(items[i]->clone());
	}

	for (int i = 0; i < solution.size(); i++) {
		newSolution.push_back(solution[i]);
	}

	return new Solution(newItems, newSolution, this->maxWeight, newMemes);
}