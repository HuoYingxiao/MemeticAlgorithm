#pragma once
#include "HillClimbing.h"
#include "Knapsack.h"

using namespace std;

class DBHC :
    public HillClimbing
{
public:
    DBHC(Knapsack* knapsack);
    DBHC(GAPProblem* gap);
    void setMoveAcceptance(int i) override;
    void localSearch(int solutionIndex) override;
    vector<int> createRandomArray(int lengthOfArray);
};

