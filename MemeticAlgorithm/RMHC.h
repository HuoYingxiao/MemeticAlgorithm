#pragma once
#include "HillClimbing.h"
class RMHC :
    public HillClimbing
{
public:
    RMHC(Knapsack* knapsack);
    RMHC(GAPProblem* gap);
    void setMoveAcceptance(int i) override;
    void localSearch(int solutionIndex) override;
    void localSearch(int solutionIndex, int timeOfSearch);
};

