#include "Multimeme_GAP_RWD.h"


Multimeme_GAP_RWD::Multimeme_GAP_RWD(GAPProblem* gap, int populationSize, double innovationRate)
	:gap(gap)
	, populationSize(populationSize)
	, innovationRate(innovationRate) {
	srand((unsigned)time(NULL));
	m_DBHC = new DBHC(gap);
	m_RMHC = new RMHC(gap);
	m_SDHC = new SDHC(gap);
	localS = m_DBHC;

	onePointXO = new OnePointCrossover(gap);
	uniformXO = new UniformCrossover(gap);

	bitMutation = new BitMutation(gap);
	exchangeMutation = new ExchangeMutation(gap);

	replacement = new Replacement();
	selection = new TournamentSelection(gap, populationSize);
	inheritance = new SimpleHeritance(gap);
}


/*
0 - local search
1 - intensity of mutation
2 - crossover operator
3 - mutation operator
4 - intensity of mutation
5 - where to apply HC 0 --> after mutation
					  1 --> after crossover
					  2 --> both after mutation and crossover
(x)6 - balance large tasks

*/
void Multimeme_GAP_RWD::runLoop() {
	int t = 3;
	
	for (int i = 0; i < populationSize; i += 2) {
		int p1 = selection->tournament(t);
		int p2 = selection->tournament(t);
		while (p1 == p2)
			p2 = selection->tournament(t);
		int c1 = i + populationSize;
		int c2 = c1 + 1;

		int meme5OptionC1 = gap->getSolution(c1)->getMeme(5)->getMemeOption();
		int meme5OptionC2 = gap->getSolution(c2)->getMeme(5)->getMemeOption();

		this->crossover(2, p1, p2, c1, c2);

		//if (meme5OptionC1 == 1 || meme5OptionC1 == 2)
		//	local(c1, 0);
		//if (meme5OptionC2 == 1 || meme5OptionC2 == 2)
		//	local(c2, 0);
		this->inheritance->inheritance(p1, p2, c1, c2);

		mutationOfMeme(c1);
		mutationOfMeme(c2);

		mutation(c1, 3, 4);
		mutation(c2, 3, 4);

		//balanceLarge(c1, 6);
		//balanceLarge(c2, 6);
		//bitMutation->bitMutation(c1);
		//bitMutation->bitMutation(c2);

		//if (meme5OptionC1 == 0 || meme5OptionC1 == 2)
			local(c1, 0);
		//if (meme5OptionC2 == 0 || meme5OptionC2 == 2)
			local(c2, 0);
	}
	replacement->doReplacement(gap, populationSize);

	double bestValue = -2;
	for (int i = 0; i < this->populationSize; i++) {
		double currentValue = this->gap->getSolution(i)->costsEvaluate();
		if (currentValue > bestValue)
			bestValue = currentValue;
	}

}

vector<int> Multimeme_GAP_RWD::createRandomArray(int lengthOfArray) {
	srand((unsigned)time(NULL));
	vector<int> perm;

	for (int i = 0; i < lengthOfArray; i++) {
		perm.push_back(i);
	}

	for (int i = 0; i < lengthOfArray; i++) {
		int j = rand() % lengthOfArray;
		int temp = perm[i];
		perm[i] = perm[j];
		perm[j] = temp;
	}

	return perm;
}


void Multimeme_GAP_RWD::crossover(int memeIndex, int p1, int p2, int c1, int c2) {
	int option1 = gap->getSolution(p1)->getMeme(memeIndex)->getMemeOption();
	int option2 = gap->getSolution(p2)->getMeme(memeIndex)->getMemeOption();

	int cost1 = gap->getSolution(p1)->costsEvaluate();
	int cost2 = gap->getSolution(p2)->costsEvaluate();

	if (option1 == option2) {
		if (option1 == 0)
			onePointXO->crossover(p1, p2, c1, c2);
		if (option1 == 1)
			uniformXO->crossover(p1, p2, c1, c2);
	}
	else if (cost1 == cost2) {
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

int Multimeme_GAP_RWD::depthOfSearch() {
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
/*
void Multimeme_GAP_RWD::balanceLarge(int solutionIndex, int memeIndex) {
	int option = 1;
	if (memeIndex >= 0 && memeIndex < gap->getSolution(solutionIndex)->getMemes().size());
		option = gap->getSolution(solutionIndex)->getMeme(memeIndex)->getMemeOption();
	if (option == 10) {
		for (int i = 0; i < (gap->getSolution(solutionIndex)->getLargeWorks().size() / gap->getSolution(solutionIndex)->getWorkers().size()); i++) {
			vector<int> perm = createRandomArray(gap->getSolution(solutionIndex)->getWorkers().size());
			for (int j = 0; j < gap->getSolution(solutionIndex)->getWorkers().size(); j++) {
				int index1 = i * gap->getSolution(solutionIndex)->getWorkers().size() + j;
				if(index1 >= 0 && index1 < gap->getSolution(solutionIndex)->getLargeWorks().size())
					gap->getSolution(solutionIndex)->setSolutionAtIndex(perm[j], gap->getSolution(solutionIndex)->getLargeWorks()[index1]);
			}
		}
	}
}*/

void Multimeme_GAP_RWD::mutation(int solutionIndex, int memeIndexOperator, int memeIndexIOM) {
	int option = gap->getSolution(solutionIndex)->getMeme(memeIndexOperator)->getMemeOption();
	int iom = gap->getSolution(solutionIndex)->getMeme(memeIndexIOM)->getMemeOption();

	if (option == 0) {
		bitMutation->setMutationRate(iom);
		bitMutation->bitMutation(solutionIndex);
	}
	if (option == 1) {
		exchangeMutation->setMutationRate(iom);
		exchangeMutation->mutation(solutionIndex);
	}

	if (rand() % 10 < 5) {
		for (int i = 0; i < gap->getSolution(solutionIndex)->getLargeWorks().size(); i++) {
			if (rand() % 10 < iom)
				gap->bitFlip(solutionIndex, gap->getSolution(solutionIndex)->getLargeWorks()[i]);
		}
	}
}

void Multimeme_GAP_RWD::local(int solutionIndex, int memeIndex) {
	int option = gap->getSolution(solutionIndex)->getMeme(memeIndex)->getMemeOption();
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

void Multimeme_GAP_RWD::mutationOfMeme(int solutionIndex) {
	if ((rand() / double(RAND_MAX)) > innovationRate)
		return;
	int memeOption = 0;
	for (int i = 0; i < gap->getSolution(solutionIndex)->getMemes().size(); i++) {
		memeOption = rand() % gap->getSolution(solutionIndex)->getMeme(i)->getNumberOfOption();
		gap->getSolution(solutionIndex)->getMeme(i)->setMemeOption(memeOption);
	}
}