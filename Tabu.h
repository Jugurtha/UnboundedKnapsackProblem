//
// Created by LENOVO on 01/05/2020.
//

#ifndef UNBOUNDEDKNAPSACKPROBLEM_TABU_H
#define UNBOUNDEDKNAPSACKPROBLEM_TABU_H

#include "commun.h"
#include "Neighbourhood.h"
#include "TabuList.h"
#include "Localizer.h"
#include "Fitness.h"
#include "StoppingCondition.h"

class Tabu {
public:
    Tabu(const Solution &initialSolution, TabuList &tabuList, unsigned int maxTabuSize,
         StoppingCondition &stoppingCondition, Fitness &fitness, Localizer &localizer);

    Solution search();
private:
    Solution initialSolution;
    TabuList & tabuList;
    unsigned int maxTabuSize;
    StoppingCondition & stoppingCondition;
    Fitness & fitness;
    Localizer & localizer;
};


#endif //UNBOUNDEDKNAPSACKPROBLEM_TABU_H
