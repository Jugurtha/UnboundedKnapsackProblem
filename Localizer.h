//
// Created by LENOVO on 01/05/2020.
//

#ifndef UNBOUNDEDKNAPSACKPROBLEM_LOCALIZER_H
#define UNBOUNDEDKNAPSACKPROBLEM_LOCALIZER_H

#include "commun.h"
#include "Neighbourhood.h"

class Localizer {
public:
    Localizer(Instance const& instance);

    virtual Neighbourhood getNeighbors(Solution center) = 0;

protected:
    Objects const& sortedObjects();

    Objects const& objects;
    const int maxWeight;
    const bool sorted;
};



#endif //UNBOUNDEDKNAPSACKPROBLEM_LOCALIZER_H
