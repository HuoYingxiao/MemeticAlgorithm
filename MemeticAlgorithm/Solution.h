#pragma once
#include <vector>
#include "Item.h"
#include "Meme.h"
using namespace std;
class Solution
{
	
public:
	Solution(vector<Item*> items, vector<int> solution, double maxWeight, vector<Meme*> memes);
	Solution(int numberOfItems, double maxWeight, int numberOfMemes, vector<int> numberOfMemeOption);
	vector<int> getSolution();
	vector<Meme*> getMemes();
	Meme* getMeme(int memeIndex);
	vector<Item*> getItems();
	void flip(int Index);
	void printSolution();
	double totalValueOfItem();
	Solution* deepCopy();
private:
	vector<Item*> items;
	vector<int> solution;
	vector<Meme*> memes;
	double maxWeight;
	
};

