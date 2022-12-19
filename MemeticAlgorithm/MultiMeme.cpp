#include "MultiMeme.h"


MultiMeme::MultiMeme(Knapsack* knapsack, int populationSize, double innovationRate) 
	:knapsack(knapsack)
	,populationSize(populationSize)
	,innovationRate(innovationRate){

	m_DBHC = new DBHC(knapsack);
	m_RMHC = new RMHC(knapsack);
	m_SDHC = new SDHC(knapsack);
	localS = m_DBHC;

	onePointXO = new OnePointCrossover(knapsack);
	uniformXO = new UniformCrossover(knapsack);

	bitMutation = new BitMutation(knapsack);
	replacement = new Replacement();
	selection = new TournamentSelection(knapsack, populationSize);
	inheritance = new SimpleHeritance(knapsack);
}

/*
0 - local search
1 - intensity of mutation
2 - crossover operator
3 - where to apply HC 0 --> after mutation 
					  1 --> after crossover 
					  2 --> both after mutation and crossover

*/
void MultiMeme::runLoop() {
	int t = 3;
	for (int i = 0; i < populationSize; i += 2) {
		int p1 = selection->tournament(t);
		int p2 = selection->tournament(t);
		while (p1 == p2)
			p2 = selection->tournament(t);
		int c1 = i + populationSize;
		int c2 = c1 + 1;

		int meme3OptionC1 = knapsack->getSolution(c1)->getMeme(3)->getMemeOption();
		int meme3OptionC2 = knapsack->getSolution(c2)->getMeme(3)->getMemeOption();

		this->crossover(2, p1, p2, c1, c2);

		if (meme3OptionC1 == 1 || meme3OptionC1 == 2)
			local(c1, 0);
		if (meme3OptionC2 == 1 || meme3OptionC2 == 2)
			local(c2, 0);
		this->inheritance->inheritance(p1, p2, c1, c2);

		mutationOfMeme(c1);
		mutationOfMeme(c2);

		bitMutation->bitMutation(c1);
		bitMutation->bitMutation(c2);

		if (meme3OptionC1 == 0 || meme3OptionC1 == 2)
			local(c1, 0);
		if (meme3OptionC2 == 0 || meme3OptionC2 == 2)
			local(c2, 0);
	}
	replacement->doReplacement(knapsack, populationSize);

	double bestValue = -2;
	for (int i = 0; i < this->populationSize; i++) {
		double currentValue = this->knapsack->getSolution(i)->totalValueOfItem();
		if (currentValue > bestValue)
			bestValue = currentValue;
	}

}


void MultiMeme::crossover(int memeIndex, int p1, int p2, int c1, int c2) {
	int option1 = knapsack->getSolution(p1)->getMeme(memeIndex)->getMemeOption();
	int option2 = knapsack->getSolution(p2)->getMeme(memeIndex)->getMemeOption();

	double value1 = knapsack->getSolution(p1)->totalValueOfItem();
	double value2 = knapsack->getSolution(p2)->totalValueOfItem();

	if (option1 == option2) {
		if (option1 == 0)
			onePointXO->crossover(p1, p2, c1, c2);
		if (option1 == 1)
			uniformXO->crossover(p1, p2, c1, c2);
	}
	else if (value1 == value2) {
		if ((rand() / double(RAND_MAX)) > 0.5) {
			if (option1 == 0)
				onePointXO->crossover(p1, p2, c1, c2);
			if (option1 == 1)
				uniformXO->crossover(p1, p2, c1, c2);
		}
		else {
			if (option2 == 0)
				onePointXO->crossover(p1, p2, c1, c2);
			if (option2 == 1)
				uniformXO->crossover(p1, p2, c1, c2);
		}
	}
	else {
		if (option2 == 0)
			onePointXO->crossover(p1, p2, c1, c2);
		if (option2 == 1)
			uniformXO->crossover(p1, p2, c1, c2);
	}
}
int MultiMeme::depthOfSearch() {
	double dos = rand() / double(RAND_MAX);
	if ((dos >= 0.0) && (dos < 0.2))
		return 1;
	if ((dos >= 0.2) && (dos < 0.4))
		return 2;
	if ((dos >= 0.4) && (dos < 0.6))
		return 3;
	if ((dos >= 0.6) && (dos < 0.8))
		return 4;
	if ((dos >= 0.8) && (dos < 1.0))
		return 5;
	return 6;
}
void MultiMeme::local(int solutionIndex, int memeIndex) {
	int option = knapsack->getSolution(solutionIndex)->getMeme(memeIndex)->getMemeOption();
	int depthOfSearch = this->depthOfSearch();

	for (int i = 0; i < depthOfSearch; i++) {
		if (option == 4) {
			m_RMHC->localSearch(solutionIndex, depthOfSearch);
		}
		else {
			if (option == 0) {
				m_DBHC->setMoveAcceptance(0);
				m_DBHC->localSearch(solutionIndex);
			}
			if (option == 1) {
				m_DBHC->setMoveAcceptance(1);
				m_DBHC->localSearch(solutionIndex);
			}
			if (option == 2) {
				m_SDHC->setMoveAcceptance(0);
				m_SDHC->localSearch(solutionIndex);
			}
			if (option == 3) {
				m_SDHC->setMoveAcceptance(1);
				m_SDHC->localSearch(solutionIndex);
			}
		}
	}
}
void MultiMeme::mutationOfMeme(int solutionIndex) {
	if ((rand() / double(RAND_MAX)) > innovationRate)
		return;
	int memeOption = 0;
	for (int i = 0; i < knapsack->getSolution(solutionIndex)->getMemes().size(); i++) {
		memeOption = rand() % knapsack->getSolution(solutionIndex)->getMeme(i)->getNumberOfOption();
		knapsack->getSolution(solutionIndex)->getMeme(i)->setMemeOption(memeOption);
	}
}