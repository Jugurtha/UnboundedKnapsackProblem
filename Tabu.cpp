//
// Created by LENOVO on 01/05/2020.
//

#include "Tabu.h"

Solution Tabu::search() {
    Solution sBest = initialSolution;
    auto bestCandidate = initialSolution;
    //tabuList = [];
    tabuList.push(initialSolution);
    while (! stoppingCondition())
    {
        auto sNeighborhood = localizer.getNeighbors(bestCandidate);
        bestCandidate = sNeighborhood.first();
        for (auto sCandidate : sNeighborhood)
            if ( (!tabuList.contains(sCandidate)) && (fitness(sCandidate) > fitness(bestCandidate)) )
                bestCandidate = sCandidate;
        if (fitness(bestCandidate) > fitness(sBest))
            sBest = bestCandidate;
        tabuList.push(bestCandidate);
        if (tabuList.size() > maxTabuSize)
            tabuList.pop();
    }
        
    return sBest;
}

Tabu::Tabu(const Solution &initialSolution, TabuList &tabuList, unsigned int maxTabuSize,
           StoppingCondition &stoppingCondition, Fitness &fitness, Localizer &localizer) : initialSolution(
        initialSolution), tabuList(tabuList), maxTabuSize(maxTabuSize), stoppingCondition(stoppingCondition),
                                                                                           fitness(fitness),
                                                                                           localizer(localizer) {}


