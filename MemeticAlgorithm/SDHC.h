#pragma once
#include "HillClimbing.h"
#include "Knapsack.h"
class SDHC :
    public HillClimbing
{
public:
    SDHC(Knapsack* knapsack);
    SDHC(GAPProblem* gap);
    void setMoveAcceptance(int i) override;
    void localSearch(int solutionIndex) override;
   

};

